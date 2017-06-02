/******************************************************************************
 * 文件名：image.h
 * 功能：  实现了指纹图像的基本操作
******************************************************************************/

#include "GUI_header/GUI_text.h"

//存放字体的缓冲区
static uint8_t sys_font_buf[128]={
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0
};

static font_t gui_sys_font={
	16,     //高跟宽以汉字为准，当ascii码的值可以通过type类型然后获取
	16,
	macro_font_style_normal
};

static pen_t  gui_sys_pen={
   	1,      //笔的宽度
	RED,  //颜色默认为红色
	WHITE,  //背景默认为白色
    macro_pen_style_lucency //画笔风格默认为透明的
};

//void gui_set_font_quick(uint32_t font_style)
//{
//	switch (font_style)
//	{
//	case FONT_STYLE_SMALL:
//		gui_sys_font.width=16;
//		gui_sys_font.height=16;
//		gui_sys_font.type=FONT_STYLE_SMALL;
//		break;  
//	case FONT_STYLE_MIDDLE:
//		gui_sys_font.width=16;
//		gui_sys_font.height=16;
//		gui_sys_font.type=FONT_STYLE_MIDDLE;
//		break;    
//	case FONT_STYLE_BIG:
//		gui_sys_font.width=24;
//		gui_sys_font.height=24;
//		gui_sys_font.type=FONT_STYLE_BIG;
//		break;    
//	case FONT_STYLE_HUGE:
//		gui_sys_font.width=32;
//		gui_sys_font.height=32;
//		gui_sys_font.type=FONT_STYLE_HUGE;
//		break;
//	default:
//		gui_sys_font.width=16;
//		gui_sys_font.height=16;
//		gui_sys_font.type = FONT_STYLE_NORMAL;
//		break;
//	}
//}
//
//
//void gui_set_font(font_t *font)
//{
//	uint32_t t_type;
//	gui_sys_font.type  =font->type;
//	t_type = GET_CN_DOT_TYPE(font->type);
//
//	switch (t_type)
//	{
//	case FONT_CN_11X12_DOT:
//		gui_sys_font.width=16;
//		gui_sys_font.height=16;
//		break;  
//	case FONT_CN_15X16_DOT:
//		gui_sys_font.width=16;
//		gui_sys_font.height=16;
//		break;    
//	case FONT_CN_24X24_DOT:
//		gui_sys_font.width=24;
//		gui_sys_font.height=24;
//		break;    
//	case FONT_CN_32X32_DOT:
//		gui_sys_font.width=32;
//		gui_sys_font.height=32;
//		break;
//	default:
//		gui_sys_font.width=16;
//		gui_sys_font.height=16;
//		gui_sys_font.type=FONT_STYLE_NORMAL;
//		break;
//	}
//}

void gui_set_font(font_t *font)
{
	//gui_sys_font.height=font->height;
	//gui_sys_font.width =font->width ;
	uint32_t t_type;
	gui_sys_font.type  =font->type         ;
	t_type=macro_get_cn_dot_type(font->type);

	switch(t_type)
	{
	case macro_font_cn_11x12_dot:gui_sys_font.width=16;gui_sys_font.height=16;break;  
	case macro_font_cn_15x16_dot:gui_sys_font.width=16;gui_sys_font.height=16;break;    
	case macro_font_cn_24x24_dot:gui_sys_font.width=24;gui_sys_font.height=24;break;    
	case macro_font_cn_32x32_dot:gui_sys_font.width=32;gui_sys_font.height=32;break;
	default:gui_sys_font.width=16;gui_sys_font.height=16;gui_sys_font.type=macro_font_style_normal;break;
	}
}

void gui_get_font(font_t*font)
{
	font->height=gui_sys_font.height;
	font->width =gui_sys_font.width ;
	font->type  =gui_sys_font.type  ;
}

void gui_set_pen(pen_t*pen)
{
    gui_sys_pen.forecolor=pen->forecolor;
    gui_sys_pen.backcolor=pen->backcolor;
    gui_sys_pen.style    =pen->style;
	gui_sys_pen.width    =pen->width;
}

void gui_get_pen(pen_t*pen)
{
    pen->forecolor=gui_sys_pen.forecolor;
    pen->backcolor=gui_sys_pen.backcolor;
    pen->style    =gui_sys_pen.style    ;
	pen->width    =gui_sys_pen.width    ;
}

