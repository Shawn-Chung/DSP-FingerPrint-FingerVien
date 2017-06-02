/******************************************************************************
 * 文件名：image_base.c
 * 功能：  一些基本的图像操作
******************************************************************************/


#include "dip_header/image_base.h"
#include "dip_header/image.h"


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <string.h>

//#pragma warning (disable:4996)



/******************************************************************************
  * 功能：图像灰度归一
  * 参数：pDst			处理后图像数据
  *		  pSrc			处理前图像数据
  *		  width			图像数据宽度
  *		  height		图像数据高度
  *		  pitch			图像数据每行字节数
  * 返回：
  * 算法: ImgNew(x,y)=[(ImgOld(x,y)-min_gray)*255]/(max_gray-min_gray);
******************************************************************************/
void GrayNormalize
(
 uint8_t *pDst, 
 uint8_t *pSrc, 
 const int32_t src_width,
 const int32_t src_height,
 const int32_t src_pitch
 )
{
	int32_t i, temp;
	int32_t min_gray, max_gray, max_min;
	uint8_t *p1 = pSrc;
	int32_t size = src_width * src_height;

	//求最大,最小灰度
	max_gray = 0;
	min_gray = 255;
	for (i = 0; i < size; i++) {
		min_gray = (*p1) > min_gray ? min_gray : (*p1);
		max_gray = (*p1) < max_gray ? max_gray : (*p1);
		p1++;
	}

	//求差,并赋给max_gray;
	max_min = max_gray - min_gray;
	for (i = 0; i < size; i++) {
		//if ((*p) < (uint8_t)min_gray) {
		//		*p = 0;
		//	} else if ((*p) > (uint8_t)max_gray){
		//		*p = 255;
		//	} else {
				temp = pSrc[i];
				temp -= min_gray;
				temp = (temp * 255) / max_min;
				pDst[i] = (uint8_t)temp;
			//}
		//pSrc++;
	}
}


//void GrayNormalizeV1
//(
// uint8_t *pDst, 
// uint8_t *pSrc,
// uint8_t *pSeg,
// const int32_t src_width,
// const int32_t src_height,
// const int32_t src_pitch
// )
//{
//	int32_t i, temp;
//	int32_t min_gray, max_gray, max_min;
//	uint8_t *p1 = pSrc;
//	int32_t size = src_width * src_height;
//
//	//求最大,最小灰度
//	max_gray = 0;
//	min_gray = 255;
//	for (i = 0; i < size; i++) {
//		if (*(pSeg+i) == 255) {
//			p1++;
//			continue;
//		}
//		min_gray = (*p1) > min_gray ? min_gray : (*p1);
//		max_gray = (*p1) < max_gray ? max_gray : (*p1);
//		p1++;
//	}
//
//	//求差,并赋给max_gray;
//	max_min = max_gray - min_gray;
//	for (i = 0; i < size; i++) {
//		//if ((*p) < (uint8_t)min_gray) {
//		//		*p = 0;
//		//	} else if ((*p) > (uint8_t)max_gray){
//		//		*p = 255;
//		//	} else {
//		if (*(pSeg+i) == 255) {
//			continue;
//		}
//				temp = pSrc[i];
//				temp -= min_gray;
//				temp = (temp * 255) / max_min;
//				pDst[i] = (uint8_t)temp;
//			//}
//		//pSrc++;
//	}
//}


/******************************************************************************
  * 功能：图像的梯度及其幅值计算,输出梯度幅值数据(被图像梯度获取函数调用)
  * 参数：pDst				输出数据
  *		  pSrc				输入数据
  *       width				正常图像宽度
  *		  height			正常图像高度
  * 返回：
******************************************************************************/
void HalfWidthHeight(uint8_t *pDst, uint8_t *pSrc, const int32_t width, const int32_t height)
{
	//int32_t	x, y;
	//uint8_t *pS;
	//uint8_t *pD;
	//int32_t	sum;
	////int32_t SiteD8[8] = {width-1, width, width+1, 1, -width+1, -width, -width-1, -1};
	//int32_t SiteD8[8];
	//SiteD8[0] = width-1;
	//SiteD8[1] = width;
	//SiteD8[2] = width+1;
	//SiteD8[3] = 1;
	//SiteD8[4] = -width+1;
	//SiteD8[5] = -width;
	//SiteD8[6] = -width-1;
	//SiteD8[7] = -1;
	////左右边缘部分 
	//for(y = 0; y < height; y+=2) {
	//	pS = pSrc + y*width;
	//	pD = pDst + (y/2)*(width/2);
	//	*pD = *pS;
	//	pS = pSrc + y*width + width - 1;
	//	pD = pDst + (y/2)*(width/2) + (width/2 - 1);
	//	*pD = *pS;
	//}
	////上下边缘部分
	//for(x = 0; x < width; x+=2) {
	//	pS = pSrc + x;
	//	pD = pDst + x/2;
	//	*pD = *pS;
	//	pS = pSrc + (height-1)*width + x;
	//	pD = pDst + (height/2-1)*(width/2) + x/2;
	//	*pD = *pS;
	//}

	//// 非边缘部分用高斯模板提取低频信息
	//// 1 2 1
	//// 2 4 2
	//// 1 2 1
	//for(y = 2; y < height-2; y += 2) {
	//	for(x = 2; x < width-2; x += 2) {
	//		pS = pSrc + y*width + x;
	//		pD = pDst + (y/2)*(width/2) + x/2;
	//		sum = *pS*4 + *(pS + SiteD8[0]) +
	//			  *(pS + SiteD8[1])*2 + *(pS + SiteD8[2]) +
	//			  *(pS + SiteD8[3])*2 + *(pS + SiteD8[4]) +
	//			  *(pS + SiteD8[5])*2 + *(pS + SiteD8[6]) +
	//			  *(pS + SiteD8[7])*2;

	//		sum = sum>>4;
	//		*pD = (uint8_t)sum;
	//	}
	//}
	int32_t	x, y;
	uint8_t *pS;
	uint8_t *pD;
	int32_t	sum;
	int32_t tempY = 0, tempY2 = 0;
	//int32_t SiteD8[8] = {width-1, width, width+1, 1, -width+1, -width, -width-1, -1};
	int32_t SiteD8[8];
	SiteD8[0] = width-1;
	SiteD8[1] = width;
	SiteD8[2] = width+1;
	SiteD8[3] = 1;
	SiteD8[4] = -width+1;
	SiteD8[5] = -width;
	SiteD8[6] = -width-1;
	SiteD8[7] = -1;
	//左右边缘部分 
	for(y = 0; y < height; y+=2) {
		pS = pSrc + y*width;
		//pD = pDst + (y/2)*(width/2);
		pD = pDst + (y>>1)*(width>>1);
		*pD = *pS;
		pS = pSrc + y*width + width - 1;
		//pD = pDst + (y/2)*(width/2) + (width/2 - 1);
		pD = pDst + (y>>1)*(width>>1) + ((width>>1) - 1);
		*pD = *pS;
	}
	//上下边缘部分
	for(x = 0; x < width; x+=2) {
		pS = pSrc + x;
		//pD = pDst + x/2;
		pD = pDst + (x>>1);
		*pD = *pS;
		pS = pSrc + (height-1)*width + x;
		//pD = pDst + (height/2-1)*(width/2) + x/2;
		pD = pDst + ((height>>1)-1)*(width>>1) + (x>>1);
		*pD = *pS;
	}

	// 非边缘部分用高斯模板提取低频信息
	// 1 2 1
	// 2 4 2
	// 1 2 1
	for(y = 2; y < height-2; y += 2) {
		tempY = y*width;
		tempY2 = (y>>1)*(width>>1);
		for(x = 2; x < width-2; x += 2) {
			pS = pSrc + tempY + x;
			//pD = pDst + (y/2)*(width/2) + x/2;
			pD = pDst +  tempY2 + (x>>1);
			sum = *pS*4 + *(pS + SiteD8[0]) +
				*(pS + SiteD8[1])*2 + *(pS + SiteD8[2]) +
				*(pS + SiteD8[3])*2 + *(pS + SiteD8[4]) +
				*(pS + SiteD8[5])*2 + *(pS + SiteD8[6]) +
				*(pS + SiteD8[7])*2;

			sum = sum>>4;
			*pD = (uint8_t)sum;
		}
	}
}

