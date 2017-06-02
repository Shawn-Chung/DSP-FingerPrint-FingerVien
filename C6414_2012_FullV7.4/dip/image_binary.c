/******************************************************************************
 * 文件名：image_binary.c
 * 功  能：一些图像二值(0,1或0,255)化操作
******************************************************************************/
#include "dip_header/image_binary.h"


//#include <stdio.h>
//#include <math.h>
//#include <stdlib.h>
//#include <string.h>


/******************************************************************************
  * 功能：图像固定阈值二值化
  * 参数：image       指纹图像
  *       thr_value   阈值
  * 返回：错误编号
******************************************************************************/
FunError_t ImageBinarize(Image_t image, const uint8_t thr_value)
{
    int32_t n;
    uint8_t *pimg = ImageGetBuffer(image);
    int32_t size = ImageGetSize(image);
    if (pimg==NULL)
        return FunMemory;
    /* 循环遍历 */
    for (n = 0; n < size; n++, pimg++)
    {
        /* 阈值化 */
        *pimg = (*pimg < thr_value)?(uint8_t)0xFF:(uint8_t)0x00;
    }
    return ImageSetFlag(image, ImageBinarized);
}

/******************************************************************************
  * 功能：图像固定阈值二值化(0,1)
  * 参数：image       指纹图像
  *       thr_value   阈值
  * 返回：错误编号
******************************************************************************/
FunError_t ImageBinarizeOZ(Image_t image, const uint8_t thr_value)
{
    int32_t n;
    uint8_t *pimg = ImageGetBuffer(image);
    int32_t size = ImageGetSize(image);
    if (pimg==NULL)
        return FunMemory;
    /* 循环遍历 */
    for (n = 0; n < size; n++, pimg++)
    {
        /* 阈值化 */
        *pimg = (*pimg < thr_value)?(uint8_t)1:(uint8_t)0;
    }
    return ImageSetFlag(image, ImageBinarized);
}

/******************************************************************************
  * 功能：图像固定阈值操作(包含了固定阈值二值化的两个函数的功能)
  * 参数：image         指纹图像
  *       thr_value     阈值
  *       max_value	    在某些阈值类型操作时,取得的最大值
  *       thr_type		阈值操作类型
  * 返回：错误编号
******************************************************************************/
FunError_t ImageThreshold(Image_t image, const uint8_t thr_value, const uint8_t max_value, const int32_t thr_type)
{
    int32_t n;
    uint8_t *pimg = ImageGetBuffer(image);
    int32_t size = ImageGetSize(image);
    if (pimg==NULL)
        return FunMemory;
    /* 循环遍历 */
    for (n = 0; n < size; n++, pimg++)
    {
        /* 阈值化 */
		switch (thr_type) {
		case THR_WB:	//>thr_value: max_value, else: 0
			*pimg = (*pimg > thr_value)?((uint8_t)max_value):((uint8_t)0x00);
			break;
		case THR_WBI:	//>thr_value: 0, else: max_value
			*pimg = (*pimg > thr_value)?((uint8_t)0x00):((uint8_t)max_value);
			break;
		case THR_OZ:	//>thr_value: 1, else: 0
			*pimg = (*pimg > thr_value)?((uint8_t)1):((uint8_t)0);
			break;
		case THR_OZI:	//>thr_value: 0, else: 1
			*pimg = (*pimg > thr_value)?((uint8_t)0):((uint8_t)1);
			break;
		case THR_TRUNC:		//>thr_value: thr_value, else: *pimg
			*pimg = (*pimg > thr_value)?((uint8_t)thr_value):((uint8_t)(*pimg));
			break;
		case THR_ZERO:		//>thr_value: *pimg, else: 0
			*pimg = (*pimg > thr_value)?((uint8_t)(*pimg)):((uint8_t)0x00);
			break;
		case THR_ZEROI:		//>thr_value: *pimg, else: 0
			*pimg = (*pimg > thr_value)?((uint8_t)0x00):((uint8_t)(*pimg));
			break;
		default :			//>thr_value: max_value, else: 0
			*pimg = (*pimg > thr_value)?((uint8_t)max_value):((uint8_t)0x00);
			break;
		}
    }
    return ImageSetFlag(image, ImageBinarized);
}

/******************************************************************************
  * 功能：图像二值化,使用图像的总体均值作为阈值
  * 参数：image     指纹图像
  *       x0		截取图像部分的开始x坐标
  *       y0		截取图像部分的开始y坐标
  *       dx		截取图像部分的宽度
  *       dy		截取图像部分的高度
  *		  dir		二值化方式
  * 返回：错误编号
  * 说明: 此处的二值仅指0和1,不是0和255,简单修改下就可以实现0和255的二值化
  *		  二值化化方式:
  *			dir == 1: >thr_value: 1, else: 0
  *			dir == 0: >thr_value: 0, else: 1 
  *			dir == 2: >thr_value: 0, else: 255
  *			dir == 3: >thr_value: 255, else: 0	
  * 算法描述:
  *		  计算出截取出来的图像的总体平均灰度作为阈值	
******************************************************************************/
FunError_t ImageOverallBinary
(
 Image_t image, 
 const int32_t x0, 
 const int32_t y0, 
 const int32_t dx,
 const int32_t dy,
 const int32_t dir
 )
{
	uint8_t* p1  = ImageGetBuffer(image);
	uint8_t *pS;
    int32_t   w   = ImageGetWidth (image);
    int32_t   h   = ImageGetHeight(image);
    int32_t pitch = ImageGetPitch (image);
	uint32_t average;
	int32_t x, y;
	uint32_t total;
	//dir == 1: >thr_value: 1, else: 0
	//dir == 0: >thr_value: 0, else: 1 
	//dir == 2: >thr_value: 0, else: 255
	//dir == 3: >thr_value: 255, else: 0
	uint32_t upper_thr, under_thr;
	if (dir == 0) {
		upper_thr = 0;
		under_thr = 1;
	} else if (dir == 1) {
		upper_thr = 1;
		under_thr = 0;
	} else if (dir == 2) {
		upper_thr = 0;
		under_thr = 255;
	} else if (dir == 3) {
		upper_thr = 255;
		under_thr = 0;
	} else {
		upper_thr = 1;
		under_thr = 0;
	}
	//

	if ((y0 < 0) || (x0 < 0) || (dy <= 0) || (dx <= 0) ||(y0+dy > h) || (x0+dx) > w) {	//参数处理
		fprintf (stderr, "bad input parameter.\n");
		return FunBadParameter;
	}
	total = dx*dy;
	average = 0;
	for (y = y0; y < y0+dy; y++) {
		pS = p1 + pitch*y;
		for (x = x0; x < x0+dx; x++) {
			average += *(pS + x);
		}
	}

	average /= total;
#if defined __MY_DEBUG
		fprintf(stderr,"# ImageOverall: thr_value = %d\n", average);
#endif

	for (y = y0; y < y0+dy; y++) {
		pS = p1 + pitch*y;
		for (x = x0; x < x0+dx; x++) {
			//if (dir == 0) 
			//	*(pS + x) = *(pS + x) > average ? 0 : 1;
			//else
			//*(pS + x) = *(pS + x) > average ? 1 : 0;
			*(pS + x) =*(pS + x) > average ? upper_thr : under_thr;
		}
	}

	return FunOK;
}


