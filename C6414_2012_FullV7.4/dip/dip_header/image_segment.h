/******************************************************************************
 * 文件名：image_segment.h
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


#if !defined __IMAGE_SEGMENT_H
#define __IMAGE_SEGMENT_H

#include "../../bsp/bsp_header/z_mytype.h"
#include "../../sys/sys_header/sys_global.h"

#ifdef __cplusplus
extern "C" {
#endif

//曲率类型定义:
#define CUR_MEAN	0
#define CUR_PRI1	1
#define CUR_PRI2	2
#define CUR_GAUS	3
#define CUR_TEND	4
#define CUR_STRI	5
#define CUR_MAX		6
#define CUR_MIN		7

#define FP_SEGMENT_W		13
#define FP_SOFTEN_S			2
#define FP_SEGMENT_TH		80



FunError_t GradsRSegment
(
 uint8_t *pSrc,  
 uint8_t *pGrads, 
 const int32_t size, 
 const int32_t step, 
 const int32_t threshold, 
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
);

void FVRSegment
(
 uint8_t *pDst,
 uint8_t *pSrc,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 );


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
 );


void CurvatureSegmentV1
(
 uint8_t *pDst,
 uint8_t *pSrc,
 uint8_t *pSeg,
 int32_t cur_type, 
 int32_t size, 
 int32_t thr_type,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 );



/******************************************************************************
*******************************************************************************
************************下面的函数对指纹具有较强的适用性***********************
************************下面的函数对指纹具有较强的适用性***********************
************************下面的函数对指纹具有较强的适用性***********************
*******************************************************************************
******************************************************************************/


//去除指纹图像边缘处的黑边
void FPBlackSegment
(
 //uint8_t *pDst,
 uint8_t *pSrc,
 //uint8_t *pGrads,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 );

void FPBlackSegmentOrg
(
 //uint8_t *pDst,
 uint8_t *pSrc,
 //uint8_t *pGrads,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 );

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
);









#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* __IMAGE_SEGMENT_H */

