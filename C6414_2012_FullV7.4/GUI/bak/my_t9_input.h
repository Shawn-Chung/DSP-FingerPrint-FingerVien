
#ifndef __T9_INPUT_H_
#define __T9_INPUT_H_

/* »ù±¾ÀàĞÍ¶¨Òå */


#ifdef __cplusplus
extern "C" {
#endif

//#define EN_PC_TEST	//PCÉÏ²âÊÔ

typedef struct tag_t9PY_index
{
	char *t9PY_T9;	//Êı×Ö
	char *PY;		//Æ´Òô
	char *PY_mb;	//Âë±í
}t9PY_index;

typedef struct tag_t9_input_t
{
	//´Ó¿Õ¼ä¿¼ÂÇ,ÕûÀíË³Ğò
	unsigned char input_mode;		//ÊäÈë·¨Ä£Ê½:ÖĞ,´óĞ¡Ğ´,Êı×Ö
	unsigned char switch_mode;		//Ñ¡ÔñÆ´Òôorºº×Ö
	unsigned char py_count;			//ÊäÈëÆ´ÒôÊıÄ¿,<=6(0-5)
	unsigned char py_index;			//´ıÑ¡Æ´ÒôË÷Òı
	unsigned char mb_match_num;		//ÓëÊäÈë×Ö·û´®´óÓÚÆ¥ÅäµÄÂë±í¸öÊı,<=8(0-7);
	unsigned char hz_index;			//´ıÑ¡ºº×ÖË÷Òı
	unsigned char count;			//ÊäÈë½á¹û»º´æÇø¼ÆÊı

	unsigned char py_buf[6];		//ÊäÈëÆ´Òô×Ö´®»º´æÇø
	unsigned char hz_select[4];				//Ñ¡ÖĞµÄºº×Ö»º´æÇø
	unsigned char show_buf[20];		//ÓûÏÔÊ¾ºº×Ö»º´æÇø,0-17(9¸öºº×Ö)
	unsigned char buf[34];			//ÊäÈë½á¹û»º´æÇø

	unsigned char *py_select;
	t9PY_index *py_mb[8];			//Æ¥ÅäÆ´ÒôÔÚÂë±íÖĞµÄÎ»ÖÃ
	t9PY_index *mb_select;			//±»Ñ¡ÖĞµÄÆ´Òô¶ÔÓ¦µÄÂë±í

}t9_input_t;

/*
typedef struct tagt9_input_t
{	//´Ó·ÖÀà¿¼ÂÇ
	unsigned char input_mode;		//ÊäÈë·¨Ä£Ê½:ÖĞ,´óĞ¡Ğ´,Êı×Ö
	unsigned char switch_mode;		//Ñ¡ÔñÆ´Òôorºº×Ö

	unsigned char py_buf[6];		//ÊäÈëÆ´Òô×Ö´®»º´æÇø
	unsigned char py_count;			//ÊäÈëÆ´ÒôÊıÄ¿,<=6(0-5)
	unsigned char py_index;			//´ıÑ¡Æ´ÒôË÷Òı
	//unsigned char py_hz;
	unsigned char *py_select;

	t9PY_index *py_mb[8];			//Æ¥ÅäÆ´ÒôÔÚÂë±íÖĞµÄÎ»ÖÃ
	t9PY_index *mb_select;			//±»Ñ¡ÖĞµÄÆ´Òô¶ÔÓ¦µÄÂë±í
	unsigned char mb_match_num;		//ÓëÊäÈë×Ö·û´®´óÓÚÆ¥ÅäµÄÂë±í¸öÊı,<=8(0-7);

	unsigned char show_buf[20];		//ÓûÏÔÊ¾ºº×Ö»º´æÇø,0-17(9¸öºº×Ö)
	unsigned char hz_index;			//´ıÑ¡ºº×ÖË÷Òı
	unsigned char hz_select[4];				//Ñ¡ÖĞµÄºº×Ö»º´æÇø

	unsigned char buf[34];			//ÊäÈë½á¹û»º´æÇø
	unsigned char count;			//ÊäÈë½á¹û»º´æÇø¼ÆÊı
}t9_input_t;
*/


//	
//Ò»¼¶ËÑË÷±í			   2   3   4    5    6    7    8    9  (½¨Á¢ÒÔÊäÈëÊı×Ö´®³¤¶È2ÒÔÉÏµÄË÷Òı±í)
short t9_search_index1[8]={1, 55, 87, 125, 181, 225, 304, 323};

//¶ş¼¶ËÑË÷±í(½¨Á¢ÒÔÊäÈëÊı×Ö´®³¤¶È2ÒÔÉÏµÄË÷Òı±í)
short t9_search_index2[8][8]={
{2,		12,		17,		0,	43,		0,	49,		0,},//22,23,24,25,26,27,28,29
{56,	64,		69,		0,	75,		80,	81,		0,},//32,33,34,35,36,37,38,39
{87,	97,		0,		0,	105,	0,	109,	0,},//42,43,44,45,46,47,48,49
{125,	135,	141,	0,	159,	0,	163,	0,},//52,53,54,55,56,57,58,59
{182,	192,	200,	0,	215,	0,	218,	0,},//62,63,64,65,66,67,68,69
{225,	238,	247,	0,	283,	0,	289,	0,},//72,73,74,75,76,77,78,79
{304,	309,	311,	0,	316,	0,	318,	0,},//82,83,84,85,86,87,88,89
{323,	336,	344,	0,	377,	0,	383,	0,},//92,93,94,95,96,97,98,99
};


//#define CNTLQ      0x11
//#define CNTLS      0x13
//#define DEL        0x7F
#define BACKSPACE		0x08
#define CR				0x0D
#define LF				0x0A

#define OVER			124u // '|'

#define T9_PY_PREV		47u	// '/'
#define T9_PY_NEXT		42u	// '*'
#define T9_HZ_PREV		45u	// '-'
#define T9_HZ_NEXT		43u	// '+'

#define T9_PY_HZ		20u	// '.'



#define T9_PY_INPUT		35u // '#'

#define T9_CHN_MODE     0u
#define T9_UEN_MODE     1u
#define T9_LEN_MODE		2u
#define T9_NUM_MODE		3u

#define MAX_BUF_LEN		32

#define T9_NUM_0	48u         
#define T9_NUM_1	49u
#define T9_NUM_2	50u
#define T9_NUM_3	51u
#define T9_NUM_4	52u
#define T9_NUM_5	53u
#define T9_NUM_6	54u
#define T9_NUM_7	55u
#define T9_NUM_8	56u		
#define T9_NUM_9	57u

//×ÖÄ¸ÓëÊı×ÖµÄ¶ÔÓ¦
#define T9_ALPHABET_abc     T9_NUM_2
#define T9_ALPHABET_def     T9_NUM_3
#define T9_ALPHABET_ghi     T9_NUM_4
#define T9_ALPHABET_jkl     T9_NUM_5
#define T9_ALPHABET_mno     T9_NUM_6
#define T9_ALPHABET_pqrs    T9_NUM_7
#define T9_ALPHABET_tuv     T9_NUM_8
#define T9_ALPHABET_wxyz    T9_NUM_9


//×Ö·û×ª»»±í
char ascii_tab[8][4]={
	{'a','b','c',  },//2
	{'d','e','f',  },//3
	{'g','h','i',  },//4
	{'j','k','l',  },//5
	{'m','n','o',  },//6
	{'p','q','r','s'},//7
	{'t','u','v',  },//8
	{'w','x','y','z'},//9
};


static unsigned int my_strlen(char*str);
//static unsigned char char_to_num(char key);
static void input_switch(t9_input_t *p_t9_input);
static unsigned char t9_get_match_py_mb(t9_input_t *p_t9_input);

void t9_cn_show_handle(t9_input_t *p_t9_input, unsigned char temp_char);
void t9_cn_show(t9_input_t *p_t9_input, unsigned char temp_char);
void t9_cn_key_handle(t9_input_t *p_t9_input, unsigned char temp_char);

void t9_en_show(t9_input_t *p_t9_input, unsigned char temp_char);
void t9_en_key_handle(t9_input_t *p_t9_input, unsigned char temp_char);
void t9_input_init(t9_input_t *p_t9_input);
	

//0-396
//Æ´ÒôÊäÈë·¨ºº×ÖÅÅÁĞ±í
char PY_mb_space []={"0"};
char PY_mb_a     []={"@°¡°¢"};
char PY_mb_ai    []={"@°®°¤°­°¥°£°«°¬°¦°§°©°¨°ª°¯"};
char PY_mb_an    []={"@°´°²°µ°¸°°°³°¶°±°·"};
char PY_mb_ang   []={"@°º°»°¹"};
char PY_mb_ao    []={"@°Á°¼°½°¾°Â°¿°À°Ã°Ä"};
char PY_mb_ba    []={"@°Ë°Ñ°Í°Ö°Õ°Ô°Î°Ç°É°Ó°Å°Ì°Æ°Ê°Ï°È°Ğ"};
char PY_mb_bai   []={"@°×°Ù°Ú°Ü°İ°Û°Ø°Ş"};
char PY_mb_ban   []={"@°ì°ë°à°ã°é°å°æ°á°è°ç°ä°â°ß°í°ê"};
char PY_mb_bang  []={"@°î°ï°ó°ø°ñ°÷°ò°ô°ù°õ°ö°ğ"};
char PY_mb_bao   []={"@°ü±£±¦±¨±§±¥±©±¬°û±¡°ı±¢±¤±ª°ú±«°şÆÙ"};
char PY_mb_bei   []={"@±°±­±¯±®±±±´±·±¸±³±µ±¶±»±¹±º±²"};
char PY_mb_ben   []={"@±¼±¾±½±¿º»"};
char PY_mb_beng  []={"@±À±Á±Â±Ã±Å±Ä"};
char PY_mb_bi    []={"@±Æ±Ç±È±Ë±Ê±É±Ò±Ø±Ï±Õ±Ó±Ñ±İ±Ğ±Ö±Ô±Í±×±Ì±Î±Ú±Ü±Û"};
char PY_mb_bian  []={"@±ß±à±Ş±á±â±å±ã±ä±é±æ±ç±è"};
char PY_mb_biao  []={"@±ë±ê±ì±í"};
char PY_mb_bie   []={"@±ï±î±ğ±ñ"};
char PY_mb_bin   []={"@±ö±ò±ó±õ±ô±÷"};
char PY_mb_bing  []={"@±ù±ø±û±ü±ú±ş±ı²¢²¡"};
char PY_mb_bo    []={"@²¦²¨²£²§²±²¤²¥²®²µ²¯²´²ª²¬²°²©²³²«²­²²²·"};
char PY_mb_bu    []={"@²¹²¸²¶²»²¼²½²À²¿²º²¾"};
char PY_mb_ca    []={"@²Á"};
char PY_mb_cai   []={"@²Â²Å²Ä²Æ²Ã²É²Ê²Ç²È²Ë²Ì"};
char PY_mb_can   []={"@²Î²Í²Ğ²Ï²Ñ²Ò²Ó"};
char PY_mb_cang  []={"@²Ö²×²Ô²Õ²Ø"};
char PY_mb_cao   []={"@²Ù²Ú²Ü²Û²İ"};
char PY_mb_ce    []={"@²á²à²Ş²â²ß"};
char PY_mb_ceng  []={"@²ã²äÔø"};
char PY_mb_cha   []={"@²æ²å²é²ç²è²ë²ì²ê²í²ï²îÉ²"};
char PY_mb_chai  []={"@²ğ²ñ²ò"};
char PY_mb_chan  []={"@²ô²ó²÷²ö²ø²õ²ú²ù²û²ü"};
char PY_mb_chang []={"@²ı²ş³¦³¢³¥³£³§³¡³¨³©³«³ª"};
char PY_mb_chao  []={"@³­³®³¬³²³¯³°³±³³³´´Â"};
char PY_mb_che   []={"@³µ³¶³¹³¸³·³º"};
char PY_mb_chen  []={"@³»³¾³¼³À³Á³½³Â³¿³Ä³Ã"};
char PY_mb_cheng []={"@³Æ³Å³É³Ê³Ğ³Ï³Ç³Ë³Í³Ì³Î³È³Ñ³Ò³Ó"};
char PY_mb_chi   []={"@³Ô³Õ³Ú³Ø³Û³Ù³Ö³ß³Ş³İ³Ü³â³à³ã³á"};
char PY_mb_chong []={"@³ä³å³æ³ç³è"};
char PY_mb_chou  []={"@³é³ğ³ñ³ë³î³í³ï³ê³ì³ó³ò³ô"};
char PY_mb_chu   []={"@³ö³õ³ı³ø³ü³ú³û³÷³ù´¡´¢³ş´¦´¤´¥´£Ğó"};
char PY_mb_chuai []={"@´§"};
char PY_mb_chuan []={"@´¨´©´«´¬´ª´­´®"};
char PY_mb_chuang[]={"@´³´¯´°´²´´"};
char PY_mb_chui  []={"@´µ´¶´¹´·´¸"};
char PY_mb_chun  []={"@´º´»´¿´½´¾´¼´À"};
char PY_mb_chuo  []={"@´Á"};
char PY_mb_ci    []={"@´Ã´Ê´Ä´É´È´Ç´Å´Æ´Ë´Î´Ì´Í"};
char PY_mb_cong  []={"@´Ñ´Ó´Ò´Ğ´Ï´Ô"};
char PY_mb_cou   []={"@´Õ"};
char PY_mb_cu    []={"@´Ö´Ù´×´Ø"};
char PY_mb_cuan  []={"@´Ú´Ü´Û"};
char PY_mb_cui   []={"@´Ş´ß´İ´à´ã´á´â´ä"};
char PY_mb_cun   []={"@´å´æ´ç"};
char PY_mb_cuo   []={"@´ê´è´é´ì´ë´í"};
char PY_mb_da    []={"@´î´ï´ğ´ñ´ò´ó"};
char PY_mb_dai   []={"@´ô´õ´ö´ú´ø´ıµ¡´ù´û´ü´ş´÷"};
char PY_mb_dan   []={"@µ¤µ¥µ£µ¢µ¦µ¨µ§µ©µ«µ®µ¯µ¬µ­µ°µª"};
char PY_mb_dang  []={"@µ±µ²µ³µ´µµ"};
char PY_mb_dao   []={"@µ¶µ¼µºµ¹µ·µ»µ¸µ½µ¿µÁµÀµ¾"};
char PY_mb_de    []={"@µÃµÂµÄ"};
char PY_mb_deng  []={"@µÆµÇµÅµÈµËµÊµÉ"};
char PY_mb_di    []={"@µÍµÌµÎµÒµÏµĞµÓµÑµÕµ×µÖµØµÜµÛµİµÚµŞµÙ"};
char PY_mb_dian  []={"@µàµáµßµäµãµâµçµèµéµêµæµëµíµìµîµå"};
char PY_mb_diao  []={"@µóµğµòµïµñµõµöµô"};
char PY_mb_die   []={"@µùµøµüµıµşµúµû"};
char PY_mb_ding  []={"@¶¡¶£¶¢¶¤¶¥¶¦¶©¶¨¶§"};
char PY_mb_diu   []={"@¶ª"};
char PY_mb_dong  []={"@¶«¶¬¶­¶®¶¯¶³¶±¶²¶°¶´"};
char PY_mb_dou   []={"@¶¼¶µ¶·¶¶¶¸¶¹¶º¶»"};
char PY_mb_du    []={"@¶½¶¾¶Á¶¿¶À¶Â¶Ä¶Ã¶Ê¶Å¶Ç¶È¶É¶Æ"};
char PY_mb_duan  []={"@¶Ë¶Ì¶Î¶Ï¶Ğ¶Í"};
char PY_mb_dui   []={"@¶Ñ¶Ó¶Ô¶Ò"};
char PY_mb_dun   []={"@¶Ö¶Ø¶Õ¶×¶Ü¶Û¶Ù¶İ"};
char PY_mb_duo   []={"@¶à¶ß¶á¶Ş¶ä¶â¶ã¶ç¶é¶æ¶è¶å"};
char PY_mb_e     []={"@¶ï¶í¶ğ¶ë¶ì¶ê¶î¶ò¶ó¶ñ¶ö¶õ¶ô"};
char PY_mb_en    []={"@¶÷"};
char PY_mb_er    []={"@¶ù¶ø¶û¶ú¶ı¶ü¶ş·¡"};
char PY_mb_fa    []={"@·¢·¦·¥·£·§·¤·¨·©"};
char PY_mb_fan   []={"@·«·¬·­·ª·²·¯·°·³·®·±·´·µ·¸·º·¹·¶··"};
char PY_mb_fang  []={"@·½·»·¼·À·Á·¿·¾·Â·Ã·Ä·Å"};
char PY_mb_fei   []={"@·É·Ç·È·Æ·Ê·Ë·Ì·Í·Ï·Ğ·Î·Ñ"};
char PY_mb_fen   []={"@·Ö·Ô·×·Ò·Õ·Ó·Ø·Ú·Ù·Û·İ·Ü·Ş·ß·à"};
char PY_mb_feng  []={"@·á·ç·ã·â·è·å·é·æ·ä·ë·ê·ì·í·ï·î"};
char PY_mb_fo    []={"@·ğ"};
char PY_mb_fou   []={"@·ñ"};
char PY_mb_fu    []={"@·ò·ô·õ·ó¸¥·ü·ö·÷·ş·ı·ú¸¡¸¢·û¸¤·ù¸£·ø¸§¸¦¸®¸«¸©¸ª¸¨¸­¸¯¸¸¸¼¸¶¸¾¸º¸½¸À¸·¸´¸°¸±¸µ¸»¸³¸¿¸¹¸²"};
char PY_mb_ga    []={"@¸Â¸Á"};
char PY_mb_gai   []={"@¸Ã¸Ä¸Æ¸Ç¸È¸Å"};
char PY_mb_gan   []={"@¸É¸Ê¸Ë¸Î¸Ì¸Í¸Ñ¸Ï¸Ò¸Ğ¸Ó"};
char PY_mb_gang  []={"@¸Ô¸Õ¸Ú¸Ù¸Ø¸×¸Ö¸Û¸Ü"};
char PY_mb_gao   []={"@¸Ş¸á¸ß¸à¸İ¸â¸ã¸å¸ä¸æ"};
char PY_mb_ge    []={"@¸ê¸í¸ç¸ì¸ë¸î¸é¸è¸ó¸ï¸ñ¸ğ¸ô¸ö¸÷¸õ¿©"};
char PY_mb_gei   []={"@¸ø"};
char PY_mb_gen   []={"@¸ù¸ú"};
char PY_mb_geng  []={"@¸ü¸ı¸û¸ş¹¡¹¢¹£"};
char PY_mb_gong  []={"@¹¤¹­¹«¹¦¹¥¹©¹¬¹§¹ª¹¨¹®¹¯¹°¹²¹±"};
char PY_mb_gou   []={"@¹´¹µ¹³¹·¹¶¹¹¹º¹¸¹»"};
char PY_mb_gu    []={"@¹À¹¾¹Ã¹Â¹Á¹½¹¼¹¿¹Å¹È¹É¹Ç¹Æ¹Ä¹Ì¹Ê¹Ë¹Í"};
char PY_mb_gua   []={"@¹Ï¹Î¹Ğ¹Ñ¹Ò¹Ó"};
char PY_mb_guai  []={"@¹Ô¹Õ¹Ö"};
char PY_mb_guan  []={"@¹Ø¹Û¹Ù¹Ú¹×¹İ¹Ü¹á¹ß¹à¹Ş"};
char PY_mb_guang []={"@¹â¹ã¹ä"};
char PY_mb_gui   []={"@¹é¹ç¹ê¹æ¹ë¹è¹å¹ì¹î¹ï¹í¹ô¹ñ¹ó¹ğ¹ò"};
char PY_mb_gun   []={"@¹õ¹ö¹÷"};
char PY_mb_guo   []={"@¹ù¹ø¹ú¹û¹ü¹ı"};
char PY_mb_ha    []={"@¸ò¹ş"};
char PY_mb_hai   []={"@º¢º¡º£º¥º§º¦º¤"};
char PY_mb_han   []={"@º¨º©º¬ºªº¯º­º®º«º±º°ººº¹ºµº·º´º¸º¶º³º²"};
char PY_mb_hang  []={"@º¼º½ĞĞ"};
char PY_mb_hao   []={"@ºÁºÀº¿º¾ºÃºÂºÅºÆºÄ"};
char PY_mb_he    []={"@ºÇºÈºÌºÏºÎºÍºÓºÒºËºÉºÔºĞºÊºØºÖºÕº×"};
char PY_mb_hei   []={"@ºÚºÙ"};
char PY_mb_hen   []={"@ºÛºÜºİºŞ"};
char PY_mb_heng  []={"@ºàºßºãºáºâ"};
char PY_mb_hong  []={"@ºäºåºæºëºìºêºéºçºè"};
char PY_mb_hou   []={"@ºîºíºïºğºóºñºò"};
char PY_mb_hu    []={"@ºõºôºö»¡ºüºúºøºşºùº÷ºıºû»¢»£»¥»§»¤»¦"};
char PY_mb_hua   []={"@»¨»ª»©»¬»«»¯»®»­»°"};
char PY_mb_huai  []={"@»³»²»´»±»µ"};
char PY_mb_huan  []={"@»¶»¹»·»¸»º»Ã»Â»½»»»Á»¼»À»¾»¿"};
char PY_mb_huang []={"@»Ä»Å»Ê»Ë»Æ»Ì»Í»È»Ç»É»Ğ»Î»Ñ»Ï"};
char PY_mb_hui   []={"@»Ò»Ö»Ó»Ô»Õ»Ø»×»Ú»Ü»ã»á»ä»æ»å»â»ß»Ş»à»İ»Ù»Û"};
char PY_mb_hun   []={"@»è»ç»é»ë»ê»ì"};
char PY_mb_huo   []={"@»í»î»ğ»ï»ò»õ»ñ»ö»ó»ô"};
char PY_mb_ji    []={"@¼¥»÷¼¢»ø»ú¼¡¼¦¼£¼§»ı»ù¼¨¼©»û»ş»ü¼¤¼°¼ª¼³¼¶¼´¼«¼±¼²¼¬¼¯¼µ¼­¼®¼¸¼º¼·¼¹¼Æ¼Ç¼¿¼Í¼Ë¼É¼¼¼Ê¼Á¼¾¼È¼Ã¼Ì¼Å¼Ä¼Â¼À¼»¼½½å"};
char PY_mb_jia   []={"@¼Ó¼Ğ¼Ñ¼Ï¼Ò¼Î¼Ô¼Õ¼×¼Ö¼Ø¼Û¼İ¼Ü¼Ù¼Ş¼ÚĞ®"};
char PY_mb_jian  []={"@¼é¼â¼á¼ß¼ä¼ç¼è¼æ¼à¼ã¼ê¼å¼ğ¼ó¼í¼ë¼ñ¼õ¼ô¼ì¼ï¼ò¼î¼û¼ş½¨½¤½£¼ö¼ú½¡½§½¢½¥½¦¼ù¼ø¼ü¼ı"};
char PY_mb_jiang []={"@½­½ª½«½¬½©½®½²½±½°½¯½³½µ½´"};
char PY_mb_jiao  []={"@½»½¼½¿½½½¾½º½·½¹½¶½¸½Ç½Æ½Ê½È½Ã½Å½Â½Á½Ë½É½Ğ½Î½Ï½Ì½Ñ½Í¾õ½À"};
char PY_mb_jie   []={"@½×½Ô½Ó½Õ½Ò½Ö½Ú½Ù½Ü½à½á½İ½Ş½Ø½ß½ã½â½é½ä½æ½ì½ç½ê½ë½è"};
char PY_mb_jin   []={"@½í½ñ½ï½ğ½ò½î½ó½ö½ô½÷½õ¾¡¾¢½ü½ø½ú½ş½ı½û½ù"};
char PY_mb_jing  []={"@¾©¾­¾¥¾£¾ª¾§¾¦¾¬¾¤¾«¾¨¾®¾±¾°¾¯¾»¾¶¾·¾º¾¹¾´¾¸¾³¾²¾µ"};
char PY_mb_jiong []={"@¾¼¾½"};
char PY_mb_jiu   []={"@¾À¾¿¾¾¾Å¾Ã¾Ä¾Á¾Â¾Æ¾É¾Ê¾Ì¾Î¾Ç¾È¾Í¾Ë"};
char PY_mb_ju    []={"@¾Ó¾Ğ¾Ñ¾Ô¾Ò¾Ï¾Ö½Û¾Õ¾×¾Ú¾Ù¾Ø¾ä¾Ş¾Ü¾ß¾æ¾ã¾ç¾å¾İ¾à¾â¾Û¾á"};
char PY_mb_juan  []={"@¾ê¾è¾é¾í¾ë¾î¾ì"};
char PY_mb_jue   []={"@¾ï¾ö¾÷¾ñ¾ø¾ó¾ò¾ô¾ğ"};
char PY_mb_jun   []={"@¾ü¾ı¾ù¾û¾ú¿¡¿¤¾ş¿£¿¥¿¢"};
char PY_mb_ka    []={"@¿§¿¦¿¨"};
char PY_mb_kai   []={"@¿ª¿«¿­¿®¿¬"};
char PY_mb_kan   []={"@¼÷¿¯¿±¿°¿²¿³¿´"};
char PY_mb_kang  []={"@¿µ¿¶¿·¿¸¿º¿¹¿»"};
char PY_mb_kao   []={"@¿¼¿½¿¾¿¿"};
char PY_mb_ke    []={"@¿À¿Á¿Â¿Æ¿Ã¿Å¿Ä¿Ç¿È¿É¿Ê¿Ë¿Ì¿Í¿Î"};
char PY_mb_ken   []={"@¿Ï¿Ñ¿Ò¿Ğ"};
char PY_mb_keng  []={"@¿Ô¿Ó"};
char PY_mb_kong  []={"@¿Õ¿×¿Ö¿Ø"};
char PY_mb_kou   []={"@¿Ù¿Ú¿Û¿Ü"};
char PY_mb_ku    []={"@¿İ¿Ş¿ß¿à¿â¿ã¿á"};
char PY_mb_kua   []={"@¿ä¿å¿æ¿è¿ç"};
char PY_mb_kuai  []={"@¿é¿ì¿ë¿ê"};
char PY_mb_kuan  []={"@¿í¿î"};
char PY_mb_kuang []={"@¿ï¿ğ¿ñ¿ö¿õ¿ó¿ò¿ô"};
char PY_mb_kui   []={"@¿÷¿ù¿ø¿ú¿ü¿û¿ı¿şÀ¢À£À¡"};
char PY_mb_kun   []={"@À¤À¥À¦À§"};
char PY_mb_kuo   []={"@À©À¨À«Àª"};
char PY_mb_la    []={"@À¬À­À²À®À°À¯À±"};
char PY_mb_lai   []={"@À´À³Àµ"};
char PY_mb_lan   []={"@À¼À¹À¸À·À»À¶À¾À½ÀºÀÀÀ¿ÀÂÀÁÀÃÀÄ"};
char PY_mb_lang  []={"@ÀÉÀÇÀÈÀÅÀÆÀÊÀË"};
char PY_mb_lao   []={"@ÀÌÀÍÀÎÀÏÀĞÀÑÀÔÀÓÀÒ"};
char PY_mb_le    []={"@ÀÖÀÕÁË"};
char PY_mb_lei   []={"@À×ÀØÀİÀÚÀÙÀÜÀßÀáÀàÀÛÀŞ"};
char PY_mb_leng  []={"@ÀâÀãÀä"};
char PY_mb_li    []={"@ÀåÀæÀêÀëÀòÀçÀìÁ§ÀèÀéÀñÀîÀïÁ¨ÀíÀğÁ¦ÀúÀ÷Á¢ÀôÀöÀûÀøÁ¤ÀıÁ¥ÀşÀóÀõÀùÁ£ÀüÁ¡"};
char PY_mb_lian  []={"@Á¬Á±Á¯Á°Á«ÁªÁ®Á­Á²Á³Á·Á¶ÁµÁ´"};
char PY_mb_liang []={"@Á©Á¼Á¹ÁºÁ¸Á»Á½ÁÁÁÂÁ¾ÁÀÁ¿"};
char PY_mb_liao  []={"@ÁÊÁÉÁÆÁÄÁÅÁÈÁÎÁÃÁÇÁÍÁÏÁÌ"};
char PY_mb_lie   []={"@ÁĞÁÓÁÒÁÔÁÑ"};
char PY_mb_lin   []={"@ÁÚÁÖÁÙÁÜÁÕÁØÁ×ÁÛÁİÁßÁŞÁà"};
char PY_mb_ling  []={"@ÁæÁéÁëÁáÁèÁåÁêÁçÁâÁãÁäÁìÁîÁí"};
char PY_mb_liu   []={"@ÁïÁõÁ÷ÁôÁğÁòÁóÁñÁöÁøÁù"};
char PY_mb_long  []={"@ÁúÁüÁıÁûÂ¡ÁşÂ¤Â¢Â£"};
char PY_mb_lou   []={"@Â¦Â¥Â§Â¨ÂªÂ©"};
char PY_mb_lu    []={"@Â¶Â¬Â®Â«Â¯Â­Â±Â²Â°Â³Â½Â¼Â¸Â¹Â»ÂµÂ·Â¾ÂºÂ´"};
char PY_mb_luan  []={"@ÂÏÂÍÂÎÂĞÂÑÂÒ"};
char PY_mb_lue   []={"@ÂÓÂÔ"};
char PY_mb_lun   []={"@ÂÕÂØÂ×ÂÙÂÚÂÖÂÛ"};
char PY_mb_luo   []={"@ÂŞÂÜÂßÂàÂáÂâÂİÂãÂåÂçÂæÂä"};
char PY_mb_lv    []={"@ÂËÂ¿ÂÀÂÂÂÃÂÁÂÅÂÆÂÄÂÉÂÇÂÊÂÌÂÈ"};
char PY_mb_ma    []={"@ÂèÂéÂíÂêÂëÂìÂîÂğÂï"};
char PY_mb_mai   []={"@ÂñÂòÂõÂóÂôÂö"};
char PY_mb_man   []={"@ÂùÂøÂ÷ÂúÂüÃ¡ÂıÂşÂû"};
char PY_mb_mang  []={"@Ã¦Ã¢Ã¤Ã£Ã§Ã¥"};
char PY_mb_mao   []={"@Ã¨Ã«Ã¬Ã©ÃªÃ®Ã­Ã¯Ã°Ã³Ã±Ã²"};
char PY_mb_me    []={"@Ã´"};
char PY_mb_mei   []={"@Ã»Ã¶ÃµÃ¼Ã·Ã½ÃºÃ¸Ã¹Ã¿ÃÀÃ¾ÃÃÃÁÃÄÃÂ"};
char PY_mb_men   []={"@ÃÅÃÆÃÇ"};
char PY_mb_meng  []={"@ÃÈÃËÃÊÃÍÃÉÃÌÃÏÃÎ"};
char PY_mb_mi    []={"@ÃÖÃÔÃÕÃÑÃÓÃÒÃ×ÃĞÃÚÃÙÃØÃÜÃİÃÛ"};
char PY_mb_mian  []={"@ÃßÃàÃŞÃâÃãÃäÃáÃåÃæ"};
char PY_mb_miao  []={"@ÃçÃèÃéÃëÃìÃêÃîÃí"};
char PY_mb_mie   []={"@ÃğÃï"};
char PY_mb_min   []={"@ÃñÃóÃòÃöÃõÃô"};
char PY_mb_ming  []={"@ÃûÃ÷ÃùÃúÃøÃü"};
char PY_mb_miu   []={"@Ãı"};
char PY_mb_mo    []={"@ºÑÃşÄ¡Ä£Ä¤Ä¦Ä¥Ä¢Ä§Ä¨Ä©Ä­Ä°ÄªÄ¯Ä®Ä«Ä¬"};
char PY_mb_mou   []={"@Ä²Ä±Ä³"};
char PY_mb_mu    []={"@Ä¸Ä¶ÄµÄ·Ä´Ä¾Ä¿ÄÁÄ¼Ä¹Ä»ÄÀÄ½ÄºÄÂ"};
char PY_mb_na    []={"@ÄÃÄÄÄÇÄÉÄÈÄÆÄÅ"};
char PY_mb_nai   []={"@ÄËÄÌÄÊÄÎÄÍ"};
char PY_mb_nan   []={"@ÄĞÄÏÄÑéª"};
char PY_mb_nang  []={"@ÄÒ"};
char PY_mb_nao   []={"@ÄÓÄÕÄÔÄÖÄ×"};
char PY_mb_ne    []={"@ÄØ"};
char PY_mb_nei   []={"@ÄÚÄÙ"};
char PY_mb_nen   []={"@ÄÛ"};
char PY_mb_neng  []={"@ÄÜ"};
char PY_mb_ni    []={"@ÄİÄáÄàÄßÄŞÄãÄâÄæÄäÄçÄå"};
char PY_mb_nian  []={"@ÄéÄêÄíÄìÄëÄîÄè"};
char PY_mb_niang []={"@ÄïÄğ"};
char PY_mb_niao  []={"@ÄñÄò"};
char PY_mb_nie   []={"@ÄóÄùÄôÄöÄ÷ÄøÄõ"};
char PY_mb_nin   []={"@Äú"};
char PY_mb_ning  []={"@ÄşÅ¡ÄüÄûÄıÅ¢"};
char PY_mb_niu   []={"@Å£Å¤Å¦Å¥"};
char PY_mb_nong  []={"@Å©Å¨Å§Åª"};
char PY_mb_nu    []={"@Å«Å¬Å­"};
char PY_mb_nuan  []={"@Å¯"};
char PY_mb_nue   []={"@Å±Å°"};
char PY_mb_nuo   []={"@Å²ÅµÅ³Å´"};
char PY_mb_nv    []={"@Å®"};
char PY_mb_o     []={"@Å¶"};
char PY_mb_ou    []={"@Å·Å¹Å¸Å»Å¼ÅºÅ½"};
char PY_mb_pa    []={"@Å¿Å¾ÅÀ°ÒÅÃÅÁÅÂ"};
char PY_mb_pai   []={"@ÅÄÅÇÅÅÅÆÅÉÅÈ"};
char PY_mb_pan   []={"@ÅËÅÊÅÌÅÍÅĞÅÑÅÎÅÏ"};
char PY_mb_pang  []={"@ÅÒÅÓÅÔÅÕÅÖ"};
char PY_mb_pao   []={"@Å×ÅÙÅØÅÚÅÛÅÜÅİ"};
char PY_mb_pei   []={"@ÅŞÅßÅãÅàÅâÅáÅæÅåÅä"};
char PY_mb_pen   []={"@ÅçÅè"};
char PY_mb_peng  []={"@ÅêÅéÅëÅóÅíÅïÅğÅîÅôÅìÅñÅòÅõÅö"};
char PY_mb_pi    []={"@±ÙÅúÅ÷ÅûÅøÅüÅùÆ¤ÅşÆ£Æ¡ÅıÆ¢Æ¥Æ¦Æ¨Æ§Æ©"};
char PY_mb_pian  []={"@Æ¬Æ«ÆªÆ­"};
char PY_mb_piao  []={"@Æ¯Æ®Æ°Æ±"};
char PY_mb_pie   []={"@Æ²Æ³"};
char PY_mb_pin   []={"@Æ´Æ¶ÆµÆ·Æ¸"};
char PY_mb_ping  []={"@Æ½ÆÀÆ¾ÆÁÆ¿ÆºÆ»Æ¼Æ¹"};
char PY_mb_po    []={"@ÆÂÆÃÆÄÆÅÆÈÆÆÆÉÆÇ"};
char PY_mb_pou   []={"@ÆÊ"};
char PY_mb_pu    []={"@¸¬ÆÍÆËÆÌÆÎÆĞÆÏÆÑÆÓÆÔÆÒÆÖÆÕÆ×ÆØ"};
char PY_mb_qi    []={"@ÆßÆãÆŞÆâÆàÆÜÆİÆÚÆÛÆáÆîÆëÆäÆæÆçÆíÆêÆéÆèÆïÆåÆìÆòÆóÆñÆôÆğÆøÆıÆùÆúÆûÆüÆõÆöÆ÷"};
char PY_mb_qia   []={"@ÆşÇ¡Ç¢"};
char PY_mb_qian  []={"@Ç§ÇªÇ¤Ç¨Ç¥Ç£Ç¦Ç«Ç©Ç°Ç®Ç¯Ç¬Ç±Ç­Ç³Ç²Ç´Ç·ÇµÇ¶Ç¸"};
char PY_mb_qiang []={"@ÇºÇ¼Ç¹Ç»Ç¿Ç½Ç¾ÇÀ"};
char PY_mb_qiao  []={"@ÇÄÇÃÇÂÇÁÇÇÇÈÇÅÇÆÇÉÇÎÇÍÇÏÇÌÇËÇÊ"};
char PY_mb_qie   []={"@ÇĞÇÑÇÒÇÓÇÔ"};
char PY_mb_qin   []={"@Ç×ÇÖÇÕÇÛÇØÇÙÇİÇÚÇÜÇŞÇß"};
char PY_mb_qing  []={"@ÇàÇâÇáÇãÇäÇåÇéÇçÇèÇæÇêÇëÇì"};
char PY_mb_qiong []={"@ÇîÇí"};
char PY_mb_qiu   []={"@ÇğÇñÇïÇôÇóÇöÇõÇò"};
char PY_mb_qu    []={"@ÇøÇúÇıÇüÇùÇûÇ÷ÇşÈ¡È¢È£È¥È¤"};
char PY_mb_quan  []={"@È¦È«È¨ÈªÈ­È¬È©È§È®È°È¯"};
char PY_mb_que   []={"@È²È±È³È´È¸È·ÈµÈ¶"};
char PY_mb_qun   []={"@È¹Èº"};
char PY_mb_ran   []={"@È»È¼È½È¾"};
char PY_mb_rang  []={"@È¿ÈÂÈÀÈÁÈÃ"};
char PY_mb_rao   []={"@ÈÄÈÅÈÆ"};
char PY_mb_re    []={"@ÈÇÈÈ"};
char PY_mb_ren   []={"@ÈËÈÊÈÉÈÌÈĞÈÏÈÎÈÒÈÑÈÍ"};
char PY_mb_reng  []={"@ÈÓÈÔ"};
char PY_mb_ri    []={"@ÈÕ"};
char PY_mb_rong  []={"@ÈÖÈŞÈ×ÈÙÈİÈÜÈØÈÛÈÚÈß"};
char PY_mb_rou   []={"@ÈáÈàÈâ"};
char PY_mb_ru    []={"@ÈçÈãÈåÈæÈäÈêÈéÈèÈëÈì"};
char PY_mb_ruan  []={"@ÈîÈí"};
char PY_mb_rui   []={"@ÈïÈñÈğ"};
char PY_mb_run   []={"@ÈòÈó"};
char PY_mb_ruo   []={"@ÈôÈõ"};
char PY_mb_sa    []={"@ÈöÈ÷Èø"};
char PY_mb_sai   []={"@ÈûÈùÈúÈü"};
char PY_mb_san   []={"@ÈıÉ¡É¢Èş"};
char PY_mb_sang  []={"@É£É¤É¥"};
char PY_mb_sao   []={"@É¦É§É¨É©"};
char PY_mb_se    []={"@É«É¬Éª"};
char PY_mb_sen   []={"@É­"};
char PY_mb_seng  []={"@É®"};
char PY_mb_sha   []={"@É±É³É´É°É¯ÉµÉ¶É·ÏÃ"};
char PY_mb_shai  []={"@É¸É¹"};
char PY_mb_shan  []={"@É½É¾É¼ÉÀÉºÉ¿ÉÁÉÂÉÇÉ»ÉÈÉÆÉÉÉÃÉÅÉÄÕ¤"};
char PY_mb_shang []={"@ÉËÉÌÉÊÉÑÉÎÉÍÉÏÉĞ"};
char PY_mb_shao  []={"@ÉÓÉÒÉÕÉÔÉ×ÉÖÉØÉÙÉÛÉÜÉÚ"};
char PY_mb_she   []={"@ÉİÉŞÉàÉßÉáÉèÉçÉäÉæÉâÉåÉã"};
char PY_mb_shen  []={"@ÉêÉìÉíÉëÉğÉïÉéÉîÉñÉòÉóÉôÉöÉõÉøÉ÷Ê²"};
char PY_mb_sheng []={"@ÉıÉúÉùÉüÊ¤ÉûÉşÊ¡Ê¥Ê¢Ê£"};
char PY_mb_shi   []={"@ÊÇÊ®Ê¯Ê±Ê¿Ê¶ÊÂÊ³Ê¾Ê½Ê¹Ê¼ÊÒÊÆÊµÊÓÊÔÊ·ÊÊÊ©ÊĞÊ»ÊªËÆ³×Ê¬Ê§ÊÅÊÍÊ¦Ê­Ê«Ê¨Ê°Ê´Ê¸ÊºÊÏÊÀÊËÊÌÊÎÊÑÊÃÊÁÊÈÊÄÊÉ"};
char PY_mb_shou  []={"@ÊÕÊÖÊØÊ×ÊÙÊÜÊŞÊÛÊÚÊİ"};
char PY_mb_shu   []={"@ÊéÊãÊåÊàÊâÊáÊçÊèÊæÊäÊßÊëÊêÊìÊîÊòÊğÊóÊñÊíÊïÊõÊùÊøÊöÊ÷ÊúË¡ÊüÊıÊûÊşÊô"};
char PY_mb_shua  []={"@Ë¢Ë£"};
char PY_mb_shuai []={"@Ë¥Ë¤Ë¦Ë§"};
char PY_mb_shuan []={"@Ë©Ë¨"};
char PY_mb_shuang[]={"@Ë«ËªË¬"};
char PY_mb_shui  []={"@Ë­Ë®Ë°Ë¯"};
char PY_mb_shun  []={"@Ë±Ë³Ë´Ë²"};
char PY_mb_shuo  []={"@ËµË¸Ë·Ë¶"};
char PY_mb_si    []={"@ËÄË¿Ë¾Ë½Ë¼Ë¹ËÀËºËÂË»ËÈËÅËÇËÃËÁ"};
char PY_mb_song  []={"@ËÍËÎËÉËÊËËËÏËĞËÌ"};
char PY_mb_sou   []={"@ËÔËÑËÒËÓ"};
char PY_mb_su    []={"@ËÕËÖË×ËßËàËØËÙËÚËÜËİËÛ"};
char PY_mb_suan  []={"@ËáËâËã"};
char PY_mb_sui   []={"@ËäËêËçËåËæËèËîËìËéËíËë"};
char PY_mb_sun   []={"@ËïËğËñ"};
char PY_mb_suo   []={"@ËôËóËòËõËùË÷ËöËø"};
char PY_mb_ta    []={"@ËıËûËüËúËşÌ¡Ì¢Ì¤Ì£"};
char PY_mb_tai   []={"@Ì¥Ì¨Ì§Ì¦Ì«Ì­Ì¬Ì©Ìª"};
char PY_mb_tan   []={"@Ì®Ì°Ì¯Ì²Ì±Ì³Ì¸ÌµÌ·Ì¶Ì´Ì¹Ì»ÌºÌ¾Ì¿Ì½Ì¼"};
char PY_mb_tang  []={"@ÌÀÌÆÌÃÌÄÌÁÌÂÌÅÌÇÌÈÌÊÌÉÌÌÌË"};
char PY_mb_tao   []={"@ÌÎÌĞÌÍÌÏÌÓÌÒÌÕÌÔÌÑÌÖÌ×"};
char PY_mb_te    []={"@ÌØ"};
char PY_mb_teng  []={"@ÌÛÌÚÌÜÌÙ"};
char PY_mb_ti    []={"@ÌŞÌİÌàÌßÌäÌáÌâÌãÌåÌëÌêÌéÌèÌæÌç"};
char PY_mb_tian  []={"@ÌìÌíÌïÌñÌğÌîÌóÌò"};
char PY_mb_tiao  []={"@µ÷ÌôÌõÌöÌ÷Ìø"};
char PY_mb_tie   []={"@ÌùÌúÌû"};
char PY_mb_ting  []={"@Í£ÌüÍ¡ÌıÌşÍ¢Í¤Í¥Í¦Í§"};
char PY_mb_tong  []={"@Í¨Í¬Í®Í©Í­Í¯ÍªÍ«Í³Í±Í°Í²Í´"};
char PY_mb_tou   []={"@ÍµÍ·Í¶Í¸"};
char PY_mb_tu    []={"@Í¹ÍºÍ»Í¼Í½Í¿Í¾ÍÀÍÁÍÂÍÃ"};
char PY_mb_tuan  []={"@ÍÄÍÅ"};
char PY_mb_tui   []={"@ÍÆÍÇÍÈÍËÍÉÍÊ"};
char PY_mb_tun   []={"@¶ÚÍÌÍÍÍÎ"};
char PY_mb_tuo   []={"@ÍĞÍÏÍÑÍÔÍÓÍÕÍÒÍ×ÍÖÍØÍÙ"};
char PY_mb_wa    []={"@ÍÛÍŞÍÚÍİÍÜÍßÍà"};
char PY_mb_wai   []={"@ÍâÍá"};
char PY_mb_wan   []={"@ÍòÍêÍæÍíÍäÍëÍåÍãÍèÍçÍéÍğÍìÍñÍïÍîÍó"};
char PY_mb_wang  []={"@ÍõÍøÍùÍüÍúÍûÍôÍöÍ÷Íı"};
char PY_mb_wei   []={"@Î£ÍşÎ¢Î¡ÎªÎ¤Î§Î¥Î¦Î¨Î©Î¬Î«Î°Î±Î²Î³Î­Î¯Î®ÎÀÎ´Î»Î¶Î·Î¸Î¾Î½Î¹Î¼ÎµÎ¿Îº"};
char PY_mb_wen   []={"@ÎÂÎÁÎÄÎÆÎÅÎÃÎÇÎÉÎÈÎÊ"};
char PY_mb_weng  []={"@ÎÌÎËÎÍ"};
char PY_mb_wo    []={"@ÎÒÎÖÎÔÎÑÎÕÎĞÎÏÎÓÎÎ"};
char PY_mb_wu    []={"@ÎåÎâÎóÎŞÎİÎäÎçÎÚÎÛÎØÎ×ÎÜÎÙÎãÎáÎßÎàÎéÎëÎêÎæÎèÎğÎñÎìÎïÎòÎîÎí"};
char PY_mb_xi    []={"@Ï¦Ï«Î÷ÎüÏ£ÎôÎöÎùÏ¢ÎşÏ¤Ï§Ï©ÎøÎúÏ¬Ï¡ÏªÎıÏ¨ÎõÎûÏ¥Ï°Ï¯Ï®Ï±Ï­Ï´Ï²Ï·ÏµÏ¸Ï¶"};
char PY_mb_xia   []={"@ÏºÏ¹Ï»ÏÀÏ¿ÏÁÏ¾Ï½Ï¼ÏÂÏÅÏÄ"};
char PY_mb_xian  []={"@Ï³ÏÉÏÈÏËÏÆÏÇÏÊÏĞÏÒÏÍÏÌÏÑÏÏÏÎÏÓÏÔÏÕÏØÏÖÏßÏŞÏÜÏİÏÚÏÛÏ×ÏÙ"};
char PY_mb_xiang []={"@ÏçÏàÏãÏáÏæÏäÏåÏâÏêÏéÏèÏíÏìÏëÏòÏïÏîÏóÏñÏğ"};
char PY_mb_xiao  []={"@ÏüÏûÏôÏõÏúÏöÏùÏıĞ¡ÏşĞ¢Ğ¤ÏøĞ§Ğ£Ğ¦Ğ¥"};
char PY_mb_xie   []={"@Ğ©Ğ¨ĞªĞ«Ğ­Ğ°Ğ²Ğ±Ğ³Ğ¯Ğ¬Ğ´Ğ¹ĞºĞ¶Ğ¼ĞµĞ»Ğ¸Ğ·"};
char PY_mb_xin   []={"@ĞÄĞÃĞ¾ĞÁĞÀĞ¿ĞÂĞ½ĞÅĞÆ"};
char PY_mb_xing  []={"@ĞËĞÇĞÊĞÉĞÈĞÌĞÏĞÎĞÍĞÑĞÓĞÕĞÒĞÔ"};
char PY_mb_xiong []={"@Ğ×ĞÖĞÙĞÚĞØĞÛĞÜ"};
char PY_mb_xiu   []={"@ËŞĞİĞŞĞßĞàĞãĞåĞäĞâĞá"};
char PY_mb_xu    []={"@ĞçĞëĞéĞêĞèĞæĞìĞíĞñĞòĞğĞôĞ÷ĞøĞïĞöĞõĞîÓõ"};
char PY_mb_xuan  []={"@ĞùĞûĞúĞşĞüĞıÑ¡Ñ¢Ñ¤Ñ£"};
char PY_mb_xue   []={"@Ñ§Ñ©ÑªÏ÷Ñ¥Ñ¦Ñ¨"};
char PY_mb_xun   []={"@Ñ°Ñ®Ñ¸Ñ¯Ñ¶Ñ«Ñ¬Ñ²Ñ±Ñ­ÑµÑ´Ñ·Ñ³"};
char PY_mb_ya    []={"@Ñ½Ñ¹ÑÀÑÇÑÅÑ¾ÑºÑ»Ñ¼Ñ¿ÑÁÑÂÑÄÑÃÑÆÑÈ"};
char PY_mb_yan   []={"@ÑÊÑÌÑÍÑÉÑËÑÓÑÏÑÔÑÒÑØÑ×ÑĞÑÎÑÖÑÑÑÕÑÙÑÜÑÚÑÛÑİÑáÑåÑâÑäÑçÑŞÑéÑèÑßÑæÑãÑà"};
char PY_mb_yang  []={"@ÑôÑïÑîÑùÑøÑòÑëÑêÑíÑìÑğÑñÑóÑöÑõÑ÷Ñú"};
char PY_mb_yao   []={"@½ÄÑıÑüÑûÒ¢Ò¦Ò¤Ò¥Ò¡Ò£ÑşÒ§Ò¨Ò©ÒªÒ«Ô¿"};
char PY_mb_ye    []={"@Ò¬Ò­Ò¯Ò®Ò²Ò±Ò°ÒµÒ¶Ò·Ò³Ò¹Ò´ÒºÒ¸"};
char PY_mb_yi    []={"@Ò»ÒÁÒÂÒ½ÒÀÒ¿Ò¼Ò¾ÒÇÒÄÒÊÒËÒÌÒÈÒÆÒÅÒÃÒÉÒÍÒÒÒÑÒÔÒÓÒÏÒĞÒÎÒåÒÚÒäÒÕÒéÒàÒÙÒìÒÛÒÖÒëÒØÒ×ÒïÒèÒßÒæÒêÒîÒİÒâÒçÒŞÒáÒãÒíÒÜ"};
char PY_mb_yin   []={"@ÒòÒõÒöÒğÒñÒôÒóÒ÷ÒúÒùÒøÒüÒıÒûÒşÓ¡"};
char PY_mb_ying  []={"@Ó¦Ó¢Ó¤Ó§Ó£Ó¥Ó­Ó¯Ó«Ó¨Ó©ÓªÓ¬Ó®Ó±Ó°Ó³Ó²"};
char PY_mb_yo    []={"@Ó´"};
char PY_mb_yong  []={"@Ó¶ÓµÓ¸Ó¹ÓºÓ·ÓÀÓ½Ó¾ÓÂÓ¿ÓÁÓ¼Ó»ÓÃ"};
char PY_mb_you   []={"@ÓÅÓÇÓÄÓÆÓÈÓÉÓÌÓÊÓÍÓËÓÎÓÑÓĞÓÏÓÖÓÒÓ×ÓÓÓÕÓÔ"};
char PY_mb_yu    []={"@ÓØÓÙÓåÓÚÓèÓàÓÛÓãÓáÓéÓæÓçÓäÓâÓŞÓÜÓİÓßÓëÓîÓìÓğÓêÓíÓïÓñÔ¦ÓóÓıÓôÓüÓøÔ¡Ô¤ÓòÓûÓ÷Ô¢ÓùÔ£ÓöÓúÓşÔ¥"};
char PY_mb_yuan  []={"@Ô©Ô§Ô¨ÔªÔ±Ô°Ô«Ô­Ô²Ô¬Ô®ÔµÔ´Ô³Ô¯Ô¶Ô·Ô¹ÔºÔ¸"};
char PY_mb_yue   []={"@Ô»Ô¼ÔÂÔÀÔÃÔÄÔ¾ÔÁÔ½"};
char PY_mb_yun   []={"@ÔÆÔÈÔÇÔÅÔÊÔÉÔĞÔËÔÎÔÍÔÏÔÌ"};
char PY_mb_za    []={"@ÔÑÔÓÔÒÕ¦"};
char PY_mb_zai   []={"@ÔÖÔÕÔÔÔ×ÔØÔÙÔÚ×Ğ"};
char PY_mb_zan   []={"@ÔÛÔÜÔİÔŞ"};
char PY_mb_zang  []={"@ÔßÔàÔá"};
char PY_mb_zao   []={"@ÔâÔãÔäÔçÔæÔéÔèÔåÔîÔíÔìÔëÔïÔê"};
char PY_mb_ze    []={"@ÔòÔñÔóÔğ"};
char PY_mb_zei   []={"@Ôô"};
char PY_mb_zen   []={"@Ôõ"};
char PY_mb_zeng  []={"@ÔöÔ÷Ôù"};
char PY_mb_zha   []={"@ÔûÔüÔúÔıÔşÕ¢Õ¡Õ£Õ§Õ©Õ¨Õ¥×õ"};
char PY_mb_zhai  []={"@Õ«ÕªÕ¬µÔÕ­Õ®Õ¯"};
char PY_mb_zhan  []={"@Õ´Õ±Õ³Õ²Õ°Õ¶Õ¹ÕµÕ¸Õ·Õ¼Õ½Õ»Õ¾ÕÀÕ¿Õº"};
char PY_mb_zhang []={"@³¤ÕÅÕÂÕÃÕÄÕÁÕÇÕÆÕÉÕÌÕÊÕÈÕÍÕËÕÏÕÎ"};
char PY_mb_zhao  []={"@ÕĞÕÑÕÒÕÓÕÙÕ×ÕÔÕÕÕÖÕØ×¦"};
char PY_mb_zhe   []={"@ÕÚÕÛÕÜÕİÕŞÕßÕàÕâÕãÕá×Å"};
char PY_mb_zhen  []={"@ÕêÕëÕìÕäÕæÕèÕåÕçÕéÕïÕíÕîÕóÕñÕòÕğÖ¡"};
char PY_mb_zheng []={"@ÕùÕ÷ÕúÕõÕøÕöÕôÕüÕûÕıÖ¤Ö£ÕşÖ¢"};
char PY_mb_zhi   []={"@Ö®Ö§Ö­Ö¥Ö¨Ö¦ÖªÖ¯Ö«Ö¬Ö©Ö´Ö¶Ö±ÖµÖ°Ö²Ö³Ö¹Ö»Ö¼Ö·Ö½Ö¸ÖºÖÁÖ¾ÖÆÖÄÖÎÖËÖÊÖÅÖ¿ÖÈÖÂÖÀÖÌÖÏÖÇÖÍÖÉÖÃ"};
char PY_mb_zhong []={"@ÖĞÖÒÖØÖÕÖÑÖÓÖÔÖ×ÖÖÖÙÖÚ"};
char PY_mb_zhou  []={"@ÖİÖÛÖßÖÜÖŞÖàÖáÖâÖãÖäÖæÖçÖåÖè"};
char PY_mb_zhu   []={"@Ö÷×¡×¢×£ÖìÖíÖúÖùÖñÖğÖêÖéÖöÖøÖîÖëÖòÖïÖôÖóÖõÖü×¤ÖûÖşÖı"};
char PY_mb_zhua  []={"@×¥"};
char PY_mb_zhuai []={"@×§"};
char PY_mb_zhuan []={"@×¨×©×ª×«×­"};
char PY_mb_zhuang[]={"@×±×¯×®×°×³×´´±×²"};
char PY_mb_zhui  []={"@×·×¹×µ×¶×º×¸"};
char PY_mb_zhun  []={"@×¼×»"};
char PY_mb_zhuo  []={"@×¿×¾×½×À×Æ×Â×Ç×Ã×Ä×Á"};
char PY_mb_zi    []={"@×Î×È×É×Ë×Ê×Í×Ì×Ñ×Ó×Ï×Ò×Ö×Ô×Õ"};
char PY_mb_zong  []={"@×Ú×Û×Ø×Ù×××Ü×İ"};
char PY_mb_zou   []={"@×ß×à×Ş×á"};
char PY_mb_zu    []={"@×â×ã×ä×å×ç×è×é×æ"};
char PY_mb_zuan  []={"@×¬×ê×ë"};
char PY_mb_zui   []={"@×ì×î×ï×í"};
char PY_mb_zun   []={"@×ğ×ñ"};
char PY_mb_zuo   []={"@×ò×ó×ô×÷×ø×ù×ö"};

//0-396,397
//Æ´ÒôÊäÈë·¨²éÑ¯Âë±í,T9Êı×Ö×ÖÄ¸Ë÷Òı±í(index),
//Ê÷ĞÎÅÅÁĞ
t9PY_index t9PY_index2[] ={
{""		,	"0"	    ,	PY_mb_space},
{"2"		,	"a"	    ,	PY_mb_a},
{"22"	,	"ba"	,	PY_mb_ba},
{"22"	,	"ca"	,	PY_mb_ca},
{"224"	,	"bai"	,	PY_mb_bai},
{"224"	,	"cai"	,	PY_mb_cai},
{"226"	,	"ban"	,	PY_mb_ban},
{"226"	,	"bao"	,	PY_mb_bao},
{"226"	,	"can"	,	PY_mb_can},
{"226"	,	"cao"	,	PY_mb_cao},
{"2264"	,	"bang"	,	PY_mb_bang},
{"2264"	,	"cang"	,	PY_mb_cang},
{"23"	,	"ce"	,	PY_mb_ce},
{"234"	,	"bei"	,	PY_mb_bei},
{"236"	,	"ben"	,	PY_mb_ben},
{"2364"	,	"beng"	,	PY_mb_beng},
{"2364"	,	"ceng"	,	PY_mb_ceng},
{"24"	,	"ai"	,	PY_mb_ai},
{"24"	,	"bi"	,	PY_mb_bi},
{"24"	,	"ci"	,	PY_mb_ci},
{"242"	,	"cha"	,	PY_mb_cha},
{"2424"	,	"chai"	,	PY_mb_chai},
{"2426"	,	"bian"	,	PY_mb_bian},
{"2426"	,	"biao"	,	PY_mb_biao},
{"2426"	,	"chan"	,	PY_mb_chan},
{"2426"	,	"chao"	,	PY_mb_chao},
{"24264"	,	"chang"	,	PY_mb_chang},
{"243"	,	"bie"	,	PY_mb_bie},
{"243"	,	"che"	,	PY_mb_che},
{"2436"	,	"chen"	,	PY_mb_chen},
{"24364"	,	"cheng"	,	PY_mb_cheng},
{"244"	,	"chi"	,	PY_mb_chi},
{"246"	,	"bin"	,	PY_mb_bin},
{"2464"	,	"bing"	,	PY_mb_bing},
{"24664"	,	"chong"	,	PY_mb_chong},
{"2468"	,	"chou"	,	PY_mb_chou},
{"248"	,	"chu"	,	PY_mb_chu},
{"24826"	,	"chuan"	,	PY_mb_chuan},
{"248264"	,	"chuang",	PY_mb_chuang},
{"2484"	,	"chuai"	,	PY_mb_chuai},
{"2484"	,	"chui"	,	PY_mb_chui},
{"2484"	,	"chun"	,	PY_mb_chun},
{"2486"	,	"chuo"	,	PY_mb_chuo},
{"26"	,	"an"	,	PY_mb_an},
{"26"	,	"ao"	,	PY_mb_ao},
{"26"	,	"bo"	,	PY_mb_bo},
{"264"	,	"ang"	,	PY_mb_ang},
{"2664"	,	"cong"	,	PY_mb_cong},
{"268"	,	"cou"	,	PY_mb_cou},
{"28"	,	"bu"	,	PY_mb_bu},
{"28"	,	"cu"	,	PY_mb_cu},
{"2826"	,	"cuan"	,	PY_mb_cuan},
{"284"	,	"cui"	,	PY_mb_cui},
{"286"	,	"cun"	,	PY_mb_cun},
{"286"	,	"cuo"	,	PY_mb_cuo},
{"3"	,	"e"	    ,	PY_mb_e},
{"32"	,	"da"	,	PY_mb_da},
{"32"	,	"fa"	,	PY_mb_fa},
{"324"	,	"dai"	,	PY_mb_dai},
{"326"	,	"dan"	,	PY_mb_dan},
{"326"	,	"dao"	,	PY_mb_dao},
{"326"	,	"fan"	,	PY_mb_fan},
{"3264"	,	"dang"	,	PY_mb_dang},
{"3264"	,	"fang"	,	PY_mb_fang},
{"33"	,	"de"	,	PY_mb_de},
{"334"	,	"fei"	,	PY_mb_fei},
{"336"	,	"fen"	,	PY_mb_fen},
{"3364"	,	"deng"	,	PY_mb_deng},
{"3364"	,	"feng"	,	PY_mb_feng},
{"34"	,	"di"	,	PY_mb_di},
{"3426"	,	"dian"	,	PY_mb_dian},
{"3426"	,	"diao"	,	PY_mb_diao},
{"343"	,	"die"	,	PY_mb_die},
{"3464"	,	"ding"	,	PY_mb_ding},
{"348"	,	"diu"	,	PY_mb_diu},
{"36"	,	"en"	,	PY_mb_en},
{"36"	,	"fo"	,	PY_mb_fo},
{"3664"	,	"dong"	,	PY_mb_dong},
{"368"	,	"dou"	,	PY_mb_dou},
{"368"	,	"fou"	,	PY_mb_fou},
{"37"	,	"er"	,	PY_mb_er},
{"38"	,	"du"	,	PY_mb_du},
{"38"	,	"fu"	,	PY_mb_fu},
{"3826"	,	"duan"	,	PY_mb_duan},
{"384"	,	"dui"	,	PY_mb_dui},
{"386"	,	"dun"	,	PY_mb_dun},
{"386"	,	"duo"	,	PY_mb_duo},
//{"4"	,	"i"	,	PY_mb_space},
{"42"	,	"ha"	,	PY_mb_ha},
{"42"	,	"ga"	,	PY_mb_ga},
{"423"	,	"hai"	,	PY_mb_hai},
{"424"	,	"gai"	,	PY_mb_gai},
{"426"	,	"gan"	,	PY_mb_gan},
{"426"	,	"gao"	,	PY_mb_gao},
{"426"	,	"han"	,	PY_mb_han},
{"426"	,	"hao"	,	PY_mb_hao},
{"4264"	,	"gang"	,	PY_mb_gang},
{"4264"	,	"hang"	,	PY_mb_hang},
{"43"	,	"ge"	,	PY_mb_ge},
{"43"	,	"he"	,	PY_mb_he},
{"434"	,	"gei"	,	PY_mb_gei},
{"434"	,	"hei"	,	PY_mb_hei},
{"436"	,	"gen"	,	PY_mb_gan},
{"436"	,	"hen"	,	PY_mb_hen},
{"4364"	,	"geng"	,	PY_mb_geng},
{"4364"	,	"heng"	,	PY_mb_heng},
{"4664"	,	"gong"	,	PY_mb_gong},
{"4664"	,	"hong"	,	PY_mb_hong},
{"468"	,	"gou"	,	PY_mb_gou},
{"468"	,	"hou"	,	PY_mb_hou},
{"48"	,	"gu"	,	PY_mb_gu},
{"48"	,	"hu"	,	PY_mb_hu},
{"482"	,	"gua"	,	PY_mb_gua},
{"482"	,	"hua"	,	PY_mb_hua},
{"4823"	,	"huai"	,	PY_mb_huai},
{"4824"	,	"guai"	,	PY_mb_guai},
{"4826"	,	"guan"	,	PY_mb_guan},
{"4826"	,	"huan"	,	PY_mb_huan},
{"48264"	,	"guang"	,	PY_mb_guang},
{"48264"	,	"huang"	,	PY_mb_huang},
{"484"	,	"gui"	,	PY_mb_gui},
{"484"	,	"hui"	,	PY_mb_hui},
{"486"	,	"gun"	,	PY_mb_gun},
{"486"	,	"guo"	,	PY_mb_guo},
{"486"	,	"hun"	,	PY_mb_hun},
{"486"	,	"huo"	,	PY_mb_huo},
{"52"	,	"ka"	,	PY_mb_ka},
{"52"	,	"la"	,	PY_mb_la},
{"524"	,	"kai"	,	PY_mb_kai},
{"524"	,	"lai"	,	PY_mb_lai},
{"526"	,	"kan"	,	PY_mb_kan},
{"526"	,	"kao"	,	PY_mb_kao},
{"526"	,	"lan"	,	PY_mb_lan},
{"526"	,	"lao"	,	PY_mb_lao},
{"5264"	,	"kang"	,	PY_mb_kang},
{"5264"	,	"lang"	,	PY_mb_lang},
{"53"	,	"ke"	,	PY_mb_ke},
{"53"	,	"le"	,	PY_mb_le},
{"534"	,	"lei"	,	PY_mb_lei},
{"536"	,	"ken"	,	PY_mb_ken},
{"5364"	,	"keng"	,	PY_mb_keng},
{"5366"	,	"leng"	,	PY_mb_leng},
{"54"	,	"ji"	,	PY_mb_ji},
{"54"	,	"li"	,	PY_mb_li},
{"542"	,	"jia"	,	PY_mb_jia},
{"5426"	,	"jian"	,	PY_mb_jian},
{"5426"	,	"jiao"	,	PY_mb_jiao},
{"5426"	,	"lian"	,	PY_mb_lian},
{"5426"	,	"liao"	,	PY_mb_liao},
{"54264"	,	"jiang"	,	PY_mb_jiang},
{"54264"	,	"liang"	,	PY_mb_liang},
{"543"	,	"jie"	,	PY_mb_jie},
{"543"	,	"lie"	,	PY_mb_lie},
{"546"	,	"jin"	,	PY_mb_jin},
{"546"	,	"lin"	,	PY_mb_lin},
{"5464"	,	"jing"	,	PY_mb_jing},
{"5464"	,	"ling"	,	PY_mb_ling},
{"54664"	,	"jiong"	,	PY_mb_jiong},
{"548"	,	"jiu"	,	PY_mb_jiu},
{"548"	,	"liu"	,	PY_mb_liu},
{"5664"	,	"kong"	,	PY_mb_kong},
{"5664"	,	"long"	,	PY_mb_long},
{"568"	,	"kou"	,	PY_mb_kou},
{"568"	,	"lou"	,	PY_mb_lou},
{"58"	,	"ju"	,	PY_mb_ju},
{"58"	,	"ku"	,	PY_mb_ku},
{"58"	,	"lu"	,	PY_mb_lu},
{"58"	,	"lv"	,	PY_mb_lv},
{"582"	,	"kua"	,	PY_mb_kua},
{"5824"	,	"kuai"	,	PY_mb_kuai},
{"5826"	,	"juan"	,	PY_mb_juan},
{"5826"	,	"kuan"	,	PY_mb_kuan},
{"5826"	,	"luan"	,	PY_mb_luan},
{"58264"	,	"kuang"	,	PY_mb_kuang},
{"583"	,	"jue"	,	PY_mb_jue},
{"583"	,	"lue"	,	PY_mb_lue},
{"584"	,	"kui"	,	PY_mb_kui},
{"586"	,	"jun"	,	PY_mb_jun},
{"586"	,	"kun"	,	PY_mb_kun},
{"586"	,	"kuo"	,	PY_mb_kuo},
{"586"	,	"lun"	,	PY_mb_lun},
{"586"	,	"luo"	,	PY_mb_luo},
{"6"	,	"o"	    ,	PY_mb_o},
{"62"	,	"ma"	,	PY_mb_ma},
{"62"	,	"na"	,	PY_mb_na},
{"624"	,	"mai"	,	PY_mb_mai},
{"624"	,	"nai"	,	PY_mb_nai},
{"626"	,	"man"	,	PY_mb_man},
{"626"	,	"mao"	,	PY_mb_mao},
{"626"	,	"nan"	,	PY_mb_nan},
{"626"	,	"nao"	,	PY_mb_nao},
{"6264"	,	"mang"	,	PY_mb_mang},
{"6264"	,	"nang"	,	PY_mb_nang},
{"63"	,	"me"	,	PY_mb_me},
{"63"	,	"ne"	,	PY_mb_ne},
{"634"	,	"mei"	,	PY_mb_mei},
{"634"	,	"nei"	,	PY_mb_nei},
{"636"	,	"men"	,	PY_mb_men},
{"636"	,	"nen"	,	PY_mb_nen},
{"6364"	,	"meng"	,	PY_mb_meng},
{"6364"	,	"neng"	,	PY_mb_neng},
{"64"	,	"mi"	,	PY_mb_mi},
{"64"	,	"ni"	,	PY_mb_ni},
{"6426"	,	"mian"	,	PY_mb_mian},
{"6426"	,	"miao"	,	PY_mb_miao},
{"6426"	,	"nian"	,	PY_mb_nian},
{"6426"	,	"niao"	,	PY_mb_niao},
{"64264"	,	"niang"	,	PY_mb_niang},
{"643"	,	"mie"	,	PY_mb_mie},
{"643"	,	"nie"	,	PY_mb_nie},
{"646"	,	"min"	,	PY_mb_min},
{"646"	,	"nin"	,	PY_mb_nin},
{"6464"	,	"ming"	,	PY_mb_ming},
{"6464"	,	"ning"	,	PY_mb_ning},
{"648"	,	"miu"	,	PY_mb_miu},
{"648"	,	"niu"	,	PY_mb_niu},
{"66"	,	"mo"	,	PY_mb_mo},
{"6664"	,	"nong"	,	PY_mb_nong},
{"668"	,	"mou"	,	PY_mb_mou},
{"68"	,	"mu"	,	PY_mb_mu},
{"68"	,	"nu"	,	PY_mb_nu},
{"68"	,	"nv"	,	PY_mb_nv},
{"68"	,	"ou"	,	PY_mb_ou},
{"6826"	,	"nuan"	,	PY_mb_nuan},
{"683"	,	"nue"	,	PY_mb_nue},
{"686"	,	"nuo"	,	PY_mb_nuo},
{"72"	,	"pa"	,	PY_mb_pa},
{"72"	,	"sa"	,	PY_mb_sa},
{"724"	,	"pai"	,	PY_mb_pai},
{"724"	,	"sai"	,	PY_mb_sai},
{"726"	,	"pan"	,	PY_mb_pan},
{"726"	,	"pao"	,	PY_mb_pao},
{"726"	,	"ran"	,	PY_mb_ran},
{"726"	,	"rao"	,	PY_mb_rao},
{"726"	,	"sao"	,	PY_mb_sao},
{"726"	,	"san"	,	PY_mb_san},
{"7264"	,	"pang"	,	PY_mb_pang},
{"7264"	,	"rang"	,	PY_mb_rang},
{"7264"	,	"sang"	,	PY_mb_sang},
{"73"	,	"re"	,	PY_mb_re},
{"73"	,	"se"	,	PY_mb_se},
{"734"	,	"pei"	,	PY_mb_pei},
{"736"	,	"pen"	,	PY_mb_pen},
{"736"	,	"ren"	,	PY_mb_ren},
{"736"	,	"sen"	,	PY_mb_sen},
{"7364"	,	"peng"	,	PY_mb_peng},
{"7364"	,	"reng"	,	PY_mb_reng},
{"7364"	,	"seng"	,	PY_mb_seng},
{"74"	,	"pi"	,	PY_mb_pi},
{"74"	,	"qi"	,	PY_mb_qi},
{"74"	,	"ri"	,	PY_mb_ri},
{"74"	,	"si"	,	PY_mb_si},
{"742"	,	"qia"	,	PY_mb_qia},
{"742"	,	"sha"	,	PY_mb_sha},
{"7424"	,	"shai"	,	PY_mb_shai},
{"7426"	,	"pian"	,	PY_mb_pian},
{"7426"	,	"piao"	,	PY_mb_piao},
{"7426"	,	"qian"	,	PY_mb_qian},
{"7426"	,	"qiao"	,	PY_mb_qiao},
{"7426"	,	"shan"	,	PY_mb_shan},
{"7426"	,	"shao"	,	PY_mb_shao},
{"74264"	,	"qiang"	,	PY_mb_qiang},
{"74264"	,	"shang ",	PY_mb_shang},
{"743"	,	"pie"	,	PY_mb_pie},
{"743"	,	"qie"	,	PY_mb_qie},
{"743"	,	"she"	,	PY_mb_she},
{"7436"	,	"shen"	,	PY_mb_shen},
{"74364"	,	"sheng"	,	PY_mb_sheng},
{"744"	,	"shi"	,	PY_mb_shi},
{"746"	,	"pin"	,	PY_mb_pin},
{"746"	,	"qin"	,	PY_mb_qin},
{"7464"	,	"ping"	,	PY_mb_ping},
{"7464"	,	"qing"	,	PY_mb_qing},
{"74664"	,	"qiong"	,	PY_mb_qiong},
{"7468"	,	"shou"	,	PY_mb_shou},
{"748"	,	"qiu"	,	PY_mb_qiu},
{"748"	,	"shu"	,	PY_mb_shu},
{"7482"	,	"shua"	,	PY_mb_shua},
{"74824"	,	"shuai"	,	PY_mb_shuai},
{"74826"	,	"shuan"	,	PY_mb_shuan},
{"748264"	,	"shuang",	PY_mb_shuang},
{"7484"	,	"shui"	,	PY_mb_shui},
{"7486"	,	"shun"	,	PY_mb_shun},
{"7486"	,	"shuo"	,	PY_mb_shuo},
{"76"	,	"po"	,	PY_mb_po},
{"7664"	,	"rong"	,	PY_mb_rong},
{"7664"	,	"song"	,	PY_mb_song},
{"768"	,	"pou"	,	PY_mb_pou},
{"768"	,	"rou"	,	PY_mb_rou},
{"768"	,	"sou"	,	PY_mb_sou},
{"78"	,	"pu"	,	PY_mb_pu},
{"78"	,	"qu"	,	PY_mb_qu},
{"78"	,	"ru"	,	PY_mb_ru},
{"78"	,	"su"	,	PY_mb_su},
{"7826"	,	"quan"	,	PY_mb_quan},
{"7826"	,	"ruan"	,	PY_mb_ruan},
{"7826"	,	"suan"	,	PY_mb_suan},
{"783"	,	"que"	,	PY_mb_que},
{"784"	,	"rui"	,	PY_mb_rui},
{"784"	,	"sui"	,	PY_mb_sui},
{"786"	,	"qun"	,	PY_mb_qun},
{"786"	,	"run"	,	PY_mb_run},
{"786"	,	"ruo"	,	PY_mb_ruo},
{"786"	,	"sun"	,	PY_mb_sun},
{"786"	,	"suo"	,	PY_mb_suo},
//{"8"	,	"u"	,	PY_mb_space},
//{"8"	,	"v"	,	PY_mb_space},
{"82"	,	"ta"	,	PY_mb_ta},
{"824"	,	"tai"	,	PY_mb_tai},
{"826"	,	"tan"	,	PY_mb_tan},
{"826"	,	"tao"	,	PY_mb_tao},
{"8264"	,	"tang"	,	PY_mb_tang},
{"83"	,	"te"	,	PY_mb_te},
{"8364"	,	"teng"	,	PY_mb_teng},
{"84"	,	"ti"	,	PY_mb_ti},
{"8426"	,	"tian"	,	PY_mb_tian},
{"8426"	,	"tiao"	,	PY_mb_tiao},
{"843"	,	"tie"	,	PY_mb_tie},
{"8464"	,	"ting"	,	PY_mb_ting},
{"8664"	,	"tong"	,	PY_mb_tong},
{"868"	,	"tou"	,	PY_mb_tou},
{"88"	,	"tu"	,	PY_mb_tu},
{"8826"	,	"tuan"	,	PY_mb_tuan},
{"884"	,	"tui"	,	PY_mb_tui},
{"886"	,	"tun"	,	PY_mb_tun},
{"886"	,	"tuo"	,	PY_mb_tuo},
{"92"	,	"wa"	,	PY_mb_wa},
{"92"	,	"ya"	,	PY_mb_ya},
{"92"	,	"za"	,	PY_mb_za},
{"924"	,	"wai"	,	PY_mb_wai},
{"924"	,	"zai"	,	PY_mb_zai},
{"926"	,	"wan"	,	PY_mb_wan},
{"926"	,	"yan"	,	PY_mb_yan},
{"926"	,	"yao"	,	PY_mb_yao},
{"926"	,	"zan"	,	PY_mb_zan},
{"926"	,	"zao"	,	PY_mb_zao},
{"9264"	,	"wang"	,	PY_mb_wang},
{"9264"	,	"yang"	,	PY_mb_yang},
{"9264"	,	"zang"	,	PY_mb_zang},
{"93"	,	"ye"	,	PY_mb_ye},
{"93"	,	"ze"	,	PY_mb_ze},
{"934"	,	"wei"	,	PY_mb_wei},
{"934"	,	"zei"	,	PY_mb_zei},
{"936"	,	"wen"	,	PY_mb_wen},
{"936"	,	"zen"	,	PY_mb_zen},
{"9364"	,	"weng"	,	PY_mb_weng},
{"9364"	,	"zeng"	,	PY_mb_zeng},
{"94"	,	"xi"	,	PY_mb_xi},
{"94"	,	"yi"	,	PY_mb_yi},
{"94"	,	"zi"	,	PY_mb_zi},
{"942"	,	"xia"	,	PY_mb_xia},
{"942"	,	"zha"	,	PY_mb_zha},
{"9424"	,	"zhai"	,	PY_mb_zhai},
{"9426"	,	"xian"	,	PY_mb_xiao},
{"9426"	,	"xiao"	,	PY_mb_xiao},
{"9426"	,	"zhan"	,	PY_mb_zhan},
{"9426"	,	"zhao"	,	PY_mb_zhao},
{"94264"	,	"xiang"	,	PY_mb_xiang},
{"94264"	,	"zhang"	,	PY_mb_zhang},
{"943"	,	"xie"	,	PY_mb_xie},
{"943"	,	"zhe"	,	PY_mb_zhe},
{"9436"	,	"zhen"	,	PY_mb_zhen},
{"94364"	,	"zheng"	,	PY_mb_zheng},
{"944"	,	"zhi"	,	PY_mb_zhi},
{"946"	,	"xin"	,	PY_mb_xin},
{"946"	,	"yin"	,	PY_mb_yin},
{"9464"	,	"xing"	,	PY_mb_xing},
{"9464"	,	"ying"	,	PY_mb_ying},
{"94664"	,	"xiong"	,	PY_mb_xiong},
{"94664"	,	"zhong"	,	PY_mb_zhong},
{"9468"	,	"zhou"	,	PY_mb_zhou},
{"948"	,	"xiu"	,	PY_mb_xiu},
{"948"	,	"zhu"	,	PY_mb_zhu},
{"9482"	,	"zhua"	,	PY_mb_zhua},
{"94824"	,	"zhuai"	,	PY_mb_zhuai},
{"94826"	,	"zhuan"	,	PY_mb_zhuan},
{"948264"	,	"zhuang",	PY_mb_zhuang},
{"9484"	,	"zhui"	,	PY_mb_zhui},
{"9486"	,	"zhun"	,	PY_mb_zhun},
{"9486"	,	"zhuo"	,	PY_mb_zhuo},
{"96"	,	"wo"	,	PY_mb_wo},
{"96"	,	"yo"	,	PY_mb_yo},
{"9664"	,	"yong"	,	PY_mb_yong},
{"9664"	,	"zong"	,	PY_mb_zong},
{"968"	,	"you"	,	PY_mb_you},
{"968"	,	"zou"	,	PY_mb_zou},
{"98"	,	"wu"	,	PY_mb_wu},
{"98"	,	"xu"	,	PY_mb_xu},
{"98"	,	"yu"	,	PY_mb_yu},
{"98"	,	"zu"	,	PY_mb_zu},
{"9826"	,	"xuan"	,	PY_mb_xuan},
{"9826"	,	"yuan"	,	PY_mb_yuan},
{"9826"	,	"zuan"	,	PY_mb_zuan},
{"983"	,	"xue"	,	PY_mb_xue},
{"983"	,	"yue"	,	PY_mb_yue},
{"984"	,	"zui"	,	PY_mb_zui},
{"986"	,	"xun"	,	PY_mb_xun},
{"986"	,	"yun"	,	PY_mb_yun},
{"986"	,	"zun"	,	PY_mb_zun},
{"986"	,	"zuo"	,	PY_mb_zuo},
{""		,	""	    ,	PY_mb_space},
};


#ifdef __cplusplus
}
#endif

#endif

