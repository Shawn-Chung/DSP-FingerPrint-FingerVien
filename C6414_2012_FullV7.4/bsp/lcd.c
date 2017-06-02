
#include"bsp_header\z_lcd.h"


static uint16_t LCD_display_BUF[LCD_Y_MAX][LCD_X_MAX] ;
//extern unsigned char gImage[33920] ;

inline static void LCD_WriteCmd (uint16_t cmd)
{
    *((unsigned short*)(0x68000000))=cmd;
} 

inline static void LCD_WriteData(uint16_t data)
{
    *((unsigned short*)(0x68000002))=data;
}

void LCD_WriteReg(uint16_t Index,uint16_t Data)
{  
    //_delay_ms(1);
	LCD_WriteCmd(Index);
	//_delay_ms(1);
	LCD_WriteData(Data);
}

/************************************************
函数名：Lcd写开始函数
功能：控制Lcd控制引脚 执行写操作
入口参数：无
返回值：无
************************************************/
void LCD_WriteStart(void)
{
	LCD_WriteCmd( 0x0022 ) ;
}
/******************************************************************
** 函数名称: LCD光标起点定位函数
** 函数功能: 指定320240液晶上的一点作为写数据的起始点
** 入口参数: x 坐标 0~239
**           y 坐标 0~319
** 返回参数: 无
*******************************************************************/
void LCD_SetCursor( int16_t y ,int16_t x )
{ 
	LCD_WriteReg(0x20,y);
	LCD_WriteReg(0x21,x);
}
/******************************************************************
** 函数名称: LCD全屏擦除函数
** 函数功能: 将LCD整屏擦为指定颜色
** 入口参数: color 指定LCD全屏颜色 RGB(5-6-5)
** 返回参数: 无
******************************************************************/
void LCD_Clear(uint16_t color)
{
	uint32_t temp;
  
	LCD_WriteReg(0x0050,0x00);   //水平GRAM起始位置
	LCD_WriteReg(0x0051,239);     //水平GRAM终止位置
	LCD_WriteReg(0x0052,0);   //垂直GRAM起始位置
	LCD_WriteReg(0x0053,319);     //垂直GRAM终止位置
	
	LCD_SetCursor(0,0);
	LCD_WriteStart();

	for (temp = 0;  temp < ( LCD_Y_MAX * LCD_X_MAX ) ; temp++)
	{
		LCD_WriteData(color);
	}
	asm ( "	nop" ) ;
}
/******************************************************************
** 函数名称: LCD初始化
** 函数功能: LCD初始化
** 入口参数: 无
** 返回参数: 无
*******************************************************************/
void LCD_Init(void)
{
	LCD_BAKCLIGHT_ON ; 
	LCD_WriteReg( 0x00E5 , 0x8000 ) ;
    LCD_WriteReg( 0x0000 , 0x0001 ) ;
	_delay_ms( 10 ) ;
	LCD_WriteReg( 0x0000 , 0x0000 ) ;
	LCD_WriteReg( 0x0001 , 0x0100 ) ;
	LCD_WriteReg( 0x0002 , 0x0700 ) ;
	LCD_WriteReg( 0x0003 , 0x1018 ) ;////////////

	LCD_WriteReg( 0x0004 , 0x0000 ) ;
	LCD_WriteReg( 0x0008 , 0x0207 ) ;
	LCD_WriteReg( 0x0009 , 0x0000 ) ;
	LCD_WriteReg( 0x000A , 0x0000 ) ;
	LCD_WriteReg( 0x000C , 0x0001 ) ; //此处配置接口类型 16位 system接口
	LCD_WriteReg( 0x000D , 0x0000 ) ;
	LCD_WriteReg( 0x000F , 0x0000 ) ;

	_delay_ms( 10 ) ;
	LCD_WriteReg( 0x0007 , 0x0101 ) ;
	_delay_ms( 10 ) ;
	//电源配置
	LCD_WriteReg( 0x0010 , 0x0000 ) ;
	LCD_WriteReg( 0x0011 , 0x0000 ) ;
	LCD_WriteReg( 0x0012 , 0x0000 ) ;
	LCD_WriteReg( 0x0013 , 0x0000 ) ;
	_delay_ms( 200 ) ;
	LCD_WriteReg( 0x0010 , 0x17b0 ) ;
	LCD_WriteReg( 0x0011 , 0x0137 ) ;
	_delay_ms( 50 ) ;
	LCD_WriteReg( 0x0012 , 0x0139 ) ;
	_delay_ms( 50 ) ;
	LCD_WriteReg( 0x0013 , 0x1700 ) ;
	LCD_WriteReg( 0x0029 , 0x000c ) ;
	_delay_ms( 50 ) ;
//	LCD_WriteReg( 0x002B , (1<<14)|(1<<4) ) ;
	LCD_WriteReg( 0x0030 , 0x0000 ) ;
	LCD_WriteReg( 0x0031 , 0x0507 ) ;
	LCD_WriteReg( 0x0032 , 0x0104 ) ;
	LCD_WriteReg( 0x0035 , 0x0105 ) ;
	LCD_WriteReg( 0x0036 , 0x0404 ) ;
	LCD_WriteReg( 0x0037 , 0x0603 ) ;
	LCD_WriteReg( 0x0038 , 0x0004 ) ;
	LCD_WriteReg( 0x0039 , 0x0007 ) ;
	LCD_WriteReg( 0x003c , 0x0501 ) ;
	LCD_WriteReg( 0x003d , 0x0404 ) ;
	LCD_WriteReg( 0x0050 , 0 ) ;	//水平GRAM起始位置
	LCD_WriteReg( 0x0051 , 239 ) ;	//水平GRAM终止位置
	LCD_WriteReg( 0x0052 , 0 ) ;	//垂直GRAM起始位置
	LCD_WriteReg( 0x0053 , 319 ) ;	//垂直GRAM终止位置

	LCD_WriteReg( 0x0060 , 0x2700 ) ;
	LCD_WriteReg( 0x0061 , 0x0001 ) ;
	LCD_WriteReg( 0x006A , 0x0000 ) ;

	LCD_WriteReg( 0x0080 , 0x0000 ) ;
	LCD_WriteReg( 0x0081 , 0x0000 ) ;
	LCD_WriteReg( 0x0082 , 0x0000 ) ;
	LCD_WriteReg( 0x0083 , 0x0000 ) ;
	LCD_WriteReg( 0x0084 , 0x0000 ) ;
	LCD_WriteReg( 0x0085 , 0x0000 ) ;

	LCD_WriteReg( 0x0090 , 0x0010 ) ;
	LCD_WriteReg( 0x0092 , 0x0000 ) ;
	LCD_WriteReg( 0x0093 , 0x0003 ) ;
	LCD_WriteReg( 0x0095 , 0x0110 ) ;
	LCD_WriteReg( 0x0097 , 0x0000 ) ;
	LCD_WriteReg( 0x0098 , 0x0000 ) ;

	LCD_WriteReg( 0x0007 , 0x0173 ) ;
	_delay_ms( 10 ) ;
	
	LCD_Clear( BLUE ) ;
}
/****************************************************************************
* 显示模式：横屏
* 名    称：LCD_Fill_Pixel_Buf( uint16_t y , uint16_t x , uint16_t color )
* 功    能：将缓冲区中的一个像素点更新成color颜色
* 入口参数：Y      竖直方向座标
*           X     水平方向座标
*			color		颜色
* 出口参数：无
* 说    明：
* 调用方法：LCD_Fill_Pixel_Buf( 0 , 0 , RED ) ;
****************************************************************************/
void LCD_Fill_Pixel_Buf( uint16_t y , uint16_t x , uint16_t color )
{
	if ( ( x >= LCD_X_MAX ) || ( y >= LCD_Y_MAX ) )
	{
		return;
	}
	else
	{
		LCD_display_BUF[y][x] = color ;
	}
}
/****************************************************************************
* 显示模式：横屏
* 名    称：LCD_Fill_Rect_Buf(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX , uint16_t color)
* 功    能：将缓冲区中的一个矩形框更新成color颜色
* 入口参数：StartY      竖直方向起始座标
*           StartX     水平方向起始座标
*           LongY       竖直方向长度
*           LongX       水平方向长度
*			color		颜色
* 出口参数：无
* 说    明：参数的组合必须在屏幕范围内：(StartY+LongY)<=240,(StartX+LongX)<=320
* 调用方法：LCD_Fill_Rect_Buf( 0,0,240,320,RED) ;
****************************************************************************/

