/******************************************************************************
 * 文件名：image.h
 * 功能：  实现了指纹图像的基本操作
******************************************************************************/

#include "GUI_header/GUI.h"

uint32_t gResFileTab[MAX_RES_FILE_COUNT];


void gui_draw_v_line(int32_t x0, int32_t y0, int32_t y1, uint16_t color)
{
	for(; y0<=y1; y0++)
	{
		gui_draw_pixel(y0, x0, color);
	}
}


void gui_draw_h_line(int32_t x0, int32_t y0, int32_t x1, uint16_t color)
{
	for(; x0<=x1; x0++)
	{
		gui_draw_pixel(y0, x0, color);
	}
}

void gui_draw_rect(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint16_t color)
{
	gui_draw_v_line(x0,y0,y1,color);
	gui_draw_h_line(x0,y1,x1,color);
	gui_draw_v_line(x1,y0,y1,color);
	gui_draw_h_line(x0,y0,x1,color);
}

void load_bitmap_8bpp(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX,uint16_t *pic)
{
	uint16_t x, y;
	uint16_t color;
	uint8_t *pS = (uint8_t *)pic;
	
	for(y=StartY; y<(StartY+LongY); y++)
	{
		for(x=StartX; x<(StartX+LongX); x++)
		{
			color = Color8_To_B16_565(*pS++);
			//oLCD_WriteData(color);
			gui_draw_pixel(y, x, color);
		}
	}

}

void load_bitmap_16bpp(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX,uint16_t *pic)
{
	uint16_t x, y;
	uint16_t *pS = pic;

	for(y=StartY; y<(StartY+LongY); y++)
	{
		for(x=StartX; x<(StartX+LongX); x++)
		{
			gui_draw_pixel(y, x, *pS++);
		}
	}
}


void gui_fill_rect_buf(rect_t *rect, uint16_t color)
{
	uint16_t x ,y ;
	uint16_t StartY, StartX, LongY, LongX;
	StartY = rect->y0;
	StartX = rect->x0;
	LongY = rect->y1 - rect->y0 + 1;
	LongX = rect->x1 - rect->x0 + 1;
	for ( y = StartY ; y < ( StartY + LongY ) ; y++ )
	{
		for ( x = StartX ; x < ( StartX + LongX ) ; x++ )
		{
			gui_draw_pixel(y, x, color);
		}
	}
}

//#define 	RESOURCE_ADDR		0x803da000
#define RESOURCE_ADDR		0x80600000

void GuiInit(void) 
{
	//load_bitmap_16bpp(0, 0, 240, 320, (uint16_t *)gImage_graph1);
	uint32_t *ptr_dst;
	uint32_t *ptr_src;
	uint32_t len;
	uint32_t i;

	gInputData.size = 0;
	for (i = 0; i < 36; i++) {
		gInputData.data[i] = 0;
	}

	len= 0x26000*2;//240*320*2/2kword=37.5扇区=38扇区
	ptr_dst=(uint32_t *)RESOURCE_ADDR;
    ptr_src=(uint32_t *)0x64000000;
   //拷贝FLASH数据到SDRAM,注意先选者页号
    flash_select_page(1);
    for(i=0;i<len;i++)
    {
       *ptr_dst++=*ptr_src++;
    }
    //*(uint32_t*)(0x8060000c) = 0x00000000;

	gResFileTab[0]=(uint32_t)(RESOURCE_ADDR);  //保留给主框架
	gResFileTab[1]=(uint32_t)(RESOURCE_ADDR+0x26000);	//240*320*2/2kword=37.5扇区=38扇区
	load_bitmap_16bpp(0, 0, 240, 320, (uint16_t *)(gResFileTab[0]));
	oLCD_Update_Rect_Screen(0, 0, 240, 320);
	//load_bitmap_16bpp(0, 0, 240, 320, (uint16_t *)(gResFileTab[1]));
	//oLCD_Update_Rect_Screen(0, 0, 240, 320);
	asm ( " NOP " ) ;
}


