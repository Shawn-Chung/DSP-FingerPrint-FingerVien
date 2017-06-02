/******************************************************************************
 * 文件名：image_feature.h
 * 功  能：主要实现图像的特征提取
******************************************************************************/
#if !defined __IMAGE_FEATURE_H
#define __IMAGE_FEATURE_H

/* 包含基本的图像操作函数 */
//#include "image_base.h"

//#include "float_field.h"
#include "../../bsp/bsp_header/z_mytype.h"

#include "image_miscellaneous.h"
#include "base_fun.h"
//#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 不同细节点类型的定义 */
typedef enum MinutiaType_t
{
    MinutiaTypeEnd			= 0, /* 端点   */
    MinutiaTypeFork			= 1, /* 分支点 */
    MinutiaTypeCore			= 2, /* 核心点 */
    MinutiaTypeDelta		= 3 /* 三角点 */
} MinutiaType_t;

/* 细节点结构,尽可能准确的提取细节点的类型,坐标*/
typedef struct FVMinutia_t
{
    /* 细节点类型 */
    MinutiaType_t type;
    /* X轴坐标    */
    int32_t    x;
    /* Y轴坐标    */
    int32_t    y;
} FVMinutia_t;

#define FV_MAX_MINUTIA_NUM			250		// 最大特征点数

typedef struct FVMinutiaSet_t {
	int32_t			nbminutia; 				// 特征点数
	FVMinutia_t		FVMinutiaArr[FV_MAX_MINUTIA_NUM];	// 特征点数组
} FVMinutiaSet_t, *pFVMinutiaSet_t;



/************************************************************************
  * 功能：从细化图像中提取细节点，并储存到集合中。
  *      申请的细节点集合必须足够大，如果太小了，满了后会停止搜索细节点。
  * 参数：minutia       细节点集合，用来保存细节点
  * 	  pSrc		    图像数据
  * 	  width			图像数据宽度
  *		  height		图像数据高度
  *		  pitch			图像数据每行字节数
  * 返回：错误编号
  * 算法：
  *        注意：(1)图像的前景是"1",背景是"0"
  *              (2)图像是完全细化的图像，即没有任何冗余的点。
  * 
  *        一个点p的8邻域如图所示
  *        ----------
  *        |x4|x3|x2|
  *        ----------
  *        |x5|p |x1|
  *        ----------
  *        |x6|x7|x8|
  *        ----------
  *      
  *        当p点及其邻域同时满足以下条件时p点是特征点。
  * 
  *        (1)p点是"1",即是前景不是背景。
  * 
  *        (2)p点的8邻域"1"的点数为1,3,或者4。
  * 
  *           1)p点的8邻域"1"的点数为1则p点是端点。
  *           2)p点的8邻域"1"的点数为3则p点是三邻域交叉点。
  *           3)p点的8领域"1"的点数为4则p点是四邻域交叉点。
*************************************************************************/
//static FunError_t FVMinutiaSetExtractLowLevel
//(
// pFVMinutiaSet_t minutia,
// uint8_t *pSrc,
// const int32_t width, 
// const int32_t height, 
// const int32_t pitch
// );


/************************************************************************
  * 功能：从细化图像中提取细节点，并储存到集合中。
  *      申请的细节点集合必须足够大，如果太小了，满了后会停止搜索细节点。
  * 参数：minutia       细节点集合，用来保存细节点
  * 	  pSrc		    图像数据
  * 	  width			图像数据宽度
  *		  height		图像数据高度
  *		  pitch			图像数据每行字节数
  *       area_thr      传递给其他函数的参数,用来判断终止条件的,
  *						当计数器的值大于阈值area_thr时则终止当前扫描。
  * 返回：错误编号
  * 作用：对已经细化但是没有修剪毛刺的图像进行处理，直接提取出特征点。
  * 算法：
  *          第一步：对图像进行特征点预提取。
  *          第二步：对所有特征点逐步进行比对，设定一定的条件将伪特征点去除。
  *         第三步：去除伪特征点后再提取一次特征点。 
*************************************************************************/
//FunError_t FVMinutiaSetExtractOZ
//(
// pFVMinutiaSet_t minutia,
// uint8_t *pSrc,
// const int32_t width, 
// const int32_t height, 
// const int32_t pitch,
// const int32_t area_thr
// );

