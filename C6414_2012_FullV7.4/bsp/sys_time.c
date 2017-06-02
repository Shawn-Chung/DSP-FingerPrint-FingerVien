
#include "bsp_header\z_sys_time.h"
//#include "sys_time.h"
//#include "myctype.h"

/***********************************************************************
原地延时，当要延时小于1ms时，用_delay_us，当要延时大于1ms时调用_delay_ms
延时函数没有移植性，当CPU不是720MHz要修改，下面两个函数用示波器测试过基本
准确。要更精确的延时要自己定制。
***********************************************************************/
void _delay_ms(int32_t t)
{
   int32_t tt;
   for(;t>0;t--)
   {
     for(tt=90000;tt>0;tt--)
     {
     }
   }
}

void _delay_us(int32_t t)
{
   int32_t tt;
   for(;t>0;t--)
   {
     for(tt=85;tt>0;tt--)
     {
     }
   }
}

uint32_t get_systicks(void)
{
  return 0;
}

uint32_t get_systime_ms(void)
{
  return 0;
}

bool_t get_local_time(sys_time*time)
{
  return _true;
}

bool_t get_local_time_ascii(sys_time*time)
{
  return _true;
}





