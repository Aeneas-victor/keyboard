#ifndef __KEYBOARD_SEND_H__
#define __KEYBOARD_SEND_H__
#include "usbd_customhid.h"
#include "Delay.h"
typedef enum 
    {
        /*------------------------- HID report data -------------------------*/
        
		LEFT_CTRL_key = 1,//1
		LEFT_SHIFT_key ,//2
		LEFT_ALT_key ,//3
		LEFT_GUI_key ,//4
        RIGHT_CTRL_key ,//5
		RIGHT_SHIFT_key ,//6
		RIGHT_ALT_key ,//7
		RIGHT_GUI_key ,//8
        RESERVED_key ,//9
		ERROR_ROLL_OVER_key,//10
		POST_FAIL_key,//11
		ERROR_UNDEFINED_key,//12
        A_key,B_key,C_key,D_key,E_key,F_key,G_key,H_key,//20
		I_key,J_key,K_key,L_key,M_key,N_key,O_key,P_key,//28
		Q_key,R_key,S_key,T_key,U_key,V_key,W_key,X_key,//36
		Y_key,Z_key,NUM_1_key,NUM_2_key,NUM_3_key,NUM_4_key,NUM_5_key,NUM_6_key,//44
		NUM_7_key,NUM_8_key,NUM_9_key,NUM_0_key, ENTER_key,ESC_key,BACKSPACE_key,TAB_key,//52
		SPACE_key, MINUS_key,EQUAL_key,LEFT_U_BRACE_key,RIGHT_U_BRACE_key, BACKSLASH_key,NONE_US_key,SEMI_COLON_key,//60
		QUOTE_key, GRAVE_ACCENT_key,COMMA_key,PERIOD_key,SLASH_key, CAP_LOCK_key,F1_key,F2_key,//68
		F3_key,F4_key,F5_key,F6_key,F7_key,F8_key,F9_key,F10_key,//76
		F11_key,F12_key,PRINT_key,SCROLL_LOCK_key,PAUSE_key,INSERT_key,HOME_key,PAGE_UP_key,//84
		//PAD 小键盘区
		DELETE_key,END_key,PAGE_DOWN_key,RIGHT_ARROW_key,LEFT_ARROW_key,DOWN_ARROW_key,UP_ARROW_key,PAD_NUM_LOCK_key, //92
		PAD_SLASH_key,PAD_ASTERISK_key,PAD_MINUS_key/*减号*/,PAD_PLUS_key/*加号*/,PAD_ENTER_key, PAD_NUM_1_key,PAD_NUM_2_key,PAD_NUM_3_key,//100
		PAD_NUM_4_key,PAD_NUM_5_key,PAD_NUM_6_key,PAD_NUM_7_key,PAD_NUM_8_key,PAD_NUM_9_key,PAD_NUM_0_key, PAD_PERIOD_key ,//108
		NONUS_BACKSLASH_key,APPLICATION_key/*Windows*/,POWER_key,PAD_EQUAL_key, F13_key,F14_key,F15_key,F16_key,//116
		F17_key,F18_key,F19_key,F20_key,F21_key,F22_key,F23_key,F24_key,//124
		EXECUTE_key, HELP_key,MENU_key,SELECT_key,STOP_key,AGAIN_key,UNDO_key,CUT_key,//132
		COPY_key,PASTE_key,FIND_key,MUTE_key,VOLUME_UP_key,VOLUME_DOWN_key, FN_key//139
        /*------------------------- HID report data -------------------------*/
		//HID报告数据
    }KeyKey_t;
	
void mykeyboard_on(uint8_t key_press);
void mykeyboard_off(uint8_t key_press);
void mykeyboard_KeyPress(uint8_t key_press);


#endif


