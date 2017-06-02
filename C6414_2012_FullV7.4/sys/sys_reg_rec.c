/******************************************************************************
 * 文件名：sys_global.c
 * 功能：  一些系统的全局变量和操作
******************************************************************************/


#include "sys_header/sys_reg_rec.h"

extern user_t gobal_user;
extern InputData gInputData;

static bool_t config_user(user_t*user)
{
   int i;
   int32_t tmpltD[25] = {
	   0, 0, 1, 0, 0,
	   0, 1, 1, 1, 0,
	   1, 1, 1, 1, 1,
	   0, 1, 1, 1, 0,
	   0, 0, 1, 0, 0,
   };
   int32_t tmplt_w = 5;
   int32_t tmplt_s = 13;
   //if(mbx.size==0){
   //   //gui_tips(handle,"请输入名称");//调用gui提示函数
   //   return _false;
   //}
   
   ///
   //将图像压缩到用户缓存
   //image_set_zero(&tmp1_image);//将图像清零
   
   //pixel_dilate(dst_image.pxy ,tmp1_image.pxy,128,192);
   //pixel_dilate(tmp1_image.pxy,dst_image.pxy ,128,192);
   ImageFlood(&fv_src_copy, 0);
   //BinaryExchange(fv_dst.pimg, FV_WIDTH, FV_HEIGHT, TOWB);
   //ImageExport(&fv_dst, FINGER_VEIN);
   //BinaryExchange(fv_dst.pimg, FV_WIDTH, FV_HEIGHT, TOOZ);
   UniDilateOZ(fv_src_copy.pimg, fv_dst.pimg, tmplt_w, tmpltD, tmplt_s, FV_WIDTH, FV_HEIGHT, FV_PITCH);
   UniDilateOZ(fv_dst.pimg, fv_src_copy.pimg, tmplt_w, tmpltD, tmplt_s, FV_WIDTH, FV_HEIGHT, FV_PITCH);
   pixel_compression_ex(user->imgbuf, fv_dst.pimg, FV_WIDTH, FV_HEIGHT, FV_PITCH);
   //BinaryExchange(fv_dst.pimg, FV_WIDTH, FV_HEIGHT, TOWB);
   //ImageExport(&fv_dst, FINGER_VEIN);
   //ImageFlood(&fv_src_copy, 0);
   pixel_decompression_ex(fv_src_copy.pimg, user->imgbuf, FV_WIDTH, FV_HEIGHT, FV_PITCH);
   BinaryExchange(fv_src_copy.pimg, FV_WIDTH, FV_HEIGHT, TOWB);
   ImageExport(&fv_src_copy, FINGER_TEST);
   
   user->fp_minutia.nbminutia = fp_minutia.nbminutia;
   //user->fv_minutia.nbminutia = fv_minutia.nbminutia;
   for (i = 0; i < fp_minutia.nbminutia; i++) {
		user->fp_minutia.FPMinutiaArr[i].x = fp_minutia.FPMinutiaArr[i].x;
		user->fp_minutia.FPMinutiaArr[i].y = fp_minutia.FPMinutiaArr[i].y;
		user->fp_minutia.FPMinutiaArr[i].angle = fp_minutia.FPMinutiaArr[i].angle;
		user->fp_minutia.FPMinutiaArr[i].type = fp_minutia.FPMinutiaArr[i].type;
		user->fp_minutia.FPMinutiaArr[i].triangle[0] = fp_minutia.FPMinutiaArr[i].triangle[0];
		user->fp_minutia.FPMinutiaArr[i].triangle[1] = fp_minutia.FPMinutiaArr[i].triangle[1];
		user->fp_minutia.FPMinutiaArr[i].triangle[2] = fp_minutia.FPMinutiaArr[i].triangle[2];
   }
  // for (i = 0; i < fv_minutia.nbminutia; i++) {
		//user->fv_minutia.FVMinutiaArr[i].type = fv_minutia.FVMinutiaArr[i].type;
		//user->fv_minutia.FVMinutiaArr[i].x = fv_minutia.FVMinutiaArr[i].x;
		//user->fv_minutia.FVMinutiaArr[i].y = fv_minutia.FVMinutiaArr[i].y;
  // }

   //默认是普通用户
   user->attribute=macro_db_normal_user;
   
   user->limits=macro_db_limits_all;
   
   for(i=0;i<15;i++){
	user->name[i]=gInputData.data[i];
	  // user->name[i] = i + 0x30;
   }
   user->name[15]='\0';
   
   user->next=(user_t*)0;
   user->pre=(user_t*)0;
   
   user->sexuality=macro_db_men;
   
   //get_local_time((sys_time*)&user->reg_time);
   
   return _true;
}

