
#include "sys_header/sys_manager.h"


//显示用户变量
static user_t *user_current;
static user_t *user[4];
static int     where;
static int     max_display;

static database_t *db;

static rect_t  rect[4];

static manager_init(void);

void rect_init(void) {
	//条目0
	rect[0].x0=17;
	//rect[0].y0=42;
	rect[0].y0 = 45;
	rect[0].x1=236;
	rect[0].y1=90;

	//条目1
	rect[1].x0=17;
	rect[1].y0=90;
	rect[1].x1=236;
	rect[1].y1=136;

	//条目2
	rect[2].x0=17;
	rect[2].y0=136;
	rect[2].x1=236;
	rect[2].y1=180;

	//条目3
	rect[3].x0=17;
	rect[3].y0=180;
	rect[3].x1=236;
	rect[3].y1=225;
}

static void manager_renew(uint8_t user_index, uint16_t color) 
{
	int32_t x0 = rect[user_index].x0;
	int32_t y0 = rect[user_index].y0;
	int32_t x1 = rect[user_index].x1;
	int32_t y1 = rect[user_index].y1;
	oLCD_Fill_Rect_Buf(y0, x0, (y1-y0+1), (x1-x0+1), color);
}

static void select_user(uint8_t user_index, uint8_t sel)
{
	int32_t x0 = rect[user_index].x0;
	int32_t y0 = rect[user_index].y0;
	int32_t x1 = rect[user_index].x1;
	int32_t y1 = rect[user_index].y1;
	int32_t i;
	for (i = 0; i < 4; i++) {
		gui_draw_rect(x0+i, y0+i, x1-i, y1-i, BLACK);
	}
}

static void admin_window_text_out(char *str, int user_id, int place)
{
	int  id_b,id_s,id_g;
	char id_buf[4];
	int i;
	rect_t rect[8];

	rect[0].x0 = 50;
	//rect[0].y0 = 58;
	rect[0].y0 = 48;
	rect[0].x1 = 103;
	//rect[0].y1 = 100;
	rect[0].y1 = 90;

	rect[1].x0 = 103;
	//rect[1].y0 = 58;
	rect[1].y0 = 48;
	rect[1].x1 = 221;
	//rect[1].y1 = 100;
	rect[1].y1 = 90;

	rect[2].x0 = 50;
	//rect[2].y0 = 100;
	rect[2].y0 = 95;
	rect[2].x1 = 103;
	//rect[2].y1 = 142;
	rect[2].y1 = 129;

	rect[3].x0 = 103;
	//rect[3].y0 = 100;
	rect[3].y0 = 95;
	rect[3].x1 = 221;
	//rect[3].y1 = 142;
	rect[3].y1 = 129;

	rect[4].x0 = 50;
	rect[4].y0 = 142;
	rect[4].x1 = 103;
	rect[4].y1 = 185;

	rect[5].x0 = 103;
	rect[5].y0 = 142;
	rect[5].x1 = 221;
	rect[5].y1 = 185;

	rect[6].x0  = 50;
	rect[6].y0  = 185;
	rect[6].x1  = 103;
	rect[6].y1  = 226;

	rect[7].x0 = 103;
	rect[7].y0 = 185;
	rect[7].x1 = 221;
	rect[7].y1 = 226;

	id_buf[0] = 0;
	id_buf[1] = 0;
	id_buf[2] = 0;
	id_buf[3] = 0;

	id_b = (user_id/100);
	id_s = (user_id%100)/10;
	id_g = user_id%10;

	if (id_b != 0)
	{
		id_buf[0] = (char)id_b + 0x30;
		id_buf[1] = (char)id_s + 0x30;
		id_buf[2] = (char)id_g + 0x30;
		id_buf[3] = 0;
	}
	else if (id_s != 0)
	{
		id_buf[0] = (char)id_s + 0x30;
		id_buf[1] = (char)id_g + 0x30;
		id_buf[2] = 0;
		id_buf[3] = 0;
	}
	else
	{
		id_buf[0] = (char)id_g + 0x30;
		id_buf[1] = 0;
		id_buf[2] = 0;
		id_buf[3] = 0;
	}

	//for (i=0; i<4; i++)
	//{

		if (user[place]->attribute == macro_db_administrator)
		{
			//gui_text_out_rect("admin",&rect[i],macro_text_h_align_left|
			//                                macro_text_v_align_center);
			gui_text_out_rect("admin", &rect[2*place], macro_text_h_align_center|macro_text_v_align_center);
		}
		else if(user[place]->attribute==macro_db_normal_user)
		{
		   //gui_text_out_rect("user",&rect[i],macro_text_h_align_left|
			//                                macro_text_v_align_center);
			gui_text_out_rect("user", &rect[2*place], macro_text_h_align_center|macro_text_v_align_center);
		}
	//}
	
	//ID
	//gui_text_out_rect(id_buf, &rect[2*place], macro_text_h_align_center|macro_text_v_align_center);
	//NAME
	gui_text_out_rect(str, &rect[2*place+1], macro_text_h_align_center|macro_text_v_align_center);
	//UPDATE

	//属性
	//admin_window_display_icon();
	//gui_update_rect(rect[2*place].x0, rect[2*place].y0, rect[2*place].x1, rect[2*place].y1);
	//gui_update_rect(rect[2*place+1].x0, rect[2*place+1].y0, rect[2*place+1].x1, rect[2*place+1].y1);
	oLCD_Update_Rect_Screen(rect[2*place].y0, rect[2*place].x0, (rect[2*place].y1-rect[2*place].y0+1), (rect[2*place].x1-rect[2*place].x0+1));
	oLCD_Update_Rect_Screen(rect[2*place+1].y0, rect[2*place+1].x0, (rect[2*place+1].y1-rect[2*place+1].y0+1), (rect[2*place+1].x1-rect[2*place+1].x0+1));

}

