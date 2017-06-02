/******************************************************************************
 * 文件名：sys_gobal.h
 * 功能：  一些系统的全局变量和操作
******************************************************************************/

#if !defined __SYS_GLOBAL_H
#define __SYS_GLOBAL_H


/* 基本类型定义 */
#include "../../bsp/bsp_header/z_mytype.h"
#include "../../dip/dip_header/dip_header.h"
#include "../../dip/dip_header/image_feature.h"

#include "sys_user.h"

#ifdef __cplusplus
extern "C" {
#endif

#define KEY01		0x01
#define KEY02		0x02
#define KEY03		0x03
//#define KEY04		0x04
#define KEY05		0x05
#define KEY06		0x06
#define KEY07		0x07
//#define KEY08		0x08
#define KEY09		0x09
#define KEY10		0x0A
#define KEY11		0x0B
//#define KEY12		0x0C
//#define KEY13		0x0D
//#define KEY14		0x0E
//#define KEY15		0x0F
//#define KEY16		0x10

#define KEY00		0x0E
#define KEYUP		0x0C
#define KEYOK		0x0F
#define KEY13		0x0D
#define KEYGB		0x08
#define KEYDN		0x10
#define KEYCC		0x04


//静脉的一些定义
#define FV_WIDTH_ORG		120
#define FV_HEIGHT_ORG		300
#define FV_PITCH_ORG		FV_WIDTH_ORG
#define FV_WH_ORG_SIZE		((FV_WIDTH_ORG)*(FV_HEIGHT_ORG))
#define FV_WH_ORG_SIZE32	(FV_WH_ORG_SIZE/4)

#define FV_WIDTH			120
#define	FV_HEIGHT			300
#define FV_PITCH			FV_WIDTH
#define FV_WH_SIZE			((FV_WIDTH)*(FV_HEIGHT))		
#define FV_WH_SIZE32		(FV_WH_SIZE/4)


#define FP_WIDTH_ORG		600
#define FP_HEIGHT_ORG		470
#define FP_PITCH_ORG		FP_WIDTH_ORG
#define FP_WH_ORG_SIZE		((FP_WIDTH_ORG)*(FP_HEIGHT_ORG))
#define FP_WH_ORG_SIZE32	(FP_WH_ORG_SIZE/4)

//#define FP_WIDTH			256
//#define FP_HEIGHT			200
#define FP_WIDTH			300
#define FP_HEIGHT			235
#define FP_PITCH			FP_WIDTH
#define FP_WH_SIZE			((FP_WIDTH)*(FP_HEIGHT))
#define FP_WH_SIZE32		(FP_WH_SIZE/4)


extern Image_t fv_src_org;
extern Image_t fv_src;
extern Image_t fv_src_copy;
extern Image_t fv_imageG;
extern Image_t fv_dst;

extern float cur_value[FV_HEIGHT*FV_WIDTH];

extern FVMinutiaSet_t fv_minutia;


extern Image_t fp_src_org;
extern Image_t fp_src;
extern Image_t fp_src1;
extern Image_t fp_src_copy;
extern Image_t fp_imageG;
extern Image_t fp_imageO;

extern FPMinutiaSet_t fp_minutia;

extern Image_t image_display;
//extern Image_t image_display_fp;
//extern Image_t image_display_fv;
//extern user_t    gobal_user;
//extern user_t gobal_user;

void image_init(void);


//系统全局变量初始化
void sys_global_init(void);



#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* __SYS_GLOBAL_H */


