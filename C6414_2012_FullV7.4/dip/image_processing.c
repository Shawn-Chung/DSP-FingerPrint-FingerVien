/******************************************************************************
 * 文件名：image_processing.c
 * 功  能：图像处理函数
******************************************************************************/


#include "dip_header/image_processing.h"
//#include "../../bsp/bsp_header/z_mytype.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>


//static int32_t tmplt9[9] = {
//	0, 1, 0,
//	1, 1, 1,
//	0, 1, 0,
//};
//static int32_t tmplt_w = 3;
//static int32_t tmplt_s = 5;

/******************************************************************************
  * 功能：对静脉图像进行处理
  * 参数：image			   静脉图像
  *		  smooth_w		   均值平滑模版尺寸
  *		  cur_t			   曲率分割类型
  *		  cur_w			   曲率微分计算尺寸
  *		  tmplt_w		   腐蚀,膨胀结构元素尺寸
  *		  tmpltA		   腐蚀,膨胀结构元素
  *		  tmplt_s		   腐蚀,膨胀结构元素之和
  *		  minutia		   细节点集
  *		  region_ath	   连通域阈值
  * 返回：错误编号
******************************************************************************/
FunError_t FVImageProcessing
(
 Image_t *image_org,
 Image_t *image,
 Image_t *imageG,
 const int32_t smooth_w,
 const int32_t cur_t,
 const int32_t cur_w,
 const int32_t fore_area_thr,
 const int32_t back_area_thr,
 //const int32_t tmplt_w,
 //int32_t *tmpltA,
 //const int32_t tmplt_s,
 pFVMinutiaSet_t minutia,
 const int32_t burr_thr
)
{
	
	int32_t region_num[256];
	int32_t i;
	//int32_t tmpltD[25] = {
	//	0, 0, 1, 0, 0,
	//	0, 1, 1, 1, 0,
	//	1, 1, 1, 1, 1,
	//	0, 1, 1, 1, 0,
	//	0, 0, 1, 0, 0,
	//};
	////int32_t tmplt9[9] = {
	////	0, 1, 0,
	////	1, 1, 1,
	////	0, 1, 0,
	////};
	//int32_t tmplt_w = 5;
	//int32_t tmplt_s = 13;

	for (i = 0; i < 256; i++) {
		region_num[i] = 0;
	}


//#define FV_STEP_TEST
#define FV_ALL_TEST

#ifdef FV_STEP_TEST
	//get_fixed_roi(image->pimg, FV_WIDTH, FV_HEIGHT, FV_PITCH, image_org->pimg, 0, 35, FV_WIDTH_ORG, FV_HEIGHT_ORG, FV_PITCH_ORG);
	ImageCopy32(image, image_org);
	ImageExport(image, FINGER_VEIN);

	//ImageCopy32(&fv_src_copy, image);
	//GrayNormalize(image->pimg, fv_src_copy.pimg, FV_WIDTH, FV_HEIGHT, FV_PITCH);

	ImageExport(image, FINGER_TEST);

	ImageCopy32(&fv_src_copy, image);
	MeanSmoothV1(image->pimg, fv_src_copy.pimg, FV_WIDTH, FV_HEIGHT, FV_PITCH, smooth_w, 1);

	ImageExport(image, FINGER_TEST);
	
	//分割:最大曲率分割方法
	ImageCopy32(&fv_src_copy, image);
	CurvatureSegment(image->pimg, fv_src_copy.pimg, cur_t, cur_w, 0, FV_WIDTH, FV_HEIGHT, FV_PITCH);
	ImageExport(image, FINGER_TEST);
	//MeanBinary(image->pimg, fv_src_copy.pimg, 11, 3, FV_WIDTH, FV_HEIGHT, FV_PITCH);
	//ImageExport(image, FINGER_VEIN);

	//
	ImageCopy32(&fv_src_copy, image);
	MeanSmoothV1(image->pimg, fv_src_copy.pimg, FV_WIDTH, FV_HEIGHT, FV_PITCH, 7, 1);
	//ImageCopy32(&fv_src_copy, image);
	//GrayNormalize(image->pimg, fv_src_copy.pimg, FV_WIDTH, FV_HEIGHT, FV_PITCH);
	//ImageExport(image, FINGER_VEIN);
	ImageCopy32(&fv_src_copy, image);
	OverallBinary(image->pimg, fv_src_copy.pimg, cur_w, cur_w, FV_WIDTH-2*cur_w-7, FV_HEIGHT-2*cur_w-7, 0, FV_WIDTH, FV_HEIGHT, FV_PITCH);

	change_edge_color(image->pimg, 10, 9, 105, 286, 0, FV_WIDTH, FV_HEIGHT, FV_PITCH);

	BinaryExchange(image->pimg, FV_WIDTH, FV_HEIGHT, TOWB);
	ImageExport(image, FINGER_VEIN);
	BinaryExchange(image->pimg, FV_WIDTH, FV_HEIGHT, TOOZ);

	//ImageCopy32(&fv_src_copy, image);
	//UniDilateOZ(image->pimg, fv_src_copy.pimg, tmplt_w, tmpltD, tmplt_s, FV_WIDTH, FV_HEIGHT, FV_PITCH);

	//BinaryExchange(image->pimg, FV_WIDTH, FV_HEIGHT, TOWB);
	//ImageExport(image, FINGER_TEST);
	//BinaryExchange(image->pimg, FV_WIDTH, FV_HEIGHT, TOOZ);

	RegionMarkOZ(image->pimg, region_num, FV_WIDTH, FV_HEIGHT, FV_PITCH);
	RegionAreaFilter(image->pimg, region_num, fore_area_thr, back_area_thr, FV_WIDTH, FV_HEIGHT, FV_PITCH);

	BinaryExchange(image->pimg, FV_WIDTH, FV_HEIGHT, TOWB);
	ImageExport(image, FINGER_VEIN);
	BinaryExchange(image->pimg, FV_WIDTH, FV_HEIGHT, TOOZ);

	ConditionThiningOZ(image->pimg, FV_WIDTH, FV_HEIGHT, FV_PITCH);

	BinaryExchange(image->pimg, FV_WIDTH, FV_HEIGHT, TOWB);
	ImageExport(image, FINGER_TEST);
	BinaryExchange(image->pimg, FV_WIDTH, FV_HEIGHT, TOOZ);

	//ImageCopy32(&fv_src_copy, image);
	//UniDilateOZ(image->pimg, fv_src_copy.pimg, tmplt_w, tmpltD, tmplt_s, FV_WIDTH, FV_HEIGHT, FV_PITCH);
	//ImageCopy32(&fv_src_copy, image);
	//UniDilateOZ(image->pimg, fv_src_copy.pimg, tmplt_w, tmpltD, tmplt_s, FV_WIDTH, FV_HEIGHT, FV_PITCH);

	//BinaryExchange(image->pimg, FV_WIDTH, FV_HEIGHT, TOWB);
	//ImageExport(image, FINGER_TEST);
	//BinaryExchange(image->pimg, FV_WIDTH, FV_HEIGHT, TOOZ);

	//SkeletonBurrClearV1(image->pimg, 10, FV_WIDTH, FV_HEIGHT, FV_PITCH, 1, 0, 1);

	//BinaryExchange(image->pimg, FV_WIDTH, FV_HEIGHT, TOWB);
	//ImageExport(image, FINGER_VEIN);
	//BinaryExchange(image->pimg, FV_WIDTH, FV_HEIGHT, TOOZ);

	return FunOK;
#endif


#ifdef FV_ALL_TEST
	//get_fixed_roi(image->pimg, FV_WIDTH, FV_HEIGHT, FV_PITCH, image_org->pimg, 0, 35, FV_WIDTH_ORG, FV_HEIGHT_ORG, FV_PITCH_ORG);
	//ImageCopy32(&fv_src_copy, image);

	MeanSmoothV1(image->pimg, image_org->pimg, FV_WIDTH, FV_HEIGHT, FV_PITCH, smooth_w, 1);

	ImageCopy32(&fv_src_copy, image);
	CurvatureSegment(image->pimg, fv_src_copy.pimg, cur_t, cur_w, 0, FV_WIDTH, FV_HEIGHT, FV_PITCH);

	ImageCopy32(&fv_src_copy, image);
	MeanSmoothV1(image->pimg, fv_src_copy.pimg, FV_WIDTH, FV_HEIGHT, FV_PITCH, 7, 1);

	ImageCopy32(&fv_src_copy, image);
	OverallBinary(image->pimg, fv_src_copy.pimg, cur_w, cur_w, FV_WIDTH-2*cur_w-7, FV_HEIGHT-2*cur_w-7, 0, FV_WIDTH, FV_HEIGHT, FV_PITCH);

	change_edge_color(image->pimg, 10, 9, 105, 286, 0, FV_WIDTH, FV_HEIGHT, FV_PITCH);

	RegionMarkOZ(image->pimg, region_num, FV_WIDTH, FV_HEIGHT, FV_PITCH);
	RegionAreaFilter(image->pimg, region_num, fore_area_thr, back_area_thr, FV_WIDTH, FV_HEIGHT, FV_PITCH);

	ConditionThiningOZ(image->pimg, FV_WIDTH, FV_HEIGHT, FV_PITCH);

	return FunOK;
#endif

}