static void get_user_num(char KeyValue)
{
	switch(KeyValue)
	{

	case KEYCC:
		sys_user_unregister(user[where]); 
		//admin_window_init((void*)0);		
		manager_init();
		break;

	case KEY13:
		if (user[where]->attribute == macro_db_administrator)
		{
			user[where]->attribute = macro_db_normal_user;
		}
		else
		{
			user[where]->attribute = macro_db_administrator;
		}

		//更新到FLASH
		sys_db_write_unit(user[where]->id, user[where]);
		manager_renew(where, WHITE);
		admin_window_text_out(user[where]->name, user[where]->id, where);
		select_user(where, 1);
		break;

		//case USER_INFO_BUTTON_ID:
		//激活USER_INFO_WINDOW应用程序
		//	gui_window_active(USER_INFO_WINDOW_HANDLE, &mbx, MBX_NUMBER0);
		//	break;

	case KEYGB:
		gWindowType = MANAGER_WIN;
		break;

	case KEYUP:
		if (max_display == 4)
		{
			if ((where==1) || (where==2) || (where==3))
			{
				//admin_window_renew(where);
				//admin_window_text_out(user[where]->name, user[where]->id, where);
				manager_renew(where, WHITE);
				admin_window_text_out(user[where]->name, user[where]->id, where);
				where--;
				select_user(where, 1);
				//admin_window_xor_selected(where);
			}
			else
			{
				if (user[0]->pre == (user_t *)0)//到达表头
				{
					user[3] = sys_database_get_tail();
					user[2] = user[3]->pre;
					user[1] = user[2]->pre;
					user[0] = user[1]->pre;
					where = 3;
					//admin_window_renew(3);
					//admin_window_renew(2);
					//admin_window_renew(1);
					//admin_window_renew(0);
					manager_renew(3, WHITE);
					manager_renew(2, WHITE);
					manager_renew(1, WHITE);
					manager_renew(0, WHITE);
					
					admin_window_text_out(user[0]->name, user[0]->id, 0);
					admin_window_text_out(user[1]->name, user[1]->id, 1);
					admin_window_text_out(user[2]->name, user[2]->id, 2);
					admin_window_text_out(user[3]->name, user[3]->id, 3);
					select_user(3, 1);
					//admin_window_xor_selected(3);
					//admin_window_display_icon();
				}
				else
				{
					user[3]=user[3]->pre;
					user[2]=user[2]->pre;
					user[1]=user[1]->pre;
					user[0]=user[0]->pre;
					//admin_window_renew(3);
					//admin_window_renew(2);
					//admin_window_renew(1);
					//admin_window_renew(0);
					manager_renew(3, WHITE);
					manager_renew(2, WHITE);
					manager_renew(1, WHITE);
					manager_renew(0, WHITE);
					admin_window_text_out(user[0]->name, user[0]->id, 0);
					admin_window_text_out(user[1]->name, user[1]->id, 1);
					admin_window_text_out(user[2]->name, user[2]->id, 2);
					admin_window_text_out(user[3]->name, user[3]->id, 3);
					select_user(0, 1);
					//admin_window_xor_selected(0);
					//admin_window_display_icon();
					//where不变
				}
			}


		}
		else
		{
			if (where != 0)
			{
				//admin_window_renew(where);
				manager_renew(where, WHITE);
				admin_window_text_out(user[where]->name, user[where]->id, where);
				where--;
				select_user(where, 1);
				//admin_window_xor_selected(where);
			}
			else
			{
				//admin_window_renew(0);
				manager_renew(0, WHITE);
				admin_window_text_out(user[0]->name, user[0]->id, 0);
				where = max_display-1;
				select_user(where, 1);
				//admin_window_xor_selected(where);

			}

		}

		break;

	case KEYDN:
		if (max_display == 4)
		{
			if ((where==0) || (where==1) || (where==2))
			{
				//admin_window_renew(where);
				manager_renew(where, WHITE);
				admin_window_text_out(user[where]->name, user[where]->id, where);
				where++;
				select_user(where, 1);
				//admin_window_xor_selected(where);
			}
			else
			{
				if ((user[3]->next) == (user_t *)0)//到达数据库最后一项，返回头部
				{
					user[0] = sys_database_get_head();
					user[1] = user[0]->next;
					user[2] = user[1]->next;
					user[3] = user[2]->next;
					where = 0;//where归0
					//admin_window_renew(3);
					//admin_window_renew(2);
					//admin_window_renew(1);
					//admin_window_renew(0);
					manager_renew(3, WHITE);
					manager_renew(2, WHITE);
					manager_renew(1, WHITE);
					manager_renew(0, WHITE);

					admin_window_text_out(user[0]->name, user[0]->id, 0);
					admin_window_text_out(user[1]->name, user[1]->id, 1);
					admin_window_text_out(user[2]->name, user[2]->id, 2);
					admin_window_text_out(user[3]->name, user[3]->id, 3);
					select_user(0, 1);
					//admin_window_xor_selected(0);
					//admin_window_display_icon();
				}
				else//没有到达数据库最后一项，各项链表指向下一个
				{
					user[0]=user[0]->next;
					user[1]=user[1]->next;
					user[2]=user[2]->next;
					user[3]=user[3]->next;
					//admin_window_renew(3);
					//admin_window_renew(2);
					//admin_window_renew(1);
					//admin_window_renew(0);
					manager_renew(3, WHITE);
					manager_renew(2, WHITE);
					manager_renew(1, WHITE);
					manager_renew(0, WHITE);

					admin_window_text_out(user[0]->name, user[0]->id, 0);
					admin_window_text_out(user[1]->name, user[1]->id, 1);
					admin_window_text_out(user[2]->name, user[2]->id, 2);
					admin_window_text_out(user[3]->name, user[3]->id, 3);
					select_user(3, 1);
					//admin_window_xor_selected(3);
					//admin_window_display_icon();
					//where不变
				}
			}
		}
		else
		{
			if(where<(max_display-1))
			{
				//admin_window_renew(where);
				//manager_renew(where, WHITE);
				manager_renew(where, WHITE);
				admin_window_text_out(user[where]->name, user[where]->id, where);
				where++;
				select_user(where, 1);
				//admin_window_xor_selected(where);
			}
			else
			{
				//admin_window_renew(max_display-1);
				manager_renew(max_display-1, WHITE);
				admin_window_text_out(user[max_display-1]->name, user[max_display-1]->id, max_display-1);
				where = 0;
				select_user(where, 1);
				//admin_window_xor_selected(where);
			}

		}

		break;
	default:
		break;

	}
}

