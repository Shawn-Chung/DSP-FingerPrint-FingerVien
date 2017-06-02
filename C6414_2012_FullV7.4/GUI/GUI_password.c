
#include "GUI_header/GUI_password.h"


#define BEGIN_X		1
#define BEGIN_Y		240-60-10

static t9_input_t input;
static rect_t     rect;
static rect_t	  input_rect = {
	120,		60,
	319,		100
};

//显示输入的数组的拼音组合
static rect_t     input_num_rect={
	BEGIN_X+24,		BEGIN_Y+20,
	BEGIN_X+24+48,	BEGIN_Y+40
};

//显示可供选择的字
static rect_t	  input_buf_rect={
	BEGIN_X+24,		BEGIN_Y+40,
	BEGIN_X+24+48,	BEGIN_Y+60
};

//显示输入法模式:中,英
static rect_t     input_mode_rect ={
	BEGIN_X,		BEGIN_Y+20,
	BEGIN_X+16,		BEGIN_Y+40	
};

static unsigned char get_key_num (char KeyValue) 
{
	unsigned char key_num;
	switch (KeyValue) {
	case KEY00:
		key_num = macro_t9_key_0;
		//if (gSelect == 0) {
		//	key_num = macro_t9_key_0;
		//} else if (gSelect == 1) { 
		//	key_num = macro_t9_key_pinyin0;
		//} else if (gSelect == 2) {
		//	key_num = macro_t9_key_word0;
		//	gSelect = 0;
		//}
		break;
	case KEY01:
		//key_num = macro_t9_key_1;
//		if (gSelect == 0) {
			key_num = macro_t9_key_1;
// 		} else if (gSelect == 1) { 
// 			key_num = macro_t9_key_pinyin0;
// 		} else if (gSelect == 2) {
// 			key_num = macro_t9_key_word0;
// 			gSelect = 0;
// 		}
		break;
	case KEY02:
		//key_num = macro_t9_key_2;
//		if (gSelect == 0) {
			key_num = macro_t9_key_2;
// 		} else if (gSelect == 1) {
// 			key_num = macro_t9_key_pinyin1;
// 		} else if (gSelect == 2) {
// 			key_num = macro_t9_key_word1;
// 			gSelect = 0;
// 		}
		break;
	case KEY03:
		//key_num = macro_t9_key_3;
//		if (gSelect == 0) {
			key_num = macro_t9_key_3;
		//} else if (gSelect == 1) {
		//	key_num = macro_t9_key_pinyin2;
		//} else if (gSelect == 2) {
		//	key_num = macro_t9_key_word2;
		//	gSelect = 0;
		//}
		break;
	case KEY05:
		//key_num = macro_t9_key_4;
//		if (gSelect == 0) {
			key_num = macro_t9_key_4;
		//} else if (gSelect == 1) { 
		//	key_num = macro_t9_key_pinyin3;
		//} else if (gSelect == 2) {
		//	key_num = macro_t9_key_word3;
		//	gSelect = 0;
		//}
		break;
	case KEY06:
		//key_num = macro_t9_key_5;
		//if (gSelect == 0) {
			key_num = macro_t9_key_5;
		//} else if (gSelect == 1) {
		//	key_num = macro_t9_key_pinyin4;
		//} else if (gSelect == 2) {
		//	key_num = macro_t9_key_word4;
		//	gSelect = 0;
		//}
		break;
	case KEY07:
		//key_num = macro_t9_key_6;
//		if (gSelect == 0) {
			key_num = macro_t9_key_6;
// 		} else if (gSelect == 1) {
// 			key_num = macro_t9_key_pinyin5;
// 		} else if (gSelect == 2) {
// 			key_num = macro_t9_key_word5;
// 			gSelect = 0;
// 		}
		break;
	case KEY09:
		key_num = macro_t9_key_7;
		break;
	case KEY10:
		key_num = macro_t9_key_8;
		break;
	case KEY11:
		key_num = macro_t9_key_9;
		break;
	case KEYCC:
		key_num = macro_t9_key_backspace;
		break;
	case KEYGB:
		key_num = macro_t9_key_space;
		//key_num = macro_t9_key_switch;
		break;
	case KEYUP:
		key_num = macro_t9_key_space;
		//key_num = macro_t9_key_show_back;
		break;
	case KEYDN:
		key_num = macro_t9_key_space;
		//key_num = macro_t9_key_show_forward;
		break;
	case KEYOK:
		key_num = macro_t9_key_enter;
		//gSelect++;
		//if (gSelect >= 3) {
		//	gSelect = 0;
		//}
		break;
	case KEY13:
		key_num = macro_t9_key_exit;
		break;
	default :
		key_num = macro_t9_key_space;
		break;
	}
	return key_num;
}

void password_init(void*ptr)
{
	t9_initialize(&input,t9_py_index);
	input.input_mode=macro_t9_mode_num;
	//gSelect = 0;
	//t9_update(PL_NULL);
}



