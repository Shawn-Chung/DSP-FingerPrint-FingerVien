/******************************************************************************
 * 文件名：image_miscellaneous.c
 * 功  能：一些基本的图像操作
******************************************************************************/


#include "dip_header/image_miscellaneous.h"
//#include "../../bsp/bsp_header/z_mytype.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#undef  P
#define P(x, y)   p[(x) + (y)*pitch]
/************************************************************************
* 功能：对骨架图像进行扫描并标记
* 参数：p         指向源图像数据区
*       pitch     每像素所占字节数
*       x         端点x坐标(种子点x坐标)
*		  y         端点y坐标(种子点y坐标)
*       part_num  当前扫描块的编号
*       part_area 用来记录联通区域大小的计数器
*       area_thr  用来判断终止条件的,当计数器的值大于阈值area_thr时则终止当前扫描
* 返回：void
* 说明: 输入图像数据为二值数据(0,1),且图像是骨骼化后的
*       输入的(x,y)坐标是骨骼化图像的端点坐标
* 算法: 
*       1.从输入的种子点坐标(x,y)开始进行扫描,
*       2.计算种子点8邻域和连通面积记录并进行如下:
*         (1)超出连通面积的终止条件area_thr
*         (2)是端点
*			(3)挨着交叉点的点
*         (4)种子点是交叉点
*         如果满足上面的要求,则退出迭代,否则,进入3
*       3.寻找下一个方向,并将此方向的点作为下一个种子点,返回步骤1
*       4.不断迭代,直到终止条件.(终止条件为2中的几个条件)
*************************************************************************/
//void SkeletonBurrMarkOZ
//(
// uint8_t *p,
// const int32_t pitch,
// const int32_t   x,
// const int32_t   y,
// const int32_t   part_num, //连通区域的编号
// uint8_t *part_area,  //返回值，记录联通区域的大小
// const int32_t   area_thr
// )
//{
//	static int32_t x1,x2,x3,x4,x5,x6,x7,x8;
//	static int32_t temp1,temp2;
//
//	//1.从输入的种子点坐标(x,y)开始进行扫描
//	//直接判断是否为0,巧妙避开了标记后点的值不为(0,1)二值,
//	//与ImageConditionThiningOZ函数里面对标记的处理有异曲同工之妙
//	x1=((P(x+1, y  )==0)?0:1); //x1
//	x2=((P(x+1, y+1)==0)?0:1); //x2
//	x3=((P(x  , y+1)==0)?0:1); //x3
//	x4=((P(x-1, y+1)==0)?0:1); //x4
//	x5=((P(x-1, y  )==0)?0:1); //x5
//	x6=((P(x-1, y-1)==0)?0:1); //x6
//	x7=((P(x  , y-1)==0)?0:1); //x7
//	x8=((P(x+1, y-1)==0)?0:1); //x8
//
//	//2.计算种子点8邻域和连通面积记录
//	temp1=x1+x2+x3+x4+x5+x6+x7+x8;
//
//	/*temp2=abs(x1-x2)+abs(x2-x3)+abs(x3-x4)+abs(x4-x5)+
//	abs(x5-x6)+abs(x6-x7)+abs(x7-x8)+abs(x8-x1);*/	//适用细化和完全细化???
//	temp2=(x1&x2)+(x2&x3)+(x3&x4)+(x4&x5)+
//		(x5&x6)+(x6&x7)+(x7&x8)+(x8&x1);					//适用完全细化???
//
//
//	//(4).如果是交叉点,不需继续进行标记扫描,也不标记,因为这个交叉点
//	//与端点组成的可能是一条静脉延伸出来的一小段毛刺,是要去除的.
//	if((temp1>=3) && (temp2==0)){ 
//		return;		//4.不断迭代,直到终止条件.(终止条件为2中的几个条件)
//	}
//
//	++(*part_area);	   //记录骨架长度
//	P(x, y)=part_num;  //标记该点。
//
//	/*
//	//是另一个端点。
//	if((temp1==1)&&(*part_area)>1){
//	return;
//	}
//	//是挨着交叉点的点
//	if(temp1>=3&&temp2!=0){
//	return;
//	}
//	//超过了一定的阈值则退出。
//	if(*part_area>area_thr){
//	return;
//	}*/
//
//	//(1).骨架长度超过阈值,不需继续进行标记扫描.这条线足够长,最后会被删除
//	//(2).与交叉点挨着的点,不需继续进行标记扫描(注意此点被标记),最后会被删除.此处功能与4相同
//	//(3).是另一个端点,不需继续进行标记扫描,此时属于小于阈值的孤立小线段,最后会被删除
//	//步骤压缩，以让编译器产生短路检测代码
//	if(((*part_area) > area_thr) ||\
//		((temp1>=3) && (temp2!=0)) ||\
//		((temp1==1) && ((*part_area)>1))) {	
//			return;		//4.不断迭代,直到终止条件.(终止条件为2中的几个条件)
//	}
//
//	//3.寻找下一个方向,并将此方向的点作为下一个种子点,返回步骤1
//	//普通点，取出下一个搜索方向。
//	x1=((P(x+1, y  )==1)?1:0); //x1
//	x2=((P(x+1, y+1)==1)?1:0); //x2
//	x3=((P(x  , y+1)==1)?1:0); //x3
//	x4=((P(x-1, y+1)==1)?1:0); //x4
//	x5=((P(x-1, y  )==1)?1:0); //x5
//	x6=((P(x-1, y-1)==1)?1:0); //x6
//	x7=((P(x  , y-1)==1)?1:0); //x7
//	x8=((P(x+1, y-1)==1)?1:0); //x8
//	//计算方向
//	temp1=(x8<<7)|(x7<<6)|(x6<<5)|(x5<<4)|(x4<<3)|(x3<<2)|(x2<<1)|x1;
//
//	if(temp1==0){
//		return;//下一个点已经被标记。
//	}
//	//根据方向对下一个点进行扫描
//	switch(temp1){
//	case 0x01: SkeletonBurrMarkOZ(p, pitch, x+1, y  , part_num, part_area, area_thr);
//		break;
//	case 0x02: SkeletonBurrMarkOZ(p, pitch, x+1, y+1, part_num, part_area, area_thr);
//		break;
//	case 0x04: SkeletonBurrMarkOZ(p, pitch, x  , y+1, part_num, part_area, area_thr);
//		break;
//	case 0x08: SkeletonBurrMarkOZ(p, pitch, x-1, y+1, part_num, part_area, area_thr);
//		break;
//	case 0x10: SkeletonBurrMarkOZ(p, pitch, x-1, y  , part_num, part_area, area_thr);
//		break;
//	case 0x20: SkeletonBurrMarkOZ(p, pitch, x-1, y-1, part_num, part_area, area_thr);
//		break;
//	case 0x40: SkeletonBurrMarkOZ(p, pitch, x  , y-1, part_num, part_area, area_thr);
//		break;
//	case 0x80: SkeletonBurrMarkOZ(p, pitch, x+1, y-1, part_num, part_area, area_thr);
//		break;
//	default:printf("SkeletonBurrMarkOZ发生错误，迭代次数%d\n",*part_area);
//		//	break;
//	}
//}