void LCD_Fill_Rect_Buf(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX , uint16_t color)
{
	uint16_t x ,y ;

	for ( y = StartY ; y < ( StartY + LongY ) ; y++ )
	{
		for ( x = StartX ; x <= ( StartX + LongX ) ; x++ )
		{
			LCD_display_BUF[y][x] = color;
		}
	}
}
/****************************************************************************
* 显示模式：横屏
* 名    称：LCD_Fill_Full_Buf ( uint16_t color )
* 功    能：把color填充到整个显示缓冲区
* 入口参数：color		颜色
* 出口参数：无
* 说    明：可用LCD_Fill_Rect_Buf() ;代替
* 调用方法：LCD_Fill_Full_Buf ( RED ) ;
****************************************************************************/
/**/
void LCD_Fill_Full_Buf ( uint16_t color )
{
	uint16_t y ,x ;
	for ( y=0 ; y<LCD_Y_MAX ; y++ )
	{
		for ( x=0 ; x<LCD_X_MAX ; x++ )
		{
			LCD_display_BUF[y][x] = color;
		}
	}
}
/****************************************************************************
* 显示模式：横屏
* 名    称：LCD_Draw_Picture(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX,uint16_t *pic)
* 功    能：将整个缓冲区的数据刷新到屏幕
* 入口参数：*buf   缓冲数组
* 出口参数：无
* 说    明：
* 调用方法：LCD_Update_Full_Screen(&LCD_display_BUF[0][0]) ;
****************************************************************************/
/**/
void LCD_Update_Full_Screen(uint16_t *buf)
{
	uint32_t i;
	LCD_WriteReg(0x0050,0  );//
	LCD_WriteReg(0x0051,239);//
	LCD_WriteReg(0x0052,0  );//
	LCD_WriteReg(0x0053,319);//

	LCD_SetCursor(-1, 0);
    LCD_WriteStart();
    
    LCD_WriteData ( *( buf ) ) ;//写第一个数据时不再指定的区域内，这里额外多写一个数据
	for( i = 0 ; i < ( LCD_Y_MAX * LCD_X_MAX ) ; i++ )
	{
		LCD_WriteData ( *( buf + i ) ) ;
	}
}
/****************************************************************************
* 显示模式：横屏
* 名    称：LCD_Draw_Picture(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX,uint16_t *pic)
* 功    能：在指定座标范围显示一副图片
* 入口参数：StartY      竖直方向起始座标
*           StartX     水平方向起始座标
*           LongY       竖直方向长度
*           LongX       水平方向长度
            pic        图片头指针
* 出口参数：无
* 说    明：图片取模格式为水平扫描，16位颜色模式
*           参数的组合必须在屏幕范围内：(StartY+LongY)<=240,(StartX+LongX)<=320
* 调用方法：LCD_Draw_Picture( 0,0,240,320,(uint16_t*)gImage_pic) ;
****************************************************************************/
void LCD_Draw_Picture(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX,uint16_t *pic)
{
  uint32_t  i;
  LCD_WriteReg(0x0050,StartY  );//
  LCD_WriteReg(0x0051,StartY+LongY-1 );//
  LCD_WriteReg(0x0052,319-(StartX+LongX-1));//
  LCD_WriteReg(0x0053,319-StartX);//

  
  LCD_SetCursor(StartY-1, 319-(StartX+LongX-1));
  LCD_WriteStart();
	
  LCD_WriteData(*pic); //写第一个数据时不再指定的区域内，这里额外多写一个数据
  for (i=0;i<( LongY * LongX ) ;i++ )
  {
      LCD_WriteData(*pic++);
  }     
}
/****************************************************************************
* 显示模式：横屏
* 名    称：LCD_Draw_Picture(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX,uint16_t *pic)
* 功    能：把显示缓冲区的指定区域的数据更新到指定矩形区域
* 入口参数：StartY      竖直方向起始座标
*           StartX     水平方向起始座标
*           LongY       竖直方向长度
*           LongX       水平方向长度
* 出口参数：无
* 说    明：参数的组合必须在屏幕范围内：(StartY+LongY)<=240,(StartX+LongX)<=320
* 调用方法：LCD_Update_Rect_Screen( 0,0,240,320) ;
****************************************************************************/

