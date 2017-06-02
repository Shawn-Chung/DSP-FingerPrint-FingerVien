#ifndef __DS1302_H__
#define __DS1302_H__

#include <csl_gpio.h>
#include "z_mytype.h"
#include "z_sys_time.h"
#include "z_cpld_cmd.h"

/*=========时钟芯片驱动（DS1302）================*/
/*--硬件连接--*/
//DS1302_CLK-->GP9		（初始化输出）
//DS1302_IO -->GP0		（初始化输出）
//DS1302_RST-->GP3		（初始化输出）
/*===========================================*/
extern  GPIO_Handle hGpio;

#define DS1302_IO			GPIO_PIN0
#define DS1302_CLK			GPIO_PIN9
#define DS1302_RST			GPIO_PIN3

#define DS1302_IO_IN		GPIO_pinDirection( hGpio , DS1302_IO , GPIO_INPUT )
#define DS1302_IO_OUT		GPIO_pinDirection( hGpio , DS1302_IO , GPIO_OUTPUT )

#define	DS1302_IO_H			GPIO_pinWrite( hGpio , DS1302_IO , 1 )
#define	DS1302_IO_L			GPIO_pinWrite( hGpio , DS1302_IO , 0 )

#define	DS1302_CLK_H		GPIO_pinWrite( hGpio , DS1302_CLK , 1 )
#define	DS1302_CLK_L		GPIO_pinWrite( hGpio , DS1302_CLK , 0 )

#define	DS1302_RST_H		GPIO_pinWrite( hGpio , DS1302_RST , 1 )
#define	DS1302_RST_L		GPIO_pinWrite( hGpio , DS1302_RST , 0 )

//返回一个32位的值:0或1
#define	DS1302_IO_VAL		GPIO_pinRead ( hGpio , DS1302_IO )
//BCD码转为十进制
#define BCD_TO_BIN(val)		( (val) = ( (val) >> 4 )*10 + ( (val)&15 ) )
//时钟读写定义
#define WRITE				0x00
#define READ				0x01
//时钟地址定义
#define SECOND				0x80	//秒地址
#define MINUTE				0x82	//分地址
#define HOUR				0x84	//小时
#define DAY					0x86	//日期
#define MONTH				0x88	//月
#define	WEEK				0x8a	//星期
#define YEAR				0x8c	//年
#define CONTROL				0x8e	//控制寄存器（控制写保护）
#define CHARGE				0x90	//
#define BURST				0xbe
//数据配置
#define STOP				0x80	//停止振荡器
#define START				0x00	//启动震荡器
#define AM_PM				0x80	//时间制式选择
#define PROTECT				0x80	//写保护
#define UPROTECT			0x00	//取消写保护

typedef struct {
	unsigned char second;
	unsigned char minute;
	unsigned char hour;
	unsigned char day;
	unsigned char month;
	unsigned char week;
	unsigned char year;
	unsigned char rsv;//保留
} time_t;

inline static void DS1302_Dalay(void) ;
static void DS1302_Write_Byte(uint8_t byte) ;
static uint8_t DS1302_Read_Byte(void) ;
static void DS1302_Write_Addr(uint8_t addr,uint8_t data) ;
//static 
uint8_t DS1302_Read_Addr(uint8_t addr) ;
void ds1302_init(void) ;
uint8_t DS1302_Set_Time(time_t *systime) ;
uint8_t DS1302_Get_Time(time_t *systime) ;


















#endif 