/******************************************************************************
  * 功能：图像二值滤波操作，通过计算均值实现
  * 参数：image     指纹图像
  *       size      软化窗口大小(2*r+1)
  *		  dir		二值化方式
  * 返回：错误编号
  * 说明: 此处的二值仅指0和1,不是0和255,简单修改下就可以实现0和255的二值化
  *		  二值化化方式:
  *			dir == 1: >thr_value: 1, else: 0
  *			dir == 0: >thr_value: 0, else: 1 
  *			dir == 2: >thr_value: 0, else: 255
  *			dir == 3: >thr_value: 255, else: 0	
  *       边界影响,经过这个函数处理后的图像实际上被裁剪去了size行和size列
******************************************************************************/
FunError_t ImageMeanBinary(Image_t image, const int32_t size, const int32_t dir)
{
	uint8_t* p1  = ImageGetBuffer(image);
    uint8_t* p2;
    int32_t   w   = ImageGetWidth (image);
    int32_t   h   = ImageGetHeight(image);
    int32_t pitch = ImageGetPitch (image);
    int32_t pitch2;
    int32_t x,y,s,p,q,a,c,c0;
	int32_t sx, sy;
    Image_t im2;
	//dir == 1: >thr_value: 1, else: 0
	//dir == 0: >thr_value: 0, else: 1 
	//dir == 2: >thr_value: 0, else: 255
	//dir == 3: >thr_value: 255, else: 0
	uint32_t upper_thr, under_thr;
	if (dir == 0) {
		upper_thr = 0;
		under_thr = 1;
	} else if (dir == 1) {
		upper_thr = 1;
		under_thr = 0;
	} else if (dir == 2) {
		upper_thr = 0;
		under_thr = 255;
	} else if (dir == 3) {
		upper_thr = 255;
		under_thr = 0;
	} else {
		upper_thr = 1;
		under_thr = 0;
	}

    im2 = ImageCreate();
    
    if (im2==NULL || p1==NULL)
        return FunMemory;

    s = size/2;		/* 大小 */
    a = size*size;	/* 面积 */    
    if (a==0)
	return FunBadParameter;
	
    /* 拷贝图像进行计算 */
    ImageCopy(im2, image);
    p2 = ImageGetBuffer(im2);
    if (p2==NULL)
    {
		ImageDestroy(im2);
		return FunMemory;
    }
    pitch2 = ImageGetPitch (im2);
    
	//for (y = s; y < h - s; y++)
 //   for (x = s; x < w - s; x++)
	for (y = 0; y < h; y++)
    for (x = 0; x < w; x++)
    {
		c = 0;
		sx = x - s;
		sy = y - s;
		if (y < s || y >= h-s ||\
			x < s || x >= w-s) {
			p1[pitch*y + x] = 0;
			continue;
		} 
		//优化前
		//for (q=-s;q<=s;q++)
		//for (p=-s;p<=s;p++)
		//{
  //  		 c += p2[(x+p)+(y+q)*pitch2];
		//}
		//优化后
		for (q = y-s; q <= y+s; q++)
		for (p = x-s; p <= x+s; p++)
		{
			c += p2[p+q*pitch2];
		}
		//优化前
		//c0 = p1[x+y*pitch];
		//c = c/a;
		//p1[x+y*pitch] = c0>c?0:1;	//这里修改为255:0就可以实现黑白二值化
		//优化后
		c0 = p1[x+y*pitch]*a;
		//if (dir == 0)
		//	p1[x + y*pitch] = c0>c ? 0 : 1;	//这里修改为255:0就可以实现黑白二值化
		//else 
		//	p1[x + y*pitch] = c0>c ? 1 : 0;	//这里修改为255:0就可以实现黑白二值化
		p1[x + y*pitch]= c0 > c ? upper_thr : under_thr;

		//if (OZ_WB == OZ) {
		//	p1[x+y*pitch] = c0>c?0:1;	//这里修改为255:0就可以实现黑白二值化
		//} else if (OZ_WB == WB) {
		//	p1[x+y*pitch] = c0>c?0:255;	//这里修改为255:0就可以实现黑白二值化
		//}
    }
    
    ImageDestroy(im2);
    return FunOK;
}

/******************************************************************************
  * 功能：图像二值滤波操作，通过计算均值实现
  * 参数：image     指纹图像
  *       size      软化窗口大小(2*r+1)
  *		  dir		二值化方式
  * 返回：错误编号
  * 说明: 此处的二值仅指0和1,不是0和255,简单修改下就可以实现0和255的二值化
  *		  二值化化方式:
  *			dir == 1: >thr_value: 1, else: 0
  *			dir == 0: >thr_value: 0, else: 1 
  *			dir == 2: >thr_value: 0, else: 255
  *			dir == 3: >thr_value: 255, else: 0	
  *		  图像先进行直接延伸,在进行模版操作
  *		  因此宽,高在模版操作后没有变化
******************************************************************************/
FunError_t ImageMeanBinaryV1(Image_t image, const int32_t size, const int32_t dir)
{
	uint8_t* p1  = ImageGetBuffer(image);
    uint8_t* p2;
    int32_t   w   = ImageGetWidth (image);
    int32_t   h   = ImageGetHeight(image);
    int32_t pitch = ImageGetPitch (image);
    int32_t pitch2;
    int32_t x,y,s,p,q,a,c,c0;
	int32_t sx, sy;
    Image_t im2;
	//dir == 1: >thr_value: 1, else: 0
	//dir == 0: >thr_value: 0, else: 1 
	//dir == 2: >thr_value: 0, else: 255
	//dir == 3: >thr_value: 255, else: 0
	uint32_t upper_thr, under_thr;
	if (dir == 0) {
		upper_thr = 0;
		under_thr = 1;
	} else if (dir == 1) {
		upper_thr = 1;
		under_thr = 0;
	} else if (dir == 2) {
		upper_thr = 0;
		under_thr = 255;
	} else if (dir == 3) {
		upper_thr = 255;
		under_thr = 0;
	} else {
		upper_thr = 1;
		under_thr = 0;
	}

    im2 = ImageCreate();
    
    if (im2==NULL || p1==NULL)
        return FunMemory;

    s = size/2;		/* 大小 */
    a = size*size;	/* 面积 */    
    if (a==0)
	return FunBadParameter;
	
    /* 拷贝图像进行计算 */
    //ImageCopy(im2, image);
	ImageExtendCopy(im2, image, size);
    p2 = ImageGetBuffer(im2);
    if (p2==NULL)
    {
		ImageDestroy(im2);
		return FunMemory;
    }
    pitch2 = ImageGetPitch (im2);
    
    for (y = s; y < h+s; y++)
    for (x = s; x < w+s; x++)
    {
		c = 0;
		sx = x - s;
		sy = y - s;

		for (q = y-s; q <= y+s; q++)
		for (p = x-s; p <= x+s; p++)
		{
			c += p2[p+q*pitch2];
		}
		//c0 = p1[sx+sy*pitch]*a;
		c0 = p2[x+y*pitch2]*a;
		//if (dir == 0)
		//	p1[sx+sy*pitch] = c0>c?0:1;	//这里修改为255:0就可以实现黑白二值化
		//else 
		//	p1[sx+sy*pitch] = c0>c?1:0;	//这里修改为255:0就可以实现黑白二值化
		p1[sx+sy*pitch] = c0>c?upper_thr:under_thr;

		//if (OZ_WB == OZ) {
		//	p1[sx+sy*pitch] = c0>c?0:1;	//这里修改为255:0就可以实现黑白二值化
		//} else if (OZ_WB == WB) {
		//	p1[sx+sy*pitch] = c0>c?0:255;	//这里修改为255:0就可以实现黑白二值化
		//}
    }
    
    ImageDestroy(im2);
    return FunOK;
}


