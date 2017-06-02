
#include "bsp_header\z_ds1302.h"
#include "bsp_header\z_sys_time.h"


inline static void DS1302_Dalay(void)
{
	_delay_us(5);
}
/*******************************************************************
函数功能：向DS1302送一字节数据程序
入口参数：byte
********************************************************************/
static void DS1302_Write_Byte(uint8_t byte)
{
	uint8_t	count ;
	for ( count = 0; count < 8; count++ ){	
		DS1302_CLK_L ;
		if ( byte & 0x01 )
			DS1302_IO_H ;
		else
			DS1302_IO_L ;
		DS1302_Dalay();
		DS1302_CLK_H ;     //_____/--------		
		byte >>= 1;
	}
}
/*******************************************************************
函数功能：读DS1302一个字节程序
出口参数：data
*******************************************************************/
static uint8_t DS1302_Read_Byte(void)
{
	uint8_t count ;
	uint8_t temp ;
	uint8_t data = 0 ;
	DS1302_IO_IN ; //IO SHOULD BE INPUT
	DS1302_Dalay();
	for ( count = 0; count < 8; count ++ ){
		data >>= 1;
		DS1302_CLK_H ;
		DS1302_Dalay();
		DS1302_CLK_L ;
		DS1302_Dalay();
		temp = DS1302_IO_VAL ;
		if ( temp ) data |= 0x80;
	}
	DS1302_IO_OUT ;//IO RESET TO BE OUTPUT
	return data ;
}
/*******************************************************************
函数功能：向DS1302某地址写一字节数据程序
入口参数：addr,data
*******************************************************************/
static void DS1302_Write_Addr(uint8_t addr,uint8_t data)
{
	DS1302_RST_L ;
	DS1302_CLK_L ;
	DS1302_Dalay();
	DS1302_RST_H ;
	DS1302_Dalay();
	DS1302_Write_Byte( addr ) ;
	DS1302_Dalay();
	DS1302_CLK_L ;
	DS1302_Dalay();
	DS1302_Write_Byte( data ) ;
	DS1302_CLK_L ;
	DS1302_Dalay();
	DS1302_RST_L ;
}
/******************************************************************
函数功能：读DS1302地址程序 读出为BCD码
入口参数：addr 
******************************************************************/
//static 
uint8_t DS1302_Read_Addr(uint8_t addr)
{
	uint8_t  data;
	
	DS1302_RST_L ;
	DS1302_CLK_L ;
	DS1302_Dalay();
	DS1302_RST_H ;
	DS1302_Dalay();
	DS1302_Write_Byte( addr ) ;
	DS1302_Dalay();
	data = DS1302_Read_Byte() ;
	DS1302_Dalay();
	DS1302_CLK_L ;
	DS1302_RST_L ;

	return data;
}
/******************************************************************
函数功能：初始化DS1302程序
*******************************************************************/
void ds1302_init(void)
{

	asm ( " NOP " ) ;
	///设定时间
	DS1302_Write_Addr( CONTROL|WRITE , UPROTECT ) ;

	//DS1302_Write_Addr( SECOND|WRITE , 0x30 ) ;
	//DS1302_Write_Addr( MINUTE|WRITE , 0x20 ) ;
	//DS1302_Write_Addr( HOUR|WRITE , 0x22 ) ;
	//DS1302_Write_Addr( DAY|WRITE , 0x04 ) ;
	//DS1302_Write_Addr( MONTH|WRITE , 0x06 ) ;
	//DS1302_Write_Addr( WEEK|WRITE , 0x01 ) ;
	//DS1302_Write_Addr( YEAR|WRITE , 0x12 ) ;

	DS1302_Write_Addr( CONTROL|WRITE , PROTECT ) ;

}
/******************************************************************
函数功能：DS1302修改时间
*******************************************************************/
uint8_t DS1302_Set_Time(time_t *systime)
{
	if (systime == NULL)
	{
		return FALSE;
	}
	else
	{
		DS1302_Write_Addr(CONTROL|WRITE, UPROTECT);	          //不保护寄存器，在对时钟或RAM写前WP一定要为0,启动振荡器
		DS1302_Write_Addr(YEAR|WRITE, systime->year);    //年
		DS1302_Write_Addr(WEEK|WRITE, systime->week);    //星期
		DS1302_Write_Addr(MONTH|WRITE, systime->month);   //月
		DS1302_Write_Addr(DAY|WRITE, systime->day);     //日
		DS1302_Write_Addr(HOUR|WRITE, systime->hour);    //时
		DS1302_Write_Addr(MINUTE|WRITE, systime->minute);  //分
		DS1302_Write_Addr(SECOND|WRITE, systime->second);  //秒
		DS1302_Write_Addr(CONTROL|WRITE, PROTECT);          //写保护寄存器
	}
	
	return TRUE;
}
/******************************************************************
函数功能：读DS1302时间程序
出口参数：
******************************************************************/
uint8_t DS1302_Get_Time(time_t *systime)
{
	if (systime == NULL)
	{
		return FALSE;
	}
	else
	{
		systime->second = DS1302_Read_Addr(SECOND|READ);  //读秒
		systime->minute = DS1302_Read_Addr(MINUTE|READ);  //分
		systime->hour   = DS1302_Read_Addr(HOUR|READ);  //时
		systime->day    = DS1302_Read_Addr(DAY|READ);  //日
		systime->month  = DS1302_Read_Addr(MONTH|READ);  //月
		systime->week   = DS1302_Read_Addr(WEEK|READ);  //星期
		systime->year   = DS1302_Read_Addr(YEAR|READ);  //年
	}
	
	return TRUE;
}


















