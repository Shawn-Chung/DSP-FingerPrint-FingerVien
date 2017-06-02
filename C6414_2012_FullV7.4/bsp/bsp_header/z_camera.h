/******************************************************************************
 * 文件名：z_camera.h
 * 功能：  启动指纹和指静脉镜头采集图像	
******************************************************************************/
#ifndef __CAMERA_H__
#define __CAMERA_H__


#include "z_mytype.h"

#include "..\..\C6414_2012_Fullcfg.h"
#include <csl.h>
#include <csl_irq.h>  
#include <csl_edma.h>


#ifdef __cplusplus
extern "C" {
#endif


//定义要采集的图像是指纹、指静脉的宏。
#define FINGER_VEIN     (0x00000001U)
#define FINGER_PRINT    (0x00000002U)
#define FINGER_TEST		(0x00000003U)

//void camera_reset(void);			 //摄像头复位
void camera_capture(uint32_t flag); //摄像头捕获一幅照片
void camera_init(void);			 //摄像头初始化


#ifdef __cplusplus
}
#endif /* extern "C" */



#endif




