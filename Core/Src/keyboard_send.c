#include "keyboard_send.h"
typedef enum 
    {
        /*------------------------- HID report data -------------------------*/
        
		LEFT_CTRL = -8,//1
		LEFT_SHIFT = -7,//2
		LEFT_ALT = -6,//3
		LEFT_GUI = -5,//4
        RIGHT_CTRL = -4,//5
		RIGHT_SHIFT = -3,//6
		RIGHT_ALT = -2,//7
		RIGHT_GUI = -1,//8
        RESERVED = 0,//9
		ERROR_ROLL_OVER,//10
		POST_FAIL,//11
		ERROR_UNDEFINED,//12
        A,B,C,D,E,F,G,H,I,J,K,L,M,//14
        N,O,P,Q,R,S,T,U,V,W,X,Y,Z,//
        NUM_1/*1!*/,NUM_2/*2@*/,NUM_3/*3#*/,NUM_4/*4$*/,NUM_5/*5%*/,//43
        NUM_6/*6^*/,NUM_7/*7&*/,NUM_8/*8**/,NUM_9/*9(*/,NUM_0/*0)*/,
        ENTER,ESC,BACKSPACE,TAB,SPACE,
        MINUS/*-_*/,EQUAL/*=+*/,LEFT_U_BRACE/*[{*/,RIGHT_U_BRACE/*]}*/,
        BACKSLASH/*\|*/,NONE_US/**/,SEMI_COLON/*;:*/,QUOTE/*'"*/,
        GRAVE_ACCENT/*`~*/,COMMA/*,<*/,PERIOD/*.>*/,SLASH/*/?*/,
        CAP_LOCK,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,
        PRINT,SCROLL_LOCK,PAUSE,INSERT,HOME,PAGE_UP,DELETE,END,PAGE_DOWN,
        RIGHT_ARROW,LEFT_ARROW,DOWN_ARROW,UP_ARROW,PAD_NUM_LOCK,
        PAD_SLASH,PAD_ASTERISK,PAD_MINUS,PAD_PLUS,PAD_ENTER,
        PAD_NUM_1,PAD_NUM_2,PAD_NUM_3,PAD_NUM_4,PAD_NUM_5,
        PAD_NUM_6,PAD_NUM_7,PAD_NUM_8,PAD_NUM_9,PAD_NUM_0,
        PAD_PERIOD , NONUS_BACKSLASH,APPLICATION,POWER,PAD_EQUAL,
        F13,F14,F15,F16,F17,F18,F19,F20,F21,F22,F23,F24, EXECUTE,
        HELP,MENU,SELECT,STOP,AGAIN,UNDO,CUT,COPY,PASTE,FIND,MUTE,VOLUME_UP,VOLUME_DOWN,
        FN = 1000
        /*------------------------- HID report data -------------------------*/
		//HID报告数据
    }KeyCode_t;

uint8_t hidbuffer[17];
const uint8_t KeyMap[]= \
{
	0x01,//LEFT_CTRL
	0x02,//LEFT_SHIFT
	0x04,//LEFT_ALT
	0x08,//LEFT_GUI
	0x10,//RIGHT_CTRL  
	0x20,//RIGHT_CTRL
	0x40,//RIGHT_SHIFT
	0x80,//RIGHT_GUI 
};
extern USBD_HandleTypeDef hUsbDeviceFS;
 
void mykeyboard_on(uint8_t key_press)//按键按下
{
	uint8_t array=key_press/8 +1;
    memset(hidbuffer,0,17);
    hidbuffer[0] = 1;
    if((HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5))==0)
    {
        Delay_us(100);
       if((HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5))==0)
       {
         hidbuffer[array] = KeyMap[key_press%8-1];
       }
    }
    USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,hidbuffer,17);
}
void mykeyboard_off(uint8_t key_press)
{
	uint8_t array=key_press/8 + 1;
    memset(hidbuffer,0,17);
    hidbuffer[0] = 1;
    if((HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5))==0)
    {
        Delay_us(100);
       if((HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5))==0)
       {
         hidbuffer[array] = 0x00;
       }
    }
    USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,hidbuffer,17);
}
void mykeyboard_KeyPress(uint8_t key_press)
{
	mykeyboard_on(key_press);
	Delay_ms(50);
	mykeyboard_off(key_press);
}
