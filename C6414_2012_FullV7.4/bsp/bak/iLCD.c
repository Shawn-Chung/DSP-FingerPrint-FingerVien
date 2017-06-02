


#include"bsp_header\z_iLCD.h"


static uint16_t pic[16384] ;
static uint16_t iLCD_display_BUF[iLCD_Y_MAX][iLCD_X_MAX] ;
inline static void iLCD_WriteCmd (uint16_t cmd)
{   
//以下为液晶7783（带锁存器）的数据写法，先低后高
#ifdef _7783_
	LCD_CMD_BEGIN ; //写指令开始
	_74HC573_LE_H ; //写低8位开始
	*((unsigned short*)(0x6c000040))= cmd ;//BEA6//CE0
	_74HC573_LE_L ; //写高8位开始
	*((unsigned short*)(0x6c000040))= (cmd>>8);//BEA6//CE0
	LCD_TRANSFER_END ; //写完毕
#endif
//以上为液晶7783（带锁存器）的数据写法，先低后高

//以下为液晶ILI9320(真正的8位模式)的数据写法，先高后低
#ifdef ILI9320
	LCD_CMD_BEGIN ; //写指令开始
	*((unsigned short*)(0x6c000040))= (cmd>>8) ;//BEA6//CE0
	*((unsigned short*)(0x6c000040))= cmd ;//BEA6//CE0
	LCD_TRANSFER_END ; //写完毕
#endif
//以上为液晶ILI9320(真正的8位模式)的数据写法，先高后低
} 

inline static void iLCD_WriteData(uint16_t data)//
{
//以下为液晶7783（带锁存器）的数据写法，先低后高
#ifdef _7783_
	LCD_DATA_BEGIN ; //写数据开始
	_74HC573_LE_H ; //写低8位开始
	*((unsigned short*)(0x6c000040))=data;//BEA6//CE0
	_74HC573_LE_L ; //写高8位开始
	*((unsigned short*)(0x6c000040))=(data>>8);//BEA6//CE0
	LCD_TRANSFER_END ; //写完毕
#endif
//以上为液晶7783（带锁存器）的数据写法，先低后高

//以下为液晶ILI9320(真正的8位模式)的数据写法，先高后低
#ifdef ILI9320
	LCD_DATA_BEGIN ; //写指令开始
	*((unsigned short*)(0x6c000040))= (data>>8) ;//BEA6//CE0
	*((unsigned short*)(0x6c000040))= data ;//BEA6//CE0
	LCD_TRANSFER_END ; //写完毕
#endif
//以上为液晶ILI9320(真正的8位模式)的数据写法，先高后低
}

