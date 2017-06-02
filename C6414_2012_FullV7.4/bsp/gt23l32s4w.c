

#include "bsp_header\z_gt23l32s4w.h"

//char PY_mb_o     []  = {"哦"}; //测试字符

/*****************************************************************
*函数名：GT23L32S4W_init
*参  数：没有
*返  回：没有
*说  明：初始化GT23L32S4W硬件工作环境。
*        控制GT23L32S4W芯片的McBSP的初始化
*****************************************************************/
void gt23l32s4w_init(void)
{
	/*McBSP初始化*/

	McBSP2_SPCR =  0x01001000;//bit24 bit12
	McBSP2_RCR  =  0x00040000;//bit18
	McBSP2_XCR  =  0x00040000;//bit18
	McBSP2_SPGR =  0x20000063;
	McBSP2_PCR  =  0x00000F03;
	
    McBSP2_SPCR |= ((1<<FRST) | (1<<GRST));
	_delay_us(1);
	McBSP2_SPCR |= ((1<<RRST) | (1<<XRST));
	_delay_us(1);

    /*GT23L32S4W片选相连的GPIO对应管脚置高*/
	GT23L32S4W_CS_OFF ;
}

/*****************************************************************
*函数名：mcbsp2_rw_byte
*参  数：data
*返  回：data
*说  明：
*****************************************************************/
uint8_t Mcbsp2_RW_Byte(uint8_t data)
{
	uint32_t spcr = 0;
    
	McBSP2_DXR = data;
	while ((spcr&0x00000002) != 0x00000002) // check if the Receiver is ready ?
	{
		spcr = McBSP2_SPCR;   
	}
	data = McBSP2_DRR;

	return data;
}
/*******************************************************************
*函数名：gt23l32s4w_get_font
*参  数：uint32_t addr  :读取数据的起始地址，这个地址必须为有效地址。
*        uint32_t count :读取数据的数量，字节为单位。这个数必须大于0
*        uint8_t  *buf  :指向存放读取的数据的缓冲区指针。这个指针必须
*                        指向一个有效的且容量足够大的缓冲区。
*返  回：没有
*说  明：从GT23L32S4W芯片的addr地址开始读取count字节的数据存放到buf
*        开的缓冲区。
*        包括两个部分：
********************************************************************/
void Gt23l32s4w_Get_Font(uint32_t addr, uint32_t count, uint8_t *buf)
{
	uint8_t  tmp;
	uint32_t i;

	/*片选置低*/
	GT23L32S4W_CS_ON; //使能字库芯片
	_delay_ms(1);
	Mcbsp2_RW_Byte(0x0B);
	tmp = (uint8_t)(addr>>16) ;

	Mcbsp2_RW_Byte(tmp);
	tmp = (uint8_t)(addr>>8) ;

	Mcbsp2_RW_Byte(tmp);
	tmp = (uint8_t)(addr) ;

	Mcbsp2_RW_Byte(tmp);

	Mcbsp2_RW_Byte(0xFF);//dummy byte

	for (i = 0; i < count; i++)
	{
		buf[i] = Mcbsp2_RW_Byte(0xff);

	}
    /*片选置高*/
    GT23L32S4W_CS_OFF;
}

//void Gt23l32s4w_Test (uint8_t *buf)
//{
//	uint32_t LSB ;
//	uint32_t MSB ;
//	uint32_t Address ;
//
//	MSB = ( uint32_t ) ( PY_mb_o[0] ) & 0x000000ff ;
//	LSB = ( uint32_t ) ( PY_mb_o[1] ) & 0x000000ff ;
//	
//	Address=0x68190;//24*24
//	if (MSB>=0xA4 && MSB<=0Xa8 && LSB>=0xA1)
//	{
//		Address = Address;
//	}else if (MSB>=0xA1 && MSB<=0Xa9 && LSB>=0xA1)
//	{
//		Address = ((MSB - 0xA1) * 94 + (LSB - 0xA1))*72 + Address;
//	}else if (MSB>=0xB0 && MSB<=0xF7 && LSB>=0xA1)
//	{
//		Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+ 846)*72 + Address;
//	}
//	Gt23l32s4w_Get_Font(Address, 72, buf);	
//
//}












