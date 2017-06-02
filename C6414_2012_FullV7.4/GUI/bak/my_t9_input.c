
#include <stdio.h>

#include <string.h>
#include "GUI_header/t9_input.h"


//#define my_strlen(ptr) strlen(ptr)
//计算字符串长度的函数，用户可以通过宏定义引用函数库的函数
static unsigned int my_strlen(char*str)
{
   unsigned int count=0;
   while(*str++) {
     count++;
   }
   return count;
}

#define my_getchar()   getchar()

#ifdef EN_PC_TEST
//PC按键转换为T9数字按键
static unsigned char char_to_num(char key)	
{
	switch (key) {

	case 'A':
	case 'a':return T9_ALPHABET_abc;
	case 'B':
	case 'b':return T9_ALPHABET_abc;
	case 'C':
	case 'c':return T9_ALPHABET_abc;
	case 'D':
	case 'd':return T9_ALPHABET_def;
	case 'E':
	case 'e':return T9_ALPHABET_def;
	case 'F':
	case 'f':return T9_ALPHABET_def;
	case 'G':
	case 'g':return T9_ALPHABET_ghi;
	case 'H':
	case 'h':return T9_ALPHABET_ghi;
	case 'I':
	case 'i':return T9_ALPHABET_ghi;
	case 'J':
	case 'j':return T9_ALPHABET_jkl;
	case 'K':
	case 'k':return T9_ALPHABET_jkl;
	case 'L':
	case 'l':return T9_ALPHABET_jkl;
	case 'M':
	case 'm':return T9_ALPHABET_mno;
	case 'N':
	case 'n':return T9_ALPHABET_mno;
	case 'O':
	case 'o':return T9_ALPHABET_mno;
	case 'P':
	case 'p':return T9_ALPHABET_pqrs;
	case 'Q':
	case 'q':return T9_ALPHABET_pqrs;
	case 'R':
	case 'r':return T9_ALPHABET_pqrs;
	case 'S':
	case 's':return T9_ALPHABET_pqrs;
	case 'T':
	case 't':return T9_ALPHABET_tuv;
	case 'U':
	case 'u':return T9_ALPHABET_tuv;
	case 'V':
	case 'v':return T9_ALPHABET_tuv;
	case 'W':
	case 'w':return T9_ALPHABET_wxyz;
    case 'X':
	case 'x':return T9_ALPHABET_wxyz;
	case 'Y':
	case 'y':return T9_ALPHABET_wxyz;
	case 'Z':
	case 'z':return T9_ALPHABET_wxyz;

    case '0':return T9_NUM_0;
	case '1':return T9_NUM_1;
	case '2':return T9_NUM_2;
	case '3':return T9_NUM_3;
	case '4':return T9_NUM_4;
	case '5':return T9_NUM_5;
	case '6':return T9_NUM_6;
	case '7':return T9_NUM_7;
	case '8':return T9_NUM_8;
	case '9':return T9_NUM_9;

	case '/':return T9_PY_PREV;
	case '*':return T9_PY_NEXT;

//	case ' ':
	case '.':return T9_PY_HZ;
	
	case '\n':return CR;
	case '#':return T9_PY_INPUT;

	case '=':
	case '+':return T9_HZ_NEXT;

	case '-':return T9_HZ_PREV;
	case '|':return OVER;
	case '<':return BACKSPACE;

	default:return  0;
	}
}
#endif

//输入法切换
static void input_switch(t9_input_t *p_t9_input)
{
	unsigned char i = 0;
	p_t9_input->switch_mode = 0;

	p_t9_input->py_count = 0;
	p_t9_input->py_index = 0;

	p_t9_input->mb_match_num = 0;

	p_t9_input->hz_index = 0;

	for (i = 0; i < 6; i++) 
		p_t9_input->py_buf[i] = 0;
	
	for (i = 0; i < 20; i++)
		p_t9_input->show_buf[i] = 0;

	switch (p_t9_input->input_mode) {
	case T9_CHN_MODE:
		p_t9_input->input_mode = T9_UEN_MODE;
		printf("\n大写输入:\n");
		break;
	case T9_UEN_MODE:
		p_t9_input->input_mode = T9_LEN_MODE;
		printf("\n小写输入:\n");
		break;
	case T9_LEN_MODE:
		p_t9_input->input_mode = T9_NUM_MODE;
		p_t9_input->switch_mode = 1;	//数字输入时,直接就是输入数字了,没有选择过程
		printf("\n数字输入:\n");
		break;
	case T9_NUM_MODE:
		p_t9_input->input_mode = T9_CHN_MODE;
		printf("\n中文输入:\n");
		break;
	default:
		p_t9_input->input_mode = T9_CHN_MODE;
		printf("\n中文输入:\n");
		break;
	}
	
}

