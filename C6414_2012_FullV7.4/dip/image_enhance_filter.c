/******************************************************************************
 * 文件名：image_enhance_filter.h
 * 功能：  一些基本的图像增强和滤波操作
******************************************************************************/


#include "dip_header/image_enhance_filter.h"


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <string.h>


/******************************************************************************
  * 功能：图像数据软化(平滑)操作，通过计算均值实现
  * 参数：pDst      平滑(软化)后数据
  *		  pSrc		软化(平滑)前数据
  *		  width		数据宽度
  *		  height	数据高度
  *		  pitch		每行字节数
  *       size      软化(平滑)窗口大小(2*r+1)
  *		  step		软化(平滑)步长
  * 返回：
******************************************************************************/
void MeanSmooth
(
 uint8_t *pDst, 
 uint8_t *pSrc, 
 const int32_t width,
 const int32_t height,
 const int32_t pitch,
 const int32_t size, 
 const int32_t step
 )
{
	int32_t x,y,r,p,q;
	int32_t sum, num;
	r = size/2;	
	for (y = r; y < height-r; y++) {
		for (x = r; x < width-r; x++) {
			sum = 0;
			num = 0;
			//优化前
			//for (q=-r;q<=r;q+=step) {
			//	for (p=-r;p<=r;p+=step) {
   // 				 sum += pSrc[(x+p)+(y+q)*pitch];
			//		 num++;
			//	}
			//}
			//优化后
			for (q = y-r; q <= y+r; q+=step) {
				for (p = x-r; p <= x+r; p+=step) {
					sum += pSrc[p+q*pitch];
					num++;
				}
			}

			pDst[x+y*pitch] = sum/num;
		}
	}
}

/******************************************************************************
  * 功能：图像数据软化(平滑)操作，通过计算均值实现
  * 参数：pDst      平滑(软化)后数据
  *		  pSrc		软化(平滑)前数据
  *		  width		数据宽度
  *		  height	数据高度
  *		  pitch		每行字节数
  *       size      软化(平滑)窗口大小(2*r+1)
  *		  step		软化(平滑)步长
  * 返回：
******************************************************************************/
void MeanSmoothV1
(
 uint8_t *pDst, 
 uint8_t *pSrc, 
 const int32_t width,
 const int32_t height,
 const int32_t pitch,
 const int32_t size, 
 const int32_t step
 )
{
	int32_t x,y,r,p,q;
	int32_t sum, num;
	r = size/2;	
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			if ((y < r) || (y >= height - r) ||\
				(x < r) || (x >= width - r)) {
				pDst[x+y*pitch] = 0;
				continue;
			}
			sum = 0;
			num = 0;
			//优化前
			//for (q=-r;q<=r;q+=step) {
			//	for (p=-r;p<=r;p+=step) {
   // 				 sum += pSrc[(x+p)+(y+q)*pitch];
			//		 num++;
			//	}
			//}
			//优化后
			for (q = y-r; q <= y+r; q+=step) {
				for (p = x-r; p <= x+r; p+=step) {
					sum += pSrc[p+q*pitch];
					num++;
				}
			}

			pDst[x+y*pitch] = sum/num;
		}
	}
}









/******************************************************************************
*******************************************************************************
************************下面的函数对指纹具有较强的适用性***********************
************************下面的函数对指纹具有较强的适用性***********************
************************下面的函数对指纹具有较强的适用性***********************
*******************************************************************************
******************************************************************************/

