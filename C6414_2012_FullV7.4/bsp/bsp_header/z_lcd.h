#ifndef __LCD__
#define __LCD__

#include"z_mytype.h"
#include"z_cpld_cmd.h"

#define   LCD_Y_MAX     240
#define   LCD_X_MAX     320
/*定义常见颜色*/
#define   RED        0x001f
#define   BLUE       0xf800
#define   GREEN      0x07e0
#define   BLACK      0x0000
#define   WHITE      0xffff
#define   YELLOW     0xffe0
#define   ORANGE     0x05bf
#define   CHOCOLATE  0x4451
#define   GREY       0x8430
#define   CYAN       0x7fff   //青色
#define   MAGENTA    0xf81f   //粉红
#define   BROWN 	 0xBC40 //棕色
#define   BRRED 	 0XFC07 //棕红色
#define   LGRAY 	 0XC618 //浅灰色


extern unsigned char gImage_pic[] ;

inline static void LCD_WriteCmd ( uint16_t cmd ) ;
inline static void LCD_WriteData( uint16_t data ) ;
void LCD_WriteReg( uint16_t Index ,uint16_t Data ) ;
void LCD_WriteStart( void ) ;
void LCD_SetCursor( int16_t y , int16_t x ) ;
void LCD_Clear( uint16_t color ) ;
void LCD_Init( void ) ;
void LCD_Update_Full_Screen( uint16_t *buf ) ;
void LCD_Fill_Pixel_Buf( uint16_t y , uint16_t x , uint16_t color ) ;
void LCD_Fill_Rect_Buf(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX , uint16_t color) ;
void LCD_Update_Rect_Screen ( uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX ) ;
void LCD_Fill_Full_Buf ( uint16_t color ) ;
void LCD_Write_Screen ( void ) ;
void LCD_Draw_Picture(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX,uint16_t *pic) ;




#endif  