void FVMinutiaSetDilateOZ
(
 uint8_t *pSrc,
 pFVMinutiaSet_t minutia,	
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

#define	FP_MAX_SINGULARYTY_NUM		30
#define FP_MAX_END_NUM				60
#define FP_MAX_FORK_NUM				60
#define FP_MAX_MINUTIA_NUM			60		// 最大特征点数
#define FP_MAX_RAW_MINUTIA_NUM     100		// 包含虚假特征点的初始特征点最大数目

/* 细节点结构,尽可能准确的提取细节点的类型,坐标*/
typedef struct FPMinutia_t
{
    /* 细节点类型 */
    MinutiaType_t type;
    /* X轴坐标    */
    int32_t    x;
    /* Y轴坐标    */
    int32_t    y;
	/* 细节点方向:范围(0-360)*/
	//double    angle;
	int32_t	   angle;
	/*特征点为中心外接圆半径为定值的正三角形三个顶点的方向,范围(0-180)*/
	int32_t	   triangle[3];	
} FPMinutia_t;

typedef struct FPMinutiaSet_t {
	int32_t			nbminutia; 				// 特征点数
	FPMinutia_t		FPMinutiaArr[FP_MAX_MINUTIA_NUM];	// 特征点数组
} FPMinutiaSet_t, *pFPMinutiaSet_t;

/************************************************************************
  * 功能：根据点的地址,计算出该点在图像中的x坐标
  * 参数：pPos				指向该点的地址
  *		  pSrc				指向源图像数据区
  *		  width				图像数据宽度
  *		  height			图像数据高度
  *		  pitch				图像数据每行字节数
  * 返回：该点在图像中的x坐标
  * 说明: 
*************************************************************************/
int32_t  M_PX(uint8_t *pPos, uint8_t *pSrc, uint32_t pitch);


/************************************************************************
  * 功能：根据点的地址,计算出该点在图像中的y坐标
  * 参数：pPos				指向该点的地址
  *		  pSrc				指向源图像数据区
  *		  width				图像数据宽度
  *		  height			图像数据高度
  *		  pitch				图像数据每行字节数
  * 返回：该点在图像中的y坐标
  * 说明: 
*************************************************************************/
int32_t  M_PY(uint8_t *pPos, uint8_t *pSrc, uint32_t pitch);


/************************************************************************
  * 功能：根据奇异点的类型,获取两点之间方向场的变化
  * 参数：angle1			角度1
  *		  angle2			角度2
  *		  flag				奇异点类型 1:三角点, 其他:中心点
  * 返回：方向场变化角度
  * 说明: 
*************************************************************************/
int32_t GetOrientChange(const int32_t angle1, const int32_t angle2, const uint8_t flag);


/************************************************************************
  * 功能：提取指纹图像的奇异点
  * 参数：minutia			细节点集合
  *		  pOrientation		经过分割(非纹路分割(粗分割)FPImageGradsRSegment)
  *							后的图像方向场
  *		  width				图像数据宽度
  *		  height			图像数据高度
  *		  pitch				图像数据每行字节数
  *		  flag				奇异点类型 1:三角点, 其他:中心点
  * 返回：void
  * 说明: 粗分割:分割ROI与背景,细分割:ROI区域里面纹路与非纹路的分割
  * 算法: 
  *		  原理: 一个场,如果存在奇点,其周围的方向场变化剧烈.
  *				对于中心点和三角点的提取就是基于这点原理.
  *		    目前提取指纹图像奇异点方法有很多种，其中最常用的是基于Poincare
  *		  Index的方法。该方法通过分析指纹图像的方向图来提取奇异点。
  *		  在此定义Poincare Index为一条封闭曲线上的点(大约25个)的方向变化之
  *		  和.沿指纹方向图上封闭曲线逆时针一圈,若曲线上的像素点方向变化之和
  *		  为0,则该点对应的像素点是普通点.若和为1/2,则该点对应的像素点是中心点,
  *		  若为-1/2,则该点对应的像素点是三角点
  *		    设象素点的方向 Sita属于[0, PI],离散化矩形封闭曲线的长度为L,曲线长度
  *		  不能太小,否则引入伪奇异点,太大则可能包含多个奇异点.封闭曲线所围
  *		  绕的象素点(x,y)的Poincare Index通过以下公式计算:
  *			Poincare(i,j)=1/(2PI)*Sigma<0,L-1>Delta(k)
  *						   PI-Beta(k)	Beta(k)>=PI/2
  *				Delta(k) = PI+Beta(k)   Beta(k)<=-PI/2
  *						   Beta(k)		其他
  *		  			其中Beta(k)=Sita((k+1)modL)-Sita(k).
  *		  	  为了简化Poincare Index提取奇异点,闭曲线采用5x5的方格,
  *		  		D12	D11	D10
  *		  	D1	d1	d8	d7	D9
  *		  	D2	d2	i,j	d6	D8
  *		  	D3	d3	d4	d5	D7
  *		  		D4	D5	D6
  *		  	分别计算以d和D为半径的区域方向场差的和.
  *		    在5x5方格内,计算Poincare Index值,以(i,j)为中心,按顺时针方向
  *		  形成闭合曲线D1,D2,...D12分别表示该点的方向.该闭合曲线的Poincare
  *		  Index值:
  *					Poincare(i,j)=Sigma<1,12>|Di-D((i+1)mod12)|
  *		  同理在3x3方格内:
  *					Poincare(i,j)=Sigma<1,8>|di-d((i+1)mod8)|
  *		    由于一些指纹图像存在噪音的问题,可能存在伪奇异点,为了消除伪奇异点.只有在
  *		  3x3和5x5方格算出的Poincare值(中心点为1/2或三角点为-1/2)相同的时候,
  *		  才算是真正的奇异点.
  *		    若所得的奇异点附近已有奇异点,则用它们的均值作为最终的奇异点
*************************************************************************/
void FPMinutiaSetExtractSingularity
(
 pFPMinutiaSet_t minutia,
 uint8_t *pOrientation, 
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch,
 const uint8_t flag 
 );


/************************************************************************
  * 功能：判断点(x,y)与粗边界距离在r以外
  * 参数：pOrietation		粗分割后图像方向场数据
  *		  x					坐标点x
  *		  y					坐标点y
  *		  r					边界阈值r
  *		  width				图像数据宽度
  *		  height			图像数据高度
  *		  pitch				图像数据每行字节数
  *		  rbackcolor		粗背景色颜色(指粗分割后非ROI区域的颜色)
  * 返回：1: 不在 0: 在
  * 说明: 这里的粗边界是指粗分割后ROI区域与非ROI区域的边界.
  *		  没有进行图像区域的越界处理,因此调用此函数要保证不会越界
*************************************************************************/
int32_t IsAtEdge
(
 uint8_t *pOrietation, 
 const int32_t x, 
 const int32_t y, 
 const int32_t r, 
 //const int32_t width, 
 //const int32_t height, 
 const int32_t pitch, 
 const int32_t rbackcolor
) ;


/************************************************************************
  * 功能：判断点(x,y)的方向场变化是否剧烈
  * 参数：pOrietation		粗分割后图像方向场数据
  *		  x					坐标点x
  *		  y					坐标点y
  *		  site				以(x,y)为圆心,半径为r的圆上所有点的地址偏移
  *		  site_num			以(x,y)为圆心,半径为r的圆上所有点的个数
  *		  width				图像数据宽度
  *		  height			图像数据高度
  *		  pitch				图像数据每行字节数
  *		  ori_thr		    方向场变化是否剧烈的阈值
  * 返回：1: 不剧烈 0: 剧烈
  * 说明: 这里的粗边界是指粗分割后ROI区域与非ROI区域的边界.
  *		  没有进行图像区域的越界处理,因此调用此函数要保证不会越界
*************************************************************************/
int32_t IsOriChgViolent
(
 uint8_t *pOrietation, 
 const int32_t x, 
 const int32_t y, 
 int32_t *site, 
 const int32_t site_num,
 //const int32_t width, 
 //const int32_t height, 
 const int32_t pitch, 
 const int32_t ori_thr
) ;


///************************************************************************
//  * 功能：获取图像的粗末梢点或粗分叉点
//  * 参数：pSrc				指向源图像数据区
//  *		  pOrientation		指向源图像粗分割后的方向场
//  *		  pMinutia			特征点坐标存储数组
//  *		  minutia_num		特征点数目
//  *		  width				图像数据宽度
//  *		  height			图像数据高度
//  *		  pitch				图像数据每行字节数
//  *		  r					边界阈值r(采用默认16)
//  *		  ori_thr			方向场变化剧烈程度(默认半径为5的点的变化为96)
//  *		  forecolor		    图像数据前景颜色(默认0)
//  *		  rbackcolor		粗背景色颜色(指粗分割后非ROI区域的颜色)(默认255)
//  *		  bina_type			图像二值类型1:(0,1)或其他:(0,255)(默认255)
//  *		  min_type			特征点类型1:分叉点 其他:末梢点
//  * 返回：0:正确获取,1:错误
//  * 说明:   有些函数参数使用了默认的值,没有真正作为形参,要使用时只需将注释
//  *		  去掉,并且将函数开头设置的默认值注释掉即可.
//  *		    这里在寻找特征点的时候首先去除了在图像边缘(粗边界)和周围方向场剧烈变化
//  *		  的伪特征点
//  * 算法: 
//  *		  1.遍历图像的每个点,并判断是否为分叉点和末梢点(IsFork和IsEnd函数)
//  *		  2.若是端点和末梢点,则判断是否满足边界阈值r(IsAtEdge)和
//  *		    周围方向场是否变化剧烈(IsOriChgViolent).只要有一个不满足,
//  *		  	则此为伪特征点,不添加到存储数组中,并继续进行步骤1.否则,进行3.
//  *		  3.存储该点的坐标到存储数组中,并记录存储的总数目.
//  *		  4.直到遍历完整个图像,结束.
//*************************************************************************/
//int32_t GetRawEndOrFork
//(
// uint8_t *pSrc,
// uint8_t *pOrientation,
// Point_t *pMinutia,
// int32_t *minutia_num,
// const int32_t width,
// const int32_t height,
// const int32_t pitch,
// //const int32_t r,
// //const int32_t ori_thr,
// //const int32_t forecolor,
// //const int32_t rbackcolor,
// //const int32_t bina_type,
// const int32_t min_type
// );


/************************************************************************
  * 功能：获取图像的粗末梢点和粗分叉点
  * 参数：pSrc				指向源图像数据区
  *		  pOrientation		指向源图像粗分割后的方向场
  *		  pFork				分叉点坐标存储数组
  *		  fork_num			分叉点数目
  *		  pEnd				末梢点坐标存储数组
  *		  end_num			末梢点数目
  *		  width				图像数据宽度
  *		  height			图像数据高度
  *		  pitch				图像数据每行字节数
  *		  r					边界阈值r(采用默认16)
  *		  ori_thr			方向场变化剧烈程度(默认半径为5的点的变化为96)
  *		  forecolor		    图像数据前景颜色(默认0)
  *		  rbackcolor		粗背景色颜色(指粗分割后非ROI区域的颜色)(默认255)
  *		  bina_type			图像二值类型1:(0,1)或其他:(0,255)(默认255)
  * 返回：0:正确获取,1:错误
  * 说明:   有些函数参数使用了默认的值,没有真正作为形参,要使用时只需将注释
  *		  去掉,并且将函数开头设置的默认值注释掉即可.
  *		    这里在寻找特征点的时候首先去除了在图像边缘(粗边界)和周围方向场剧烈变化
  *		  的伪特征点
  * 算法: 
  *		  1.遍历图像的每个点,并判断是否为分叉点和末梢点(IsFork和IsEnd函数)
  *		  2.若是端点和末梢点,则判断是否满足边界阈值r(IsAtEdge)和
  *		    周围方向场是否变化剧烈(IsOriChgViolent).只要有一个不满足,
  *		  	则此为伪特征点,不添加到存储数组中,并继续进行步骤1.否则,进行3.
  *		  3.存储该点的坐标到存储数组中,并记录存储的总数目.
  *		  4.直到遍历完整个图像,结束.
*************************************************************************/
int32_t GetRawEndAndFork
(
 uint8_t *pSrc,
 uint8_t *pOrientation,
 Point_t *pFork,
 int32_t *fork_num,
 Point_t *pEnd,
 int32_t *end_num,
 const int32_t width,
 const int32_t height,
 const int32_t pitch
 //const int32_t r,
 //const int32_t ori_thr
 //const int32_t forecolor,
 //const int32_t rbackcolor,
 //const int32_t bina_type, 
 );


/************************************************************************
  * 功能：清除伪末梢点
  * 参数：pSrc				指向源图像数据区
  *		  pMinutia			粗特征提取后特征点坐标存储数组
  *		  minutia_num		特征点数目
  *		  fixed_dis			特征点之间固定最小距离
  *		  var_dis			特征点之间动态最小距离
  *		  trace_len			纹线跟踪长度(默认为8)
  *		  width				图像数据宽度
  *		  height			图像数据高度
  *		  pitch				图像数据每行字节数
  *		  forecolor		    图像数据前景颜色(默认0)
  *		  bina_type			图像二值类型1:(0,1)或其他:(0,255)(默认255)
  * 返回：没什么意义
  * 说明:   有些函数参数使用了默认的值,没有真正作为形参,要使用时只需将注释
  *		  去掉,并且将函数开头设置的默认值注释掉即可.
  *		    这里清除了距离过小的伪特征点和断线之间的的伪特征点
  * 算法: 
  *		  1.从特征点数组提取一组特征点1(A1)和2(B1),首先计算两者之间的距离,
  *		    若过小则清除,继续提取下一个特征点.反之,进入步骤2
  *		  2.若满足,则判断是否为一条断开的纹线的两个伪特征:
  *		    先沿线跟踪纹线,分别找到两特征点纹线上的A2,B2.计算A1A2的角度angle1,
  *		    B1B2的角度angle2若两角度差为锐角,则不是伪特征点.反之,进入步骤3
  *		  3.计算A1B1的角度angle3.分别判断angle1,angle2和angle3的角度.
  *		    若较大,则不是伪特征点.反之,进入步骤4.
  *		  4.将伪特征点坐标置为(0,0),继续查找下一组特征点.
  *		    直到所有特征点均检验完毕,结束.
*************************************************************************/
int32_t ClearFakeEnd
(
 uint8_t *pSrc,
 Point_t *pMinutia,
 const int32_t minutia_num,
 const int32_t fixed_dis,
 const int32_t var_dis,
 //const int32_t trace_len
 //const int32_t width,
 //const int32_t height,
 const int32_t pitch
 //const int32_t forecolor,
 //const int32_t bina_type,
 );


/************************************************************************
  * 功能：获取真正的末梢点
  * 参数：pSrc				指向源图像数据区
  *		  pMinutia			经过伪特征清除函数后特征点坐标存储数组
  *		  minutia_num		特征点数目
  *		  trace_len			纹线跟踪长度(默认为8)
  *		  width				图像数据宽度
  *		  height			图像数据高度
  *		  pitch				图像数据每行字节数
  *		  forecolor		    图像数据前景颜色(默认0)
  *		  bina_type			图像二值类型1:(0,1)或其他:(0,255)(默认255)
  * 返回：0表示错误,需要调整动态的最小距离var_dis 1:正确
  * 说明:   有些函数参数使用了默认的值,没有真正作为形参,要使用时只需将注释
  *		  去掉,并且将函数开头设置的默认值注释掉即可.
  *			调用函数前先调用CleanFakeEnd获取pMinutia指向的特征存储数组
  * 算法: 
  *		  找到真特征点后,沿纹线看是否trace_len的点是否为前景色(去除毛刺)
  *		  的伪特征点.若是则记录,若否则去除伪特征
*************************************************************************/
int32_t GetRealEnd
(
 uint8_t *pSrc,
 Point_t *pMinutia,
 const int32_t minutia_num,
 //const int32_t trace_len
 //const int32_t width,
 //const int32_t height,
 const int32_t pitch
 //const int32_t forecolor,
 //const int32_t bina_type,
 );


/************************************************************************
  * 功能：将特征末梢点添加到特征点集MinutiaSet中
  * 参数：minutia			记录特征点的特征点集
  *		  pSrc				指向源图像数据区
  *		  pOrientation		指向源图像粗分割后的方向场
  *		  pMinutia			粗特征提取后特征点坐标存储数组
  *		  minutia_num		特征点数目
  *		  trilen			正三角形外接圆半径
  *		  trace_len			纹线跟踪长度(默认为8)
  *		  width				图像数据宽度
  *		  height			图像数据高度
  *		  pitch				图像数据每行字节数
  *		  forecolor		    图像数据前景颜色(默认0)
  *		  bina_type			图像二值类型1:(0,1)或其他:(0,255)(默认255)
  * 返回：分叉点数目
  * 说明:   有些函数参数使用了默认的值,没有真正作为形参,要使用时只需将注释
  *		  去掉,并且将函数开头设置的默认值注释掉即可.
  *		    这里清除了距离过小的伪特征点和断线之间的的伪特征点
  * 算法: 
  *		  1.由特征点A沿纹线跟踪找到trace_len(8)的点B,计算AB的角度angle1
  *			并与A点方向场angle2比较等到temp_angle作为特征点A的角度特征Angle
  *		  2.根据外接圆半径trilen和A点坐标和角度Angle计算A点外接圆上正三角形的
  *		    三个顶点坐标的方向场temp_triangle[3]作为A的特征顶点的角度特征
  *		  3.调用MinutiaSetAddV2将A点的特征添加到特征点集中
*************************************************************************/
int32_t FPAddEnd
(
 pFPMinutiaSet_t minutia,
 uint8_t *pSrc, 
 uint8_t *pOrientation,
 Point_t *pMinutia,
 const int32_t minutia_num,
 const int32_t trilen,
 //const int32_t trace_len,
 //const int32_t width,
 //const int32_t height,
 const int32_t pitch
 //const int32_t forecolor,
 //const int32_t bina_type,
 );


/************************************************************************
  * 功能：清除伪分叉点
  * 参数：pSrc				指向源图像数据区
  *		  pMinutia			粗特征提取后特征点坐标存储数组
  *		  minutia_num		特征点数目
  *		  var_dis			特征点之间动态最小距离
  *		  trace_len			纹线跟踪长度(默认为8)
  *		  width				图像数据宽度
  *		  height			图像数据高度
  *		  pitch				图像数据每行字节数
  *		  forecolor		    图像数据前景颜色(默认0)
  *		  bina_type			图像二值类型1:(0,1)或其他:(0,255)(默认255)
  * 返回：没什么意义
  * 说明:   有些函数参数使用了默认的值,没有真正作为形参,要使用时只需将注释
  *		  去掉,并且将函数开头设置的默认值注释掉即可.
  *		    这里清除了距离过小的伪特征点
  * 算法: 
  *		  1.从特征点数组提取一组特征点1(A1)和2(B1),首先计算两者之间的距离,
  *		    若过小则清除,将伪特征点坐标置为(0,0),继续查找下一组特征点.
  *		    直到所有特征点均检验完毕,结束.
*************************************************************************/
int32_t ClearFakeFork
(
 uint8_t *pSrc,
 Point_t *pMinutia,
 const int32_t minutia_num,
 //const int32_t fixed_dis,
 const int32_t var_dis,
 //const int32_t trace_len
 //const int32_t width,
 //const int32_t height,
 const int32_t pitch
 //const int32_t forecolor,
 //const int32_t bina_type,
 );


/************************************************************************
  * 功能：获取真正的分叉点
  * 参数：pSrc				指向源图像数据区
  *		  pMinutia			经过伪特征清除函数后特征点坐标存储数组
  *		  minutia_num		特征点数目
  *		  trace_len			纹线跟踪长度(默认为8)
  *		  width				图像数据宽度
  *		  height			图像数据高度
  *		  pitch				图像数据每行字节数
  *		  forecolor		    图像数据前景颜色(默认0)
  *		  backcolor		    图像数据背景景颜色(默认255)
  *		  bina_type			图像二值类型1:(0,1)或其他:(0,255)(默认255)
  * 返回：0表示错误,需要调整动态的最小距离var_dis 1:正确
  * 说明:   有些函数参数使用了默认的值,没有真正作为形参,要使用时只需将注释
  *		  去掉,并且将函数开头设置的默认值注释掉即可.
  *			调用函数前先调用CleanFakeEnd获取pMinutia指向的特征存储数组
  * 算法: 
  *		  找到真特征点后,检查是否为真的分叉点,若是则保存
*************************************************************************/
int32_t GetRealFork
(
 uint8_t *pSrc,
 Point_t *pMinutia,
 const int32_t minutia_num,
 //const int32_t trace_len
 //const int32_t width,
 //const int32_t height,
 const int32_t pitch
 //const int32_t forecolor,
 //const int32_t backcolor,
 //const int32_t bina_type,
 );


/************************************************************************
  * 功能：将特征分叉点添加到特征点集MinutiaSet中
  * 参数：minutia			记录特征点的特征点集
  *		  pSrc				指向源图像数据区
  *		  pOrientation		指向源图像粗分割后的方向场
  *		  pMinutia			粗特征提取后特征点坐标存储数组
  *		  minutia_num		特征点数目
  *		  trilen			正三角形外接圆半径
  *		  trace_len			纹线跟踪长度(默认为8)
  *		  width				图像数据宽度
  *		  height			图像数据高度
  *		  pitch				图像数据每行字节数
  *		  forecolor		    图像数据前景颜色(默认0)
  *		  backcolor		    图像数据背景景颜色(默认255)
  *		  bina_type			图像二值类型1:(0,1)或其他:(0,255)(默认255)
  * 返回：分叉点数目
  * 说明:   有些函数参数使用了默认的值,没有真正作为形参,要使用时只需将注释
  *		  去掉,并且将函数开头设置的默认值注释掉即可.
  *		    这里清除了距离过小的伪特征点和断线之间的的伪特征点
  * 算法: 
  *		  1.由特征点A沿纹线跟踪找到trace_len(8)的点B,C,D
  *		  2.计算三点距离d0,d1,d2.其中最小距离的对应叉线方向,由此得到叉线方向
  *		    坐标E.
  *		  3.计算E和A点的角度angle1并与A点方向场angle2比较得到temp_angle
  *			作为特征点A的角度特征Angle
  *		  4.根据外接圆半径trilen和A点坐标和角度Angle计算A点外接圆上正三角形的
  *		    三个顶点坐标的方向场temp_triangle[3]作为A的特征顶点的角度特征
  *		  5.调用MinutiaSetAddV2将A点的特征添加到特征点集中
*************************************************************************/
int32_t FPAddFork
(
 pFPMinutiaSet_t minutia,
 uint8_t *pSrc, 
 uint8_t *pOrientation,
 Point_t *pMinutia,
 const int32_t minutia_num,
 const int32_t trilen,
 //const int32_t trace_len,
 //const int32_t width,
 //const int32_t height,
 const int32_t pitch
 //const int32_t forecolor,
 //const int32_t backcolor,
 //const int32_t bina_type,
 );


/************************************************************************
  * 功能：提取指纹特征末梢点和分叉点到特征点集MinutiaSet中
  * 参数：minutia			记录特征末梢点和分叉点的特征点集
  *		  pSrc				指向源图像数据区
  *		  pOrientation		指向源图像粗分割后的方向场
  *		  pMinutia			粗特征提取后特征点坐标存储数组
  *		  minutia_num		特征点数目
  *		  width				图像数据宽度
  *		  height			图像数据高度
  *		  pitch				图像数据每行字节数
  *		  r					边界阈值r(采用默认16)
  *		  ori_thr			方向场变化剧烈程度(默认半径为5的点的变化为96)
  *		  fixed_dis			特征点之间固定最小距离(默认16)
  *		  var_dis			特征点之间动态最小距离(初始默认7)
  *		  trace_len			纹线跟踪长度(默认为8)
  *		  trilen			正三角形外接圆半径(默认16)
  *		  rbackcolor		粗背景色颜色(指粗分割后非ROI区域的颜色)(默认255)
  *		  forecolor		    图像数据前景颜色(默认0)
  *		  backcolor		    图像数据背景景颜色(默认255)
  *		  bina_type			图像二值类型1:(0,1)或其他:(0,255)(默认255)
  * 返回：分叉点数目
  * 说明:   有些函数参数使用了默认的值,没有真正作为形参,要使用时只需将注释
  *		  去掉,并且将函数开头设置的默认值注释掉即可.
  * 算法: 
  *		  1.遍历整幅图像,获取所有分叉点和末梢点(GetRawEndAndFork).这里获得的
  *			特征点已经去除边缘区域的伪特征和方向场剧烈变换的伪特征
  *		  2.分别对末梢点和分叉点进行伪特征去除和添加
  *			 末梢点:(1)末梢点伪特征去除(ClearFakeEnd),主要去除距离相近的伪特征点和
  *					   断线之间的的伪特征点
  *					(2)获取真实的末梢点(GetRealEnd),主要去除短的纹线
  *				       (毛刺,短棒,粘桥等)伪特征点.其中函数返回值bGood还反映了
  *					   特征点之间动态最小距离var_dis是否设置合适.不合适则要修改
  *					(3)添加末梢点及其特征到特征点集中(FPAddEnd)
  *			 分叉点:(1)分叉点伪特征去除(ClearFakeFork),主要去除距离相近的伪特征点
  *					(2)获取真实的分叉点(GetRealFork),主要去除短的纹线
  *				       (毛刺,短棒,粘桥等)伪特征点其中函数返回值bGood还反映了
  *					   特征点之间动态最小距离var_dis是否设置合适.不合适则要修改
  *					(3)添加末梢点及其特征到特征点集中(FPAddFork)
  *		  3.根据bGood决定是否需要调整var_dis.
  *			如果bGood==0,则要调整var_dis,继续进行步骤2,
  *			反之bGood==1,进入步骤4
  *			如果调整次数loopnum达到一定值(32)仍没有很好的效果则进入步骤4.
  *		  4.结束指纹特征末梢点和分叉点的提取.
  *	P.S : 伪特征点的描述
  *	参考文献:]
  *		1.基于DSP的指纹识别系统研究--韩书娜	(21-23)	<优秀硕士论文>
  *		  去除伪特征点时，要计算纹线间距，由于手指纹线的间距差异性很大，
  *		  本文在求取纹线间距时采用动态阈值法求取指纹纹线的间距，在细化的指纹
  *		  图像上做出垂直和水平两条直线，与指纹脊线相交，交点记为 X [ M ]，是一
  *		  个含有纵横坐标的二维数组。可求取指纹各个纹线之间间距的平均值
  *		  特征点时采用纹线跟踪技术，即沿某一条纹线，对该
  *		  纹线走过的点沿着一个方向进行跟踪记录到一个链表中，该链表中单元的次
  *		  序是被跟踪的像素点在纹线上的次序，每个单元记录了被跟踪的像素点的纵
  *		  坐标，横坐标和该点的类型（其中 1 表示端点；2 表示连续点；3 表示分叉
  *		  点）下面用纹线跟踪技术去除为特征点。
  *		  (1)． 去除毛刺
  *		  毛刺是在对指纹图像二值化时由随机噪声引起的，在提取细节特征点
  *		  时，毛刺表现为一个端点和一个分叉点，且二者的距离很近。去除毛刺的算
  *		  法如下：
  *		  依次选取所有的分叉点，沿着其分叉处的三条纹线，利用纹线跟踪技
  *		  术，检测在阈值长度T1内是否存在一个端点，若检测到这样的端点，
  *		  则该点是伪特征点，删除该点到分叉点的所有像素点即可去除毛刺。
  *		  (2)． 去除短纹
  *		  短纹是在指纹采集过程中，采集样本手指比较脏而产生的。在提取特征
  *		  点时表现为两个端点，且这两个端点的距离很近。去除短纹的算法如下：
  *		  依次选取所有的端点，利用纹线跟踪技术，沿纹线方向检测在阈值长度
  *		  T2内是否存在端点，若存在这样的端点，则该点是伪特征点，删除该
  *		  这两个端点之间像素点去除短纹。
  *		  (3)． 去除小环
  *		  小环是二值化图像模糊或在二值化纹线出现空洞引起的，在提取的细节特征
  *		  点表现为两个分叉点，因此，去除小环的算法如下：
  *		  依次选取所有的分叉点，利用纹线跟踪技术，沿纹线三个方向检测在阈
  *		  值长度T3内是否存在分叉点，若存在这样的分叉点，则该点是伪特征
  *		  点，去除这两个分叉点见的纹线。
  *		  (4)． 去除伪小桥
  *		  当采集样本手指在按压时用力不均匀，是的纹线之间相互粘连，形成伪
  *		  小桥。其在提取的细节特征点表现为两个分叉点，且这两个分叉点的连线与
  *		  其两个相邻的纹线几乎垂直。其消除算法如下：
  *		  依次选取所有的分叉点，利用纹线跟踪技术，沿纹线三个方向检测在阈
  *		  值长度T4内是否存在分叉点，若存在这样的分叉点，则该点是伪特征
  *		  点，去除这两个分叉点见的纹线。
  *		  (5)． 去除纹线的间断
  *		  当采集样本手指比较干的情况下，采集的指纹会出现纹线的间断，特征
  *		  点表现为两个不相连但是距离很近的端点。所以此时不能再用纹线跟踪技
  *		  术。此时，本文判断这两个端点连线的方向与端点所在小区阈纹线的方向差
  *		  是否为0或+-PI ，若是则这两个端点均为伪特征点，删除这两个伪特征点。
  *		  (6)． 去除指纹边缘处伪特征点
  *		  指纹图像边缘处的特征点大部分是伪特征点，这些短并非是纹线的终
  *		  点，而是由于图像大小有限使得一部分纹线无法显示造成的。去除这些特征
  *		  点的算法是一次选取所有的端点和分叉点，若其到边界的距离小于预先设定
  *		  的阈值，则该点为伪特征点，删除该点即可。
  *		2.精通Visual C++指纹模式识别系统算法及实现--李昊 (147-161)<2008年12月第一版>
*************************************************************************/
int32_t FPMinutiaSetExtractEndAndFork
(
 pFPMinutiaSet_t minutia,
 uint8_t *pSrc, 
 uint8_t *pOrientation, 
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch,
 //const int32_t r,
 //const int32_t ori_thr
 //const int32_t fixed_dis,
 //const int32_t var_dis,
 //const int32_t trace_len,
 //const int32_t trilen,
 //const int32_t rbackcolor,
 const int32_t forecolor,
 const int32_t backcolor,
 const int32_t bina_type
 );


/******************************************************************************
  * 功能：从细化图像中提取细节点，并储存到集合中。
  * 参数：minutia			细节点集合，用来保存细节点
  *		  pSrc				图像数据
  *       pOri				经过前后景分割的方向场
  *		  forecolor		    图像数据前景颜色(默认0)
  *		  backcolor		    图像数据背景景颜色(默认255)
  *		  rbackcolor		粗背景色颜色(指粗分割后非ROI区域的颜色)(默认255)
  *		  bina_type			图像二值类型1:(0,1)或其他:(0,255)(默认255)
  *		  width				图像数据宽度
  *		  height			图像数据高度
  *		  pitch				图像数据每行字节数
  * 返回：错误编号
  * 说明: 
  *		  1.获取奇异点(FPMinutiaSetExtractSingularity)
  *		  2.获取末梢点和分叉点(FPMinutiaSetExtractEndAndFork)
******************************************************************************/
FunError_t FPMinutiaSetExtract
(
 pFPMinutiaSet_t minutia,
 uint8_t *pSrc,
 uint8_t *pOri,
 const int32_t forecolor,
 const int32_t backcolor,
 const int32_t bina_type,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
);




void FPMinutiaSetDilateOZ
(
 uint8_t *pSrc,
 pFPMinutiaSet_t minutia,	
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 );








#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* __IMAGE_FEATURE_H */