static font_t oldfont;
static font_t newfont;
static rect_t rect_reg_rec;
void do_register(void)
{
	gui_get_font(&oldfont);
	newfont.type=macro_font_style_huge;
	gui_set_font(&newfont);
	rect_reg_rec.x0 = 0;
	rect_reg_rec.y0 = 0;
	rect_reg_rec.x1 = 319;
	rect_reg_rec.y1 = 239;
      if(_true==config_user(&gobal_user)) {
	//if (1==0) {
        sys_user_register(&gobal_user);       
		BUZZER_TIP;
		oLCD_Fill_Rect_Buf(rect_reg_rec.y0,rect_reg_rec.x0, 240, 320, WHITE);
		gui_text_out_rect("注册成功", &rect_reg_rec, macro_text_h_align_center|macro_text_v_align_center);
		oLCD_Update_Rect_Screen(rect_reg_rec.y0,rect_reg_rec.x0, 240, 320);
		_delay_ms(2000);
	  } else {
		  BUZZER_TIP;
		  oLCD_Fill_Rect_Buf(rect_reg_rec.y0,rect_reg_rec.x0, 240, 320, WHITE);
		  gui_text_out_rect("注册失败",&rect_reg_rec, macro_text_h_align_center|macro_text_v_align_center);
		  oLCD_Update_Rect_Screen(rect_reg_rec.y0,rect_reg_rec.x0, 240, 320);
		  _delay_ms(1000);
		  oLCD_Fill_Rect_Buf(rect_reg_rec.y0,rect_reg_rec.x0, 240, 320, WHITE);
		  oLCD_Update_Rect_Screen(rect_reg_rec.y0,rect_reg_rec.x0, 240, 320);
		  _delay_ms(1000);
		  BUZZER_TIP;
		  gui_text_out_rect("注册失败",&rect_reg_rec, macro_text_h_align_center|macro_text_v_align_center);
		  oLCD_Update_Rect_Screen(rect_reg_rec.y0,rect_reg_rec.x0, 240, 320);
		  _delay_ms(1000);
		  oLCD_Fill_Rect_Buf(rect_reg_rec.y0,rect_reg_rec.x0, 240, 320, BLACK);
	  }  
		gui_set_font(&oldfont);


}

