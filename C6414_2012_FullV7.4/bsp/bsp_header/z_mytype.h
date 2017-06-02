

#ifndef __MYCTYPE_H__
#define __MYCTYPE_H__


#ifdef __cplusplus
extern "C" {
#endif


typedef  char               int8_t   ;
typedef  short int          int16_t  ;
typedef  int                int32_t  ;

typedef  unsigned char      uint8_t  ;
typedef  unsigned short int uint16_t ;
typedef  unsigned int       uint32_t ;

//typedef  unsigned int       size_t   ;

typedef  int                bool_t   ;

typedef  uint8_t            byte_t   ;
typedef  uint16_t           word_t   ;
typedef  uint32_t           dword_t  ;

typedef  uint16_t           color_t  ;




#ifndef TRUE
#define FALSE               ((int32_t)0)
#define TRUE                ((int32_t)1)
#endif

#define  _true              ((int32_t)1)
#define  _false             ((int32_t)0)

#ifndef NULL
#define NULL                ((void*)0)
#endif

#define  PL_NULL            ((void*)0)



/* 指针类型 */
typedef void*			Pointer_t;
/* 句柄类型，用来操作不透明的指针 */
typedef void*			Handle_t;
/* 字符串类型 */
typedef char*			String_t;


typedef struct Point_t {
	int32_t x;
	int32_t y;
} Point_t;

/* 布尔类型 */
typedef enum Bool_t
{
	/* false标记 */
	bFalse = 0,
    /* true标记 */
	bTrue  = 1
} Bool_t;

/* 定义PI值 */
#ifndef M_PI
//#define M_PI			3.1415926535897932384626433832795
//#define M_PI				3.1415926
//#define M_EPI				57.29578		//180/M_PI
#define M_PI				3.1415926
#define M_PI_X2				6.2831852
#define M_EPI				57.29578		//180/M_PI
#define M_EPI_2				28.64789
#endif

/* 定义错误类型 */
typedef enum FunError_t
{
	/* 未定义错误 */
	FunFailure			= -1,
	/* 没有错误 */
	FunOK				= 0,
	/* 内存不足 */
	FunMemory,
	/* 参数无效 */
	FunBadParameter,
	/* 文件格式错误 */
	FunBadFormat,
	/* 输入输出错误 */
	FunIoError,
	FunError
} FunError_t;


#ifdef __cplusplus
}
#endif /* extern "C" */



#endif /* __MYCTYPE_H__ */









