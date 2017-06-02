/******************************************************************************
 * 文件名：image.h
 * 功能：  实现了指纹图像的基本操作
******************************************************************************/

#include "GUI_header/GUI_menu.h"

uint8_t gWindowType = MAIN_WIN;
uint8_t gMenuIndex = 0;
InputData gInputData;

void Gui_ipost(void)
{
	SEM_ipost(&SEM_INPUT);
}

void SelectMenu(uint8_t winType, uint8_t menuNum, uint8_t sel)
{
	//int32_t x, y;
	int32_t i;
	switch (winType) {
	case MAIN_WIN:
		asm ( " NOP " ) ;
		break;

	case MANAGER_WIN:
		if (menuNum == BUTTON_REGISTER) {
			for (i = 0; i < 5; i++) {
				gui_draw_rect(BTN_REG_X0+i-7, BTN_REG_Y0+i-7, BTN_REG_X1-i+1, BTN_REG_Y1-i+1, BROWN);

			}
		} else if (menuNum == BUTTON_MANAGER) {
			for (i = 0; i < 5; i++) {
				gui_draw_rect(BTN_MAN_X0+i-7, BTN_MAN_Y0+i-7, BTN_MAN_X1-i+1, BTN_MAN_Y1-i+1, BROWN);
			}
		}
		break;
	case PASSWORD_WIN : 
		if (menuNum == 0) {
			for (i = 0; i < 4; i++) {
				gui_draw_rect(85+i, 13+i, 235-i, 51-i, BLACK);

			}
		} else if (menuNum == 1) {
			for (i = 0; i < 4; i++) {
				gui_draw_rect(85+i, 60+i, 235-i, 100-i, BLACK);
			}
		}
		break;

	default :
		break;
	}
}


#define MENU_NUMS		2u
#define SUB_MENU_NUMS	5u
#define PASSWORD_MENU_NUMS	2u
void get_win_menu_num (char KeyValue, uint8_t *menu_index) 
{
	if (gWindowType == MAIN_WIN) {
		switch (KeyValue) {
		case KEYOK:
			//gWindowType = PASSWORD_WIN;
			SEM_post(&SEM_OK);
			break;
			
		default :
			break;	
		}
	} else if (gWindowType == MANAGER_WIN) {
		switch (KeyValue) {
		case KEYDN:
			(*menu_index)++;
			if ((*menu_index) >= MENU_NUMS) {
				(*menu_index) = 0;
			}
			break;
		case KEYUP:
			if ((*menu_index) == 0) {
				(*menu_index) = MENU_NUMS;
			}
			(*menu_index)--;
			break;

		case KEYOK:
			SEM_post(&SEM_OK);
			break;
		case KEYGB:
			gWindowType = MAIN_WIN;
			*menu_index = 0;
			break;
			
		default :
			break;	
		}
	} else if (gWindowType == PASSWORD_WIN) {
		switch (KeyValue) {
		case KEYDN:
			(*menu_index)++;
			if ((*menu_index) >= PASSWORD_MENU_NUMS) {
				(*menu_index) = 0;
			}
			break;
		case KEYUP:
			if ((*menu_index) == 0) {
				(*menu_index) = PASSWORD_MENU_NUMS;
			}
			(*menu_index)--;
			break;

		case KEYOK:
			SEM_post(&SEM_OK);
			break;
		case KEYGB:
			gWindowType = MAIN_WIN;
			*menu_index = 0;
			break;
			
		default :
			break;	
		}
	}
	//BUZZER_TIP;

}

