


#include "header.h"

//extern far STS_Obj sts; 


int main ( void )
{
	uint32_t i;
	//volatile uint32_t*ptr;
	//volatile uint32_t*ptrd;
	//time_t tm;

	//font_t oldfont;
	//font_t newfont;
	//pen_t oldPen;
	//pen_t newPen;
	//rect_t rect;
	//rect.x0=0;
	//rect.y0=0;
	//rect.x1=319;
	//rect.y1=40;
	

	bsp() ;			//初始化
	sys_global_init(); 

	GuiInit();
	asm ( " NOP " ) ;
	//while(1) {
	//	ZLG7290_Test_Key();
	//}
	//while (1) {
	//	flash_select_page(3);
	//	flash_erase_sector(0x64000000);
	//	for (i = 0; i < 4096; i+=2) {
	//		flash_write_word(0x64000000+i, 0x00);
	//	}

	//	asm ( " NOP " ) ;
	//}
#if 1
	while (1) {
		#if 0
		LIGHT_UP;
		LIGHT_UP;
		LIGHT_UP;
		//LIGHT_UP;D
		//LIGHT_UP;
		#endif
		#if 0
		LIGHT_DOWN;
		LIGHT_DOWN;
		LIGHT_DOWN;
		//LIGHT_DOWN;
		//LIGHT_DOWN;
		#endif
		#if 0
     	camera_capture(FINGER_VEIN);
		ImageImport(&fv_src_org, FINGER_VEIN);
		asm ( " NOP " ) ;
		#endif
		#if 1
		camera_capture(FINGER_PRINT);
		ImageImport(&fp_src_org, FINGER_PRINT);
		asm ( " NOP " ) ;
		#endif
	}
#endif
	//while (1) {
	//	//DS1302_Get_Time(&tm);
	//	ShowTime();
	//}
	//while (1) {
	//	
	//	gui_get_font(&oldfont);
	//	newfont.type=macro_font_style_middle;
	//	gui_set_font(&newfont);
	//	gui_text_out_rect("红色16", &rect, macro_text_v_align_center|macro_text_h_align_left);
	//	oLCD_Update_Rect_Screen(0, 0, 240, 320);
	//	newfont.type=macro_font_style_big;
	//	
	//	gui_set_font(&newfont);
	//	gui_get_pen(&oldPen);
	//	//newPen.style = macro_pen_style_overlap;
	//	newPen.forecolor = WHITE;
	//	//newPen.backcolor = RED;
	//	gui_set_pen(&newPen);
	//	gui_text_out_rect("白色24", &rect, macro_text_v_align_center|macro_text_h_align_left);
	//	oLCD_Update_Rect_Screen(0, 0, 240, 320);

	//	gui_set_font(&oldfont);
	//	gui_set_pen(&oldPen);

	//}
	//while (1) {
	//	//静脉
	//	//ImageFlood(&fv_dst, 0);
	//	//for (i = 0; i < 5; i++) {
	//	//camera_capture(FINGER_VEIN);
	//	//ImageImport(&fv_src_org, FINGER_VEIN);
	//	//camera_capture(FINGER_PRINT);
	//	//ImageImport(&fp_src_org, FINGER_PRINT);

	//	//FVImageProcessing(&fv_src_org, &fv_src, &fv_imageG, 7, 2, 6, 200, 80, &fv_minutia, 20);
	//	//pixel_add(fv_dst.pimg, fv_src.pimg, FV_WIDTH, FV_HEIGHT, FV_PITCH);
	//	//BinaryExchange(fv_dst.pimg, FV_WIDTH, FV_HEIGHT, TOWB);
	//	//ImageExport(&fv_dst, FINGER_VEIN);
	//	//BinaryExchange(fv_dst.pimg, FV_WIDTH, FV_HEIGHT, TOOZ);
	//	//ImageFlood(&fv_src_copy, 0);
	//	//ImageExport(&fv_src_copy, FINGER_VEIN);
	//	//pixel_compression_ex(fv_src_copy.pimg, fv_dst.pimg, FV_WIDTH, FV_HEIGHT, FV_PITCH);
	//	//pixel_decompression_ex(fv_dst.pimg, fv_src_copy.pimg, FV_WIDTH, FV_HEIGHT, FV_PITCH);
	//	//BinaryExchange(fv_dst.pimg, FV_WIDTH, FV_HEIGHT, TOWB);
	//	//ImageExport(&fv_dst, FINGER_VEIN);

	//	//asm ( " NOP " ) ;
	//	//}
	//	camera_capture(FINGER_VEIN);
	//	ImageImport(&fv_src_org, FINGER_VEIN);
	//	camera_capture(FINGER_PRINT);
	//	ImageImport(&fp_src_org, FINGER_PRINT);
	//	FPImageProcessing(&fp_src_org, &fp_src, &fp_imageG, &fp_imageO, 13, 13, 2, 30, 0.4, 3, 12, &fp_minutia);
	//	BinaryExchange(fp_src.pimg, FP_WIDTH, FP_HEIGHT, TOWB);
	//	ImageExport(&fp_src, FINGER_PRINT);

	//}

	

	//	
	//	asm ( " NOP " ) ;

	return 0;
	
}








