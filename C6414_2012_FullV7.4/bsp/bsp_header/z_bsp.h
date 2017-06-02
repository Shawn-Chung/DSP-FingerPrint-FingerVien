#ifndef  __DSP_BSP_H__
#define  __DSP_BSP_H__

#include "..\..\C6414_2012_Fullcfg.h"
#include <csl.h>
#include <csl_irq.h>  
#include <csl_edma.h>
#include <csl_gpio.h>

#include "z_mytype.h"
#include "z_sys_time.h"
#include "z_cpld_cmd.h"
#include "z_fifo_idt.h"
#include "z_I2C_master.h"
#include "z_glb_variable.h"
#include "z_oLCD.h"
#include "z_iLCD.h"
#include "z_flash.h"
#include "z_zlg7290.h"
#include "z_ds1302.h"

#include "../../gui/gui_header/gui_header.h"

/*---------------- variable -----------------*/




/*----------------- Functions -------------------*/

void bsp(void);
void interrupt_init (void) ;
void gpio_init(void) ;


#endif /* __DSP_BSP_H__ */