/************************************************************************
* 功能：对扫描标记后的骨架图像进行清除毛刺
* 参数：p         指向源图像数据区
*       w         图像宽度
*		  h         图像高度
*       pitch     每像素所占字节数
*       part_area 用来记录联通区域大小的计数器
*       area_thr  用来判断终止条件的,当计数器的值大于阈值area_thr时则终止当前扫描
* 返回：void
* 说明: 输入图像数据为二值数据(0,1),且图像是骨骼化后的
*       输入的(x,y)坐标是骨骼化图像的端点坐标
*************************************************************************/
//void SkeletonBurrClearOZ
//(
// uint8_t *p,
// const int32_t   w,
// const int32_t   h,
// const int32_t   pitch,
// uint8_t *part_area,
// const int32_t   area_thr 
// )
//{
//	int32_t x,y;
//	for(y=0;y<h;y++){
//		for(x=0;x<w;x++){
//			switch(P(x, y))
//			{
//			case 0:
//			case 1:
//				break;
//			default:
//				P(x, y)=part_area[P(x, y)]>area_thr?1:0;
//			}//end switch
//		}//end for ( j=0...
//	}//end for ( i=0...
//}


/************************************************************************
* 功能：清除图像孤立点
* 参数：p         指向源图像数据区
*       w         图像宽度
*		  h         图像高度
* 返回：void
* 说明: 输入图像数据为二值数据(0,1)
*************************************************************************/
//void RemoveAcnode
//(
// uint8_t *p,
// const int32_t   w,
// const int32_t   h,
// const int32_t   pitch
// )
//{
//	int32_t x, y;
//	int32_t x1, x2, x3, x4, x5, x6, x7, x8;
//	int32_t temp1;
//	for (y = 1; y < h-1; y++) {
//		for (x = 1; x < w-1; x++) {
//			x1=P(x  , y+1); 
//			x2=P(x+1, y+1); 
//			x3=P(x+1, y  ); 
//			x4=P(x+1, y-1); 
//			x5=P(x  , y-1); 
//			x6=P(x-1, y-1); 
//			x7=P(x-1, y  ); 
//			x8=P(x-1, y+1); 
//			temp1 = (x1|x2|x3|x4|x5|x6|x7|x8);
//			P(x, y) = (P(x, y) & temp1);
//		}
//	}
//}