void LCD_Update_Rect_Screen ( uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX )
{
	uint16_t x ,y ;

	LCD_WriteReg(0x0050,StartY  );//
    LCD_WriteReg(0x0051,StartY+LongY-1 );//
    LCD_WriteReg(0x0052,319-(StartX+LongX-1));//
    LCD_WriteReg(0x0053,319-StartX);//

	LCD_SetCursor(StartY-1, 319-(StartX+LongX-1));
	LCD_WriteStart();

	LCD_WriteData(LCD_display_BUF[0][0]);//第一个数据为无效值，不在指定的区域内
	for(y=StartY; y<(StartY+LongY); y++)
	{
		for(x=StartX; x<=(StartX+LongX); x++)
		{
			LCD_WriteData(LCD_display_BUF[y][x]);
		}
	}
}
/****************************************************************************
* 显示模式：横屏
* 名    称：LCD_Draw_Picture(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX,uint16_t *pic)
* 功    能：操作屏幕，在屏幕上显示内容
* 入口参数：无
* 出口参数：无
* 说    明：LCD调试功能函数的时候用
* 调用方法：LCD_Write_Screen () ;
****************************************************************************/
void LCD_Write_Screen ( void )
{
	//LCD_Draw_Picture( 0,0,240,320,(uint16_t*)gImage_pic) ;
	asm ( " NOP " ) ;
	
	LCD_Fill_Rect_Buf( 239,300,1,1,RED) ;
	LCD_Update_Rect_Screen( 239,300,1,1) ;
	LCD_Update_Full_Screen(&LCD_display_BUF[0][0]) ;
}








