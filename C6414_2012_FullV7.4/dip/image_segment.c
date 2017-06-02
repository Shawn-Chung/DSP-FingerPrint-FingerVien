/******************************************************************************
 * 文件名：image_segment.c
 * 功能：  一些图像的分割算法
 * 说明:   
        函数名字的解释:
		    前缀:Image    (表示函数对一般图像都是比较通用的)    (image)
			     FP       (表示函数对指纹图像比较适用)          (fp)
				 FV       (表示函数对静脉图像比较使用)          (fv)
			后缀:	 
				 LL       (表示函数为底层函数,被上层函数调用)   (ll,lowlevel)
				 V?       (表示函数的升级版本)                  (Ver?,ver?)
				 A?       (表示同样功能不同方法的函数)          (Alt?,alt?)
				 W?       (表示同样功能不同方法的函数)          (Way?,way?)
				 OZ       (表示函数的输入或输出的图像数据为1(One),0(Zero)的二值)
******************************************************************************/

#include "dip_header/image_segment.h"
//#include "../../bsp/bsp_header/z_mytype.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//#include "image_base.h"
//#include "image_enhance_filter.h"


//FunError_t GradsRSegment
//(
// uint8_t *pSrc,  
// uint8_t *pGrads, 
// const int32_t size, 
// const int32_t step, 
// const int32_t threshold, 
// const int32_t width, 
// const int32_t height, 
// const int32_t pitch
//)
//{
//	int32_t	x, y, i, j, k;
//	int32_t r = size / 2;
//	int32_t num = 0;
//	int32_t tempY;
//	int32_t min_x, max_x;
//	int32_t mem_size = width*height;
//	int32_t threshold1, sum, max_sum, min_max, pos, max_pos, min_pos;
//	int32_t max_d[2], pos_d[2];
//	threshold1 = 0;
//#define MASK_W		10
//#define MASK_H		50
//	max_sum = 0;
//	min_max = 0;
//	sum = 0;
//	pos = 0;
//	max_pos = 0;
//	min_pos = 255;
//	//for (i = width-1; i > MASK_W; i--) {
//	//	sum = 0;
//	//	for (j = height - 1; j > height - 1 - MASK_H; j--) {
//	//		for (k = 0; k < MASK_W; k++) {
//	//			sum += pGrads[j*pitch + i - k];
//	//		}
//	//	}
//	//	if (sum > max_sum) {
//	//		max_sum = sum;
//	//		pos = i;
//	//		//if (pos > max_pos) {
//	//		//	max_pos = pos;
//	//		//}
//	//		//if (pos < min_pos) {
//	//		//	min_pos = pos;
//	//		//}
//	//	}
//	//}
//	//max_d[0] = 0;
//	//pos_d[0] = 0;
//	//for (i = 2; i < width - 1; i++) {
//	//	sum = pGrads[i+1]+pGrads[i]-pGrads[i-1]-pGrads[i-2];
//	//	if (max_d[0] < sum) {
//	//		for (k = 5; k >= 1; k--) {
//	//			max_d[k] = max_d[k-1];
//	//			pos_d[k] = pos_d[k-1];
//	//		}
//	//		//max_d[1] = max_d[0];
//	//		//pos_d[1] = pos_d[0];
//	//		max_d[0] = sum;
//	//		pos_d[0] = i;
//	//	}
//	//}
//
//	//threshold1 = min_max / (3);
//	//min_pos = pos_d[0];
//	//max_pos = pos_d[0];
//	//for (k = 1; k <= 5; k++) {
//	//	if (pos_d[k]>max_pos) {
//	//		max_pos = pos_d[k];
//	//	}
//	//	if (pos_d[k]<min_pos) {
//	//		min_pos = pos_d[k];
//	//	}
//	//}
//	////if (pos_d[0] > pos_d[1]) {
//	////	min_pos = pos_d[1];
//	////	max_pos = pos_d[0];
//	////} else {
//	////	min_pos = pos_d[0];
//	////	max_pos = pos_d[1];
//	////}
//	//min_x = 255;
//	//max_x = 0;
//
//	tempY = 0;
//	for (y = 0; y < height; y++) {
//		//for (x = 0; x < width; x++) {
//		for (x = 0;  x < width; x++) {
//			//if (x < min_pos || x > max_pos) {
//			//	*(pGrads + y*pitch + x) = 255;
//			if(*(pGrads + y*pitch + x) < threshold) {
//				*(pGrads + y*pitch + x) = 255;			//背景设为白色
//				//if (min_x > x) {
//				//	min_x = x;
//				//}
//			} else {
//				break;//continue;
//			}
//		}
//		for (x = width-1; x >= 0; x--) {
//			if (*(pGrads+y*pitch+x) < threshold) {
//				*(pGrads + y*pitch + x) = 255;			//背景设为白色
//			} else {
//				break;//continue;
//			}
//		}
//		tempY += pitch;
//	}
//
//
//	// 如果前景区域面积小于总面积的5分之一，则表示前景区域太小，返回错误
//	//if(num < height * width/5)
//	//	return FunFailure;
//
//	////清除背景
//	tempY = 0;
//	for(y = 0; y < height; y++) {
//		//优化前:
//		//tempY = y * pitch;
//		for(x = 0; x < width; x++) {	
//			// 如果是背景区域，则置该点灰度和方向场为白点
//			if (x < 15 || x > width - 15 || y < 20) {
//				*(pSrc + tempY + x) = 0;
//				//continue;
//			}
//			//if(*(pGrads + tempY + x) == 255) {
//			//	*(pSrc + tempY + x) = 0;					//边缘点设为背景(白色)	
//			//}
//		}
//		//优化后
//		tempY += pitch;
//	}
//	return FunOK;
//
//}