/******************************************************************************
  * 功能：图像统计滤波操作，通过计算均值实现
  * 参数：image     图像
  *       size      滤波器模版大小(2*r+1)
  *       thre_val  阈值
  *		  dir		二值化方式
  * 返回：错误编号
  * 说明: 此处的二值仅指0和1,不是0和255,简单修改下就可以实现0和255的二值化
  *		  二值化化方式:
  *			dir == 1: >thr_value: 1, else: 0
  *			dir == 0: >thr_value: 0, else: 1 
  *			dir == 2: >thr_value: 0, else: 255
  *			dir == 3: >thr_value: 255, else: 0	
  *       边界影响,经过这个函数处理后的图像实际上被裁剪去了size行和size列
******************************************************************************/
FunError_t ImageStatisticsFilter(Image_t image, const int32_t size, const int32_t thre_val, const int32_t dir)
{
	uint8_t* p1  = ImageGetBuffer(image);
    uint8_t* p2;
    int32_t   w   = ImageGetWidth (image);
    int32_t   h   = ImageGetHeight(image);
    int32_t pitch = ImageGetPitch (image);
    int32_t pitch2;
    int32_t x,y,s,p,q,a,c;
    Image_t im2;
	//dir == 1: >thr_value: 1, else: 0
	//dir == 0: >thr_value: 0, else: 1 
	//dir == 2: >thr_value: 0, else: 255
	//dir == 3: >thr_value: 255, else: 0
	uint32_t upper_thr, under_thr;
	if (dir == 0) {
		upper_thr = 0;
		under_thr = 1;
	} else if (dir == 1) {
		upper_thr = 1;
		under_thr = 0;
	} else if (dir == 2) {
		upper_thr = 0;
		under_thr = 255;
	} else if (dir == 3) {
		upper_thr = 255;
		under_thr = 0;
	} else {
		upper_thr = 1;
		under_thr = 0;
	}

    im2 = ImageCreate();
    
    if (im2==NULL || p1==NULL)
        return FunMemory;

    s = size/2;		/* 大小 */
    a = size*size;	/* 面积 */    
    if (a==0)
	return FunBadParameter;
	
    /* 拷贝图像进行计算 */
    ImageCopy(im2, image);
    p2 = ImageGetBuffer(im2);
    if (p2==NULL)
    {
		ImageDestroy(im2);
		return FunMemory;
    }
    pitch2 = ImageGetPitch (im2);
    
    for (y = s; y < h-s; y++)
    for (x = s; x < w-s; x++)
    {
		c = 0;

		for (q = y-s; q <= y+s; q++)
		for (p = x-s; p <= x+s; p++)
		{
			c += p2[p+q*pitch2];
		}

		//if (dir == 0)
		//	p1[x+y*pitch] = c>=thre_val?0:1;	//这里修改为255:0就可以实现黑白二值化
		//else 
		//	p1[x+y*pitch] = c>=thre_val?1:0;	//这里修改为255:0就可以实现黑白二值化
		p1[x+y*pitch] = c>= thre_val?upper_thr:under_thr;

		//if (OZ_WB == OZ)
		//	p1[x+y*pitch] = c>=thre_val?1:0;	//这里修改为255:0就可以实现黑白二值化
		//else if (OZ_WB == WB)
		//	p1[x+y*pitch] = c>=thre_val?255:0;	//这里修改为255:0就可以实现黑白二值化
    }
    
    ImageDestroy(im2);
    return FunOK;
}


