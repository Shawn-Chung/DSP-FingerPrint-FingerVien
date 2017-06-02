#include "bsp_header\z_zlg7290.h"

extern uint8_t		key_on ;

void ZLG7290_I2C_Delay ( void )
{
//	_delay_ms(10) ;
	_delay_us(30) ;
}
void ZLG7290_I2C_Init ( void )
{	
//	KEY_RESET_ON ;
//	_delay_ms(20);
//	KEY_RESET_OFF;
//	_delay_ms(200);

	ZLG7290_SDA_EN ;
	ZLG7290_SCL_EN ;
	ZLG7290_SCL_OUT ;
	ZLG7290_SDA_OUT ;

	ZLG7290_SDA_1 ;
	ZLG7290_I2C_Delay() ;
	ZLG7290_SDA_1 ;
	ZLG7290_I2C_Delay() ;
}
//SDA	-----\________
//SCL	---------\____
void ZLG7290_I2C_Start ( void )
{
	ZLG7290_SDA_1 ;
	ZLG7290_I2C_Delay() ;
	ZLG7290_SCL_1 ;
	ZLG7290_I2C_Delay() ;
	ZLG7290_SDA_0 ;
	ZLG7290_I2C_Delay() ;
	ZLG7290_SCL_0 ;
	ZLG7290_I2C_Delay() ;
}
//SDA	____/---------
//SCL	/-------------
void ZLG7290_I2C_Stop ( void )
{
	ZLG7290_SDA_0 ;
	ZLG7290_I2C_Delay() ;
	ZLG7290_SCL_1 ;
	ZLG7290_I2C_Delay() ;
	ZLG7290_SDA_1 ;
	ZLG7290_I2C_Delay() ;
	_delay_ms(100) ;    //在下一次产生START之前一定要加一定的延时
}
void ZLG7290_I2C_Write ( uint8_t data )
{
	uint8_t   t = 8 ; 
	do
	{
		if ( data & 0x80 )
			ZLG7290_SDA_1 ;
		else ZLG7290_SDA_0 ;
		data <<= 1 ;
		ZLG7290_SCL_1 ;
		ZLG7290_I2C_Delay() ;
		ZLG7290_SCL_0 ;
		ZLG7290_I2C_Delay() ;
	}while ( --t != 0 ) ;
}
char ZLG7290_I2C_Read ( void )
{
	char dat  ;
	unsigned char t = 8 ;

	ZLG7290_SDA_1 ;//在读取数据之前，要把SDA 拉高 
	ZLG7290_I2C_Delay() ;
	ZLG7290_SDA_IN ;//数据线设置为输入
	do
	{
		ZLG7290_SCL_1 ;
		ZLG7290_I2C_Delay () ;
		dat <<= 1 ;
		if ( ZLG7290_SDA_VAL ) dat |= 0x01;
		ZLG7290_SCL_0 ;
		ZLG7290_I2C_Delay () ;
	} while ( --t != 0 );
	ZLG7290_SDA_OUT ;//数据线设置为输出
	return dat ;
}
uint32_t ZLG7290_I2C_GetAck ( void )
{
	uint32_t ack ;
	ZLG7290_SDA_1 ;	
	ZLG7290_I2C_Delay() ;
	ZLG7290_SCL_1 ;
	ZLG7290_I2C_Delay() ;
	ZLG7290_SDA_IN ;//数据线设置为输入
	ack = ZLG7290_SDA_VAL ;
	ZLG7290_SCL_0 ;
	ZLG7290_I2C_Delay () ;
	ZLG7290_SDA_OUT ;//数据线设置为输出
	return ack; 
}
/****************************************************************************
* 名    称：ZLG7290_I2C_PutAck ( uint32_t ack )
* 功    能：主机产生应答位或非应答位
* 入口参数：ACK	0时，主机产生应答位；1时，主机产生非应答位
* 出口参数：无
* 说    明：主机在接收完每一个字节的数据后，都应当产生应答位 
*           主机在接收完最后一个字节的数据后，应当产生非应答位 
* 调用方法：ZLG7290_I2C_PutAck ( 1 ) ;
****************************************************************************/
void ZLG7290_I2C_PutAck ( uint32_t ack )
{
	if ( ack )  
		ZLG7290_SDA_1 ;
	else
		ZLG7290_SDA_0 ;
	ZLG7290_I2C_Delay () ;
	ZLG7290_SCL_1 ;
	ZLG7290_I2C_Delay () ;
	ZLG7290_SCL_0 ;
	ZLG7290_I2C_Delay () ;
}
/****************************************************************************
* 名    称：ZLG7290_I2C_Gets
* 功    能：I2C总线综合接收函数，从从机接收1个字节的数据
* 入口参数：SlaveAddr：从机地址（7位纯地址，不含读写位）
*		    SubAddr： 从机的子地址
*          *dat：     保存接收到的数据
* 出口参数：0：	接收成功
*			1：在接收过程中出现异常
* 说    明：主机在接收完每一个字节的数据后，都应当产生应答位 
*           主机在接收完最后一个字节的数据后，应当产生非应答位 
* 调用方法：
****************************************************************************/
uint32_t ZLG7290_I2C_Gets
(
	unsigned char SlaveAddr,
	unsigned char SubAddr,
	unsigned char SubMod ,
	char *data ,
	unsigned int  Size
)
{
	unsigned char i ;
	char a[3] ;
	//检查长度
	if ( Size == 0 ) return 0 ;
	//准备从机地址
	a[0] = ( SlaveAddr << 1 ) ;
	//检查子地址模式
	if ( SubMod > 2 ) SubMod = 2 ;
	//如果有子地址的从机，则要先发送从机地址和子地址
	if (SubMod != 0)
	{
		//确定子地址
		if (SubMod==1)
		{
			a[1] = (char)(SubAddr);
		}
		else
		{
			a[1] = (char)(SubAddr >> 8);
			a[2] = (char)(SubAddr) ;
		}
		//发送从机地址，接着发送子地址
		SubMod ++ ;
		ZLG7290_I2C_Start() ;
		for (i=0;i<SubMod;i++)
		{
			ZLG7290_I2C_Write(a[i]) ;
			if (ZLG7290_I2C_GetAck())
			{
				ZLG7290_I2C_Stop() ;
				return 1 ;
			}
		}
	}
	ZLG7290_I2C_Start();
	//发送从机地址
	ZLG7290_I2C_Write(a[0]+1) ;
	if (ZLG7290_I2C_GetAck())
	{
		ZLG7290_I2C_Stop() ;
		return 1 ;
	}
	//接收数据
	for (;;)
	{
		*data++ = ZLG7290_I2C_Read() ;
		if (--Size == 0)
		{
			ZLG7290_I2C_PutAck(1) ;
			break ;
		}
		ZLG7290_I2C_PutAck(0) ;
	}
	ZLG7290_I2C_Stop() ;
	return 0 ;
}
/****************************************************************************
* 名    称：ZLG7290_ReadReg(unsigned char RegAddr, uint32_t *dat)
* 功    能：读寄存器
* 入口参数：RegAddr：ZLG7290的内部寄存器地址
*       	*dat：保存读出的数据
* 出口参数：0：正常
*	    	1：访问ZLG7290时出现异常
* 说    明：
* 调用方法：
****************************************************************************/
uint32_t ZLG7290_ReadReg(unsigned char RegAddr, char *dat)
{
	uint32_t b;//
	b = ZLG7290_I2C_Gets(ZLG7290_I2C_ADDR,RegAddr,1,dat,1);
	return b;
}
/****************************************************************************
* 名    称：ZLG7290_Test_Key(void)
* 功    能：按键测试
* 入口参数：
* 出口参数：键值
* 说    明：调试用
* 调用方法：ZLG7290_Test_Key() ;
****************************************************************************/
char ZLG7290_Test_Key(void)
{
	char KeyValue;
	if ( key_on )		//如果有键按下
	{
		key_on = 0 ; //清除按键标识		
		 
		if ( !ZLG7290_ReadReg(ZLG7290_Key,&KeyValue) )//读取键值
		{
			key_on = 0 ; //清除按键标识	
			asm ( " NOP " ) ;
			return KeyValue ;
		}
		else
			return -1 ;
		
	}
	else
		return -1 ;
}
























