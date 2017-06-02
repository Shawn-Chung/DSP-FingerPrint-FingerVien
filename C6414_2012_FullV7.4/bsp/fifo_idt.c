
#include "bsp_header\z_fifo_idt.h"

/********************************************************
*函数名：idt72v36110_init
*参  数：没有
*返  回：没有
*作  用：将FIFO芯片IDT72V36110初始化，FIFO全局复位。
**********************************************************/
void idt72v36110_init(void)
{
	FIFO_MASTER_RESET_ON ;
	_delay_ms ( 100 ) ;
	FIFO_MASTER_RESET_OFF ;
}
/********************************************************
*函数名：idt72v36110_reset
*参  数：没有
*返  回：没有
*作  用：将FIFO芯片IDT72V36110复位,FIFO的局部复位
**********************************************************/
void idt72v36110_reset(void)
{
	FIFO_PARTIAL_RESET_ON ;
	_delay_ms ( 100 ) ;
	FIFO_PARTIAL_RESET_OFF ;
}
