/******************************************************************************
 * 文件名：image_acquisition.c
 * 功能：  图像导入导出操作
******************************************************************************/

#include "dip_header/image_acquisition.h"

/******************************************************************************
  * 功能：从文件中加载图像
  * 参数：image       图像
  *       flag 标识采集的是什么图像
  *			FINGER_PRINT 指纹图像
  *			FINGER_VEIN  指静脉图像
  * 返回：错误编号
******************************************************************************/
void ImageImport(Image_t *image, uint32_t flag)
{
	volatile uint32_t *ptr;
	volatile uint32_t *ptrd;
	int32_t i, j;
	int32_t tempJ;
	if (flag == FINGER_VEIN) {
		ptr = ptrd = (uint32_t*)(IMAGE_IN_ADDR);
		for (i = 0; i <  FV_WH_ORG_SIZE32; i++) {			
			*ptrd++ = *ptr;
			ptr += 2;
		}

		ptr = ((uint32_t *)(IMAGE_IN_ADDR)) ;
		ptrd= ((uint32_t *)(IMAGE_FV_IN_ADDR)) ;
		//asm ( " NOP " ) ;

		for (j = FV_HEIGHT_ORG-1; j >= 0; j--) {
			tempJ = (j*FV_WIDTH_ORG)>>2;
			for (i = 0; i < (FV_WIDTH_ORG>>2); i++) {
				*(ptrd+tempJ+i) = *ptr++;
			}
		}
		//for (i = 0; i < FV_WH_ORG_SIZE32; i++) {
		//	*ptrd = *ptr;

		//}

	} else if (flag == FINGER_PRINT) {
		ptr = ptrd = (uint32_t*)(IMAGE_IN_ADDR);
		for (i = 0; i <  FP_WH_ORG_SIZE32; i++) {			
			*ptrd++ = *ptr;
			ptr += 2;
		}

		ptr = ((uint32_t *)(IMAGE_IN_ADDR)) ;
		ptrd= ((uint32_t *)(IMAGE_FP_IN_ADDR)) ;
		//asm ( " NOP " ) ;
		for (j = FP_HEIGHT_ORG-1; j >= 0; j--) {
			tempJ = (FP_WIDTH_ORG * j)>>2;
			for (i = 0; i < (FP_WIDTH_ORG>>2); i++) {
				*(ptrd+tempJ+i) = *ptr++;
			}
		}
		//for (i = 0; i < FP_WH_ORG_SIZE; i++) {
		//	*ptrd = *ptr ;

		//}

	}

}


/******************************************************************************
  * 功能：从文件中加载图像
  * 参数：image       图像
  *       flag 标识采集的是什么图像
  *			FINGER_PRINT 指纹图像
  *			FINGER_VEIN  指静脉图像
  * 返回：错误编号
******************************************************************************/
void ImageExport(Image_t *image, uint32_t flag)
{
	volatile uint32_t *ptr;
	volatile uint32_t *ptrd;
	int32_t i;
	
	if (flag == FINGER_VEIN) {
		ptr = ((uint32_t *)(image->pimg));
		ptrd= ((unsigned int*)(IMAGE_FV_OUT_ADDR)) ;
		for (i = 0; i < FV_WH_SIZE32; i++) {
			*ptrd = *ptr ;
			ptr++;
			ptrd++;
		}


	} else if (flag == FINGER_PRINT) {
		ptr = ((uint32_t *)(image->pimg));
		ptrd= ((unsigned int*)(IMAGE_FP_OUT_ADDR)) ;

		for (i = 0; i < FP_WH_SIZE32; i++) {
			*ptrd = *ptr ;
			ptr++;
			ptrd++;
		}
	} else if (flag == FINGER_TEST) {
		ptr = ((uint32_t *)(image->pimg));
		ptrd= ((unsigned int*)(IMAGE_TEST_ADDR)) ;

		for (i = 0; i < FP_WH_ORG_SIZE32; i++) {
			*ptrd = *ptr ;
			ptr++;
			ptrd++;
		}
	}
}



/******************************************************************************
  * 功能：从文件中加载图像
  * 参数：image       图像
  *       flag 标识采集的是什么图像
  *			FINGER_PRINT 指纹图像
  *			FINGER_VEIN  指静脉图像
  * 返回：错误编号
******************************************************************************/
//void FeatureExport(pFPMinutiaSet_t minutia1, pFVMinutiaSet_t minutia2, uint32_t id)
//{
//	volatile uint32_t *ptr;
//	volatile uint32_t *ptrd;
//	int32_t i;
//	
//
//	if (flag == FINGER_VEIN) {
//		ptr = ((uint32_t *)(minutia1));
//		ptrd= ((unsigned int*)(FEATURE_OUT_ADDR) + id * 4096) ;
//		*ptrd = id;
//		ptrd++;
//		*ptrd = minutia1->nbminutia;
//		*
//		for (i = 0; i < FV_WH_SIZE32; i++) {
//			*ptrd = *ptr ;
//			ptr++;
//			ptrd++;
//		}
//
//
//	} else if (flag == FINGER_PRINT) {
//		ptr = ((uint32_t *)(image->pimg));
//		ptrd= ((unsigned int*)(IMAGE_FP_OUT_ADDR)) ;
//
//		for (i = 0; i < FP_WH_SIZE32; i++) {
//			*ptrd = *ptr ;
//			ptr++;
//			ptrd++;
//		}
//	} 
//}