/******************************************************************************
  * 功能：图像数据的缩放函数(双线性插值法)--使用浮点运算,底层函数,被图像缩放函数调用
  * 参数：pDst				缩放后图像数据
  *       dst_width			缩放后图像宽度
  *		  dst_height		缩放后图像高度
  *		  dst_pitch			缩放后图像每行字节数
  *		  pSrc				缩放前图像数据
  *       src_width			缩放前图像宽度
  *		  src_height		缩放前图像高度
  *		  src_pitch			缩放前图像每行字节数
  *		  inter_type		插值方法
  *		  image_type		图像类型(8位灰度or32位彩色)
  * 返回：错误编号
  * 说明: 考虑了边界问题
  * 算法: 使用最近临插值,双线性插值实现图像的缩放
******************************************************************************/
//void SizeNormalize
//( 
// uint8_t *pDst, 
// const int32_t dst_width, 
// const int32_t dst_height,
// const int32_t dst_pitch,
// uint8_t *pSrc, 
// const int32_t src_width,
// const int32_t src_height,
// const int32_t src_pitch,
// Interpolation_t inter_type,
// ImageFlag_t image_type
// )
//{
//	uint8_t *pS, *pD;		//图像数据指针
//	//目标图像坐标(x, y)
//	int32_t x, y, k;
//	//目标图像像素点(x,y)向后映射的坐标(tempx, tempy)
//	//(tempx, tempy)缩小后其最临近的4个点的横纵坐标
//	double tempx, tempy;
//	int32_t sx1, sx2, sy1, sy2;
//
//	//最临近4个点的灰度值gray1,2,3,4
//	//gray5,6为按4个点权重所得的中间值
//	int32_t gray1, gray2, gray3, gray4, gray5, gray6;
//
//	//4个点对于计算灰度是所占的权重
//	double dy,dx;
//	double bfx = (double)(src_width) / dst_width;
//	double bfy = (double)(src_height) / dst_height;
//
//	pS = pSrc;
//	pD = pDst;
//
//	//通过双线性插值求尺寸归一化后目标图像(x,y)的灰度值
//	if (inter_type == InterLinear) {
//		for ( y = 0; y < dst_height; y++) {
//			tempy = y * bfy;		
//			sy1 = (int32_t)tempy;
//			sy2 = sy1 + 1;
//			dy = tempy - sy1;
//			for (x = 0; x < dst_width; x++) {
//
//				if (image_type == ImageGray) {
//					tempx = x * bfx;
//
//					sx1 = (int32_t)tempx;
//					sx2 = sx1 + 1;
//			
//					dx = tempx - sx1;
//
//				//注意:向后映射出来的坐标(x,y)有可能超出了源图像的
//				//范围(0～Width, 0～Height),所以存在几种情况	
//					if ((sx1 >= src_width - 1) && (sy1 >= src_height - 1)) {	
//						//1.如果坐标超出图像的右下角(宽高均超出范围)
//						gray6 = (*(pS + sy1*src_pitch + sx1));
//					} else if (sx1 >= src_width - 1) {
//						//2.如果图像在最后一列外侧
//						gray1 = (*(pS + sy1*src_pitch + sx1));
//						gray3 = (*(pS + sy2*src_pitch + sx1));
//						gray6 = (int32_t)(gray1 * (1 - dy) + gray3 * dy);
//					} else if (sy1 >= src_height - 1) {
//						//3.如果图像在最后一行外侧
//						gray1 = (*(pS + sy1*src_pitch + sx1));
//						gray2 = (*(pS + sy1*src_pitch + sx2));
//						gray6 = (int32_t)(gray1 * (1 - dx) + gray2 * dx);	
//					} else {
//						gray1 = (*(pS + sy1*src_pitch + sx1));
//						gray2 = (*(pS + sy1*src_pitch + sx2));
//						gray3 = (*(pS + sy2*src_pitch + sx1));
//						gray4 = (*(pS + sy2*src_pitch + sx1));
//				
//						gray5 = (int32_t)(gray1 * (1 - dx) + gray2 * dx);
//						gray6 = (int32_t)(gray3 * (1 - dx) + gray4 * dx);
//
//						gray6 = (int32_t)(gray5*(1 - dy) + gray6 * dy);
//					}
//					*(pD + y*dst_pitch + x) = (uint8_t)gray6;
//
//				} else if (image_type == ImageColor) {
//					tempx = x * bfx;
//					
//					sx1 = (int32_t)tempx;
//					sx2 = sx1 + 1;
//					
//					dx = tempx - sx1;
//
//					// 对于32位真彩色需要分别计算三原色
//					for (k = 0; k < 3; k++) {
//						//注意:向后映射出来的坐标(x,y)有可能超出了源图像的
//						//范围(0～Width, 0～Height),所以存在几种情况	
//						if ((sx1 >= src_width - 1) && (sy1 >= src_height - 1)) {	
//							//1.如果坐标超出图像的右下角(宽高均超出范围)
//							gray6 = (*(pS + sy1*src_pitch + sx1*4 + k));
//						} else if (sx1 >= src_width - 1) {
//							//2.如果图像在最后一列外侧
//							gray1 = (*(pS + sy1*src_pitch + sx1*4 + k));
//							gray3 = (*(pS + sy2*src_pitch + sx1*4 + k));
//							gray6 = (int32_t)(gray1 * (1 - dy) + gray3 * dy);
//						} else if (sy1 >= src_height - 1) {
//							//3.如果图像在最后一行外侧
//							gray1 = (*(pS + sy1*src_pitch + sx1*4 + k));
//							gray2 = (*(pS + sy1*src_pitch + sx2*4 + k));
//							gray6 = (int32_t)(gray1 * (1 - dx) + gray2 * dx);	//扩大100倍
//						} else {
//							gray1 = (*(pS + sy1*src_pitch + sx1*4 + k));
//							gray2 = (*(pS + sy1*src_pitch + sx2*4 + k));
//							gray3 = (*(pS + sy2*src_pitch + sx1*4 + k));
//							gray4 = (*(pS + sy1*src_pitch + sx2*4 + k));
//					
//							gray5 = (int32_t)(gray1 * (1 - dx) + gray2 * dx);//灰度放大100倍
//							gray6 = (int32_t)(gray3 * (1 - dx) + gray4 * dx);
//
//							gray6 = (int32_t)(gray5*(1 - dy) + gray6 * dy);
//						}
//						*(pD + y * dst_pitch + x*4 + k) = (uint8_t)gray6;
//					}
//				}
//			}
//		}
//	}
//}


