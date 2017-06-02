/******************************************************************************
 * 文件名：z_camera.h
 * 功能：  启动指纹和指静脉镜头采集图像	
******************************************************************************/

#include "bsp_header/z_camera.h"

#include "bsp_header/z_cpld_cmd.h"
#include <csl_edma.h>

/**************************************************
函数名：camera_reset
参  数：没有
返  回：没有
作  用：将摄像头复位实际上是FIFO复位。
***************************************************/
//void camera_reset  (void)
//{
//    idt72v36110_reset();		//FIFO局部复位，地址归零
//}
//用函数宏提高效率。
#define camera_reset   idt72v36110_reset

/***************************************************
*函数名：camera_capture
*参  数：flag 标识采集的是什么图像
*        FINGER_PRINT 指纹图像
*        FINGER_VEIN  指静脉图像
*返  回：没有
*作  用：采集一幅图像到FIFO并且用EDMA传送到SDRAM。
*注  意：这里采集到的图像数据还没有整理过的。
***************************************************/
void camera_capture(uint32_t flag)
{
	/*复位摄像头*/
	camera_reset();


	/*要采集图像是指静脉时*/
	if(flag==FINGER_VEIN) {
	  /*开始采集*/
	  FINGER_VEIN_CAPTURE ;//指定采集指静脉,开始采集

	  /*这里要等待一段时间*/
	  _delay_ms(50);		//要足够长,能够满足全部数据采集完毕,

	  /*设置EDMA事件将FIFO里面的数据读到SDRAM*/
	  EDMA_setChannel(hEdmaCha5);

	  _delay_ms(1);

	}

	/*要采集图像是指纹时*/
	else if(flag==FINGER_PRINT) {
	   /*开始采集*/
	   //FINGER_D0307_LED_ON ;
	   asm ( " NOP " ) ;

	   FINGER_PRINT_CAPTURE ;//指定采集指纹,开始采集

	   /*这里要等待一段时间*/
	   _delay_ms(100);		//要足够长,能够满足全部数据采集完毕,

	   /*设置EDMA事件将FIFO里面的数据读到SDRAM*/
	   EDMA_setChannel(hEdmaCha7);

	}
}

/***********************************************************
函数名：camera_init
参  数：没有
返  回：没有
作  用：初始化摄像头的工作环境，实际工作是使能对应的EDMA通道
************************************************************/
void camera_init(void)
{
    EDMA_disableChaining(hEdmaCha5);   //禁止EDMA的链接
    EDMA_enableChannel(hEdmaCha5);     //允许EDMA
    
    EDMA_disableChaining(hEdmaCha7);  
    EDMA_enableChannel(hEdmaCha7);     
}

