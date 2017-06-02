/******************************************************************************
 * 文件名：image_matching.h
 * 功  能：一些基本的图像匹配操作
******************************************************************************/

#if !defined __IMAGE_MATCHING_H
#define __IMAGE_MATCHING_H

#include "../../bsp/bsp_header/z_mytype.h"
#include "image_feature.h"


#ifdef __cplusplus
extern "C" {
#endif

//Hausdorff:经典HD,MHD,M-HD,PHD,LTS-HD,CHD
#define OHD		0	
#define MHD		1	
#define M_HD	2
#define PHD		3
#define LTS_HD	4
#define CHD		5


#define MATCH_SIMILARITY		50
#define MATCH_PERCENT			70


//typedef Handle_t PointSet_t;		//点集
typedef Handle_t MatchingSet_t;		//匹配集(点集,
//typedef Image_t  MatchingImage_t;	//匹配图像


typedef struct iMatchingSet_t { 
  int32_t   similarity; 
  int32_t   rotation; 
  int32_t   transX;
  int32_t   transY;
  int32_t	match_num;
} iMatchingSet_t, *pMatchingSet; 

/******************************************************************************
  * 功能：两幅同样(尺寸类型一致)图像的模版匹配
  * 参数：pSrc				匹配图像数据
  *		  pTmplt			模版图像数据
  *       match_percent		匹配度百分比(出口参数)
  *		  width				图像数据宽度
  *		  height			图像数据高度
  *		  pitch				图像数据每行字节数
  * 返回：错误编号
  * 说明: 
  * 算法:
******************************************************************************/
FunError_t ImageTemplateMatching
(
 uint8_t *pSrc,
 uint8_t *pTmplt,
 int32_t *match_percent,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
);

FunError_t ImageTemplateMatchingV1
(
 uint8_t *pSrc,
 uint8_t *pTmplt,
 int32_t *match_percent,
 int32_t r_x,
 int32_t step_x,
 int32_t r_y,
 int32_t step_y,
 int32_t angle,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 );


/******************************************************************************
  * 功能：两幅同样(尺寸类型一致)图像的模版匹配
  * 参数：pSrc				匹配图像数据
  *       minutia1			欲匹配图像提取的细节点
  *       minutiaT			模版图像的细节点
  *       size				细节点平移尺寸
  *       pm_type			暂时没用上
  *       match_percent		匹配百分比(出口参数)
  *		  width				图像数据宽度
  *		  height			图像数据高度
  *		  pitch				图像数据每行字节数
  * 返回：错误编号
  * 说明: 将模版图像的细节点膨胀后检测欲匹配图像上重合度,最后计算百分比
  * 算法: 通过移动摹本细节点,测试其在欲匹配图像上的重合度,找出平移细节点后
  *		  得到的所有重合度的最大值作为此模版图像对欲匹配图像的重合度,最后
  *		  计算出匹配百分比
******************************************************************************/
FunError_t ImagePointMatching
(
 uint8_t *pSrc,
 pFVMinutiaSet_t minutia, 
 pFVMinutiaSet_t minutiaT,
 const int32_t size,
 const int32_t pm_type,
 int32_t *match_percent,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
);


/******************************************************************************
  * 功能：计算单向Hausdorff距离(底层函数)
  * 参数：A			点集A
  *       B			点集B
  *       nA		点集A的点数
  *       nB		点集B的点数
  *       hd_type	各种计算Hausdorff距离的算法
  *       pos_aB	所有点到点集距离D_aB升序排序的第pos_aB个(取值0-nA)
  *					如:CHD算法
  *       pos_AB	所有点集到点集距离d_AB升序排序的第pos_AB个(取值0-nA),
  *					如:PHD,CHD,LTS-HD
  *       d_thr		点集到点集的阈值,若d_AB>d_thr,则令d_AB=d_thr,如M-HD
  * 返回：单向Hausdorff距离(h_AB)
  * 说明: pos_aB,pos_AB,d_thr这三个参数并对所有hd_type都有用的.比如d_thr就只对
  *		  M-HD算法有效.其他时候,它可以取任何值
  * 算法:
  *		  经典HD整体描述:
  *			已知两个点集A={a1,a2,...,anA},B={b1,b2,...,bnB},nA和nB分别是
  *			点集A,B中点的个数,则两个点集之间的HD距离定义为:
  *			H(A,B) = max(h(A,B),h(B,A))								(1)
  *			其中h(A,B) = max(min(||a-b||)) = max(D(a,B))			(2)
  *						 a(A b(B             a(A
  *				h(B,A) = max(min(||b-a||)) = max(D(b,A))			(3)
  *					     b(B a(A             b(B
  *			注解:x(X表示x属于X
  *				 d或d(a,b)表示点到点距离
  *				 D或D(a,B)表示点到点集距离
  *				 h或h(A,B)表示点集到点集距离
  *			式(1)称为双向HD,式(2),(3)分别称为从点集A到点集B和从点集B到点集A的
  *			单向HD.如果计算了单向HD就可以通过取两者的最大值得到双向HD了.
  *		  其他改进HD算法描述:
  *			PHD(Partial HD):
  *				将所有点到点集距离(D)从小到大排序,取第k个距离值作为PHD的单向HD(h)	
  *			CHD(Censored HD):
  *				首先将集合A中任意一点到集合B中所有点的距离(d)从小到大
  *				排序, 取第q个距离作为该点到集合B的距离, 
  *				然后将所有集合A中的点到集合B的距离(D)从小到大排序, 
  *				取第p个距离作为集合A到集合B的单向HD
  *			MHD(Modified HD):
  *				对所有点到点集的最小距离(D)求平均作为单向HD. 
  *				MHD可以有效抵抗噪声干扰,但抗遮掩和外点干扰的性能并不好
  *			M-HD(M-estimation HD):
  *				将超过固定设定阈值的点到点集的最小距离值赋予固定值,
  *				然后再取平均作为单向HD,以避免由于部分噪声像素点带来的偏差
  *			LTS-HD:
  *				将点到点集的距离排序, 取前h个的平均值作为单向HD, 
  *				对噪声、严重遮挡或者存在外点干扰的图像有较好的效果
  *			WHD:(Weighted HD):
  *				根据各点所在位置对图像匹配的不同重要性赋予不同的权值.
  *			其他算法:
  *				1.为减小噪声的干扰,还提出了用3x3的窗口将二值图像转换为灰度图像, 
  *				对灰度图像计算HD的方法;
  *				2.基于相似度加权的自适应HD算法等
  *		  算法步骤:根据经典HD的定义,计算HD主要分为3步:
  *			1.计算点到点的距离(d)
  *			2.计算点到点集的距离(D)
  *			3.计算点集到点集的距离(h)
  *		  各种改进算法的工作大多集中在步骤3,只有CHD对步骤2进行改进.
  *		  根据第3步的计算方法, 可以将 HD 的定义大体归纳为三种类型. 
  *			1)直接取某一个点到点集的距离值作为单向 HD, 如经典 HD、PHD和CHD等
  *			  该类方法由于过分依赖于某一单点到点集的距离值
  *			  因此容易受到噪声和遮挡的干扰, 鲁棒性差.
  *  		2)取某一部分点到点集的距离值计算单向HD, 如M-HD
  *			  和 LTS-HD. 由于被遮挡部分的点到点集的最小距
  *			  离受到干扰很大, 该类方法通过舍去比较大的点到
  *			  点集的最小距离值, 从而提高了存在遮挡时算法的鲁棒性. 		
  *  		3) 将多个点到点集的距离的平均值作为单向 HD, 
  *			  如MHD、LTS-HD、M-HD和WHD,取点到点集的平均最小距离是
  *			  抵抗噪声干扰的有效方法,增强了算法的鲁棒性.	 
  *			实际上, 取部分点到点集的最小距离和取点到点集的
  *		  平均最小距离是一对互相矛盾的做法. 取部分点到点集的距离
  *		  就是要尽可能地剔除干扰点, 但是在剔除干扰点的同时,
  *		  必然减少了可利用的点到点集最小距离的个数,
  *		  从而降低了算法的稳定性. 取点到点集的平均最小距离是另一个极端, 
  *		  它利用了所有点到点集的最小距离值, 尽可能保证算法的鲁棒性,
  *		  但是受到噪声和遮挡等干扰的点到点集的最小距离也被利用了, 	   
  *		  因此在计算精度上不能达到最优. 上面的分析用一句话概括就是: 
  *			取部分点到点集的最小距离是通过降低算法稳定性来换取计算精
  *		  度; 取点到点集的平均最小距离是通过降低计算精度来换取算法鲁棒性.
******************************************************************************/
static int32_t HausdorffDistanceLL
(
 Point_t *A, 
 Point_t *B, 
 const int32_t nA, 
 const int32_t nB,
 const int32_t hd_type,
 int32_t pos_aB,
 int32_t pos_AB,
 const int32_t d_thr
 );


/******************************************************************************
  * 功能：计算Hausdorff距离,调用底层HausdorffDistance函数
  * 参数：A			点集A
  *       B			点集B
  *       nA		点集A的点数
  *       nB		点集B的点数
  *		  hd_dir    计算双向或单向HD
  *       hd_type	各种计算Hausdorff距离的算法
  *       pos_aB	所有点到点集距离D_aB升序排序的第pos_aB个(取值0-nA)
  *					如:CHD算法
  *       pos_AB	所有点集到点集距离d_AB升序排序的第pos_AB个(取值0-nA),
  *					如:PHD,CHD,LTS-HD
  *       d_thr		点集到点集的阈值,若d_AB>d_thr,则令d_AB=d_thr,如M-HD
  * 返回：点集A和B的Hausdorff距离(h_AB)
  * 说明: pos_aB,pos_AB,d_thr这三个参数并对所有hd_type都有用的.比如d_thr就只对
  *		  M-HD算法有效.其他时候,它可以取任何值
  * 算法:
  *		  经典HD整体描述:
  *			已知两个点集A={a1,a2,...,anA},B={b1,b2,...,bnB},nA和nB分别是
  *			点集A,B中点的个数,则两个点集之间的HD距离定义为:
  *			H(A,B) = max(h(A,B),h(B,A))								(1)
  *			其中h(A,B) = max(min(||a-b||)) = max(D(a,B))			(2)
  *						 a(A b(B             a(A
  *				h(B,A) = max(min(||b-a||)) = max(D(b,A))			(3)
  *					     b(B a(A             b(B
  *			注解:x(X表示x属于X
  *				 d或d(a,b)表示点到点距离
  *				 D或D(a,B)表示点到点集距离
  *				 h或h(A,B)表示点集到点集距离
  *			式(1)称为双向HD,式(2),(3)分别称为从点集A到点集B和从点集B到点集A的
  *			单向HD.如果计算了单向HD就可以通过取两者的最大值得到双向HD了.
  *		  其他改进HD算法描述:
  *			PHD(Partial HD):
  *				将所有点到点集距离(D)从小到大排序,取第k个距离值作为PHD的单向HD(h)	
  *			CHD(Censored HD):
  *				首先将集合A中任意一点到集合B中所有点的距离(d)从小到大
  *				排序, 取第q个距离作为该点到集合B的距离, 
  *				然后将所有集合A中的点到集合B的距离(D)从小到大排序, 
  *				取第p个距离作为集合A到集合B的单向HD
  *			MHD(Modified HD):
  *				对所有点到点集的最小距离(D)求平均作为单向HD. 
  *				MHD可以有效抵抗噪声干扰,但抗遮掩和外点干扰的性能并不好
  *			M-HD(M-estimation HD):
  *				将超过固定设定阈值的点到点集的最小距离值赋予固定值,
  *				然后再取平均作为单向HD,以避免由于部分噪声像素点带来的偏差
  *			LTS-HD:
  *				将点到点集的距离排序, 取前h个的平均值作为单向HD, 
  *				对噪声、严重遮挡或者存在外点干扰的图像有较好的效果
  *			WHD:(Weighted HD):
  *				根据各点所在位置对图像匹配的不同重要性赋予不同的权值.
  *			其他算法:
  *				1.为减小噪声的干扰,还提出了用3x3的窗口将二值图像转换为灰度图像, 
  *				对灰度图像计算HD的方法;
  *				2.基于相似度加权的自适应HD算法等
  *		  算法步骤:根据经典HD的定义,计算HD主要分为3步:
  *			1.计算点到点的距离(d)
  *			2.计算点到点集的距离(D)
  *			3.计算点集到点集的距离(h)
  *		  各种改进算法的工作大多集中在步骤3,只有CHD对步骤2进行改进.
  *		  根据第3步的计算方法, 可以将 HD 的定义大体归纳为三种类型. 
  *			1)直接取某一个点到点集的距离值作为单向 HD, 如经典 HD、PHD和CHD等
  *			  该类方法由于过分依赖于某一单点到点集的距离值
  *			  因此容易受到噪声和遮挡的干扰, 鲁棒性差.
  *  		2)取某一部分点到点集的距离值计算单向HD, 如M-HD
  *			  和 LTS-HD. 由于被遮挡部分的点到点集的最小距
  *			  离受到干扰很大, 该类方法通过舍去比较大的点到
  *			  点集的最小距离值, 从而提高了存在遮挡时算法的鲁棒性. 		
  *  		3) 将多个点到点集的距离的平均值作为单向 HD, 
  *			  如MHD、LTS-HD、M-HD和WHD,取点到点集的平均最小距离是
  *			  抵抗噪声干扰的有效方法,增强了算法的鲁棒性.	 
  *			实际上, 取部分点到点集的最小距离和取点到点集的
  *		  平均最小距离是一对互相矛盾的做法. 取部分点到点集的距离
  *		  就是要尽可能地剔除干扰点, 但是在剔除干扰点的同时,
  *		  必然减少了可利用的点到点集最小距离的个数,
  *		  从而降低了算法的稳定性. 取点到点集的平均最小距离是另一个极端, 
  *		  它利用了所有点到点集的最小距离值, 尽可能保证算法的鲁棒性,
  *		  但是受到噪声和遮挡等干扰的点到点集的最小距离也被利用了, 	   
  *		  因此在计算精度上不能达到最优. 上面的分析用一句话概括就是: 
  *			取部分点到点集的最小距离是通过降低算法稳定性来换取计算精
  *		  度; 取点到点集的平均最小距离是通过降低计算精度来换取算法鲁棒性.
******************************************************************************/
int32_t HausdorffDistance
(
 Point_t *A, 
 Point_t *B, 
 const int32_t nA, 
 const int32_t nB,
 const int32_t hd_dir,
 const int32_t hd_type,
 int32_t pos_aB,
 int32_t pos_AB,
 const int32_t d_thr
 );


/******************************************************************************
  * 功能：计算两幅图像的特征点集的HD
  * 参数：minutiaA	特征点集A
  *       minutiaB	特征点集B
  *		  hd_dir    计算双向或单向HD
  *       hd_type	各种计算Hausdorff距离的算法
  *       pos_aB	所有点到点集距离D_aB升序排序的第pos_aB个(取值0-nA)
  *					如:CHD算法
  *       pos_AB	所有点集到点集距离d_AB升序排序的第pos_AB个(取值0-nA),
  *					如:PHD,CHD,LTS-HD
  *       d_thr		点集到点集的阈值,若d_AB>d_thr,则令d_AB=d_thr,如M-HD
  * 返回：两幅图像的特征点集的HD
  * 说明: pos_aB,pos_AB,d_thr这三个参数并对所有hd_type都有用的.比如d_thr就只对
  *		  M-HD算法有效.其他时候,它可以取任何值
******************************************************************************/
int ImageMinutiaHD
(
 pFVMinutiaSet_t minutiaA, 
 pFVMinutiaSet_t minutiaB, 
 const int32_t hd_dir,
 const int32_t hd_type,
 int32_t pos_aB,
 int32_t pos_AB,
 const int32_t d_thr
 );








/******************************************************************************
*******************************************************************************
************************下面的函数对指纹具有较强的适用性***********************
************************下面的函数对指纹具有较强的适用性***********************
************************下面的函数对指纹具有较强的适用性***********************
*******************************************************************************
******************************************************************************/


#define MATCH_MODE_FAST		1

#define CENTRAL_THR			60
//#define BOUND_BOX			10
#define BOUND_BOX			15
#define SIMI_THR			100
//#define ANGLE_THR			8
#define ANGLE_THR			15

extern int32_t  DisTbl[15][15];

/************************************************************************
  * 功能：图像特征点配准(旋转变换)
  * 参数：minutia			细节点集合
  *		  align_minutia		经过配准后的特征点集合[out]
  *		  coreXY			配准(旋转变换)中心点
  *		  rotation			旋转角度
  *		  transx			水平偏移
  *		  transy			垂直偏移
  * 返回：void
  * 说明: 将指纹特征按一定的角度和位置进行坐标变换配准运算,从而实现图像细节点
  *		  的配准,为下一步图像匹配和比对做好准备.
  *		  调用函数前注意要为align_minutia分配空间
  * 算法: 
*************************************************************************/
void MinutiaSetAlign
(
 pFPMinutiaSet_t minutia,
 pFPMinutiaSet_t align_minutia,
 Point_t coreXY, 
 int32_t rotation, 
 int32_t transx, 
 int32_t transy
 );


/************************************************************************
  * 功能：两个坐标系对齐的图像特征点进行匹配(比对)
  * 参数：minutiaA			经过配准的欲匹配细节点集合
  *		  minutiaT			匹配模版
  *		  pMatchResult		配准结果结构体指针
  *		  bound_box			界限盒大小
  *		  simi_thr			相似度阈值
  *		  match_mode		配准模式:1:快速模式
  * 返回：void
  * 说明: 将指纹特征按一定的角度和位置进行坐标变换配准运算,从而实现图像细节点
  *		  的配准,为下一步图像匹配和比对做好准备.
  *		  调用函数前注意要为align_minutia分配空间
  * 算法: 1.两个已经配准的图像进行匹配(比对)时,其相似度就是指两图像拓扑结构点比对
  *		  的一致程度.计算公式:
  *			similarity = 4*score*最大相似度*最大特征数/(总特征点数*总特征点数)
  *		    (1)分数是匹配特征点和样板上的对应特征点匹配成功的记录.匹配成功
  *		       就增加分数.分数由自己定义.如:设定A为夹角误差的允许的最大值(界限盒)
  *		       a为当前夹角.若a越大,分数应该最小.故分数=分数+(A-a)
  *		    (2)最大特征数:匹配图像设定的最大特征数
  *		    (3)总特征数:两个匹配图像特征点数总和
  *		  2.若相似度大于某个合格的阈值,则两图像相似.
  *		    注意,由于分数计算方法不一样,界限盒设置的方法(大小,固定,可变)
  *		  得到的相似度也不一样,合格阈值也不同.
  *		    界限盒模型:可分为固定的和可变的.这里采用固定界限盒bound_box=10
*************************************************************************/
void MinutiaSetAlignMatch
(
 pFPMinutiaSet_t minutiaA, 
 pFPMinutiaSet_t minutiaT, 
 pMatchingSet pMatchResult, 
 int32_t bound_box,
 int32_t simi_thr,
 int32_t match_mode
 );


/************************************************************************
  * 功能：中心点匹配
  * 参数：minutiaA			经过配准的欲匹配细节点集合
  *		  minutiaT			匹配模版
  *		  pMatchResult		配准结果结构体指针
  *		  bound_box			界限盒大小
  *		  simi_thr			相似度阈值
  *		  match_mode		配准模式:1:快速模式
  *		  pCoreA			匹配图像的中心点最特征点集中的位置
  *		  coreA_num			匹配图像的中心点个数
  *		  pCoreT			模版图像的中心点最特征点集中的位置
  *		  coreT_num			模版图像的中心点个数
  * 返回：void
  * 说明: 图像的"柔性"配准,即为一定范围内的大致配准
  *		  指纹图像的柔性配准方法有:局部配准(CenteralMatching),
  *       特殊点(CoreMatching,DeltaMatching)和全局配准(GlobalMatching),傅里叶法
  *		  特殊点法:包括中心点和三角点.寻找图像的特殊点,利用特殊点位置的偏移和旋转
  *				   对图像进行配准(MinutiaSetAlign)和匹配(MinutiaSetAlignMatch)
  *		  局部法:在规定的一定的图像中间区域为取点范围,分别取不同的点进行配准
  *				 和匹配.
  *		  全局法:在整幅图像,分别去不同的点进行配准和匹配.
  *		  
  * 算法: 1.根据两幅图像的特殊点计算配准的参数(偏移,旋转角度等)
  *		  2.对欲匹配特征点集合minutiaA进行配准(MinutiaSetAlign)
  *			得到配准后的特征点集align_minutia
  *		  3.对配准后的特征点集和模版进行匹配(MinutiaSetAlignMatch)
  *			计算匹配集合参数pMatchResult
  *		  4.遍历所有特殊点,找到最大的匹配集参数pMatchResult
*************************************************************************/
void CoreMatching
(
 pFPMinutiaSet_t minutiaA, 
 pFPMinutiaSet_t minutiaT, 
 pMatchingSet pMatchResult, 
 int32_t bound_box,
 int32_t simi_thr,
 int32_t match_mode,
 int32_t *pCoreA,
 int32_t coreA_num, 
 int32_t *pCoreT, 
 int32_t coreT_num 
 );


/************************************************************************
  * 功能：三角点匹配
  * 参数：minutiaA			经过配准的欲匹配细节点集合
  *		  minutiaT			匹配模版
  *		  pMatchResult		配准结果结构体指针
  *		  bound_box			界限盒大小
  *		  simi_thr			相似度阈值
  *		  match_mode		配准模式:1:快速模式
  *		  pDeltaA			匹配图像的三角点最特征点集中的位置
  *		  deltaA_num		匹配图像的三角点个数
  *		  pDeltaT			模版图像的三角点最特征点集中的位置
  *		  DeltaT_num		模版图像的三角点个数
  * 返回：void
  * 说明: 图像的"柔性"配准,即为一定范围内的大致配准
  *		  指纹图像的柔性配准方法有:局部配准(CenteralMatching),
  *       特殊点(CoreMatching,DeltaMatching)和全局配准(GlobalMatching),傅里叶法
  *		  特殊点法:包括中心点和三角点.寻找图像的特殊点,利用特殊点位置的偏移和旋转
  *				   对图像进行配准(MinutiaSetAlign)和匹配(MinutiaSetAlignMatch)
  *		  局部法:在规定的一定的图像中间区域为取点范围,分别取不同的点进行配准
  *				 和匹配.
  *		  全局法:在整幅图像,分别去不同的点进行配准和匹配.
  *		  
  * 算法: 1.根据两幅图像的特殊点计算配准的参数(偏移,旋转角度等)
  *		  2.对欲匹配特征点集合minutiaA进行配准(MinutiaSetAlign)
  *			得到配准后的特征点集align_minutia
  *		  3.对配准后的特征点集和模版进行匹配(MinutiaSetAlignMatch)
  *			计算匹配集合参数pMatchResult
  *		  4.遍历所有特殊点,找到最大的匹配集参数pMatchResult
*************************************************************************/
void DeltaMatching
(
 pFPMinutiaSet_t minutiaA, 
 pFPMinutiaSet_t minutiaT, 
 pMatchingSet pMatchResult, 
 int32_t bound_box,
 int32_t simi_thr,
 int32_t match_mode, 
 int32_t *pDeltaA,
 int32_t deltaA_num,
 int32_t *pDeltaT, 
 int32_t deltaT_num
 );


//计算两点间的距离
int32_t dist(int32_t x0, int32_t y0, int32_t x1, int32_t y1);


/************************************************************************
  * 功能：局部匹配
  * 参数：minutiaA			经过配准的欲匹配细节点集合
  *		  minutiaT			匹配模版
  *		  pMatchResult		配准结果结构体指针
  *		  bound_box			界限盒大小
  *		  simi_thr			相似度阈值
  *		  angle_thr			三角拓扑结构角度误差
  *		  central_thr		中心区域范围阈值
  *		  match_mode		配准模式:1:快速模式
  * 返回：void
  * 说明: 图像的"柔性"配准,即为一定范围内的大致配准
  *		  指纹图像的柔性配准方法有:局部配准(CenteralMatching),
  *       特殊点(CoreMatching,DeltaMatching)和全局配准(GlobalMatching),傅里叶法
  *		  特殊点法:包括中心点和三角点.寻找图像的特殊点,利用特殊点位置的偏移和旋转
  *				   对图像进行配准(MinutiaSetAlign)和匹配(MinutiaSetAlignMatch)
  *		  局部法:在规定的一定的图像中间区域为取点范围,分别取不同的点进行配准
  *				 和匹配.
  *		  全局法:在整幅图像,分别去不同的点进行配准和匹配.
  *		  
  * 算法: 1.根据两幅图像的特征点中心区域附近(CENTRALRADIUS)
  *			的任意两点计算配准的参数(偏移,旋转角度等)
  *		  2.对欲匹配特征点集合minutiaA进行配准(MinutiaSetAlign)
  *			得到配准后的特征点集align_minutia
  *		  3.对配准后的特征点集和模版进行匹配(MinutiaSetAlignMatch)
  *			计算匹配集合参数pMatchResult
  *		  4.遍历所有两幅图像的特征点中心区域附近的点,
  *			找到最大的匹配集参数pMatchResult
*************************************************************************/
void CentralMatching
(
 pFPMinutiaSet_t minutiaA, 
 pFPMinutiaSet_t minutiaT, 
 pMatchingSet pMatchResult, 
 int32_t bound_box,
 int32_t simi_thr,
 int32_t angle_thr,
 int32_t central_thr,
 int32_t match_mode
 );


/************************************************************************
  * 功能：全局匹配
  * 参数：minutiaA			经过配准的欲匹配细节点集合
  *		  minutiaT			匹配模版
  *		  pMatchResult		配准结果结构体指针
  *		  bound_box			界限盒大小
  *		  simi_thr			相似度阈值
  *		  angle_thr			三角拓扑结构角度误差
  *		  match_mode		配准模式:1:快速模式
  * 返回：void
  * 说明: 图像的"柔性"配准,即为一定范围内的大致配准
  *		  指纹图像的柔性配准方法有:局部配准(CenteralMatching),
  *       特殊点(CoreMatching,DeltaMatching)和全局配准(GlobalMatching),傅里叶法
  *		  特殊点法:包括中心点和三角点.寻找图像的特殊点,利用特殊点位置的偏移和旋转
  *				   对图像进行配准(MinutiaSetAlign)和匹配(MinutiaSetAlignMatch)
  *		  局部法:在规定的一定的图像中间区域为取点范围,分别取不同的点进行配准
  *				 和匹配.
  *		  全局法:在整幅图像,分别去不同的点进行配准和匹配.
  *		  
  * 算法: 1.根据两幅图像的特征点的任意两点计算配准的参数(偏移,旋转角度等)	
  *		  2.对欲匹配特征点集合minutiaA进行配准(MinutiaSetAlign)
  *			得到配准后的特征点集align_minutia
  *		  3.对配准后的特征点集和模版进行匹配(MinutiaSetAlignMatch)
  *			计算匹配集合参数pMatchResult
  *		  4.遍历所有两幅图像的特征点找到最大的匹配集参数pMatchResult	
*************************************************************************/
void  GlobalMatching
(
 pFPMinutiaSet_t minutiaA, 
 pFPMinutiaSet_t minutiaT, 
 pMatchingSet pMatchResult,
 int32_t bound_box,
 int32_t simi_thr,
 int32_t angle_thr,
 int32_t match_mode
 );


/************************************************************************
  * 功能：特征点集的匹配总函数
  * 参数：minutiaA			经过配准的欲匹配细节点集合
  *		  minutiaT			匹配模版
  *		  pMatchResult		配准结果结构体指针
  *		  bound_box			界限盒大小
  *		  simi_thr			相似度阈值
  *		  angle_thr			三角拓扑结构角度误差
  *		  central_thr		中心区域范围阈值
  *		  match_mode		配准模式:1:快速模式
  * 返回：void
  * 说明: 图像的"柔性"配准,即为一定范围内的大致配准
  *		  指纹图像的柔性配准方法有:局部配准(CenteralMatching),
  *       特殊点(CoreMatching,DeltaMatching)和全局配准(GlobalMatching),傅里叶法
  *		  特殊点法:包括中心点和三角点.寻找图像的特殊点,利用特殊点位置的偏移和旋转
  *				   对图像进行配准(MinutiaSetAlign)和匹配(MinutiaSetAlignMatch)
  *		  局部法:在规定的一定的图像中间区域为取点范围,分别取不同的点进行配准
  *				 和匹配.
  *		  全局法:在整幅图像,分别去不同的点进行配准和匹配.
  *		  
  * 算法: 分别调用中心点匹配(CoreMatching), 三角点匹配(DeltaMatching)
  *		  局部匹配(CentralMatching)和全局匹配(GlobalMatching)
*************************************************************************/
void  FPMinutiaSetMatching
(		  
 pFPMinutiaSet_t minutiaA, 
 pFPMinutiaSet_t minutiaT, 
 pMatchingSet pMatchResult, 
 int32_t bound_box,
 int32_t simi_thr,
 int32_t angle_thr,
 int32_t central_thr,
 int32_t match_mode
 );










#ifdef __cplusplus
}
#endif	/* extern "C" */

#endif /* __IMAGE_MATCHING_H */