/******************************************************************************
  * 功能：图像数据的缩放函数(双线性插值法)--使用浮点运算,底层函数,被图像缩放函数调用
  * 参数：pDst				缩放后图像数据
  *       dst_width			缩放后图像宽度
  *		  dst_height		缩放后图像高度
  *		  dst_pitch			缩放后图像每行字节数
  *		  pSrc				缩放前图像数据
  *       src_width			缩放前图像宽度
  *		  src_height		缩放前图像高度
  *		  src_pitch			缩放前图像每行字节数
  *		  inter_type		插值方法
  *		  image_type		图像类型(8位灰度or32位彩色)
  * 返回：错误编号
  * 说明: 考虑了边界问题
  * 算法: 使用最近临插值,双线性插值实现图像的缩放
******************************************************************************/
#define SCALE 100	//去小数点放大取整倍数:取值100,10000对于缩小没问题,
						//不过图像如果放大的话会失真较严重
void SizeNormalizeV1
( 
 uint8_t *pDst, 
 const int32_t dst_width, 
 const int32_t dst_height,
 const int32_t dst_pitch,
 uint8_t *pSrc, 
 const int32_t src_width,
 const int32_t src_height,
 const int32_t src_pitch,
 Interpolation_t inter_type,
 ImageFlag_t image_type
 )
{ 
	uint8_t *pS, *pD;		//图像数据指针
	
	//目标图像坐标(x, y)
	int32_t x, y, k;
	//目标图像像素点(x,y)向后映射并扩大100倍的坐标(tempx, tempy)
	//(tempx, tempy)缩小后其最临近的4个点的横纵坐标
	int32_t tempx, tempy;
	int32_t sx1, sx2, sy1, sy2;
	
	//最临近4个点的灰度值gray1,2,3,4
	//gray5,6为按4个点权重所得的中间值
	int32_t gray1, gray2, gray3, gray4, gray5, gray6;
	
	//4个点对于计算灰度是所占的权重
	int32_t dy, dx;

	int32_t bfx = (src_width * SCALE) / dst_width;//缩放比的倒数的100倍(100倍是指SCALE,不一定就是100)
	int32_t bfy = (src_height * SCALE) / dst_height;//缩放比的倒数的100倍	

	pS = pSrc;
	pD = pDst;
	

	//通过双线性插值求尺寸归一化后目标图像(x,y)的灰度值
	//通过双线性插值求尺寸归一化后目标图像(x,y)的灰度值
	if (inter_type == InterLinear) {
		for ( y = 0; y < dst_height; y++) {
			tempy = y * bfy;	//源图像y坐标的100倍
			sy1 = tempy / SCALE;	
			sy2 = sy1 + 1;
			dy = tempy - sy1 * SCALE;//比例放大100倍

			for (x = 0; x < dst_width; x++) {

				if (image_type == ImageGray) { //8位灰度图
					tempx = x * bfx;
					sx1 = tempx / SCALE;
					sx2 = sx1 + 1;
					dx = tempx - sx1 * SCALE;//比例放大100倍

					//注意:向后映射出来的坐标(x,y)有可能超出了源图像的
					//范围(0～Width, 0～Height),所以存在几种情况
					if ((sx1 >= src_width - 1) && (sy1 >= src_height - 1)) {	
						//1.如果坐标超出图像的右下角(宽高均超出范围)
						gray6 = (*(pS + sy1*src_pitch + sx1));			
					} else if (sx1 >= src_width - 1) {
						//2.如果图像在最后一列外侧
						gray1 = (*(pS + sy1*src_pitch + sx1));
						gray3 = (*(pS + sy2*src_pitch + sx1));
						gray6 = (int32_t)(gray1 * (SCALE - dy) + gray3 * dy);	//扩大100倍
					} else if (sy1 >= src_height - 1) {
						//3.如果图像在最后一行外侧
						gray1 = (*(pS + sy1*src_pitch + sx1));
						gray2 = (*(pS + sy1*src_pitch + sx2));
						gray6 = (int32_t)(gray1 * (SCALE - dx) + gray2 * dx);	//扩大100倍
					} else {
						gray1 = (*(pS + sy1*src_pitch + sx1));
						gray2 = (*(pS + sy1*src_pitch + sx2));
						gray3 = (*(pS + sy2*src_pitch + sx1));
						gray4 = (*(pS + sy2*src_pitch + sx1));
				
						gray5 = (int32_t)(gray1 * (SCALE - dx) + gray2 * dx);
						gray6 = (int32_t)(gray3 * (SCALE - dx) + gray4 * dx);

						//gray6 = gray5 * (100 - dy) + gray6 * dy; //共放大100 * 100
						gray6 = dy * (gray6 - gray5) / SCALE + gray5; //放大100
					}
					*(pD + y*dst_pitch + x) = (uint8_t)(gray6 / SCALE);				//恢复

				} else if (image_type == ImageColor) {	//24位与32位彩色图
					tempx = x * bfx;
					sx1 = tempx / SCALE;
					sx2 = sx1 + 1;
					dx = tempx - sx1 * SCALE;//比例放大100倍

					// 对于32位真彩色需要分别计算三原色
					for (k = 0; k < 3; k++) {
						//注意:向后映射出来的坐标(x,y)有可能超出了源图像的
						//范围(0～Width, 0～Height),所以存在几种情况	
						if ((sx1 >= src_width - 1) && (sy1 >= src_height - 1)) {	
							//1.如果坐标超出图像的右下角(宽高均超出范围)
							gray6 = (*(pS + sy1*src_pitch + sx1*4 + k));
						} else if (sx1 >= src_width - 1) {
							//2.如果图像在最后一列外侧
							gray1 = (*(pS + sy1*src_pitch + sx1*4 + k));
							gray3 = (*(pS + sy2*src_pitch + sx1*4 + k));
							gray6 = (int32_t)(gray1 * (SCALE - dy) + gray3 * dy);
						} else if (sy1 >= src_height - 1) {
							//3.如果图像在最后一行外侧
							gray1 = (*(pS + sy1*src_pitch + sx1*4 + k));
							gray2 = (*(pS + sy1*src_pitch + sx2*4 + k));
							gray6 = (int32_t)(gray1 * (SCALE - dx) + gray2 * dx);	//扩大100倍
						} else {
							gray1 = (*(pS + sy1*src_pitch + sx1*4 + k));
							gray2 = (*(pS + sy1*src_pitch + sx2*4 + k));
							gray3 = (*(pS + sy2*src_pitch + sx1*4 + k));
							gray4 = (*(pS + sy1*src_pitch + sx2*4 + k));
					
							gray5 = (int32_t)(gray1 * (SCALE - dx) + gray2 * dx);//灰度放大100倍
							gray6 = (int32_t)(gray3 * (SCALE - dx) + gray4 * dx);

							gray6 = dy * (gray6 - gray5) / SCALE + gray5; //放大100
						}		
					
						gray6 /= SCALE;	//恢复
						*(pD + y * dst_pitch + x*4 + k) = (uint8_t)gray6;
					}
				}
			}
		}
	}

}