//7x7邻域分块模板,以某点(x0,y0)为中心,以单个像素为
//量化单位的12个方向上的点的偏移(x0,y0)的坐标值(off_x,off_y)
//12:12个方向 
//7:7x7模版 
//2:表示偏移(off_x,off_y)坐标值.前面的为off_x,后面的为off_y
int g_direction_xy[12][7][2] = {
	-3, 0,  -2, 0,  -1, 0,   0, 0,   1, 0,   2, 0,   3, 0,
	-3,-1,  -2,-1,  -1, 0,   0, 0,   1, 0,   2, 1,   3, 1,
	-3,-2,  -2,-1,  -1,-1,   0, 0,   1, 1,   2, 1,   3, 2,
	-3,-3,  -2,-2,  -1,-1,   0, 0,   1, 1,   2, 2,   3, 3,
	-2,-3,  -1,-2,  -1,-1,   0, 0,   1, 1,   1, 2,   2, 3,
	-1,-3,  -1,-2,   0,-1,   0, 0,   0, 1,   1, 2,   1, 3,
	 0,-3,   0,-2,   0,-1,   0, 0,   0, 1,   0, 2,   0, 3,
	-1, 3,  -1, 2,   0, 1,   0, 0,   0,-1,   1,-2,   1,-3,
	-2, 3,  -1, 2,  -1, 1,   0, 0,   1,-1,   1,-2,   2,-3,
	-3, 3,  -2, 2,  -1, 1,   0, 0,   1,-1,   2,-2,   3,-3,
	-3, 2,  -2, 1,  -1, 1,   0, 0,   1,-1,   2,-1,   3,-2,
	-3, 1,  -2, 1,  -1, 0,   0, 0,   1, 0,   2,-1,   3,-1
};

/******************************************************************************
  * 功能：由角度算出方向,得到的作为方向分块数组(g_direction_xy)的索引,被调用
  * 参数：angle		某点的纹线方向角度(0-180)
  * 返回：方向
  * 说明: 
******************************************************************************/
int32_t AngleToDirection(int32_t angle)
{
	if((angle>=173) || (angle<8))
		return 0;
	else
		return ((angle-8)/15 + 1);
}