char gKeyValue = 0;
void KeyTask(void)
{
	static font_t oldfont;
	static font_t newfont;

	//uint32_t active_id;
	rect_t pw_rect, pw_rect1;
	pw_rect.x0 = 0;
	pw_rect.y0 = 13;
	pw_rect.x1 = 319;
	pw_rect.y1 = 51;
	pw_rect1.x0 = 0;
	pw_rect1.y0 = 60;
	pw_rect1.x1 = 319;
	pw_rect1.y1 = 100;

	while(SEM_pend(&SEM_INPUT,  SYS_FOREVER)) {

		IRQ_disable(IRQ_EVT_EXTINT4);//禁止中断	

		ZLG7290_ReadReg(ZLG7290_Key,&gKeyValue);//读取键值

		get_win_menu_num(gKeyValue, &gMenuIndex);
		
		if (gWindowType == MAIN_WIN) {
			//if (gKeyValue == KEYGB ) {
			load_bitmap_16bpp(0, 0, 240, 320, (uint16_t *)gResFileTab[0]);
			//camera_capture(FINGER_VEIN);
			//ImageImport(&fv_src_org, FINGER_VEIN);
			//asm ( " NOP " ) ;
			//camera_capture(FINGER_PRINT);
			//ImageImport(&fp_src_org, FINGER_PRINT);

			//显示采集到的指纹图像和静脉图像
			//SizeNormalizeV1(image_display.pimg, DIS_FV_W, DIS_FV_H, DIS_FV_W, fv_src_org.pimg, FV_WIDTH_ORG, FV_HEIGHT_ORG, FV_PITCH_ORG, InterLinear, ImageGray);

			//load_bitmap_8bpp(DIS_FV_Y, DIS_FV_X, DIS_FV_H, DIS_FV_W, (uint16_t*)(image_display.pimg));

			//SizeNormalizeV1(image_display.pimg, DIS_FP_W, DIS_FP_Y, DIS_FP_W, fp_src_org.pimg, FP_WIDTH_ORG, FP_HEIGHT_ORG, FP_PITCH_ORG, InterLinear, ImageGray);

			//load_bitmap_8bpp(DIS_FP_Y, DIS_FP_X, DIS_FP_H, DIS_FP_W, (uint16_t*)(image_display.pimg));

			oLCD_Update_Rect_Screen(0, 0, 240, 320);		
			asm ( " NOP " ) ;
			//}
		} else if (gWindowType == MANAGER_WIN) {
			//if (gKeyValue == KEYOK) {
			load_bitmap_16bpp(0, 0, 240, 320, (uint16_t *)gResFileTab[1]);
			SelectMenu(MANAGER_WIN, gMenuIndex, 1);
			oLCD_Update_Rect_Screen(0, 0, 240, 320);
			asm ( " NOP " ) ;
			//}
		} else if (gWindowType == PASSWORD_WIN) {
			asm ( " NOP " ) ;
			asm ( " NOP " ) ;
			//oLCD_Clear(WHITE);
			oLCD_Fill_Full_Buf(WHITE);

			gui_get_font(&oldfont);
			newfont.type=macro_font_style_big;
			gui_set_font(&newfont);
			gui_text_out_rect("输入密码^_^", &pw_rect, macro_text_h_align_center|macro_text_v_align_center);
			gui_text_out_rect("修改密码^_^", &pw_rect1, macro_text_h_align_center|macro_text_v_align_center);
			SelectMenu(PASSWORD_WIN, gMenuIndex, 1);
			asm ( " NOP " ) ;
			oLCD_Update_Rect_Screen(0, 0, 240, 320);
			asm ( " NOP " ) ;
			gui_set_font(&oldfont);
			asm ( " NOP " ) ;
		}

		IRQ_clear(IRQ_EVT_EXTINT4);//清除中断标志
		IRQ_enable(IRQ_EVT_EXTINT4);//使能中断
	}

}


void SendMessageTask(void)
{
	while (1) {
		SEM_pend(&SEM_OK,  SYS_FOREVER);
		if (gWindowType == MAIN_WIN) {
			//gWindowType = MANAGER_WIN;
			gWindowType = PASSWORD_WIN;
			//SEM_post(&SEM_INPUT);
		} else if (gWindowType == PASSWORD_WIN) {
			if (gMenuIndex == 0) {
				gWindowType = PASSWORD_SUB_WIN0;
				//SEM_post(&SEM_REGISTER);
				SEM_post(&SEM_PASSWORD);
			} else if (gMenuIndex == 1) {
				//SEM_post(&SEM_MANAGER);
				gWindowType = PASSWORD_SUB_WIN1;
				//SEM_post(&SEM_SUB_MANAGER);
				SEM_post(&SEM_PASSWORD);
			}
		}
		else if (gWindowType == MANAGER_WIN) {
			if (gMenuIndex == BUTTON_REGISTER) {
				gWindowType = REGISTER_WIN;
				SEM_post(&SEM_REGISTER);
			} else if (gMenuIndex == BUTTON_MANAGER) {
				//SEM_post(&SEM_MANAGER);
				gWindowType = MANAGER_SUB_WIN;
				SEM_post(&SEM_SUB_MANAGER);
			}
		}
		asm ( " NOP " ) ;
		asm ( " NOP " ) ;

	}
}


