/******************************************************************************
 * 文件名：image_matching.c
 * 功  能：一些基本的图像匹配操作
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "dip_header/image_matching.h"
#include "dip_header/base_fun.h"

//#include "../../bsp/bsp_header/z_mytype.h"


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
//FunError_t ImageTemplateMatching
//(
// uint8_t *pSrc,
// uint8_t *pTmplt,
// int32_t *match_percent,
// const int32_t width, 
// const int32_t height, 
// const int32_t pitch
//)
//{	
//	int32_t x, y, count, percent, temp;
//	int32_t tempY;
//	uint8_t *pS, *pD;
//
//	count = 0;
//	percent = 0;
//	tempY = 0;
//	for (y = 0; y < height; y++) {
//		pS = pSrc + tempY;
//		pD = pTmplt + tempY;
//		for (x = 0; x < width; x++) {
//			count += *(pS + x);
//			percent += ((*(pS+x)) & (*(pD+x)));	
//		}
//		tempY += pitch;
//	}
//
//	temp = (percent*100)/count;
//	*(match_percent) = temp; 
//
//	//printf("匹配数:%d, 总数:%d, 匹配百分比:%d\n", percent, count, temp); 
//	return FunOK;
//}

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
 )
{	
	int32_t x, y, i, j, count, percent, temp, max_percent;
	//int32_t tempY;
	uint8_t *pS, *pD;
#if 0	
	int32_t k;
	double sinv, cosv;
	int32_t j1, i1;
	pS = pSrc;
	pD = pTmplt;
	max_percent = 0;
	for (k = -angle; k <= angle; k++) {
		sinv = sin(k*M_PI/180.0);
		cosv = cos(k*M_PI/180.0);
		for (j = -r_y; j <= r_y; j += step_y) {
			for (i = -r_x ; i <= r_x; i += step_x) {
				count = 0;
				percent = 0;
				for (y = 0; y < height; y++) {
					for (x = 0; x < width; x++) {
						j1 = (int32_t)((y+j)*cosv - (x+i)*sinv);
						i1 = (int32_t)((y+j)*sinv + (x+i)*cosv);
						if (j1 < 0 || j1 >= height || i1 < 0 || i1 >= width) {
							continue;
						}
						count += *(pS + j1*pitch + i1);
						percent += ((*(pS + j1*pitch + i1)) & (*(pD+y*pitch+x)));	
					}
				} 
				temp = (percent*100)/count;
				if (temp > max_percent) {
					max_percent = temp;
				}
			}
		}
	}
#endif

#if 1
	max_percent = 0;
	for (j = -r_y; j <= r_y; j += step_y) {
		for (i = -r_x ; i <= r_x; i += step_x) {
			count = 0;
			percent = 0;
			for (y = 0; y < height; y++) {
				if ((y+j)<0 || (y+j)>=height) {
					continue;
				}
				pS = pSrc + (y+j)*pitch;
				pD = pTmplt + y*pitch;
				for (x = 0; x < width; x++) {
					if ((x+i)<0 || (x+i)>=width) {
						continue;
					}
					count += *(pS + x + i);
					percent += ((*(pS+x+i)) & (*(pD+x)));	
				}
			} 
			temp = (percent*100)/count;
			if (temp > max_percent) {
				max_percent = temp;
			}
		}
	}
#endif

	*(match_percent) = max_percent; 

	//printf("匹配百分比:%d\n",  max_percent); 
	return FunOK;
}

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
//FunError_t ImagePointMatching
//(
// uint8_t *pSrc,
// pFVMinutiaSet_t minutia, 
// pFVMinutiaSet_t minutiaT,
// const int32_t size,
// const int32_t pm_type,
// int32_t *match_percent,
// const int32_t width, 
// const int32_t height, 
// const int32_t pitch
//)
//{
//	int32_t i , x, y, u, v;
//	int32_t r;
//	int32_t cnt_temp, cnt_max;	//交叉点匹配的数目临时值和最大值
//	int32_t percent;			//数据库端交叉点匹配的百分比
//	int32_t percentT;			//匹配端交叉点匹配的百分比
//	int32_t n, nT;				//特征点集A,B的点数 
//
//	r = size / 2;
//	//获取nA,nB,minutiaA->FPMinutiaArr,minB
//	n = minutia->nbminutia;
//	nT = minutiaT->nbminutia;
//
//	cnt_temp = 0;
//	cnt_max = 0;
//	percent = 0;
//	percentT = 0;
//
//	//计算,检测重合度
//	for (u=-r; u<=r; u++) {
//		for (v=-r; v<=r; v++) {
//			for (i=0; i<nT; i++) {
//				x = minutiaT->FVMinutiaArr[i].x + v;
//				y = minutiaT->FVMinutiaArr[i].y + u;
//				//防止越界
//				if (x < 0 || x >= width ||\
//					y < 0 || y >= height) {
//					continue;
//				}
//
//				if (pSrc[y*pitch + x] == 1) {
//					cnt_temp++;
//				}
//			}
//			if (cnt_temp>cnt_max) {
//				cnt_max = cnt_temp;
//			}
//			cnt_temp = 0;
//		}
//	}
//
//	//计算匹配度
//	cnt_max *= 100;
//	//计算数据库端和匹配段的匹配百分比
//	percent   = cnt_max / n;
//	percentT = cnt_max / nT;
//	//两边权重各一半
//	(*match_percent) = (percent>>1) + (percentT>>1);
//
//	return FunOK;
//}

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
//static int32_t HausdorffDistanceLL
//(
// Point_t *A, 
// Point_t *B, 
// const int32_t nA, 
// const int32_t nB,
// const int32_t hd_type,
// int32_t pos_aB,
// int32_t pos_AB,
// const int32_t d_thr
// )
//{
//	int32_t i, j, k;
//	int32_t dx, dy;
//	int32_t h_AB;
//	int32_t d_ab[FV_MAX_MINUTIA_NUM];
//	int32_t D_aB[FV_MAX_MINUTIA_NUM];
//	//int32_t *d_ab = (int32_t *)malloc(sizeof(int32_t)*nB);	//点到点的距离
//	//int32_t *D_aB = (int32_t *)malloc(sizeof(int32_t)*nA);	//点到点集的距离
//
//	//if (d_ab == NULL || D_aB == NULL) 
//	//	return -1;
//
//	//初始化数组为0
//	//for (i = 0; i < FV_MAX_MINUTIA_NUM; i++) {
//	//	d_ab[i] = 0;
//	//	D_aB[i] = 0;
//	//}
//
//	if (pos_aB >= nA) {
//		printf("pos_aB should be less than or equal to nA!\n");
//		pos_aB = nA - 1;
//	}
//	if (pos_AB >= nA) {
//		printf("pos_AB should be less than or equal to nA!\n");
//		pos_AB = nA - 1;
//	}
//
//	for (i = 0; i < nA; i++) {
//		//1.计算点到点的距离d_ab
//		for (j = 0; j < nB; j++) {
//			//加快运算,不求距离,求距离的平方
//			dx = A[i].x - B[j].x;
//			dy = A[i].y - B[j].y;
//			d_ab[j] = dx*dx + dy*dy;	
//		}
//		//2.计算点到点集的距离D_aB
//		if (hd_type == CHD) {					//CHD
//			my_sort((void*)d_ab, nB);
//			D_aB[i] = d_ab[pos_aB];
//		} else {
//			D_aB[i] = d_ab[0];
//			for (k = 1; k < nB; k++) {
//				if (d_ab[k] < D_aB[i])
//					D_aB[i] = d_ab[k];
//			}
//		}
//	}
//
//	//3.计算点集到点集的距离h_AB
//	h_AB = 0;
//	if (hd_type == OHD) {						//经典HD算法
//		h_AB = D_aB[0];
//		for (k = 1; k < nA; k++) {	//所有点到点集D_aB中最大值作为h_AB			
//			if (D_aB[k] > h_AB)
//				h_AB = D_aB[k];
//		}
//	} else if (hd_type == MHD) {				//MHD
//		//h_AB = 0;
//		for (k = 0; k < nA; k++) {	//所有点到点集D_aB的平均值作为h_AB
//			h_AB += D_aB[k];
//		}
//		h_AB /= nA;
//	} else if (hd_type == M_HD) {				//M-HD
//		//h_AB = 0;
//		for (k = 0; k < nA; k++) {	//所有点到点集D_aB的平均值作为h_AB
//			if (D_aB[k] > d_thr)	//超出设定阈值的赋予固定值(阈值)
//				D_aB[k] = d_thr;
//			h_AB += D_aB[k];
//		}
//		h_AB /= nA;
//	} else if (hd_type == PHD) {				//PHD
//		//h_AB = 0;
//		my_sort((void*)D_aB, nA);	//所有点到点集D_aB的从小到大排序后的
//		h_AB = D_aB[pos_AB];		//第pos_AB个值作为h_AB
//	} else if (hd_type == LTS_HD) {				//LTS-HD
//		//h_AB = 0;
//		my_sort((void*)D_aB, nA);
//		for (k = 0; k <= pos_AB; k++) {	//所有点到点集D_aB的从小到大排序的
//			h_AB += D_aB[k];			//前pos_AB个值的平均值作为h_AB
//		}
//		h_AB /= (pos_AB+1);
//	} else if (hd_type == CHD) {				//CHD
//		//h_AB = 0;
//		my_sort((void*)D_aB, nA);	//所有点到点集D_aB的从小到大排序后的
//		h_AB = D_aB[pos_AB];		//第pos_AB个值作为h_AB
//	} else {								//其他,使用经典HD
//		h_AB = D_aB[0];
//		for (k = 1; k < nA; k++) {
//			if (D_aB[k] > h_AB)
//				h_AB = D_aB[k];
//		}
//	}
//
//	//if (d_ab != NULL) {
//	//	free(d_ab);
//	//	d_ab = NULL;
//	//}
//	//if (D_aB != NULL) {
//	//	free(D_aB);
//	//	D_aB = NULL;
//	//}
//
//	return h_AB;
//
//}

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
//int32_t HausdorffDistance
//(
// Point_t *A, 
// Point_t *B, 
// const int32_t nA, 
// const int32_t nB,
// const int32_t hd_dir,
// const int32_t hd_type,
// int32_t pos_aB,
// int32_t pos_AB,
// const int32_t d_thr
// )
//{
//	int32_t h_AB, h_BA;
//	
//	if (hd_dir == 1) {	//单向
//		h_AB = HausdorffDistanceLL(A, B, nA, nB, hd_type, pos_aB, pos_AB, d_thr);
//	} else {
//		h_AB = HausdorffDistanceLL(A, B, nA, nB, hd_type, pos_aB, pos_AB, d_thr);
//		h_BA = HausdorffDistanceLL(B, A, nB, nA, hd_type, pos_aB, pos_AB, d_thr);
//
//		if (h_AB < h_BA)
//			h_AB = h_BA;
//	}
//
//	return h_AB;
//}

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
//int32_t ImageMinutiaHD
//(
// pFVMinutiaSet_t minutiaA, 
// pFVMinutiaSet_t minutiaB, 
// const int32_t hd_dir,
// const int32_t hd_type,
// int32_t pos_aB,
// int32_t pos_AB,
// const int32_t d_thr
// )
//{
//	int32_t H_AB = 0, k;
//	int32_t nA, nB;					//特征点集A,B的点数 
//	//Point_t *A, *B;					//点集A,B
//	Point_t A[FV_MAX_MINUTIA_NUM];
//	Point_t B[FV_MAX_MINUTIA_NUM];
//	//获取nA,nB,minutiaA->FPMinutiaArr,minB
//	nA = minutiaA->nbminutia;
//	nB = minutiaB->nbminutia;
//
//	//为A,B分配空间
//	//A = (Point_t *)malloc(sizeof(Point_t) * nA);
//	//B = (Point_t *)malloc(sizeof(Point_t) * nB);
//
//	//初始化数组为0
//	//for (k = 0; k < FV_MAX_MINUTIA_NUM; k++) {
//	//	A[k].x = 0;
//	//	A[k].y = 0;
//	//	B[k].x = 0;
//	//	B[k].y = 0;
//	//}
//
//	//初始化点集A,B
//	for (k = 0; k < nA; k++) {
//		A[k].x = minutiaA->FVMinutiaArr[k].x;
//		A[k].y = minutiaA->FVMinutiaArr[k].y;
//	}
//	for (k = 0; k < nB; k++) {
//		B[k].x = minutiaB->FVMinutiaArr[k].x;
//		B[k].y = minutiaB->FVMinutiaArr[k].y;
//	}
//
//	//计算HD
//	H_AB = HausdorffDistance(A, B, nA, nB, hd_dir, hd_type, pos_aB, pos_AB, d_thr);
//
//	printf("the HD of MinutiaSet A&B is: %d\n", H_AB);
//
//	//if (A != NULL) {
//	//	free(A);
//	//	A = NULL;
//	//}
//	//if (B != NULL) {
//	//	free(B);
//	//	B = NULL;
//	//}
//	
//	return H_AB;
//}






/******************************************************************************
*******************************************************************************
************************下面的函数对指纹具有较强的适用性***********************
************************下面的函数对指纹具有较强的适用性***********************
************************下面的函数对指纹具有较强的适用性***********************
*******************************************************************************
******************************************************************************/