//下面两个函数是内部调用时使用的函数
static pen_t*gui_sys_get_pen(void)
{
	return  &gui_sys_pen;
}

static font_t*gui_sys_get_font(void)
{
	return &gui_sys_font;
}

//获取点阵信息
/**********************************************************
*加载字符的点阵信息,uint16_t ch 要被加载的字符内码.(GB2312)
*uint32_t type 要加载的字体的类型。
***********************************************************/
uint32_t gui_load_dot_matrix(uint16_t ch, uint32_t type)
{ 
	uint32_t Address;
	uint32_t t_type;
	uint32_t LSB,MSB;
	LSB= (uint32_t)macro_low_word(ch);
	MSB= (uint32_t)macro_high_word(ch);
	if(macro_is_cn_char(ch))
	{
		t_type=macro_get_cn_dot_type(type);
		switch(t_type)
		{
		case macro_font_cn_11x12_dot:
			Address=0x00000000;
			if(MSB >=0xA1 && MSB <= 0Xa3 && LSB >=0xA1){
               Address =( (MSB - 0xA1) * 94 + (LSB - 0xA1))*24+ Address;
			}else if(MSB == 0XA9 && LSB >=0xA1){
               Address =(282 + (LSB - 0xA1))*24+ Address;
			}else if(MSB >=0xB0 && MSB <= 0xF7 && LSB >=0xA1){
               Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+ 376)*24+ Address;
			}
		    load_char_dot_matrix(Address,24,sys_font_buf);
			return 24;
			//break;
		case macro_font_cn_15x16_dot:
			Address=0x2C9D0;
			if(MSB >=0xA4 && MSB <= 0Xa8 && LSB >=0xA1){
				Address = Address;
			}else if(MSB >=0xA1 && MSB <= 0Xa9 && LSB >=0xA1){
				Address =( (MSB - 0xA1) * 94 + (LSB - 0xA1))*32+ Address;
			}else if(MSB >=0xB0 && MSB <= 0xF7 && LSB >=0xA1){
				Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+ 846)*32+ Address;
			}
			load_char_dot_matrix(Address,32,sys_font_buf);
			return 32;
		case macro_font_cn_24x24_dot:
			Address=0x68190;
			if(MSB >=0xA4 && MSB <= 0Xa8 && LSB >=0xA1){
				Address = Address;
			}else if(MSB >=0xA1 && MSB <= 0Xa9 && LSB >=0xA1){
				Address =( (MSB - 0xA1) * 94 + (LSB - 0xA1))*72+ Address;
			}else if(MSB >=0xB0 && MSB <= 0xF7 && LSB >=0xA1){
				Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+ 846)*72+ Address;
			}
			load_char_dot_matrix(Address,72,sys_font_buf);
			return 72;
		case macro_font_cn_32x32_dot:
			Address=0XEDF00;
            if(MSB >=0xA4 && MSB <= 0Xa8 && LSB >=0xA1){
				Address = Address;
			}else if(MSB >=0xA1 && MSB <= 0Xa9 && LSB >=0xA1){
				Address =( (MSB - 0xA1) * 94 + (LSB - 0xA1))*128+ Address;
			}else if(MSB >=0xB0 && MSB <= 0xF7 && LSB >=0xA1){
				Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+ 846)*128+ Address;
			}
			load_char_dot_matrix(Address,128,sys_font_buf);
			return 128;
		default:break;
		}
	}
	else if(macro_is_ecn_char(ch))
	{
		t_type=macro_get_ecn_dot_type(type);
		switch(t_type)
		{
		case macro_font_ecn_6x12_dot :
			Address=0x1DBE00;
			if(ch>=0xAAA1&&ch<=0xAAFE){
				Address=(ch-0xAAA1)*12+Address;
			}else if(ch>0xABA1&&ch<=0xABC0){
				Address=(ch-0xABA1+94)*12+Address;
			}
			load_char_dot_matrix(Address,12,sys_font_buf);
			return 12;
		case macro_font_ecn_8x16_dot :
			Address=0x1DD780;
			if(ch>=0xAAA1&&ch<=0xAAFE){
				Address=(ch-0xAAA1)*16+Address;
			}else if(ch>0xABA1&&ch<=0xABC0){
				Address=(ch-0xABA1+94)*16+Address;
			}
			load_char_dot_matrix(Address,16,sys_font_buf);
			return 16;
		case macro_font_ecn_12x24_dot:
			Address=0x1DFF00;
			if(ch>=0xAAA1&&ch<=0xAAFE){
				Address=(ch-0xAAA1)*48+Address;
			}else if(ch>0xABA1&&ch<=0xABC0){
				Address=(ch-0xABA1+94)*48+Address;
			}
			load_char_dot_matrix(Address,48,sys_font_buf);
			return 48;
		case macro_font_ecn_16x32_dot:
			Address=0x1E5A50;
			if(ch>=0xAAA1&&ch<=0xAAFE){
				Address=(ch-0xAAA1)*64+Address;
			}else if(ch>0xABA1&&ch<=0xABC0){
				Address=(ch-0xABA1+94)*64+Address;
			}
			load_char_dot_matrix(Address,64,sys_font_buf);
			return 64;
		default:break;
		}
	}
	else if(macro_is_ascii_char(ch))
	{
		t_type=macro_get_ascii_dot_type(type);
		switch(t_type)
		{
		case macro_font_ascii_6x12_dot :
			Address=0x1DBE00;
			Address=(ch-0x20)*12+Address;
			load_char_dot_matrix(Address,12,sys_font_buf);
			return 12;
		case macro_font_ascii_8x16_dot :
			Address=0x1DD780;
			Address=(ch-0x20)*16+Address;
			load_char_dot_matrix(Address,16,sys_font_buf);
			return 16;
		case macro_font_ascii_12x24_dot:
			Address=0x1DFF00;
			Address=(ch-0x20)*48+Address;
			load_char_dot_matrix(Address,48,sys_font_buf);
			return 48;
		case macro_font_ascii_16x32_dot:
			Address=0x1E5A50;
			Address=(ch-0x20)*64+Address;
			load_char_dot_matrix(Address,64,sys_font_buf);
			return 64;
		case macro_font_ascii_5x7_dot  :
			Address=0x1DDF80;
			Address=(ch-0x20)*8+Address;
			load_char_dot_matrix(Address,8,sys_font_buf);
			return 8;
		case macro_font_ascii_7x8_dot  :
			Address=0x1DE280;
			Address=(ch-0x20)*8+Address;
			load_char_dot_matrix(Address,8,sys_font_buf);
			return 8;
		default:break;
		}
	}
	return 0;
}