/******************************************************************************
  * 功能：对指纹图像进行处理
  * 参数：image			   指纹图像
  *		  imageGrads	   指纹图像的梯度图像
  *		  imageOri		   指纹图像的方向场图像
  *		  grads_ori_size   计算梯度和方向尺寸
  *		  seg_size		   粗分割尺寸
  *		  seg_step		   粗分割步长
  *		  seg_thr		   粗分割阈值
  *		  gauss_sigma	   高斯标准差
  *		  soft_size		   软化(平滑)尺寸
  *		  thin_thr		   细化毛刺阈值
  *		  minutia		   细节点集
  * 返回：错误编号
******************************************************************************/
FunError_t FPImageProcessing
(
 Image_t *image_org,
 Image_t *image,
 Image_t *imageGrads,
 Image_t *imageOri,
 const int32_t grads_ori_size,
 const int32_t seg_size,
 const int32_t seg_step,
 const int32_t seg_thr,
 const double gauss_sigma,
 const int32_t soft_size,
 const int32_t thin_thr,
 pFPMinutiaSet_t minutia
)
{
	//grads_ori_size = 13;
	//seg_size = 13;
	//seg_step = 2;
	//seg_thr = 80;
	//gauss_sigma = 0.4;
	//soft_size = 3;
	//thin_thr = 12;
	FunError_t err = FunOK;
	int32_t bina_dir = 1;	//0, 1, 2, 3
	int32_t forecolor = 0;
	int32_t backcolor = 1;
	int32_t bina_type = 1;
	//int32_t width = FP_WIDTH;
	//int32_t height = FP_HEIGHT;
	//int32_t pitch = FP_PITCH;
	//uint8_t pBuf[FP_WIDTH*FP_HEIGHT];
	//uint8_t pFPTemp[FP_HEIGHT*FP_WIDTH];


//#define FP_STEP_TEST
#define FP_ALL_TEST

#ifdef FP_STEP_TEST

	SizeNormalizeV2(image->pimg, FP_WIDTH, FP_HEIGHT, FP_PITCH,  image_org->pimg, FP_WIDTH_ORG, FP_HEIGHT_ORG, FP_PITCH_ORG);
	ImageExport(image, FINGER_PRINT);

	//ImageFlood(&fp_src_copy, 0);
	HalfWidthHeight(fp_src_copy.pimg, image->pimg, FP_WIDTH, FP_HEIGHT);
	//ImageExport(&fp_src_copy, FINGER_PRINT);
	GetGradsAndOrientationFast(imageGrads->pimg, imageOri->pimg, fp_src_copy.pimg, FP_WIDTH, FP_HEIGHT, FP_PITCH, grads_ori_size);

	//ImageExport(imageGrads, FINGER_PRINT);
	//ImageExport(imageOri, FINGER_PRINT);

	FPGradsRSegment(image->pimg, imageOri->pimg, imageGrads->pimg, seg_size, seg_step, seg_thr, FP_WIDTH, FP_HEIGHT, FP_PITCH);

	//ImageExport(imageGrads, FINGER_PRINT);

	//ImageExport(imageOri, FINGER_PRINT);	

	ImageExport(image, FINGER_TEST);

	Equalization(image->pimg, FP_WIDTH, FP_HEIGHT, FP_PITCH);

	ImageExport(image, FINGER_PRINT);

	ImageCopy32(&fp_src_copy, image);
	MeanSmooth(image->pimg, fp_src_copy.pimg, FP_WIDTH, FP_HEIGHT, FP_PITCH, soft_size, 1);

	OrientEnhance(image->pimg, imageOri->pimg, FP_WIDTH, FP_HEIGHT, FP_PITCH);
	OrientEnhance(image->pimg, imageOri->pimg, FP_WIDTH, FP_HEIGHT, FP_PITCH);
	ImageExport(image, FINGER_PRINT);

	OrientBinary(image->pimg, imageOri->pimg, imageGrads->pimg, FP_WIDTH, FP_HEIGHT, FP_PITCH, bina_dir);

	BinaryExchange(image->pimg, FP_WIDTH, FP_HEIGHT, TOWB);
	ImageExport(image, FINGER_PRINT);
	BinaryExchange(image->pimg, FP_WIDTH, FP_HEIGHT, TOOZ);

	ErasetableThining(image->pimg, FP_WIDTH, FP_HEIGHT, FP_PITCH, forecolor, backcolor, bina_type);

	BinaryExchange(image->pimg, FP_WIDTH, FP_HEIGHT, TOWB);
	ImageExport(image, FINGER_TEST);
	BinaryExchange(image->pimg, FP_WIDTH, FP_HEIGHT, TOOZ);

	SkeletonBurrClearV1(image->pimg, thin_thr, FP_WIDTH, FP_HEIGHT, FP_PITCH, forecolor, backcolor, bina_type); 

	BinaryExchange(image->pimg, FP_WIDTH, FP_HEIGHT, TOWB);
	ImageExport(image, FINGER_PRINT);
	BinaryExchange(image->pimg, FP_WIDTH, FP_HEIGHT, TOOZ);

	FPMinutiaSetExtract(minutia, image->pimg, imageOri->pimg, forecolor, backcolor, bina_type, FP_WIDTH, FP_HEIGHT, FP_PITCH);

	//BinaryExchange(image->pimg, FP_WIDTH, FP_HEIGHT, TOWB);
	//ImageExport(image, FINGER_PRINT);
	//BinaryExchange(image->pimg, FP_WIDTH, FP_HEIGHT, TOOZ);

	FPMinutiaSetDilateOZ(image->pimg, minutia, FP_WIDTH, FP_HEIGHT, FP_PITCH);
	////
	BinaryExchange(image->pimg, FP_WIDTH, FP_HEIGHT, TOWB);
	ImageExport(image, FINGER_PRINT);

	return FunOK;
#endif

#ifdef FP_ALL_TEST
	SizeNormalizeV2(image->pimg, FP_WIDTH, FP_HEIGHT, FP_PITCH,  image_org->pimg, FP_WIDTH_ORG, FP_HEIGHT_ORG, FP_PITCH_ORG);

	HalfWidthHeight(fp_src_copy.pimg, image->pimg, FP_WIDTH, FP_HEIGHT);
	GetGradsAndOrientationFast(imageGrads->pimg, imageOri->pimg, fp_src_copy.pimg, FP_WIDTH, FP_HEIGHT, FP_PITCH, grads_ori_size);

	FPGradsRSegment(image->pimg, imageOri->pimg, imageGrads->pimg, seg_size, seg_step, seg_thr, FP_WIDTH, FP_HEIGHT, FP_PITCH);

	Equalization(image->pimg, FP_WIDTH, FP_HEIGHT, FP_PITCH);

	ImageCopy32(&fp_src_copy, image);
	MeanSmooth(image->pimg, fp_src_copy.pimg, FP_WIDTH, FP_HEIGHT, FP_PITCH, soft_size, 1);

	OrientEnhance(image->pimg, imageOri->pimg, FP_WIDTH, FP_HEIGHT, FP_PITCH);
	OrientEnhance(image->pimg, imageOri->pimg, FP_WIDTH, FP_HEIGHT, FP_PITCH);

	OrientBinary(image->pimg, imageOri->pimg, imageGrads->pimg, FP_WIDTH, FP_HEIGHT, FP_PITCH, bina_dir);

	ErasetableThining(image->pimg, FP_WIDTH, FP_HEIGHT, FP_PITCH, forecolor, backcolor, bina_type);

	SkeletonBurrClearV1(image->pimg, thin_thr, FP_WIDTH, FP_HEIGHT, FP_PITCH, forecolor, backcolor, bina_type); 

	err = FPMinutiaSetExtract(minutia, image->pimg, imageOri->pimg, forecolor, backcolor, bina_type, FP_WIDTH, FP_HEIGHT, FP_PITCH);

	if (err == FunError) {
		return err;
	}

	//FPMinutiaSetDilateOZ(image->pimg, minutia, FP_WIDTH, FP_HEIGHT, FP_PITCH);

	return FunOK;
#endif	
	
	
}



