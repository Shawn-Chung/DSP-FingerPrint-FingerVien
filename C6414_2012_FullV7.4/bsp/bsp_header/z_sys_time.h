#ifndef SYS_TIME_H_H______
#define SYS_TIME_H_H______
#include "z_mytype.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
	union{
		uint32_t year;
		char     a_year[4];
	}yy;
	union{
		uint32_t mon ;
		char     a_mon[4];
	}mo;
	union{
		uint32_t day;
		char     a_day[4];
	}dd;
	union{
		uint32_t hour;
		char     a_hour[4];
	}hh;
	union{
		uint32_t week;
		char     a_week;
	}ww;
	union{
		uint32_t min ;
		char     a_min[4];
	}mm;
	union{
		uint32_t sec ;
		char     a_sec;
	}ss;
	union{
		uint32_t msec;
		char     a_msec[4];
	}ms;
}sys_time;


//下面的函数在720MHz下是比较精确的延时函数。
extern void _delay_ms(int32_t t);
extern void _delay_us(int32_t t);

//下面的是获取系统时间的函数

/*****************************************
*获取系统运行了多少个时钟节拍。
*****************************************/
uint32_t get_systicks(void);

/*****************************************
*以ms为单位返回系统运行了多少个毫秒
******************************************/
uint32_t get_systime_ms(void);

/******************************************************
*函数名称：bool_t get_local_time(sys_time*time)
*输入参数：sys_time*time 指向一个系统时间的数据结构
*返回参数：bool_t 当返回为 _false时表明系统没有实时时钟
*          当返回为_true时，表明系统有实时时钟

*说明：    获取系统当前的本地时间，由系统的实时时钟提供
*          当系统不存在系统时钟时，由系统节拍器提供一个
*          相对时间。
*******************************************************/
bool_t get_local_time(sys_time*time);

/******************************************************
*用于获取当前系统时间，但是该时间是ascii码形式的。
*******************************************************/
bool_t get_local_time_ascii(sys_time*time);

#ifdef __cplusplus
}
#endif /* extern "C" */
#endif

