#ifndef  __GT23L32S4W_H__
#define  __GT23L32S4W_H__


#include "z_mytype.h"
#include "z_sys_time.h"
#include "z_cpld_cmd.h"

#define McBSP2_DRR    *((volatile uint32_t*)0x01A40000)
#define McBSP2_DXR    *((volatile uint32_t*)0x01A40004)
#define McBSP2_SPCR   *((volatile uint32_t*)0x01A40008)
#define McBSP2_RCR    *((volatile uint32_t*)0x01A4000C)
#define McBSP2_XCR    *((volatile uint32_t*)0x01A40010)
#define McBSP2_SPGR   *((volatile uint32_t*)0x01A40014)
#define McBSP2_PCR    *((volatile uint32_t*)0x01A40024)

#ifndef FRST
#define FRST          23
#endif
#ifndef GRST
#define GRST          22
#endif
#ifndef XRDY 
#define XRDY          17
#endif
#ifndef XRST
#define XRST          16
#endif
#ifndef RRDY
#define RRDY          1
#endif
#ifndef RRST
#define RRST          0
#endif




void gt23l32s4w_init(void) ;
uint8_t Mcbsp2_RW_Byte(uint8_t data) ;
void Gt23l32s4w_Get_Font(uint32_t addr, uint32_t count, uint8_t *buf) ;
void Gt23l32s4w_Test (uint8_t *buf) ;



#endif 