//实时显示采集的图像
void ShowCaptureImageTask(void) 
{
	uint8_t finger_ready = _false;
	static font_t oldfont;
	static font_t newfont;

	//uint32_t active_id;
	rect_t pw_rect, pw_rect1;
	pw_rect.x0 = 0;
	pw_rect.y0 = 13;
	pw_rect.x1 = 319;
	pw_rect.y1 = 51;
	pw_rect1.x0 = 0;
	pw_rect1.y0 = 60;
	pw_rect1.x1 = 319;
	pw_rect1.y1 = 100;
	
	while (1) {
		if ((gWindowType ==  MAIN_WIN) ||  (gWindowType == MANAGER_WIN)) {
		camera_capture(FINGER_VEIN);
		ImageImport(&fv_src_org, FINGER_VEIN);
		asm ( " NOP " ) ;
		camera_capture(FINGER_PRINT);
		ImageImport(&fp_src_org, FINGER_PRINT);
		
		SizeNormalizeV1(image_display.pimg, DIS_FV_W, DIS_FV_H, DIS_FV_W, fv_src_org.pimg, FV_WIDTH_ORG, FV_HEIGHT_ORG, FV_PITCH_ORG, InterLinear, ImageGray);

		load_bitmap_8bpp(DIS_FV_Y, DIS_FV_X, DIS_FV_H, DIS_FV_W, (uint16_t*)(image_display.pimg));
		//ImageExport(&image_display, 3);
		SizeNormalizeV1(image_display.pimg, DIS_FP_W, DIS_FP_H, DIS_FP_W, fp_src_org.pimg, FP_WIDTH_ORG, FP_HEIGHT_ORG, FP_PITCH_ORG, InterLinear, ImageGray);

		load_bitmap_8bpp(DIS_FP_Y, DIS_FP_X, DIS_FP_H, DIS_FP_W, (uint16_t*)(image_display.pimg));

		if (gWindowType == MAIN_WIN) {
			ShowTime();
			finger_ready = check_finger_ok(fp_src_org.pimg, FP_WIDTH_ORG, FP_HEIGHT_ORG, FP_PITCH_ORG);
			if (finger_ready == _true) {
				//BUZZER_TIP;
				SEM_post(&SEM_RECOGNITION);
			}
			asm ( " NOP " ) ;
		} else if (gWindowType == MANAGER_WIN) {
			//load_bitmap_16bpp(0, 0, 240, 320, (uint16_t *)gResFileTab[1]);
			//SelectMenu(MANAGER_WIN, gMenuIndex, 1);
			//oLCD_Update_Rect_Screen(0, 0, 240, 320);
			asm ( " NOP " ) ;

		} else {
			oLCD_Fill_Full_Buf(WHITE);

			gui_get_font(&oldfont);
			newfont.type=macro_font_style_big;
			gui_set_font(&newfont);
			gui_text_out_rect("输入密码^_^", &pw_rect, macro_text_h_align_center|macro_text_v_align_center);
			gui_text_out_rect("修改密码^_^", &pw_rect1, macro_text_h_align_center|macro_text_v_align_center);
			SelectMenu(PASSWORD_WIN, gMenuIndex, 1);
			oLCD_Update_Rect_Screen(0, 0, 240, 320);
			gui_set_font(&oldfont);
		}
		oLCD_Update_Rect_Screen(0, 0, 240, 320);
		TSK_sleep(5);
		asm ( " NOP " ) ;
		asm ( " NOP " ) ;
		}
	}
}