/******************************************************************************
  * 功能：图像Niblack操作,局部动态阈值算法
  * 参数：image     图像
  *       size      模版窗口大小(2*r+1)
  *		  ratio		Niblack修正系数
  *		  dir		二值化方式
  * 返回：错误编号
  * 说明: 此处的二值仅指0和1,不是0和255,简单修改下就可以实现0和255的二值化
  *		  二值化化方式:
  *			dir == 1: >thr_value: 1, else: 0
  *			dir == 0: >thr_value: 0, else: 1 
  *			dir == 2: >thr_value: 0, else: 255
  *			dir == 3: >thr_value: 255, else: 0	
  *       边界影响,经过这个函数处理后的图像实际上被裁剪去了size行和size列
  * 算法描述: 
  *       一种简单有效的局部动态阈值算法,对图像中的每一点,在rxr领域内,
  *		  计算领域内像素点的均值和方差,然后用T(x,y) = m(x,y) + k x s(x,y)
  *		  作为阈值,进行二值化.
  *		  T(x,y)为该点阈值,m(x,y)为该点rxr领域内像素的均值,s(x,y)为标准方差
  *		  k为修正系数
******************************************************************************/
FunError_t ImageNiBlack(Image_t image, const int32_t size, const double ratio, const int32_t dir)
{
	uint8_t* p1  = ImageGetBuffer(image);
    uint8_t* p2;
    int32_t   w   = ImageGetWidth (image);
    int32_t   h   = ImageGetHeight(image);
    int32_t pitch = ImageGetPitch (image);
    int32_t pitch2;
    int32_t x,y,s,p,q,a,c,c1;
    Image_t im2;
	double average = 0.0;
	double variance = 0.0;
	uint8_t  temp0 = 0;
	uint8_t  temp1 = 0;
	//dir == 1: >thr_value: 1, else: 0
	//dir == 0: >thr_value: 0, else: 1 
	//dir == 2: >thr_value: 0, else: 255
	//dir == 3: >thr_value: 255, else: 0
	uint32_t upper_thr, under_thr;
	if (dir == 0) {
		upper_thr = 0;
		under_thr = 1;
	} else if (dir == 1) {
		upper_thr = 1;
		under_thr = 0;
	} else if (dir == 2) {
		upper_thr = 0;
		under_thr = 255;
	} else if (dir == 3) {
		upper_thr = 255;
		under_thr = 0;
	} else {
		upper_thr = 1;
		under_thr = 0;
	}

    im2 = ImageCreate();
    
    if (im2==NULL || p1==NULL)
        return FunMemory;

    s = size/2;		/* 大小 */
    a = size*size;	/* 面积 */    
    if (a==0)
	return FunBadParameter;
	
    /* 拷贝图像进行计算 */
    ImageCopy(im2, image);
    p2 = ImageGetBuffer(im2);
    if (p2==NULL)
    {
		ImageDestroy(im2);
		return FunMemory;
    }
    pitch2 = ImageGetPitch (im2);
    
    for (y = s; y < h-s; y++)
    for (x = s; x < w-s; x++)
    {
		c = 0;
		c1 = 0;
		average = 0.0;
		variance = 0.0;
		for (q = y-s; q <= y+s; q++)
		for (p = x-s; p <= x+s; p++)
		{
			c += p2[p+q*pitch2];
			c1 += p2[p+q*pitch2] * p2[p+q*pitch2];

		}

		average = (double)c / (double)a;
		variance = sqrt((double)c1 / (double)a);
		//
		//for (q = y-s; q <= y+s; q++)
		//for (p = x-s; p <= x+s; p++)
		//{
		//	variance += (p2[p+q*pitch2] - average)*(p2[p+q*pitch2] - average);
		//}

		//variance = sqrt(variance / a);
		temp1 = (uint8_t)(average + ratio * variance);		
		//p1[x+y*pitch] = temp1;
		temp0 = p1[x+y*pitch];
		//if (dir == 0)
		//	p1[x+y*pitch] = temp0 > temp1 ? 0 : 1;	//这里修改为255:0就可以实现黑白二值化
		//else 
		//	p1[x+y*pitch] = temp0 > temp1 ? 1 : 0;	//这里修改为255:0就可以实现黑白二值化
		p1[x+y*pitch] = temp0 > temp1 ? upper_thr : under_thr;
    }

    ImageDestroy(im2);
    return FunOK;
}


/******************************************************************************
  * 功能：图像Otsu算法(大律法或最大类间方差法),利用阈值将原图像分成前景，背景两个图象
  * 参数：image     图像
  *       x0		截取图像部分的开始x坐标
  *       y0		截取图像部分的开始y坐标
  *       dx		截取图像部分的宽度
  *       dy		截取图像部分的高度
  *		  dir		二值化方式
  * 返回：错误编号
  * 说明: 此处的二值仅指0和1,不是0和255,简单修改下就可以实现0和255的二值化
  *		  二值化化方式:
  *			dir == 1: >thr_value: 1, else: 0
  *			dir == 0: >thr_value: 0, else: 1 
  *			dir == 2: >thr_value: 0, else: 255
  *			dir == 3: >thr_value: 255, else: 0	
  * 算法描述: 
  *       一种简单有效的局部动态阈值算法,对图像中的每一点,在rxr领域内,
  *       记t为前景与背景的分割阈值，前景点数占图像比例为w0，平均灰度为u0；
  *       背景点数 占图像比例为w1，平均灰度为u1。
  *       则图像的总平均灰度为：u=w0*u0+w1*u1
  *       前景和背景图象的方差：
  *       g=w0*(u0-u)*(u0-u)+w1*(u1-u)*(u1-u)=w0*w1*(u0-u1)*(u0-u1),此公式为方差公式
  *       可参照概率论课本上面的g的公式也就是下面程序中的sb的表达式。当方差g最大时，
  *       可以认为此时前景和背景差异最大，此时的灰度t是最佳阈值   
  *       sb = w1*w2*(u1-u0)*(u0-u1)
******************************************************************************/
FunError_t ImageOtsu
	(
	 Image_t image, 
	 const int32_t x0, 
	 const int32_t y0, 
	 const int32_t dx, 
	 const int32_t dy,
	 const int32_t dir
	 )
{
	uint8_t* p1  = ImageGetBuffer(image);
    int32_t   w   = ImageGetWidth (image);
    int32_t   h   = ImageGetHeight(image);
    int32_t pitch = ImageGetPitch (image);
	int32_t hist[256];	// 图像直方图，256个点
	int32_t i, x, y;
	//int32_t total;                     //total为总和，累计值
	uint8_t gray;
	uint8_t *pS;
	int32_t n, n1, n2, gmin, gmax;
	int32_t thr_value = 1; // 阈值
	double m1, m2, sum, csum, fmax, sb;	//sb为类间方差，fmax存储最大方差值
	//dir == 1: >thr_value: 1, else: 0
	//dir == 0: >thr_value: 0, else: 1 
	//dir == 2: >thr_value: 0, else: 255
	//dir == 3: >thr_value: 255, else: 0
	uint32_t upper_thr, under_thr;
	if (dir == 0) {
		upper_thr = 0;
		under_thr = 1;
	} else if (dir == 1) {
		upper_thr = 1;
		under_thr = 0;
	} else if (dir == 2) {
		upper_thr = 0;
		under_thr = 255;
	} else if (dir == 3) {
		upper_thr = 255;
		under_thr = 0;
	} else {
		upper_thr = 1;
		under_thr = 0;
	}

	gmin=255; 
	gmax=0;

	if ((y0 < 0) || (x0 < 0) || (dy <= 0) || (dx <= 0) ||(y0+dy > h) || (x0+dx) > w) {	//参数处理
		fprintf (stderr, "bad input parameter.\n");
		return FunBadParameter;
	}

	//对直方图清0
	for (i = 0; i < 256; i++)
		hist[i] = 0;
	//生成直方图
	for (y = y0; y < (dy+y0); y++) {
		pS = p1 + pitch*y;
		for (x = x0; x < (dx+x0); x++) {
			gray = *(pS + x);
			hist[gray]++;
		}
	}

	//for (i = 0; i < 256; i++)
	//	printf("%d ", hist[i]);
	//printf("\n");
	//直方图平滑化
	//for (i = 0; i < 256; i++)
	//{
	//	total = 0;
	//	for (j = -2; j <= 2; j++)     //与附近2个灰度做平滑化，t值应取较小的值
	//	{
	//		gray = i + j;
	//		if (gray < 0)                              //越界处理
	//			gray = 0;
	//		if (gray > 255)
	//			gray = 255;
	//		total += hist[gray];    //total为总和，累计值
	//	}
	//	//平滑化,左边2个+中间1个+右边2个灰度,共5个,所以总和除以5,后面加0.5是用修正值
	//	hist[i] = (int32_t)((float)total / 5.0 + 0.5);
	//}

	//求阈值
	sum = csum = 0.0;
	n = 0;
	//计算总的图象的点数和质量矩，为后面的计算做准备
	for (i = 0; i < 256; i++) {
		//x*f(x)质量矩，也就是每个灰度的值乘以其点数（归一化后为概率），sum为其总和
		sum += (double)(i*hist[i]);	
		//n为图象总的点数，归一化后就是累积概率
		n += hist[i];						
	}

	if (!n) {
		// if n has no value, there is problems
		fprintf (stderr, "there is no value.\n");
		return FunBadParameter;
	}

	fmax = -1.0;	 //类间方差sb不可能为负，所以fmax初始值
	n1 = 0;
	for (i = 0; i < 256; i++) {	//对每个灰度（从0到255）计算一次分割后的类间方差sb
		n1 += hist[i];		//n1为在当前阈值遍前景图象的点数

		if (!n1)			//没有分出前景后景
			continue; 
		n2 = n - n1;		//n2为背景图象的点数
		if (n2 == 0)		//n2为0表示全部都是后景图象，与n1=0情况类似，
			break;			//之后的遍历不可能使前景点数增加，所以此时可以退出循环

		csum += (double)(i * hist[i]);	//前景的“灰度的值*其点数”的总和
		m1 = csum / n1;					//m1为前景的平均灰度
		m2 = (sum - csum) / n2;			 //m2为背景的平均灰度
		//sb为类间方差,按照公式,这里的n1, n2应该用n1/n和n2/n,不过对结果不影响
		sb = (double)n1 * (double) n2 * (m1 - m2) * (m1 - m2);
		if (sb > fmax) {	//如果算出的类间方差大于前一次算出的类间方差
			fmax = sb;
			thr_value = i;	//取最大类间方差时对应的灰度的i就是最佳阈值
		}
	}

#if defined __MY_DEBUG
		fprintf(stderr,"# ImageOtst: thr_value = %d gmin=%d gmax=%d\n",thr_value, gmin, gmax);
#endif

	//二值化
	for (y = y0; y < (dy+y0); y++) {
		pS = p1 + pitch*y;
		for (x = x0; x < (dx+x0); x++) {
			gray = *(pS + x);
			//if (dir == 0)
			//	*(pS + x) = (gray > thr_value) ? 0 : 1;
			//else 
			//	*(pS + x) = (gray > thr_value) ? 1 : 0;
			*(pS + x) = (gray > thr_value) ? upper_thr : under_thr;
		}
	}
	return FunOK;
}