/******************************************************************************
  * 功能：4邻域连通区域填充
  * 参数：pSrc			图像数据指针(图像为二值图像)
  *       width			输入图像宽度
  *       height			输入图像高度
  *       pitch			输入图像每行字节个数
  *       x				种子点x坐标
  *       y				种子点y坐标
  *       end_area		判断终止条件,为0时完全填充,其他值时,若>end_area就停止填充
  *       mark_gary		使用此值标记生长区域的灰度值
  * 返回：填充区域的面积
  * 说明: 图像为二值图像,但不一定要是0,1二值
  * 算法:
  *       1.先判断(x,y)坐标颜色类型是否为color_type且是否已填充为mark_gary,
  *         是退出,否进入步骤2
  *       2.从第i=y行开始,自左向右(j=0~width)做个像素进行扫描,判断扫描的
  *		  当前点是否已填充为mark_gary,若不是,继续步骤2,扫描下一点.若是,进入步骤3
  *       3.判断当前的4邻域内是否有点与种子点是同一类型(temp_color)且没有标记,若否
  *         进入步骤2.若是进入步骤4
  *       4.标记4邻域的点为mark_gray,且区域面积++.同时判断4邻域的点是否在第i行前,
  *         若否,什么不做.若是,更新yMin和bNew标记.在本行i扫描完毕后,使i=yMin-1.
******************************************************************************/
int32_t FourNeighbor
(
 uint8_t *pSrc,
 const int32_t width,
 const int32_t height,
 const int32_t pitch,
 const int32_t x,
 const int32_t y,
 const int32_t color_type,
 const int32_t end_area,
 const uint8_t mark_gray
 )
{
	uint8_t *pS;
	int32_t i, j, k;
	int32_t yMin, tempy, bNew;
	int32_t temp_color;
	int32_t tempI;
	int32_t region_area = 0; //连通域面积

	//左,左上,上,上右...
	//int32_t	SiteD4[4] = {-1, -pitch, 1, pitch};
	int32_t SiteD4[4];
	SiteD4[0] = -1;	SiteD4[1] = -pitch;	SiteD4[2] = 1;	SiteD4[3] = pitch;

	//保存种子点的颜色值
	temp_color = pSrc[y*pitch+x];
	
	//1.先判断(x,y)坐标颜色类型是否为color_type且是否已填充为mark_gary
	if ((temp_color == color_type) && temp_color != mark_gray) {
		pSrc[y*pitch+x] = mark_gray;
	} else {
		return region_area;
	}

	region_area = 1;

	//2.从第i=y行开始,自左向右(j=0~width)做个像素进行扫描,判断扫描的
	//当前点是否已填充为mark_gary
	for (i = y; i < height; i++) {
		bNew = 0;
        yMin = i;
		tempI = i*pitch;
		pS = pSrc + tempI;
		for (j = 0; j < width; j++) {
			if ((*(pS+j) == mark_gray)) {
				for (k = 0; k < 4; k++) {
					//防止越界
					if ((tempI+j+SiteD4[k]) < 0 || \
						(tempI+j+SiteD4[k]) > ((width)*(height))) {
							continue;
					}

					//3.判断当前的8邻域内是否有点与种子点是同一类型(color_type)
					//且没有标记
					if (((*(pS+j+SiteD4[k])) == color_type) && \
						((*(pS+j+SiteD4[k])) != mark_gray)) {

						//4.标记8邻域的点为mark_gray,且区域面积++.
						//同时判断8邻域的点是否在第i行前
						(*(pS+j+SiteD4[k])) = mark_gray;
						region_area++;

						if ((end_area != 0) && (region_area > end_area)) {
							return region_area;
						}

						tempy = (tempI+j+SiteD4[k]) / pitch;
						if (tempy <= yMin) {
							yMin = tempy;
							if(bNew == 0) {
								bNew = 1;
							}
						}
					}			
				}
			}
		}

		if(bNew) {
			i= yMin - 1;
        }
	}

	return region_area;

}