//静脉图像处理任务TSK_touch
//void FingerVeinDIPTask(void)
//{
//	//
//	while(1) {
//		//STS_set(&sts, CLK_gethtime());
//		SEM_pend(&SEM_CAMERA_FV,  SYS_FOREVER);
//		//camera_capture(FINGER_VEIN);
//		//ImageImport(&fv_src_org, FINGER_VEIN);
//
//		//SEM_post(&SEM_CAMERA);
//
//		FVImageProcessing(&fv_src_org, &fv_src, &fv_imageG, 7, 2, 8, 200, 70, tmplt_w, tmplt9, tmplt_s, &fv_minutia, 20);
//
//		//TSK_sleep(1);
//		//STS_delta(&sts, CLK_gethtime());
//		asm ( " NOP " ) ;
//	}
//
//}

//指纹图像处理任务TSK_touch
void DIPTask(void)
{
	//
	//while(1) {
	//	//STS_set(&sts, CLK_gethtime());
	//	SEM_pend(&SEM_CAMERA,  SYS_FOREVER);
	//	//camera_capture(FINGER_PRINT);
	//	//ImageImport(&fp_src_org, FINGER_PRINT);

	//	//SEM_post(&SEM_CAMERA);
	//	//FVImageProcessing(&fv_src_org, &fv_src, &fv_imageG, 7, 2, 6, 200, 70, /*tmplt_w, tmplt9, tmplt_s,*/ &fv_minutia, 40);

	//	//FPImageProcessing(&fp_src_org, &fp_src, &fp_imageG, &fp_imageO,
	//	//	13, 13, 2, 50, 0.4, 3, 12, &fp_minutia);
	//	
	//	//TSK_sleep(1);
	//	//STS_delta(&sts, CLK_gethtime());
	//	asm ( " NOP " ) ;
	//}

}