//进行两次Otsu计算,第一次算出阈值,然后再在此阈值
//基础上进行新的一次Otsu计算
FunError_t ImageOtsuV1
	(
	 Image_t image, 
	 const int32_t x0, 
	 const int32_t y0, 
	 const int32_t dx, 
	 const int32_t dy,
	 const int32_t dir
	 )
{
	uint8_t* p1  = ImageGetBuffer(image);
    int32_t   w   = ImageGetWidth (image);
    int32_t   h   = ImageGetHeight(image);
    int32_t pitch = ImageGetPitch (image);
	int32_t hist[256];	// 图像直方图，256个点
	int32_t i, x, y;
	//int32_t total;                     //total为总和，累计值
	uint8_t gray;
	uint8_t *pS;
	int32_t n, n1, n2, gmin, gmax;
	int32_t thr_value = 1; // 阈值
	int32_t thr_value1 = 1;
	double m1, m2, sum, csum, fmax, sb;	//sb为类间方差，fmax存储最大方差值
	//dir == 1: >thr_value: 1, else: 0
	//dir == 0: >thr_value: 0, else: 1 
	//dir == 2: >thr_value: 0, else: 255
	//dir == 3: >thr_value: 255, else: 0
	uint32_t upper_thr, under_thr;
	if (dir == 0) {
		upper_thr = 0;
		under_thr = 1;
	} else if (dir == 1) {
		upper_thr = 1;
		under_thr = 0;
	} else if (dir == 2) {
		upper_thr = 0;
		under_thr = 255;
	} else if (dir == 3) {
		upper_thr = 255;
		under_thr = 0;
	} else {
		upper_thr = 1;
		under_thr = 0;
	}

	gmin=255; 
	gmax=0;

	if ((y0 < 0) || (x0 < 0) || (dy <= 0) || (dx <= 0) ||(y0+dy > h) || (x0+dx) > w) {	//参数处理
		fprintf (stderr, "bad input parameter.\n");
		return FunBadParameter;
	}

	//对直方图清0
	for (i = 0; i < 256; i++)
		hist[i] = 0;
	//生成直方图
	for (y = y0; y < (dy+y0); y++) {
		pS = p1 + pitch*y;
		for (x = x0; x < (dx+x0); x++) {
			gray = *(pS + x);
			hist[gray]++;
		}
	}


	//求阈值
	sum = csum = 0.0;
	n = 0;
	//计算总的图象的点数和质量矩，为后面的计算做准备
	for (i = 0; i < 256; i++) {
		//x*f(x)质量矩，也就是每个灰度的值乘以其点数（归一化后为概率），sum为其总和
		sum += (double)(i*hist[i]);	
		//n为图象总的点数，归一化后就是累积概率
		n += hist[i];						
	}

	if (!n) {
		// if n has no value, there is problems
		fprintf (stderr, "there is no value.\n");
		return FunBadParameter;
	}

	fmax = -1.0;	 //类间方差sb不可能为负，所以fmax初始值
	n1 = 0;
	for (i = 0; i <256; i++) {	//对每个灰度（从0到255）计算一次分割后的类间方差sb
		n1 += hist[i];		//n1为在当前阈值遍前景图象的点数

		if (!n1)			//没有分出前景后景
			continue; 
		n2 = n - n1;		//n2为背景图象的点数
		if (n2 == 0)		//n2为0表示全部都是后景图象，与n1=0情况类似，
			break;			//之后的遍历不可能使前景点数增加，所以此时可以退出循环

		csum += (double)(i * hist[i]);	//前景的“灰度的值*其点数”的总和
		m1 = csum / n1;					//m1为前景的平均灰度
		m2 = (sum - csum) / n2;			 //m2为背景的平均灰度
		//sb为类间方差,按照公式,这里的n1, n2应该用n1/n和n2/n,不过对结果不影响
		sb = (double)n1 * (double) n2 * (m1 - m2) * (m1 - m2);
		if (sb > fmax) {	//如果算出的类间方差大于前一次算出的类间方差
			fmax = sb;
			thr_value = i;	//取最大类间方差时对应的灰度的i就是最佳阈值
		}
	}

#if defined __MY_DEBUG
		fprintf(stderr,"# ImageOtst: thr_value = %d gmin=%d gmax=%d\n",thr_value, gmin, gmax);
#endif

	//对新得到的灰度范围再次进行otsu计算
	sum = csum = 0.0;
	n = 0;
	//计算总的图象的点数和质量矩，为后面的计算做准备
	for (i = thr_value; i < 256; i++) {
		//x*f(x)质量矩，也就是每个灰度的值乘以其点数（归一化后为概率），sum为其总和
		sum += (double)(i*hist[i]);	
		//n为图象总的点数，归一化后就是累积概率
		n += hist[i];						
	}

	if (!n) {
		// if n has no value, there is problems
		fprintf (stderr, "there is no value.\n");
		return FunBadParameter;
	}

	fmax = -1.0;	 //类间方差sb不可能为负，所以fmax初始值
	n1 = 0;

	for (i = thr_value; i < 256; i++) {	//对每个灰度（从0到255）计算一次分割后的类间方差sb
		n1 += hist[i];		//n1为在当前阈值遍前景图象的点数

		if (!n1)			//没有分出前景后景
			continue; 
		n2 = n - n1;		//n2为背景图象的点数
		if (n2 == 0)		//n2为0表示全部都是后景图象，与n1=0情况类似，
			break;			//之后的遍历不可能使前景点数增加，所以此时可以退出循环

		csum += (double)(i * hist[i]);	//前景的“灰度的值*其点数”的总和
		m1 = csum / n1;					//m1为前景的平均灰度
		m2 = (sum - csum) / n2;			 //m2为背景的平均灰度
		//sb为类间方差,按照公式,这里的n1, n2应该用n1/n和n2/n,不过对结果不影响
		sb = (double)n1 * (double) n2 * (m1 - m2) * (m1 - m2);
		if (sb > fmax) {	//如果算出的类间方差大于前一次算出的类间方差
			fmax = sb;
			thr_value1 = i;	//取最大类间方差时对应的灰度的i就是最佳阈值
		}
	}

#if defined __MY_DEBUG
		fprintf(stderr,"# ImageOtst: thr_value1 = %d gmin=%d gmax=%d\n",thr_value1, gmin, gmax);
#endif

	//二值化
	for (y = y0; y < (dy+y0); y++) {
		pS = p1 + pitch*y;
		for (x = x0; x < (dx+x0); x++) {
			gray = *(pS + x);
			//*(pS + x) = (gray > thr_value1) ? 0 : 1;
			*(pS + x) = (gray > thr_value1) ? upper_thr : under_thr;
		}
	}
	return FunOK;
}