/******************************************************************************
  * 功能：图像数据连通区域标记
  * 参数：
  *		  pSrc			图像数据指针(图像为二值图像)
  *		  region_num	连通区域编号数组(数组的元素值对应改编号区域大小)
  *       width			输入图像宽度
  *       height		输入图像高度
  *       pitch			输入图像每行字节个数
  * 返回：
  * 说明: 标记的区域编号从2开始,其中原图数据为0的值变为偶数编号(2,4,...)
  *		  原图数据为1的值变为奇数编号(3,5,...)
  *		  一般根据最后region_num调用RegionAreaFilter函数进行小区域去噪处理
  * 算法: 1.对图像数据自左向右,自上向下逐点扫描并调用8邻域(4邻域)填充函数进行标记
  *		  2.根据标记值对图像数据自左向右,自上向下逐点扫描并记录到region_num数组中
******************************************************************************/
void RegionMarkOZ
(
 uint8_t *pSrc,
 int32_t *region_num,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 )
{
	int32_t x, y;
	uint8_t *pS;
	//int32_t k;
	int32_t tempY = 0;
	int32_t mark_num1, mark_num2;
	mark_num1 = 3;
	mark_num2 = 2;

	//1.对图像数据自左向右,自上向下逐点扫描并调用8邻域(4邻域)填充函数进行标记
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			if (*(pSrc+y*pitch+x) == 1) {
				//EightNeighbor(pSrc, width, height, pitch, x, y, 0, mark_num1);
				FourNeighbor(pSrc, width, height, pitch, x, y, 1, 0, mark_num1);
				mark_num1+=2;
			}
			if (*(pSrc+y*pitch+x) == 0) {
				//EightNeighbor(pSrc, width, height, pitch, x, y, 0, mark_num2);
				FourNeighbor(pSrc, width, height, pitch, x, y, 0, 0, mark_num2);
				mark_num2+=2;
			}
		}
	}

	//2.根据标记值对图像数据自左向右,自上向下逐点扫描并记录到region_num数组中
	tempY = 0;
	for (y = 0; y < height; y++) {
		pS = pSrc + tempY;
		for (x = 0; x < width; x++) {
			region_num[*(pS+x)]++;
		}
		tempY += pitch;
	}
}

