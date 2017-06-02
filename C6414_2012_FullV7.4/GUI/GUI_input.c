

#include "GUI_header/GUI_input.h"

//extern uint8_t key_on;
//extern unsigned char gImage_input11[51200];

uint8_t gSelect = 0;
static t9_input_t input;
static rect_t     rect;

#define BEGIN_X		1
#define BEGIN_Y		240-60-10
//显示已输入的汉字
static rect_t	  input_rect = {
	120,		60,
	319,		100
};
//temp_rect.x0 = 120;
//temp_rect.y0 = 60;
//temp_rect.x1 = 319;
//temp_rect.y1 = 100;

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


//static unsigned char get_key_num (char KeyValue) 
//{
//	unsigned char key_num;
//	switch (KeyValue) {
//	case KEY00:
//		key_num = macro_t9_key_0;
//		//if (gSelect == 0) {
//		//	key_num = macro_t9_key_0;
//		//} else if (gSelect == 1) { 
//		//	key_num = macro_t9_key_pinyin0;
//		//} else if (gSelect == 2) {
//		//	key_num = macro_t9_key_word0;
//		//	gSelect = 0;
//		//}
//		break;
//	case KEY01:
//		//key_num = macro_t9_key_1;
//		if (gSelect == 0) {
//			key_num = macro_t9_key_1;
//		} else if (gSelect == 1) { 
//			key_num = macro_t9_key_pinyin0;
//		} else if (gSelect == 2) {
//			key_num = macro_t9_key_word0;
//			gSelect = 0;
//		}
//		break;
//	case KEY02:
//		//key_num = macro_t9_key_2;
//		if (gSelect == 0) {
//			key_num = macro_t9_key_2;
//		} else if (gSelect == 1) {
//			key_num = macro_t9_key_pinyin1;
//		} else if (gSelect == 2) {
//			key_num = macro_t9_key_word1;
//			gSelect = 0;
//		}
//		break;
//	case KEY03:
//		//key_num = macro_t9_key_3;
//		if (gSelect == 0) {
//			key_num = macro_t9_key_3;
//		} else if (gSelect == 1) {
//			key_num = macro_t9_key_pinyin2;
//		} else if (gSelect == 2) {
//			key_num = macro_t9_key_word2;
//			gSelect = 0;
//		}
//		break;
//	case KEY04:
//		//key_num = macro_t9_key_4;
//		if (gSelect == 0) {
//			key_num = macro_t9_key_4;
//		} else if (gSelect == 1) { 
//			key_num = macro_t9_key_pinyin3;
//		} else if (gSelect == 2) {
//			key_num = macro_t9_key_word3;
//			gSelect = 0;
//		}
//		break;
//	case KEY05:
//		//key_num = macro_t9_key_5;
//		if (gSelect == 0) {
//			key_num = macro_t9_key_5;
//		} else if (gSelect == 1) {
//			key_num = macro_t9_key_pinyin4;
//		} else if (gSelect == 2) {
//			key_num = macro_t9_key_word4;
//			gSelect = 0;
//		}
//		break;
//	case KEY06:
//		//key_num = macro_t9_key_6;
//		if (gSelect == 0) {
//			key_num = macro_t9_key_6;
//		} else if (gSelect == 1) {
//			key_num = macro_t9_key_pinyin5;
//		} else if (gSelect == 2) {
//			key_num = macro_t9_key_word5;
//			gSelect = 0;
//		}
//		break;
//	case KEY07:
//		key_num = macro_t9_key_7;
//		break;
//	case KEY08:
//		key_num = macro_t9_key_8;
//		break;
//	case KEY09:
//		key_num = macro_t9_key_9;
//		break;
//	case KEYCC:
//		key_num = macro_t9_key_backspace;
//		break;
//	case KEYGB:
//		key_num = macro_t9_key_switch;
//		break;
//	case KEYUP:
//		key_num = macro_t9_key_show_back;
//		break;
//	case KEYDN:
//		key_num = macro_t9_key_show_forward;
//		break;
//	case KEYOK:
//		key_num = macro_t9_key_enter;
//		gSelect++;
//		if (gSelect >= 3) {
//			gSelect = 0;
//		}
//		break;
//	case KEY13:
//		key_num = macro_t9_key_exit;
//		break;
//	default :
//		key_num = macro_t9_key_space;
//		break;
//	}
//	return key_num;
//}

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
		if (gSelect == 0) {
			key_num = macro_t9_key_1;
		} else if (gSelect == 1) { 
			key_num = macro_t9_key_pinyin0;
		} else if (gSelect == 2) {
			key_num = macro_t9_key_word0;
			gSelect = 0;
		}
		break;
	case KEY02:
		//key_num = macro_t9_key_2;
		if (gSelect == 0) {
			key_num = macro_t9_key_2;
		} else if (gSelect == 1) {
			key_num = macro_t9_key_pinyin1;
		} else if (gSelect == 2) {
			key_num = macro_t9_key_word1;
			gSelect = 0;
		}
		break;
	case KEY03:
		//key_num = macro_t9_key_3;
		if (gSelect == 0) {
			key_num = macro_t9_key_3;
		} else if (gSelect == 1) {
			key_num = macro_t9_key_pinyin2;
		} else if (gSelect == 2) {
			key_num = macro_t9_key_word2;
			gSelect = 0;
		}
		break;
	case KEY05:
		//key_num = macro_t9_key_4;
		if (gSelect == 0) {
			key_num = macro_t9_key_4;
		} else if (gSelect == 1) { 
			key_num = macro_t9_key_pinyin3;
		} else if (gSelect == 2) {
			key_num = macro_t9_key_word3;
			gSelect = 0;
		}
		break;
	case KEY06:
		//key_num = macro_t9_key_5;
		if (gSelect == 0) {
			key_num = macro_t9_key_5;
		} else if (gSelect == 1) {
			key_num = macro_t9_key_pinyin4;
		} else if (gSelect == 2) {
			key_num = macro_t9_key_word4;
			gSelect = 0;
		}
		break;
	case KEY07:
		//key_num = macro_t9_key_6;
		if (gSelect == 0) {
			key_num = macro_t9_key_6;
		} else if (gSelect == 1) {
			key_num = macro_t9_key_pinyin5;
		} else if (gSelect == 2) {
			key_num = macro_t9_key_word5;
			gSelect = 0;
		}
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
		key_num = macro_t9_key_switch;
		break;
	case KEYUP:
		key_num = macro_t9_key_show_back;
		break;
	case KEYDN:
		key_num = macro_t9_key_show_forward;
		break;
	case KEYOK:
		key_num = macro_t9_key_enter;
		gSelect++;
		if (gSelect >= 3) {
			gSelect = 0;
		}
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