static font_t oldfont;
static font_t newfont;
static void password_update(void*ptr)
{
	uint32_t i;
	//font_t oldfont;
	//font_t newfont;
	//pen_t  oldPen;
	//pen_t newPen;
	rect_t temp_rect;
	char buf[4]={0,0,0,0};
	char input_buf1[10] = {0,0,0,0,0,0,0,0,0,0};


	ptr=ptr;//防止编译器提示警告

	rect.x0=0;
	rect.y0=0;
	rect.x1=319;
	rect.y1=239;


	//gui_get_font(&oldfont);
	//gui_get_pen(&oldPen);
	newfont.type=macro_font_style_huge;
	gui_set_font(&newfont);
	//gui_set_pen(&newPen);

	//gui_window_update(handle,&rect);

	rect.x0=5;
	rect.x1=319;
	rect.y1=46;

	gui_fill_rect_buf(&input_rect, WHITE);
	//gui_draw_h_line(input_rect.x0, input_rect.y0, input_rect.x1, BLUE);

	rect.x0 = input_mode_rect.x0;
	rect.y0 = input_mode_rect.y0;
	rect.y1 = input_mode_rect.y1;
	gui_fill_rect_buf(&rect, WHITE);

	//gui_draw_h_line(rect.x0, rect.y0, rect.x1, BLUE);

	rect.x0 = input_mode_rect.x0;
	rect.y0 = input_mode_rect.y0 + 20;
	rect.y1 = input_mode_rect.y1 + 20;
	gui_fill_rect_buf(&rect, WHITE);
	//gui_draw_h_line(rect.x0, rect.y0, rect.x1, BLUE);
	//gui_draw_h_line(rect.x0, rect.y1, rect.x1, BLUE);

	//gui_draw_v_line(BEGIN_X-1, BEGIN_Y, BEGIN_Y+60, BLUE);
	//gui_draw_v_line(319, BEGIN_Y, BEGIN_Y+60, BLUE);

	//temp_rect.x0 = 120;
	//temp_rect.y0 = 60;
	//temp_rect.x1 = 319;
	//temp_rect.y1 = 100;
	for (i = 0; i < input.count; i++) {
		input_buf1[i] = '*';
	}
	//gui_text_out_rect(input.buf,&input_rect,macro_text_v_align_center|
	//	macro_text_h_align_left);
	gui_text_out_rect(input_buf1,&input_rect,macro_text_v_align_center|
			macro_text_h_align_left);


	//将字体恢复，防止系统出错.
	gui_set_font(&oldfont);
	//gui_update_rect(0,0,399,239);
	oLCD_Update_Rect_Screen(0, 0, 240, 320);
}

static void password_do_input(uint32_t active_id)
{
	//switch(input.input_mode)
	//{
	//case macro_t9_mode_cn:
	//	if(t9_cn_keyhandler(&input,active_id)==_true)
	//	{
	//		t9_cn_searchhandler(&input);
	//	}
	//	break;
	//case macro_t9_mode_len:
	//case macro_t9_mode_uen:
	//case macro_t9_mode_num:
		t9_en_keyhandler(&input,active_id);
	//	break;
	//default:break;
	//}
}

void PassWordTask(void) 
{
	char KeyValue;
	
	uint32_t i;
	uint32_t active_id;
	rect_t pw_rect, pw_rect1;
	pw_rect.x0 = 0;
	pw_rect.y0 = 13;
	pw_rect.x1 = 319;
	pw_rect.y1 = 51;
	pw_rect1.x0 = 60;
	pw_rect1.y0 = 60;
	pw_rect1.x1 = 319;
	pw_rect1.y1 = 100;
	while (1) {
		SEM_pend(&SEM_PASSWORD,  SYS_FOREVER);

		oLCD_Fill_Full_Buf(WHITE);
		key_on = 0;
		IRQ_clear(IRQ_EVT_EXTINT4);//清除中断标志
		IRQ_enable(IRQ_EVT_EXTINT4);//使能中断

		gui_get_font(&oldfont);
		newfont.type=macro_font_style_big;
		gui_set_font(&newfont);
		password_init(PL_NULL);
		gui_text_out_rect("请输入密码^_^", &pw_rect, macro_text_h_align_center|macro_text_v_align_center);
		while (1) {
			if (key_on == 1) {
				key_on = 0;
				IRQ_disable(IRQ_EVT_EXTINT4);//禁止中断	
				ZLG7290_ReadReg(ZLG7290_Key,&KeyValue);//读取键值
				active_id = (uint32_t)get_key_num(KeyValue);
				if (input.count < 6) {
					password_do_input(active_id);
					password_update(PL_NULL);
				}
				
				if (active_id == macro_t9_key_exit) {
					//if (pl_strlen(input.buf) != 0) {
						gWindowType = MAIN_WIN;
						gui_set_font(&oldfont);
						break;
					//}
				}
				if (active_id == macro_t9_key_enter) {
					if (input.count == 6) {
						for(i=0;i<input.count;i++)
						{
							if (input.buf[i] != '1') {
								//gCorrect = 0;
								gWindowType = MAIN_WIN;
								break;
							} 
						}
						if (i == 6) {
							gWindowType = MANAGER_WIN;
							gui_set_font(&oldfont);
						}
					} else {
						gWindowType = MAIN_WIN;
						gui_set_font(&oldfont);
					}
					break;
				}

				IRQ_clear(IRQ_EVT_EXTINT4);//清除中断标志
				IRQ_enable(IRQ_EVT_EXTINT4);//使能中断
		}
		oLCD_Update_Rect_Screen(0, 0, 240, 320);
		}

	}
}

