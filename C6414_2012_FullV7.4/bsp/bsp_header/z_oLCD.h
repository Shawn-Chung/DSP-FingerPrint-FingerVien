#ifndef __oLCD__
#define __oLCD__

#include"z_mytype.h"
#include"z_cpld_cmd.h"
#include"z_flash.h"

#define   oLCD_Y_MAX     240
#define   oLCD_X_MAX     320
/*定义常见颜色*/
#define   RED        0xf800
#define   BLUE       0x001f
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




//inline static void oLCD_WriteCmd ( uint16_t cmd ) ;
//inline static void oLCD_WriteData( uint16_t data ) ;
void oLCD_WriteReg( uint16_t Index ,uint16_t Data ) ;
void oLCD_WriteStart( void ) ;
void oLCD_SetCursor( int16_t y , int16_t x ) ;
void oLCD_Clear( uint16_t color ) ;
void oLCD_Init( void ) ;
void oLCD_Update_Full_Screen( uint16_t *buf ) ;
void oLCD_Fill_Pixel_Buf( uint16_t y , uint16_t x , uint16_t color ) ;
void oLCD_Fill_Rect_Buf(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX , uint16_t color) ;
void oLCD_Update_Rect_Screen ( uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX ) ;
void oLCD_Fill_Full_Buf ( uint16_t color ) ;
//void oLCD_Test ( void ) ;
void oLCD_Draw_Picture(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX,uint16_t *pic) ;
uint16_t Color8_To_B16_565(uint8_t color) ;
//uint16_t Color8_To_B16_565(uint8_t color);
void oLCD_Write_Chinese ( uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX ,uint16_t CharColor , uint16_t CharBackColor , uint8_t *ChineseCode ) ;



void oLCD_Draw_Picture8(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX, uint16_t *pic);


#endif  


