

#include "bsp_header\z_bsp.h"

GPIO_Handle hGpio;


/**********************************************************
*初始化板上支持库的所有芯片（除了液晶）
***********************************************************/
void bsp(void)
{
	CSL_init();     //初始化外设
	CSL_cfgInit() ; //外设配置
	gpio_init() ;  //GPIO初始化
	interrupt_init (); //中断初始化
	
	idt72v36110_init() ; //FIFO初始化，全局复位
	cmos_CF400G_init() ; //指纹头CF400G初始化
//	cmos_D0307_init() ;  //指纹头D0307 初始化
	//cmos_OV7670_init() ; //可视镜头OV7670初始化

	//ds1302_init() ;	
	flash_init() ;
	oLCD_Init() ;
	//iLCD_Init() ;
	ZLG7290_I2C_Init () ;
	gt23l32s4w_init() ;
	

}
/*===================中断初始化=============*/
//外部中断6		-->		指纹头I2C初始化
//外部中断4		-->		按键中断
void interrupt_init (void)
{
	IRQ_globalEnable();

	IRQ_clear(IRQ_EVT_EXTINT6);	//清除中断标志
	IRQ_clear(IRQ_EVT_EXTINT4);	
	IRQ_enable(IRQ_EVT_EXTINT6);//使能中断
	IRQ_enable(IRQ_EVT_EXTINT4);
}
/*===========GPIO初始化===============*/
//ZLG7290_SDA-->GP10	（初始化输出）
//ZLG7290_SCL-->GP11	（输出）
//ZLG7290_INT-->GP4     （中断输入）
//CPLD进行指纹头I2C初始化时中断输出-->GP6		（输入）
//DS1302_CLK-->GP9		（初始化输出）
//DS1302_IO -->GP0		（初始化输出）
//DS1302_RST-->GP3		（初始化输出）
void gpio_init(void)
{
	hGpio=GPIO_open(GPIO_DEV0,GPIO_OPEN_RESET);
	GPIO_configArgs(
		hGpio,//GPIO_Handle hGpio,
		0x00000000,//Uint32 gpgc,
		0x00000E59,//Uint32 gpen,
		0x00000E09,//Uint32 gpdir,
		0x00000000,//Uint32 gpval,//输入值或输出值
		0x00000000,//Uint32 gphm,
		0x00000000,//Uint32 gplm,
		0x00000010 //Uint32 gppol //INT4下降沿触发
	);
}