// 为节省时间，短距离的两点间距离采用查表法
int32_t  DisTbl[15][15] = {
	0, 1, 2, 3, 4, 5, 6,   7,  8,  9, 10,  11, 12, 13, 14,
	1, 1, 2, 3, 4, 5, 6,   7,  8,  9, 10,  11, 12, 13, 14,
	2, 2, 2, 3, 4, 5, 6,   7,  8,  9, 10,  11, 12, 13, 14,
	3, 3, 3, 4, 5, 5, 6,   7,  8,  9, 10,  11, 12, 13, 14,
	4, 4, 4, 5, 5, 6, 7,   8,  8,  9, 10,  11, 12, 13, 14,
	5, 5, 5, 5, 6, 7, 7,   8,  9, 10, 11,  12, 13, 13, 14,
	6, 6, 6, 6, 7, 7, 8,   9, 10, 10, 11,  12, 13, 14, 15,  
	7, 7, 7, 7, 8, 8, 9,   9, 10, 11, 12,  13, 14, 15, 16, 
	8, 8, 8, 8, 8, 9, 10, 10, 11, 12, 12,  13, 14, 15, 16, 
	9, 9, 9, 9, 9, 10,10, 11, 12, 12, 13,  14, 15, 15, 16,
	10,10,10,10,10,11,11, 12, 12, 13, 14,  14, 15, 16, 17,
	11,11,11,11,11,12,12, 13, 13, 14, 14,  15, 16, 17, 17,
	12,12,12,12,12,13,13, 14, 14, 15, 15,  16, 16, 17, 18,
	13,13,13,13,13,13,14, 15, 15, 15, 16,  17, 17, 18, 19,
	14,14,14,14,14,14,15, 16, 16, 16, 17,  17, 18, 19, 19
};


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
 )
{
	int32_t i;
	int32_t x, y, angle;
	int32_t cx, cy;
	double rota, sinv, cosv;
	int32_t min_num;			//特征点集数目

	min_num = minutia->nbminutia;

	//获取配准后的特征点集合的指针及其数目
	align_minutia->nbminutia = min_num;

	//坐标转换的中心点坐标
	cx = coreXY.x;
	cy = coreXY.y;
	//旋转的弧度
	rota = rotation/M_EPI;
	//旋转弧度的sin值
	sinv = sin(rota);
	//旋转弧度的cos值
	cosv = cos(rota);
	
	//计算配准(旋转变化)后的参数
	for (i = 0; i < min_num; i++) {
		//x = min[i].x;
		//y = min[i].y;
		//angle = min[i].angle;
		//坐标转换后的新坐标
		//旋转后特征点的新方向
		//align_min->ptable[i].x = (int32_t)(cx + cosv*(x-cx) - sinv*(y-cy) + transx + 0.5);
		//align_min->ptable[i].y = (int32_t)(cy + sinv*(x-cx) + cosv*(y-cy) + transy + 0.5);
		//align_min->ptable[i].angle = (angle + rotation) % 360;
		//align_min->ptable[i].type = min[i].type;
		//align_min->ptable[i].triangle[0] = min[i].triangle[0];
		//align_min->ptable[i].triangle[1] = min[i].triangle[1];
		//align_min->ptable[i].triangle[2] = min[i].triangle[2];


		x = minutia->FPMinutiaArr[i].x;
		y = minutia->FPMinutiaArr[i].y;
		angle = minutia->FPMinutiaArr[i].angle;

		//坐标转换后的新坐标
		//旋转后特征点的新方向
		align_minutia->FPMinutiaArr[i].x = (int32_t)(cx + cosv*(x-cx) - sinv*(y-cy) + transx + 0.5);
		align_minutia->FPMinutiaArr[i].y = (int32_t)(cy + sinv*(x-cx) + cosv*(y-cy) + transy + 0.5);
		align_minutia->FPMinutiaArr[i].angle = (angle + rotation) % 360;
		align_minutia->FPMinutiaArr[i].type = minutia->FPMinutiaArr[i].type;
		align_minutia->FPMinutiaArr[i].triangle[0] = minutia->FPMinutiaArr[i].triangle[0];
		align_minutia->FPMinutiaArr[i].triangle[1] = minutia->FPMinutiaArr[i].triangle[1];
		align_minutia->FPMinutiaArr[i].triangle[2] = minutia->FPMinutiaArr[i].triangle[2];

	}

}

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
 )
{
	int32_t	i, j;
	uint8_t flagA[FP_MAX_MINUTIA_NUM];	//标记minutiaA中特征点是否已经有匹配对象
	uint8_t flagT[FP_MAX_MINUTIA_NUM];	//标记minutiaT中特征点是否已经有匹配对象

	int32_t	x1, y1, x2, y2;
	int32_t dis, angle;
	int32_t score, match_num, s;
	//int32_t step = 1;

	int32_t minA_num, minT_num;
	//Minutia_t *minutiaA->FPMinutiaArr,*minutiaT->FPMinutiaArr;		//特征点集A,B


	//minA_num = MinutiaSetGetCount(minutiaA);
	//minutiaA->FPMinutiaArr = MinutiaSetGetBuffer(minutiaA);
	//minT_num = MinutiaSetGetCount(minutiaT);
	//minutiaT->FPMinutiaArr = MinutiaSetGetBuffer(minutiaT);
	minA_num = minutiaA->nbminutia;
	minT_num = minutiaT->nbminutia;

	//标记清零
	//memset(flagA, 0, FP_MAX_MINUTIA_NUM);
	//memset(flagT, 0, FP_MAX_MINUTIA_NUM);
	for (i = 0; i < FP_MAX_MINUTIA_NUM; i++) {
		flagA[i] = 0;
		flagT[i] = 0;
	}

	score = 0;		//总分清零
	match_num = 0;	//匹配特征点数清零

	//相同类型特征点的匹配分数
	for (i = 0; i < minT_num; i++) {
		if(flagT[i])			//是否已有匹配对象
			continue;
		for (j = 0; j < minA_num; j++) {
			if(flagA[j])		//是否已有匹配对象
				continue;

			//特征点类型是否相同
			if (minutiaT->FPMinutiaArr[i].type != minutiaA->FPMinutiaArr[j].type)
				continue;

			//特征点方向夹角
			angle = GetAngle180In360(minutiaT->FPMinutiaArr[i].angle, minutiaA->FPMinutiaArr[j].angle);
			//夹角>=10则不匹配
			if(angle >= bound_box)
				continue;

			x1 = minutiaT->FPMinutiaArr[i].x;
			y1 = minutiaT->FPMinutiaArr[i].y;
			x2 = minutiaA->FPMinutiaArr[j].x;
			y2 = minutiaA->FPMinutiaArr[j].y;
			//水平距离>=10则不匹配
			if(abs(x1-x2) >= bound_box)
				continue;
			//垂直距离>=10则不匹配
			if(abs(y1-y2) >= bound_box)
				continue;
			//两特征点间的距离
			dis = DisTbl[abs(y1-y2)][abs(x1-x2)];
			//dis = (int32_t)sqrt((double)((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
			//距离>=10则不匹配
			if(dis >= bound_box)
				continue;

			//对这两个特征点做标记，表示已经有匹配对象
			flagA[j] = 1;
			flagT[i] = 1;

			//总分加上此两个特征点的匹配分数
			//此表明dis,angle越大，分数越小
			score += (bound_box-angle);
			score += (bound_box-dis);

			//匹配特征点数加一
			match_num++;
			
			//如果是快速比对模式
			if (match_mode == MATCH_MODE_FAST && match_num >= 8) {
				//计算相似度
				s = 4 * score * match_num * FP_MAX_MINUTIA_NUM / ((minA_num + minT_num) * ( minA_num + minT_num));
				//if (s > 100) {			//相似度足够大则返回比对结果
				if (s > simi_thr) {			//相似度足够大则返回比对结果
					pMatchResult->match_num = match_num;
					pMatchResult->rotation = 0;
					pMatchResult->similarity = s;
					pMatchResult->transX = 0;
					pMatchResult->transX = 0;
					return;
				}
			}
		}
	}

	//非快速匹配模式
	if (match_mode != MATCH_MODE_FAST) {
		//由于图像处理的误差导致可能端点处理成叉点或叉点处理成端点
		//假设概率为50%，计算此种情况的分数
		for(i = 0; i < minT_num; i++) {
			if(flagT[i])		//是否已有匹配对象
				continue;
			for(j = 0; j < minA_num; j++) {
				if(flagA[j])	//是否已有匹配对象
					continue;

				//是否类型不同
				if(minutiaT->FPMinutiaArr[i].type == minutiaA->FPMinutiaArr[j].type)
					continue; 

				//特征点方向夹角
				angle = GetAngle180In360(minutiaT->FPMinutiaArr[i].angle, minutiaA->FPMinutiaArr[j].angle);
				//夹角>=10则不匹配
				if(angle >= bound_box)
					continue;

				x1 = minutiaT->FPMinutiaArr[i].x;
				y1 = minutiaT->FPMinutiaArr[i].y;
				x2 = minutiaA->FPMinutiaArr[j].x;
				y2 = minutiaA->FPMinutiaArr[j].y;
				//水平距离>=10则不匹配
				if(abs(x1-x2) >= bound_box)
					continue;
				//垂直距离>=10则不匹配
				if(abs(y1-y2) >= bound_box)
					continue;
				//两特征点间的距离
				dis = DisTbl[abs(y1-y2)][abs(x1-x2)];
				//dis = (int32_t)sqrt((double)((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
				//距离>=10则不匹配
				if(dis >= bound_box)
					continue;

				//对这两个特征点做标记，表示已经有匹配对象
				flagA[j] = 1;
				flagT[i] = 1;
				//总分加上此两个特征点的匹配分数
				score += ((bound_box-angle)/2);
				score += ((bound_box-dis)/2);
				// 匹配特征点数加一
				match_num++;

			}
		}								
	}

	//计算相似度，返回比对结果
	s = 4 * score * match_num * FP_MAX_MINUTIA_NUM / ((minA_num+minT_num)*(minA_num+minT_num));

	pMatchResult->match_num = match_num;
	pMatchResult->rotation = 0;
	pMatchResult->similarity = s;
	pMatchResult->transX = 0;
	pMatchResult->transX = 0;
}


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
 )
{
	int32_t i, j;
	int32_t rotation;
	//int32_t  num = 0;

	int32_t transx, transy;
	int32_t n, m;
	int32_t nn, mm;			//匹配图像和模版图像的中心点总个数

	iMatchingSet_t align_max;			//相似度最大的比对结果
	iMatchingSet_t g_match_result;		//最终比对结果
	FPMinutiaSet_t align_minutia;		//配准后的细节点集合
	int32_t minA_num, minT_num;
	Point_t temp_core;

	minA_num = minutiaA->nbminutia;
	minT_num = minutiaT->nbminutia;

	//初始化最好的比对结果
	align_max.similarity = 0;
	align_max.match_num = 0;
	align_max.rotation = 0;
	align_max.transX = 0;
	align_max.transY = 0;

	//将中心点点特征两两作为同一个特征进行对齐比对
	for (nn = 0; nn < coreT_num; nn++) {
		for (mm = 0; mm < coreA_num; mm++) {
	
			n = pCoreT[nn];	//获取中心点在细节点集合中的位置
			m = pCoreA[mm];	//获取中心点在细节点集合中的位置

			//位置偏移
			transx = (minutiaT->FPMinutiaArr[n].x - minutiaA->FPMinutiaArr[m].x);
			transy = (minutiaT->FPMinutiaArr[n].y - minutiaA->FPMinutiaArr[n].y);

			for (i = 0; i < minA_num; i++) {
				for (j = 0; j < minT_num; j++) {
					
					//若为中心点或三角点,跳过
					if (minutiaA->FPMinutiaArr[i].type == MinutiaTypeCore || \
						minutiaT->FPMinutiaArr[j].type == MinutiaTypeCore)
						continue;
					if (minutiaA->FPMinutiaArr[i].type == MinutiaTypeDelta || \
						minutiaT->FPMinutiaArr[j].type == MinutiaTypeDelta)
						continue;
					
					//计算配准(旋转变换)角度
					rotation = XY2Angle(minutiaT->FPMinutiaArr[j].x, minutiaT->FPMinutiaArr[j].y, minutiaA->FPMinutiaArr[i].x, minutiaA->FPMinutiaArr[i].y);
					
					//计算配准(旋转变换)中心点
					temp_core.x = minutiaA->FPMinutiaArr[i].x;
					temp_core.y = minutiaA->FPMinutiaArr[i].y;
					
					//对欲匹配图像进行配准minutiaA-->align_minutia
					MinutiaSetAlign(minutiaA, &align_minutia, temp_core, rotation, transx, transy);

					//将两个对齐的align_minutia和minutiaT特征进行匹配(比对)
					MinutiaSetAlignMatch(&align_minutia, minutiaT, &g_match_result,
						bound_box, simi_thr, match_mode);
						 

					//如果比对结果比最好的比对结果更好，则更新align_max
					if (g_match_result.similarity > align_max.similarity) {
						align_max.match_num = g_match_result.match_num;
						align_max.similarity = g_match_result.similarity;
						align_max.rotation = rotation;
						align_max.transX = transx;
						align_max.transY = transy;
						
						//如果是快速比对模式，则相似度达到一定程度则退出
						if (match_mode == MATCH_MODE_FAST && \
							align_max.match_num >= 8) {
							//if (align_max.similarity > 100) {
							if (align_max.similarity > simi_thr) {
								*pMatchResult = align_max;

								//释放为配准后的细节点集合分配空间
								//MinutiaSetDestroy(align_minutia);
								return;
							}
						}
					}
				}
			}
		}
	}


	//最终比对结果
	*pMatchResult = align_max;
}


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
 )
{
	//int32_t num = 0;
	int32_t n, m;
	int32_t nn, mm;		//匹配图像和模版图像的三角点总个数
	int32_t i, j;
	int32_t rotation;
	int32_t transx, transy;

	iMatchingSet_t align_max;			//相似度最大的比对结果
	iMatchingSet_t g_match_result;		//最终比对结果
	FPMinutiaSet_t align_minutia;		//配准后的细节点集合

	int32_t minA_num, minT_num;
	Point_t temp_core;

	minA_num = minutiaA->nbminutia;
	minT_num = minutiaT->nbminutia;

	//初始化最好的比对结果
	align_max.similarity = 0;
	align_max.match_num = 0;
	align_max.rotation = 0;
	align_max.transX = 0;
	align_max.transY = 0;


	//将三角点特征两两作为同一个特征进行对齐比对
	for (nn = 0; nn < deltaT_num; nn++) {
		for (mm = 0; mm < deltaA_num; mm++) {
	
			n = pDeltaT[nn];	//获取三角点在细节点集合中的位置
			m = pDeltaA[mm];	//获取三角点在细节点集合中的位置
	
			//位置偏移
			transx = (minutiaT->FPMinutiaArr[n].x - minutiaA->FPMinutiaArr[m].x);
			transy = (minutiaT->FPMinutiaArr[n].y - minutiaA->FPMinutiaArr[n].y);

			for (i = 0; i < minA_num; i++) {
				for (j = 0; j < minT_num; j++) {
								
					//若为中心点或三角点,跳过
					if (minutiaA->FPMinutiaArr[i].type == MinutiaTypeCore || \
						minutiaT->FPMinutiaArr[j].type == MinutiaTypeCore) 
						continue;

					if (minutiaA->FPMinutiaArr[i].type == MinutiaTypeDelta || \
						minutiaT->FPMinutiaArr[j].type == MinutiaTypeDelta) 
						continue;
	
					//计算配准(旋转变换)角度
					rotation = XY2Angle(minutiaA->FPMinutiaArr[i].x, minutiaA->FPMinutiaArr[i].y, minutiaT->FPMinutiaArr[j].x, minutiaT->FPMinutiaArr[j].y);
					
					//计算配准(旋转变换)中心点
					temp_core.x = minutiaA->FPMinutiaArr[i].x;
					temp_core.y = minutiaA->FPMinutiaArr[i].y;

					//对欲匹配图像进行配准minutiaA-->align_minutia
					MinutiaSetAlign(minutiaA, &align_minutia, temp_core, rotation, transx, transy);
					//将两个对齐的align_minutia和minutiaT特征进行匹配(比对)
					MinutiaSetAlignMatch(&align_minutia, minutiaT,&g_match_result,  
						bound_box, simi_thr, match_mode);

					//如果比对结果比最好的比对结果更好，则更新align_max
					if (g_match_result.similarity > align_max.similarity) {
						align_max.match_num = g_match_result.match_num;
						align_max.similarity = g_match_result.similarity;
						align_max.rotation = rotation;
						align_max.transX = transx;
						align_max.transY = transy;
						
						//如果是快速比对模式，则相似度达到一定程度则退出
						if (match_mode == MATCH_MODE_FAST && \
							align_max.match_num >= 8) {
							//if (align_max.similarity > 100) {
							if (align_max.similarity > simi_thr) {
								*pMatchResult = align_max;

								//释放为配准后的细节点集合分配空间
								//MinutiaSetDestroy(align_minutia);
								return;
							}
						}
					}
				}
			}
		}
	}

	//最终比对结果
	*pMatchResult = align_max;

}