static manager_init(void)
{
	int count = 0;
	rect_t name_rect, id_rect;
	
	id_rect.x0 = 50;
	id_rect.y0 = 3;
	id_rect.x1 = 103;
	id_rect.y1 = 45;

	name_rect.x0 = 103;
	name_rect.y0 = 3;
	name_rect.x1 = 221;
	name_rect.y1 = 45;

	where = 0;
	oLCD_Fill_Full_Buf(WHITE);
	sys_database_go_to_head();
	user_current = sys_database_get_head();
	while (user_current != (user_t*)0)
	{
		user[count] = user_current;
		admin_window_text_out(user[count]->name, user[count]->id, count);
		user_current = sys_database_get_next();
		count++;
		if (count == 4)
		{
			break;
		}
	}
	max_display = count;
	
	//admin_window_display_icon();
	//admin_window_xor_selected(0);
	select_user(0, 1);
	if (db->all_cnt < 4)
	{
		max_display = db->all_cnt;
	}
	else
	{
		max_display = 4;
	}
	//gui_text_out_rect("ID", &id_rect, macro_text_h_align_center|macro_text_v_align_center);
	gui_text_out_rect("级别", &id_rect, macro_text_h_align_center|macro_text_v_align_center);
	gui_text_out_rect("名字", &name_rect, macro_text_h_align_center|macro_text_v_align_center);
	oLCD_Update_Rect_Screen(0, 0, 240, 320);
}

void SubManagerTask(void) 
{
	char KeyValue;
	rect_init();
	db=sys_get_database();
	while (1) {
		SEM_pend(&SEM_SUB_MANAGER,  SYS_FOREVER);
		manager_init();
		while (1) {
			if (key_on == 1) {
			key_on = 0;
			IRQ_disable(IRQ_EVT_EXTINT4);//禁止中断	

			ZLG7290_ReadReg(ZLG7290_Key,&KeyValue);//读取键值

			get_user_num(KeyValue);
			if (KeyValue == KEYGB) {
				break;
			}
			oLCD_Update_Rect_Screen(0, 0, 240, 320);
			IRQ_clear(IRQ_EVT_EXTINT4);//清除中断标志
			IRQ_enable(IRQ_EVT_EXTINT4);//使能中断
			}
		}
	}
}