//#define MASK_H		20
//#define MASK_W		4
////静脉粗分割
//void FVRSegment
//(
// uint8_t *pDst,
// uint8_t *pSrc,
// const int32_t width, 
// const int32_t height, 
// const int32_t pitch
// )
//{
//	int32_t x_pos_y_l[FV_HEIGHT];
//	int32_t x_pos_y_r[FV_HEIGHT];
//	int32_t y_min, y_max;
//	int32_t max_value = 0;
//	int32_t max_value_l, max_value_r;
//	int32_t x_pos_l, x_pos_r;
//	int32_t sum;
//	int32_t i, j, k;
//	int32_t tempJ;
//	uint8_t *pS, *pD;
//
//	for (i = 0; i < FV_HEIGHT; i++) {
//		x_pos_y_l[i] = 0;
//		x_pos_y_r[i] = 0;
//	}
//	
//	//找出上边界y_min
//	tempJ = 0; 
//	max_value = 0;
//	y_min = 0;
//	for (j = 0; j < height / 2; j++) {
//		pS = pSrc + tempJ;
//		sum = 0;
//		for (i = 0; i < width; i++) {
//			sum += *(pS + pitch*3 + i) + *(pS + pitch*2 + i) - 
//				   *(pS + pitch   + i) - *(pS +           i);  
//		}
//		if (sum > max_value) {
//			max_value = sum;
//			y_min = j+3;
//		}
//		
//		tempJ += pitch;
//	}
//
//	//找出下边界y_max
//	//tempJ = (height/2)*pitch; 
//	//max_value = 0;
//	//y_max = 0;
//	//for (j = height/2; j < height-3; j++) {
//	//	pS = pSrc + tempJ;
//	//	sum = 0;
//	//	for (i = 0; i < width; i++) {
//	//		sum += *(pS + pitch   + i) + *(pS +           i) - 
//	//			   *(pS + pitch*3 + i) - *(pS + pitch*2 + i);  
//	//	}
//	//	if (sum > max_value) {
//	//		max_value = sum;
//	//		y_max = j;
//	//	}
//	//	
//	//	tempJ += pitch;
//	//}
//	y_max = height - 1;
//
//	tempJ = y_min * pitch;
//	for (j = y_min; ((j <= y_max - MASK_H)); j++) {
//		pS = pSrc + tempJ;
//		max_value_l = 0;
//		max_value_r = 0;
//		for (i = 0; i <= width - MASK_W; i++) {
//			sum = 0;
//			for (k = 0; k < MASK_H; k++) {
//				sum += *(pS+k*pitch+i+2) + *(pS+k*pitch+i+3) - 
//					   *(pS+k*pitch+i  ) - *(pS+k*pitch+i+1) ;
//			}
//			if (sum > max_value_l) {
//				if (i < width/2) {
//					max_value_l = sum;
//					x_pos_l = i;//i+3;
//				}
//			}
//			if (sum < max_value_r) {
//				if (i > width/2) {
//					max_value_r = sum;
//					x_pos_r = i+3;//i;
//				}
//			}
//		}
//		x_pos_y_l[j] = x_pos_l;
//		x_pos_y_r[j] = x_pos_r;
//
//		tempJ += pitch;
//	}
//
//
//	//得出分割区域(背景255,前景0);
//#if 0
//	//每行的左右边界互不相同
//	tempJ = 0; 
//	for (j = 0; j < height; j++) {
//		pS = pDst + tempJ;
//		if (j < y_min || j > y_max) {		//上下边界外的背景设为255
//			for (i = 0; i < width; i++) {
//				*(pS + i) = 255;
//			}
//		} else if (j <= height - MASK_H) {	//左右边界外的背景设为255
//			for (i = 0; i < width; i++) {
//				if ((i < x_pos_y_l[j]) || (i > x_pos_y_r[j])) {
//					*(pS + i) = 255;
//				} 
//			}
//		} else if (j >= height - MASK_H) {	//左右边界外的背景设为255
//			for (i = 0; i < width; i++) {
//				if ((i < x_pos_y_l[height - MASK_H])|| \
//					(i > x_pos_y_r[height - MASK_H])) {
//					*(pS + i) = 255;
//				} 
//			}
//		}
//
//		tempJ += pitch;
//	}
//#endif
//
//	//每行的左右边界:所有左右边界中的最大和最小值
//	//max_value_l = x_pos_y_l[y_min];
//	//max_value_r = x_pos_y_r[y_min];
//	//for (j = y_min; j <= y_max - MASK_H; j++) {
//	//	if (x_pos_y_l[j] > max_value_l) {
//	//		max_value_l = x_pos_y_l[j];
//	//	}
//	//	if (x_pos_y_r[j] < max_value_l) {
//	//		max_value_r = x_pos_y_r[j];
//	//	}
//	//}
//	
//	//每行的左右边界:求均值
//	max_value_l = 0;
//	max_value_r = 0;
//	for (j = y_min; j <= y_max - MASK_H; j++) {
//		max_value_l += x_pos_y_l[j];
//		max_value_r += x_pos_y_r[j];
//	}
//	max_value_l /= (y_max-MASK_H-y_min+1);
//	max_value_r /= (y_max-MASK_H-y_min+1);
//
//
//	tempJ = 0; 
//	for (j = 0; j < height; j++) {
//		pD = pDst + tempJ;
//		pS = pSrc + tempJ;
//		if (j < y_min || j > y_max) {		//上下边界外的背景设为255
//			for (i = 0; i < width; i++) {
//				*(pD + i) = 255;
//				*(pS + i) = 0;
//			}
//		} else {							
//			for (i = 0; i < width; i++) {	//左右边界外的背景设为255
//				if ((i < max_value_l) || (i > max_value_r)) {
//					*(pD + i) = 255;
//					*(pS + i) = 0;
//				} else {
//					*(pD + i) = 0;			//前景设为0
//				}
//			}
//		}
//
//		tempJ += pitch;
//	}
//
//}