//获取输入拼音字串对应的汉字的码表
//p_input:输入的按键序列，由'0'~'9'组成的字符串
//match_mb:存储"获取到的拼音索引地址"的数组
//返回值:与输入序列匹配(全匹配或大于匹配)的拼音,最多8个
static unsigned char t9_get_match_py_mb(t9_input_t *p_t9_input)//(char *p_input, t9PY_index **match_mb)
{
	unsigned char i = 0, j = 0;
	unsigned char input_len = 0;

	unsigned char match_num = 0;//p_t9_input->mb_match_num;
	char *p_input = p_t9_input->py_buf;
	t9PY_index **match_mb = p_t9_input->py_mb;

	t9PY_index *p_current_index,*p_last_index;	//指向"拼音输入法查询码表"数组的某个下标元素的地址
//	t9PY_index *p_temp_index;

	unsigned int index_begin = 0, index_end = 0;
	unsigned char py_1 = 0, py_2 = 0;			//一维或二维索引表的下表
	if (*p_input == '\0')
		return 0;

	input_len = my_strlen(p_input);

	//下面一大堆:计算搜索的起始地址,分析一维,二维索引表可能出现的各种情况
	if (input_len >= 2) {	//输入数字串>=2,使用二维搜索
		py_1 = (*p_input) - 0x32;	// 输入的第一个字符 - '2'
		//p_input++;
		py_2 = (*(p_input+1)) - 0x32; // 输入的第二个字符 - '2'
		
		index_begin = t9_search_index2[py_1][py_2];
		if (index_begin == 0) {						//没有这种字串组合(25,27,29,99等),index_begin为0沿用一维搜索
			index_begin = t9_search_index1[py_1];	//开始地址修改为一维搜索对应的地址
			if (py_2 < 7)							//非一维索引表最后一个元素,则搜索结束地址为下一元素对应的地址
				index_end = t9_search_index1[py_1+1];
			else									//对应'99'
				index_end = 397;
		} else										//其他开始地址不为0
			index_end = t9_search_index2[py_1][py_2+1];

		while (index_end == 0) {	//下一元素为0,即index_end为0,则计算index_end为最先不为0的位置
			py_2++;			       //如果index_end已经超出[py_1][8]了,则
			if(py_2 > 7) {			//移植下一行[py_1 + 1][0]
				if (py_1 < 7) {
					py_1++;
					py_2 = 0;
				} else {
					index_end = 397;
					break;
				}
			}//end if (py_2 > 7)
			index_end = t9_search_index2[py_1][py_2];
		}//end while (index_end == 0)
	} else {	//输入数字串==1,一维搜索
		py_1 = (*p_input) - 0x32;
		index_begin = t9_search_index1[py_1];
		if (py_1 >= 7)
			index_end = 397;
		else
			index_end = t9_search_index1[py_1+1];
	}
	//上面一大堆:计算搜索的起始地址,分析一维,二维索引表可能出现的各种情况

	p_current_index = &(t9PY_index2[index_begin]);	//索引表开始地址
	p_last_index = &(t9PY_index2[index_end]);		//索引表结束地址

	while (p_current_index < p_last_index) {	//遍历索引表
		for (i = 0; i < input_len; i++) {
			if ((*(p_input + i)) != *(p_current_index->t9PY_T9 + i)) {	//完全或大于匹配
				//((*(p_input + i)) != *((*p_current_index).t9PY_T9 + i)) {	//完全或大于匹配
/*				if (i + 1 > j) {	//找出所有不匹配中最长的那个不匹配数字串(长度保存在j中,串保存在p_temp_index中)
					j = i + 1;
					p_temp_index = p_current_index; 
				}*/
				break; //
			} 
		}

		if ((i == input_len) && (match_num < 8)) {	//匹配的保存到出口参数match_mb
			//匹配,最多8组.匹配并不是指相比较的字符长短一样，不是完全匹配
			match_mb[match_num] = p_current_index;
			match_num++;
		}

		p_current_index++;
	}//end while (p_current_index < p_last_index)

//	if (j != input_len)	//不匹配但最多匹配字符的1组
//		match_mb[7] = p_temp_index;	
	p_t9_input->mb_match_num = match_num;
	return match_num;
}