//由于字符可能是汉字或者ascii码，所以用16位无符号整数表示.
void gui_put_char(uint16_t ch ,int x,int y)
{
	uint16_t i,j;
	uint8_t  temp;
	uint16_t byte_width;
	pen_t*pen;
	font_t*font;
 
	font=gui_sys_get_font();
	pen=gui_sys_get_pen();

	if(gui_load_dot_matrix(ch,font->type)==0){
		return;
	}//如果返回为0则表明这个字符不可显示或者是查不到其点阵数据
	else if(macro_is_cn_char(ch)){
		byte_width=font->width>>3;//字符的字节宽度
	}else{
		switch(font->width)
		{
		   case 16:byte_width=1;break;
		   case 24:byte_width=2;break;
		   case 32:byte_width=2;break;
		   default:byte_width=1;break;
		}
	}
	for(i=0;i<font->height;i++)
	{
		for(j=0;j<byte_width;j++)
		{
			temp=sys_font_buf[i*byte_width+j];
			j<<=3;
			if(temp&0x80){
				gui_draw_pixel(i+y,j+x,pen->forecolor);
			}
			if(temp&0x40){
				gui_draw_pixel(i+y,j+x+1,pen->forecolor);
			}
			if(temp&0x20){
				gui_draw_pixel(i+y,j+x+2,pen->forecolor);
			}
			if(temp&0x10){
				gui_draw_pixel(i+y,j+x+3,pen->forecolor);
			}
			if(temp&0x08){
				gui_draw_pixel(i+y,j+x+4,pen->forecolor);
			}
			if(temp&0x04){
				gui_draw_pixel(i+y,j+x+5,pen->forecolor);
			}
			if(temp&0x02){
				gui_draw_pixel(i+y,j+x+6,pen->forecolor);
			}
			if(temp&0x01){
				gui_draw_pixel(i+y,j+x+7,pen->forecolor);
			}

			j>>=3;
		}
	}
	//oLCD_Write_Chinese (50, 50, 16, 8, RED, BLACK, sys_font_buf);
	//oLCD_Update_Rect_Screen(0, 0, 240, 320);
	//oLCD_Update_Rect_Screen(y, x, font->height, (byte_width<<3));
}