/******************************************************************************
  * 功能：图像数据的方向增强(有Gabor小波增强算法改善运算速度演变而来)
  * 参数：pSrc				欲增强图像的数据指针	
  *		  pOrient			方向场数据指针(调用GetOrientation获得)
  *		  width				图像宽度
  *		  height			图像高度
  *		  pitch				图像每行字节数
  * 返回：错误编号
  * 说明: 1.利用方向场计算函数计算得到图像每点(x,y)的方向场
  *		  2.然后调用方向增强函数(方向图增强或小波增强)对图像进行方向增强,
  *		  3.最终得到方向增强后的图像.
  *		  基于指纹图像场场论和Gabor小波两个工具,解决了图像的智能增强问题.
  *			利用指纹图像场场论可以获得"方向场"和"频率场"
  *			利用Gabor小波函数,可以在该位置方向场上对图像进行增强,以弥补图像中
  *			纹线的断裂等不足.
  * 算法: 
  *		  1.获得方向场数据.函数的参数pOrient即为方向场数据,因此要确保先计算
  *		    得到pOrient(调用GetOrientation获得)
  *		  2.由pOrient数据得到每点的纹线角度,并调用AngleToDirection函数获得纹线
  *		    方向
  *		  3.由纹线方向对g_direction_xy数组索引表进行索引,获得对应方向上点的坐标
  *		  4.分别利用平滑滤波器Hw和Vw对纹线水平方向进行平滑滤波,垂直方向进行锐化
  *			滤波.
  *	总结: 对每一点进行Gabor函数运算,即可实现智能增强的效果.如:
  *		  ImageEnhanceGabor等函数.
  *       加速算法(模版大小固定7x7):
  *			  (1)为了加快速度,将Gabor函数制成模版,用模版来拟合Gabor函数,如:
  *		         这里的OrientEnhance函数.
  *			  (2)又因为Gabor函数模版运算也很耗时,故将矩形模版变为两条相交的
  *			     线段性模版,这样作模版运算,运算量就小很多.
  *			  (3)化简后得到的切向滤波模版是:		Hw=1/7( 1, 1,1,1,1, 1, 1)
  *							 法向滤波(锐化)模版是	Vw=1/7(-3,-1,3,9,3,-1,-3)
  *	P.S.: 函数OrientBinary的实现与之类似
******************************************************************************/
void OrientEnhance
(
 uint8_t *pSrc, 
 uint8_t *pOrientation, 
 const int32_t width, 
 const int32_t height,
 const int32_t pitch 
)
{
	int32_t x, y;
	int32_t i;
	int32_t d = 0;
	int32_t sum = 0;
	// 纹线方向上进行平滑滤波的平滑滤波器
	int32_t Hw[7] = {1, 1, 1, 1, 1, 1, 1};
	// 纹线方向的垂直方向上进行锐化滤波的锐化滤波器
	int32_t Vw[7] = {-3, -1, 3, 9, 3, -1, -3};
	int32_t hsum = 0;
	int32_t vsum = 0;
	int32_t tempY = 0;
	uint8_t  *pS;
	uint8_t  *pOri;
	//uint8_t pFPTemp[FP_HEIGHT*FP_WIDTH];
	uint8_t *pFPTemp = fp_src_copy.pimg;

	//uint8_t *pFPTemp = new uint8_t[width * height];
	//uint8_t *pFPTemp = (uint8_t *)malloc(sizeof(uint8_t)*width*height);

	// 纹线方向上进行平滑滤波
	tempY = 0;
	for(y = 0; y < height; y++) {
		//优化前
		//tempY = y*pitch;	
		for(x = 0; x < width; x++) {
			pOri = pOrientation + tempY + x;
			pS = pSrc + tempY + x;
			// 纹线方向的索引
			d = AngleToDirection(*pOri);
			sum = 0;
			hsum = 0;
			for(i = 0; i < 7; i++) {
				//防止越界
				if((y+g_direction_xy[d][i][1] < 0) ||\
				   (y+g_direction_xy[d][i][1] >= height) ||\
				   (x+g_direction_xy[d][i][0] < 0) ||\
				   (x+g_direction_xy[d][i][0] >= width)) {
					continue;
				}
				sum += Hw[i]*(*(pS + g_direction_xy[d][i][1]*pitch + g_direction_xy[d][i][0]));
				hsum += Hw[i];
			}
			if(hsum != 0) {
				*(pFPTemp + tempY + x) = (uint8_t)(sum/hsum);
			} else {
				*(pFPTemp + tempY + x) = 255;			//边缘点设为背景(白色)
			}
		}
		//优化后
		tempY += pitch;
	}

	// 纹线方向的垂直方向上进行锐化滤波
	tempY = 0;
	for(y = 0; y < height; y++) {
		//优化前
		//tempY = y*pitch;
		for(x = 0; x < width; x++) {
			pOri = pOrientation + tempY + x;
			pS = fp_src_copy.pimg + tempY + x;//pFPTemp + tempY + x;	
			// 纹线方向的垂直方向的索引
			d = (AngleToDirection(*pOri)+6) % 12;
			sum = 0;
			vsum = 0;
			for(i = 0; i < 7; i++) {
				//防止越界
				if((y+g_direction_xy[d][i][1] < 0) ||\
				   (y+g_direction_xy[d][i][1] >= height) ||\
				   (x+g_direction_xy[d][i][0] < 0) ||\
				   (x+g_direction_xy[d][i][0] >= width)) {
					continue;
				}
				sum += Vw[i]*(*(pS + g_direction_xy[d][i][1]*pitch + g_direction_xy[d][i][0]));
				vsum += Vw[i];
			}
			if(vsum > 0) {
				sum /= vsum;
				if(sum > 255) {
					*(pSrc + tempY + x) = 255;			//边缘点设为背景(白色)
				} else if(sum < 0) {
					*(pSrc + tempY + x) = 0;
				} else {
					*(pSrc + tempY + x) = (uint8_t)sum;
				}
			} else {
				*(pSrc + tempY + x) = 255;				//边缘点设为背景(白色)
			}
		}
		//优化后
		tempY += pitch;
	}

	//if (pFPTemp != NULL) {
	//	free(pFPTemp);
	//	pFPTemp = NULL;
	//}

}

