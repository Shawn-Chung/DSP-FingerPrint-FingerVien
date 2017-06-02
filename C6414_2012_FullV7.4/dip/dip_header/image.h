/******************************************************************************
 * 文件名：image.h
 * 功能：  实现了指纹图像的基本操作
******************************************************************************/

#if !defined __IMAGE_H
#define __IMAGE_H

/* 基本类型定义 */
#include "../../bsp/bsp_header/z_mytype.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 对象的这些接口实现是私有的，不必为用户所知。使用这里提供的函数操作图像 */
typedef Handle_t ImageHandle_t;


/* 定义图像属性 */
typedef enum
{
    ImageGray      = 0,	/* 8-bit灰度图像 */
	ImageColor	   = 1, /* 32-bit灰度图像*/
    ImageBinarized = 2,	/* 二值化图像    */
    ImageThinned   = 3	/* 细化图像      */
} ImageFlag_t;

/* 指纹图像结构。256级灰度图 */
typedef struct Image_t
{
    uint8_t       *pimg;         /*  8-bit图像数组一维指针*/  
	uint8_t		  **ppimg;		 /*	 8-bit图像数组二维指针*/  
    int32_t       width;         /*  宽度            */
    int32_t       height;        /*  高度            */
	int32_t       pitch;         /*  节距:每行字节数 */
	int32_t		  size;			 /*  图像大小(h*pitch)*/	
    ImageFlag_t  flags;          /*  标记            */
} Image_t;


//创建图像:将图像结构体初始化
void ImageCreate
(
 Image_t *image, 
 void *data, 
 int32_t width, 
 int32_t height, 
 int32_t pitch, 
 ImageFlag_t flags
 );


//图像数据值为value
void ImageFlood(Image_t *image, const uint8_t value);


//设置图像标记
void ImageSetFlags(Image_t *image, ImageFlag_t flags);


//图像拷贝
void ImageCopy(Image_t *dst_image, Image_t *src_image);
void ImageCopy32(Image_t *dst_image, Image_t *src_image);

void BufferCopy32(uint32_t *pDst, uint32_t *pSrc, unsigned int size);
void BufferCopyV1(uint8_t *pDst, uint8_t *pSrc, unsigned int size) ;









#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* __IMAGE_H */

