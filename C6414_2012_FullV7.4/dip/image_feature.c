/******************************************************************************
* 文件名：image_feature.c
* 功  能：主要实现图像的特征提取
******************************************************************************/
#include "dip_header/image_feature.h"

#include <math.h>


/************************************************************************
* 名称：FVMinutiaSetExtractLowLevel
* 功能：从细化图像中提取细节点，并储存到集合中。
*       申请的细节点集合必须足够大，如果太小了，满了后会停止搜索细节点。
* 参数：minutia      细节点集合，用来保存细节点
*       image        细化后的图像
* 返回：错误编号
* 算法：
*          注意：(1)图像的前景是"1",背景是"0"
*                (2)图像是完全细化的图像，即没有任何冗余的点。
*
*          一个点p的8邻域如图所示
*          ----------
*          |x4|x3|x2|
*          ----------
*          |x5|p |x1|
*          ----------
*          |x6|x7|x8|
*          ----------
*        
*          当p点及其邻域同时满足以下条件时p点是特征点。
*
*          (1)p点是"1",即是前景不是背景。
*
*          (2)p点的8邻域"1"的点数为1,3,或者4。
*
*             1)p点的8邻域"1"的点数为1则p点是端点。
*             2)p点的8邻域"1"的点数为3则p点是三邻域交叉点。
*             3)p点的8领域"1"的点数为4则p点是四邻域交叉点。
*************************************************************************/
//static FunError_t FVMinutiaSetExtractLowLevel
//(
// pFVMinutiaSet_t minutia,
// uint8_t *pSrc,
// const int32_t width, 
// const int32_t height, 
// const int32_t pitch
// )
//{
//	//int32_t w      = ImageGetWidth(image);
//	//int32_t h      = ImageGetHeight(image);
//	//int32_t pitch  = ImageGetPitch(image);
//	//uint8_t* p    = ImageGetBuffer(image);
//	int32_t   x, y;
//	//int32_t i,j;
//	//int32_t all_cnt;    //特征的总数量
//	//int32_t epoint32_t_cnt; //端点的数量
//	//int32_t jpoint32_t_cnt; //交叉点的数量
//	int32_t t_h;
//	int32_t t_w;
//	int32_t temp1,temp2;
//	int32_t x1,x2,x3,x4,x5,x6,x7,x8; 
//	int32_t nbminutia;
//	t_h=height-1;
//	t_w=width-1;
//#undef  PSRC	
//#define PSRC(x, y)		pSrc[(x)+(y)*pitch]
//	//all_cnt   =0;
//	//epoint32_t_cnt=0;
//	//jpoint32_t_cnt=0;
//
//	//if (p==NULL)
//	//	return FunMemory;
//
//	//(void)FVMinutiaSetEmpty(minutia);
//	nbminutia = 0;
//	for(y=1;y<t_h;y++){
//		for(x=1;x<t_w;x++){
//
//			if(PSRC(x, y)==0){
//				continue;
//			}
//
//			x1=PSRC(x+1, y  ); //x1
//			x2=PSRC(x+1, y+1); //x2
//			x3=PSRC(x  , y+1); //x3
//			x4=PSRC(x-1, y+1); //x4
//			x5=PSRC(x-1, y  ); //x5
//			x6=PSRC(x-1, y-1); //x6
//			x7=PSRC(x  , y-1); //x7
//			x8=PSRC(x+1, y-1); //x8
//
//			temp1=x1+x2+x3+x4+x5+x6+x7+x8;
//			//temp2=abs(x1-x2)+abs(x2-x3)+abs(x3-x4)+abs(x4-x5)+
//			//  abs(x5-x6)+abs(x6-x7)+abs(x7-x8)+abs(x8-x1);	//适用细化和完全细化???
//			temp2=(x1&x2)+(x2&x3)+(x3&x4)+(x4&x5)+
//				(x5&x6)+(x6&x7)+(x7&x8)+(x8&x1);				//适用完全细化???
//
//			if(temp1==1){
//				//(void)MinutiaSetAdd(minutia, x, y,
//				//	MinutiaTypeEnd);
//				minutia->FVMinutiaArr[nbminutia].type = MinutiaTypeEnd;
//				minutia->FVMinutiaArr[nbminutia].x = x;
//				minutia->FVMinutiaArr[nbminutia].y = y;
//				//minutia->nbminutia++;
//				nbminutia++;
//				continue;
//			}
//
//			if(temp1>=3&&temp2==0){
//				//P(x, y) = 0;
//				//(void)MinutiaSetAdd(minutia, x, y,
//				//	MinutiaTypeFork);
//				minutia->FVMinutiaArr[nbminutia].type = MinutiaTypeFork;
//				minutia->FVMinutiaArr[nbminutia].x = x;
//				minutia->FVMinutiaArr[nbminutia].y = y;
//				//minutia->nbminutia++;
//				nbminutia++;
//			}
//
//			//nbminutia = MinutiaSetGetCount(minutia);
//			if (nbminutia >= FV_MAX_MINUTIA_NUM) {
//				return FunOK;
//			}
//
//		}//end for (j=1...
//	}//end for (i=1...
//
//	minutia->nbminutia = nbminutia;
//
//	return FunOK;
//}


/************************************************************************
* 名称：FVMinutiaSetExtractLowLevel
* 功能：从细化图像中提取细节点，并储存到集合中。
*       申请的细节点集合必须足够大，如果太小了，满了后会停止搜索细节点。
* 参数：minutia      细节点集合，用来保存细节点
*       image        细化后的图像
*       area_thr         传递给其他函数的参数,用来判断终止条件的,
*                    当计数器的值大于阈值area_thr时则终止当前扫描。             
* 返回：错误编号
* 作用：对已经细化但是没有修剪毛刺的图像进行处理，直接提取出特征点。
* 算法：
*          第一步：对图像进行特征点预提取。
*          第二步：对所有特征点逐步进行比对，设定一定的条件将伪特征点去除。
*          第三步：去除伪特征点后再提取一次特征点。 
*************************************************************************/
//FunError_t FVMinutiaSetExtractOZ
//(
// pFVMinutiaSet_t minutia,
// uint8_t *pSrc,
// const int32_t width, 
// const int32_t height, 
// const int32_t pitch,
// const int32_t area_thr
// )
//{
//	int32_t i;
//	//int32_t x, y;
//	int32_t nbminutia;
//	//Minutia_t* min;
//	uint8_t part_area[256];//当前端点的扫描情况。
//
//	//预提取,0,1不使用,因为在SkeletonBurrMarkOZ中标记的关系
//	part_area[0]=255;
//	part_area[1]=255;
//	for (i = 2; i < 256; i++){
//		part_area[i]=0;
//	}
//
//	FVMinutiaSetExtractLowLevel(minutia, pSrc, width, height, pitch);
//
//	nbminutia = minutia->nbminutia;
//
//	for (i = 0; i < nbminutia; i++){
//
//		if (minutia->FVMinutiaArr[i].type == MinutiaTypeFork)
//			continue;
//		//标记冗余的特征点。
//		SkeletonBurrMarkOZ(pSrc, pitch,
//			minutia->FVMinutiaArr[i].x,
//			minutia->FVMinutiaArr[i].y,
//			i+2,
//			&part_area[i+2],
//			area_thr
//			);
//		/*if(i>=255){
//		printf("pixel_get_feature_ex特征点过多!\n");
//		}*/
//	}
//
//	//清除冗余的特征点。
//	SkeletonBurrClearOZ(pSrc, width, height, pitch, part_area, area_thr);
//
//	//重新提取一次特征点。
//	FVMinutiaSetExtractLowLevel(minutia, pSrc, width, height, pitch);
//
//	return FunOK;
//}



void FVMinutiaSetDilateOZ
(
 uint8_t *pSrc,
 pFVMinutiaSet_t minutia,	
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 )
{
	int32_t x, y;
	int32_t x1, y1;
	int32_t i;
	int32_t m, n;
	for (i = 0; i < minutia->nbminutia; i++) {
		x = minutia->FVMinutiaArr[i].x;
		y = minutia->FVMinutiaArr[i].y;

		for (m = -3; m <= 3; m++) {
			for (n = -3; n <= 3; n++) {
				x1 = x+n;
				y1 = y+m;
				if ((x1 < 0) || (x1 >= width) || \
					(y1 < 0) || (y1 >= height)) {
					continue;
				}
				*(pSrc + y1*pitch + x1) = 1;
			}
		}


	}

}