/******************************************************************************
  * 功能：图像数据区域去噪处理
  * 参数：
  *		  pSrc			经过标记的图像数据
  *		  region_num	连通区域编号数组(数组的元素值对应改编号区域大小)
  *		  fore_area_thr	前景色区域阈值
  *		  back_area_thr	背景色区域阈值
  *       width			输入图像宽度
  *       height		输入图像高度
  *       pitch			输入图像每行字节个数
  * 返回：
  * 说明: 
******************************************************************************/
void RegionAreaFilter
(
 uint8_t *pSrc,
 int32_t *region_num,
 const int32_t fore_area_thr,
 const int32_t back_area_thr,
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch 
 )
{
	int32_t x, y;
	int32_t tempY;
	tempY = 0;
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			switch (pSrc[tempY+x]) {
			case 0:
			case 1:
				//pSrc[tempY+x] = 0;
				break;
			default:
				if (pSrc[tempY+x]&0x01) {	//连通区域>fore_area_thr则设为1
					pSrc[tempY+x] = ((region_num[pSrc[tempY+x]] > fore_area_thr) ? 1 : 0);
				} else {	//连通区域<back_area_thr则设为1
					pSrc[tempY+x] = ((region_num[pSrc[tempY+x]] < back_area_thr) ? 1 : 0);
				}
				break;
			}
		}
		tempY += pitch;
	}
}




/******************************************************************************
*******************************************************************************
************************下面的函数对指纹具有较强的适用性***********************
************************下面的函数对指纹具有较强的适用性***********************
************************下面的函数对指纹具有较强的适用性***********************
*******************************************************************************
******************************************************************************/



/************************************************************************
  * 功能：寻找当前点的下一有效点,被SkeletonBurrClearV1等调用
  * 参数：pNow				当前点的地址[In]
  *		  width				前驱点的地址[In]
  *		  ppNext			下一个点的地址的指针[Out]
  *		  width				图像数据宽度
  *		  height			图像数据高度
  *		  pitch				图像数据每行字节数
  *		  forecolor		    图像数据前景颜色
  *		  backcolor		    图像数据背景颜色
  * 返回：0:正确找到.1:没找到或找到多个
  * 说明: 被SkeletonBurrClearV1调用,被image_feature中的很多函数调用
*************************************************************************/
int32_t GetNext
(
 uint8_t *pNow, 
 uint8_t *pLast, 
 uint8_t **ppNext, 
 //const int32_t width, 
 //const int32_t height, 
 const int32_t pitch,
 const int32_t forecolor
 )
{
	int32_t i;
	uint8_t *pS = NULL;
	int32_t n;
	uint8_t *Temp[8];	// 某点周围8个点的地址
	//int32_t	SiteD8[8] = {pitch-1, pitch, pitch+1, 1, -pitch+1, -pitch, -pitch-1, -1};

	int32_t SiteD8[8];
	SiteD8[0] = pitch-1;	SiteD8[1] = pitch;		SiteD8[2] = pitch+1;
	SiteD8[3] = 1;			SiteD8[4] = 1-pitch;	SiteD8[5] = -pitch;
	SiteD8[6] = -pitch-1;	SiteD8[7] = -1;
	
	*ppNext = NULL;

	//找到当前点周围的是黑点(前景点)并且不是前驱点的黑点(前景点)，保存到数组
	n = 0;
	for(i = 0; i < 8; i++) {
		pS = pNow + SiteD8[i];
		//if(*pS == 0 && pS != pLast) {
		if(*pS == forecolor && pS != pLast) {
			Temp[n] = pS;
			n++;
		}
	}

	if(n == 0) {		// 没有找到其他黑点则表示没有后继点
		*ppNext = NULL;
		return 1;
	} else if(n == 1) {	// 找到了一个，则其为后继点
		*ppNext = Temp[0];
		return 0;
	} else {			// 找到多个点则返回错误
		*ppNext = NULL;
		return 1;
	}

	//return 0;
}

