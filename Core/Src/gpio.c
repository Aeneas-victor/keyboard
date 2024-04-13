/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
#include "keyboard_send.h"
/* USER CODE BEGIN 0 */
#define ROW_NUM 16//行数
#define COL_NUM 8//列数
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */
	GPIO_TypeDef* row_ports[ROW_NUM]={GPIOA,GPIOA,GPIOA,GPIOA,GPIOA,GPIOA,GPIOA,GPIOA,\
		GPIOB,GPIOB,GPIOB,GPIOB,\
		GPIOC,GPIOC,GPIOC,GPIOC};
	uint16_t row_pins[ROW_NUM]={GPIO_PIN_0,GPIO_PIN_1,GPIO_PIN_2,GPIO_PIN_3,GPIO_PIN_4,GPIO_PIN_5,GPIO_PIN_6,GPIO_PIN_7,\
		GPIO_PIN_0,GPIO_PIN_1,GPIO_PIN_2,GPIO_PIN_3,\
		GPIO_PIN_0,GPIO_PIN_1,GPIO_PIN_2,GPIO_PIN_3};
	GPIO_TypeDef* col_ports[COL_NUM]={GPIOB,GPIOB,GPIOB,GPIOB,GPIOB,GPIOB,GPIOB,GPIOB};
	uint16_t col_pins[COL_NUM]={GPIO_PIN_4,GPIO_PIN_5,GPIO_PIN_6,GPIO_PIN_7,GPIO_PIN_8,GPIO_PIN_9,GPIO_PIN_10,GPIO_PIN_11};
	
/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
}