/******************************************************************************
*******************************************************************************
************************下面的函数对指纹具有较强的适用性***********************
************************下面的函数对指纹具有较强的适用性***********************
************************下面的函数对指纹具有较强的适用性***********************
*******************************************************************************
******************************************************************************/


/******************************************************************************
  * 功能：图像数据的基于方向的智能二值化
  * 参数：pSrc				经过前后景分割的图像的数据指针	
  *		  pOrient			经过前后景分割的方向场数据指针
  *	      pGrads			经过前后景分割的梯度幅值数据指针
  *		  width				图像宽度
  *		  height			图像高度
  *		  pitch				图像每行字节数
  *		  dir				图像二值化方向
  * 返回：错误编号
  * 说明: 此处的二值仅指0和1,不是0和255,简单修改下就可以实现0和255的二值化
  *		  二值化化方式:
  *			dir == 1: >thr_value: 1, else: 0
  *			dir == 0: >thr_value: 0, else: 1 
  *			dir == 2: >thr_value: 0, else: 255
  *			dir == 3: >thr_value: 255, else: 0	
  *       指纹图像二值化有两种方法:灰度阈值分割法(常用的阈值分割)和智能
  *		  二值化邻域分析法.
  *		  智能二值化邻域分析法:
  *			原理:位于场中的粒子必然受到场的作用.同样,指纹纹线场(方向场)中的
  *				 指纹微粒也可以看做受其作用排列,并拥有场的性质.那么,在某一
  *				 区域内,在某一个指纹微粒的切线方向上,必然是同类指纹微粒.即
  *				 在某一区域内脊上某点的切线方向上的点还是属于脊,谷也同理.
  *			分析:1.对于纹线上的黑点,沿纹线方向的附近区域应该都是黑点,其灰度
  *				   值的和较小;纹线垂直方向上附近的都是白点,其灰度值较大.
  *				 2.对于纹线上之间的白点,沿纹线方向的附近区域应该都是白点,其灰度
  *				   值的和较大;纹线垂直方向上附近的都是黑点,其灰度值较小.
  *				   由此可得:对于一个点,如果切向灰度和小于法向灰度和,判断为黑点在
  *				   脊上.反之,则为白点在谷上.
  *		    实现:1.设f(x0,y0)为该点的灰度值,其方向场为O(x0,y0),w为邻域范围
  *				   H为切向像素值之和:H = sum(f(x,x/cos(O(x0,y0))))  (x=-w/2...w/2)
  *				   V为法向像素值之和:V = sum(f(x,x/sin(O(x0,y0))))  (x=-w/2...w/2)
  *				 2.如果V>H,该点在脊上,反之,在谷上
  *				 3.实际运算中,考虑到误差因素,故在求灰度和时,对每一点都设置了权值
  *				   采用加权平均的方法来降低误差
  *				   设纹线方向七点的权值为:			Hw=1/7(2,2,3,4,3,2,2)
  *				   设纹线方向垂直方向七点的权值为:	Vw=1/7(1,1,1,1,1,1,1)
  * 算法: 
  *		  1.获得方向场数据.函数的参数pOrient即为方向场数据,因此要确保先计算
  *		    得到pOrient(调用GetOrientation获得)
  *		  2.由pOrient数据得到每点的纹线角度,并调用AngleToDirection函数获得纹线
  *		    方向
  *		  3.由纹线方向对g_direction_xy数组索引表进行索引,获得对应方向上点的坐标
  *		  4.分别利用加权滤波器Hw和Vw对纹线水平方向,垂直方向进行加权滤波
  *		  5.根据纹线和垂直于纹线等到的加权滤波值,判断图像是那种颜色.
  *	总结: 
  *       加速算法(模版大小固定7x7):
  *			  (1)为了加快速度,将Gabor函数制成模版,用模版来拟合Gabor函数,如:
  *		         这里的OrientBinary函数.
  *			  (2)又因为二维矩形模版运算也很耗时,故将矩形模版变为两条相交的
  *			     线段性模版,这样作模版运算,运算量就小很多.
  *			  (3)化简后得到的切向滤波模版是:		Hw=1/7(2,2,3,4,3,2,2)
  *							 法向滤波模版是:		Vw=1/7(1,1,1,1,1,1,1)
  *	P.S.: 函数OrientEnhance的实现与之类似
******************************************************************************/
void OrientBinary
(
 uint8_t *pSrc, 
 uint8_t *pOrientation, 
 uint8_t *pGrads,
 int32_t width, 
 int32_t height, 
 int32_t pitch, 
 int32_t dir
)
{
	int32_t x, y;
	int32_t i;
	int32_t d = 0;
	int32_t sum = 0;
	int32_t hsum = 0;	// 纹线方向上的7个点的加权和
	int32_t vsum = 0;	// 纹线方向的垂直方向上的7个点的加权和	
	// 纹线方向上的7个点的权值
	int32_t Hw[7] = {2, 2, 3, 4, 3, 2, 2};
	// 纹线方向的垂直方向上的7个点的权值
	int32_t Vw[7] = {1, 1, 1, 1, 1, 1, 1};

	int32_t Hv = 0;		// 纹线方向上的7个点的加权平均值
	int32_t Vv = 0;		// 纹线方向的垂直方向上的7个点的加权平均值
	int32_t tempY = 0;
	uint8_t *pS = NULL;		// 指纹图像像素点指针
	uint8_t *pT = NULL;		//pTemp指针
	uint8_t *pOri = NULL;	//纹线方向指针
	uint8_t *pTemp = NULL;	//临时数据缓存区
	//uint32_t under_thr = 0;
	//uint32_t upper_thr = 1;

	// 某点周围8个点的地址偏移
	int32_t	SiteD8[8] = {pitch-1, pitch, pitch+1, 1, -pitch+1, -pitch, -pitch-1, -1};
	int32_t exit = 1;
	int32_t n = 0;
	int32_t num = 0;
	//dir == 1: >thr_value: 1, else: 0
	//dir == 0: >thr_value: 0, else: 1 
	//dir == 2: >thr_value: 0, else: 255
	//dir == 3: >thr_value: 255, else: 0
	uint32_t upper_thr, under_thr;
	if (dir == 0) {
		upper_thr = 0;
		under_thr = 1;
	} else if (dir == 1) {
		upper_thr = 1;
		under_thr = 0;
	} else if (dir == 2) {
		upper_thr = 0;
		under_thr = 255;
	} else if (dir == 3) {
		upper_thr = 255;
		under_thr = 0;
	} else {
		upper_thr = 1;
		under_thr = 0;
	}
	
	pTemp = (uint8_t *)malloc(sizeof(uint8_t)*width*height);

	if (pTemp == NULL)
		return;

	tempY = 0;
	for(y = 0; y < height; y++) {
		//优化前
		//tempY = y*pitch;	
		for(x = 0; x < width; x++) {
			pOri = pOrientation + tempY + x;
			pS = pSrc + tempY + x;			
			//如果该点非常黑，则在临时缓冲区内置该点为黑点，值为0
			if(*pS < 4) {
				*(pTemp + tempY + x) = 0;
				continue;
			}

			// 计算纹线方向的方向索引（量化为12个方向）
			d = AngleToDirection(*pOri);
			// 计算当前点在纹线方向上的加权平均值
			sum = 0;
			hsum = 0;
			for(i = 0; i < 7; i++) {
				// 坐标是否越界
				if((y+g_direction_xy[d][i][1] < 0) || \
				   (y+g_direction_xy[d][i][1] >= height) || \
				   (x+g_direction_xy[d][i][0] < 0) || \
				   (x+g_direction_xy[d][i][0] >= width)) {	
					   continue;
				}
				sum += Hw[i]*(*(pS + g_direction_xy[d][i][1]*pitch + g_direction_xy[d][i][0]));
				hsum += Hw[i];
			}
			if(hsum != 0) {
				Hv = sum/hsum;
			} else {
				Hv = 255;
			}

			// 纹线方向的垂直方向的索引
			d = (d+6)%12;
			// 计算当前点在纹线方向的垂直方向上的加权平均值
			sum = 0;
			vsum = 0;
			for(i = 0; i < 7; i++) {
				if((y+g_direction_xy[d][i][1] < 0) || \
				   (y+g_direction_xy[d][i][1] >= height) || \
				   (x+g_direction_xy[d][i][0] < 0) || \
				   (x+g_direction_xy[d][i][0] >= width)) {
					   continue;
				}
				sum += Vw[i]*(*(pS + g_direction_xy[d][i][1]*pitch + g_direction_xy[d][i][0]));
				vsum += Vw[i];
			}
			if(vsum != 0) {
				Vv = sum/vsum;
			} else {
				Vv = 255;
			}

			//比较纹线及其垂直方向的大小
			if(Hv < Vv) {
				// 纹线方向上加权平均值较小则置当前点为黑点
				//*(pTemp + tempY + x) = 0;
				*(pTemp + tempY + x) = under_thr;
			} else {
				// 纹线方向上加权平均值较大则置当前点为白点
				//*(pTemp + tempY + x) = 255;
				*(pTemp + tempY + x) = upper_thr;
			}
		}
		//优化后
		tempY += pitch;
	}

	//将临时缓冲区内数据拷贝到原始图像数据缓冲区,注释掉这一句,这样pTemp
	//就作为下面对二值化指纹图像进行去噪的源数据了
	//memcpy(pSrc, pTemp, sizeof(uint8_t)*width*height);

	//对二值化指纹图像进行去噪声
	n = 0;
	num = 0;
	exit = 1;
	// 循环处理直到处理完毕或者处理次数超过8
	while(exit && n < 8) {
		exit = 0;
		n++;
		//tempY = pitch;
		tempY = 0;
		//for(y = 1; y < height-1; y++) {
		for(y = 0; y < height; y++) {
			//优化前
			//tempY = y*pitch
			//for(x = 1; x < width-1; x++) {
			for(x = 0; x < width; x++) {
				//防止越界
				if ((x < 1) || (x >= width-1) || \
					(y < 1) || (y >= height-1)) {
					*(pSrc + tempY + x) = upper_thr;	//对边缘区域修改为二值化的背景点
					continue;
				}
				// 背景的点不处理
				if(*(pGrads + tempY + x) == 0) {
					*(pSrc + tempY + x) = upper_thr;	//对背景区域修改为二值化的背景点
					continue;
				}
				// 统计当前点周围与它相同类型点的个数
				num = 0;
				//pS = pSrc + tempY + x;
				pT = pTemp + tempY + x;
				for(i = 0; i < 8; i++) {
					//if(*(pS+SiteD8[i]) == *pS) {
					if(*(pT+SiteD8[i]) == *pT) {
						num++;
					}
				}
				
				if(num < 2) {
					//相同点个数小于二则改变当前点类型(0-->0,255-->1)
					//*(pTemp+temp+x) = 255 - *pS;
					//*(pSrc + tempY + x) = 255 - *pT;
					if ((*(pTemp+tempY+x)) == under_thr)
						*(pSrc + tempY + x) = upper_thr;
					else
						*(pSrc + tempY + x) = under_thr;
					exit = 1;
				} else {	//否则不改变(0-->0,255-->1)
					//*(pTemp+temp+x) = *pS;
					if ((*(pTemp+tempY+x)) == under_thr)
						*(pSrc + tempY + x) = under_thr;
					else
						*(pSrc + tempY + x) = upper_thr;
				}

			}
			//优化后
			tempY += pitch;
		}
	}

	if (pTemp != NULL) {
		free(pTemp);
		pTemp = NULL;
	}

}


