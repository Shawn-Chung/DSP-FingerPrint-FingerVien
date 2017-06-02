
#ifndef __I2C_MASTER_H__
#define __I2C_MASTER_H__

#include "z_cpld_cmd.h"
#include "z_mytype.h"
#include "z_sys_time.h"
#include "z_glb_variable.h"

#define CHANGE_REG_NUM 167

void write_cmos_sensor(uint16_t, uint16_t) ;
void cmos_CF400G_init(void) ;
void cmos_D0307_init(void) ;


#endif