//static user_t*user;
//static iMatchingSet_t match_result;
////static FPMinutiaSet_t fp_minutiaT;
////static FVMinutiaSet_t fv_minutiaT;
//#define MAX_FAIL_NUM		30
//void RegisterTask(void)
//{
//	uint8_t ok = _true;
//	uint8_t i = 0;
//	uint8_t failed_num = 0;
//	rect_t rect1;
//	rect_t rect2;
//	//uint8_t step = 0;
//	rect1.x0 = 230;
//	rect1.y0 = 51;
//	rect1.x1 = 310;
//	rect1.y1 = 71;
//	rect2.x0 = 230;
//	rect2.y0 = 71;
//	rect2.x1 = 310;
//	rect2.y1 = 91;
//
//	while (1) {
//		SEM_pend(&SEM_REGISTER,  SYS_FOREVER);
//
//		while (failed_num < MAX_FAIL_NUM) {
//			camera_capture(FINGER_PRINT);
//			ImageImport(&fp_src_org, FINGER_PRINT);
//			camera_capture(FINGER_VEIN);
//			ImageImport(&fv_src_org, FINGER_VEIN);
//			ok = check_finger_ok(fp_src_org.pimg, FP_WIDTH_ORG, FP_HEIGHT_ORG, FV_PITCH_ORG);
//			if (ok == _true) {
//				BUZZER_TIP;
//				oLCD_Fill_Rect_Buf(rect1.y0,rect1.x0,rect1.y1-rect1.y0+1, rect1.x1-rect1.x0+1, BLACK);
//				gui_text_out_rect("采集中...", &rect1, macro_text_h_align_center|macro_text_v_align_center);
//				oLCD_Update_Rect_Screen(rect1.y0,rect1.x0,rect1.y1-rect1.y0+1, rect1.x1-rect1.x0+1);
//
//				camera_capture(FINGER_PRINT);
//				ImageImport(&fp_src_org, FINGER_PRINT);
//				ImageFlood(&fv_dst, 0);
//				for (i = 0; i < 5; i++) {
//					camera_capture(FINGER_VEIN);
//					ImageImport(&fv_src_org, FINGER_VEIN);
//					asm ( " NOP " ) ;
//					FVImageProcessing(&fv_src_org, &fv_src, &fv_imageG, 7, 2, 6, 200, 80, &fv_minutia, 20);
//					pixel_add(fv_dst.pimg, fv_src.pimg, FV_WIDTH, FV_HEIGHT, FV_PITCH);
//					asm ( " NOP " ) ;
//				}
//				
//				BUZZER_TIP;
//
//				oLCD_Fill_Rect_Buf(rect1.y0,rect1.x0,rect1.y1-rect1.y0+1, rect1.x1-rect1.x0+1, BLACK);
//				gui_text_out_rect("注册中...", &rect1, macro_text_h_align_center|macro_text_v_align_center);
//				oLCD_Update_Rect_Screen(rect1.y0,rect1.x0,rect1.y1-rect1.y0+1, rect1.x1-rect1.x0+1);
//
//				FPImageProcessing(&fp_src_org, &fp_src, &fp_imageG, &fp_imageO, 13, 13, 2, 30, 0.4, 3, 12, &fp_minutia);
//
//				gWindowType = T9_WIN;
//				//oLCD_Fill_Full_Buf(WHITE);
//				//key_on = 0;
//				//IRQ_clear(IRQ_EVT_EXTINT4);//清除中断标志
//				//IRQ_enable(IRQ_EVT_EXTINT4);//使能中断
//				SEM_post(&SEM_T9);
//
//				do_register();
//				asm ( " NOP " ) ;
//				//BUZZER_TIP;
//				//oLCD_Fill_Rect_Buf(rect1.y0,rect1.x0,rect1.y1-rect1.y0+1, rect1.x1-rect1.x0+1, BLACK);
//				//gui_text_out_rect("注册成功", &rect1, macro_text_h_align_center|macro_text_v_align_center);
//				//oLCD_Update_Rect_Screen(rect1.y0,rect1.x0,rect1.y1-rect1.y0+1, rect1.x1-rect1.x0+1);
//				//_delay_ms(2000);
//				break;
//			} else {
//				failed_num++;
//				oLCD_Fill_Rect_Buf(rect1.y0,rect1.x0,rect1.y1-rect1.y0+1, rect1.x1-rect1.x0+1, BLACK);
//				gui_text_out_rect("请调整", &rect1,macro_text_h_align_center|macro_text_v_align_center);
//
//				SizeNormalizeV1(image_display.pimg, DIS_FV_W, DIS_FV_H, DIS_FV_W, fv_src_org.pimg, FV_WIDTH_ORG, FV_HEIGHT_ORG, FV_PITCH_ORG, InterLinear, ImageGray);
//				load_bitmap_8bpp(DIS_FV_Y, DIS_FV_X, DIS_FV_H, DIS_FV_W, (uint16_t*)(image_display.pimg));
//
//				SizeNormalizeV1(image_display.pimg, DIS_FP_W, DIS_FP_H, DIS_FP_W, fp_src_org.pimg, FP_WIDTH_ORG, FP_HEIGHT_ORG, FP_PITCH_ORG, InterLinear, ImageGray);
//				load_bitmap_8bpp(DIS_FP_Y, DIS_FP_X, DIS_FP_H, DIS_FP_W, (uint16_t*)(image_display.pimg));
//			}
//			oLCD_Update_Rect_Screen(0, 0, 240, 320);
//		}
//		
//		if (ok == _true) {
//			//SEM_post(&SEM_INPUT);
//			//ImageCopy32
//		} else {
//			oLCD_Fill_Rect_Buf(rect1.y0,rect1.x0,rect1.y1-rect1.y0+1, rect1.x1-rect1.x0+1, BLACK);
//			gui_text_out_rect("注册失败", &rect1, macro_text_h_align_center|macro_text_v_align_center);
//			gui_text_out_rect("请重来", &rect2, macro_text_h_align_center|macro_text_v_align_center);
//			
//			
//		}
//		_delay_ms(200);
//		oLCD_Fill_Rect_Buf(rect1.y0,rect1.x0,rect1.y1-rect1.y0+1, rect1.x1-rect1.x0+1, BLACK);
//		gWindowType = MANAGER_WIN;
//		asm ( " NOP " ) ;
//		asm ( " NOP " ) ;
//
//	
//	}
//}
//
//
//void RecognitionTask(void)
//{
//	//uint8_t ok = _true;
//	uint8_t match_ok = _false;
//	int percent = 0;
//	rect_t rectd;
//
//	rectd.x0=120;
//	rectd.y0=70;
//	rectd.x1=200;
//	rectd.y1=90;
//
//	while (1) {
//		SEM_pend(&SEM_RECOGNITION,  SYS_FOREVER);
//		
//
//		asm ( " NOP " ) ;
//		camera_capture(FINGER_VEIN);
//		ImageImport(&fv_src_org, FINGER_VEIN);
//		
//		//if (ok == _true) {
//			//camera_capture(FINGER_VEIN);
//			//ImageImport(&fv_src_org, FINGER_VEIN);			
//			camera_capture(FINGER_PRINT);
//			ImageImport(&fp_src_org, FINGER_PRINT);
//			//ShowTime();
//			//oLCD_Update_Rect_Screen(0, 0, 240, 320);
//			asm ( " NOP " ) ;
//			oLCD_Update_Rect_Screen(0, 0, 240, 320);
//			BUZZER_TIP;	
//			gui_text_out_rect("识别中...",&rectd,macro_text_h_align_center|\
//				macro_text_v_align_center);
//			oLCD_Update_Rect_Screen(rectd.y0,rectd.x0,rectd.y1-rectd.y0+1, rectd.x1-rectd.x0+1);
//			
//			
//			FVImageProcessing(&fv_src_org, &fv_src, &fv_imageG, 7, 2, 6, 200, 80, &fv_minutia, 20);
//			//ShowTime();
//			
//			asm ( " NOP " ) ;
//			//FPImageProcessing(&fp_src_org, &fp_src, &fp_imageG, &fp_imageO, 13, 13, 2, 50, 0.4, 3, 12, &fp_minutia);
//			//BUZZER_TIP;	
//			//gui_text_out_rect("识别中...",&rectd,macro_text_h_align_center|\
//			//	macro_text_v_align_center);
//			//oLCD_Update_Rect_Screen(rectd.y0,rectd.x0,rectd.y1-rectd.y0+1, rectd.x1-rectd.x0+1);
//			//ShowTime();
//			//oLCD_Update_Rect_Screen(0, 0, 240, 320);
//			//asm ( " NOP " ) ;
//			user=sys_database_get_head();
//		     sys_database_go_to_head();
//		     while(user!=(user_t*)0)
//		     {
//				 //ImageFlood(&fv_src_copy, 0);
//				 //ImageExport(&fv_src_copy, FINGER_TEST);
//				 pixel_decompression_ex(fv_src_copy.pimg, user->imgbuf, FV_WIDTH, FV_HEIGHT, FV_PITCH);
//				 //BinaryExchange(fv_src_copy.pimg, FV_WIDTH, FV_HEIGHT, TOWB);
//				 //ImageExport(&fv_src_copy, FINGER_TEST);
//				 //BinaryExchange(fv_src.pimg, FV_WIDTH, FV_HEIGHT, TOWB);
//				 //ImageExport(&fv_src, FINGER_VEIN);
//				 //BinaryExchange(fv_src.pimg, FV_WIDTH, FV_HEIGHT, TOOZ);
//				 //BinaryExchange(fv_src_copy.pimg, FV_WIDTH, FV_HEIGHT, TOOZ);
//					
//				 //FPMinutiaSetMatching(&fp_minutia, &(user->fp_minutia), &match_result, BOUND_BOX, SIMI_THR, ANGLE_THR, CENTRAL_THR, 1);
//				 ImageTemplateMatchingV1(fv_src.pimg, fv_src_copy.pimg, &percent, 30, 5, 60, 5, 2, FV_WIDTH, FV_HEIGHT, FV_PITCH);
//		  
//		         if (percent > MATCH_PERCENT) {
//					 FPImageProcessing(&fp_src_org, &fp_src, &fp_imageG, &fp_imageO, 13, 13, 2, 30, 0.4, 3, 12, &fp_minutia);
//					 FPMinutiaSetMatching(&fp_minutia, &(user->fp_minutia), &match_result, BOUND_BOX, SIMI_THR, ANGLE_THR, CENTRAL_THR, 1);
//					 if (match_result.similarity > MATCH_SIMILARITY) {
//						match_ok = _true;
//						break;
//					 } else {
//						 match_ok = _false;
//						 user=sys_database_get_next();
//					 }
//				} else{
//					match_ok = _false;
//		              user=sys_database_get_next();
//		         }  
//		     }
//
//			 if (match_ok == _true) {
//			 	 BUZZER_TIP;
//			 	 oLCD_Fill_Rect_Buf(rectd.y0,rectd.x0,rectd.y1-rectd.y0+1, rectd.x1-rectd.x0+1, BLACK);
//				 gui_text_out_rect(user->name,&rectd,macro_text_h_align_center|\
//					 macro_text_v_align_center);
//				 oLCD_Update_Rect_Screen(rectd.y0,rectd.x0,rectd.y1-rectd.y0+1, rectd.x1-rectd.x0+1);
//				 _delay_ms(2000);
//				 oLCD_Fill_Rect_Buf(rectd.y0,rectd.x0,rectd.y1-rectd.y0+1, rectd.x1-rectd.x0+1, BLACK);
//			 } else {
//				 BUZZER_TIP;
//				 oLCD_Fill_Rect_Buf(rectd.y0,rectd.x0,rectd.y1-rectd.y0+1, rectd.x1-rectd.x0+1, BLACK);
//				 gui_text_out_rect("请重试!",&rectd,macro_text_h_align_center|\
//					 macro_text_v_align_center);
//				 oLCD_Update_Rect_Screen(rectd.y0,rectd.x0,rectd.y1-rectd.y0+1, rectd.x1-rectd.x0+1);
//				 _delay_ms(500);
//				 oLCD_Fill_Rect_Buf(rectd.y0,rectd.x0,rectd.y1-rectd.y0+1, rectd.x1-rectd.x0+1, BLACK);
//				 oLCD_Update_Rect_Screen(rectd.y0,rectd.x0,rectd.y1-rectd.y0+1, rectd.x1-rectd.x0+1);
//				 _delay_ms(500);
//				 BUZZER_TIP;
//				 gui_text_out_rect("请重试!",&rectd,macro_text_h_align_center|\
//					 macro_text_v_align_center);
//				 oLCD_Update_Rect_Screen(rectd.y0,rectd.x0,rectd.y1-rectd.y0+1, rectd.x1-rectd.x0+1);
//				 _delay_ms(500);
//				 oLCD_Fill_Rect_Buf(rectd.y0,rectd.x0,rectd.y1-rectd.y0+1, rectd.x1-rectd.x0+1, BLACK);
//				//oLCD_Update_Rect_Screen(rectd.y0,rectd.x0,rectd.y1-rectd.y0+1, rectd.x1-rectd.x0+1);
//				//_delay_ms(500);
//			 }
//
//			 oLCD_Update_Rect_Screen(rectd.y0,rectd.x0,rectd.y1-rectd.y0+1, rectd.x1-rectd.x0+1);
//			
//			//BUZZER_TIP;
//
//		//}
//		asm ( " NOP " ) ;
//	}
//}





