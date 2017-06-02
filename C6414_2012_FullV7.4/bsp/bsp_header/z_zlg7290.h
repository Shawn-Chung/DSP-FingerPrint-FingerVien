#ifndef __ZLG7290_H__
#define __ZLG7290_H__

#include <csl_gpio.h>
#include "z_mytype.h"
#include "z_sys_time.h"
#include "z_cpld_cmd.h"

/*=========键盘驱动（zlg7290）================*/
/*--硬件连接--*/
//SDA-->DSP_GP10
//SCL-->DSP_GP11
//INT-->EXT_INT4	下降沿触发
/*===========================================*/
extern  GPIO_Handle hGpio;

#define ZLG7290_SDA			GPIO_PIN10
#define ZLG7290_SCL			GPIO_PIN11

#define ZLG7290_SDA_EN		GPIO_pinEnable( hGpio , ZLG7290_SDA )
#define ZLG7290_SCL_EN		GPIO_pinEnable( hGpio , ZLG7290_SCL )

#define ZLG7290_SCL_OUT		GPIO_pinDirection( hGpio , ZLG7290_SCL , GPIO_OUTPUT )
#define ZLG7290_SDA_IN		GPIO_pinDirection( hGpio , ZLG7290_SDA , GPIO_INPUT )
#define ZLG7290_SDA_OUT		GPIO_pinDirection( hGpio , ZLG7290_SDA , GPIO_OUTPUT )

#define	ZLG7290_SDA_1		GPIO_pinWrite( hGpio , ZLG7290_SDA , 1 )
#define	ZLG7290_SDA_0		GPIO_pinWrite( hGpio , ZLG7290_SDA , 0 )

#define	ZLG7290_SCL_1		GPIO_pinWrite( hGpio , ZLG7290_SCL , 1 )
#define	ZLG7290_SCL_0		GPIO_pinWrite( hGpio , ZLG7290_SCL , 0 )
//返回一个32位的值:0或1
#define	ZLG7290_SDA_VAL		GPIO_pinRead ( hGpio , ZLG7290_SDA )

//定义ZLG7290在I2C总线协议中的从机地址
#define ZLG7290_I2C_ADDR	0x38

//定义ZLG7290内部寄存器地址（子地址）
#define ZLG7290_SystemReg		0x00		//系统寄存器
#define ZLG7290_Key				0x01		//键值寄存器
#define ZLG7290_RepeatCnt		0x02		//连击次数寄存器
#define ZLG7290_FunctionKey		0x03		//功能键寄存器
#define ZLG7290_CmdBuf			0x07		//命令缓冲区起始地址
#define ZLG7290_CmdBuf0			0x07		//命令缓冲区0
#define ZLG7290_CmdBuf1			0x08		//命令缓冲区1
#define ZLG7290_FlashOnOff		0x0C		//闪烁控制寄存器
#define ZLG7290_ScanNum			0x0D		//扫描位数寄存器
#define ZLG7290_DpRam			0x10		//显示缓存起始地址
#define ZLG7290_DpRam0			0x10		//显示缓存0
#define ZLG7290_DpRam1			0x11		//显示缓存1
#define ZLG7290_DpRam2			0x12		//显示缓存2
#define ZLG7290_DpRam3			0x13		//显示缓存3
#define ZLG7290_DpRam4			0x14		//显示缓存4
#define ZLG7290_DpRam5			0x15		//显示缓存5
#define ZLG7290_DpRam6			0x16		//显示缓存6
#define ZLG7290_DpRam7			0x17		//显示缓存7
//键值定义
#define KEY_00					0X04	//0
#define KEY_01					0X01	//1
#define KEY_02					0X02	//2
#define KEY_03					0X03	//3
#define KEY_04					0X09	//4
#define KEY_05					0X0A	//5
#define KEY_06					0X0B	//6
#define KEY_07					0X11	//7
#define KEY_08					0X12	//8
#define KEY_09					0X13	//9

#define KEY_UP					0X06	//上
#define KEY_DOWN				0X14	//下
#define KEY_OK					0X0D	//确定
#define KEY_CANCEL				0X05	//取消
#define KEY_GO_BACK				0X15	//返回

//函数申明

void ZLG7290_I2C_Delay ( void ) ;
void ZLG7290_I2C_Init ( void ) ;
void ZLG7290_I2C_Start ( void ) ;
void ZLG7290_I2C_Stop ( void ) ;
void ZLG7290_I2C_Write ( uint8_t data ) ;
char ZLG7290_I2C_Read ( void ) ;
uint32_t ZLG7290_I2C_GetAck ( void ) ;
void ZLG7290_I2C_PutAck ( uint32_t ack ) ;
uint32_t ZLG7290_I2C_Gets
(
 unsigned char SlaveAddr,
 unsigned char SubAddr,
 unsigned char SubMod ,
 char *data ,
 unsigned int  Size
 ) ;
uint32_t ZLG7290_ReadReg(unsigned char RegAddr, char *dat) ;
char ZLG7290_Test_Key(void) ;









#endif 