/************************************************************************
  * 功能：判断所在点是否为交叉点,被SkeletonBurrClearV1等调用
  * 参数：pNow				当前点的地址[In]
  *		  width				图像数据宽度
  *		  height			图像数据高度
  *		  pitch				图像数据每行字节数
  *		  bina_type			图像二值类型1:(0,1)或其他:(0,255)
  * 返回：若为交叉点,返回1.	其他返回0
  * 说明: 被SkeletonBurrClearV1调用,被image_feature中的很多函数调用
*************************************************************************/
int32_t IsFork
(
 uint8_t *pNow, 
 //const int32_t width, 
 //const int32_t height, 
 const int32_t pitch,
 const int32_t bina_type
 )
{
	int32_t i, sum, sub_sum;
	//int32_t sum8;
	int32_t sub_sum8;
	// 某点周围8个点的地址偏移
	//int32_t	SiteD8[8] = {pitch-1, pitch, pitch+1, 1, -pitch+1, -pitch, -pitch-1, -1};

	int32_t SiteD8[8];
	SiteD8[0] = pitch-1;	SiteD8[1] = pitch;		SiteD8[2] = pitch+1;
	SiteD8[3] = 1;			SiteD8[4] = 1-pitch;	SiteD8[5] = -pitch;
	SiteD8[6] = -pitch-1;	SiteD8[7] = -1;
	// 8个点所有相邻两个点的差的绝对值的和如果为6*255则为叉点
	sum = 0;
	sub_sum = 0;
	for(i = 0; i < 8; i++) {
		//优化前
		sub_sum += abs(*(pNow + SiteD8[(i+1)%8]) - *(pNow + SiteD8[i]));
		sum += *(pNow+SiteD8[i]);
	}

	//若是交叉点,则仅0-1变换3次(等效于1-0变换3次),
	//因此共有6次差值变换,总和为6*(|1-0|或|255-0|)
	if (bina_type == 1)	{	//0,1二值 
		sub_sum8 = 6 * 1;
//		sum8 = 5;
	} else {				//0,255二值
		sub_sum8 = 6 * 255;	
		//背景色为255
//		sum8 = 5 * 255;
	}

	if(sub_sum == sub_sum8)
		return 1;
	else
		return 0;
}

/************************************************************************
  * 功能：判断所在点是否为端点,被SkeletonBurrClearV1等调用
  * 参数：pNow				细化后图像的当前点的地址[In]
  *		  width				图像数据宽度
  *		  height			图像数据高度
  *		  pitch				图像数据每行字节数
  *		  bina_type			图像二值类型1:(0,1)或其他:(0,255)
  * 返回：若为交叉点,返回1.	其他返回0
  * 说明: 被SkeletonBurrClearV1调用,被image_feature中的很多函数调用
*************************************************************************/
int32_t IsEnd
(
 uint8_t *pNow, 
 //const int32_t width, 
 //const int32_t height, 
 const int32_t pitch,
 const int32_t bina_type
 )
{
	int32_t i, sum, sub_sum;
	//int32_t sum8, 
	int32_t sub_sum8;
	// 某点周围8个点的地址偏移
	//int32_t	SiteD8[8] = {pitch-1, pitch, pitch+1, 1, -pitch+1, -pitch, -pitch-1, -1};

	int32_t SiteD8[8];
	SiteD8[0] = pitch-1;	SiteD8[1] = pitch;		SiteD8[2] = pitch+1;
	SiteD8[3] = 1;			SiteD8[4] = 1-pitch;	SiteD8[5] = -pitch;
	SiteD8[6] = -pitch-1;	SiteD8[7] = -1;


	// 8个点所有相邻两个点的差的绝对值的和如果为6*255则为叉点
	sum = 0;
	sub_sum = 0;
	//asum = 0;
	for(i = 0; i < 8; i++) {
		sub_sum += abs(*(pNow + SiteD8[(i+1)%8]) - *(pNow + SiteD8[i]));
		sum += *(pNow+SiteD8[i]);
	}


	//若是末梢点,则仅0-1变换1次(等效于1-0变换1次),
	//因此共有2次差值变换,总和为2*(|1-0|或|255-0|)
	//优化前
	//if(sum == 255*2)
	if (bina_type == 1)	{//0,1二值
		sub_sum8 = 2 * 1;
//		sum8 = 7;
	} else {				//0,255二值
		sub_sum8 = 2 * 255;	
//		sum8 = 7*255;
	}
	//if(sub_sum == sub_sum8 && sum == sum8)
	if(sub_sum == sub_sum8)
		return 1;
	else
		return 0;
}