/* USER CODE BEGIN 2 */
void MyGPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct={0};
    // 初始化引脚
    //初始化A0~A7和B0~B1，C0~C1
   for(uint8_t i=0;i<ROW_NUM;i++)
	{
		GPIO_InitTypeDef GPIO_InitStruct={0};
		GPIO_InitStruct.Pin=row_pins[i];
		GPIO_InitStruct.Mode=GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull=GPIO_PULLUP;
		GPIO_InitStruct.Speed=GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(row_ports[i],&GPIO_InitStruct);
	}
	//初始化B4~B11
	for(uint8_t j=0;j<COL_NUM;j++)
	{
		GPIO_InitTypeDef GPIO_InitStruct={0};
		GPIO_InitStruct.Pin=col_pins[j];
		GPIO_InitStruct.Mode=GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull=GPIO_PULLDOWN;
		GPIO_InitStruct.Speed=GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(col_ports[j],&GPIO_InitStruct);
	}
	
}
void matrix_scan_keypad()//扫描矩阵按键
{
	HAL_GPIO_WritePin(row_ports[0],row_pins[0],GPIO_PIN_RESET);
	if(HAL_GPIO_ReadPin(col_ports[0],col_pins[0])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(LEFT_ARROW_key);
	else if(HAL_GPIO_ReadPin(col_ports[1],col_pins[1])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(FN_key);
	else if(HAL_GPIO_ReadPin(col_ports[2],col_pins[2])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(PAD_NUM_1_key);
	else if(HAL_GPIO_ReadPin(col_ports[3],col_pins[3])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(PAD_NUM_2_key);
	else if(HAL_GPIO_ReadPin(col_ports[4],col_pins[4])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(PAD_NUM_3_key);
	else if(HAL_GPIO_ReadPin(col_ports[5],col_pins[5])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(APPLICATION_key);
	else if(HAL_GPIO_ReadPin(col_ports[7],col_pins[7])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(END_key);

	HAL_GPIO_WritePin(row_ports[1],row_pins[1],GPIO_PIN_RESET);
	if(HAL_GPIO_ReadPin(col_ports[6],col_pins[6])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(LEFT_CTRL_key);
	else if(HAL_GPIO_ReadPin(col_ports[7],col_pins[7])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(RIGHT_CTRL_key);

	HAL_GPIO_WritePin(row_ports[2],row_pins[2],GPIO_PIN_RESET);
	if(HAL_GPIO_ReadPin(col_ports[6],col_pins[6])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(LEFT_ALT_key);
	else if(HAL_GPIO_ReadPin(col_ports[7],col_pins[7])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(RIGHT_ALT_key);

	HAL_GPIO_WritePin(row_ports[3],row_pins[3],GPIO_PIN_RESET);
	if(HAL_GPIO_ReadPin(col_ports[6],col_pins[6])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(RIGHT_SHIFT_key);
	else if(HAL_GPIO_ReadPin(col_ports[7],col_pins[7])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(LEFT_SHIFT_key);

	HAL_GPIO_WritePin(row_ports[4],row_pins[4],GPIO_PIN_RESET);
	if(HAL_GPIO_ReadPin(col_ports[0],col_pins[0])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(X_key);
	else if(HAL_GPIO_ReadPin(col_ports[1],col_pins[1])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(Z_key);
	else if(HAL_GPIO_ReadPin(col_ports[2],col_pins[2])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(CAP_LOCK_key);
	else if(HAL_GPIO_ReadPin(col_ports[3],col_pins[3])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(A_key);
	else if(HAL_GPIO_ReadPin(col_ports[4],col_pins[4])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(TAB_key);
	else if(HAL_GPIO_ReadPin(col_ports[5],col_pins[5])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(Q_key);
	else if(HAL_GPIO_ReadPin(col_ports[6],col_pins[6])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(SPACE_key);
	else if(HAL_GPIO_ReadPin(col_ports[7],col_pins[7])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(PAD_MINUS_key);

	HAL_GPIO_WritePin(row_ports[5],row_pins[5],GPIO_PIN_RESET);
	if(HAL_GPIO_ReadPin(col_ports[0],col_pins[0])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(V_key);
	else if(HAL_GPIO_ReadPin(col_ports[1],col_pins[1])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(B_key);
	else if(HAL_GPIO_ReadPin(col_ports[2],col_pins[2])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(S_key);
	else if(HAL_GPIO_ReadPin(col_ports[3],col_pins[3])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(Y_key);
	else if(HAL_GPIO_ReadPin(col_ports[5],col_pins[5])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(R_key);
	else if(HAL_GPIO_ReadPin(col_ports[7],col_pins[7])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(PAD_NUM_LOCK_key);

	HAL_GPIO_WritePin(row_ports[6],row_pins[6],GPIO_PIN_RESET);
	if(HAL_GPIO_ReadPin(col_ports[0],col_pins[0])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(W_key);
	else if(HAL_GPIO_ReadPin(col_ports[1],col_pins[1])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(C_key);
	else if(HAL_GPIO_ReadPin(col_ports[2],col_pins[2])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(F_key);
	else if(HAL_GPIO_ReadPin(col_ports[3],col_pins[3])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(G_key);
	else if(HAL_GPIO_ReadPin(col_ports[4],col_pins[4])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(E_key);
	else if(HAL_GPIO_ReadPin(col_ports[5],col_pins[5])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(T_key);
	else if(HAL_GPIO_ReadPin(col_ports[6],col_pins[6])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(PAD_NUM_4_key);
	else if(HAL_GPIO_ReadPin(col_ports[7],col_pins[7])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(PAD_PLUS_key);

	HAL_GPIO_WritePin(row_ports[7],row_pins[7],GPIO_PIN_RESET);
	if(HAL_GPIO_ReadPin(col_ports[1],col_pins[1])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(N_key);
	else if(HAL_GPIO_ReadPin(col_ports[2],col_pins[2])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(K_key);
	else if(HAL_GPIO_ReadPin(col_ports[3],col_pins[3])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(D_key);
	else if(HAL_GPIO_ReadPin(col_ports[4],col_pins[4])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(NUM_2_key);
	else if(HAL_GPIO_ReadPin(col_ports[5],col_pins[5])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(NUM_1_key);
	else if(HAL_GPIO_ReadPin(col_ports[6],col_pins[6])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(GRAVE_ACCENT_key);
	else if(HAL_GPIO_ReadPin(col_ports[7],col_pins[7])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(ESC_key);

	HAL_GPIO_WritePin(row_ports[8],row_pins[8],GPIO_PIN_RESET);
	if(HAL_GPIO_ReadPin(col_ports[0],col_pins[0])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(PAD_NUM_0_key);
	else if(HAL_GPIO_ReadPin(col_ports[1],col_pins[1])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(H_key);
	else if(HAL_GPIO_ReadPin(col_ports[2],col_pins[2])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(U_key);
	else if(HAL_GPIO_ReadPin(col_ports[4],col_pins[4])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(NUM_4_key);
	else if(HAL_GPIO_ReadPin(col_ports[5],col_pins[5])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(NUM_3_key);
	else if(HAL_GPIO_ReadPin(col_ports[6],col_pins[6])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(F2_key);
	else if(HAL_GPIO_ReadPin(col_ports[7],col_pins[7])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(F1_key);

	HAL_GPIO_WritePin(row_ports[9],row_pins[9],GPIO_PIN_RESET);
	if(HAL_GPIO_ReadPin(col_ports[0],col_pins[0])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(PAD_PERIOD_key);
	else if(HAL_GPIO_ReadPin(col_ports[1],col_pins[1])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(J_key);
	else if(HAL_GPIO_ReadPin(col_ports[2],col_pins[2])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(M_key);
	else if(HAL_GPIO_ReadPin(col_ports[3],col_pins[3])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(I_key);
	else if(HAL_GPIO_ReadPin(col_ports[4],col_pins[4])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(NUM_7_key);
	else if(HAL_GPIO_ReadPin(col_ports[5],col_pins[5])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(NUM_6_key);
	else if(HAL_GPIO_ReadPin(col_ports[6],col_pins[6])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(F4_key);
	else if(HAL_GPIO_ReadPin(col_ports[7],col_pins[7])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(F3_key);
	
	HAL_GPIO_WritePin(row_ports[10],row_pins[10],GPIO_PIN_RESET);
	if(HAL_GPIO_ReadPin(col_ports[0],col_pins[0])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(PAD_SLASH_key);
	else if(HAL_GPIO_ReadPin(col_ports[2],col_pins[2])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(L_key);
	else if(HAL_GPIO_ReadPin(col_ports[3],col_pins[3])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(PAD_NUM_0_key);
	else if(HAL_GPIO_ReadPin(col_ports[4],col_pins[4])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(NUM_9_key);
	else if(HAL_GPIO_ReadPin(col_ports[5],col_pins[5])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(NUM_8_key);
	else if(HAL_GPIO_ReadPin(col_ports[6],col_pins[6])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(F6_key);
	else if(HAL_GPIO_ReadPin(col_ports[7],col_pins[7])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(F5_key);
	
	HAL_GPIO_WritePin(row_ports[11],row_pins[11],GPIO_PIN_RESET);
	if(HAL_GPIO_ReadPin(col_ports[0],col_pins[0])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(PAD_ASTERISK_key);
	else if(HAL_GPIO_ReadPin(col_ports[1],col_pins[1])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(PAD_NUM_8_key);
	else if(HAL_GPIO_ReadPin(col_ports[2],col_pins[2])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(PERIOD_key);
	else if(HAL_GPIO_ReadPin(col_ports[3],col_pins[3])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(SEMI_COLON_key);
	else if(HAL_GPIO_ReadPin(col_ports[4],col_pins[4])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(P_key);
	else if(HAL_GPIO_ReadPin(col_ports[5],col_pins[5])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(NUM_0_key);
	else if(HAL_GPIO_ReadPin(col_ports[6],col_pins[6])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(F8_key );
	else if(HAL_GPIO_ReadPin(col_ports[7],col_pins[7])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(F7_key);
	
	HAL_GPIO_WritePin(row_ports[12],row_pins[12],GPIO_PIN_RESET);
	if(HAL_GPIO_ReadPin(col_ports[2],col_pins[2])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(SLASH_key);
	else if(HAL_GPIO_ReadPin(col_ports[3],col_pins[3])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(QUOTE_key);
	else if(HAL_GPIO_ReadPin(col_ports[4],col_pins[4])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(LEFT_U_BRACE_key);
	else if(HAL_GPIO_ReadPin(col_ports[5],col_pins[5])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(MINUS_key);
	else if(HAL_GPIO_ReadPin(col_ports[6],col_pins[6])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(F10_key );
	else if(HAL_GPIO_ReadPin(col_ports[7],col_pins[7])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(F9_key);
	
	HAL_GPIO_WritePin(row_ports[13],row_pins[13],GPIO_PIN_RESET);
	if(HAL_GPIO_ReadPin(col_ports[0],col_pins[0])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(BACKSLASH_key);
	else if(HAL_GPIO_ReadPin(col_ports[2],col_pins[2])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(INSERT_key);
	else if(HAL_GPIO_ReadPin(col_ports[3],col_pins[3])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(RIGHT_U_BRACE_key);
	else if(HAL_GPIO_ReadPin(col_ports[4],col_pins[4])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(EQUAL_key);
	else if(HAL_GPIO_ReadPin(col_ports[5],col_pins[5])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(F12_key);
	else if(HAL_GPIO_ReadPin(col_ports[6],col_pins[6])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(RIGHT_ARROW_key );
	else if(HAL_GPIO_ReadPin(col_ports[7],col_pins[7])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(F11_key);
	
	HAL_GPIO_WritePin(row_ports[14],row_pins[14],GPIO_PIN_RESET);
	if(HAL_GPIO_ReadPin(col_ports[1],col_pins[1])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(UP_ARROW_key);
	else if(HAL_GPIO_ReadPin(col_ports[2],col_pins[2])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(PAD_NUM_7_key);
	else if(HAL_GPIO_ReadPin(col_ports[3],col_pins[3])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(BACKSPACE_key);
	else if(HAL_GPIO_ReadPin(col_ports[4],col_pins[4])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(PAD_NUM_5_key);
	else if(HAL_GPIO_ReadPin(col_ports[5],col_pins[5])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(PAUSE_key);
	else if(HAL_GPIO_ReadPin(col_ports[7],col_pins[7])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(DELETE_key);
	
	HAL_GPIO_WritePin(row_ports[15],row_pins[15],GPIO_PIN_RESET);
	if(HAL_GPIO_ReadPin(col_ports[0],col_pins[0])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(MENU_key);
	else if(HAL_GPIO_ReadPin(col_ports[2],col_pins[2])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(ENTER_key);
	else if(HAL_GPIO_ReadPin(col_ports[4],col_pins[4])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(DOWN_ARROW_key);
	else if(HAL_GPIO_ReadPin(col_ports[5],col_pins[5])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(PAD_NUM_9_key);
	else if(HAL_GPIO_ReadPin(col_ports[7],col_pins[7])==GPIO_PIN_RESET)
		mykeyboard_KeyPress(PAD_NUM_6_key);
}

/* USER CODE END 2 */