/******************************************************************************
  * 功能：求取图像的曲率,并进行灰度延伸作为新的图像数据
  * 参数：pDst			处理后图像数据
  *		  pSrc			处理前图像数据
  *		  cur_type		所求曲率类型
  *		  size			计算导数时用到的像素尺寸(导数计算使用像素点)
  *		  thr_type	    对求的的曲率进行灰度延伸时的方法
  *		  width			图像数据宽度
  *		  height		图像数据高度
  *		  pitch			图像数据每行字节数
  * 返回：错误编号
  * 说明: 经过函数的处理,图像数据不在是原来的数据,而是曲率进行灰度延伸后的一副
  *		  新图像.
  *		  边界影响,经过这个函数处理后的图像实际上被裁剪去了2*size行和2*size列
  * 算法: 
  *		  1.根据曲率公式,计算每一点的曲率
  *		  2.适当的确定灰度延时的公式,如:
  *		    NewGray(x, y) = (H(x,y) - Hmin) * 256 / (Hmax-Hmin)
  *			其中NewGray(x,y),H(x,y),Hmin,Hmax分别表示(x,y)这点新的灰度值,
  *			这点的曲率,整幅图像算出的所有曲率中的最小,最大值
  * 文献:
  *		  1 - A finger-vein verification system using mean curvature:
  *		      Wonseok Song...
  *			  Pattern Recognition Letters 32 (2011) 1541–1547
  *       2 - Finger vein extraction using gradient normalization and 
  *			  principal curvature:
  *			  Joon Hwan Choi...
******************************************************************************/
void CurvatureSegment
(
 uint8_t *pDst,
 uint8_t *pSrc,
 int32_t cur_type, 
 int32_t size, 
 int32_t thr_type,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 )
{
	int32_t x, y;
	int32_t temp;
	double fx, fy, fxx, fxy, fyy, f2x, f2y;

	int32_t r = size / 2;
	double size1 = 1.0 / (double)size;	//先计算倒数,将除法变成乘法
	//int32_t width, height, pitch;
	//int32_t width = ImageGetWidth(image);
	//int32_t height = ImageGetHeight(image);
	//int32_t pitch = ImageGetPitch(image);
	//uint8_t *pDst = ImageGetBuffer(image);
 
	//unsigned char *pSrc;
	unsigned char *pS;
 
	int32_t tempD;
	int32_t i;
	double min_cur, max_cur;		//计算出来的曲率的最大,最小值
	double hn, hd;	//分子, 分母
	double H, H1, H2;
	//double *cur_value = (double *)malloc(sizeof(double)*width*height);	//每点曲率值缓存区


	//循环计算每点曲率值,并存储到cur_value中
	//for (y = size; y < height - size; y++) {
	for (y = 0; y < height; y++) {
		temp = pitch * y;
		//for (x = size; x < width - size; x++) {
		for (x = 0; x < width; x++) {
			if (y < size || y >= height - size ||\
				x < size || x >= width - size) {
				*(cur_value + temp + x) = 0.0;
				continue;
			}
			//if (y < 30 || x < 25 || x > width - 25) {
			//	*(cur_value + temp + x) = 0.0;
			//	continue;
			//}
			pS = pSrc + temp + x;

			//计算一阶,二阶导数
			fx  = (*(pS - r) - *(pS + r)) * (size1);
			fy  = (*(pS - pitch * r) - *(pS + pitch * r)) * (size1);
			fxx = ((*pS + *pS - *(pS + size) - *(pS - size)) * (size1));
			fyy = ((*pS + *pS - *(pS + pitch * size) - *(pS - pitch * size)) * (size1));
			fxy = ((*(pS - pitch * r + r) + *(pS + pitch * r - r))-(*(pS - pitch * r - r) + *(pS + pitch * r + r)));
			fxy = fxy*size1;
		  
			f2x = fx * fx;
			f2y = fy * fy;

			//平均曲率
			if (cur_type == CUR_MEAN) {
				hn  = ((1.0+f2x)*fyy + (1.0+f2y)*fxx - 2.0*fx*fy*fxy)*0.5;
				hd  = (1.0+f2x+f2y)*sqrt((double)(1.0+f2x+f2y));
				if (hd != 0)
					H = (hn / hd);
				else
					H = 0;
			}

			//主曲率1, 2
			if (cur_type == CUR_PRI1 || cur_type == CUR_PRI2) {
				//平均曲率
				hn  = ((1.0+f2x)*fyy + (1.0+f2y)*fxx - 2.0*fx*fy*fxy)*0.5;
				hd  = (1.0+f2x+f2y)*sqrt((double)(1.0+f2x+f2y));
				if (hd != 0)
					H1 = (hn / hd);
				else
					H1 = 0;

				//高斯曲率
				hn = fxx * fyy - fxy*fxy;
				hd = (1.0 + f2x + f2y) * (1.0 + f2x + f2y);
				if (hd != 0)
					H2 = (hn / hd);
				else
					H2 = 0;

				if (cur_type == CUR_PRI1)
					H = H1 + sqrt((double)(H1*H1 - H2));
				else
					H = H1 - sqrt((double)(H1*H1 - H2));
			}

			//高斯曲率
			if (cur_type == CUR_GAUS) {
				hn = fxx * fyy - fxy*fxy;
				hd = (1.0 + f2x + f2y) * (1.0 + f2x + f2y);
				if (hd != 0)
					H = (hn / hd);
				else
					H = 0;
			}

			//倾向曲率
			if (cur_type == CUR_TEND) {
				hn  = (fxx*f2x + fyy*f2y + 2.0*fx*fy*fxy);
				hd  = (f2x+f2y)*(1.0+f2x+f2y)*sqrt((double)(1.0+f2x+f2y));
				if (hd != 0)
					H = (hn / hd);
				else
					H = 0;
			}

			//走向曲率
			if (cur_type == CUR_STRI) {
				hn  = (fxx*f2y + fyy*f2x - 2.0*fx*fy*fxy);
				hd  = (f2x+f2y)*sqrt((double)(1.0+f2x+f2y));
				if (hd != 0)
					H = (hn / hd);
				else
					H = 0;
			}

			//Kmax,Kmin
			if (cur_type == CUR_MAX || cur_type == CUR_MIN) {
				hn  = (fxx + fyy) * 0.5;
				hd  = sqrt((double)((fxx-fyy)*(fxx-fyy)*0.25 + fxy*fxy));
				if (cur_type == CUR_MAX)
					H = hn + hd;
				else
					H = hn - hd;
			}

			*(cur_value + temp + x) = (H);	//存储每点曲率值
		}
	}

	//获取所有点曲率的最大,最小曲率
	min_cur = 0;	
	max_cur = 0;

	//直接求最大最小值作为曲率的范围
	if (thr_type == 0) {
		for (i = 0; i < width * height; i++) {
			if (cur_value[i] < min_cur) {
				min_cur = cur_value[i];
			}
			if (cur_value[i] > max_cur) {
				max_cur = cur_value[i];
			}
		}
	}

	//灰度变换根据曲率的范围直接映射到0-255
	//if (thr_type == 0 || thr_type == 1) {
		for (y = 0; y < height; y++) {
			temp = pitch * y;
			for (x = 0; x < width; x++) {
				if (y < size || y >= height - size ||\
					x < size || x >= width - size) {
					*(pDst + temp + x ) = 0;
					continue;
				}
				if (thr_type == 1 || thr_type == 0) {
					if (cur_value[temp + x] <= min_cur) {
						tempD = 0;
					} 
					else if (cur_value[temp + x] >= max_cur) {
						tempD = 255;
					} 
					else if ((cur_value[temp+x] <= min_cur/15.0)) {
						if (cur_value[temp+x] <= min_cur/2.0)
							tempD = 0;
						else
							tempD = (int32_t)((cur_value[temp+x]+cur_value[temp+x]-min_cur)*256.0/(max_cur-min_cur));
					}
					else {
						tempD = (int32_t)((cur_value[temp + x]*2.0-min_cur) * 256.0 / (max_cur-min_cur));
					}
				}

				if (tempD < 0)
					tempD = 0;
				if (tempD > 255)
					tempD = 255;
				*(pDst + temp + x) = tempD;
			}
		}
	//}

	////释放
	//if (cur_value != NULL) {
	//	free(cur_value);
	//	cur_value = NULL;
	//}

}