//计算两点间的距离
int32_t dist(int32_t x0, int32_t y0, int32_t x1, int32_t y1)
{
	return (int32_t)sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
}


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
 )
{
	int32_t	m, n, a1, a2;
	int32_t	rotation;		//旋转角度
	int32_t	transx, transy;	//位置偏移

	//int32_t  num = 0;
	int32_t nx, ny;			//细节点中心坐标
	int32_t mx, my;			//细节点中心坐标
	int32_t Counter;

	iMatchingSet_t align_max;			//相似度最大的比对结果
	iMatchingSet_t g_match_result;		//最终比对结果
	FPMinutiaSet_t align_minutia;			//配准后的细节点集合

	int32_t minA_num, minT_num;
	Point_t temp_core;


	minA_num = minutiaA->nbminutia;
	minT_num = minutiaT->nbminutia;

	// 初始化最好的比对结果
	align_max.similarity = 0;
	align_max.match_num = 0;
	align_max.rotation = 0;
	align_max.transX = 0;
	align_max.transY = 0;

	//计算细节点中心坐标
	nx = 0;
	ny = 0;
	for (n = 0; n < minT_num; n++) {
		nx += minutiaT->FPMinutiaArr[n].x;
		ny += minutiaT->FPMinutiaArr[n].y;
	}
	nx = nx / minT_num;
	ny = ny / minT_num;

	mx = 0;
	my = 0;
	for (m = 0; m < minA_num; m++) {
		mx += minutiaA->FPMinutiaArr[m].x;
		my += minutiaA->FPMinutiaArr[m].y;
	}
	mx = mx / minA_num;
	my = my / minA_num;


	Counter = 0;

	//将相同类型的特征两两作为同一个特征进行对齐比对
	for (n = 0; n < minT_num; n++) {

		//超出中心区域范围阈值的点舍弃
		if (dist(nx, ny, minutiaT->FPMinutiaArr[n].x, minutiaT->FPMinutiaArr[n].y) > central_thr) 
			continue;

		for (m = 0; m < minA_num; m++) {

			//若为中心点或三角点,跳过
			if (minutiaA->FPMinutiaArr[m].type == MinutiaTypeCore || \
				minutiaT->FPMinutiaArr[n].type == MinutiaTypeCore)
				continue;

			if (minutiaA->FPMinutiaArr[m].type == MinutiaTypeDelta || \
				minutiaT->FPMinutiaArr[n].type == MinutiaTypeDelta)
				continue;

			//不同类型则不比对
			if (minutiaA->FPMinutiaArr[m].type != minutiaT->FPMinutiaArr[n].type)
				continue;

			//超出中心区域范围阈值的点舍弃
			if (dist(mx, my, minutiaA->FPMinutiaArr[m].x, minutiaA->FPMinutiaArr[m].y) > central_thr) 
				continue;

			Counter++;

			if (match_mode == MATCH_MODE_FAST) {
				//特征点三角拓扑结构比对，相似则进行配准
				if (minutiaA->FPMinutiaArr[m].triangle[0] != 255 && \
					minutiaT->FPMinutiaArr[n].triangle[0] != 255) {

					a1 = GetAngle90In180(minutiaA->FPMinutiaArr[m].triangle[0], minutiaA->FPMinutiaArr[m].angle % 180);
					a2 = GetAngle90In180(minutiaT->FPMinutiaArr[n].triangle[0], minutiaT->FPMinutiaArr[n].angle % 180);
					if (abs(a1-a2) > angle_thr)
						continue;
				}
				if (minutiaA->FPMinutiaArr[m].triangle[0] != 255 && \
					minutiaT->FPMinutiaArr[n].triangle[0] != 255 && \
					minutiaA->FPMinutiaArr[m].triangle[1] != 255 && \
					minutiaT->FPMinutiaArr[n].triangle[1] != 255) {

					a1 = GetAngle90In180(minutiaA->FPMinutiaArr[m].triangle[0], minutiaA->FPMinutiaArr[m].triangle[1]);
					a2 = GetAngle90In180(minutiaT->FPMinutiaArr[n].triangle[0], minutiaT->FPMinutiaArr[n].triangle[1]);
					if (abs(a1-a2) > angle_thr)
						continue;
				}

				if (minutiaA->FPMinutiaArr[m].triangle[2] != 255 && \
				    minutiaT->FPMinutiaArr[n].triangle[2] != 255 && \
				    minutiaA->FPMinutiaArr[m].triangle[1] != 255 && \
				    minutiaT->FPMinutiaArr[n].triangle[1] != 255) {

					a1 = GetAngle90In180(minutiaA->FPMinutiaArr[m].triangle[1], minutiaA->FPMinutiaArr[m].triangle[2]);
					a2 = GetAngle90In180(minutiaT->FPMinutiaArr[n].triangle[1], minutiaT->FPMinutiaArr[n].triangle[2]);
					if (abs(a1-a2) > angle_thr)
						continue;
				}

				if (minutiaA->FPMinutiaArr[m].triangle[0] != 255 && \
					minutiaT->FPMinutiaArr[n].triangle[0] != 255 && \
					minutiaA->FPMinutiaArr[m].triangle[2] != 255 && \
					minutiaT->FPMinutiaArr[n].triangle[2] != 255) {

					a1 = GetAngle90In180(minutiaA->FPMinutiaArr[m].triangle[0], minutiaA->FPMinutiaArr[m].triangle[2]);
					a2 = GetAngle90In180(minutiaT->FPMinutiaArr[n].triangle[0], minutiaT->FPMinutiaArr[n].triangle[2]);
					if (abs(a1-a2) > angle_thr)
						continue;
				}
			}

			//alignFeature.MinutiaNum = 0;

			//计算配准(旋转变换)角度
			rotation = GetAngle360In360(minutiaA->FPMinutiaArr[m].angle, minutiaT->FPMinutiaArr[n].angle);

			//计算配准偏移
			transx = (minutiaT->FPMinutiaArr[n].x - minutiaA->FPMinutiaArr[m].x);
			transy = (minutiaT->FPMinutiaArr[n].y - minutiaA->FPMinutiaArr[m].y);
			
			//计算配准(旋转变换)中心点
			temp_core.x = minutiaA->FPMinutiaArr[m].x;
			temp_core.y = minutiaA->FPMinutiaArr[m].y;
	
			//对欲匹配图像进行配准minutiaA-->align_minutia
			MinutiaSetAlign(minutiaA, &align_minutia, temp_core, rotation, transx, transy);

			//将两个对齐的align_minutia和minutiaT特征进行匹配(比对)
			MinutiaSetAlignMatch(&align_minutia, minutiaT, &g_match_result, 
				 bound_box, simi_thr, match_mode);

			//如果比对结果比最好的比对结果更好，则更新align_max
			if (g_match_result.similarity > align_max.similarity) {
				align_max.match_num = g_match_result.match_num;
				align_max.similarity = g_match_result.similarity;
				align_max.rotation = rotation;
				align_max.transX = transx;
				align_max.transY = transy;
				
				// 如果是快速比对模式，则相似度达到一定程度则退出
				if (match_mode == MATCH_MODE_FAST && \
					align_max.match_num >= 8 ) {
					
					//if (align_max.similarity > 100) {
					if (align_max.similarity > simi_thr) {
						*pMatchResult = align_max;

						//释放为配准后的细节点集合分配空间
						//MinutiaSetDestroy(align_minutia);
						return;
					}
				}
			}
		}
	}
	
	//最终比对结果
	*pMatchResult = align_max;
}


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
 )
{
	int32_t	m, n, a1, a2;
	int32_t	rotation;		//旋转角度
	int32_t	transx, transy;	//位置偏移
	//int32_t  num = 0;

	iMatchingSet_t align_max;			//相似度最大的比对结果
	iMatchingSet_t g_match_result;		//最终比对结果
	FPMinutiaSet_t align_minutia;			//配准后的细节点集合
	//iMinutiaSet_t *palign;

	int32_t minA_num, minT_num;
	Point_t temp_core;

	minA_num = minutiaA->nbminutia;
	minT_num = minutiaT->nbminutia;

	// 初始化最好的比对结果
	align_max.similarity = 0;
	align_max.match_num = 0;
	align_max.rotation = 0;
	align_max.transX = 0;
	align_max.transY = 0;


	//将相同类型的特征两两作为同一个特征进行对齐比对
	for (n = 0; n < minT_num; n++) {
		for (m = 0; m < minA_num; m++) {

			//若为中心点或三角点,跳过
			if (minutiaA->FPMinutiaArr[m].type == MinutiaTypeCore || \
				minutiaT->FPMinutiaArr[n].type == MinutiaTypeCore)
				continue;

			if (minutiaA->FPMinutiaArr[m].type == MinutiaTypeDelta || \
				minutiaT->FPMinutiaArr[n].type == MinutiaTypeDelta)
				continue;

			//不同类型则不比对
			if (minutiaA->FPMinutiaArr[m].type != minutiaT->FPMinutiaArr[n].type)
				continue;

			if (match_mode == MATCH_MODE_FAST) {
				//特征点三角拓扑结构比对，相似则进行配准
				if (minutiaA->FPMinutiaArr[m].triangle[0] != 255 && \
					minutiaT->FPMinutiaArr[n].triangle[0] != 255) {

					a1 = GetAngle90In180(minutiaA->FPMinutiaArr[m].triangle[0], minutiaA->FPMinutiaArr[m].angle % 180);
					a2 = GetAngle90In180(minutiaT->FPMinutiaArr[n].triangle[0], minutiaT->FPMinutiaArr[n].angle % 180);
					if (abs(a1-a2) > angle_thr)
						continue;
				}
				if (minutiaA->FPMinutiaArr[m].triangle[0] != 255 && \
					minutiaT->FPMinutiaArr[n].triangle[0] != 255 && \
					minutiaA->FPMinutiaArr[m].triangle[1] != 255 && \
					minutiaT->FPMinutiaArr[n].triangle[1] != 255) {

					a1 = GetAngle90In180(minutiaA->FPMinutiaArr[m].triangle[0], minutiaA->FPMinutiaArr[m].triangle[1]);
					a2 = GetAngle90In180(minutiaT->FPMinutiaArr[n].triangle[0], minutiaT->FPMinutiaArr[n].triangle[1]);
					if (abs(a1-a2) > angle_thr)
						continue;
				}
				if (minutiaA->FPMinutiaArr[m].triangle[2] != 255 && \
					minutiaT->FPMinutiaArr[n].triangle[2] != 255 && \
					minutiaA->FPMinutiaArr[m].triangle[1] != 255 && \
					minutiaT->FPMinutiaArr[n].triangle[1] != 255) {

					a1 = GetAngle90In180(minutiaA->FPMinutiaArr[m].triangle[1], minutiaA->FPMinutiaArr[m].triangle[2]);
					a2 = GetAngle90In180(minutiaT->FPMinutiaArr[n].triangle[1], minutiaT->FPMinutiaArr[n].triangle[2]);
					if (abs(a1-a2) > angle_thr)
						continue;
				}
				if (minutiaA->FPMinutiaArr[m].triangle[0] != 255 && \
					minutiaT->FPMinutiaArr[n].triangle[0] != 255 && \
					minutiaA->FPMinutiaArr[m].triangle[2] != 255 && \
					minutiaT->FPMinutiaArr[n].triangle[2] != 255) {

					a1 = GetAngle90In180(minutiaA->FPMinutiaArr[m].triangle[0], minutiaA->FPMinutiaArr[m].triangle[2]);
					a2 = GetAngle90In180(minutiaT->FPMinutiaArr[n].triangle[0], minutiaT->FPMinutiaArr[n].triangle[2]);
					if (abs(a1-a2) > angle_thr)
						continue;
				}
			}
			//alignFeature.MinutiaNum = 0;
			//palign->nbminutia = 0;
			
			//计算配准(旋转变换)角度
			rotation = GetAngle360In360(minutiaA->FPMinutiaArr[m].angle, minutiaT->FPMinutiaArr[n].angle);
			//计算配准偏移
			transx = (minutiaT->FPMinutiaArr[n].x - minutiaA->FPMinutiaArr[m].x);
			transy = (minutiaT->FPMinutiaArr[n].y - minutiaA->FPMinutiaArr[m].y);	
			//计算配准(旋转变换)中心点
			temp_core.x = minutiaA->FPMinutiaArr[m].x;
			temp_core.y = minutiaA->FPMinutiaArr[m].y;
			
			//对欲匹配图像进行配准minutiaA-->align_minutia
			MinutiaSetAlign(minutiaA, &align_minutia, temp_core, rotation, transx, transy);

			//将两个对齐的align_minutia和minutiaT特征进行匹配(比对)
			MinutiaSetAlignMatch(&align_minutia, minutiaT, &g_match_result, 
				 bound_box, simi_thr, match_mode);

			//如果比对结果比最好的比对结果更好，则更新align_max
			if (g_match_result.similarity > align_max.similarity) {
				align_max.match_num = g_match_result.match_num;
				align_max.similarity = g_match_result.similarity;
				align_max.rotation = rotation;
				align_max.transX = transx;
				align_max.transY = transy;
				
				//如果是快速比对模式，则相似度达到一定程度则退出
				if (match_mode == MATCH_MODE_FAST && \
					align_max.match_num >= 8) {
					//if (align_max.similarity > 100) {
					if (align_max.similarity > simi_thr) {
						*pMatchResult = align_max;

						return;
					}
				}
			}
		}
	}
	
	//最终比对结果
	*pMatchResult = align_max;
}


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
 )
{

	//细节点集合中的中心点和三角点位置存储和数目存储
	int32_t CoreA[FP_MAX_SINGULARYTY_NUM];
	int32_t CoreT[FP_MAX_SINGULARYTY_NUM];
	int32_t DeltaA[FP_MAX_SINGULARYTY_NUM];
	int32_t DeltaT[FP_MAX_SINGULARYTY_NUM];
	int32_t coreA_num;
	int32_t coreT_num;
	int32_t deltaA_num;
	int32_t deltaT_num;

	int32_t n, m;

	int32_t minA_num, minT_num;

	minA_num = minutiaA->nbminutia;
	minT_num = minutiaT->nbminutia;

	//获取细节点集合中的中心点和三角点位置存储和数目存储
	coreA_num = 0;
	deltaA_num = 0;
	for (n = 0; n < FP_MAX_SINGULARYTY_NUM; n++) {
		CoreA[n] = 0;
		CoreT[n] = 0;
		DeltaA[n] = 0;
		DeltaT[n] = 0;
	}

	for (n = 0; n < minA_num; n++) {
		if (minutiaA->FPMinutiaArr[n].type == MinutiaTypeCore) {
			CoreA[coreA_num] = n;
			coreA_num++;
		}

		if (minutiaA->FPMinutiaArr[n].type == MinutiaTypeDelta) {
			DeltaA[deltaA_num] = n;
			deltaA_num++;
		}
	}

	coreT_num = 0;
	deltaT_num = 0;
	for (m = 0; m < minT_num; m++) {
		if (minutiaT->FPMinutiaArr[m].type == MinutiaTypeCore) {
			CoreT[coreT_num] = m;
			coreT_num++;
		}

		if (minutiaT->FPMinutiaArr[m].type == MinutiaTypeDelta) {
			DeltaT[deltaT_num] = m;
			deltaT_num++;
		}
	}

	//中心点匹配
	if (coreA_num > 0 && coreT_num > 0) {
		CoreMatching(minutiaA, minutiaT, pMatchResult, bound_box, simi_thr,
			match_mode, CoreA, coreA_num, CoreT, coreT_num);

		// 如果是快速比对模式，则相似度达到一定程度则退出
		if (match_mode == MATCH_MODE_FAST && \
			pMatchResult->match_num >= 8) {
			//if (pMatchResult->similarity > 100) {		
			if (pMatchResult->similarity > simi_thr) {	
				return;
			}
		}
	}

	//三角点匹配
	if (deltaA_num > 0 && deltaT_num > 0) {
		DeltaMatching(minutiaA, minutiaT, pMatchResult, bound_box, simi_thr,
			match_mode, DeltaA, deltaA_num, DeltaT, deltaT_num);

		//如果是快速比对模式，则相似度达到一定程度则退出
		if (match_mode == MATCH_MODE_FAST && pMatchResult->match_num >= 8) {
			//if (pMatchResult->similarity > 100) {		
			if (pMatchResult->similarity > simi_thr) {				
				return;
			}
		}
	} 

	//区域匹配
	CentralMatching(minutiaA, minutiaT, pMatchResult, bound_box, simi_thr,
		angle_thr, central_thr, match_mode);
	if (match_mode == MATCH_MODE_FAST && \
		pMatchResult->match_num >= 8) {
		//if (pMatchResult->similarity > 100) {
		if (pMatchResult->similarity > simi_thr) {				
			return;
		}
	}

	//全局匹配	
	GlobalMatching(minutiaA, minutiaT, pMatchResult, bound_box, simi_thr, angle_thr, match_mode);
	
}

