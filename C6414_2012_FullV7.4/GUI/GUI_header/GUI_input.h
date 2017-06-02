/******************************************************************************
 * 文件名：image.h
 * 功能：  实现了指纹图像的基本操作
******************************************************************************/

#if !defined __GUI_INPUT_H
#define __GUI_INPUT_H

#include "GUI.h"
#include "GUI_text.h"
#include "t9_input.h"

#ifdef __cplusplus
extern "C" {
#endif




static void t9_do_input(uint32_t active_id);
static void t9_update(void*ptr);
static void t9_init(void*ptr);
static void t9_do_exit(void);













#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* __IMAGE_H */