void iLCD_WriteReg(uint16_t Index,uint16_t Data)
{  
    //_delay_ms(1);
	iLCD_WriteCmd(Index);
	//_delay_ms(1);
	iLCD_WriteData(Data);
}
/************************************************
函数名：Lcd写开始函数
功能：控制Lcd控制引脚 执行写操作
入口参数：无
返回值：无
************************************************/
void iLCD_WriteStart(void)
{
	iLCD_WriteCmd( 0x0022 ) ;
}
/******************************************************************
** 函数名称: LCD光标起点定位函数
** 函数功能: 指定320240液晶上的一点作为写数据的起始点
** 入口参数: y 坐标 0~239
**           x 坐标 0~319
** 返回参数: 无
*******************************************************************/
void iLCD_SetCursor( int16_t y ,int16_t x )
{ 
	iLCD_WriteReg(0x20,y);
	iLCD_WriteReg(0x21,x);//
}
/******************************************************************
** 函数名称: LCD全屏擦除函数
** 函数功能: 将LCD整屏擦为指定颜色
** 入口参数: color 指定LCD全屏颜色 RGB(5-6-5)
** 返回参数: 无
******************************************************************/
void iLCD_Clear(uint16_t color)
{
	uint32_t temp;
  
	iLCD_WriteReg(0x0050,0x00);   //水平GRAM起始位置
	iLCD_WriteReg(0x0051,239);     //水平GRAM终止位置
	iLCD_WriteReg(0x0052,0);   //垂直GRAM起始位置
	iLCD_WriteReg(0x0053,319);     //垂直GRAM终止位置
	
	iLCD_SetCursor(0,0);
	iLCD_WriteStart();

	for (temp = 0;  temp < ( iLCD_Y_MAX * iLCD_X_MAX ) ; temp++)
	{
		iLCD_WriteData(color);
	}
	asm ( "	nop" ) ;
}
/******************************************************************
** 函数名称: LCD初始化
** 函数功能: LCD初始化
** 入口参数: 无
** 返回参数: 无
*******************************************************************/
void iLCD_Init(void)
{
	LCD_BAKCLIGHT_ON ;//开背光
	LCD_INSIDE_RESET ;//复位（不可少）
	LCD_SET ;		  //DSP向内部液晶写数据（写数据之前一定要有这句）
//型号：7783
#ifdef _7783_
	iLCD_WriteReg(0x00FF,0x0001);
	iLCD_WriteReg(0x00F3,0x0008);
	iLCD_WriteReg(0x0001,0x0100);
	iLCD_WriteReg(0x0002,0x0700);
	iLCD_WriteReg(0x0003,0x1018);  //0x1030
	iLCD_WriteReg(0x0008,0x0302);
	iLCD_WriteReg(0x0008,0x0207);
	iLCD_WriteReg(0x0009,0x0000);
	iLCD_WriteReg(0x000A,0x0000);
	iLCD_WriteReg(0x0010,0x0000);  //0x0790
	iLCD_WriteReg(0x0011,0x0005);
	iLCD_WriteReg(0x0012,0x0000);
	iLCD_WriteReg(0x0013,0x0000);
	_delay_ms(50);
	iLCD_WriteReg(0x0010,0x12B0);
	_delay_ms(50);
	iLCD_WriteReg(0x0011,0x0007);
	_delay_ms(50);
	iLCD_WriteReg(0x0012,0x008B);
	_delay_ms(50);
	iLCD_WriteReg(0x0013,0x1700);
	_delay_ms(50);
	iLCD_WriteReg(0x0029,0x0022);
	
	//################# void Gamma_Set(void) ####################//
	iLCD_WriteReg(0x0030,0x0000);
	iLCD_WriteReg(0x0031,0x0707);
	iLCD_WriteReg(0x0032,0x0505);
	iLCD_WriteReg(0x0035,0x0107);
	iLCD_WriteReg(0x0036,0x0008);
	iLCD_WriteReg(0x0037,0x0000);
	iLCD_WriteReg(0x0038,0x0202);
	iLCD_WriteReg(0x0039,0x0106);
	iLCD_WriteReg(0x003C,0x0202);
	iLCD_WriteReg(0x003D,0x0408);
	_delay_ms(50);
	
	
	iLCD_WriteReg(0x0050,0x0000);		
	iLCD_WriteReg(0x0051,0x00EF);		
	iLCD_WriteReg(0x0052,0x0000);		
	iLCD_WriteReg(0x0053,0x013F);		
	iLCD_WriteReg(0x0060,0xA700);		
	iLCD_WriteReg(0x0061,0x0001);
	iLCD_WriteReg(0x0090,0x0033);				
	iLCD_WriteReg(0x002B,0x000B);		
	iLCD_WriteReg(0x0007,0x0133);
	_delay_ms(50);
	iLCD_Clear( BLUE ) ;

	LCD_RT_DISPLAY ; //DSP向内部液晶写数据完毕，把液晶总线交给AL422B开始实时显示
					//每次DSP想内部液晶写完数据都要有这句。。。。。
#endif

//型号ILI9320
#ifdef ILI9320
	iLCD_WriteReg( 0x00E5 , 0x8000 ) ;
    iLCD_WriteReg( 0x0000 , 0x0001 ) ;
	_delay_ms( 10 ) ;
	iLCD_WriteReg( 0x0000 , 0x0000 ) ;
	iLCD_WriteReg( 0x0001 , 0x0100 ) ;
	iLCD_WriteReg( 0x0002 , 0x0700 ) ;
	iLCD_WriteReg( 0x0003 , 0x1018 ) ;////////////

	iLCD_WriteReg( 0x0004 , 0x0000 ) ;
	iLCD_WriteReg( 0x0008 , 0x0207 ) ;
	iLCD_WriteReg( 0x0009 , 0x0000 ) ;
	iLCD_WriteReg( 0x000A , 0x0000 ) ;
	iLCD_WriteReg( 0x000C , 0x0001 ) ; //此处配置接口类型 16位 system接口
	iLCD_WriteReg( 0x000D , 0x0000 ) ;
	iLCD_WriteReg( 0x000F , 0x0000 ) ;

	_delay_ms( 10 ) ;
	iLCD_WriteReg( 0x0007 , 0x0101 ) ;
	_delay_ms( 10 ) ;
	//电源配置
	iLCD_WriteReg( 0x0010 , 0x0000 ) ;
	iLCD_WriteReg( 0x0011 , 0x0000 ) ;
	iLCD_WriteReg( 0x0012 , 0x0000 ) ;
	iLCD_WriteReg( 0x0013 , 0x0000 ) ;
	_delay_ms( 200 ) ;
	iLCD_WriteReg( 0x0010 , 0x17b0 ) ;
	iLCD_WriteReg( 0x0011 , 0x0137 ) ;
	_delay_ms( 50 ) ;
	iLCD_WriteReg( 0x0012 , 0x0139 ) ;
	_delay_ms( 50 ) ;
	iLCD_WriteReg( 0x0013 , 0x1700 ) ;
	iLCD_WriteReg( 0x0029 , 0x000c ) ;
	_delay_ms( 50 ) ;

	iLCD_WriteReg( 0x0030 , 0x0000 ) ;
	iLCD_WriteReg( 0x0031 , 0x0507 ) ;
	iLCD_WriteReg( 0x0032 , 0x0104 ) ;
	iLCD_WriteReg( 0x0035 , 0x0105 ) ;
	iLCD_WriteReg( 0x0036 , 0x0404 ) ;
	iLCD_WriteReg( 0x0037 , 0x0603 ) ;
	iLCD_WriteReg( 0x0038 , 0x0004 ) ;
	iLCD_WriteReg( 0x0039 , 0x0007 ) ;
	iLCD_WriteReg( 0x003c , 0x0501 ) ;
	iLCD_WriteReg( 0x003d , 0x0404 ) ;
	iLCD_WriteReg( 0x0050 , 0 ) ;	//水平GRAM起始位置
	iLCD_WriteReg( 0x0051 , 239 ) ;	//水平GRAM终止位置
	iLCD_WriteReg( 0x0052 , 0 ) ;	//垂直GRAM起始位置
	iLCD_WriteReg( 0x0053 , 319 ) ;	//垂直GRAM终止位置

	iLCD_WriteReg( 0x0060 , 0x2700 ) ;
	iLCD_WriteReg( 0x0061 , 0x0001 ) ;
	iLCD_WriteReg( 0x006A , 0x0000 ) ;

	iLCD_WriteReg( 0x0080 , 0x0000 ) ;
	iLCD_WriteReg( 0x0081 , 0x0000 ) ;
	iLCD_WriteReg( 0x0082 , 0x0000 ) ;
	iLCD_WriteReg( 0x0083 , 0x0000 ) ;
	iLCD_WriteReg( 0x0084 , 0x0000 ) ;
	iLCD_WriteReg( 0x0085 , 0x0000 ) ;

	iLCD_WriteReg( 0x0090 , 0x0010 ) ;
	iLCD_WriteReg( 0x0092 , 0x0000 ) ;
	iLCD_WriteReg( 0x0093 , 0x0003 ) ;
	iLCD_WriteReg( 0x0095 , 0x0110 ) ;
	iLCD_WriteReg( 0x0097 , 0x0000 ) ;
	iLCD_WriteReg( 0x0098 , 0x0000 ) ;

	iLCD_WriteReg( 0x0007 , 0x0173 ) ;
	_delay_ms( 10 ) ;
	
	iLCD_Clear( 0 ) ;

	LCD_RT_DISPLAY ; //DSP向内部液晶写数据完毕，把液晶总线交给AL422B开始实时显示
	                     //每次DSP想内部液晶写完数据都要有这句。。。。。
#endif
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

void iLCD_Fill_Rect_Buf(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX , uint16_t color)
{
	uint16_t x ,y ;

	for ( y = StartY ; y < ( StartY + LongY ) ; y++ )
	{
		for ( x = StartX ; x <= ( StartX + LongX ) ; x++ )
		{
			iLCD_display_BUF[y][x] = color;
		}
	}
}
/****************************************************************************
* 显示模式：横屏
* 名    称：oLCD_Draw_Picture(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX,uint16_t *pic)
* 功    能：把显示缓冲区的指定区域的数据更新到指定矩形区域
* 入口参数：StartY      竖直方向起始座标
*           StartX     水平方向起始座标
*           LongY       竖直方向长度
*           LongX       水平方向长度
* 出口参数：无
* 说    明：参数的组合必须在屏幕范围内：(StartY+LongY)<=240,(StartX+LongX)<=320
* 调用方法：oLCD_Update_Rect_Screen( 0,0,240,320) ;
****************************************************************************/

void iLCD_Update_Rect_Screen ( uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX )
{
	uint16_t x ,y ;

	iLCD_WriteReg(0x0050,StartY  );//
    iLCD_WriteReg(0x0051,StartY+LongY-1 );//
    iLCD_WriteReg(0x0052,319-(StartX+LongX-1));//
    iLCD_WriteReg(0x0053,319-StartX);//

	iLCD_SetCursor(StartY,319-(StartX+LongX-1));
	iLCD_WriteStart();

//	iLCD_WriteData(iLCD_display_BUF[0][0]);//第一个数据为无效值，不在指定的区域内
	for(y=StartY; y<(StartY+LongY); y++)
	{
		for(x=StartX; x<(StartX+LongX); x++)
		{
			iLCD_WriteData(iLCD_display_BUF[y][x]);
		}
	}
}
/****************************************************************************
* 显示模式：横屏
* 名    称：oLCD_Draw_Picture(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX,uint16_t *pic)
* 功    能：在指定座标范围显示一副图片
* 入口参数：StartY      竖直方向起始座标
*           StartX     水平方向起始座标
*           LongY       竖直方向长度
*           LongX       水平方向长度
            pic        图片头指针
* 出口参数：无
* 说    明：图片取模格式为水平扫描，16位颜色模式
*           参数的组合必须在屏幕范围内：(StartY+LongY)<=240,(StartX+LongX)<=320
* 调用方法：oLCD_Draw_Picture( 0,0,240,320,(uint16_t*)gImage_pic) ;
****************************************************************************/
void iLCD_Draw_Picture(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX,uint16_t *pic)
{
  uint32_t  i;
  uint16_t  *ppic ;
  ppic = pic ;
  iLCD_WriteReg(0x0050,StartY  );//
  iLCD_WriteReg(0x0051,StartY+LongY-1 );//
  iLCD_WriteReg(0x0052,319-(StartX+LongX-1));//
  iLCD_WriteReg(0x0053,319-StartX);//

  
  iLCD_SetCursor(StartY, 319-(StartX+LongX-1));
  iLCD_WriteStart();
	
//  oLCD_WriteData(*ppic); //写第一个数据时不再指定的区域内，这里额外多写一个数据
  for (i=0;i<( LongY * LongX ) ;i++ )
  {
      iLCD_WriteData(*ppic++);
  }     
}
/****************************************************************************
* 显示模式：横屏
* 名    称：oLCD_Write_Chinese ( uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t * *           LongX ,uint16_t CharColor , uint16_t CharBackColor , uint16_t *ChineseCode )
* 功    能：显示汉字
* 入口参数：StartY      竖直方向起始座标
*           StartX     水平方向起始座标
*           LongY       竖直方向长度
*           LongX       水平方向长度，应为8的倍数
* 出口参数：无
* 说    明：取模顺序：左到右 上到下 横向8点左高位
*           取模数据类型为8位
* 调用方法：oLCD_Write_Chinese ( 0,0,16,16 , WHITE , BLACK , GB_16 ) ;
****************************************************************************/
void iLCD_Write_Chinese ( uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX ,uint16_t CharColor , uint16_t CharBackColor , uint8_t *ChineseCode )
{
	uint8_t  *pic ;
	uint8_t   ByteCounter , BitCounter ;
	pic = ChineseCode ;

	iLCD_WriteReg(0x0050,StartY  );//
	iLCD_WriteReg(0x0051,StartY+LongY-1 );//
	iLCD_WriteReg(0x0052,319-(StartX+LongX-1));//
	iLCD_WriteReg(0x0053,319-StartX);//

	iLCD_SetCursor(StartY, 319-(StartX+LongX-1));
    iLCD_WriteStart();
//	iLCD_WriteData(*pic); //写第一个数据时不再指定的区域内，这里额外多写一个数据
	for ( ByteCounter = 0 ; ByteCounter < ( LongY*LongX/8 ) ; ByteCounter++ )
	{
		for ( BitCounter = 0 ; BitCounter < 8 ; BitCounter++ )
		{
			if ( ( *pic & ( 0x80 >> BitCounter ) ) == 0x00 )
				iLCD_WriteData( CharBackColor ) ;
			else
				iLCD_WriteData( CharColor ) ;
		}
		pic++ ;
	}
}
/****************************************************************************
* 显示模式：横屏
* 名    称：oLCD_Draw_Picture(uint16_t StartY,uint16_t StartX,uint16_t LongY,uint16_t LongX,uint16_t *pic)
* 功    能：操作屏幕，在屏幕上显示内容
* 入口参数：无
* 出口参数：无
* 说    明：oLCD调试功能函数的时候用
* 调用方法：LCD_Write_Screen () ;
****************************************************************************/
void iLCD_Test ( void )
{

//	iLCD_Fill_Rect_Buf(1,1,5,5 , 0x0000) ;
//	iLCD_Update_Rect_Screen ( 1,1,5,5 ) ;
	uint32_t i , j ;
	flash_select_page(1) ; //flash选页
	j = 0 ;
	for ( i=0; i<0x8000; i+=2 ){
		pic[j] = flash_read_word( (FLASH_BASE_ADDR+i) ) ;
		j++ ;
	}
	iLCD_Draw_Picture( 0,192,128,128,pic) ;
	asm ( " NOP " ) ;
	asm ( " NOP " ) ;
}











