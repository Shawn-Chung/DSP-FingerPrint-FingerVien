/******************************************************************************
 * 文件名：image.h
 * 功能：  实现了指纹图像的基本操作
******************************************************************************/

#if !defined __GUI_H
#define __GUI_H


/* 基本类型定义 */
#include "../../bsp/bsp_header/z_mytype.h"
#include "../../header.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_RES_FILE_COUNT		10


extern uint32_t gResFileTab[MAX_RES_FILE_COUNT];
extern uint8_t key_on;

typedef struct area_t{
	int32_t x0;   //左上角x坐标
	int32_t y0;   //左上角y坐标
	int32_t x1;   //右下脚x坐标
	int32_t y1;   //右下角y坐标
}area_t;

typedef area_t rect_t;

typedef struct font_t{
	uint16_t height;
	uint16_t width;
	uint32_t type;
}font_t;


typedef struct pen_t{
	uint16_t width;    //画笔的直线宽度
	uint16_t forecolor;//前景色
	uint16_t backcolor;//背景色
	uint16_t style;    //画笔风格
}pen_t;


#define load_char_dot_matrix(ch,count,buf)  Gt23l32s4w_Get_Font(ch, count, buf)

#define gui_draw_pixel(y, x, color)			oLCD_Fill_Pixel_Buf(y, x, color)


//#define load_bitmap_8bpp(StartY, StartX, LongY, LongX, pic)		oLCD_Draw_Picture8(StartY, StartX, LongY, LongX, pic)


//#define load_bitmap_16bpp(StartY, StartX, LongY, LongX, pic)	oLCD_Draw_Picture(StartY, StartX, LongY, LongX, pic)

void load_bitmap_8bpp(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX,uint16_t *pic);

void load_bitmap_16bpp(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX,uint16_t *pic);

void gui_fill_rect_buf(rect_t *rect, uint16_t color);



void gui_draw_h_line(int32_t x0,int32_t y0,int32_t x1,uint16_t color);
void gui_draw_v_line(int32_t x0,int32_t y0,int32_t y1,uint16_t color);

void gui_draw_rect(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint16_t color);


void gui_put_char(uint16_t ch ,int x,int y);
void gui_text_out     (char*str,int32_t x,int32_t y);
void gui_text_out     (char*str,int32_t x,int32_t y);
void gui_text_out_c   (char*str,int32_t x,int32_t y ,int32_t count);
void gui_text_out_rect(char*str,rect_t *rect,uint32_t style);

//与设备相关的操作，向上一层提供与设备无关的操作
//void     gui_set_font(font_t *font);
void 	 gui_set_font(font_t *font);
void     gui_get_font(font_t *font);
void     gui_set_pen (pen_t *pen);
void     gui_get_pen (pen_t *pen);



void GuiInit(void);

void ShowTime(void) ;


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* __IMAGE_H */

