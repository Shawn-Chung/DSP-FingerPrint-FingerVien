/******************************************************************************
 * 文件名：image_base.h
 * 功  能：一些基本的图像操作
******************************************************************************/

#if !defined __IMAGE_BASE_H
#define __IMAGE_BASE_H

#include "../../bsp/bsp_header/z_mytype.h"
#include "../../sys/sys_header/sys_global.h"

#include "image.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef enum Interpolation_t 
{
	InterLinear 	= 1,	// - 双线性插值
	InterNN			= 2	// - 最近邻插值
}Interpolation_t;


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
 );


void GrayNormalizeV1
(
 uint8_t *pDst, 
 uint8_t *pSrc,
 uint8_t *pSeg,
 const int32_t src_width,
 const int32_t src_height,
 const int32_t src_pitch
 );

/******************************************************************************
  * 功能：图像的梯度及其幅值计算,输出梯度幅值数据(被图像梯度获取函数调用)
  * 参数：pDst				输出数据
  *		  pSrc				输入数据
  *       width				正常图像宽度
  *		  height			正常图像高度
  * 返回：
******************************************************************************/
void HalfWidthHeight(uint8_t *pDst, uint8_t *pSrc, const int32_t width, const int32_t height);
//void HalfWidthHeight(uint8_t *pDst, uint8_t *pSrc, const int32_t width, const int32_t height);

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
void SizeNormalize
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
 );


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
//#define SCALE 1000000	//去小数点放大取整倍数:取值100,10000对于缩小没问题,
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
 );

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
 );


/******************************************************************************
  * 功能：图像数据均衡,被图像均衡函数调用
  * 参数：pSrc		欲均衡图像数据
  *       width		图像宽度
  *		  height    图像高度
  *		  pitch		图像每行字节数
  * 返回：
******************************************************************************/
void Equalization(uint8_t *pSrc, const int32_t width, const int32_t height, const int32_t pitch);

void EqualizationV1(uint8_t *pSrc, uint8_t *pSeg, const int32_t width, const int32_t height, const int32_t pitch);



//梯度算子
#define SOBEL_H			1
#define SOBEL_V			2
#define SOBEL_H1		3
#define SOBEL_V1		4
#define SOBEL_HV		5

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
void GetGrads
(
 uint8_t *pDst, 
 uint8_t *pSrc, 
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch,
 const int32_t size,
 const int32_t operator_type
);


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
 );



#define THR_WB			0		
#define THR_WBI			1	
#define THR_OZ			2
#define THR_OZI			3
#define THR_TRUNC		4
#define THR_ZERO		5
#define THR_ZEROI		6

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
 );


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
 );


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
void OverallBinaryGrads
(
 uint8_t *pDst,
 uint8_t *pSrc,
 uint8_t *pGrads,
 const int32_t size,
 const int32_t dir,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 );

void MeanBinary
( 
 uint8_t *pDst,
 uint8_t *pSrc,
 const int32_t size, 
 const int32_t dir,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 );

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
 );






#define TOOZ  0
#define TOWB  1
/******************************************************************************
  * 功能：图像二值互换(OZ二值与黑白二值互换)
  * 参数：pSrc        图像必须为二值化后的图像数据
  * 参数：dir         从1:OZ-->WB, 0:WB-->OZ
  * 返回：错误编号
******************************************************************************/
FunError_t BinaryExchange(uint8_t *pSrc, const int32_t w, int32_t h, const int32_t dir);


/******************************************************************************
  * 功能：图像膨胀通用算法
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
 );




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
 );


/******************************************************************************
*******************************************************************************
************************下面的函数对指纹具有较强的适用性***********************
************************下面的函数对指纹具有较强的适用性***********************
************************下面的函数对指纹具有较强的适用性***********************
*******************************************************************************
******************************************************************************/
extern int g_direction_xy[12][7][2];


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
);




#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* __IMAGE_BASE_H */


