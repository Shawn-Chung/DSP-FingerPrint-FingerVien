/******************************************************************************
 * 文件名：image.h
 * 功能：  实现了指纹图像的基本操作
******************************************************************************/

#if !defined __GUI_MENU_H
#define __GUI_MENU_H

#include "GUI.h"


#ifdef __cplusplus
extern "C" {
#endif

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色 

#define MAIN_WIN		0u
#define REGISTER_WIN	1u
#define T9_WIN			4u
#define MANAGER_WIN		2u
#define MANAGER_SUB_WIN	3u
#define PASSWORD_WIN		5u
#define PASSWORD_SUB_WIN0		6u
#define PASSWORD_SUB_WIN1		7u

#define REGISTER_NUM	0u
	#define REGISTER_X0		35u
	#define REGISTER_Y0		125u
	#define REGISTER_X1		140u
	#define REGISTER_Y1		215u

#define MANAGER_NUM		1u
	#define MANAGER_X0		175u
	#define MANAGER_Y0		125u
	#define MANAGER_X1		280u
	#define MANAGER_Y1		215u

#define BUTTON_REGISTER		0u
	#define BTN_REG_X0		142
	#define BTN_REG_Y0		13
	#define BTN_REG_X1		222
	#define BTN_REG_Y1		51

#define BUTTON_MANAGER		1u
	#define BTN_MAN_X0		142
	#define BTN_MAN_Y0		58
	#define BTN_MAN_X1		222
	#define BTN_MAN_Y1		96


#define DIS_FV_X		13
#define DIS_FV_Y		11
#define DIS_FV_W		96
#define DIS_FV_H		216

#define DIS_FP_X		126
#define DIS_FP_Y		105
#define DIS_FP_W		124
#define DIS_FP_H		124


typedef struct InputData{
	uint32_t size;
	char     data[36];
}InputData;


extern uint8_t gWindowType;
extern InputData gInputData;

void Gui_ipost(void);

void SelectMenu(uint8_t winType, uint8_t menuNum, uint8_t sel);




#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* __IMAGE_H */






