/******************************************************************************
 * 文件名：image_acquisition.h
 * 功能：  加载图像
******************************************************************************/

#if !defined __IMAGE_ACQUISITION_H
#define __IMAGE_ACQUISITION_H

#ifdef __cplusplus
extern "C" {
#endif

/* 基本类型定义 */
#include "../../bsp/bsp_header/z_mytype.h"
#include "../../bsp/bsp_header/z_camera.h"

#include "image.h"
#include "../../sys/sys_header/sys_global.h"

#define IMAGE_IN_ADDR			0x80000000
#define IMAGE_FV_IN_ADDR		0x80100000
#define IMAGE_FP_IN_ADDR		0x80200000

#define IMAGE_FV_OUT_ADDR		0x80300000
#define IMAGE_FP_OUT_ADDR		0x80400000
#define IMAGE_TEST_ADDR			0x80500000

/******************************************************************************
  * 功能：从文件中加载图像
  * 参数：image       图像
  *       flag 标识采集的是什么图像
  *			FINGER_PRINT 指纹图像
  *			FINGER_VEIN  指静脉图像
  * 返回：错误编号
******************************************************************************/
void ImageImport(Image_t *image, uint32_t flag);


/******************************************************************************
  * 功能：从文件中加载图像
  * 参数：image       图像
  *       flag 标识采集的是什么图像
  *			FINGER_PRINT 指纹图像
  *			FINGER_VEIN  指静脉图像
  * 返回：错误编号
******************************************************************************/
void ImageExport(Image_t *image, uint32_t flag);





#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* __IMAGE_ACQUISITION_H */



