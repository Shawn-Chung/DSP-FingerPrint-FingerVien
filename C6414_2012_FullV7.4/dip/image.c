/******************************************************************************
 * 文件名：image.c
 * 功能：  实现了指纹图像的基本操作
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
//
//#include <string.h>

#include "dip_header/image.h"

//创建图像:将图像结构体初始化
void ImageCreate
(
 Image_t *image, 
 void *data, 
 int32_t width, 
 int32_t height, 
 int32_t pitch, 
 ImageFlag_t flags
 )
{
	//int32_t i;
	image->pimg = data;
	image->width = width;
	image->height = height;
	image->pitch = pitch;
	image->flags = flags;
	image->size = width * height;

	//for (i = 0; i < height; i++) {
	//	*(image->ppimg+i) = (uint8_t *)data + i * pitch;
	//}
}

//图像数据值为value
void ImageFlood(Image_t *image, const uint8_t value)
{
	int32_t i;
	for (i = 0; i < image->size; i++) {
		*(image->pimg+i) = value;
	}
}

//设置图像标记
void ImageSetFlags(Image_t *image, ImageFlag_t flags)
{
	image->flags = flags;
}

//图像拷贝
void ImageCopy(Image_t *dst_image, Image_t *src_image)
{
	int32_t i = 0;
	if ((dst_image->height != src_image->height) ||
		(dst_image->width  != src_image->width) ||
		(dst_image->pitch  != src_image->pitch)) {
		return;
	}

	for (i = 0; i < src_image->size; i++) {
		*(dst_image->pimg + i) = *(src_image->pimg + i);
	}
}

void ImageCopy32(Image_t *dst_image, Image_t *src_image)
{
	int32_t i = 0;
	uint32_t *pD, *pS;
	//if ((dst_image->height != src_image->height) ||
	//	(dst_image->width  != src_image->width) ||
	//	(dst_image->pitch  != src_image->pitch)) {
	//	return;
	//}

	int32_t size = src_image->size >> 2;
	pS = (uint32_t *)(src_image->pimg);
	pD = (uint32_t *)(dst_image->pimg);

	for (i = 0; i < size; i++) {
		*(pD + i) = *(pS + i);
	}
}


//DSP的存储和读写为32位
void BufferCopy32(uint32_t *pDst, uint32_t *pSrc, unsigned int size) 
{
	unsigned int i;
	for (i = 0; i < size; i++) {
		*(pDst+i) = *(pSrc+i);
	}
}

void BufferCopyV1(uint8_t *pDst, uint8_t *pSrc, unsigned int size) 
{
	unsigned int i;
	uint32_t *pS, *pD;
	pS = (uint32_t *)pSrc;
	pD = (uint32_t *)pDst;
	i = size >> 2;
	for (; i > 0; i--) {
		*pD++ = *pS++;
	}
}