//处理p_t9_input的成员:show_buf,hz_select等
//temp_char:按键键值
void t9_cn_show_handle(t9_input_t *p_t9_input, unsigned char temp_char)
{
	unsigned char count = 0,i = 0,j = 0;
	unsigned char pos = 2 * (temp_char - 0x31);		  //计算选择的汉字的位置,1个汉字对应2个字节
	unsigned char offset = (p_t9_input->hz_index/2)*2;//除于2后又乘于2的作用是为了获得偶数(因为拼音码表首字符是'@'而不是汉字)
	
	t9PY_index *temp_py_mb = p_t9_input->py_mb[p_t9_input->py_index];
	p_t9_input->mb_select = p_t9_input->py_mb[p_t9_input->py_index];
	
	if ((temp_char >= T9_NUM_1) && (temp_char <= T9_NUM_9)) {	//选择汉字
		if (p_t9_input->show_buf[pos] != 0) {	//数字对应的汉字非空,
																		
			p_t9_input->hz_select[0] = p_t9_input->show_buf[pos];	//更新选中汉字缓存区
			p_t9_input->hz_select[1] = p_t9_input->show_buf[pos + 1];

			if (p_t9_input->count < MAX_BUF_LEN) {//输入缓存区未满
				p_t9_input->buf[p_t9_input->count] = p_t9_input->show_buf[pos];	//更新输入缓存区
				p_t9_input->count++;
				p_t9_input->buf[p_t9_input->count] = p_t9_input->show_buf[pos + 1];
				p_t9_input->count++;
			}

			p_t9_input->py_index = 0;	//更新结构信息，准备下次的输入
			p_t9_input->py_count = 0;
			for (i = 0; i < 6; i++) 
				p_t9_input->py_buf[i] = 0;

			p_t9_input->hz_index = 0;
			//for (i = 0; i < 20; i++)
				//p_t9_input->show_buf[i] = 0;
		}
	} else {	//非1-9,根据实际功能按键进行设置
		p_t9_input->py_select = temp_py_mb->PY;
		count = strlen(temp_py_mb->PY_mb) - 1;
		count = count - offset > 18 ? 18 : count - offset;//算出有多少个有效汉字,多于9个,显示9,少于则选择实际的个数
		for (j = 0; j < count; j++) {	//更新显示缓存
			p_t9_input->show_buf[j] = *(temp_py_mb->PY_mb + offset + 1 + j);
		}
		for (; j < 18; j++) {
			p_t9_input->show_buf[j] = 0;
		}
	}
}


unsigned char flag = 0;//用于标记是否显示pritf("\n按键 /:...\n");
//根据不同的输入键值,显示对应的界面
//temp_char:输入的键值
void t9_cn_show(t9_input_t *p_t9_input, unsigned char temp_char)
{
	unsigned char temp;
	t9PY_index * temp_py_mb;
	if ((temp_char >= T9_NUM_1) && (temp_char <= T9_NUM_9)) {		//显示被选汉字及输入缓存区
			if (p_t9_input->show_buf[2 * (temp_char - 0x31)] != 0) {	//输入的数字有效,即对应位置有汉字
				printf("                   \n");
				printf("选择的汉字为:   ");
				printf(p_t9_input->hz_select);
				printf("\n");
				printf(p_t9_input->buf);
				printf("\n");
				p_t9_input->switch_mode = 0;	//更新为拼写状态
				flag = 1;
			} 
		} else if (temp_char != CR){	//显示选择界面
			printf("\n\n你选择的拼音:    ");
			printf((p_t9_input->mb_select)->PY);

			printf("\n输入数字或+,-选择 \n");
			printf(p_t9_input->show_buf);
			//printf((p_t9_input->mb_select)->PY_mb + (hz_index/2)*2 + 1);
			printf("\n1 2 3 4 5 6 7 8 9\n");

			printf ("拼写组合:");
            for (temp = p_t9_input->py_index; temp < p_t9_input->mb_match_num; temp++) {
                temp_py_mb = p_t9_input->py_mb[temp];

                printf (" ");
                printf (temp_py_mb->PY);//printf ((*(temp_py_mb)).PY);
            }
               printf ("\n");
		}

}