void ImageCaptureTask(void) 
{
	//while(1) { 
	//	SEM_pend(&SEM_CAPTURE, SYS_FOREVER);
	//	camera_capture(FINGER_VEIN);
	//	ImageImport(&fv_src_org, FINGER_VEIN);
	//	asm ( " NOP " ) ;
	//	camera_capture(FINGER_PRINT);
	//	ImageImport(&fp_src_org, FINGER_PRINT);
	//	//SEM_post(&SEM_CAMERA);
	//	//SEM_post(&SEM_CAMERA_FP);
	//	FVImageProcessing(&fv_src_org, &fv_src, &fv_imageG, 7, 2, 6, 200, 70, /*tmplt_w, tmplt9, tmplt_s,*/ &fv_minutia, 40);
	//	asm ( " NOP " ) ;
	//	FPImageProcessing(&fp_src_org, &fp_src, &fp_imageG, &fp_imageO,
	//		13, 13, 2, 50, 0.4, 3, 12, &fp_minutia);
	//	asm ( " NOP " ) ;
	//}
}


bool_t check_finger_ok
(	
 uint8_t *pSrc, 
 const int32_t src_width,
 const int32_t src_height,
 const int32_t src_pitch
)
{

    int i,j;
    int tmp;
	uint8_t *pS = pSrc;
    tmp=0;
    for (i = 30; i < 425; i++) {
       for (j = 85; j < 550; j++) {
           if (*(pS + i*src_pitch +j) > 10) {
              tmp++;
           }
        }//end for (j=128...
    }//end for (i=200...        
    
	return (tmp > 145000) ? _false : _true;
}