static void t9_do_input(uint32_t active_id)
{
	switch(input.input_mode)
	{
		case macro_t9_mode_cn:
			if(t9_cn_keyhandler(&input,active_id)==_true)
			{
			  t9_cn_searchhandler(&input);
			}
			break;
	    case macro_t9_mode_len:
		case macro_t9_mode_uen:
		case macro_t9_mode_num:
			t9_en_keyhandler(&input,active_id);
			 break;
		default:break;
	}
}




static void t9_init(void*ptr)
{
	t9_initialize(&input,t9_py_index);
	gSelect = 0;
	//t9_update(PL_NULL);
}

static void t9_do_exit(void)
{
     //win_mbx_t mbx;
     uint32_t i;
     gInputData.size=pl_strlen(input.buf);
     for(i=0;i<input.count;i++)
     {
       gInputData.data[i]=input.buf[i];
     }
     
     //gui_window_exit_ex(handle,&mbx);
}

static font_t oldfont;
static font_t newfont;

static void t9_update(void*ptr)
{
	uint32_t i;
	//font_t oldfont;
	//font_t newfont;
	//pen_t  oldPen;
	//pen_t newPen;
	rect_t temp_rect;
	char buf[4]={0,0,0,0};
	
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

	gui_draw_h_line(rect.x0, rect.y0, rect.x1, BLUE);

	rect.x0 = input_mode_rect.x0;
	rect.y0 = input_mode_rect.y0 + 20;
	rect.y1 = input_mode_rect.y1 + 20;
	gui_fill_rect_buf(&rect, WHITE);
	gui_draw_h_line(rect.x0, rect.y0, rect.x1, BLUE);
	gui_draw_h_line(rect.x0, rect.y1, rect.x1, BLUE);

	gui_draw_v_line(BEGIN_X-1, BEGIN_Y, BEGIN_Y+60, BLUE);
	gui_draw_v_line(319, BEGIN_Y, BEGIN_Y+60, BLUE);
	
	//temp_rect.x0 = 120;
	//temp_rect.y0 = 60;
	//temp_rect.x1 = 319;
	//temp_rect.y1 = 100;
	gui_text_out_rect(input.buf,&input_rect,macro_text_v_align_center|
			                                macro_text_h_align_left);

	newfont.type=macro_font_style_middle;
	  gui_set_font(&newfont);
   if(input.input_mode==macro_t9_mode_cn)
   {
      for(i=0;i<6;i++)
	  {
		  if(input.mb_index[i]!=(t9PY_index*)0){
			  temp_rect.x0 = input_num_rect.x0 + i*48;
			  temp_rect.y0 = input_num_rect.y0;
			  temp_rect.x1 = input_num_rect.x1 + i*48;
			  temp_rect.y1 = input_num_rect.y1;
			  gui_text_out_rect(input.mb_index[i]->PY,\
				                 &temp_rect,\
						         macro_text_v_align_center|\
                                 macro_text_h_align_center);
		  }
	  }
	  

     for(i=0;i<6;i++)
	 {
	     //buf[0]=input.show_buf[i*2];
	   	 //buf[1]=input.show_buf[i*2+1];
		 buf[0]=i+1+0x30;
		 buf[1]=input.show_buf[i*2];
	   	 buf[2]=input.show_buf[i*2+1];
		 temp_rect.x0 = input_buf_rect.x0 + i*48;
		 temp_rect.y0 = input_buf_rect.y0;
		 temp_rect.x1 = input_buf_rect.x1 + i*48;
		 temp_rect.y1 = input_buf_rect.y1;
         gui_text_out_rect(buf,\
			              &temp_rect,\
						  macro_text_v_align_center|\
                          macro_text_h_align_center);
	  }//end for i
	}//end if 
	else if(input.input_mode==macro_t9_mode_len||
	        input.input_mode==macro_t9_mode_uen)
	{
	   //newfont.type=macro_font_style_big;
	   //gui_set_font(&newfont);

      for(i=0;i<6;i++)
	  {
	     buf[0]=input.show_buf[i];
		 temp_rect.x0 = input_num_rect.x0 + i*48;
		 temp_rect.y0 = input_num_rect.y0;
		 temp_rect.x1 = input_num_rect.x1 + i*48;		  
		 temp_rect.y1 = input_num_rect.y1;

         gui_text_out_rect(buf,\
			              &temp_rect,\
						  macro_text_v_align_center|\
                          macro_text_h_align_center);
	  }//end for i
	}
	
	//gui_window_update(handle,&reschain[12].rect);'
	if (input.input_mode==macro_t9_mode_len||
		input.input_mode==macro_t9_mode_uen) {
			if (gSelect == 2) {
				gSelect = 0;
			}
	}

	if (input.input_mode==macro_t9_mode_num) {
				gSelect = 0;
	}

	if (gSelect == 1) {
		temp_rect.x0 = input_mode_rect.x0 + 16;
		temp_rect.y0 = input_mode_rect.y0;
		temp_rect.x1 = input_mode_rect.x1 + 8;		  
		temp_rect.y1 = input_mode_rect.y1;

		gui_text_out_rect("#", &temp_rect, macro_text_v_align_center|macro_text_h_align_center);
	} else if (gSelect == 2) {
		temp_rect.x0 = input_mode_rect.x0 + 16;
		temp_rect.y0 = input_mode_rect.y0 + 20;
		temp_rect.x1 = input_mode_rect.x1 + 8;		  
		temp_rect.y1 = input_mode_rect.y1 + 20;

		gui_text_out_rect("#", &temp_rect, macro_text_v_align_center|macro_text_h_align_center);
	} 

	switch(input.input_mode)
	{
	case macro_t9_mode_cn:
	 gui_text_out_rect("中",\
				  &input_mode_rect,\
				  macro_text_v_align_center|\
				  macro_text_h_align_center);
				  break;
	case macro_t9_mode_len:
	 gui_text_out_rect("a ",\
				  &input_mode_rect,\
				  macro_text_v_align_center|\
				  macro_text_h_align_center);
				  break;
	case macro_t9_mode_uen:
	 gui_text_out_rect("A ",\
				  &input_mode_rect,\
				  macro_text_v_align_center|\
				  macro_text_h_align_center);
				  break;
	case macro_t9_mode_num:
	 gui_text_out_rect("1 ",\
				  &input_mode_rect,\
				  macro_text_v_align_center|\
				  macro_text_h_align_center);
				  break;
	default:break;
	}
	//将字体恢复，防止系统出错.
	gui_set_font(&oldfont);
     //gui_update_rect(0,0,399,239);
	oLCD_Update_Rect_Screen(0, 0, 240, 320);
}