//根据输入的不同键值,更新p_t9_input(swich_mode,py_index,hz_index等)
//及获取对应拼音的码表
//temp_char:输入的键值
void t9_cn_key_handle(t9_input_t *p_t9_input, unsigned char temp_char)
{

	unsigned char match_num = 0;

	switch (temp_char) {
	case T9_NUM_2:
	case T9_NUM_3:
	case T9_NUM_4:
	case T9_NUM_5:
	case T9_NUM_6:
	case T9_NUM_7:
	case T9_NUM_8:
	case T9_NUM_9:
		if (p_t9_input->switch_mode == 0) {	//2-9按键对应的拼音组合
			if(p_t9_input->py_count < 6)	//一次最多输入6个拼音
			{
				p_t9_input->py_buf[p_t9_input->py_count] = temp_char;	//将输入的数字串写入对应的
				p_t9_input->py_count++;									//拼音缓存区里
				p_t9_input->hz_index = 0;   
				match_num = t9_get_match_py_mb(p_t9_input);				//更新码表
			}
		}
		break;
	case T9_PY_PREV:		//先前选择拼音
			if (p_t9_input->py_index > 0)
				p_t9_input->py_index--;	
			else
				p_t9_input->py_index = p_t9_input->mb_match_num - 1;
			p_t9_input->hz_index = 0;
			break;
	case T9_PY_NEXT:		//向后选择
			p_t9_input->py_index++;
			if (p_t9_input->py_index >= p_t9_input->mb_match_num)
				p_t9_input->py_index = 0;
			p_t9_input->hz_index = 0;
			break;
//	case '.':
//	case ' ':
	case T9_PY_INPUT:		//输入法切换
		input_switch(p_t9_input);
		break;
	case T9_PY_HZ:			//字串(拼音)输入or确定汉字
		p_t9_input->switch_mode ^= 1;
		break;
	//case '=':
	case T9_HZ_NEXT:		//下一页汉字
		if (p_t9_input->hz_index < strlen((p_t9_input->mb_select)->PY_mb) - 19) //开头有个'@'
			p_t9_input->hz_index += 18;
		break;
	case T9_HZ_PREV:		//上一页汉字
		if (p_t9_input->hz_index >=18)
			p_t9_input->hz_index -=18;
		break;
	case BACKSPACE:								//删除输入拼音(数字串)或输入缓冲区的汉字或字母
		if (p_t9_input->switch_mode == 0) {
			if (p_t9_input->py_count > 0) {			//删除拼音(数字串)
				//i--;
				p_t9_input->py_count--;
			}
			p_t9_input->py_buf[p_t9_input->py_count] = 0x00; 
			p_t9_input->hz_index = 0; 
			match_num = t9_get_match_py_mb(p_t9_input);
		} else {									//删除输入缓冲区
			if (p_t9_input->count > 0) {		
				p_t9_input->count--;
			}
			if (p_t9_input->buf[p_t9_input->count] > 0x7E) {//判断是汉字还是字符
				p_t9_input->buf[p_t9_input->count] = 0x00;	//汉字删除两个字节
				p_t9_input->count--;
				p_t9_input->buf[p_t9_input->count] = 0x00;
			//	p_t9_input->count--;
			} else {
				p_t9_input->buf[p_t9_input->count] = 0x00;	//字符删除一个字节
			//	p_t9_input->count--;				
			}
		}
		break;
//		case OVER:
//			py_ok = 1;
//			break;
	default:
		break;
	}
	
	if (p_t9_input->switch_mode) {			//汉字模式下,进行显示处理和显示
		t9_cn_show_handle(p_t9_input, temp_char);
		t9_cn_show(p_t9_input, temp_char);
	} 
}

