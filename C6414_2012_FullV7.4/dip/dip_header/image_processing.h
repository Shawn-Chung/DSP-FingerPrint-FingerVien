/******************************************************************************
 * 文件名：image_processing.h
 * 功  能：图像处理函数
******************************************************************************/

#if !defined __IMAGE_PROCESSING_H
#define __IMAGE_PROCESSING_H

//#include "image.h"
//#include "image_base.h"
//#include "image_binary.h"
//#include "image_segment.h"
//#include "image_enhance_filter.h"
//#include "image_morphology.h"
//#include "image_miscellaneous.h"
//#include "image_thining.h"
//#include "image_feature.h"
//#include "image_math.h"

#include "../../bsp/bsp_header/z_mytype.h"
#include "../../sys/sys_header/sys_global.h"
#include "image.h"
#include "image_feature.h"
#include "image_base.h"
#include "image_acquisition.h"

#ifdef __cplusplus
extern "C" {
#endif

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
);


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
);




bool_t check_finger_ok
(	
 uint8_t *pSrc, 
 const int32_t src_width,
 const int32_t src_height,
 const int32_t src_pitch
);


void pixel_decompression_ex
(
 uint8_t *pDst,
 uint8_t *pSrc, 
 const int32_t dst_width,
 const int32_t dst_height,
 const int32_t dst_pitch
);


//压缩操作
void pixel_compression_ex
(
 uint8_t *pDst,
 uint8_t *pSrc, 
 const int32_t src_width,
 const int32_t src_height,
 const int32_t src_pitch
);

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
 );

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
 );

void pixel_add
(
 uint8_t *pDst,
 uint8_t *pSrc,
 const int32_t src_width,
 const int32_t src_height,
 const int32_t src_pitch
 );


#ifdef __cplusplus
}
#endif	/* extern "C" */

#endif /* __IMAGE_PROCESSING_H */