void SizeNormalizeV2
( 
 uint8_t *pDst, 
 const int32_t dst_width, 
 const int32_t dst_height,
 const int32_t dst_pitch,
 uint8_t *pSrc, 
 const int32_t src_width,
 const int32_t src_height,
 const int32_t src_pitch/*,
 Interpolation_t inter_type,
 ImageFlag_t image_type*/
 )
{ 
	uint8_t *pS, *pD;		//图像数据指针
	
	int32_t x, y;
	pS = pSrc;
	pD = pDst;
	for (y = 0; y < dst_height; y++) {
		for (x = 0; x < dst_width; x++) {
			*(pD + y * dst_pitch + x) = *(pS + 2*y*src_pitch + x*2);
		}
	}

}

/******************************************************************************
  * 功能：图像数据均衡,被图像均衡函数调用
  * 参数：pSrc		欲均衡图像数据
  *       width		图像宽度
  *		  height    图像高度
  *		  pitch		图像每行字节数
  * 返回：
******************************************************************************/
void Equalization(uint8_t *pSrc, const int32_t width, const int32_t height, const int32_t pitch)
{
	uint8_t *pS;
	int32_t i, j, temp;
	int32_t wh = width * height;
	int32_t hist[256];
	int32_t gray_map[256];	//直方图,灰度映射表
	//对直方图清0
	for (i = 0; i < 256; i++)
		hist[i] = 0;
	//生成直方图
	for (i = 0; i < height; i++) {
		pS = pSrc + pitch*i;
		for (j = 0; j < width; j++) {
			hist[*(pS+j)]++;
		}
	}

	//转换公式:D<B> = D<max> * sigma<0,x>(hist[i]) * 255 / A0 
	//(其中i为灰度级,hist[i]为第i级灰度的像素个数)
	//计算灰度映射表:gray_map[i] = sigma<0,x>(hist[i]) * 255 / A0; (A0 = width * height)
	temp = 0;
	for (i = 0; i < 256; i++) {
		temp += hist[i];
		gray_map[i] = (int32_t)(temp * 255 / wh);
	}

	for (i = 0; i < height; i++) {
		pS = pSrc + i * pitch;
		for (j = 0; j < width; j++) {
			*(pS+j) = gray_map[*(pS+j)];
		}
	}
}

//void EqualizationV1(uint8_t *pSrc, uint8_t *pSeg, const int32_t width, const int32_t height, const int32_t pitch)
//{
//	uint8_t *pS;
//	int32_t i, j, temp;
//	int32_t wh = width * height;
//	int32_t hist[256];
//	int32_t gray_map[256];	//直方图,灰度映射表
//	//对直方图清0
//	for (i = 0; i < 256; i++)
//		hist[i] = 0;
//	//生成直方图
//	for (i = 0; i < height; i++) {
//		pS = pSrc + pitch*i;
//		for (j = 0; j < width; j++) {
//			if (*(pSeg + i*pitch +j) == 255) {
//				continue;
//			}
//			hist[*(pS+j)]++;
//		}
//	}
//
//	//转换公式:D<B> = D<max> * sigma<0,x>(hist[i]) * 255 / A0 
//	//(其中i为灰度级,hist[i]为第i级灰度的像素个数)
//	//计算灰度映射表:gray_map[i] = sigma<0,x>(hist[i]) * 255 / A0; (A0 = width * height)
//	temp = 0;
//	for (i = 0; i < 256; i++) {
//		temp += hist[i];
//		gray_map[i] = (int32_t)(temp * 255 / wh);
//	}
//
//	for (i = 0; i < height; i++) {
//		pS = pSrc + i * pitch;
//		for (j = 0; j < width; j++) {
//			if (*(pSeg + i*pitch +j) == 255) {
//				continue;
//			}
//			*(pS+j) = gray_map[*(pS+j)];
//		}
//	}
//}

/******************************************************************************
  * 功能：图像的梯度及其幅值计算,输出梯度幅值数据(被图像梯度获取函数调用)
  * 参数：pDst				梯度幅值(输出)
  *		  pSrc				长宽缩小一半的图像数据(输入)
  *       width				正常图像宽度
  *		  height			正常图像高度
  *       pitch				正常图像每行字节数
  *		  size				偏导计算模版尺寸
  *		  operator_type		算子类型
  * 返回：
  * 说明: 
  * 算法: 
  *		  梯度计算,就是对(x,y)点求x,y的偏导dx,dy(可参考冈萨雷斯的数字图象处理)
  *		  dx = f(x+1,y) - f(x,y), dy = f(x, y+1) - f(x, y)
  *		  梯度幅值T(x,y) = sqrt(dx*dx + dy*dy) 近似等于|dx|+|dy|
  *		  P.S.梯度算子可以从定义到简单的Sobel算子再到复杂的Marr-Hildreth 算子
******************************************************************************/
//void GetGrads
//(
// uint8_t *pDst, 
// uint8_t *pSrc, 
// const int32_t width, 
// const int32_t height, 
// const int32_t pitch,
// const int32_t size,
// const int32_t operator_type
//)
//{
//	int32_t x, y, i, j;
//	int32_t vx, vy;		//x, y方向偏导
//	uint8_t *pS;
//	uint8_t *pD;
//	int32_t	num;
//	int32_t gradSum;
//	int32_t grad;
//	int32_t r = size / 2;
//	
//	for(y = 0; y < height; y++) {
//		for(x = 0; x < width; x++) {			
//
//			pD = pDst + y*pitch + x;
//			num = 0;
//			gradSum = 0;
//			for(i = -r; i <= r; i++) {
//				//防止越界
//				if(y+i<1 || y+i>=height-1) 
//					continue;
//				for(j = -r; j <= r; j++) {
//					if(x+j<1 || x+j>=width-1) 
//						continue;
//
//					pS = pSrc + (y+i)*(pitch) + x + j;
//
//					//使用Sobel算子求导
//					if (operator_type == SOBEL_H) {
//						//-1 0 1; -2 0 2; -1 0 1;
//						gradSum += *(pS + pitch + 1) -  *(pS + pitch - 1) +
//								   *(pS + 1)*2 - *(pS - 1)*2 +
//								   *(pS - pitch + 1) - *(pS - pitch - 1);
//					} else if (operator_type == SOBEL_V) {	
//						//-1 -2 -1; 0 0 0; 1 2 1;
//						gradSum += *(pS + pitch - 1) - *(pS - pitch - 1) +
//								   *(pS + pitch)*2 - *(pS - pitch)*2 +
//								   *(pS + pitch + 1) - *(pS - pitch + 1);
//					} else if (operator_type == SOBEL_H1) {
//						//-1 2 -1; -1 2 -1; -1 2 -1;
//						gradSum += *(pS + pitch)*2  - *(pS + pitch + 1) - *(pS + pitch - 1) +
//								   *(pS)*2 - *(pS + 1) - *(pS - 1) + 
//								   *(pS-pitch)*2 - *(pS - pitch + 1) - *(pS - pitch - 1);
//					} else if (operator_type == SOBEL_V1) {
//						//-1 -1 -1; 2 2 2; -1 -1 -1;
//						gradSum += -*(pS + pitch)  - *(pS + pitch + 1) - *(pS + pitch - 1) +
//								   *(pS)*2 + *(pS + 1)*2 + *(pS - 1)*2 + 
//								   -*(pS-pitch) - *(pS - pitch + 1) - *(pS - pitch - 1);
//					} else if (operator_type == SOBEL_HV) {
//						vx = *(pS + pitch + 1) - *(pS + pitch - 1) +
//							 *(pS + 1) - *(pS - 1) +
//							 *(pS - pitch + 1) - *(pS - pitch - 1);
//						//求y方向偏导
//						vy = *(pS + pitch - 1) - *(pS - pitch - 1) +
//							 *(pS + pitch)*2 - *(pS - pitch)*2 +
//							 *(pS + pitch + 1) - *(pS - pitch + 1);
//
//						//近似梯度幅值:sqrt(vx^2+vy^2) = |vx| + |vy|
//						gradSum += (abs(vx)+abs(vy));		
//					}
//
//					num++;							//邻域像素数目+1
//				}
//			}
//
//			if(num == 0)
//				num = 1;
//			// 求幅值，保存到pDst中，用于分割前景背景
//			grad = gradSum/num;
//			
//			if(grad > 255)
//				grad = 255;
//			if (grad < 0)
//				grad = 0;
//			
//			*pD = (uint8_t)grad;
//		}
//	}
//}