static user_t*user;
static iMatchingSet_t match_result;
//static FPMinutiaSet_t fp_minutiaT;
//static FVMinutiaSet_t fv_minutiaT;
#define MAX_FAIL_NUM		30
void RegisterTask(void)
{
	uint8_t ok = _true;
	uint8_t i = 0;
	uint8_t failed_num = 0;
	rect_t rect1;
	rect_t rect2;
	//uint8_t step = 0;
	rect1.x0 = 230;
	rect1.y0 = 51;
	rect1.x1 = 310;
	rect1.y1 = 71;
	rect2.x0 = 230;
	rect2.y0 = 71;
	rect2.x1 = 310;
	rect2.y1 = 91;

	while (1) {
		SEM_pend(&SEM_REGISTER,  SYS_FOREVER);

		while (failed_num < MAX_FAIL_NUM) {
			camera_capture(FINGER_PRINT);
			ImageImport(&fp_src_org, FINGER_PRINT);
			camera_capture(FINGER_VEIN);
			ImageImport(&fv_src_org, FINGER_VEIN);
			ok = check_finger_ok(fp_src_org.pimg, FP_WIDTH_ORG, FP_HEIGHT_ORG, FV_PITCH_ORG);
			if (ok == _true) {
				BUZZER_TIP;
				oLCD_Fill_Rect_Buf(rect1.y0,rect1.x0,rect1.y1-rect1.y0+1, rect1.x1-rect1.x0+1, BLACK);
				gui_text_out_rect("采集中...", &rect1, macro_text_h_align_center|macro_text_v_align_center);
				oLCD_Update_Rect_Screen(rect1.y0,rect1.x0,rect1.y1-rect1.y0+1, rect1.x1-rect1.x0+1);

				camera_capture(FINGER_PRINT);
				ImageImport(&fp_src_org, FINGER_PRINT);
				ImageFlood(&fv_dst, 0);
				for (i = 0; i < 3; i++) {
					camera_capture(FINGER_VEIN);
					ImageImport(&fv_src_org, FINGER_VEIN);
					asm ( " NOP " ) ;
					FVImageProcessing(&fv_src_org, &fv_src, &fv_imageG, 7, 2, 6, 200, 80, &fv_minutia, 20);
					pixel_add(fv_dst.pimg, fv_src.pimg, FV_WIDTH, FV_HEIGHT, FV_PITCH);
					asm ( " NOP " ) ;
				}

				BUZZER_TIP;

				oLCD_Fill_Rect_Buf(rect1.y0,rect1.x0,rect1.y1-rect1.y0+1, rect1.x1-rect1.x0+1, BLACK);
				gui_text_out_rect("注册中...", &rect1, macro_text_h_align_center|macro_text_v_align_center);
				oLCD_Update_Rect_Screen(rect1.y0,rect1.x0,rect1.y1-rect1.y0+1, rect1.x1-rect1.x0+1);

				FPImageProcessing(&fp_src_org, &fp_src, &fp_imageG, &fp_imageO, 13, 13, 2, 30, 0.4, 3, 12, &fp_minutia);

				gWindowType = T9_WIN;
				//oLCD_Fill_Full_Buf(WHITE);
				//key_on = 0;
				//IRQ_clear(IRQ_EVT_EXTINT4);//清除中断标志
				//IRQ_enable(IRQ_EVT_EXTINT4);//使能中断
				SEM_post(&SEM_T9);

				do_register();
				asm ( " NOP " ) ;
				//BUZZER_TIP;
				//oLCD_Fill_Rect_Buf(rect1.y0,rect1.x0,rect1.y1-rect1.y0+1, rect1.x1-rect1.x0+1, BLACK);
				//gui_text_out_rect("注册成功", &rect1, macro_text_h_align_center|macro_text_v_align_center);
				//oLCD_Update_Rect_Screen(rect1.y0,rect1.x0,rect1.y1-rect1.y0+1, rect1.x1-rect1.x0+1);
				//_delay_ms(2000);
				break;
			} else {
				failed_num++;
				oLCD_Fill_Rect_Buf(rect1.y0,rect1.x0,rect1.y1-rect1.y0+1, rect1.x1-rect1.x0+1, BLACK);
				gui_text_out_rect("请调整", &rect1,macro_text_h_align_center|macro_text_v_align_center);

				SizeNormalizeV1(image_display.pimg, DIS_FV_W, DIS_FV_H, DIS_FV_W, fv_src_org.pimg, FV_WIDTH_ORG, FV_HEIGHT_ORG, FV_PITCH_ORG, InterLinear, ImageGray);
				load_bitmap_8bpp(DIS_FV_Y, DIS_FV_X, DIS_FV_H, DIS_FV_W, (uint16_t*)(image_display.pimg));

				SizeNormalizeV1(image_display.pimg, DIS_FP_W, DIS_FP_H, DIS_FP_W, fp_src_org.pimg, FP_WIDTH_ORG, FP_HEIGHT_ORG, FP_PITCH_ORG, InterLinear, ImageGray);
				load_bitmap_8bpp(DIS_FP_Y, DIS_FP_X, DIS_FP_H, DIS_FP_W, (uint16_t*)(image_display.pimg));
			}
			oLCD_Update_Rect_Screen(0, 0, 240, 320);
		}

		if (ok == _true) {
			//SEM_post(&SEM_INPUT);
			//ImageCopy32
		} else {
			oLCD_Fill_Rect_Buf(rect1.y0,rect1.x0,rect1.y1-rect1.y0+1, rect1.x1-rect1.x0+1, BLACK);
			gui_text_out_rect("注册失败", &rect1, macro_text_h_align_center|macro_text_v_align_center);
			gui_text_out_rect("请重来", &rect2, macro_text_h_align_center|macro_text_v_align_center);


		}
		_delay_ms(200);
		oLCD_Fill_Rect_Buf(rect1.y0,rect1.x0,rect1.y1-rect1.y0+1, rect1.x1-rect1.x0+1, BLACK);
		gWindowType = MANAGER_WIN;
		asm ( " NOP " ) ;
		asm ( " NOP " ) ;


	}
}


