/******************************************************************************
 * 文件名：sys_gobal.h
 * 功能：  一些系统的全局变量和操作
******************************************************************************/

#if !defined __SYS_USER_H
#define __SYS_USER_H


/* 基本类型定义 */
#include "../../bsp/bsp_header/z_mytype.h"
#include "../../dip/dip_header/dip_header.h"
#include "../../dip/dip_header/image_feature.h"




#ifdef __cplusplus
extern "C" {
#endif



/*
数据库规则说明：
*所有的读操作都在SDRAM中完成，上电时系统会加载一份数据到SDRAM，并将其组织成循环链表。
*所有写操作都遵循先在SDRAM中修改，然后再更新到FLASH的原则。
*写如数据库的一般流程：
*1.准备好一个单元的数据大小4KB
*2.在SDRAM中添加一个单元。
*3.擦除FLASH上的一个单元。
*4.将这个单元的数据写入FLASH中。
*/

//属性
#define macro_db_administrator 0
#define macro_db_normal_user   1


//权限宏定义读权限，写权限，所有权限、私有权限
#define macro_db_limits_all    0
//root用户
#define macro_db_limits_read   1
#define macro_db_limits_write  2
//管理员
#define macro_db_limits_self   4
//用户，只能看到自己的信息

//性别属性宏定义
#define macro_db_men            0
#define macro_db_women          1


typedef struct t_user_t{

struct t_user_t *next ; //指向后面一个用户的指针
struct t_user_t *pre  ; //指向前面一个用户的指针
uint32_t  id          ; //内部ID,当id为0xffffffff时表明为无效用户
uint32_t  attribute   ; //属性,管理员普通用户等等
uint32_t  limits      ; //权限,该用户拥有的权限
//time_t    reg_time    ; //注册时间
char      name[16]    ; //名称
uint32_t  sexuality   ; //性别
//feature_t feature   ; //识别用的特征  //jjdeng
FPMinutiaSet_t fp_minutia;
uint8_t   imgbuf[4500];  //特征图像     //pl
//uint8_t   rsvd[1]     ; //保留区用来凑齐4kB对齐的数据
}user_t;



typedef struct{

uint32_t user_cnt;           //普通用户数量
uint32_t admin_cnt;          //管理员的数量
uint32_t all_cnt;            //总用户数
user_t*  list_head;          //指向用户列表的开头的数据结构,这个变量只是指向动态变量。
user_t*  list_current;      //列表当前的用户
user_t*  list_tail;          //用户列表尾部

/*下面是和数据结构特征相关的成员*/
uint32_t start_addr;      //数据库的起始地址
uint32_t size      ;      //数据库的大小,字节为单位
uint32_t unit_size ;      //数据库的每单元单元大小，字节为单位
uint32_t dynamic_start_addr; //动态数据库的起始地址
uint32_t id_map[8];      //ID号的位图
//uint32_t id_map[16];      //ID号的位图

}database_t;



bool_t sys_user_register   (user_t*user);
bool_t sys_user_unregister (user_t*user);
//bool_t sys_user_login      (user_t*user);
//bool_t sys_user_find       (user_t*user);
//bool_t sys_user_add        (user_t*user);
//bool_t sys_user_delete     (user_t*user);
bool_t sys_is_normal_user  (user_t*user);
bool_t sys_is_administrator(user_t*user);
//bool_t sys_user_change_mod (user_t*user);
//char*  sys_user_get_name   (user_t*user);
//uint32_t sys_user_get_id   (user_t*user);


/*数据库底层函数，有api调用，用户不会接触到这一层。*/
void    sys_db_write_unit(uint32_t id,void*buf);
database_t*sys_get_database      (void       );
void     sys_database_init       (void       );
bool_t   sys_database_add        (user_t*user);
bool_t   sys_database_delete     (user_t*user);
user_t*  sys_database_get_next   (void       );
user_t*  sys_database_get_pre    (void       );
user_t*  sys_database_get_head   (void       );
user_t*  sys_database_get_tail   (void       );
void     sys_database_go_to_head (void       );
void     sys_database_go_to_tail (void       );
uint32_t sys_database_malloc_id  (void       );//分配一个id号
void     sys_database_free_id    (uint32_t id);
user_t*  sys_database_malloc_user(uint32_t id);//获取存放的用户数据结构的内存
//bool_t  sys_database_change_mod(user*_t  );



void sys_database_init0(void);



#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* __SYS_GLOBAL_H */
