/******************************************************************************
  * 功能：图像数据的方向场计算,输出方向场数据(被图像方向场获取函数调用)
  * 参数：pGrads			梯度幅值数据(输出)
  *       pOrientation		方向图数值
  *		  pSrc				长宽缩小一半的图像数据(输入)
  *       width				正常图像宽度
  *		  height			正常图像高度
  *		  pitch				正常图像每行字节数
  *		  size				偏导计算模版尺寸
  * 返回：
  * 说明: 
  *		  1.调用HalfWidthHeight将输入的图像数据利用高斯模板提取低频信息并宽高减半
  *		  2.方向计算(调用函数GetOrientationFast(此函数只使用宽高减半后的输入图像))
******************************************************************************/
void GetGradsAndOrientationFast
(
 uint8_t *pGrads,
 uint8_t *pOrientation, 
 uint8_t *pSrc, 
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch,
 const int32_t  size
 )
{
	//int32_t  x, y, i, j;
	//int32_t  vx, vy, lvx, lvy;	//x, y方向偏导, sin(2sita), cos(2sita)
	//int32_t r = size / 2;
	//uint8_t *pS = NULL;
	//uint8_t *pG = NULL;
	//uint8_t *pOri = NULL;
	//int32_t	angle, num;
	//int32_t gradSum;
	//int32_t grad;
	//double  fAngle;
	//
	////由于计算梯度场较为费时,为提高速度,这里源图像的数据为缩小为一半后的
	////这样源图像计算出来的1个像素点应该对应目标图像的4个点
	////pSrc指向的数据只有width/2 * height/2 个,即宽高分别为width/2, height/2
	////这里x,y是目标图像数据的(输出数据的)坐标,而源图像的坐标就为x/2,y/2了
	//for(y = 0; y < height/2; y++)
	//{
	//	for(x = 0; x < width/2; x++)
	//	{
	//		//这里*2是因为源图像一点要变成目标图像的4点
	//		pOri = pOrientation + 2 * y * pitch + 2 * x;
	//		pG = pGrads + 2 * y * pitch + 2 * x;
	//		lvx = 0;
	//		lvy = 0;
	//		num = 0;
	//		gradSum = 0;
	//		for(i = -r; i <= r; i++)	// 为提高速度，步长为1
	//		{
	//			//防止越界
	//			if(y+i<1 || y+i>=height/2-1) 
	//				continue;
	//			for(j = -r; j <= r; j++)	// 为提高速度，步长为1
	//			{
	//				if(x+j<1 || x+j>=width/2-1) 
	//					continue;

	//				//使用Sobel算子求导
	//				pS = pSrc + (y+i)*(width/2) + x+j;
	//				//求x方向偏导
	//				vx = *(pS + pitch/2 + 1) - *(pS + pitch/2 - 1) +
	//					 *(pS + 1)*2 - *(pS - 1)*2 +
	//					 *(pS - pitch/2 + 1) - *(pS - pitch/2 - 1);
	//				//求y方向偏导
	//				vy = (*(pS + pitch/2 - 1) - *(pS - pitch/2 - 1) +
	//					 *(pS + pitch/2)*2 - *(pS - pitch/2)*2 +
	//					 *(pS + pitch/2 + 1) - *(pS - pitch/2 + 1));

	//				//计算梯度
	//				//近似梯度幅值:sqrt(vx^2+vy^2) = |vx| + |vy|
	//				gradSum += (abs(vx)+abs(vy));		
	//				//计算方向场
	//				//利用周围点的梯度累加作为sin(2sita),cos(2sita)
	//				lvx += vx * vy * 2;		//sin(2sita)
	//				lvy += vx*vx - vy*vy;	//cos(2sita)
	//				num++;					//邻域像素数目+1
	//			}
	//		}

	//		if(num == 0) 
	//			num = 1;

	//		// 求弧度
	//		fAngle = atan2(lvy, lvx);
	//		// 变换到(0 - 2*pi)
	//		if(fAngle < 0)	fAngle += 2.0*M_PI;
	//		
	//		// 求纹线角度
	//		fAngle = (fAngle*M_EPI*0.5 + 0.5);
	//		angle = (int32_t)fAngle;

	//		// 因为采用sobel算子，所以角度偏转了度，所以要旋转求得的角度
	//		angle -= 135;
	//		// 角度变换到(-180)
	//		if(angle <= 0)	
	//			angle += 180;
	//		
	//		angle = 180-angle;

	//		//源图像一点要变成目标图像的4点,因此让4个值都为相同的结果
	//		// 最终纹线角度
	//		*pOri = (uint8_t)angle;
	//		*(pOri + 1) = (uint8_t)angle;
	//		*(pOri + pitch) = (uint8_t)angle;
	//		*(pOri + pitch + 1) = (uint8_t)angle;

	//		// 求幅值，保存到pDst中，用于分割前景背景
	//		grad = gradSum/num;
	//		
	//		if(grad > 255)
	//			grad = 255;
	//		//源图像一点要变成目标图像的4点,因此让4个值都为相同的结果
	//		*pG = (uint8_t)grad;
	//		*(pG + 1) = (uint8_t)grad;
	//		*(pG + pitch) = (uint8_t)grad;
	//		*(pG + pitch + 1) = (uint8_t)grad;

	//	}
	//}
	int32_t  x, y, i, j;
	int32_t  vx, vy, lvx, lvy;	//x, y方向偏导, sin(2sita), cos(2sita)
	int32_t r = size / 2;
	uint8_t *pS = NULL;
	uint8_t *pG = NULL;
	uint8_t *pOri = NULL;
	int32_t	angle, num;
	int32_t gradSum;
	int32_t grad;
	double  fAngle;

	int32_t tempY = 0;
	int32_t tempPitch = pitch>>1;

	//由于计算梯度场较为费时,为提高速度,这里源图像的数据为缩小为一半后的
	//这样源图像计算出来的1个像素点应该对应目标图像的4个点
	//pSrc指向的数据只有width/2 * height/2 个,即宽高分别为width/2, height/2
	//这里x,y是目标图像数据的(输出数据的)坐标,而源图像的坐标就为x/2,y/2了
	for(y = 0; y < height/2; y++)
	{
		tempY = 2*y*pitch;
		for(x = 0; x < width/2; x++)
		{
			//这里*2是因为源图像一点要变成目标图像的4点
			//pOri = pOrientation + 2 * y * pitch + 2 * x;
			pOri = pOrientation + tempY + 2 * x;
			//pG = pGrads + 2 * y * pitch + 2 * x;
			pG = pGrads + tempY + 2*x;
			lvx = 0;
			lvy = 0;
			num = 0;
			gradSum = 0;
			for(i = -r; i <= r; i++)	// 为提高速度，步长为1
			{
				//防止越界
				if(y+i<1 || y+i>=height/2-1) 
					continue;
				for(j = -r; j <= r; j++)	// 为提高速度，步长为1
				{
					if(x+j<1 || x+j>=width/2-1) 
						continue;

					//使用Sobel算子求导
					//pS = pSrc + (y+i)*(width/2) + x+j;
					pS = pSrc + (y+i)*(tempPitch) + x+j;
					//求x方向偏导
					//vx = *(pS + pitch/2 + 1) - *(pS + pitch/2 - 1) +
					//    *(pS + 1)*2 - *(pS - 1)*2 +
					//    *(pS - pitch/2 + 1) - *(pS - pitch/2 - 1);
					vx = *(pS + tempPitch + 1) - *(pS + tempPitch - 1) +
						*(pS + 1)*2 - *(pS - 1)*2 +
						*(pS - tempPitch + 1) - *(pS - tempPitch - 1);
					//求y方向偏导
					//vy = (*(pS + pitch/2 - 1) - *(pS - pitch/2 - 1) +
					//    *(pS + pitch/2)*2 - *(pS - pitch/2)*2 +
					//    *(pS + pitch/2 + 1) - *(pS - pitch/2 + 1));
					vy = (*(pS + tempPitch - 1) - *(pS - tempPitch - 1) +
						*(pS + tempPitch)*2 - *(pS - tempPitch)*2 +
						*(pS + tempPitch + 1) - *(pS - tempPitch + 1));

					//计算梯度
					//近似梯度幅值:sqrt(vx^2+vy^2) = |vx| + |vy|
					gradSum += (abs(vx)+abs(vy));		
					//计算方向场
					//利用周围点的梯度累加作为sin(2sita),cos(2sita)
					lvx += vx * vy * 2;		//sin(2sita)
					lvy += vx*vx - vy*vy;	//cos(2sita)
					num++;					//邻域像素数目+1
				}
			}

			if(num == 0) 
				num = 1;

			// 求弧度
			fAngle = atan2(lvy, lvx);
			// 变换到(0 - 2*pi)
			if(fAngle < 0)	//fAngle += 2.0*M_PI;
				fAngle += M_PI_X2;

			// 求纹线角度
			//fAngle = (fAngle*M_EPI*0.5 + 0.5);
			fAngle = (M_EPI_2*fAngle + 0.5);
			angle = (int32_t)fAngle;

			// 因为采用sobel算子，所以角度偏转了度，所以要旋转求得的角度
			angle -= 135;
			// 角度变换到(-180)
			if(angle <= 0)	
				angle += 180;

			angle = 180-angle;

			//源图像一点要变成目标图像的4点,因此让4个值都为相同的结果
			// 最终纹线角度
			*pOri = (uint8_t)angle;
			*(pOri + 1) = (uint8_t)angle;
			*(pOri + pitch) = (uint8_t)angle;
			*(pOri + pitch + 1) = (uint8_t)angle;

			// 求幅值，保存到pDst中，用于分割前景背景
			grad = gradSum/num;

			if(grad > 255)
				grad = 255;
			//源图像一点要变成目标图像的4点,因此让4个值都为相同的结果
			*pG = (uint8_t)grad;
			*(pG + 1) = (uint8_t)grad;
			*(pG + pitch) = (uint8_t)grad;
			*(pG + pitch + 1) = (uint8_t)grad;

		}
	}
}