/******************************************************************************
  * 功能：利用梯度对指纹图像进行前景与背景的分割
  * 参数：image			经过前后景分割的指纹图像[Out]
  *       image_ori		经过前后景分割的方向场[In]
  *		  image_grads	经过前后景分割的梯度(用于判断像素点是前景还是背景)[In]
  *       dir			二值化方向
  * 返回：错误编号
  * 说明: 此处的二值仅指0和1,不是0和255,简单修改下就可以实现0和255的二值化
  *		  二值化化方式:
  *			dir == 1: >thr_value: 1, else: 0
  *			dir == 0: >thr_value: 0, else: 1 
  *			dir == 2: >thr_value: 0, else: 255
  *			dir == 3: >thr_value: 255, else: 0	
  *       指纹图像二值化有两种方法:灰度阈值分割法(常用的阈值分割)和智能
  *		  二值化邻域分析法.
  *		  智能二值化邻域分析法:
  *			原理:位于场中的粒子必然受到场的作用.同样,指纹纹线场(方向场)中的
  *				 指纹微粒也可以看做受其作用排列,并拥有场的性质.那么,在某一
  *				 区域内,在某一个指纹微粒的切线方向上,必然是同类指纹微粒.即
  *				 在某一区域内脊上某点的切线方向上的点还是属于脊,谷也同理.
  *			分析:1.对于纹线上的黑点,沿纹线方向的附近区域应该都是黑点,其灰度
  *				   值的和较小;纹线垂直方向上附近的都是白点,其灰度值较大.
  *				 2.对于纹线上之间的白点,沿纹线方向的附近区域应该都是白点,其灰度
  *				   值的和较大;纹线垂直方向上附近的都是黑点,其灰度值较小.
  *				   由此可得:对于一个点,如果切向灰度和小于法向灰度和,判断为黑点在
  *				   脊上.反之,则为白点在谷上.
  *		    实现:1.设f(x0,y0)为该点的灰度值,其方向场为O(x0,y0),w为邻域范围
  *				   H为切向像素值之和:H = sum(f(x,x/cos(O(x0,y0))))  (x=-w/2...w/2)
  *				   V为法向像素值之和:V = sum(f(x,x/sin(O(x0,y0))))  (x=-w/2...w/2)
  *				 2.如果V>H,该点在脊上,反之,在谷上
  *				 3.实际运算中,考虑到误差因素,故在求灰度和时,对每一点都设置了权值
  *				   采用加权平均的方法来降低误差
  *				   设纹线方向七点的权值为:			Hw=1/7(2,2,3,4,3,2,2)
  *				   设纹线方向垂直方向七点的权值为:	Vw=1/7(1,1,1,1,1,1,1)
******************************************************************************/
FunError_t ImageOrientBinary
(
 Image_t image,
 Image_t image_ori,
 Image_t image_grads,
 const int32_t dir
)
{
	//获取指纹数据,方向场数据,梯度数据指针
	uint8_t *pSrc  = ImageGetBuffer(image);
	uint8_t *pOri = ImageGetBuffer(image_ori);
	uint8_t *pGrads = ImageGetBuffer(image_grads);
    int32_t   width   = ImageGetWidth (image);
    int32_t   height   = ImageGetHeight(image);
    int32_t pitch = ImageGetPitch (image);

	if (pSrc == NULL || pOri == NULL || pGrads == NULL)
		return FunMemory;

	OrientBinary(pSrc, pOri, pGrads, width, height, pitch, dir);

	return FunOK;
}