void pixel_decompression_ex
(
 uint8_t *pDst,
 uint8_t *pSrc, 
 const int32_t dst_width,
 const int32_t dst_height,
 const int32_t dst_pitch
)
{

	int i, j;
	unsigned char tmp;
	int t_cols;
	t_cols = dst_width>>3;
	for (i = 0; i< dst_height; i++){
		for(j = 0;j < dst_width; j += 8){
			//tmp=psrc[i][j>>3];
			tmp = *(pSrc + i*t_cols + (j>>3));
			pDst[i*dst_pitch + j    ] = (tmp>>7)&0x01;
			pDst[i*dst_pitch + j + 1] = (tmp>>6)&0x01;
			pDst[i*dst_pitch + j + 2] = (tmp>>5)&0x01;
			pDst[i*dst_pitch + j + 3] = (tmp>>4)&0x01;
			pDst[i*dst_pitch + j + 4] = (tmp>>3)&0x01;
			pDst[i*dst_pitch + j + 5] = (tmp>>2)&0x01;
			pDst[i*dst_pitch + j + 6] = (tmp>>1)&0x01;
			pDst[i*dst_pitch + j + 7] = (tmp   )&0x01;
		}
	}
}

//压缩操作
void pixel_compression_ex
(
 uint8_t *pDst,
 uint8_t *pSrc, 
 const int32_t src_width,
 const int32_t src_height,
 const int32_t src_pitch
)
{
	int i, j, temp;
	int t_cols = src_width>>3;

	for (i = 0; i < src_height; i++) {
		for ( j = 0; j < t_cols; j++){
			temp = j*8;
			pDst[i*t_cols+j] =  (pSrc[i*src_pitch+temp]<<7) | 
								(pSrc[i*src_pitch+temp+1]<<6) |
								(pSrc[i*src_pitch+temp+2]<<5) |
								(pSrc[i*src_pitch+temp+3]<<4) |
								(pSrc[i*src_pitch+temp+4]<<3) |
								(pSrc[i*src_pitch+temp+5]<<2) |
								(pSrc[i*src_pitch+temp+6]<<1) |
								(pSrc[i*src_pitch+temp+7]);
		}
	}
}