void FPMinutiaSetDilateOZ
(
 uint8_t *pSrc,
 pFPMinutiaSet_t minutia,	
 const int32_t width, 
 const int32_t height, 
 const int32_t pitch
 )
{
	int32_t x, y;
	int32_t x1, y1;
	int32_t i;
	int32_t m, n;
	for (i = 0; i < minutia->nbminutia; i++) {
		x = minutia->FPMinutiaArr[i].x;
		y = minutia->FPMinutiaArr[i].y;

		for (m = -3; m <= 3; m++) {
			for (n = -3; n <= 3; n++) {
				x1 = x+n;
				y1 = y+m;
				if ((x1 < 0) || (x1 >= width) || \
					(y1 < 0) || (y1 >= height)) {
					continue;
				}
				*(pSrc + y1*pitch + x1) = 0;
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


//!!!!!!!!!!!!注意!!!!!!!!!!!!
//若提取特征时,前景色为0,图像是0,1二值图像,则要设置为:
#define BACKCOLOR		1
#define BINA_TYPE		1
//若提取特征时,前景色为0,图像是0,255二值图像,则要设置为:
//#define BACKCOLOR		255
//#define BINA_TYPE		255
#define RBACKCOLOR		255

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
int32_t  M_PX(uint8_t *pPos, uint8_t *pSrc, uint32_t pitch)
{
	return ((pPos - pSrc) % pitch);
}

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
int32_t  M_PY(uint8_t *pPos, uint8_t *pSrc, uint32_t pitch)
{
	return ((pPos - pSrc) / pitch);
}

/************************************************************************
* 功能：根据奇异点的类型,获取两点之间方向场的变化
* 参数：angle1			角度1
*		  angle2			角度2
*		  flag				奇异点类型 1:三角点, 其他:中心点
* 返回：方向场变化角度
* 说明: 
*************************************************************************/
#define ORICHG	10
int32_t GetOrientChange(const int32_t angle1, const int32_t angle2, const uint8_t flag)
{
	int32_t  d;
	d = angle2 - angle1;
	if(flag == 1) {	//三角点
		if(d < 0)
			d += ORICHG;
	} else {		//中心点
		if(d > 0)
			d -= ORICHG;
	}
	return d;
}

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
 )
{
//	int32_t x, y, i;
//	int32_t num;			//记录奇异点个数
//	int32_t sum1, sum2;		//3x3,5x5方格的方向场差值之和
//	int32_t d;
//	uint8_t *pOri;			//某点方向场指针
//	int32_t ori_value;		//某点方向场值
//	int32_t a1, a2;			//角度
//	Point_t temp_arr[30];	//奇异点坐标暂存,一般不会超过30个,
//	//且设置的奇异点最大个数FP_MAX_SINGULARYTY_NUM就是30
//	//int32_t nbminutia;
//	int32_t value;			//Poincare值
//	double dis;
//	int32_t found = 0;		//是否找到奇异点标志
//	int32_t bg_flag = 0;	//区域内是否有背景标志
//
//	//以某点为中心,3/2为半径的偏移量(offset_x,offset_y)
//	int32_t    D3[8][2] = {
//		-1,-1, -1,0,  -1,1,  0,1,  1,1,  1,0,  1,-1,  0,-1
//	};
//	//以某点为中心,5/2为半径的偏移量(offset_x,offset_y)
//	int32_t    D5[12][2] = {
//		-2,-1, -2,0,  -2,1, -1,2,  0,2,  1,2, 2,1,  2,0,  2,-1, 1,-2, 0,-2, -1,-2
//	};
//	//以某点为中心,7/2为半径的偏移量(offset_x,offset_y)
//	int32_t    D7[24][2] = {
//		-3,-3, -3,-2, -3,-1, -3,0, -3,1, -3,2, -3,3, -2,3, -1,3, 0,3, 1,3, 2,3, 3,3, 3,2, 3,1, 3,0,
//		3,-1, 3,-2, 3,-3, 2,-3, 1,-3, 0,-3, -1,-3, -2,-3
//	};
//
//	num = 0;
//	if (flag == 1) {		//三角点
//		value = ORICHG;
//	} else {			 //中心点	
//		value = -ORICHG;
//	}
//
//	//memset(temp_arr, 0, sizeof(temp_arr));	//初始化奇异点数组，清零
//	for (i = 0; i < 30; i++) {
//		temp_arr[i].x = 0;
//		temp_arr[i].y = 0;
//	}
//
//	//最大为7,半径7/2=3,考虑边界则从3开始
//	for (y = 3; y < height-3; y++) {
//		for (x = 3; x < width-3; x++) {			//遍历整幅图
//			pOri = pOrientation + y*pitch + x;		//获得某点的方向场指针
//			ori_value = *pOri;					//获取某点的方向场的值
//
//			//前面计算方向场和粗分割时,将粗背景区域的方向场设定为了255，
//			//if(ori_value == backcolor) {		//若是背景区域，则跳入下一个循环
//			if (ori_value == 255)				//若是背景区域，则跳入下一个循环
//				continue;
//
//			bg_flag = 0;									
//			for (i = 0; i < 24; i++) {//若在半径为7的区域内有背景,则跳入下一个循环
//				if(pOri[D7[i][1]*pitch + D7[i][0]]==255) {
//					bg_flag = 1;			
//					break;
//				}
//			}
//			if (bg_flag)
//				continue;
//
//			//计算3x3方格的Poincare值
//			sum1 = 0;
//			for (i = 0; i < 8; i++) {
//				//这里的得到的方向场角度/24是因为
//				//前面计算方向场的时候用的是12个方向
//				//前面计算方向场得到的角度在0-180之间
//				//[180/24]=7,即两角度之差为(-14, 14)
//				//经过+-10的修正,则变为(三角点为例+10)
//				//两角度之差变为(-4, 14)
//				a1 = pOri[D3[i][1]*pitch + D3[i][0]]/24;
//				a2 = pOri[D3[(i+1)%8][1]*pitch + D3[(i+1)%8][0]]/24;
//				//GetOrientChange里面的+-10应该与24, 12有关
//				d = GetOrientChange(a1, a2, flag);
//				//这个5也与10,24,12有关
//				if (abs(d) > 5) 
//					break;
//				sum1 += d;
//			}
//			//计算5x5方格的Poincare值
//			sum2 = 0;
//			for (i = 0; i < 12; i++) {
//				a1 = pOri[D5[i][1]*pitch + D5[i][0]]/24;
//				a2 = pOri[D5[(i+1)%12][1]*pitch + D5[(i+1)%12][0]]/24;
//				d = GetOrientChange(a1, a2, flag);
//
//				if(abs(d) > 5)
//					break;
//				sum2 += d;
//			}
//
//			//里外两圈的方向场差值相同,此点为奇异点
//			if (sum2 == value && sum1 == value) {
//				found = 0;
//				//比对新找到的奇异点与之前找到的奇异点
//				for(i = 0; i < num; i++) {
//					dis = sqrt((double)((x - temp_arr[i].x)*(x - temp_arr[i].x) +
//						(y - temp_arr[i].y)*(y - temp_arr[i].y)));
//					//若发现与之前找到的奇异点重叠,则用平均位置作为原来奇异点的坐标
//					if(dis < 4) {		
//						temp_arr[i].x = (temp_arr[i].x + x)/2;
//						temp_arr[i].y = (temp_arr[i].y + y)/2;
//						found = 1;		//设置找到标志为1(没找到)
//						break;
//					}
//				}
//
//				//若没有发现与之前的奇异点重叠,则其为新的奇异点,记录保存
//				if (!found) {		//找到了新的奇异点,添加到奇异点暂存数组中
//					temp_arr[num].x = x;
//					temp_arr[num].y = y;
//					num++;
//					//若奇异点数量超过最大限制，则停止寻找奇异点
//					if(num >= FP_MAX_SINGULARYTY_NUM) {	
//						goto GS_OUT;
//					}
//				}
//			}
//		}
//	}
//
//GS_OUT:
//
//	//nbminutia = minutia->nbminutia;
//	for (i = 0; i < num; i++) {	//将找到的奇异点存入输入数组
//
//		x = temp_arr[i].x;
//		y = temp_arr[i].y;
//
//		//判断奇异点是否在边缘区域,若是,则舍弃
//		if (((x + 0.0) / width < 0.1) || ((x + 0.0) / width > 0.9)) 
//			continue;
//		if (((y + 0.0) / height < 0.1 ) || ((y + 0.0) / height > 0.9))
//			continue;
//
//		//将找到的奇异点添加到输入数组中
//		if (flag == 1)	{	//三角点
//			//(void)MinutiaSetAddV1(minutia, x, y, MinutiaTypeDelta, 0);
//			minutia->FPMinutiaArr[minutia->nbminutia].type = MinutiaTypeDelta;
//			minutia->FPMinutiaArr[minutia->nbminutia].x = x;
//			minutia->FPMinutiaArr[minutia->nbminutia].y = y;
//			minutia->FPMinutiaArr[minutia->nbminutia].angle = 0;
//			minutia->nbminutia++;
//		} else {				//中心点
//			//(void)MinutiaSetAddV1(minutia, x, y, MinutiaTypeCore, 0);
//			minutia->FPMinutiaArr[minutia->nbminutia].type = MinutiaTypeCore;
//			minutia->FPMinutiaArr[minutia->nbminutia].x = x;
//			minutia->FPMinutiaArr[minutia->nbminutia].y = y;
//			minutia->FPMinutiaArr[minutia->nbminutia].angle = 0;
//			minutia->nbminutia++;
//		}
//		//nbminutia++;
//	}

	int32_t x, y, i;
	int32_t num;			//记录奇异点个数
	int32_t sum1, sum2;		//3x3,5x5方格的方向场差值之和
	int32_t d;
	uint8_t *pOri;			//某点方向场指针
	int32_t ori_value;		//某点方向场值
	int32_t a1, a2;			//角度
	Point_t temp_arr[30];	//奇异点坐标暂存,一般不会超过30个,
	//且设置的奇异点最大个数FP_MAX_SINGULARYTY_NUM就是30
	//int32_t nbminutia;
	int32_t value;			//Poincare值
	//double dis;
	int32_t dis;
	int32_t found = 0;		//是否找到奇异点标志
	int32_t bg_flag = 0;	//区域内是否有背景标志

	//以某点为中心,3/2为半径的偏移量(offset_x,offset_y)
	int32_t    D3[8][2] = {
		-1,-1, -1,0,  -1,1,  0,1,  1,1,  1,0,  1,-1,  0,-1
	};
	//以某点为中心,5/2为半径的偏移量(offset_x,offset_y)
	int32_t    D5[12][2] = {
		-2,-1, -2,0,  -2,1, -1,2,  0,2,  1,2, 2,1,  2,0,  2,-1, 1,-2, 0,-2, -1,-2
	};
	//以某点为中心,7/2为半径的偏移量(offset_x,offset_y)
	int32_t    D7[24][2] = {
		-3,-3, -3,-2, -3,-1, -3,0, -3,1, -3,2, -3,3, -2,3, -1,3, 0,3, 1,3, 2,3, 3,3, 3,2, 3,1, 3,0,
		3,-1, 3,-2, 3,-3, 2,-3, 1,-3, 0,-3, -1,-3, -2,-3
	};

	num = 0;
	if (flag == 1) {		//三角点
		value = ORICHG;
	} else {			 //中心点	
		value = -ORICHG;
	}

	//memset(temp_arr, 0, sizeof(temp_arr));	//初始化奇异点数组，清零
	for (i = 0; i < 30; i++) {
		temp_arr[i].x = 0;
		temp_arr[i].y = 0;
	}

	//最大为7,半径7/2=3,考虑边界则从3开始
	for (y = 3; y < height-3; y++) {
		for (x = 3; x < width-3; x++) {			//遍历整幅图
			pOri = pOrientation + y*pitch + x;		//获得某点的方向场指针
			ori_value = *pOri;					//获取某点的方向场的值

			//前面计算方向场和粗分割时,将粗背景区域的方向场设定为了255，
			//if(ori_value == backcolor) {		//若是背景区域，则跳入下一个循环
			if (ori_value == 255)				//若是背景区域，则跳入下一个循环
				continue;

			bg_flag = 0;									
			for (i = 0; i < 24; i++) {//若在半径为7的区域内有背景,则跳入下一个循环
				if(pOri[D7[i][1]*pitch + D7[i][0]]==255) {
					bg_flag = 1;			
					break;
				}
			}
			if (bg_flag)
				continue;

			//计算3x3方格的Poincare值
			sum1 = 0;
			for (i = 0; i < 8; i++) {
				//这里的得到的方向场角度/24是因为
				//前面计算方向场的时候用的是12个方向
				//前面计算方向场得到的角度在0-180之间
				//[180/24]=7,即两角度之差为(-14, 14)
				//经过+-10的修正,则变为(三角点为例+10)
				//两角度之差变为(-4, 14)
				a1 = pOri[D3[i][1]*pitch + D3[i][0]]/24;
				a2 = pOri[D3[(i+1)%8][1]*pitch + D3[(i+1)%8][0]]/24;
				//GetOrientChange里面的+-10应该与24, 12有关
				d = GetOrientChange(a1, a2, flag);
				//这个5也与10,24,12有关
				if (abs(d) > 5) 
					break;
				sum1 += d;
			}
			//计算5x5方格的Poincare值
			sum2 = 0;
			for (i = 0; i < 12; i++) {
				a1 = pOri[D5[i][1]*pitch + D5[i][0]]/24;
				a2 = pOri[D5[(i+1)%12][1]*pitch + D5[(i+1)%12][0]]/24;
				d = GetOrientChange(a1, a2, flag);

				if(abs(d) > 5)
					break;
				sum2 += d;
			}

			//里外两圈的方向场差值相同,此点为奇异点
			if (sum2 == value && sum1 == value) {
				found = 0;
				//比对新找到的奇异点与之前找到的奇异点
				for(i = 0; i < num; i++) {
					//dis = sqrt((double)((x - temp_arr[i].x)*(x - temp_arr[i].x) +
					//	(y - temp_arr[i].y)*(y - temp_arr[i].y)));
					dis = ((x - temp_arr[i].x)*(x - temp_arr[i].x) +(y - temp_arr[i].y)*(y - temp_arr[i].y));
					//若发现与之前找到的奇异点重叠,则用平均位置作为原来奇异点的坐标
					//if(dis < 4) {	
					if (dis < 16) {
						temp_arr[i].x = (temp_arr[i].x + x)/2;
						temp_arr[i].y = (temp_arr[i].y + y)/2;
						found = 1;		//设置找到标志为1(没找到)
						break;
					}
				}

				//若没有发现与之前的奇异点重叠,则其为新的奇异点,记录保存
				if (!found) {		//找到了新的奇异点,添加到奇异点暂存数组中
					temp_arr[num].x = x;
					temp_arr[num].y = y;
					num++;
					//若奇异点数量超过最大限制，则停止寻找奇异点
					if(num >= FP_MAX_SINGULARYTY_NUM) {	
						goto GS_OUT;
					}
				}
			}
		}
	}

GS_OUT:

	//nbminutia = minutia->nbminutia;
	for (i = 0; i < num; i++) {	//将找到的奇异点存入输入数组

		x = temp_arr[i].x;
		y = temp_arr[i].y;

		//判断奇异点是否在边缘区域,若是,则舍弃
		//if (((x + 0.0) / width < 0.1) || ((x + 0.0) / width > 0.9)) 
		//	continue;
		//if (((y + 0.0) / height < 0.1 ) || ((y + 0.0) / height > 0.9))
		//	continue;
		if ((x < width/10) || (x   > width*9/10)) 
			continue;
		if ((y < height/10 ) || ((y) > height*9/10))
			continue;


		//将找到的奇异点添加到输入数组中
		if (flag == 1)	{	//三角点
			//(void)MinutiaSetAddV1(minutia, x, y, MinutiaTypeDelta, 0);
			minutia->FPMinutiaArr[minutia->nbminutia].type = MinutiaTypeDelta;
			minutia->FPMinutiaArr[minutia->nbminutia].x = x;
			minutia->FPMinutiaArr[minutia->nbminutia].y = y;
			minutia->FPMinutiaArr[minutia->nbminutia].angle = 0;
			minutia->nbminutia++;
		} else {				//中心点
			//(void)MinutiaSetAddV1(minutia, x, y, MinutiaTypeCore, 0);
			minutia->FPMinutiaArr[minutia->nbminutia].type = MinutiaTypeCore;
			minutia->FPMinutiaArr[minutia->nbminutia].x = x;
			minutia->FPMinutiaArr[minutia->nbminutia].y = y;
			minutia->FPMinutiaArr[minutia->nbminutia].angle = 0;
			minutia->nbminutia++;
		}
		//nbminutia++;
	}

	//调用FPMinutiaSetExtractEndAndFork或调用FPMinutiaSetExtractSingularity前
	//即获取指纹特征点集前,应该先初始化minutia->nbminutia = 0;
	//minutia->nbminutia += nbminutia;
}

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
 ) 
{
	int32_t i, j;
	int32_t flag = 1;

	for (i = -r; i <= r && flag; i++) {			//这样就不用使用goto了
		for (j = -r; j <= r && flag; j++) {
			//没有进行越界处理,因此调用此函数要保证不会越界
			//if(y+i<0 || y+i>=height || x+j<0 || x+j>=width) {	
			//	continue;
			//}
			//前面计算方向场和分割时,将背景区域的方向场设定为了255
			if (*(pOrietation + (y+i)*pitch + x + j) == rbackcolor) {
				flag = 0;		
				break;		//如果前面的判断没有使用&&flag,则break只能
				//结束里面的循环,要想跳出就要用到goto或者
				//像这里一样使用&&flag来作为一个判断条件.
			}
		}
	}
	return flag;
}

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
 ) 
{
	int32_t i;
	int32_t flag = 1;
	int32_t sum = 0;
	//没有进行越界处理,因此调用此函数要保证不会越界
	for (i = 0; i < site_num; i++) {	//计算半径为5的28个点的方向场变换
		sum += GetAngle90In180(*(pOrietation+y*pitch+site[(i+1)%site_num]+x), *(pOrietation+y*pitch+site[i]+x));
	}
	//设定ori_thr作为剧烈变化的阈值
	if (sum > ori_thr)
		flag = 0;
	return flag;
}




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
 )
{
	int32_t x, y;
	int32_t r = 16;			//边缘设定为16
	int32_t forecolor = 0;	//图像前景色为黑点
	int32_t rbackcolor = 255;//方向场背景色为白点
	//int32_t bina_type = 255;//0,255的二值类型
	int32_t bina_type = BINA_TYPE;
	int32_t ori_thr = 96;	//方向场变换剧烈成都
	int32_t min_num = 0;
	int32_t min_num1 = 0;
	//uint8_t *pOri;
	uint8_t *pNow;
	int32_t tempY;
	int32_t flag;		//伪特征点标记, 0:伪特征点,1:真
	//某点为圆心，半径为5的圆上所有点的地址偏移
	//int32_t	SiteR5[28] = {
	//	-5, pitch-5, 2*pitch-5, 3*pitch-4, 4*pitch-3, 5*pitch-2, 5*pitch-1, 5*pitch,
	//	5*pitch+1, 5*pitch+2, 4*pitch+3, 3*pitch+4, 2*pitch+5, pitch+5, 5, -pitch+5,
	//	-2*pitch+5, -3*pitch+4, -4*pitch+3, -5*pitch+2, -5*pitch+1, -5*pitch,
	//	-5*pitch-1, -5*pitch-2, -4*pitch-3, -3*pitch-4, -2*pitch-5, -pitch-5
	//}; 
	int32_t SiteR5[28];
	//某点周围8个点的地址偏移
	//int32_t	SiteU8[8] = {pitch-1, pitch, pitch+1, 1, -pitch+1, -pitch, -pitch-1, -1};
	//int32_t SiteD8[8];
	
	SiteR5[0] = -5;		SiteR5[1] = pitch-5;	SiteR5[2] = 2*pitch-5;
	SiteR5[3] = 3*pitch-4;	SiteR5[4] = 4*pitch-3;	SiteR5[5] = 5*pitch-2;
	SiteR5[6] = 5*pitch-1;	SiteR5[7]=5*pitch;
	SiteR5[8] = 5*pitch+1;	SiteR5[9] = 5*pitch+2;	SiteR5[10]= 4*pitch+3;
	SiteR5[11] = 3*pitch+4;	SiteR5[12] = 2*pitch+5;	SiteR5[13] = pitch+5;
	SiteR5[14] = 5;	SiteR5[15] = -pitch+5;
	SiteR5[16] = -2*pitch+5;	SiteR5[17] = -3*pitch+4;	SiteR5[18] = -4*pitch+3;
	SiteR5[19] = -5*pitch+2;	SiteR5[20] = -5*pitch+1;	SiteR5[21] = -5*pitch;
	SiteR5[22] = -5*pitch-1;	SiteR5[23] = -5*pitch-2;	SiteR5[24] = -4*pitch-3;
	SiteR5[25] = -3*pitch-4;	SiteR5[26] = -2*pitch-5;	SiteR5[27] = -pitch-5;
	
	//SiteD8[0] = pitch-1;	SiteD8[1] = pitch;		SiteD8[2] = pitch+1;
	//SiteD8[3] = 1;			SiteD8[4] = 1-pitch;	SiteD8[5] = -pitch;
	//SiteD8[6] = -pitch-1;	SiteD8[7] = -1;

	//优化后
	tempY = (r+1)*pitch;	//前面设置允许特征点靠近前景边缘的最近距离r=16,
	//因此从(r+1)开始
	for (y = (r+1); y < height-(r+1); y++) {
		//优化前:
		//tempY = y*pitch;
		for (x = (r+1); x < width-(r+1); x++) {
			pNow = pSrc + tempY + x;
			//pOri = pOrientation + tempY + x;

			//if(*pNow != 0) {			//不是黑点(前景点)则不考虑
			if (*pNow != forecolor) {	//不是黑点(前景点)则不考虑
				continue;
			}

			//if (min_type == 1) {
			//是交叉点
			if(IsFork(pNow, width, bina_type)) {	
				//检查是否靠近边缘, 靠近边缘则不考虑
				flag = IsAtEdge(pOrientation, x, y, r, pitch, rbackcolor);
				//检查该点周围方向场是否变化剧烈,
				//变化剧烈则不考虑,因为很可能是虚假点
				flag &= IsOriChgViolent(pOrientation, x, y, SiteR5, 28, pitch, ori_thr);
				//达到所有要求则记录下来该点
				if(flag) {	
					pFork[min_num].x = x;
					pFork[min_num].y = y;
					min_num++;
					//如果总数已经超过允许最大数目，则返回错误
					if(min_num >= FP_MAX_RAW_MINUTIA_NUM) {
						min_num = 0;
						return 1;
					}
				}
			}
			//} else {
			// 如果是端点
			else if (IsEnd(pNow, width, bina_type)) {
				// 检查是否靠近边缘, 靠近边缘则不考虑
				flag = IsAtEdge(pOrientation, x, y, r, pitch, rbackcolor);

				//检查该点周围方向场是否变化剧烈,
				//变化剧烈则不考虑,因为很可能是虚假点
				flag &= IsOriChgViolent(pOrientation, x, y, SiteR5, 28, pitch, ori_thr);

				//达到所有要求则记录下来该点
				if(flag) {				
					pEnd[min_num1].x = x;
					pEnd[min_num1].y = y;
					min_num1++;
					// 如果总数已经超过允许最大数目，则返回错误
					if(min_num1 >= FP_MAX_RAW_MINUTIA_NUM) {
						min_num1 = 0;
						return 1;
					}
				}
			}
			//}
		}
		//优化后
		tempY += pitch;
	}
	*fork_num = min_num;
	*end_num = min_num1;

	return 0;
}

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
 )
{
	//int32_t i, j;
	//int32_t forecolor = 0;	//图像前景色为黑点
	////int32_t backcolor = 255;//方向场背景色为白点
	////int32_t bina_type = 255;//0,255的二值类型
	//int32_t bina_type = BINA_TYPE;
	//int32_t trace_len = 8;	//沿纹线循迹的长度:设为8
	//uint8_t *pNow;
	//uint8_t *pDis;			//沿纹线循迹的trace_len长度的点的地址
	//int32_t xDis, yDis;		//沿纹线循迹的trace_len长度的点的坐标
	//int32_t xi, yi, xj, yj;	//第一,第二个端点的坐标
	//int32_t flag;		//伪特征点标记, 0:伪特征点,1:真
	//int32_t angle1, angle2, angle3, angle4;
	//double d; 

	//for (i = 0; i < minutia_num-1; i++) {
	//	flag = 1;
	//	xi = pMinutia[i].x;
	//	yi = pMinutia[i].y;
	//	for (j = i+1; j < minutia_num; j++) {
	//		xj = pMinutia[j].x;
	//		yj = pMinutia[j].y;
	//		//求两个端点的距离
	//		d = sqrt((double)((xi-xj)*(xi-xj) + (yi-yj)*(yi-yj)));

	//		//距离足够大则检查下一个端点
	//		if (d > fixed_dis && d > var_dis) {	//var_dis是可变化的合适的最小距离值
	//			continue;
	//		}
	//		//距离太小,则将其坐标置为(0，0)
	//		if (d <= var_dis) {
	//			pMinutia[j].x = 0;
	//			pMinutia[j].y = 0;
	//			flag = 0;
	//			continue;
	//		}

	//		//求第一个端点所在纹线的角度
	//		pNow = pSrc + yi*pitch + xi;

	//		//获取沿纹线循迹的trace_len长度的点的地址
	//		//if(GetByDis(pNow, &pDis, 8) != 0)
	//		if (GetPointByDis(pNow, &pDis, trace_len, pitch, forecolor, bina_type)!=0) {
	//			break;	//由端点开始,如果没有找到,
	//		}			//则这点不用再与其他点进行测试,直接break,结束本轮检

	//		//获取沿纹线循迹的trace_len长度的点的坐标
	//		xDis = M_PX(pDis, pSrc, pitch);	
	//		yDis = M_PX(pDis, pSrc, pitch);
	//		angle1 = XY2Angle(xi, yi, xDis, yDis);

	//		//求第二个端点所在纹线的角度
	//		pNow = pSrc + yj*pitch + xj;

	//		//获取沿纹线循迹的trace_len长度的点的地址
	//		//if(GetByDis(pNow, &pDis, 8) != 0)
	//		if (GetPointByDis(pNow, &pDis, trace_len, pitch, forecolor, bina_type)!=0) {
	//			continue;	//由端点开始,如果没有找到,
	//		}				//则这点无效,直接continue,结束本次检测

	//		//获取沿纹线循迹的trace_len长度的点的坐标
	//		xDis = M_PX(pDis, pSrc, pitch);
	//		yDis = M_PX(pDis, pSrc, pitch);
	//		angle2 = XY2Angle(xj, yj, xDis, yDis);

	//		//求两个角度间的距离
	//		angle3 = GetAngle360In360(angle1, angle2);
	//		//如果两个角度间成锐角,则不是虚假特征点
	//		if (angle3 > 270 || angle3 < 90) {
	//			continue;
	//		}

	//		//求两个端点连线的角度
	//		angle3 = XY2Angle(xi, yi, xj, yj);
	//		//求第一个端点纹线与连线的夹角
	//		angle3 = GetAngle360In360(angle1, angle3);
	//		// 如果夹角较大则不是虚假点
	//		if (angle3 < 150 || angle3 > 210) {
	//			continue;
	//		}

	//		//求第二个端点纹线与连线的夹角
	//		angle4 = XY2Angle(xj, yj, xi, yi);
	//		angle4 = GetAngle360In360(angle2, angle4);
	//		//如果夹角较大则不是虚假点
	//		if (angle4 < 150 || angle4 > 210) {	
	//			continue;
	//		}

	//		//否则表示这两个点是同一条纹线上的断裂处的两个端点,坐标置原点
	//		pMinutia[j].x = 0;
	//		pMinutia[j].y = 0;
	//		flag = 0;
	//	}

	//	//表示这两个点是同一条纹线上的断裂处的两个端点,坐标置原点
	//	if (flag == 0) {	
	//		pMinutia[i].x = 0;
	//		pMinutia[i].y = 0;
	//	}
	//}
	//return flag;
	int32_t i, j;
	int32_t forecolor = 0;	//图像前景色为黑点
	//int32_t backcolor = 255;//方向场背景色为白点
	//int32_t bina_type = 255;//0,255的二值类型
	int32_t bina_type = BINA_TYPE;
	int32_t trace_len = 8;	//沿纹线循迹的长度:设为8
	uint8_t *pNow;
	uint8_t *pDis;			//沿纹线循迹的trace_len长度的点的地址
	int32_t xDis, yDis;		//沿纹线循迹的trace_len长度的点的坐标
	int32_t xi, yi, xj, yj;	//第一,第二个端点的坐标
	int32_t flag = 0;		//伪特征点标记, 0:伪特征点,1:真
	int32_t angle1, angle2, angle3, angle4;
	//double d; 

	int32_t d;
	int32_t d_fixed_dis = fixed_dis *fixed_dis;
	int32_t d_var_dis = var_dis *var_dis;

	for (i = 0; i < minutia_num-1; i++) {
		flag = 1;
		xi = pMinutia[i].x;
		yi = pMinutia[i].y;
		for (j = i+1; j < minutia_num; j++) {
			xj = pMinutia[j].x;
			yj = pMinutia[j].y;
			//求两个端点的距离
			//d = sqrt((double)((xi-xj)*(xi-xj) + (yi-yj)*(yi-yj)));

			d = ((xi-xj)*(xi-xj) + (yi-yj)*(yi-yj));

			//距离足够大则检查下一个端点
			if (d > d_fixed_dis && d > d_var_dis) {	//var_dis是可变化的合适的最小距离值
				continue;
			}
			//距离太小,则将其坐标置为(0，0)
			if (d <= d_var_dis) {
				pMinutia[j].x = 0;
				pMinutia[j].y = 0;
				flag = 0;
				continue;
			}

			//求第一个端点所在纹线的角度
			pNow = pSrc + yi*pitch + xi;

			//获取沿纹线循迹的trace_len长度的点的地址
			//if(GetByDis(pNow, &pDis, 8) != 0)
			if (GetPointByDis(pNow, &pDis, trace_len, pitch, forecolor, bina_type)!=0) {
				break;	//由端点开始,如果没有找到,
			}			//则这点不用再与其他点进行测试,直接break,结束本轮检

			//获取沿纹线循迹的trace_len长度的点的坐标
			xDis = M_PX(pDis, pSrc, pitch);	
			yDis = M_PX(pDis, pSrc, pitch);
			angle1 = XY2Angle(xi, yi, xDis, yDis);

			//求第二个端点所在纹线的角度
			pNow = pSrc + yj*pitch + xj;

			//获取沿纹线循迹的trace_len长度的点的地址
			//if(GetByDis(pNow, &pDis, 8) != 0)
			if (GetPointByDis(pNow, &pDis, trace_len, pitch, forecolor, bina_type)!=0) {
				continue;	//由端点开始,如果没有找到,
			}				//则这点无效,直接continue,结束本次检测

			//获取沿纹线循迹的trace_len长度的点的坐标
			xDis = M_PX(pDis, pSrc, pitch);
			yDis = M_PX(pDis, pSrc, pitch);
			angle2 = XY2Angle(xj, yj, xDis, yDis);

			//求两个角度间的距离
			angle3 = GetAngle360In360(angle1, angle2);
			//如果两个角度间成锐角,则不是虚假特征点
			if (angle3 > 270 || angle3 < 90) {
				continue;
			}

			//求两个端点连线的角度
			angle3 = XY2Angle(xi, yi, xj, yj);
			//求第一个端点纹线与连线的夹角
			angle3 = GetAngle360In360(angle1, angle3);
			// 如果夹角较大则不是虚假点
			if (angle3 < 150 || angle3 > 210) {
				continue;
			}

			//求第二个端点纹线与连线的夹角
			angle4 = XY2Angle(xj, yj, xi, yi);
			angle4 = GetAngle360In360(angle2, angle4);
			//如果夹角较大则不是虚假点
			if (angle4 < 150 || angle4 > 210) {	
				continue;
			}

			//否则表示这两个点是同一条纹线上的断裂处的两个端点,坐标置原点
			pMinutia[j].x = 0;
			pMinutia[j].y = 0;
			flag = 0;
		}

		//表示这两个点是同一条纹线上的断裂处的两个端点,坐标置原点
		if (flag == 0) {	
			pMinutia[i].x = 0;
			pMinutia[i].y = 0;
		}
	}
	return flag;
}

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
 )
{
	int32_t i, j;
	int32_t forecolor = 0;	//图像前景色为黑点
	//int32_t backcolor = 255;//方向场背景色为白点
	//int32_t bina_type = 255;//0,255的二值类型
	int32_t bina_type = BINA_TYPE;
	int32_t trace_len = 8;	//沿纹线循迹的长度:设为8
	uint8_t *pNow;
	uint8_t *pDis;			//沿纹线循迹的trace_len长度的点的地址
	int32_t xi, yi;	//第一,第二个端点的坐标
	int32_t flag;		//伪特征点标记, 0:伪特征点,1:真

	//统计新的端点数目
	flag = 1;
	j = 0;
	for (i = 0; i < minutia_num; i++) {
		//非有效端点
		xi = pMinutia[i].x;
		yi = pMinutia[i].y;

		if (xi == 0 || yi == 0) {
			continue;
		}

		//沿纹线找到第8个点
		pNow = pSrc + yi*pitch + xi;
		//if(GetByDis(pNow, &pDis, 8) != 0)
		if (GetPointByDis(pNow, &pDis, trace_len, pitch, forecolor, bina_type)!=0) {
			continue;
		}

		j++;
		//如果端点数目还是过多,则需要调整动态的最小距离var_dis,
		//这样特征点点周围没有的特征点的范围变大,特征点的数目将会减少
		//if(j >= FP_MAX_MINUTIA_NUM) {
		if (j >= FP_MAX_END_NUM) {
			flag = 0;	//flag == 0表示错误,需要调整动态的最小距离var_dis
			break;
		}
	}

	return flag;
}

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
 )
{
	//int32_t i, j;
	//int32_t forecolor = 0;	//图像前景色为黑点
	////int32_t backcolor = 255;//方向场背景色为白点
	////int32_t bina_type = 255;//0,255的二值类型
	//int32_t bina_type = BINA_TYPE;
	//int32_t trace_len = 8;	//沿纹线循迹的长度:设为8
	//int32_t xDis, yDis;		//沿纹线循迹的trace_len长度的点的坐标
	//uint8_t *pNow;
	//uint8_t *pDis;			//沿纹线循迹的trace_len长度的点的地址
	//int32_t xi, yi;			//第一,第二个端点的坐标
	//int32_t x11, y11;
	////int32_t flag;			//伪特征点标记, 0:伪特征点,1:真
	//int32_t angle1, angle2, angle3;
	//int32_t temp_angle;
	//MinutiaType_t temp_type;
	//int32_t temp_triangle[3];
	////int32_t nbminutia;
	//double a; 

	////j = minutia->nbminutia;
	////nbminutia = 0;
	//j = 0;
	//for (i = 0; i < minutia_num; i++) {
	//	xi = pMinutia[i].x;
	//	yi = pMinutia[i].y;
	//	//非有效端点
	//	if (xi == 0 || yi == 0) {
	//		continue;
	//	}
	//	//沿纹线找到第8个点
	//	pNow = pSrc + yi*pitch + xi;
	//	//if(GetByDis(pNow, &pDis, 8) != 0)
	//	if (GetPointByDis(pNow, &pDis, trace_len, pitch, forecolor, bina_type)!=0) {
	//		//沿纹线找到第8个点是否为前景点
	//		continue;
	//	}

	//	//求该点与端点连线的角度
	//	//获取沿纹线循迹的trace_len长度的点的坐标
	//	xDis = M_PX(pDis, pSrc, pitch);
	//	yDis = M_PX(pDis, pSrc, pitch);
	//	angle1 = XY2Angle(xi, yi, xDis, yDis);

	//	angle2 = *(pOrientation + yi*pitch + xi);

	//	angle3 = GetAngle360In360(angle1, angle2);

	//	//特征角度:0-360
	//	if(angle3 > 90 && angle3 < 270) {	//如果成钝角,则表示该特征点方向与该点方向场方向相反
	//		temp_angle = angle2 + 180;
	//	} else { //如果成锐角,则表示该特征点方向与该点方向场方向相同
	//		temp_angle = angle2;
	//	}

	//	//特征三角形角度(0-180)
	//	a = temp_angle / M_EPI + M_PI/4.0;
	//	x11 = xi + (int32_t)(trilen*cos(a) + 0.5);
	//	y11 = yi + (int32_t)(trilen*sin(a) + 0.5);
	//	temp_triangle[0] = *(pOrientation + y11*pitch + x11);

	//	a += M_PI*2/3.0;
	//	x11 = xi + (int32_t)(trilen*cos(a) + 0.5);
	//	y11 = yi + (int32_t)(trilen*sin(a) + 0.5);
	//	temp_triangle[1] = *(pOrientation + y11*pitch + x11);
	//	a += M_PI*2/3.0;

	//	x11 = xi + (int32_t)(trilen*cos(a) + 0.5);
	//	y11 = yi + (int32_t)(trilen*sin(a) + 0.5);
	//	temp_triangle[2] = *(pOrientation + y11*pitch + x11);

	//	//特征类型
	//	temp_type = MinutiaTypeEnd;
	//	//MinutiaSetAddV2(minutia, xi, yi, temp_type, temp_angle, temp_triangle);
	//	minutia->FPMinutiaArr[minutia->nbminutia].x = xi;
	//	minutia->FPMinutiaArr[minutia->nbminutia].y = yi;
	//	minutia->FPMinutiaArr[minutia->nbminutia].type = temp_type;
	//	minutia->FPMinutiaArr[minutia->nbminutia].angle = temp_angle;
	//	minutia->FPMinutiaArr[minutia->nbminutia].triangle[0] = temp_triangle[0];
	//	minutia->FPMinutiaArr[minutia->nbminutia].triangle[1] = temp_triangle[1];
	//	minutia->FPMinutiaArr[minutia->nbminutia].triangle[2] = temp_triangle[2];
	//	minutia->nbminutia++;
	//	j++;
	//}

	////调用FPMinutiaSetExtractEndAndFork或调用FPMinutiaSetExtractSingularity前
	////即获取指纹特征点集前,应该先初始化minutia->nbminutia = 0;
	////minutia->nbminutia += j;

	//return j;
	int32_t i, j;
	int32_t forecolor = 0;	//图像前景色为黑点
	//int32_t backcolor = 255;//方向场背景色为白点
	//int32_t bina_type = 255;//0,255的二值类型
	int32_t bina_type = BINA_TYPE;
	int32_t trace_len = 8;	//沿纹线循迹的长度:设为8
	int32_t xDis, yDis;		//沿纹线循迹的trace_len长度的点的坐标
	uint8_t *pNow;
	uint8_t *pDis;			//沿纹线循迹的trace_len长度的点的地址
	int32_t xi, yi;			//第一,第二个端点的坐标
	int32_t x11, y11;
	//int32_t flag;			//伪特征点标记, 0:伪特征点,1:真
	int32_t angle1, angle2, angle3;
	int32_t temp_angle;
	MinutiaType_t temp_type;
	int32_t temp_triangle[3];
	//int32_t nbminutia;
	//double a; 
	int32_t a;
	int32_t temp_sin;
	int32_t temp_cos;


	//j = minutia->nbminutia;
	//nbminutia = 0;
	j = 0;
	for (i = 0; i < minutia_num; i++) {
		xi = pMinutia[i].x;
		yi = pMinutia[i].y;
		//非有效端点
		if (xi == 0 || yi == 0) {
			continue;
		}
		//沿纹线找到第8个点
		pNow = pSrc + yi*pitch + xi;
		//if(GetByDis(pNow, &pDis, 8) != 0)
		if (GetPointByDis(pNow, &pDis, trace_len, pitch, forecolor, bina_type)!=0) {
			//沿纹线找到第8个点是否为前景点
			continue;
		}

		//求该点与端点连线的角度
		//获取沿纹线循迹的trace_len长度的点的坐标
		xDis = M_PX(pDis, pSrc, pitch);
		yDis = M_PX(pDis, pSrc, pitch);
		angle1 = XY2Angle(xi, yi, xDis, yDis);

		angle2 = *(pOrientation + yi*pitch + xi);

		angle3 = GetAngle360In360(angle1, angle2);

		//特征角度:0-360
		if(angle3 > 90 && angle3 < 270) {	//如果成钝角,则表示该特征点方向与该点方向场方向相反
			temp_angle = angle2 + 180;
		} else { //如果成锐角,则表示该特征点方向与该点方向场方向相同
			temp_angle = angle2;
		}

		//特征三角形角度(0-180)
		//a = temp_angle / M_EPI + M_PI/4.0;
		//x11 = xi + (int32_t)(trilen*cos(a) + 0.5);
		//y11 = yi + (int32_t)(trilen*sin(a) + 0.5);
		a = temp_angle+45;
		if (a >= 0 && a <= 360) {
			//temp_angle = a;
		} else {
			a = a - 360;
		}
		temp_cos = get_sin_cos(a, 0);
		temp_sin = get_sin_cos(a, 1);
		x11 = (xi*10000 + trilen*temp_cos)/10000;
		y11 = (yi*10000 + trilen*temp_sin)/10000;
		temp_triangle[0] = *(pOrientation + y11*pitch + x11);

		//a += M_PI*2/3.0;
		//x11 = xi + (int32_t)(trilen*cos(a) + 0.5);
		//y11 = yi + (int32_t)(trilen*sin(a) + 0.5);
		a += 120;
		if (a >= 0 && a <= 360) {
			//temp_angle = a;
		} else {
			a = a - 360;
		}
		temp_cos = get_sin_cos(a, 0);
		temp_sin = get_sin_cos(a, 1);
		x11 = (xi*10000 + trilen*temp_cos)/10000;
		y11 = (yi*10000 + trilen*temp_sin)/10000;
		temp_triangle[1] = *(pOrientation + y11*pitch + x11);
		//a += M_PI*2/3.0;

		a += 120;
		if (a >= 0 && a <= 360) {
			//temp_angle = a;
		} else {
			a = a - 360;
		}
		//x11 = xi + (int32_t)(trilen*cos(a) + 0.5);
		//y11 = yi + (int32_t)(trilen*sin(a) + 0.5);
		temp_cos = get_sin_cos(a, 0);
		temp_sin = get_sin_cos(a, 1);
		x11 = (xi*10000 + trilen*temp_cos)/10000;
		y11 = (yi*10000 + trilen*temp_sin)/10000;
		temp_triangle[2] = *(pOrientation + y11*pitch + x11);

		//特征类型
		temp_type = MinutiaTypeEnd;
		//MinutiaSetAddV2(minutia, xi, yi, temp_type, temp_angle, temp_triangle);
		minutia->FPMinutiaArr[minutia->nbminutia].x = xi;
		minutia->FPMinutiaArr[minutia->nbminutia].y = yi;
		minutia->FPMinutiaArr[minutia->nbminutia].type = temp_type;
		minutia->FPMinutiaArr[minutia->nbminutia].angle = temp_angle;
		minutia->FPMinutiaArr[minutia->nbminutia].triangle[0] = temp_triangle[0];
		minutia->FPMinutiaArr[minutia->nbminutia].triangle[1] = temp_triangle[1];
		minutia->FPMinutiaArr[minutia->nbminutia].triangle[2] = temp_triangle[2];
		minutia->nbminutia++;
		if (minutia->nbminutia >= FP_MAX_MINUTIA_NUM) {
			break;
		}
		j++;
	}

	//调用FPMinutiaSetExtractEndAndFork或调用FPMinutiaSetExtractSingularity前
	//即获取指纹特征点集前,应该先初始化minutia->nbminutia = 0;
	//minutia->nbminutia += j;

	return j;
}

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
 )
{
	//int32_t i, j;
	////int32_t forecolor = 0;	//图像前景色为黑点
	////int32_t backcolor = 255;//方向场背景色为白点
	////int32_t bina_type = 255;//0,255的二值类型
	////int32_t bina_type = BINA_TYPE;
	////int32_t trace_len = 8;	//沿纹线循迹的长度:设为8
	////uint8_t *pNow;
	//int32_t xi, yi, xj, yj;	//第一,第二个端点的坐标
	//int32_t flag;		//伪特征点标记, 0:伪特征点,1:真
	//double d;

	////去掉距离太近的叉点
	//for (i = 0; i < minutia_num-1; i++) {
	//	flag = 1;
	//	xi = pMinutia[i].x;
	//	yi = pMinutia[i].y;
	//	for(j = i+1; j < minutia_num; j++) {
	//		xj = pMinutia[j].x;
	//		yj = pMinutia[j].y;
	//		d = sqrt((double)((xi-xj)*(xi-xj) + (yi-yj)*(yi-yj)));

	//		if (d <= var_dis-2) {
	//			pMinutia[j].x = 0;
	//			pMinutia[j].y = 0;
	//			flag = 0;
	//		}
	//	}
	//	if (flag == 0) {
	//		pMinutia[i].x = 0;
	//		pMinutia[i].y = 0;
	//	}
	//}
	//return flag;
	int32_t i, j;
	//int32_t forecolor = 0;	//图像前景色为黑点
	//int32_t backcolor = 255;//方向场背景色为白点
	//int32_t bina_type = 255;//0,255的二值类型
	//int32_t bina_type = BINA_TYPE;
	//int32_t trace_len = 8;	//沿纹线循迹的长度:设为8
	//uint8_t *pNow;
	int32_t xi, yi, xj, yj;	//第一,第二个端点的坐标
	int32_t flag = 0;		//伪特征点标记, 0:伪特征点,1:真
	//double d;

	int32_t d;
	int32_t d_var_dis = (var_dis-2)*(var_dis-2);

	//去掉距离太近的叉点
	for (i = 0; i < minutia_num-1; i++) {
		flag = 1;
		xi = pMinutia[i].x;
		yi = pMinutia[i].y;
		for(j = i+1; j < minutia_num; j++) {
			xj = pMinutia[j].x;
			yj = pMinutia[j].y;
			//d = sqrt((double)((xi-xj)*(xi-xj) + (yi-yj)*(yi-yj)));
			d = ((xi-xj)*(xi-xj) + (yi-yj)*(yi-yj));

			if (d <= d_var_dis) {
				pMinutia[j].x = 0;
				pMinutia[j].y = 0;
				flag = 0;
			}
		}
		if (flag == 0) {
			pMinutia[i].x = 0;
			pMinutia[i].y = 0;
		}
	}
	return flag;
}

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
 )
{
	int32_t i, j;
	int32_t k, n;
	int32_t forecolor = 0;	//图像前景色为黑点
	//int32_t backcolor = 255;//方向场背景色为白点
	int32_t backcolor = BACKCOLOR;
	//int32_t bina_type = 255;//0,255的二值类型
	//int32_t bina_type = BINA_TYPE;
	//int32_t trace_len = 8;	//沿纹线循迹的长度:设为8
	uint8_t *pNow;
	int32_t xi, yi;	//第一,第二个端点的坐标
	int32_t flag;		//伪特征点标记, 0:伪特征点,1:真
	//// 某点周围8个点的地址偏移
	//int32_t	SiteU8[8] = {pitch-1, pitch, pitch+1, 1, -pitch+1, -pitch, -pitch-1, -1};
	int32_t SiteD8[8];
	uint8_t *tempPtr[8];
	
	SiteD8[0] = pitch-1;	SiteD8[1] = pitch;		SiteD8[2] = pitch+1;
	SiteD8[3] = 1;			SiteD8[4] = 1-pitch;	SiteD8[5] = -pitch;
	SiteD8[6] = -pitch-1;	SiteD8[7] = -1;
	
	//统计新的真正的叉点
	flag = 1;
	j = 0;
	for (i = 0; i < minutia_num; i++) {
		xi = pMinutia[i].x;
		yi = pMinutia[i].y;
		//非有效叉点
		if (xi == 0 || yi == 0) {
			continue;
		}
		pNow = pSrc + yi*pitch + xi;

		tempPtr[0] = pNow;
		//*tempPtr[0] = 255;			//设为背景点
		*tempPtr[0] = backcolor;		//设为背景点

		//检查是否真正叉点
		n = 0;
		for (k = 0; k < 8; k++) {
			if(*(pNow + SiteD8[k]) == 0) {
				tempPtr[n+1] = pNow + SiteD8[k];
				//*tempPtr[n+1] = 255;	//设为背景点
				*tempPtr[n+1] = backcolor;	//设为背景点
				n++;
			}
		}
		for (k = 0; k < 4; k++) {
			//*tempPtr[k] = 0;			//恢复4个为前景点
			*tempPtr[k] = forecolor;	//恢复4个为前景点
		}
		if (n != 3) {
			continue;
		}
		j++;

		//如果特征点总数还是过多,则需要调整var_dis,
		//这样特征点点周围没有的特征点的范围变大,特征点的数目将会减少
		//if(EndNum + j >= FP_MAX_MINUTIA_NUM) {
		//if (j >= FP_MAX_MINUTIA_NUM) {
		if (j >= FP_MAX_FORK_NUM) {
			flag = 0;	//flag == 0表示错误,需要调整动态的最小距离var_dis
			break;
		}
	}
	return flag;
}

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
 )
{
	//int32_t i, j;
	//int32_t n, k;
	//int32_t forecolor = 0;	//图像前景色为黑点
	////int32_t backcolor = 255;//方向场背景色为白点
	//int32_t backcolor = BACKCOLOR;
	////int32_t bina_type = 255;//0,255的二值类型
	//int32_t bina_type = BINA_TYPE;
	//int32_t trace_len = 8;	//沿纹线循迹的长度:设为8
	////沿纹线循迹的trace_len长度的点的坐标
	//int32_t xDis0, yDis0, xDis1, yDis1, xDis2, yDis2;		
	//uint8_t *pNow;
	////uint8_t *pDis;			//沿纹线循迹的trace_len长度的点的地址
	//uint8_t *tempPtr[8];
	//uint8_t *disPtr[3];
	////int32_t	SiteU8[8] = {pitch-1, pitch, pitch+1, 1, -pitch+1, -pitch, -pitch-1, -1};
	//int32_t xi, yi;			//第一,第二个端点的坐标
	//int32_t x11, y11;
	//int32_t x21, y21;
	////int32_t flag;			//伪特征点标记, 0:伪特征点,1:真
	//int32_t angle1, angle2, angle3;
	//int32_t temp_angle;
	//MinutiaType_t temp_type;
	//int32_t temp_triangle[3];

	//double d0, d1, d2, a; 
	//int32_t SiteD8[8];
	//SiteD8[0] = pitch-1;	SiteD8[1] = pitch;		SiteD8[2] = pitch+1;
	//SiteD8[3] = 1;			SiteD8[4] = 1-pitch;	SiteD8[5] = -pitch;
	//SiteD8[6] = -pitch-1;	SiteD8[7] = -1;

	////j = minutia->nbminutia;
	//j = 0;
	//for (i = 0; i < minutia_num; i++) {
	//	xi = pMinutia[i].x;
	//	yi = pMinutia[i].y;
	//	if (xi == 0 || yi == 0) {
	//		continue;
	//	}

	//	pNow = pSrc + yi*pitch + xi;

	//	tempPtr[0] = pNow;
	//	//*tempPtr[0] = 255;				//设为背景点
	//	*tempPtr[0] = backcolor;			//设为背景点
	//	//检查是否真正叉点
	//	n = 0;
	//	for(k = 0; k < 8; k++) {
	//		if(*(pNow + SiteD8[k]) == 0) {
	//			tempPtr[n+1] = pNow + SiteD8[k];
	//			//*tempPtr[n+1] = 255;	//设为背景点
	//			*tempPtr[n+1] = backcolor;	//设为背景点
	//			n++;
	//		}
	//	}
	//	if(n != 3) {
	//		continue;
	//	}
	//	//找到叉点三个方向纹线上距离为8的点
	//	for(k = 0; k < 3; k++) {
	//		GetPointByDis(tempPtr[k+1], &disPtr[k], trace_len, pitch, forecolor, bina_type);
	//	}

	//	for(k = 0; k < 4; k++) {
	//		//*tempPtr[k] = 0;	//恢复4个为前景点
	//		*tempPtr[k] = forecolor;	//恢复4个为前景点
	//	}

	//	//求该三个点两两间的距离
	//	xDis0 = M_PX(disPtr[0], pSrc, pitch);
	//	yDis0 = M_PY(disPtr[0], pSrc, pitch);
	//	xDis1 = M_PX(disPtr[1], pSrc, pitch);
	//	yDis1 = M_PY(disPtr[1], pSrc, pitch);
	//	xDis2 = M_PX(disPtr[2], pSrc, pitch);
	//	yDis2 = M_PY(disPtr[2], pSrc, pitch);

	//	d0 = sqrt((double)(xDis1-xDis2)*(xDis1-xDis2) + (yDis1-yDis2)*(yDis1-yDis2));

	//	d1 = sqrt((double)(xDis0-xDis2)*(xDis0-xDis2) + (yDis0-yDis2)*(yDis0-yDis2));

	//	d2 = sqrt((double)(xDis1-xDis0)*(xDis1-xDis0) + (yDis1-yDis0)*(yDis1-yDis0));

	//	//距离最短的边对应的是叉线方向
	//	if(d0 < d1 && d0 < d2) {
	//		//disPtr[1],disPtr[2]
	//		x11 = xDis1;
	//		y11 = yDis1;
	//		x21 = xDis2;
	//		y21 = yDis2;
	//		//pDis = disPtr[0];
	//	} else if(d1 < d0 && d1 < d2) {
	//		//disPtr[0],disPtr[2]
	//		x11 = xDis0;
	//		y11 = yDis0;
	//		x21 = xDis2;
	//		y21 = yDis2;
	//		//pDis = disPtr[1];
	//	} else {
	//		//disPtr[0],disPtr[1]
	//		x11 = xDis0;
	//		y11 = yDis0;
	//		x21 = xDis1;
	//		y21 = yDis1;
	//		//pDis = disPtr[2];
	//	}

	//	//求最短边中点与叉点连线的方向与该点方向场方向的夹角
	//	angle1 = XY2Angle(xi, yi, (x11+x21)/2, (y11+y21)/2);

	//	angle2 = *(pOrientation + yi*pitch + xi);

	//	angle3 = GetAngle360In360(angle1, angle2);

	//	//特征角度:0-360
	//	// 如果成钝角，则表示该特征点方向与该点方向场方向相反
	//	if(angle3 > 90 && angle3 < 270) {
	//		temp_angle = angle2 + 180;
	//	} else {// 如果成锐角，则表示该特征点方向与该点方向场方向相同
	//		temp_angle = angle2;
	//	}

	//	//特征三角形角度(0-180)	
	//	//纪录以特征点为中心外接圆半径为trilen的正三角形三个顶点的方向
	//	a = temp_angle / M_EPI + M_PI/4.0;
	//	x11 = xi + (int32_t)(trilen*cos(a) + 0.5);
	//	y11 = yi + (int32_t)(trilen*sin(a) + 0.5);
	//	temp_triangle[0] = *(pOrientation+y11*pitch+x11);

	//	a += M_PI*2/3.0;
	//	x11 = xi + (int32_t)(trilen*cos(a) + 0.5);
	//	y11 = yi + (int32_t)(trilen*sin(a) + 0.5);
	//	temp_triangle[1] = *(pOrientation+y11*pitch+x11);

	//	a += M_PI*2/3.0;
	//	x11 = xi + (int32_t)(trilen*cos(a) + 0.5);
	//	y11 = yi + (int32_t)(trilen*sin(a) + 0.5);
	//	temp_triangle[2] = *(pOrientation+y11*pitch+x11);

	//	//特征类型
	//	temp_type = MinutiaTypeFork;

	//	//MinutiaSetAddV2(minutia, xi, yi, temp_type, temp_angle, temp_triangle);
	//	minutia->FPMinutiaArr[minutia->nbminutia].x = xi;
	//	minutia->FPMinutiaArr[minutia->nbminutia].y = yi;
	//	minutia->FPMinutiaArr[minutia->nbminutia].type = temp_type;
	//	minutia->FPMinutiaArr[minutia->nbminutia].angle = temp_angle;
	//	minutia->FPMinutiaArr[minutia->nbminutia].triangle[0] = temp_triangle[0];
	//	minutia->FPMinutiaArr[minutia->nbminutia].triangle[1] = temp_triangle[1];
	//	minutia->FPMinutiaArr[minutia->nbminutia].triangle[2] = temp_triangle[2];
	//	minutia->nbminutia++;
	//	j++;
	//}

	////调用FPMinutiaSetExtractEndAndFork或调用FPMinutiaSetExtractSingularity前
	////即获取指纹特征点集前,应该先初始化minutia->nbminutia = 0;
	////minutia->nbminutia += j;

	//return j; // 叉点数目
	int32_t i, j;
	int32_t n, k;
	int32_t forecolor = 0;	//图像前景色为黑点
	//int32_t backcolor = 255;//方向场背景色为白点
	int32_t backcolor = BACKCOLOR;
	//int32_t bina_type = 255;//0,255的二值类型
	int32_t bina_type = BINA_TYPE;
	int32_t trace_len = 8;	//沿纹线循迹的长度:设为8
	//沿纹线循迹的trace_len长度的点的坐标
	int32_t xDis0, yDis0, xDis1, yDis1, xDis2, yDis2;		
	uint8_t *pNow;
	//uint8_t *pDis;			//沿纹线循迹的trace_len长度的点的地址
	uint8_t *tempPtr[8];
	uint8_t *disPtr[3];
	//int32_t	SiteU8[8] = {pitch-1, pitch, pitch+1, 1, -pitch+1, -pitch, -pitch-1, -1};
	int32_t xi, yi;			//第一,第二个端点的坐标
	int32_t x11, y11;
	int32_t x21, y21;
	//int32_t flag;			//伪特征点标记, 0:伪特征点,1:真
	int32_t angle1, angle2, angle3;
	int32_t temp_angle;
	MinutiaType_t temp_type;
	int32_t temp_triangle[3];

	//double d0, d1, d2, a, a1; 
	
	int32_t d0, d1, d2;
	//double a, a1;
	int32_t a, temp_cos, temp_sin;

	int32_t SiteD8[8];
	SiteD8[0] = pitch-1;	SiteD8[1] = pitch;		SiteD8[2] = pitch+1;
	SiteD8[3] = 1;			SiteD8[4] = 1-pitch;	SiteD8[5] = -pitch;
	SiteD8[6] = -pitch-1;	SiteD8[7] = -1;

	//j = minutia->nbminutia;
	j = 0;
	for (i = 0; i < minutia_num; i++) {
		xi = pMinutia[i].x;
		yi = pMinutia[i].y;
		if (xi == 0 || yi == 0) {
			continue;
		}

		pNow = pSrc + yi*pitch + xi;

		tempPtr[0] = pNow;
		//*tempPtr[0] = 255;				//设为背景点
		*tempPtr[0] = backcolor;			//设为背景点
		//检查是否真正叉点
		n = 0;
		for(k = 0; k < 8; k++) {
			if(*(pNow + SiteD8[k]) == 0) {
				tempPtr[n+1] = pNow + SiteD8[k];
				//*tempPtr[n+1] = 255;	//设为背景点
				*tempPtr[n+1] = backcolor;	//设为背景点
				n++;
			}
		}
		if(n != 3) {
			continue;
		}
		//找到叉点三个方向纹线上距离为8的点
		for(k = 0; k < 3; k++) {
			GetPointByDis(tempPtr[k+1], &disPtr[k], trace_len, pitch, forecolor, bina_type);
		}

		for(k = 0; k < 4; k++) {
			//*tempPtr[k] = 0;	//恢复4个为前景点
			*tempPtr[k] = forecolor;	//恢复4个为前景点
		}

		//求该三个点两两间的距离
		xDis0 = M_PX(disPtr[0], pSrc, pitch);
		yDis0 = M_PY(disPtr[0], pSrc, pitch);
		xDis1 = M_PX(disPtr[1], pSrc, pitch);
		yDis1 = M_PY(disPtr[1], pSrc, pitch);
		xDis2 = M_PX(disPtr[2], pSrc, pitch);
		yDis2 = M_PY(disPtr[2], pSrc, pitch);

		//d0 = sqrt((double)(xDis1-xDis2)*(xDis1-xDis2) + (yDis1-yDis2)*(yDis1-yDis2));

		//d1 = sqrt((double)(xDis0-xDis2)*(xDis0-xDis2) + (yDis0-yDis2)*(yDis0-yDis2));

		//d2 = sqrt((double)(xDis1-xDis0)*(xDis1-xDis0) + (yDis1-yDis0)*(yDis1-yDis0));

		d0 = (xDis1-xDis2)*(xDis1-xDis2) + (yDis1-yDis2)*(yDis1-yDis2);
		d1 = (xDis0-xDis2)*(xDis0-xDis2) + (yDis0-yDis2)*(yDis0-yDis2);
		d2 = (xDis1-xDis0)*(xDis1-xDis0) + (yDis1-yDis0)*(yDis1-yDis0);

		//距离最短的边对应的是叉线方向
		if(d0 < d1 && d0 < d2) {
			//disPtr[1],disPtr[2]
			x11 = xDis1;
			y11 = yDis1;
			x21 = xDis2;
			y21 = yDis2;
			//pDis = disPtr[0];
		} else if(d1 < d0 && d1 < d2) {
			//disPtr[0],disPtr[2]
			x11 = xDis0;
			y11 = yDis0;
			x21 = xDis2;
			y21 = yDis2;
			//pDis = disPtr[1];
		} else {
			//disPtr[0],disPtr[1]
			x11 = xDis0;
			y11 = yDis0;
			x21 = xDis1;
			y21 = yDis1;
			//pDis = disPtr[2];
		}

		//求最短边中点与叉点连线的方向与该点方向场方向的夹角
		angle1 = XY2Angle(xi, yi, (x11+x21)/2, (y11+y21)/2);

		angle2 = *(pOrientation + yi*pitch + xi);

		angle3 = GetAngle360In360(angle1, angle2);

		//特征角度:0-360
		// 如果成钝角，则表示该特征点方向与该点方向场方向相反
		if(angle3 > 90 && angle3 < 270) {
			temp_angle = angle2 + 180;
		} else {// 如果成锐角，则表示该特征点方向与该点方向场方向相同
			temp_angle = angle2;
		}

		//特征三角形角度(0-180)	
		//纪录以特征点为中心外接圆半径为trilen的正三角形三个顶点的方向
		//a = temp_angle / M_EPI + M_PI/4.0;
		//a1 = cos(a);
		//a1 = a1*trilen;
		a = temp_angle+45;
		if (a >= 0 && a <= 360) {
			//temp_angle = a;
		} else {
			a = a - 360;
		}
		temp_cos = get_sin_cos(a, 0);
		temp_sin = get_sin_cos(a, 1);
		x11 = (xi*10000 + trilen*temp_cos)/10000;
		y11 = (yi*10000 + trilen*temp_sin)/10000;
		//x11 = xi + (int32_t)(trilen*cos(a) + 0.5);
		//y11 = yi + (int32_t)(trilen*sin(a) + 0.5);
		temp_triangle[0] = *(pOrientation+y11*pitch+x11);

		//a += M_PI*2/3.0;
		a += 120;
		//x11 = xi + (int32_t)(trilen*cos(a) + 0.5);
		//y11 = yi + (int32_t)(trilen*sin(a) + 0.5);
		if (a >= 0 && a <= 360) {
			//temp_angle = a;
		} else {
			a = a - 360;
		}
		temp_cos = get_sin_cos(a, 0);
		temp_sin = get_sin_cos(a, 1);
		x11 = (xi*10000 + trilen*temp_cos)/10000;
		y11 = (yi*10000 + trilen*temp_sin)/10000;
		temp_triangle[1] = *(pOrientation+y11*pitch+x11);

		//a += M_PI*2/3.0;
		a += 120;
		//x11 = xi + (int32_t)(trilen*cos(a) + 0.5);
		//y11 = yi + (int32_t)(trilen*sin(a) + 0.5);
		if (a >= 0 && a <= 360) {
			//temp_angle = a;
		} else {
			a = a - 360;
		}
		temp_cos = get_sin_cos(a, 0);
		temp_sin = get_sin_cos(a, 1);
		x11 = (xi*10000 + trilen*temp_cos)/10000;
		y11 = (yi*10000 + trilen*temp_sin)/10000;
		temp_triangle[2] = *(pOrientation+y11*pitch+x11);

		//特征类型
		temp_type = MinutiaTypeFork;

		//MinutiaSetAddV2(minutia, xi, yi, temp_type, temp_angle, temp_triangle);
		minutia->FPMinutiaArr[minutia->nbminutia].x = xi;
		minutia->FPMinutiaArr[minutia->nbminutia].y = yi;
		minutia->FPMinutiaArr[minutia->nbminutia].type = temp_type;
		minutia->FPMinutiaArr[minutia->nbminutia].angle = temp_angle;
		minutia->FPMinutiaArr[minutia->nbminutia].triangle[0] = temp_triangle[0];
		minutia->FPMinutiaArr[minutia->nbminutia].triangle[1] = temp_triangle[1];
		minutia->FPMinutiaArr[minutia->nbminutia].triangle[2] = temp_triangle[2];
		minutia->nbminutia++;
		if (minutia->nbminutia >= FP_MAX_MINUTIA_NUM) {
			break;
		}
		j++;
	}

	//调用FPMinutiaSetExtractEndAndFork或调用FPMinutiaSetExtractSingularity前
	//即获取指纹特征点集前,应该先初始化minutia->nbminutia = 0;
	//minutia->nbminutia += j;

	return j; // 叉点数目
}

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
 )
{
	int32_t i;
	//int32_t r = 16;			//允许特征点靠近前景边缘的最近距离
	//int32_t ori_thr = 96;	//方向场变化剧烈程度
	int32_t fixed_dis = 16;	//允许两个特征点间最近的距离
	int32_t var_dis = 7;	//允许两个特征点间最近的距离,由bGood决定是否需要增加
	//int32_t trace_len = 8;	//纹线跟踪长度(默认为8)
	int32_t trilen = 16;	//正三角形外接圆半径

	int32_t tempForkNum;
	int32_t tempEndNum;
	int32_t ForkNum;
	int32_t EndNum;

	int32_t bGood = 0;	//标记阈值是否调整好,使特征点数目在允许范围内
	int32_t loopnum;	//循环次数,最大循环设为32


	//临时特征点数组
	Point_t tempFork[FP_MAX_RAW_MINUTIA_NUM];
	Point_t tempEnd[FP_MAX_RAW_MINUTIA_NUM];
	Point_t ForkArr[FP_MAX_RAW_MINUTIA_NUM];
	Point_t EndArr[FP_MAX_RAW_MINUTIA_NUM];

	// 初始化临时特征点数组
	for (i = 0; i < FP_MAX_RAW_MINUTIA_NUM; i++){
		tempFork[i].x = 0;
		tempFork[i].y = 0;
		tempEnd[i].x = 0;
		tempEnd[i].y = 0;
		ForkArr[i].x = 0;
		ForkArr[i].y = 0;
		EndArr[i].x = 0;
		EndArr[i].y = 0;
	}

	//第一遍寻找所有端点和叉点	
	ForkNum = 0; 
	EndNum = 0; 

	GetRawEndAndFork(pSrc, pOrientation, ForkArr, &ForkNum, EndArr, &EndNum, width, height, pitch);

	//初始化临时缓冲区,准备循环调整两个特征点间允许的最小距离,使之增大到一个合适的值
	//因为如果特征点非常密集的地方很有可能是质量很差的地方
	for(i = 0; i < FP_MAX_RAW_MINUTIA_NUM; i++) {
		tempEnd[i] = EndArr[i];
	}
	for(i = 0; i < FP_MAX_RAW_MINUTIA_NUM; i++) {
		tempFork[i] = ForkArr[i];
	}
	tempForkNum = ForkNum;
	tempEndNum = EndNum;

	//循环调整
	bGood = 0;
	loopnum = 0;	// 调整的次数
	//while(!bGood && loopnum < 32) {	//最多调整32次
	while (!bGood && loopnum < 8) {
		loopnum++;	// 调整次数加一
		//得到新的特征点数组
		for(i = 0; i < FP_MAX_RAW_MINUTIA_NUM; i++) {
			EndArr[i].x = tempEnd[i].x;
			EndArr[i].y = tempEnd[i].y;
		}
		for(i = 0; i < FP_MAX_RAW_MINUTIA_NUM; i++) {
			ForkArr[i].x = tempFork[i].x;
			ForkArr[i].y = tempFork[i].y;
		}
		//新的特征点数
		ForkNum = tempForkNum;	//叉点
		EndNum = tempEndNum;	//端点

		//去掉虚假的端点
		bGood = 1;
		ClearFakeEnd(pSrc, EndArr, EndNum, fixed_dis, var_dis, pitch);

		bGood = GetRealEnd(pSrc, EndArr, EndNum, pitch);
		//调整var_dis
		if(!bGood) {
			var_dis++; // 加一
			continue;
		}

		EndNum = FPAddEnd(minutia, pSrc, pOrientation, EndArr, EndNum, trilen, pitch);

		ClearFakeFork(pSrc, ForkArr, ForkNum, var_dis, pitch);

		bGood = GetRealFork(pSrc, ForkArr, ForkNum, pitch);

		if(!bGood) {
			var_dis++; // 加一
			continue;
		}

		ForkNum = FPAddFork(minutia, pSrc, pOrientation, ForkArr, ForkNum, trilen, pitch);

	}
	//如果循环32次都不能得到理想结果，则表示图像质量差，返回错误
	//if(loopnum >= 32) {
	if (loopnum >= 8) {
		//MinutiaSetEmpty(minutia);
		//minutia->nbminutia = 0;
		return 1;
	}

	//特征点数目太少则返回错误
	if(ForkNum + EndNum < 8) {
		//MinutiaSetEmpty(minutia);
		minutia->nbminutia = 0;
		return 1;
	}

	return 0;
}

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
 )
{
	//minutia->nbminutia = 0;

	//FPMinutiaSetExtractSingularity(minutia, pOri, width, height, pitch, 0);
	//FPMinutiaSetExtractSingularity(minutia, pOri, width, height, pitch, 1);
	//FPMinutiaSetExtractEndAndFork(minutia, pSrc, pOri, width, height, pitch, forecolor, backcolor, bina_type);
	int32_t err = 0;
	minutia->nbminutia = 0;

	FPMinutiaSetExtractSingularity(minutia, pOri, width, height, pitch, 0);
	FPMinutiaSetExtractSingularity(minutia, pOri, width, height, pitch, 1);
	err = FPMinutiaSetExtractEndAndFork(minutia, pSrc, pOri, width, height, pitch, forecolor, backcolor, bina_type);
	if (err == 1) {
		return FunError;
	}
	if (minutia->nbminutia > 60) {
		minutia->nbminutia = 60;
		return FunError;
	}

	return FunOK;
}