void RecognitionTask(void)
{
	//uint8_t ok = _true;
	uint8_t match_ok = _false;
	int percent = 0;
	rect_t rectd;

	rectd.x0=120;
	rectd.y0=70;
	rectd.x1=200;
	rectd.y1=90;

	while (1) {
		SEM_pend(&SEM_RECOGNITION,  SYS_FOREVER);


		asm ( " NOP " ) ;
		camera_capture(FINGER_VEIN);
		ImageImport(&fv_src_org, FINGER_VEIN);

		//if (ok == _true) {
		//camera_capture(FINGER_VEIN);
		//ImageImport(&fv_src_org, FINGER_VEIN);			
		camera_capture(FINGER_PRINT);
		ImageImport(&fp_src_org, FINGER_PRINT);
		//ShowTime();
		//oLCD_Update_Rect_Screen(0, 0, 240, 320);
		asm ( " NOP " ) ;
		oLCD_Update_Rect_Screen(0, 0, 240, 320);
		BUZZER_TIP;	
		gui_text_out_rect("识别中...",&rectd,macro_text_h_align_center|\
			macro_text_v_align_center);
		oLCD_Update_Rect_Screen(rectd.y0,rectd.x0,rectd.y1-rectd.y0+1, rectd.x1-rectd.x0+1);


		FVImageProcessing(&fv_src_org, &fv_src, &fv_imageG, 7, 2, 6, 200, 80, &fv_minutia, 15);
		//ShowTime();

		asm ( " NOP " ) ;
		//FPImageProcessing(&fp_src_org, &fp_src, &fp_imageG, &fp_imageO, 13, 13, 2, 50, 0.4, 3, 12, &fp_minutia);
		//BUZZER_TIP;	
		//gui_text_out_rect("识别中...",&rectd,macro_text_h_align_center|\
		//	macro_text_v_align_center);
		//oLCD_Update_Rect_Screen(rectd.y0,rectd.x0,rectd.y1-rectd.y0+1, rectd.x1-rectd.x0+1);
		//ShowTime();
		//oLCD_Update_Rect_Screen(0, 0, 240, 320);
		//asm ( " NOP " ) ;
		user=sys_database_get_head();
		sys_database_go_to_head();
		while(user!=(user_t*)0)
		{
			//ImageFlood(&fv_src_copy, 0);
			//ImageExport(&fv_src_copy, FINGER_TEST);
			pixel_decompression_ex(fv_src_copy.pimg, user->imgbuf, FV_WIDTH, FV_HEIGHT, FV_PITCH);
			//BinaryExchange(fv_src_copy.pimg, FV_WIDTH, FV_HEIGHT, TOWB);
			//ImageExport(&fv_src_copy, FINGER_TEST);
			//BinaryExchange(fv_src.pimg, FV_WIDTH, FV_HEIGHT, TOWB);
			//ImageExport(&fv_src, FINGER_VEIN);
			//BinaryExchange(fv_src.pimg, FV_WIDTH, FV_HEIGHT, TOOZ);
			//BinaryExchange(fv_src_copy.pimg, FV_WIDTH, FV_HEIGHT, TOOZ);

			//FPMinutiaSetMatching(&fp_minutia, &(user->fp_minutia), &match_result, BOUND_BOX, SIMI_THR, ANGLE_THR, CENTRAL_THR, 1);
			ImageTemplateMatchingV1(fv_src.pimg, fv_src_copy.pimg, &percent, 20, 5, 30, 5, 2, FV_WIDTH, FV_HEIGHT, FV_PITCH);

			if (percent > MATCH_PERCENT) {
				FPImageProcessing(&fp_src_org, &fp_src, &fp_imageG, &fp_imageO, 13, 13, 2, 30, 0.4, 3, 12, &fp_minutia);
				FPMinutiaSetMatching(&fp_minutia, &(user->fp_minutia), &match_result, BOUND_BOX, /*SIMI_THR*/70, ANGLE_THR, CENTRAL_THR, 1);
				if (match_result.similarity > MATCH_SIMILARITY) {
					match_ok = _true;
					break;
				} else {
					match_ok = _false;
					user=sys_database_get_next();
				}
			} else{
				match_ok = _false;
				user=sys_database_get_next();
			}  
		}

		if (match_ok == _true) {
			BUZZER_TIP;
			oLCD_Fill_Rect_Buf(rectd.y0,rectd.x0,rectd.y1-rectd.y0+1, rectd.x1-rectd.x0+1, BLACK);
			gui_text_out_rect(user->name,&rectd,macro_text_h_align_center|\
				macro_text_v_align_center);
			oLCD_Update_Rect_Screen(rectd.y0,rectd.x0,rectd.y1-rectd.y0+1, rectd.x1-rectd.x0+1);
			_delay_ms(2000);
			oLCD_Fill_Rect_Buf(rectd.y0,rectd.x0,rectd.y1-rectd.y0+1, rectd.x1-rectd.x0+1, BLACK);
		} else {
			BUZZER_TIP;
			oLCD_Fill_Rect_Buf(rectd.y0,rectd.x0,rectd.y1-rectd.y0+1, rectd.x1-rectd.x0+1, BLACK);
			gui_text_out_rect("请重试!",&rectd,macro_text_h_align_center|\
				macro_text_v_align_center);
			oLCD_Update_Rect_Screen(rectd.y0,rectd.x0,rectd.y1-rectd.y0+1, rectd.x1-rectd.x0+1);
			_delay_ms(500);
			oLCD_Fill_Rect_Buf(rectd.y0,rectd.x0,rectd.y1-rectd.y0+1, rectd.x1-rectd.x0+1, BLACK);
			oLCD_Update_Rect_Screen(rectd.y0,rectd.x0,rectd.y1-rectd.y0+1, rectd.x1-rectd.x0+1);
			_delay_ms(500);
			BUZZER_TIP;
			gui_text_out_rect("请重试!",&rectd,macro_text_h_align_center|\
				macro_text_v_align_center);
			oLCD_Update_Rect_Screen(rectd.y0,rectd.x0,rectd.y1-rectd.y0+1, rectd.x1-rectd.x0+1);
			_delay_ms(500);
			oLCD_Fill_Rect_Buf(rectd.y0,rectd.x0,rectd.y1-rectd.y0+1, rectd.x1-rectd.x0+1, BLACK);
			//oLCD_Update_Rect_Screen(rectd.y0,rectd.x0,rectd.y1-rectd.y0+1, rectd.x1-rectd.x0+1);
			//_delay_ms(500);
		}

		oLCD_Update_Rect_Screen(rectd.y0,rectd.x0,rectd.y1-rectd.y0+1, rectd.x1-rectd.x0+1);

		//BUZZER_TIP;

		//}
		asm ( " NOP " ) ;
	}
}