/************************************************************************
  * 功能：沿纹线跟踪找到距离当前点距离为dis的点,返回其地址
  * 参数：pPoint			细化后图像的当前点的地址[In]
  *		  ppPos				距离当前点dis的点的地址的指针[Out]
  *		  dis				跟踪距离(像素点点数)
  *		  width				图像数据宽度
  *		  height			图像数据高度
  *		  pitch				图像数据每行字节数
  *		  forecolor		    图像数据前景颜色
  *		  backcolor		    图像数据背景颜色
  * 返回：若找到返回0, 错误:返回1
  * 说明: 被image_feature中的很多函数调用
*************************************************************************/
int32_t  GetPointByDis
(
 uint8_t *pPoint, 
 uint8_t **ppPos, 
 int32_t dis,
 //const int32_t width, 
 //const int32_t height, 
 const int32_t pitch,
 const int32_t forecolor,
 const int32_t bina_type
 )
{

	int32_t i, n;
	uint8_t *pNow = NULL;
	uint8_t *pLast = NULL;
	uint8_t *pNext = NULL;
	//int32_t	SiteD8[8] = {pitch-1, pitch, pitch+1, 1, -pitch+1, -pitch, -pitch-1, -1};

	int32_t SiteD8[8];
	SiteD8[0] = pitch-1;	SiteD8[1] = pitch;		SiteD8[2] = pitch+1;
	SiteD8[3] = 1;			SiteD8[4] = 1-pitch;	SiteD8[5] = -pitch;
	SiteD8[6] = -pitch-1;	SiteD8[7] = -1;

	*ppPos = NULL;

	// 找到当前点周围的是黑点并且不是前驱点的黑点，保存到数组
	n = 0;
	for(i = 0; i < 8; i++) {
		//if(*(pPoint + SiteD8[i]) == 0)
		if(*(pPoint + SiteD8[i]) == forecolor) {
			pNow = pPoint + SiteD8[i];
			n++;
		}
	}
	if(n != 1) {	// 数目如果不是1则返回错误
		return 1;
	}

	// 找到的黑点地址为pNow
	// 端点作为前驱点,地址保存到pLast
	pLast = pPoint; 
	// 循环找dis次后继点
	for(i = 0; i < dis; i++) {
		// 如果是叉点则跳出循环
		if(IsFork(pNow, pitch, bina_type)) {	
			break;
		}
		// 成功找到下一个点则更改当前点和前驱点
		if(GetNext(pNow, pLast, &pNext, pitch, forecolor) == 0) {	
			pLast = pNow;
			pNow = pNext;
		} else {
			break;
		}
	}

	// 如果找到的点为叉点，则返回其前驱点
	if(IsFork(pNow, pitch, bina_type)) {
		*ppPos = pLast;
	} else {			// 否则返回当前点
		*ppPos = pNow;
	}

	return 0;
}