void GUIInputTask(void)
{
	char KeyValue;
	uint32_t active_id;
	rect_t t9_rect, t9_rect1;
	t9_rect.x0 = 0;
	t9_rect.y0 = 13;
	t9_rect.x1 = 319;
	t9_rect.y1 = 51;
	t9_rect1.x0 = 60;
	t9_rect1.y0 = 60;
	t9_rect1.x1 = 319;
	t9_rect1.y1 = 100;


	while(1) {
		SEM_pend(&SEM_T9,  SYS_FOREVER);
			
		oLCD_Fill_Full_Buf(WHITE);
		key_on = 0;
		IRQ_clear(IRQ_EVT_EXTINT4);//清除中断标志
		IRQ_enable(IRQ_EVT_EXTINT4);//使能中断

		gui_get_font(&oldfont);
		newfont.type=macro_font_style_big;
		gui_set_font(&newfont);
		

		t9_init(PL_NULL);
		gui_text_out_rect("请输入您的名字^_^", &t9_rect, macro_text_h_align_center|macro_text_v_align_center);
		
		gui_text_out_rect("名字:", &t9_rect1, macro_text_v_align_center|macro_text_h_align_left);
		gui_draw_h_line(t9_rect1.x0+60, t9_rect1.y1+3, t9_rect1.x0+60+144, BLUE);

		t9_update(PL_NULL);
		//oLCD_Fill_Full_Buf(BLACK);
		while (1) {
		if (key_on == 1) {
			key_on = 0;
			IRQ_disable(IRQ_EVT_EXTINT4);//禁止中断	
			ZLG7290_ReadReg(ZLG7290_Key,&KeyValue);//读取键值
			active_id = (uint32_t)get_key_num(KeyValue);
			t9_do_input(active_id);
			t9_update(PL_NULL);
			if (active_id == macro_t9_key_exit) {
				if (pl_strlen(input.buf) != 0) {
					t9_do_exit();
					gui_set_font(&oldfont);
					break;
				}
			}

			IRQ_clear(IRQ_EVT_EXTINT4);//清除中断标志
			IRQ_enable(IRQ_EVT_EXTINT4);//使能中断
		}
		
		oLCD_Update_Rect_Screen(0, 0, 240, 320);
		}
		asm ( " NOP " ) ;
		asm ( " NOP " ) ;
	}
}