void get_fixed_roi
(
 uint8_t *pDst,
 const int32_t dst_width,
 const int32_t dst_height,
 const int32_t dst_pitch,
 uint8_t *pSrc,
 const int32_t upleft_x,
 const int32_t upleft_y,
 const int32_t src_width,
 const int32_t src_height,
 const int32_t src_pitch
 )
{
	int32_t x, y;
	int32_t tempD, tempS;
	uint8_t *pS = pSrc;
	uint8_t *pD = pDst;
	for (y = 0; y < dst_height; y++) {
		tempD = y*dst_pitch;
		tempS = (upleft_y+y)*src_pitch;
		for (x = 0; x < dst_width; x++) {
			*(pD + tempD + x) = *(pS + tempS + (upleft_x+x));

		}
	}
}

void change_edge_color
(
 //uint8_t *pDst,
 uint8_t *pSrc, 
 const int32_t up_x,
 const int32_t up_y,
 const int32_t dn_x, 
 const int32_t dn_y,
 const int32_t color,
 const int32_t src_width,
 const int32_t src_height,
 const int32_t src_pitch
 )
{
	int32_t x, y;
	for (y = 0; y <= up_y; y++) {
		for (x = 0; x < src_width; x++) {
			pSrc[y*src_pitch+x] = color;
		}
	}
	for (y = dn_y; y < src_height; y++) {
		for (x = 0; x < src_width; x++) {
			pSrc[y*src_pitch+x] = color;
		}
	}

	for (x = 0; x <= up_x; x++) {
		for (y = up_y; y < dn_y; y++) {
			pSrc[y*src_pitch+x] = color;
		}
	}

	for (x = dn_x; x < src_width; x++) {
		for (y = up_y; y < dn_y; y++) {
			pSrc[y*src_pitch+x] = color;
		}
	}

}

/*将一幅图像添加到另外一幅图像上*/
void pixel_add
(
 uint8_t *pDst,
 uint8_t *pSrc,
 const int32_t src_width,
 const int32_t src_height,
 const int32_t src_pitch
)
{
	int i;
	int size;
	uint8_t *pS, *pD;
	pS = pSrc;
	pD = pDst;
	size = src_height * src_width;
	//for(i=0;i<rows;i++){
	//	for(j=0;j<cols;j++){
	//		pdst[i][j]=psrc[i][j] | pdst[i][j];
	//	}
	//}
	
	for (i = 0; i < size; i++) {
		*pD |=  *pS;
		pD++;
		pS++;
	}
}