/******************************************************************************
  * 功能：图像固定阈值操作(包含了固定阈值二值化的两个函数的功能)
  * 参数：image         指纹图像
  *       thr_value     阈值
  *       max_value	    在某些阈值类型操作时,取得的最大值
  *       thr_type		阈值操作类型
  * 返回：错误编号
******************************************************************************/
void Threshold
(
 uint8_t *pSrc,
 const uint8_t thr_value, 
 const uint8_t max_value, 
 const int32_t thr_type,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 )
{
    int32_t n;
	uint8_t *pimg = pSrc;
	int32_t size = (width * height);
    /* 循环遍历 */
    for (n = 0; n < size; n++, pimg++) {
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
    //return ImageSetFlag(image, ImageBinarized);
}


/******************************************************************************
  * 功能：图像二值化,使用图像的总体均值作为阈值
  * 参数：pDst			二值化后图像数据
  *		  pSrc			二值化前图像数据
  *       x0			截取图像部分的开始x坐标
  *       y0			截取图像部分的开始y坐标
  *       dx			截取图像部分的宽度
  *       dy			截取图像部分的高度
  *		  dir			二值化方式
  *		  width			图像数据宽度
  *		  height		图像数据高度
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
void OverallBinary
(
 uint8_t *pDst,
 uint8_t *pSrc,
 const int32_t x0, 
 const int32_t y0, 
 const int32_t dx,
 const int32_t dy,
 const int32_t dir,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 )
{
	uint8_t *pS;
	uint8_t *pD;
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

	if ((y0 < 0) || (x0 < 0) || (dy <= 0) || (dx <= 0) || \
		(y0+dy > height) || (x0+dx) > width) {	//参数处理
		//fprintf (stderr, "bad input parameter.\n");
		//return FunBadParameter;
		return;
	}
	total = dx*dy;
	average = 0;
	for (y = y0; y < y0+dy; y++) {
		pS = pSrc + pitch*y;
		for (x = x0; x < x0+dx; x++) {
			average += *(pS + x);
		}
	}

	average /= total;
#if defined __MY_DEBUG
		fprintf(stderr,"# ImageOverall: thr_value = %d\n", average);
#endif

	for (y = y0; y < y0+dy; y++) {
		pS = pSrc + pitch*y;
		pD = pDst + pitch*y;
		for (x = x0; x < x0+dx; x++) {
			//if (dir == 0) 
			//	*(pS + x) = *(pS + x) > average ? 0 : 1;
			//else
			//*(pS + x) = *(pS + x) > average ? 1 : 0;
			//*(pS + x) =*(pS + x) > average ? upper_thr : under_thr;
			*(pD + x) = *(pS + x) > average ? upper_thr : under_thr;
		}
	}
}



/******************************************************************************
  * 功能：图像二值化,使用图像的总体均值作为阈值
  * 参数：pDst			二值化后图像数据
  *		  pSrc			二值化前图像数据
  *		  pGrads		图像梯度数据,调用函数GetGrads获得
  *       x0			截取图像部分的开始x坐标
  *       y0			截取图像部分的开始y坐标
  *       dx			截取图像部分的宽度
  *       dy			截取图像部分的高度
  *		  dir			二值化方式
  *		  width			图像数据宽度
  *		  height		图像数据高度
  * 返回：错误编号
  * 说明: 此处的二值仅指0和1,不是0和255,简单修改下就可以实现0和255的二值化
  *		  二值化化方式:
  *			dir == 1: >thr_value: 1, else: 0
  *			dir == 0: >thr_value: 0, else: 1 
  *			dir == 2: >thr_value: 0, else: 255
  *			dir == 3: >thr_value: 255, else: 0	
  *		  pGrads调用函数GetGrads获得
  * 算法描述:
  *		  计算出截取出来的图像的总体平均灰度作为阈值	
******************************************************************************/
//void OverallBinaryGrads
//(
// uint8_t *pDst,
// uint8_t *pSrc,
// uint8_t *pGrads,
// const int32_t size,
// const int32_t dir,
// const int32_t width, 
// const int32_t height, 
// const int32_t pitch
// )
//{
//	uint8_t *pS;
//	uint8_t *pD;
//	uint32_t average;
//	int32_t x, y;
//	//uint32_t total;
//	uint32_t num;
//	//dir == 1: >thr_value: 1, else: 0
//	//dir == 0: >thr_value: 0, else: 1 
//	//dir == 2: >thr_value: 0, else: 255
//	//dir == 3: >thr_value: 255, else: 0
//	uint32_t upper_thr, under_thr;
//	if (dir == 0) {
//		upper_thr = 0;
//		under_thr = 1;
//	} else if (dir == 1) {
//		upper_thr = 1;
//		under_thr = 0;
//	} else if (dir == 2) {
//		upper_thr = 0;
//		under_thr = 255;
//	} else if (dir == 3) {
//		upper_thr = 255;
//		under_thr = 0;
//	} else {
//		upper_thr = 1;
//		under_thr = 0;
//	}
//	//
//
//	//if ((y0 < 0) || (x0 < 0) || (dy <= 0) || (dx <= 0) || \
//	//	(y0+dy > height) || (x0+dx) > width) {	//参数处理
//	//	fprintf (stderr, "bad input parameter.\n");
//	//	//return FunBadParameter;
//	//}
//	//total = dx*dy;
//	average = 0;
//	num = 0;
//	//for (y = y0; y < y0+dy; y++) {
//	for (y = 0; y < height; y++) {
//		pS = pSrc + pitch*y;
//		//for (x = x0; x < x0+dx; x++) {
//		for (x = 0; x < width; x++) {
//			if (pGrads[y*pitch+x] == 255) {		//图像背景区域的梯度设置为255
//				continue;
//			}
//			if (y < size || y >= height - size ||\
//				x < size || x >= width - size) {
//				continue;
//			}
//			average += *(pS + x);
//			num++;
//		}
//	}
//
//	//average /= total;
//	average /= num;
//#if defined __MY_DEBUG
//		fprintf(stderr,"# ImageOverall: thr_value = %d\n", average);
//#endif
//
//	//for (y = y0; y < y0+dy; y++) {
//	for (y = 0; y < height; y++) {
//		pS = pSrc + pitch*y;
//		pD = pDst + pitch*y;
//		for (x = 0; x < width; x++) {
//			if (pGrads[y*pitch+x] == 255) {	//背景设置为与纹路相反的颜色
//				*(pD + x) = *(pS + x) < average ? upper_thr : under_thr;
//				continue;
//			}
//			if (y < size || y >= height - size ||\
//				x < size || x >= width - size) {
//				*(pD + x) = *(pS + x) < average ? upper_thr : under_thr;
//				continue;
//			}
//
//			*(pD + x) = *(pS + x) > average ? upper_thr : under_thr;
//		}
//	}
//}

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
void MeanBinary
( 
 uint8_t *pDst,
 uint8_t *pSrc,
 const int32_t size, 
 const int32_t dir,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 )
{
	int32_t x,y,s,p,q,a,c,c0;
	//int32_t sx, sy;
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

    s = size/2;		/* 大小 */
    a = size*size;	/* 面积 */    

	for (y = 0; y < height; y++)
    for (x = 0; x < width; x++)
    {
		c = 0;
		//sx = x - s;
		//sy = y - s;
		if (y < s || y >= height-s ||\
			x < s || x >= width-s) {
			pDst[pitch*y + x] = 0;
			continue;
		} 

		//优化后
		for (q = y-s; q <= y+s; q++)
		for (p = x-s; p <= x+s; p++)
		{
			c += pSrc[p+q*pitch];
		}

		c0 = pDst[x+y*pitch]*a;
		pDst[x + y*pitch]= c0 > c ? upper_thr : under_thr;

    }
    
}
/******************************************************************************
  * 功能：图像数据统计滤波操作，通过计算均值实现
  * 参数：pDst			处理后图像数据
  *		  pSrc			处理前图像数据
  *       size			滤波器模版大小(2*r+1)
  *       thre_val		阈值
  *		  dir			二值化方式
  *		  width			图像数据宽度
  *		  height		图像数据高度
  *		  pitch			图像数据每行字节数
  * 返回：错误编号
  * 说明: 此处的二值仅指0和1,不是0和255,简单修改下就可以实现0和255的二值化
  *		  二值化化方式:
  *			dir == 1: >thr_value: 1, else: 0
  *			dir == 0: >thr_value: 0, else: 1 
  *			dir == 2: >thr_value: 0, else: 255
  *			dir == 3: >thr_value: 255, else: 0	
  *       边界影响,经过这个函数处理后的图像实际上被裁剪去了size行和size列
******************************************************************************/
void StatisticsFilter
( 
 uint8_t *pDst,
 uint8_t *pSrc, 
 const int32_t size, 
 const int32_t thre_val, 
 const int32_t dir,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 )
{
    int32_t x,y,s,p,q,c;
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

    s = size/2;		/* 大小 */ 
   
    /* 拷贝图像进行计算 */
    
    for (y = s; y < height-s; y++)
    for (x = s; x < width-s; x++)
    {
		c = 0;

		for (q = y-s; q <= y+s; q++)
		for (p = x-s; p <= x+s; p++)
		{
			c += pSrc[p+q*pitch];
		}

		//if (dir == 0)
		//	p1[x+y*pitch] = c>=thre_val?0:1;	//这里修改为255:0就可以实现黑白二值化
		//else 
		//	p1[x+y*pitch] = c>=thre_val?1:0;	//这里修改为255:0就可以实现黑白二值化
		pDst[x+y*pitch] = c>= thre_val?upper_thr:under_thr;

    }
    
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
  * 功能：图像膨胀通用算法
  * 参数：pDst			二值化后图像数据
  *		  pSrc			二值化前图像数据
  *       size			结构元素尺寸(规定长宽相同为size)
  *       tmpltA		结构元素
  *       tmpltSum		结构元素之和
  *		  width			图像数据宽度
  *		  height		图像数据高度
  *		  pitch			图像数据每行字节数
  * 返回：错误编号
  * 说明: 输入图像为(0,1)二值图像,输出图像也为(0,1)二值图像
  * 算法：
  *          膨胀算法的细节：
  *          用上面这个模板在原图像上滑动，当模板中心点对应的原图像上的点为1时，
  *          则用模板上的元素与与之重合的点进行与操作(中心点除外)，与操作的结果
  *          不完全为0时，则用模板对原图像进行或操作。但是或操作对应的结果若为1
  *          则标记起来。扫描完整幅图像后将标记的点置1，就完成了一次膨胀操作。
******************************************************************************/
void UniDilateOZ
(
 uint8_t *pDst,
 uint8_t *pSrc,
 const int32_t size, 
 int32_t *tmpltA,
 const int32_t tmpltSum,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 )
{
	int32_t i, j, k, x, y;
	int32_t temp = 0;
	int32_t r = size / 2;

	for (y = r; y < height - r; y++) {
		for (x = r; x < width - r; x++) {
			if (pSrc[y*pitch+x] == 0)
				continue;
			temp = 0;
			k = 0;
			for (j = y-r; j <= y+r; j++) {
				for (i = x-r; i <= x+r; i++) {
					if (tmpltA[k++] == 1)
						temp += pSrc[j*pitch+i];//P2(i, j);
				}
			} 
			k = 0;
			if (temp <= 1) {
				pDst[y*pitch+x] = 0;//P(x, y) = 0;//continue;
			} else {
				for (j = y-r; j <= y+r; j++) {
					for (i = x-r; i <= x+r; i++) {
						if (tmpltA[k++] == 1) {
							//P(i, j) = 1;
							pDst[j*pitch+i] = 1;
						}
					}
				} 
			}
		}
	}

}



/******************************************************************************
  * 功能：图像腐蚀通用算法
  * 参数：pDst			处理后图像数据
  *		  pSrc			处理前图像数据
  *       size			结构元素尺寸(规定长宽相同为size)
  *       tmpltA		结构元素
  *       tmpltSum		结构元素之和
  *		  width			图像数据宽度
  *		  height		图像数据高度
  *		  pitch			图像数据每行字节数
  * 返回：错误编号
  * 说明: 输入图像为(0,1)二值图像,输出图像也为(0,1)二值图像
  * 算法:   
  *          腐蚀操作细节： 
  *          用上面这个模板在原图像上滑动，当模板中心点对应的原图像上的点为1时，
  *          则用模板上的元素与与之重合的点进行与操作(中心点除外)，与操作的结果
  *          不完全为"1"时就将模板中心对应的原图像的点进行标记为可删除。若与操作
  *          结果全部为"1"时就将模板中心的对应原图像的点保留为"1".
******************************************************************************/
void UniErodeOZ
(
 uint8_t *pDst,
 uint8_t *pSrc,
 const int32_t size, 
 int32_t *tmpltA,
 const int32_t tmpltSum,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 )
{
	int32_t i, j, k, x, y;
	int32_t temp = 0;
	int32_t r = size / 2;

	for (y = r; y < height - r; y++) {
		for (x = r; x < width - r; x++) {
			if (pSrc[y*pitch+x] == 0)
				continue;

			temp = 0;
			k = 0;
			for (j = y-r; j <= y+r; j++) {
				for (i = x-r; i <= x+r; i++) {
					if (tmpltA[k++] == 1)
						temp += pSrc[j*pitch+i];//P2(i, j);
				}
			} 

			if (temp != tmpltSum) { 
				pDst[y*pitch+x] = 0;//P(x, y) = 0;//continue;
			} else {
			    //P(x, y) = 1;
				pDst[y*pitch+x] = 1;
			}
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
  *		    得到pOrient(调用GetOrientationFast获得)
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
	//纹线方向上的7个点的权值
	int32_t Hw[7] = {2, 2, 3, 4, 3, 2, 2};
	//纹线方向的垂直方向上的7个点的权值
	int32_t Vw[7] = {1, 1, 1, 1, 1, 1, 1};

	int32_t Hv = 0;		// 纹线方向上的7个点的加权平均值
	int32_t Vv = 0;		// 纹线方向的垂直方向上的7个点的加权平均值
	int32_t tempY = 0;
	uint8_t *pS;		// 指纹图像像素点指针
	//uint8_t *pT;		//pFPTemp指针
	uint8_t *pOri;	//纹线方向指针
	//uint8_t pFPTemp[FP_HEIGHT*FP_WIDTH];
	uint8_t *pFPTemp = fp_src_copy.pimg;
	//uint8_t *pFPTemp;	//临时数据缓存区
	//uint32_t under_thr = 0;
	//uint32_t upper_thr = 1;

	//某点周围8个点的地址偏移
	//int32_t	SiteD8[8] = {pitch-1, pitch, pitch+1, 1, -pitch+1, -pitch, -pitch-1, -1};
	int32_t SiteD8[8];

	int32_t exit = 1;
	int32_t n = 0;
	int32_t num = 0;
	
	//dir == 1: >thr_value: 1, else: 0
	//dir == 0: >thr_value: 0, else: 1 
	//dir == 2: >thr_value: 0, else: 255
	//dir == 3: >thr_value: 255, else: 0
	uint32_t upper_thr, under_thr;
	
	SiteD8[0] = pitch-1;	SiteD8[1] = pitch;		SiteD8[2] = pitch+1;
	SiteD8[3] = 1;			SiteD8[4] = 1-pitch;	SiteD8[5] = -pitch;
	SiteD8[6] = -pitch-1;	SiteD8[7] = -1;

	
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
	
	//pFPTemp = (uint8_t *)malloc(sizeof(uint8_t)*width*height);

	//if (pFPTemp == NULL)
	//	return;

	tempY = 0;
	for(y = 0; y < height; y++) {
		//优化前
		//tempY = y*pitch;	
		for(x = 0; x < width; x++) {
			pOri = pOrientation + tempY + x;
			pS = pSrc + tempY + x;			
			//如果该点非常黑，则在临时缓冲区内置该点为黑点，值为0
			if(*pS < 4) {
				*(pFPTemp + tempY + x) = 0;
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
				//*(pFPTemp + tempY + x) = 0;
				*(pFPTemp + tempY + x) = under_thr;
			} else {
				// 纹线方向上加权平均值较大则置当前点为白点
				//*(pFPTemp + tempY + x) = 255;
				*(pFPTemp + tempY + x) = upper_thr;
			}
		}
		//优化后
		tempY += pitch;
	}

	//将临时缓冲区内数据拷贝到原始图像数据缓冲区,注释掉这一句,这样pFPTemp
	//就作为下面对二值化指纹图像进行去噪的源数据了
	//memcpy(pSrc, pFPTemp, sizeof(uint8_t)*width*height);

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
				//pT = pFPTemp + tempY + x;
				for(i = 0; i < 8; i++) {
					//if(*(pS+SiteD8[i]) == *pS) {
					//if(*(pT+SiteD8[i]) == *pT) {
					if (*(pFPTemp + tempY + x + SiteD8[i]) == *(pFPTemp + tempY + x)) {
						num++;
					}
				}
				
				if(num < 2) {
					//相同点个数小于二则改变当前点类型(0-->0,255-->1)
					//*(pFPTemp+temp+x) = 255 - *pS;
					//*(pSrc + tempY + x) = 255 - *pT;
					if ((*(pFPTemp+tempY+x)) == under_thr)
						*(pSrc + tempY + x) = upper_thr;
					else
						*(pSrc + tempY + x) = under_thr;
					exit = 1;
				} else {	//否则不改变(0-->0,255-->1)
					//*(pFPTemp+temp+x) = *pS;
					if ((*(pFPTemp+tempY+x)) == under_thr)
						*(pSrc + tempY + x) = under_thr;
					else
						*(pSrc + tempY + x) = upper_thr;
				}

			}
			//优化后
			tempY += pitch;
		}
	}

	//if (pFPTemp != NULL) {
	//	free(pFPTemp);
	//	pFPTemp = NULL;
	//}

}