//void CurvatureSegmentV1
//(
// uint8_t *pDst,
// uint8_t *pSrc,
// uint8_t *pSeg,
// int32_t cur_type, 
// int32_t size, 
// int32_t thr_type,
// const int32_t width, 
// const int32_t height, 
// const int32_t pitch
// )
//{
//	int32_t x, y;
//	int32_t temp;
//	double fx, fy, fxx, fxy, fyy, f2x, f2y;
//
//	int32_t r = size / 2;
//	double size1 = 1.0 / (double)size;	//先计算倒数,将除法变成乘法
//
//	unsigned char *pS;
// 
//	int32_t tempD;
//	int32_t i;
//	double min_cur, max_cur;		//计算出来的曲率的最大,最小值
//	double hn, hd;	//分子, 分母
//	double H, H1, H2;
//	//double *cur_value = (double *)malloc(sizeof(double)*width*height);	//每点曲率值缓存区
//
//
//	//循环计算每点曲率值,并存储到cur_value中
//	for (y = 0; y < height; y++) {
//		temp = pitch * y;
//		for (x = 0; x < width; x++) {
//			if (y < size || y >= height - size ||\
//				x < size || x >= width - size) {
//				*(cur_value + temp + x) = 0.0;
//				continue;
//			}
//			if (*(pSeg + temp + x) == 255) {
//				*(cur_value + temp + x) = 0.0;
//				continue;
//			}
//			pS = pSrc + temp + x;
//
//			//计算一阶,二阶导数
//			fx  = (*(pS - r) - *(pS + r)) * (size1);
//			fy  = (*(pS - pitch * r) - *(pS + pitch * r)) * (size1);
//			fxx = ((*pS + *pS - *(pS + size) - *(pS - size)) * (size1));
//			fyy = ((*pS + *pS - *(pS + pitch * size) - *(pS - pitch * size)) * (size1));
//			fxy = ((*(pS - pitch * r + r) + *(pS + pitch * r - r))-(*(pS - pitch * r - r) + *(pS + pitch * r + r)));
//			fxy = fxy*size1;
//		  
//			f2x = fx * fx;
//			f2y = fy * fy;
//
//			//平均曲率
//			if (cur_type == CUR_MEAN) {
//				hn  = ((1.0+f2x)*fyy + (1.0+f2y)*fxx - 2.0*fx*fy*fxy)*0.5;
//				hd  = (1.0+f2x+f2y)*sqrt((double)(1.0+f2x+f2y));
//				if (hd != 0)
//					H = (hn / hd);
//				else
//					H = 0;
//			}
//
//			//主曲率1, 2
//			if (cur_type == CUR_PRI1 || cur_type == CUR_PRI2) {
//				//平均曲率
//				hn  = ((1.0+f2x)*fyy + (1.0+f2y)*fxx - 2.0*fx*fy*fxy)*0.5;
//				hd  = (1.0+f2x+f2y)*sqrt((double)(1.0+f2x+f2y));
//				if (hd != 0)
//					H1 = (hn / hd);
//				else
//					H1 = 0;
//
//				//高斯曲率
//				hn = fxx * fyy - fxy*fxy;
//				hd = (1.0 + f2x + f2y) * (1.0 + f2x + f2y);
//				if (hd != 0)
//					H2 = (hn / hd);
//				else
//					H2 = 0;
//
//				if (cur_type == CUR_PRI1)
//					H = H1 + sqrt((double)(H1*H1 - H2));
//				else
//					H = H1 - sqrt((double)(H1*H1 - H2));
//			}
//
//			//高斯曲率
//			if (cur_type == CUR_GAUS) {
//				hn = fxx * fyy - fxy*fxy;
//				hd = (1.0 + f2x + f2y) * (1.0 + f2x + f2y);
//				if (hd != 0)
//					H = (hn / hd);
//				else
//					H = 0;
//			}
//
//			*(cur_value + temp + x) = (H);	//存储每点曲率值
//		}
//	}
//
//	//获取所有点曲率的最大,最小曲率
//	min_cur = 0;	
//	max_cur = 0;
//
//	//直接求最大最小值作为曲率的范围
//	if (thr_type == 0) {
//		for (i = 0; i < width * height; i++) {
//			if (cur_value[i] < min_cur) {
//				min_cur = cur_value[i];
//			}
//			if (cur_value[i] > max_cur) {
//				max_cur = cur_value[i];
//			}
//		}
//	}
//
//	//灰度变换根据曲率的范围直接映射到0-255
//	//if (thr_type == 0 || thr_type == 1) {
//		for (y = 0; y < height; y++) {
//			temp = pitch * y;
//			for (x = 0; x < width; x++) {
//				if (y < size || y >= height - size ||\
//					x < size || x >= width - size) {
//					*(pDst + temp + x ) = 0;
//					continue;
//				}
//				if (*(pSeg + temp + x) == 255) {
//					*(pDst + temp + x ) = 0;
//					continue;
//				}
//
//				if (thr_type == 1 || thr_type == 0) {
//					if (cur_value[temp + x] <= min_cur) {
//						tempD = 0;
//					} 
//					else if (cur_value[temp + x] >= max_cur) {
//						tempD = 255;
//					} 
//					else if ((cur_value[temp+x] <= min_cur/15.0)) {
//						if (cur_value[temp+x] <= min_cur/2.0)
//							tempD = 0;
//						else
//							tempD = (int32_t)((cur_value[temp+x]+cur_value[temp+x]-min_cur)*256.0/(max_cur-min_cur));
//					}
//					else {
//						tempD = (int32_t)((cur_value[temp + x]*2.0-min_cur) * 256.0 / (max_cur-min_cur));
//					}
//				}
//
//				if (tempD < 0)
//					tempD = 0;
//				if (tempD > 255)
//					tempD = 255;
//				*(pDst + temp + x) = tempD;
//			}
//		}
//
//}



