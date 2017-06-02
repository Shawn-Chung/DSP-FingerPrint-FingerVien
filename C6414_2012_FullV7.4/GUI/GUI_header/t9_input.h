
#ifndef __T9_INPUT_H_
#define __T9_INPUT_H_

/* 基本类型定义 */
#include "../../bsp/bsp_header/z_mytype.h"

#ifdef __cplusplus
extern "C" {
#endif


/*"拼音输入法汉字排列表"*/
//码表数据结构
typedef struct 
{
    char  *t9PY_T9;
    char  *PY     ;
    char  *PY_mb  ;
//	int   word_count;
}t9PY_index;

//输入法数据结构
typedef struct{   
  short  input_mode      ;  //输入法模式
  
  t9PY_index*index       ;  //索引表,的起始位置

  t9PY_index*mb_index[6] ;  //指针数组，其元素指向当前搜索到的6个拼音在索引表的位置

  short  pinyin_buf[6]   ;  //当前已经输入的拼音缓存
  short  pinyin_count    ;  //拼音输入的数量 

  short  pinyin_selected ;  //当前选中的拼音的位置

  short  show_offset     ;  //当前在显示的汉字首字符在汉字码表中的相对字节位置(第几个从0开始索引) ;  
  char  show_buf[14]     ;  //显示缓存一次显示6个汉字,或者最多12个ascii码                    ;

   char  buf[32]        ;  //输入缓存最多一次输入16个汉字,或者32个ascii码
  short  count          ;  //当前已经输入的汉字所占的字节数，考虑到中英混合输入的情况  

}t9_input_t;


//t9拼音输入法的原始宏定义。
#define macro_t9_key_0                0u         
#define macro_t9_key_1                1u
#define macro_t9_key_2                2u
#define macro_t9_key_3                3u
#define macro_t9_key_4                4u
#define macro_t9_key_5                5u
#define macro_t9_key_6                6u
#define macro_t9_key_7                7u
#define macro_t9_key_8                8u
#define macro_t9_key_9                9u
#define macro_t9_key_space            10u
#define macro_t9_key_backspace        11u
#define macro_t9_key_enter            12u
#define macro_t9_key_exit             13u
#define macro_t9_key_switch           14u
#define macro_t9_key_pinyin0          15u
#define macro_t9_key_pinyin1          16u
#define macro_t9_key_pinyin2          17u
#define macro_t9_key_pinyin3          18u
#define macro_t9_key_pinyin4          19u
#define macro_t9_key_pinyin5          20u
#define macro_t9_key_show_forward     21u
#define macro_t9_key_show_back        22u
#define macro_t9_key_word0            23u
#define macro_t9_key_word1            24u
#define macro_t9_key_word2            25u
#define macro_t9_key_word3            26u
#define macro_t9_key_word4            27u
#define macro_t9_key_word5            28u

//一些转义的宏定义
#define macro_t9_key_abc     macro_t9_key_2
#define macro_t9_key_def     macro_t9_key_3
#define macro_t9_key_ghi     macro_t9_key_4
#define macro_t9_key_jkl     macro_t9_key_5
#define macro_t9_key_mno     macro_t9_key_6
#define macro_t9_key_pqrs    macro_t9_key_7
#define macro_t9_key_tuv     macro_t9_key_8
#define macro_t9_key_wxyz    macro_t9_key_9

//t9输入模式,en为英文cn为中文num为数字
/*
从上往下分别是
1.中文
2.小写字母
3.大写字母
4.数字
*/

#define macro_t9_mode_cn     0u
#define macro_t9_mode_len    1u
#define macro_t9_mode_uen    2u
#define macro_t9_mode_num    3u


//选中的拼音宏定义
#define macro_t9_pyselected0  0
#define macro_t9_pyselected1  1
#define macro_t9_pyselected2  2
#define macro_t9_pyselected3  3
#define macro_t9_pyselected4  4
#define macro_t9_pyselected5  5

//输入最大的字符个数
#define macro_t9_max_input_count  32


//外部变量的声明
extern t9PY_index t9_py_index[];

//函数定义:
bool_t t9_en_keyhandler (t9_input_t*input,short key_id);  //英文字母及数字的输入处理
bool_t t9_cn_keyhandler   (t9_input_t*input,short key_id);//按键处理,中文要在输入后进行搜索处理
bool_t t9_cn_searchhandler(t9_input_t*input);//搜索服务
void   t9_cn_showhandler  (t9_input_t*input);//显示服务
void   t9_cn_input        (t9_input_t*input,short key_id);//输入法，总函数
void   t9_initialize(t9_input_t*input,t9PY_index*index);    //输入初始化



#ifdef __cplusplus
}
#endif

#endif