/************************************************************************
  * 功能：对清除细化图像中短棒和毛刺
  * 参数：pSrc				指向源图像数据区
  *		  area_thr			短棒和毛刺的最大长度
  *		  width				图像数据宽度
  *		  height			图像数据高度
  *		  pitch				图像数据每行字节数
  *		  forecolor		    图像数据前景颜色
  *		  backcolor		    图像数据背景颜色
  *		  bina_type			图像二值类型1:(0,1)或其他:(0,255)
  * 返回：void
  * 说明: 利用类似链表的原理,而不采用函数迭代的形式(参考SkeletonBurrMarkOZ)
  *	算法: 1.遍历图像的每一像素点,计算其8邻域.
  *  		(1)若为孤立的点清除为背景点,并进入步骤1继续下一点的遍历
  *			(2)若为端点,记录其邻域的某个的为新的点,并进入步骤2
  *		  2.由此点开始扫描路径(纹线跟踪)area_thr个点.
  *		    (1)若此点遇到叉点(调用IsFork函数判断),直接结束此次跟踪,进入步骤4
  *			(2)记录此点地址,并找寻下一点(调用GetNext),
  *			   若找到下一点,继续进行步骤2.
  *			   如果找不到下一点,则进入步骤3.
  *			   或者扫描路径超过area_thr.进入步骤4
  *		  3.将刚才扫描过的路径清除为背景点
  *		  4.遍历下一个像素点,直到全部点遍历完毕.
  * 注意:输入图像数据为二值数据(0,1)或(0,255),且前景色必须为0???
*************************************************************************/
void SkeletonBurrClearV1
(
 uint8_t *pSrc, 
 const int32_t area_thr, 
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch,
 const int32_t forecolor,
 const int32_t backcolor,
 const int32_t bina_type
 )
{
	int32_t	x, y;
	int32_t i, n, num;
	int32_t tempY;
	uint8_t *Line[25];			//记录路径每点的地址,暂设25,实际应该根据area_thr
	//进行动态设置
	uint8_t *pNow = NULL;		//指向当前的指针
	uint8_t *pLast = NULL;		//指向前驱点指针(对于下一点来说,其与上一点pNow为一直)
	uint8_t *pNext = NULL;		//指向下一点指针
	uint8_t *tempPtr[8];		//用来暂存8邻域的地址,实际有用的为tempPtr[0]
	// 某点周围8个点的地址偏移
	//int32_t	SiteD8[8] = {pitch-1, pitch, pitch+1, 1, -pitch+1, -pitch, -pitch-1, -1};

	int32_t SiteD8[8];
	SiteD8[0] = pitch-1;	SiteD8[1] = pitch;		SiteD8[2] = pitch+1;
	SiteD8[3] = 1;			SiteD8[4] = 1-pitch;	SiteD8[5] = -pitch;
	SiteD8[6] = -pitch-1;	SiteD8[7] = -1;

	tempY = 0;
	for(y = 0; y < height; y++) {
		//优化前
		//tempY = y*pitch;
		for(x = 0; x < width; x++) {
			pNow = pSrc + tempY + x;	//
			//if(*pNow != 0) {	//非前景点
			if(*pNow != forecolor) {	//非前景点
				continue;
			}

			Line[0] = pNow;				//记录路径上的第一点地址
			// 统计当前点的周围黑点(前景点)个数
			n = 0;
			for(i = 0; i < 8; i++) {
				pNext = pNow + SiteD8[i];
				//if(*pNext == 0) {
				if(*pNext == forecolor) {
					tempPtr[n] = pNext;	//记录8邻域的地址,实际有用的为tempPtr[0]
					n++;
				}
			}
			//黑点个数为零，表示当前点是孤点，置为白色(背景点)
			if(n == 0) {
				//*pNow = 255;
				*pNow = backcolor;
				continue;
			}
			//黑点(背景点)个数为1，表示为端点.
			//当且仅当为端点时才进行路径搜索,其他中间点和三叉点不往下搜索
			else if(n == 1) {
				num = 0;
				pLast = pNow;			//保存当前点地址作为上一点地址
				pNow = tempPtr[0];		//获取下一点地址并更新为当前点地址
				//沿纹线跟踪area_thr个点
				for(i = 0; i < area_thr; i++) {
					// 如果遇到叉点则跳出循环
					if(IsFork(pNow, pitch, bina_type)) {
						break;
					}				
					num++;				//记录扫描路径个数计算
					Line[num] = pNow;	//同时记录路径上的点的地址
					//获取下一点地址
					if(GetNext(pNow, pLast, &pNext, pitch, forecolor) == 0) {
						pLast = pNow;	//保存当前点地址作为上一点地址
						pNow = pNext;	//获取下一点地址并更新为当前点地址
					} else {// 如果遇到异常跳出循环
						break;
					}

				}

				// 纹线较短，表示为短棒或者是毛刺,清除(设为背景点)
				if(num < area_thr) {
					for(i = 0; i <= num; i++) {
						//*Line[i] = 255;
						*Line[i] = backcolor;
					}
				}

			}
		}
		//优化后
		tempY += pitch;
	}

	//return 0;
}


