/******************************************************************************
*******************************************************************************
************************下面的函数对指纹具有较强的适用性***********************
************************下面的函数对指纹具有较强的适用性***********************
************************下面的函数对指纹具有较强的适用性***********************
*******************************************************************************
******************************************************************************/


//#define UP_EDGE			12
//#define DOWN_EDGE		FP_HEIGHT - 10
//#define LEFT_EDGE		27
//#define RIGHT_EDGE		FP_WIDTH - 10
//
////去除指纹图像边缘处的黑边
//void FPBlackSegment
//(
// //uint8_t *pDst,
// uint8_t *pSrc,
// //uint8_t *pGrads,
// const int32_t width, 
// const int32_t height, 
// const int32_t pitch
// )
//{
//	int32_t x, y;
//	int32_t tempY = 0;
//	for (y = 0; y < height; y++) {
//		for (x = 0; x < width; x++) {
//			if ((y >= UP_EDGE) && (y <= DOWN_EDGE) && \
//				(x >= LEFT_EDGE) && ( x <= RIGHT_EDGE)) {
//				continue;
//			} 
//			*(pSrc + tempY + x) = 255;
//			//*(pGrads + tempY + x) = 0;
//		}
//		tempY += pitch;
//	}
//}
//
//
//#define UP_EDGE_ORG			35
//#define DOWN_EDGE_ORG		FP_HEIGHT_ORG - 30
//#define LEFT_EDGE_ORG		70
//#define RIGHT_EDGE_ORG		FP_WIDTH_ORG - 30
//
////去除指纹图像边缘处的黑边
//void FPBlackSegmentOrg
//(
// //uint8_t *pDst,
// uint8_t *pSrc,
// //uint8_t *pGrads,
// const int32_t width, 
// const int32_t height, 
// const int32_t pitch
// )
//{
//	int32_t x, y;
//	int32_t tempY = 0;
//	for (y = 0; y < height; y++) {
//		for (x = 0; x < width; x++) {
//			if ((y >= UP_EDGE_ORG) && (y <= DOWN_EDGE_ORG) && \
//				(x >= LEFT_EDGE_ORG) && ( x <= RIGHT_EDGE_ORG)) {
//				continue;
//			} 
//			*(pSrc + tempY + x) = 255;
//			//*(pGrads + tempY + x) = 0;
//		}
//		tempY += pitch;
//	}
//}