//根据不同的输入键值,显示对应的界面
//temp_char:输入的键值
void t9_en_show(t9_input_t *p_t9_input, unsigned char temp_char)
{
	unsigned char i = 0;
	unsigned char pos = temp_char - 0x31;
	if (p_t9_input->input_mode == T9_NUM_MODE) {	//数字输入模式,直接显示输入的数字
			printf("                   \n");
			printf("输入的数字为:   ");		
			printf("%c",p_t9_input->show_buf[0]);
			printf("\n");
			printf(p_t9_input->buf);
			printf("\n");
			flag = 1;
	} else {										//大小写输入模式
		if (temp_char >= T9_NUM_1 && temp_char <= T9_NUM_9)  {	//显示选择的字母
			if (p_t9_input->show_buf[pos] != 0) {	//输入的数字有效,即对应位置有字符
				printf("                   \n");
				printf("选择的字母为:   ");
				printf("%c",p_t9_input->show_buf[pos]);	

				if (p_t9_input->count < MAX_BUF_LEN) {//输入缓存区未满
					p_t9_input->buf[p_t9_input->count] = p_t9_input->show_buf[pos];	//更新输入缓存区
					p_t9_input->count++;
				}

				printf("\n");
				printf(p_t9_input->buf);
				printf("\n");
				p_t9_input->switch_mode = 0;	//更新为拼写输入状态
				flag = 1;
			} 
		} else if (temp_char != CR ){	//显示选择界面
			//printf("\n\n你选择的字母:    ");
			//printf((p_t9_input->mb_select)->PY);

			printf("\n输入数字选择 \n");
			for (i = 0; i < 4; i++) {
				printf("%c",p_t9_input->show_buf[i]);
				printf(" ");
			}
			//printf((p_t9_input->mb_select)->PY_mb + (hz_index/2)*2 + 1);
			printf("\n1 2 3 4\n");
		}
	}	
	//}
}

//根据输入的不同键值,更新p_t9_input的成员
//temp_char:输入的键值
void t9_en_key_handle(t9_input_t *p_t9_input, unsigned char temp_char)
{
	unsigned char i = 0;
	switch (temp_char) {
	case T9_NUM_0:
	case T9_NUM_1:
		if (p_t9_input->input_mode == T9_NUM_MODE) {	//数字输入法
			if (p_t9_input->count < MAX_BUF_LEN) {
				p_t9_input->show_buf[0] = temp_char;
				p_t9_input->buf[p_t9_input->count] = temp_char;
				p_t9_input->count++;
				p_t9_input->switch_mode = 1;			//数字输入时,直接就是输入数字了,没有选择过程
			}
		}
		break;
	case T9_NUM_2:
	case T9_NUM_3:
	case T9_NUM_4:
	case T9_NUM_5:
	case T9_NUM_6:
	case T9_NUM_7:
	case T9_NUM_8:
	case T9_NUM_9:
		if (p_t9_input->switch_mode == 0) {
			if(p_t9_input->py_count < 1) {		//每次输入只接收一个
				p_t9_input->py_buf[p_t9_input->py_count] = temp_char;
				p_t9_input->py_count++;
				for (i = p_t9_input->py_count; i < 6; i++)
					p_t9_input->py_buf[i] = 0x00;
			}
			if (p_t9_input->input_mode == T9_LEN_MODE) {	//小写abc
				for (i = 0; i < 4; i++) {
					p_t9_input->show_buf[i] = ascii_tab[temp_char - 0x32][i];//小写字母
				}
			} else if (p_t9_input->input_mode == T9_UEN_MODE) {	//大写ABC
				for (i = 0; i < 3; i++) {
					p_t9_input->show_buf[i] = ascii_tab[temp_char - 0x32][i] - 32;//大写字母
				}
				if (ascii_tab[temp_char - 0x32][3] != 0)
					p_t9_input->show_buf[3] = ascii_tab[temp_char - 0x32][3] - 32;
				else
					p_t9_input->show_buf[3] = 0;
			} 
		}else if (p_t9_input->input_mode == T9_NUM_MODE) {	//数字输入时,直接就是输入数字了,没有选择过程
				if (p_t9_input->count < MAX_BUF_LEN) {
					p_t9_input->show_buf[0] = temp_char;
					p_t9_input->buf[p_t9_input->count] = temp_char;
					p_t9_input->count++;
					p_t9_input->switch_mode = 1;
				}
			}
		break;
	case T9_PY_HZ:
		if (p_t9_input->input_mode != T9_NUM_MODE)
			p_t9_input->switch_mode ^= 1;				//字母输入或确定字母
		break;
	case T9_PY_INPUT:
		input_switch(p_t9_input);
		break;
	case BACKSPACE:									//删除输入字母(数字串)或输入缓冲区的汉字或字母
		if (p_t9_input->switch_mode == 0) {
			if (p_t9_input->py_count > 0) {						//删除输入数字串
				//i--;
				p_t9_input->py_count--;
			}
			p_t9_input->py_buf[p_t9_input->py_count] = 0x00; 
		} else {												//删除输入缓存区
			if (p_t9_input->count > 0) {
				p_t9_input->count--;
			}
			if (p_t9_input->buf[p_t9_input->count] > 0x7E) {	//判读是汉字or字符
				p_t9_input->buf[p_t9_input->count] = 0x00;			//汉字删除两个字节
				p_t9_input->count--;
				p_t9_input->buf[p_t9_input->count] = 0x00;
			//	p_t9_input->count--;
			} else {												//字符删除一个字节
				p_t9_input->buf[p_t9_input->count] = 0x00;
			//	p_t9_input->count--;				
			}
		}
		break;
	}
	if (p_t9_input->switch_mode) {
//		t9_cn_show_handle(p_t9_input, temp_char);
		t9_en_show(p_t9_input, temp_char);
	} 
}

