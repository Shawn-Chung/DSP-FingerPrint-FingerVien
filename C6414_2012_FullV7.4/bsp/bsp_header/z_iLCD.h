#ifndef __iLCD__
#define __iLCD__

#include"z_mytype.h"
#include"z_cpld_cmd.h"
#include"z_flash.h"
#include"z_oLCD.h"
#define   iLCD_Y_MAX     240
#define   iLCD_X_MAX     320
/*定义常见颜色*/
//#define   RED        0x001f
//#define   BLUE       0xf800
//#define   GREEN      0x07e0
//#define   BLACK      0x0000
//#define   WHITE      0xffff
//#define   YELLOW     0xffe0
//#define   ORANGE     0x05bf
//#define   CHOCOLATE  0x4451
//#define   GREY       0x8430
//#define   CYAN       0x7fff   //青色
//#define   MAGENTA    0xf81f   //粉红
//#define   BROWN 	 0xBC40 //棕色
//#define   BRRED 	 0XFC07 //棕红色
//#define   LGRAY 	 0XC618 //浅灰色
//BEA19、18、15、14、11、10、7、6
//#define iLCD_REG_MSB	 	      ( *( uint16_t * ) 0x6C008440 )//->CPLD:0X25
//#define iLCD_REG_LSB	 	      ( *( uint16_t * ) 0x6C008480 )//->CPLD:0X26
//#define iLCD_DATA_MSB             ( *( uint16_t * ) 0x6C0084C0 )//->CPLD:0X27
//#define iLCD_DATA_LSB             ( *( uint16_t * ) 0x6C008800 )//->CPLD:0X28


inline static void iLCD_WriteCmd ( uint16_t cmd ) ;
inline static void iLCD_WriteData( uint16_t data ) ;
void iLCD_WriteReg( uint16_t Index ,uint16_t Data ) ;
void iLCD_WriteStart( void ) ;
void iLCD_SetCursor( int16_t y , int16_t x ) ;
void iLCD_Clear( uint16_t color ) ;
void iLCD_Init( void ) ;
void iLCD_Update_Full_Screen( uint16_t *buf ) ;
void iLCD_Fill_Pixel_Buf( uint16_t y , uint16_t x , uint16_t color ) ;
void iLCD_Fill_Rect_Buf(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX , uint16_t color) ;
void iLCD_Update_Rect_Screen ( uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX ) ;
void iLCD_Fill_Full_Buf ( uint16_t color ) ;
void iLCD_Test ( void ) ;
void iLCD_Draw_Picture(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX,uint16_t *pic) ;
//static uint16_t Color8_To_B16_565(uint8_t color) ;
void iLCD_Write_Chinese ( uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX ,uint16_t CharColor , uint16_t CharBackColor , uint8_t *ChineseCode ) ;



#endif  