time_t tm;
void ShowTime(void) 
{						 //0123456789					
	char *time_high_ptr = "2012-05-21";//请使用24x24字体
	char *weekcode = "一二三四五六日";
	char *time_low_ptr =  "20:18";
	char *time_week = "周一";

	rect_t rect_time_high, rect_time_low, rect_time_week; //显示年月日星期的矩形区域
	time_t *systemtime;
	rect_time_high.x0 = 120;
	rect_time_high.y0 = 11;
	rect_time_high.x1 = 200;
	rect_time_high.y1 = 31;
	rect_time_low.x0 = 120;
	rect_time_low.y0 = 31;
	rect_time_low.x1 = 200;
	rect_time_low.y1 = 41;
	rect_time_week.x0 = 120;
	rect_time_week.y0 = 41;
	rect_time_week.x1 = 200;
	rect_time_week.y1 = 65;


	DS1302_Get_Time(&tm);
	systemtime = &tm;
	time_high_ptr[2]  = (((systemtime->year)&0xf0)>>4)+0x30;//年的十位
	time_high_ptr[3]  = (((systemtime->year)&0x0f)>>0)+0x30;//年的个位
	time_high_ptr[5]  = (((systemtime->month)&0xf0)>>4)+0x30;//月的十位
	time_high_ptr[6]  = (((systemtime->month)&0x0f)>>0)+0x30;//月的个位
	time_high_ptr[8] = (((systemtime->day)&0xf0)>>4)+0x30;//日的十位
	time_high_ptr[9] = (((systemtime->day)&0x0f)>>0)+0x30;//日的个位
	//time_high_ptr[13] = weekcode[(systemtime->week-1)*2 + 0];//星期
	//time_high_ptr[14] = weekcode[(systemtime->week-1)*2 + 1];//星期

	time_low_ptr[0] = (((systemtime->hour)&0xf0)>>4)+0x30;//小时的十位
	time_low_ptr[1] = (((systemtime->hour)&0x0f)>>0)+0x30;//小时的个位
	time_low_ptr[3] = (((systemtime->minute)&0xf0)>>4)+0x30;//分钟的十位
	time_low_ptr[4] = (((systemtime->minute)&0x0f)>>0)+0x30;//分钟的个位
	//time_low_ptr[6] = (((systemtime->second)&0xf0)>>4)+0x30;
	//time_low_ptr[7] = (((systemtime->second)&0x0f)>>0)+0x30;
	time_week[2] = weekcode[(systemtime->week-1)*2 + 0];//星期
	time_week[3] = weekcode[(systemtime->week-1)*2 + 1];//星期

	//gui_set_font_quick(FONT_STYLE_MIDDLE);//设置为24x24字体
	oLCD_Fill_Rect_Buf(rect_time_high.y0, rect_time_high.x0, (rect_time_high.y1-rect_time_high.y0+1), (rect_time_high.x1-rect_time_high.x0+1), BLACK);
	oLCD_Fill_Rect_Buf(rect_time_low.y0, rect_time_high.x0, (rect_time_low.y1-rect_time_low.y0+1), (rect_time_high.x1-rect_time_low.x0+1), BLACK);
	gui_text_out_rect(time_high_ptr, &rect_time_high, macro_text_h_align_left|macro_text_v_align_center);
	gui_text_out_rect(time_low_ptr, &rect_time_low, macro_text_h_align_center|macro_text_v_align_center);
	gui_text_out_rect(time_week, &rect_time_week, macro_text_h_align_center|macro_text_v_align_center);
	//gui_set_font_quick(FONT_STYLE_NORMAL);//设置回系统默认字体
	//oLCD_Update_Rect_Screen(rect_time_high.y0, rect_time_high.x0, (rect_time_high.y1-rect_time_high.y0+1), (rect_time_high.x1-rect_time_high.x0+1));
	//oLCD_Update_Rect_Screen(rect_time_low.y0, rect_time_high.x0, (rect_time_low.y1-rect_time_low.y0+1), (rect_time_high.x1-rect_time_low.x0+1));

}