//p_t9_input各个成员的初始化
void t9_input_init(t9_input_t *p_t9_input) 
{
	unsigned char i = 0;

	p_t9_input->input_mode = 0;
	p_t9_input->switch_mode = 0;

	p_t9_input->py_count = 0;
	p_t9_input->py_index = 0;

	p_t9_input->mb_match_num = 0;

	p_t9_input->hz_index = 0;

	p_t9_input->count = 0;

	
	for (i = 0; i < 6; i++) 
		p_t9_input->py_buf[i] = 0;
	
	for (i = 0; i < 20; i++)
		p_t9_input->show_buf[i] = 0;

	for (i = 0; i < 4; i++)
		p_t9_input->hz_select[i] = 0;

	for (i = 0; i < 34; i++)
		p_t9_input->buf[i] = 0;	

	p_t9_input->py_select = (unsigned char *)0;

	for (i = 0; i < 8; i++)
		p_t9_input->py_mb[i] = (t9PY_index *)0;
	p_t9_input->mb_select = (t9PY_index *)0;

}

//void main(void)
//{
//	t9_input_t input;
//	unsigned char temp_char;
////	printf("Hello world! \n");
//	//putchar(*(PY_mb_a+1));
//	//putchar(*(PY_mb_a+2));
////	printf(temp_word);
////	printf("\n");
//	t9_input_init(&input);
//	printf ("\n按键 /:上一拼音 *:下一拼音 .和空格及回车键:输入状态和选字状态切换\n");         //
//	printf ("请按键：2-abc 3-def 4-ghi 5-jkl 6-mno 7-pqrs 8-tuv 9-wxyz \n");  
//	while (temp_char!= '|') {	//输入'|'退出程序
//		if(flag == 1) {
//			if (input.input_mode == T9_CHN_MODE) {	//中文输入提示界面
//				printf ("\n按键 /:上一拼音 *:下一拼音 .和空格及回车键:输入状态和选字状态切换\n");         //
//				printf ("拼：2-abc 3-def 4-ghi 5-jkl 6-mno 7-pqrs 8-tuv 9-wxyz \n");   
//			} else if (input.input_mode == T9_UEN_MODE) {	//大写ABC输入提示界面
//				printf ("\nABC：2-ABC 3-DEF 4-GHI 5-JKL 6-MON 7-PQRS 8-TUV 9-WXYZ \n");  			
//			} else if (input.input_mode == T9_LEN_MODE) {	//小写abc输入提示界面
//				printf ("\nabc：2-abc 3-def 4-ghi 5-jkl 6-mno 7-pqrs 8-tuv 9-wxyz \n"); 
//			} else if (input.input_mode == T9_NUM_MODE) {	//数字输入提示界面
//				printf ("\n123:\n"); 
//			}
//			flag = 0;
//		}
//		temp_char = char_to_num(my_getchar());			//键值获取
//		if (input.input_mode == T9_CHN_MODE)			//中文输入
//			t9_cn_key_handle(&input, temp_char);		//调用中文键值处理
//		else											
//			t9_en_key_handle(&input, temp_char);		//调用英文键值处理
//	}
//}