/******************************************************************************
  * 功能：利用梯度对指纹图像数据进行前景与背景的粗分割
  * 参数：pSrc			欲分割的图像数据(分割后,背景区域置255)[Out]
  *       pOrientation	欲分割的方向场(分割后,背景区域方向场置255)[Out]
  *		  pGrads		欲分割图像的梯度(用于判断像素点是前景还是背景)[In]
  *       size			对梯度进行软化(平滑)窗口大小(2*r+1)
  *		  step			对梯度进行软化(平滑)的步长
  *		  threshold		分割阈值(将像素点的梯度幅值与之比较)
  *		  width			图像数据宽度
  *		  height		图像数据高度
  *		  pitch			图像数据每行字节数
  * 返回：错误编号
  *	说明: 指纹图像的前景区域的梯度一般都比较大(黑白纹线清晰相间),而背景区域梯度都比较
  *		  小.把求出的梯度进行高度平滑,去掉梯度图像的噪声,然后用适当的阈值就可以判断
  *		  该点为前景还是背景.确定阈值的步骤如下:
  *		  1.阈值的选择与图像质量有关.对于光学图像,因为比较平滑,所以阈值A比较小,通常
  *			取30-40.如果图像不够平滑,则必须先对图像进行平滑处理,并且阈值大约取50左右
  *			(这里测试时取了80)
  *		  2.用单位区域上的梯度阈值作为灰度梯度特征,即梯度幅值T(x,y),需要计算单位区域
  *			内的平均梯度作为该区域的梯度幅值,即对梯度幅值进行平滑(软化)滤波
  *		  3.若:T(x,y)>A,则(x,y)在前景上,否则在背景
  * 算法: 
  *		  1.调用此函数前,首先要先计算好欲分割的图像的梯度值pGrads
  *		  2.函数功能:
  *			(1)先对梯度值进行平滑滤波
  *			(2)将边界梯度置为255(前景),并对非边界区域利用threshold进行分割,把每点的
  *			   梯度值置为0(背景)或255(前景)
  *			(3)判断前景区域不会太小,否则返回错误
  *			(4)根据分割后的梯度值0(背景)分别对指纹图像数据和方向场数据置255(背景)
******************************************************************************/
FunError_t FPGradsRSegment
(
 uint8_t *pSrc, 
 uint8_t *pOrientation, 
 uint8_t *pGrads, 
 const int32_t size, 
 const int32_t step, 
 const int32_t threshold, 
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
)
{
	//int32_t	x, y;
	////int32_t r = size / 2;
	//int32_t num = 0;
	//int32_t tempY;
	//
	//BufferCopyV1(fp_src_copy.pimg, pGrads, FP_WH_SIZE);
	////BufferCopy32(fp_src_copy.pimg, pGrads, FP_WH_SIZE32);
	//
	//// 对方向场幅值图像进行高度平滑滤波
	////SoftenMean(pGrads, pFPTemp, width, height, pitch, size, step);
	//MeanSmooth(pGrads, fp_src_copy.pimg, width, height, pitch, size, step);

	//// 图像边缘均设置为背景
	//for (y = 0; y < height; y++) {
	//	*(pGrads + y*pitch) = 255;
	//	*(pGrads + y*pitch + pitch - 1) = 255;			//边缘点设为背景(白色)
	//}
	//for (x = 0; x < width; x++) {
	//	*(pGrads + x) = 255;
	//	*(pGrads + (height-1)*pitch + x) = 255;			//边缘点设为背景(白色)
	//}

	//for (y = 1; y < height-1; y++) {
	//	for (x = 1; x < width-1; x++) {
	//		//if ((y < UP_EDGE) || (y > DOWN_EDGE) || \
	//		//	(x < LEFT_EDGE) || ( x > RIGHT_EDGE)) {
	//		//	*(pGrads + y*pitch + x) = 0;			//背景设为黑色
	//		//} else {
	//		// 根据幅值与阈值大小判断是否为背景区域
	//			if(*(pGrads + y*pitch + x) < threshold) {
	//				*(pGrads + y*pitch + x) = 0;			//背景设为黑色
	//			} else {
	//				*(pGrads + y*pitch + x) = 255;			//前景设为白色
	//				num++;
	//			}
	//		//}
	//	}
	//}

	//// 如果前景区域面积小于总面积的十分之一，则表示前景区域太小，返回错误
	//if(num < height * width/10)
	//	return FunFailure;

	////清除背景
	//tempY = 0;
	//for (y = 0; y < height; y++) {
	//	//优化前:
	//	//tempY = y * pitch;
	//	for (x = 0; x < width; x++) {	
	//		// 如果是背景区域，则置该点灰度和方向场为白点
	//		if (*(pGrads + tempY + x) == 0) {
	//			*(pSrc + tempY + x) = 255;					//边缘点设为背景(白色)	
	//			*(pOrientation + tempY + x) = 255;			//边缘点设为背景(白色)
	//		}
	//	}
	//	//优化后
	//	tempY += pitch;
	//}
	//return FunOK;
	int32_t	x, y;
	//int32_t r = size / 2;
	int32_t num = 0;
	int32_t tempY;

	BufferCopyV1(fp_src_copy.pimg, pGrads, FP_WH_SIZE);
	//BufferCopy32(fp_src_copy.pimg, pGrads, FP_WH_SIZE32);

	// 对方向场幅值图像进行高度平滑滤波
	//SoftenMean(pGrads, pFPTemp, width, height, pitch, size, step);
	MeanSmooth(pGrads, fp_src_copy.pimg, width, height, pitch, size, step);

	// 图像边缘均设置为背景
	for (y = 0; y < height; y++) {
		*(pGrads + y*pitch) = 255;
		*(pGrads + y*pitch + pitch - 1) = 255;			//边缘点设为背景(白色)
	}
	for (x = 0; x < width; x++) {
		*(pGrads + x) = 255;
		*(pGrads + (height-1)*pitch + x) = 255;			//边缘点设为背景(白色)
	}

	for (y = 1; y < height-1; y++) {
		tempY = y*pitch;
		for (x = 1; x < width-1; x++) {
			//if ((y < UP_EDGE) || (y > DOWN_EDGE) || \
			//	(x < LEFT_EDGE) || ( x > RIGHT_EDGE)) {
			//	*(pGrads + y*pitch + x) = 0;			//背景设为黑色
			//} else {
			// 根据幅值与阈值大小判断是否为背景区域
			//if(*(pGrads + y*pitch + x) < threshold) {
			//	*(pGrads + y*pitch + x) = 0;			//背景设为黑色
			//} else {
			//	*(pGrads + y*pitch + x) = 255;			//前景设为白色
			//	num++;
			//}
			if(*(pGrads + tempY + x) < threshold) {
				*(pGrads + tempY + x) = 0;			//背景设为黑色
			} else {
				*(pGrads + tempY + x) = 255;			//前景设为白色
				num++;
			}
			//}
		}
	}

	// 如果前景区域面积小于总面积的十分之一，则表示前景区域太小，返回错误
	//if(num < height * width/10)
	//	return FunFailure;

	//清除背景
	tempY = 0;
	for (y = 0; y < height; y++) {
		//优化前:
		//tempY = y * pitch;
		for (x = 0; x < width; x++) {	
			// 如果是背景区域，则置该点灰度和方向场为白点
			if (*(pGrads + tempY + x) == 0) {
				*(pSrc + tempY + x) = 255;					//边缘点设为背景(白色)	
				*(pOrientation + tempY + x) = 255;			//边缘点设为背景(白色)
			}
		}
		//优化后
		tempY += pitch;
	}
	return FunOK;

}