void gui_text_out(char*str,int x,int y)
{
   uint16_t temp;
   font_t*font;
   int x0=x;  //缓存起始列号

   font=gui_sys_get_font(); //系统调用

   while(*str!=(char)0)
   {
      if((uint8_t)*str>=0xa0)  //如果是GB2312编码
      {
         temp=(uint16_t)*str++;
         temp<<=8;
         temp+=((uint16_t)*str)&0xff;  
         str++;    
		 gui_put_char(temp,x,y);
         x+=font->width;
      }
      else                    //如果是ascii码;
      {
          temp=(uint16_t)*str++;

		  if(temp<=0x20||temp>0xf0)//如果是非显示字符
		  {
			  switch(temp)
			  {
			  case 0x0a/*换行符*/:x=x0;y+=font->height;break;
			  case 0x20/*空格符*/:x+=font->width;break;
              default:break;
			  }
			  continue;//中断本次循环
          }
		  gui_put_char(temp,x,y);
		  x+=font->width>>1;
      } //end else 
   }//end while
}


//将文本输出到一个矩形区域,style是显示对齐方式
//水平对齐方式
/*#define macro_text_h_align_center   0x00000001u
#define macro_text_h_align_left     0x00000002u
#define macro_text_h_align_right    0x00000004u
//垂直对齐方式
#define macro_text_v_align_center   0x00010000u
#define macro_text_v_align_top      0x00020000u
#define macro_text_v_align_bottom   0x00040000u
//获取文本的垂直对齐方式和水平对齐方式
#define macro_get_text_v_align(v)   ((v)&0xffff0000u)
#define macro_get_text_h_align(h)   ((h)&0x0000ffffu)
*/
void gui_text_out_rect(char*str,rect_t*rect,uint32_t style)
{
	int32_t len_h,len_v;//水平方向的长度，和垂直方向的长度
	int32_t rect_w,rect_h;//矩形的长和宽
	int32_t count;//用来保存要显示的的字节数
	int x,y;//保存要起始显示字符的位置
	
	font_t*font;
    rect_w=rect->x1-rect->x0;
	rect_h=rect->y1-rect->y0;

	if(rect_w<=0||rect_h<=0){
		return;               //检查矩形合法性
	}
	
	font=gui_sys_get_font();
    count=len_h=pl_strlen(str);
	len_h=(len_h*font->width)>>1;//计算出要占的长度位置
	len_v=font->height;

	//设置起始横坐标
    if(len_h>=rect_w){
			x=rect->x0;
			count=(rect_w*2)/font->width;//更正计算可以显示的最大字符字节数
	}else{
	        switch(macro_get_text_h_align(style))
			{
	        case macro_text_h_align_center:x=((rect_w-len_h)>>1)+rect->x0;break;
	        case macro_text_h_align_left  :x=rect->x0;                     break;
	        case macro_text_h_align_right :x=rect->x1-len_h;               break;//右对齐时横轴起始坐标
	        default:x=rect->x0;break;
			}
	}

	if(len_v>=rect_h){
		y=rect->y0;
	}else{

     	switch(macro_get_text_v_align(style))
		{
		case macro_text_v_align_center:y=((rect_h-len_v)>>1)+rect->y0;break;
	    case macro_text_v_align_top   :y=rect->y0;                    break;
	    case macro_text_v_align_bottom:y=rect->y1-len_v;              break;
	    default:y=rect->y0;break;
		}
	}
    
	gui_text_out_c(str,x,y,count);
}



/*
从终端的指定位置开始显示count指定的字符个数。以字节为单位
*/
void gui_text_out_c(char*str,int32_t x,int32_t y,int32_t count)
{
	uint16_t temp;
   font_t*font;
 
   font=gui_sys_get_font(); //系统调用

   while(count-->0&&*str!=0)
   {
      if((uint8_t)*str>=0xa0)  //如果是GB2312编码
      {
         temp=(uint16_t)*str++;
         temp<<=8;
         temp+=((uint16_t)*str)&0xff;  
         str++;    
		 gui_put_char(temp,x,y);
         x+=font->width;
         count--; //count再多减1;
      }
      else                    //如果是ascii码;
      {
          temp=(uint16_t)*str++;

		  if(temp<=0x20||temp>0xf0)//如果是非显示字符忽略
		  {
			  if(temp==0x20){
                  x+=font->width>>1;
			  }
			  continue;//中断本次循环
          }
		  gui_put_char(temp,x,y);
          x+=font->width>>1;
      } //end else 
   }//end while
}

