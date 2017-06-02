

#include "bsp_header\z_bsp.h"



GPIO_Handle hGpio;

uint8_t		key_on = 0 ;
uint8_t		interrupt_flag ;
uint8_t		Is_CMOS_Write_End ; //CMOS初始化开始时置0，结束时置1.初始化时所有的CMOS初始化依次执行，
                                //中间最好不要插入其他初始化程序
uint8_t		Is_CMOS_Save_Image = 0 ; //需要储存图片（照相）时，置位该变量(计时器实现)

extern uint8_t gWindowType;

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
	cmos_OV7670_init() ; //可视镜头OV7670初始化

	ds1302_init() ;	
	flash_init() ;
	oLCD_Init() ;
	iLCD_Init() ;
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
/*===================外部中断4处理程序=============*/
//按键中断函数
//volatile int32_t gTimes = 0;
void External_Interrupt4 (void)
{

	key_on = 1 ;

	if (gWindowType == T9_WIN) {
		//SEM_ipost(&SEM_T9);
	} else if (gWindowType == MANAGER_SUB_WIN){
		//SEM_ipost(&SEM_SUB_MANAGER);
	} else if (gWindowType == PASSWORD_SUB_WIN0) {
	
	} else if (gWindowType == PASSWORD_SUB_WIN1) {

	} else {
		SEM_ipost(&SEM_INPUT);
	}
	

	BUZZER_TIP;
	//asm ( " NOP " ) ;

}
/*===================外部中断6处理程序=============*/
//外部中断6为共用中断：
//1、指纹头CMOS的I2C初始化中断
//2、可视镜头CMOS的I2C初始化中断
//3、可视镜头每帧结束时中断
//其中 1和2 在中断里的处理部分只需在系统初始化时进行，初始化完后就完全把中断交给3。
//CMOS在初始化之前要把Is_CMOS_Write_End置0，初始化完要不Is_CMOS_Write_End置1。
void External_Interrupt6 (void)
{
	
	uint32_t i ;
	interrupt_flag = 1 ; //CMOS的I2C初始化中断标志
//以下为实时显示部分和照相功能控制
	if ( Is_CMOS_Write_End & ( !Is_CMOS_Save_Image ) ){
		LCD_SET ; //准备往LCD写数据 设置液晶光标 为实时显示做准备  
		    
		iLCD_WriteReg(0x0050,0x00);//水平 GRAM起始位置
	    iLCD_WriteReg(0x0051,239);//水平GRAM终止位置
	    iLCD_WriteReg(0x0052,0x00);//垂直GRAM起始位置
	    iLCD_WriteReg(0x0053,319);//垂直GRAM终止位置 
		iLCD_SetCursor( 0 ,0 ) ;
	    iLCD_WriteStart() ;//
		LCD_RT_DISPLAY ; //开始实时显示
	}
	if ( Is_CMOS_Save_Image ) { //照相
		LCD_SAVE_IMAGE ;		
		_delay_us(1) ; //延时，等待CPLD准备好
		for ( i=0 ; i<320*240 ; i++ ) {	//读取数据
//			*( uint8_t * ) ( 0x80000000 + i ) = AL422B_DATA ;
//			*( uint8_t * ) ( 0x80100000 ) = AL422B_DATA ;
		}
		
		Is_CMOS_Save_Image = 0 ;

 		LCD_SAVE_TO_RT ;
		LCD_RT_DISPLAY ; //开始实时显示
	}
//以上为实时显示部分和照相功能控制
}
/*===========GPIO初始化===============*/
//ZLG7290_SDA-->GP10	（初始化输出）
//ZLG7290_SCL-->GP11	（输出）
//ZLG7290_INT-->GP4     （中断输入，下降沿有效）
//CPLD进行指纹头I2C初始化时中断输出-->GP6		（输入，上升沿有效）
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