/******************************************************************************
  * 功能：图像二值互换(OZ二值与黑白二值互换)
  * 参数：pSrc        图像必须为二值化后的图像数据
  * 参数：dir         从1:OZ-->WB, 0:WB-->OZ
  * 返回：错误编号
******************************************************************************/
FunError_t BinaryExchange(uint8_t *pSrc, const int32_t w, int32_t h, const int32_t dir)
{
	//uint8_t* p1  = ImageGetBuffer(image);
 //   int32_t   w   = ImageGetWidth (image);
 //   int32_t   h   = ImageGetHeight(image);
 //   int32_t pitch = ImageGetPitch (image);
	int32_t i;
	int32_t size = w * h;
	uint8_t temp;

	for (i = 0; i < size; i++) {
		temp = *pSrc;
		if (dir) {	//从 OZ->WB(TOWB)
			*pSrc = (temp == 0) ? 0 : 255;
		} else {	//从 WB->OZ(TOOZ)
			*pSrc = (temp == 0) ? 0 : 1;
		}
		pSrc++;
	}
	return FunOK;
}


/******************************************************************************
  * 功能：图像二值互换(OZ二值与黑白二值互换)
  * 参数：
  *       pSrc      图像必须为二值化后的图像数据
  *       w			图像宽度
  *       h			图像高度
  *       pitch		图像每行字节数
  *       x0		截取图像部分的开始x坐标
  *       y0		截取图像部分的开始y坐标
  *       dx		截取图像部分的宽度
  *       dy		截取图像部分的高度
  *       dir       从1:OZ-->WB, 0:WB-->OZ
  * 返回：错误编号
  * 说明: 此处的二值仅指0和1,不是0和255,简单修改下就可以实现0和255的二值化
  * 算法描述: 
******************************************************************************/
FunError_t BinaryExchangeV1
	(
	 uint8_t *pSrc, 
	 const int32_t w, 
	 const int32_t h, 
	 const int32_t pitch,
	 const int32_t x0, 
	 const int32_t y0, 
	 const int32_t dx, 
	 const int32_t dy, 
	 const int32_t dir
	 )
{
	int32_t i, j;
	uint8_t temp;
	uint8_t *pS;

	if ((y0 < 0) || (x0 < 0) || (dy <= 0) || (dx <= 0) ||(y0+dy > h) || (x0+dx) > w) {	//参数处理
		//fprintf (stderr, "bad input parameter.\n");
		return FunBadParameter;
	}

	for (j = y0; j < (y0+dy); j++) {
		pS = pSrc + j*pitch;
		for (i = x0; i < (x0+dx); i++) {
			temp = *(pS + i);
			if (dir) {	//从 OZ->WB(TOWB)
				*(pS+i) = (temp == 0) ? 0 : 255;
			} else {	//从 WB->OZ(TOOZ)
				*(pS+i) = (temp == 0) ? 0 : 1;
			}
		}
	}
	return FunOK;
}

