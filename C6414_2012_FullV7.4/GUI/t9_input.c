
#include <stdio.h>

#include <string.h>
#include "GUI_header/t9_input.h"


//#define my_strlen(ptr) strlen(ptr)
//¼ÆËã×Ö·û´®³¤¶ÈµÄº¯Êı£¬ÓÃ»§¿ÉÒÔÍ¨¹ıºê¶¨ÒåÒıÓÃº¯Êı¿âµÄº¯Êı
//static unsigned int my_strlen(char*str)
//{
//   unsigned int count=0;
//   while(*str++) {
//     count++;
//   }
//   return count;
//}

/*¼ÆËã×Ö·û´®³¤¶ÈµÄº¯Êı£¬ÓÃ»§¿ÉÒÔÍ¨¹ıºê¶¨ÒåÒıÓÃº¯Êı¿âµÄº¯Êı*/
int32_t pl_strlen(char*str)
{
   int32_t count=0;
   while(*str++){
     count++;
   }
   return count;
}


//0-396
char PY_mb_space []  = {' '};
char PY_mb_a     []  = {"°¡°¢"};
char PY_mb_ai    []  = {"°®°¤°­°¥°£°«°¬°¦°§°©°¨°ª°¯"};
char PY_mb_an    []  = {"°´°²°µ°¸°°°³°¶°±°·"};
char PY_mb_ang   []  = {"°º°»°¹"};
char PY_mb_ao    []  = {"°Á°¼°½°¾°Â°¿°À°Ã°Ä"};
char PY_mb_ba    []  = {"°Ë°Ñ°Í°Ö°Õ°Ô°Î°Ç°É°Ó°Å°Ì°Æ°Ê°Ï°È°Ğ"};
char PY_mb_bai   []  = {"°×°Ù°Ú°Ü°İ°Û°Ø°Ş"};
char PY_mb_ban   []  = {"°ì°ë°à°ã°é°å°æ°á°è°ç°ä°â°ß°í°ê"};
char PY_mb_bang  []  = {"°î°ï°ó°ø°ñ°÷°ò°ô°ù°õ°ö°ğ"};
char PY_mb_bao   []  = {"°ü±£±¦±¨±§±¥±©±¬°û±¡°ı±¢±¤±ª°ú±«°şÆÙ"};
char PY_mb_bei   []  = {"±°±­±¯±®±±±´±·±¸±³±µ±¶±»±¹±º±²"};
char PY_mb_ben   []  = {"±¼±¾±½±¿º»"};
char PY_mb_beng  []  = {"±À±Á±Â±Ã±Å±Ä"};
char PY_mb_bi    []  = {"±Æ±Ç±È±Ë±Ê±É±Ò±Ø±Ï±Õ±Ó±Ñ±İ±Ğ±Ö±Ô±Í±×±Ì±Î±Ú±Ü±Û"};
char PY_mb_bian  []  = {"±ß±à±Ş±á±â±å±ã±ä±é±æ±ç±è"};
char PY_mb_biao  []  = {"±ë±ê±ì±í"};
char PY_mb_bie   []  = {"±ï±î±ğ±ñ"};
char PY_mb_bin   []  = {"±ö±ò±ó±õ±ô±÷"};
char PY_mb_bing  []  = {"±ù±ø±û±ü±ú±ş±ı²¢²¡"};
char PY_mb_bo    []  = {"²¦²¨²£²§²±²¤²¥²®²µ²¯²´²ª²¬²°²©²³²«²­²²²·"};
char PY_mb_bu    []  = {"²¹²¸²¶²»²¼²½²À²¿²º²¾"};
char PY_mb_ca    []  = {"²Á"};
char PY_mb_cai   []  = {"²Â²Å²Ä²Æ²Ã²É²Ê²Ç²È²Ë²Ì"};
char PY_mb_can   []  = {"²Î²Í²Ğ²Ï²Ñ²Ò²Ó"};
char PY_mb_cang  []  = {"²Ö²×²Ô²Õ²Ø"};
char PY_mb_cao   []  = {"²Ù²Ú²Ü²Û²İ"};
char PY_mb_ce    []  = {"²á²à²Ş²â²ß"};
char PY_mb_ceng  []  = {"²ã²äÔø"};
char PY_mb_cha   []  = {"²æ²å²é²ç²è²ë²ì²ê²í²ï²îÉ²"};
char PY_mb_chai  []  = {"²ğ²ñ²ò"};
char PY_mb_chan  []  = {"²ô²ó²÷²ö²ø²õ²ú²ù²û²ü"};
char PY_mb_chang []  = {"²ı²ş³¦³¢³¥³£³§³¡³¨³©³«³ª"};
char PY_mb_chao  []  = {"³­³®³¬³²³¯³°³±³³³´´Â"};
char PY_mb_che   []  = {"³µ³¶³¹³¸³·³º"};
char PY_mb_chen  []  = {"³»³¾³¼³À³Á³½³Â³¿³Ä³Ã"};
char PY_mb_cheng []  = {"³Æ³Å³É³Ê³Ğ³Ï³Ç³Ë³Í³Ì³Î³È³Ñ³Ò³Ó"};
char PY_mb_chi   []  = {"³Ô³Õ³Ú³Ø³Û³Ù³Ö³ß³Ş³İ³Ü³â³à³ã³á"};
char PY_mb_chong []  = {"³ä³å³æ³ç³è"};
char PY_mb_chou  []  = {"³é³ğ³ñ³ë³î³í³ï³ê³ì³ó³ò³ô"};
char PY_mb_chu   []  = {"³ö³õ³ı³ø³ü³ú³û³÷³ù´¡´¢³ş´¦´¤´¥´£Ğó"};
char PY_mb_chuai []  = {"´§"};
char PY_mb_chuan []  = {"´¨´©´«´¬´ª´­´®"};
char PY_mb_chuang[]  = {"´³´¯´°´²´´"};
char PY_mb_chui  []  = {"´µ´¶´¹´·´¸"};
char PY_mb_chun  []  = {"´º´»´¿´½´¾´¼´À"};
char PY_mb_chuo  []  = {"´Á"};
char PY_mb_ci    []  = {"´Ã´Ê´Ä´É´È´Ç´Å´Æ´Ë´Î´Ì´Í"};
char PY_mb_cong  []  = {"´Ñ´Ó´Ò´Ğ´Ï´Ô"};
char PY_mb_cou   []  = {"´Õ"};
char PY_mb_cu    []  = {"´Ö´Ù´×´Ø"};
char PY_mb_cuan  []  = {"´Ú´Ü´Û"};
char PY_mb_cui   []  = {"´Ş´ß´İ´à´ã´á´â´ä"};
char PY_mb_cun   []  = {"´å´æ´ç"};
char PY_mb_cuo   []  = {"´ê´è´é´ì´ë´í"};
char PY_mb_da    []  = {"´î´ï´ğ´ñ´ò´ó"};
char PY_mb_dai   []  = {"´ô´õ´ö´ú´ø´ıµ¡´ù´û´ü´ş´÷"};
char PY_mb_dan   []  = {"µ¤µ¥µ£µ¢µ¦µ¨µ§µ©µ«µ®µ¯µ¬µ­µ°µª"};
char PY_mb_dang  []  = {"µ±µ²µ³µ´µµ"};
char PY_mb_dao   []  = {"µ¶µ¼µºµ¹µ·µ»µ¸µ½µ¿µÁµÀµ¾"};
char PY_mb_de    []  = {"µÃµÂµÄ"};
char PY_mb_deng  []  = {"µÆµÇµÅµÈµËµÊµÉ"};
char PY_mb_di    []  = {"µÍµÌµÎµÒµÏµĞµÓµÑµÕµ×µÖµØµÜµÛµİµÚµŞµÙ"};
char PY_mb_dian  []  = {"µàµáµßµäµãµâµçµèµéµêµæµëµíµìµîµå"};
char PY_mb_diao  []  = {"µóµğµòµïµñµõµöµô"};
char PY_mb_die   []  = {"µùµøµüµıµşµúµû"};
char PY_mb_ding  []  = {"¶¡¶£¶¢¶¤¶¥¶¦¶©¶¨¶§"};
char PY_mb_diu   []  = {"¶ª"};
char PY_mb_dong  []  = {"¶«¶¬¶­¶®¶¯¶³¶±¶²¶°¶´"};
char PY_mb_dou   []  = {"¶¼¶µ¶·¶¶¶¸¶¹¶º¶»"};
char PY_mb_du    []  = {"¶½¶¾¶Á¶¿¶À¶Â¶Ä¶Ã¶Ê¶Å¶Ç¶È¶É¶Æ"};
char PY_mb_duan  []  = {"¶Ë¶Ì¶Î¶Ï¶Ğ¶Í"};
char PY_mb_dui   []  = {"¶Ñ¶Ó¶Ô¶Ò"};
char PY_mb_dun   []  = {"¶Ö¶Ø¶Õ¶×¶Ü¶Û¶Ù¶İ"};
char PY_mb_duo   []  = {"¶à¶ß¶á¶Ş¶ä¶â¶ã¶ç¶é¶æ¶è¶å"};
char PY_mb_e     []  = {"¶ï¶í¶ğ¶ë¶ì¶ê¶î¶ò¶ó¶ñ¶ö¶õ¶ô"};
char PY_mb_en    []  = {"¶÷"};
char PY_mb_er    []  = {"¶ù¶ø¶û¶ú¶ı¶ü¶ş·¡"};
char PY_mb_fa    []  = {"·¢·¦·¥·£·§·¤·¨·©"};
char PY_mb_fan   []  = {"·«·¬·­·ª·²·¯·°·³·®·±·´·µ·¸·º·¹·¶··"};
char PY_mb_fang  []  = {"·½·»·¼·À·Á·¿·¾·Â·Ã·Ä·Å"};
char PY_mb_fei   []  = {"·É·Ç·È·Æ·Ê·Ë·Ì·Í·Ï·Ğ·Î·Ñ"};
char PY_mb_fen   []  = {"·Ö·Ô·×·Ò·Õ·Ó·Ø·Ú·Ù·Û·İ·Ü·Ş·ß·à"};
char PY_mb_feng  []  = {"·á·ç·ã·â·è·å·é·æ·ä·ë·ê·ì·í·ï·î"};
char PY_mb_fo    []  = {"·ğ"};
char PY_mb_fou   []  = {"·ñ"};
char PY_mb_fu    []  = {"·ò·ô·õ·ó¸¥·ü·ö·÷·ş·ı·ú¸¡¸¢·û¸¤·ù¸£·ø¸§¸¦¸®¸«¸©¸ª¸­¸¯¸¸¸¼¸¶¸¾¸º¸½¸À¸·¸´¸°¸±¸µ¸»¸³¸¿¸¹¸²"};
char PY_mb_ga    []  = {"¸Â¸Á"};
char PY_mb_gai   []  = {"¸Ã¸Ä¸Æ¸Ç¸È¸Å"};
char PY_mb_gan   []  = {"¸É¸Ê¸Ë¸Î¸Ì¸Í¸Ñ¸Ï¸Ò¸Ğ¸Ó"};
char PY_mb_gang  []  = {"¸Ô¸Õ¸Ú¸Ù¸Ø¸×¸Ö¸Û¸Ü"};
char PY_mb_gao   []  = {"¸Ş¸á¸ß¸à¸İ¸â¸ã¸å¸ä¸æ"};
char PY_mb_ge    []  = {"¸ê¸í¸ç¸ì¸ë¸î¸é¸è¸ó¸ï¸ñ¸ğ¸ô¸ö¸÷¸õ¿©"};
char PY_mb_gei   []  = {"¸ø"};
char PY_mb_gen   []  = {"¸ù¸ú"};
char PY_mb_geng  []  = {"¸ü¸ı¸û¸ş¹¡¹¢¹£"};
char PY_mb_gong  []  = {"¹¤¹­¹«¹¦¹¥¹©¹¬¹§¹ª¹¨¹®¹¯¹°¹²¹±"};
char PY_mb_gou   []  = {"¹´¹µ¹³¹·¹¶¹¹¹º¹¸¹»"};
char PY_mb_gu    []  = {"¹À¹¾¹Ã¹Â¹Á¹½¹¼¹¿¹Å¹È¹É¹Ç¹Æ¹Ä¹Ì¹Ê¹Ë¹Í"};
char PY_mb_gua   []  = {"¹Ï¹Î¹Ğ¹Ñ¹Ò¹Ó"};
char PY_mb_guai  []  = {"¹Ô¹Õ¹Ö"};
char PY_mb_guan  []  = {"¹Ø¹Û¹Ù¹Ú¹×¹İ¹Ü¹á¹ß¹à¹Ş"};
char PY_mb_guang []  = {"¹â¹ã¹ä"};
char PY_mb_gui   []  = {"¹é¹ç¹ê¹æ¹ë¹è¹å¹ì¹î¹ï¹í¹ô¹ñ¹ó¹ğ¹ò"};
char PY_mb_gun   []  = {"¹õ¹ö¹÷"};
char PY_mb_guo   []  = {"¹ù¹ø¹ú¹û¹ü¹ı"};
char PY_mb_ha    []  = {"¸ò¹ş"};
char PY_mb_hai   []  = {"º¢º¡º£º¥º§º¦º¤"};
char PY_mb_han   []  = {"º¨º©º¬ºªº¯º­º®º«º±º°ººº¹ºµº·º´º¸º¶º³º²"};
char PY_mb_hang  []  = {"º¼º½ĞĞ"};
char PY_mb_hao   []  = {"ºÁºÀº¿º¾ºÃºÂºÅºÆºÄ"};
char PY_mb_he    []  = {"ºÇºÈºÌºÏºÎºÍºÓºÒºËºÉºÔºĞºÊºØºÖºÕº×"};
char PY_mb_hei   []  = {"ºÚºÙ"};
char PY_mb_hen   []  = {"ºÛºÜºİºŞ"};
char PY_mb_heng  []  = {"ºàºßºãºáºâ"};
char PY_mb_hong  []  = {"ºäºåºæºëºìºêºéºçºè"};
char PY_mb_hou   []  = {"ºîºíºïºğºóºñºò"};
char PY_mb_hu    []  = {"ºõºôºö»¡ºüºúºøºşºùº÷ºıºû»¢»£»¥»§»¤»¦"};
char PY_mb_hua   []  = {"»¨»ª»©»¬»«»¯»®»­»°"};
char PY_mb_huai  []  = {"»³»²»´»±»µ"};
char PY_mb_huan  []  = {"»¶»¹»·»¸»º»Ã»Â»½»»»Á»¼»À»¾»¿"};
char PY_mb_huang []  = {"»Ä»Å»Ê»Ë»Æ»Ì»Í»È»Ç»É»Ğ»Î»Ñ»Ï"};
char PY_mb_hui   []  = {"»Ò»Ö»Ó»Ô»Õ»Ø»×»Ú»Ü»ã»á»ä»æ»å»â»ß»Ş»à»İ»Ù»Û"};
char PY_mb_hun   []  = {"»è»ç»é»ë»ê»ì"};
char PY_mb_huo   []  = {"»í»î»ğ»ï»ò»õ»ñ»ö»ó»ô"};
char PY_mb_ji    []  = {"»÷¼¢»ø»ú¼¡¼¦¼£»ı»ù¼¨»ü¼¤¼°¼ª¼³¼¶¼´¼«¼±¼²¼¯¼µ¼­¼®¼¸¼º¼·¼¹¼Æ¼Ç¼Í¼Ë¼É¼¼¼Ê¼Á¼¾¼È¼Ã¼Ì¼Å¼Ä¼À½å"};
char PY_mb_jia   []  = {"¼Ó¼Ğ¼Ñ¼Ï¼Ò¼Î¼Ô¼Õ¼×¼Ö¼Ø¼Û¼İ¼Ü¼Ù¼Ş¼ÚĞ®"};
char PY_mb_jian  []  = {"¼é¼â¼á¼ß¼ä¼ç¼è¼æ¼à¼ã¼ê¼å¼ğ¼ó¼í¼ë¼ñ¼õ¼ô¼ì¼ï¼ò¼î¼û¼ş½¨½¤½£¼ö¼ú½¡½§½¢½¥½¦¼ù¼ø¼ü¼ı"};
char PY_mb_jiang []  = {"½­½ª½«½¬½©½®½²½±½°½¯½³½µ½´"};
char PY_mb_jiao  []  = {"½»½¼½¿½½½¾½º½·½¹½¶½¸½Ç½Æ½Ê½È½Ã½Å½Â½Á½Ë½É½Ğ½Î½Ï½Ì½Ñ½Í¾õ½À"};
char PY_mb_jie   []  = {"½×½Ô½Ó½Õ½Ò½Ö½Ú½Ù½Ü½à½á½İ½Ş½Ø½ß½ã½â½é½ä½æ½ì½ç½ê½ë½è"};
char PY_mb_jin   []  = {"½í½ñ½ï½ğ½ò½î½ó½ö½ô½÷½õ¾¡¾¢½ü½ø½ú½ş½ı½û½ù"};
char PY_mb_jing  []  = {"¾©¾­¾¥¾£¾ª¾§¾¦¾¬¾¤¾«¾¨¾®¾±¾°¾¯¾»¾¶¾·¾º¾¹¾´¾¸¾³¾²¾µ"};
char PY_mb_jiong []  = {"¾¼¾½"};
char PY_mb_jiu   []  = {"¾À¾¿¾¾¾Å¾Ã¾Ä¾Á¾Â¾Æ¾É¾Ê¾Ì¾Î¾Ç¾È¾Í¾Ë"};
char PY_mb_ju    []  = {"¾Ó¾Ğ¾Ñ¾Ô¾Ò¾Ï¾Ö½Û¾Õ¾×¾Ú¾Ù¾Ø¾ä¾Ş¾Ü¾ß¾æ¾ã¾ç¾å¾İ¾à¾â¾Û¾á"};
char PY_mb_juan  []  = {"¾ê¾è¾é¾í¾ë¾î¾ì"};
char PY_mb_jue   []  = {"¾ï¾ö¾÷¾ñ¾ø¾ó¾ò¾ô¾ğ"};
char PY_mb_jun   []  = {"¾ü¾ı¾ù¾û¾ú¿¡¿¤¾ş¿£¿¥¿¢"};
char PY_mb_ka    []  = {"¿§¿¦¿¨"};
char PY_mb_kai   []  = {"¿ª¿«¿­¿®¿¬"};
char PY_mb_kan   []  = {"¼÷¿¯¿±¿°¿²¿³¿´"};
char PY_mb_kang  []  = {"¿µ¿¶¿·¿¸¿º¿¹¿»"};
char PY_mb_kao   []  = {"¿¼¿½¿¾¿¿"};
char PY_mb_ke    []  = {"¿À¿Á¿Â¿Æ¿Ã¿Å¿Ä¿Ç¿È¿É¿Ê¿Ë¿Ì¿Í¿Î"};
char PY_mb_ken   []  = {"¿Ï¿Ñ¿Ò¿Ğ"};
char PY_mb_keng  []  = {"¿Ô¿Ó"};
char PY_mb_kong  []  = {"¿Õ¿×¿Ö¿Ø"};
char PY_mb_kou   []  = {"¿Ù¿Ú¿Û¿Ü"};
char PY_mb_ku    []  = {"¿İ¿Ş¿ß¿à¿â¿ã¿á"};
char PY_mb_kua   []  = {"¿ä¿å¿æ¿è¿ç"};
char PY_mb_kuai  []  = {"¿é¿ì¿ë¿ê"};
char PY_mb_kuan  []  = {"¿í¿î"};
char PY_mb_kuang []  = {"¿ï¿ğ¿ñ¿ö¿õ¿ó¿ò¿ô"};
char PY_mb_kui   []  = {"¿÷¿ù¿ø¿ú¿ü¿û¿ı¿şÀ¢À£À¡"};
char PY_mb_kun   []  = {"À¤À¥À¦À§"};
char PY_mb_kuo   []  = {"À©À¨À«Àª"};
char PY_mb_la    []  = {"À¬À­À²À®À°À¯À±"};
char PY_mb_lai   []  = {"À´À³Àµ"};
char PY_mb_lan   []  = {"À¼À¹À¸À·À»À¶À¾À½ÀºÀÀÀ¿ÀÂÀÁÀÃÀÄ"};
char PY_mb_lang  []  = {"ÀÉÀÇÀÈÀÅÀÆÀÊÀË"};
char PY_mb_lao   []  = {"ÀÌÀÍÀÎÀÏÀĞÀÑÀÔÀÓÀÒ"};
char PY_mb_le    []  = {"ÀÖÀÕÁË"};
char PY_mb_lei   []  = {"À×ÀØÀİÀÚÀÙÀÜÀßÀáÀàÀÛÀŞ"};
char PY_mb_leng  []  = {"ÀâÀãÀä"};
char PY_mb_li    []  = {"ÀåÀæÀêÀëÀòÀçÀìÁ§ÀèÀéÀñÀîÀïÁ¨ÀíÀğÁ¦ÀúÀ÷Á¢ÀôÀöÀûÀøÁ¤ÀıÁ¥ÀşÀóÀõÀùÁ£ÀüÁ¡"};
char PY_mb_lian  []  = {"Á¬Á±Á¯Á°Á«ÁªÁ®Á­Á²Á³Á·Á¶ÁµÁ´"};
char PY_mb_liang []  = {"Á©Á¼Á¹ÁºÁ¸Á»Á½ÁÁÁÂÁ¾ÁÀÁ¿"};
char PY_mb_liao  []  = {"ÁÊÁÉÁÆÁÄÁÅÁÈÁÎÁÃÁÇÁÍÁÏÁÌ"};
char PY_mb_lie   []  = {"ÁĞÁÓÁÒÁÔÁÑ"};
char PY_mb_lin   []  = {"ÁÚÁÖÁÙÁÜÁÕÁØÁ×ÁÛÁİÁßÁŞÁà"};
char PY_mb_ling  []  = {"ÁæÁéÁëÁáÁèÁåÁêÁçÁâÁãÁäÁìÁîÁí"};
char PY_mb_liu   []  = {"ÁïÁõÁ÷ÁôÁğÁòÁóÁñÁöÁøÁù"};
char PY_mb_long  []  = {"ÁúÁüÁıÁûÂ¡ÁşÂ¤Â¢Â£"};
char PY_mb_lou   []  = {"Â¦Â¥Â§Â¨ÂªÂ©"};
char PY_mb_lu    []  = {"Â¶Â¬Â®Â«Â¯Â­Â±Â²Â°Â³Â½Â¼Â¸Â¹Â»ÂµÂ·Â¾ÂºÂ´"};
char PY_mb_luan  []  = {"ÂÏÂÍÂÎÂĞÂÑÂÒ"};
char PY_mb_lue   []  = {"ÂÓÂÔ"};
char PY_mb_lun   []  = {"ÂÕÂØÂ×ÂÙÂÚÂÖÂÛ"};
char PY_mb_luo   []  = {"ÂŞÂÜÂßÂàÂáÂâÂİÂãÂåÂçÂæÂä"};
char PY_mb_lv    []  = {"ÂËÂ¿ÂÀÂÂÂÃÂÁÂÅÂÆÂÄÂÉÂÇÂÊÂÌÂÈ"};
char PY_mb_ma    []  = {"ÂèÂéÂíÂêÂëÂìÂîÂğÂï"};
char PY_mb_mai   []  = {"ÂñÂòÂõÂóÂôÂö"};
char PY_mb_man   []  = {"ÂùÂøÂ÷ÂúÂüÃ¡ÂıÂşÂû"};
char PY_mb_mang  []  = {"Ã¦Ã¢Ã¤Ã£Ã§Ã¥"};
char PY_mb_mao   []  = {"Ã¨Ã«Ã¬Ã©ÃªÃ®Ã­Ã¯Ã°Ã³Ã±Ã²"};
char PY_mb_me    []  = {"Ã´"};
char PY_mb_mei   []  = {"Ã»Ã¶ÃµÃ¼Ã·Ã½ÃºÃ¸Ã¹Ã¿ÃÀÃ¾ÃÃÃÁÃÄÃÂ"};
char PY_mb_men   []  = {"ÃÅÃÆÃÇ"};
char PY_mb_meng  []  = {"ÃÈÃËÃÊÃÍÃÉÃÌÃÏÃÎ"};
char PY_mb_mi    []  = {"ÃÖÃÔÃÕÃÑÃÓÃÒÃ×ÃĞÃÚÃÙÃØÃÜÃİÃÛ"};
char PY_mb_mian  []  = {"ÃßÃàÃŞÃâÃãÃäÃáÃåÃæ"};
char PY_mb_miao  []  = {"ÃçÃèÃéÃëÃìÃêÃîÃí"};
char PY_mb_mie   []  = {"ÃğÃï"};
char PY_mb_min   []  = {"ÃñÃóÃòÃöÃõÃô"};
char PY_mb_ming  []  = {"ÃûÃ÷ÃùÃúÃøÃü"};
char PY_mb_miu   []  = {"Ãı"};
char PY_mb_mo    []  = {"ºÑÃşÄ¡Ä£Ä¤Ä¦Ä¥Ä¢Ä§Ä¨Ä©Ä­Ä°ÄªÄ¯Ä®Ä«Ä¬"};
char PY_mb_mou   []  = {"Ä²Ä±Ä³"};
char PY_mb_mu    []  = {"Ä¸Ä¶ÄµÄ·Ä´Ä¾Ä¿ÄÁÄ¼Ä¹Ä»ÄÀÄ½ÄºÄÂ"};
char PY_mb_na    []  = {"ÄÃÄÄÄÇÄÉÄÈÄÆÄÅ"};
char PY_mb_nai   []  = {"ÄËÄÌÄÊÄÎÄÍ"};
char PY_mb_nan   []  = {"ÄĞÄÏÄÑéª"};
char PY_mb_nang  []  = {"ÄÒ"};
char PY_mb_nao   []  = {"ÄÓÄÕÄÔÄÖÄ×"};
char PY_mb_ne    []  = {"ÄØ"};
char PY_mb_nei   []  = {"ÄÚÄÙ"};
char PY_mb_nen   []  = {"ÄÛ"};
char PY_mb_neng  []  = {"ÄÜ"};
char PY_mb_ni    []  = {"ÄİÄáÄàÄßÄŞÄãÄâÄæÄäÄçÄå"};
char PY_mb_nian  []  = {"ÄéÄêÄíÄìÄëÄîÄè"};
char PY_mb_niang []  = {"ÄïÄğ"};
char PY_mb_niao  []  = {"ÄñÄò"};
char PY_mb_nie   []  = {"ÄóÄùÄôÄöÄ÷ÄøÄõ"};
char PY_mb_nin   []  = {"Äú"};
char PY_mb_ning  []  = {"ÄşÅ¡ÄüÄûÄıÅ¢"};
char PY_mb_niu   []  = {"Å£Å¤Å¦Å¥"};
char PY_mb_nong  []  = {"Å©Å¨Å§Åª"};
char PY_mb_nu    []  = {"Å«Å¬Å­"};
char PY_mb_nuan  []  = {"Å¯"};
char PY_mb_nue   []  = {"Å±Å°"};
char PY_mb_nuo   []  = {"Å²ÅµÅ³Å´"};
char PY_mb_nv    []  = {"Å®"};
char PY_mb_o     []  = {"Å¶"};
char PY_mb_ou    []  = {"Å·Å¹Å¸Å»Å¼ÅºÅ½"};
char PY_mb_pa    []  = {"Å¿Å¾ÅÀ°ÒÅÃÅÁÅÂ"};
char PY_mb_pai   []  = {"ÅÄÅÇÅÅÅÆÅÉÅÈ"};
char PY_mb_pan   []  = {"ÅËÅÊÅÌÅÍÅĞÅÑÅÎÅÏ"};
char PY_mb_pang  []  = {"ÅÒÅÓÅÔÅÕÅÖ"};
char PY_mb_pao   []  = {"Å×ÅÙÅØÅÚÅÛÅÜÅİ"};
char PY_mb_pei   []  = {"ÅŞÅßÅãÅàÅâÅáÅæÅåÅä"};
char PY_mb_pen   []  = {"ÅçÅè"};
char PY_mb_peng  []  = {"ÅêÅéÅëÅóÅíÅïÅğÅîÅôÅìÅñÅòÅõÅö"};
char PY_mb_pi    []  = {"±ÙÅúÅ÷ÅûÅøÅüÅùÆ¤ÅşÆ£Æ¡ÅıÆ¢Æ¥Æ¦Æ¨Æ§Æ©"};
char PY_mb_pian  []  = {"Æ¬Æ«ÆªÆ­"};
char PY_mb_piao  []  = {"Æ¯Æ®Æ°Æ±"};
char PY_mb_pie   []  = {"Æ²Æ³"};
char PY_mb_pin   []  = {"Æ´Æ¶ÆµÆ·Æ¸"};
char PY_mb_ping  []  = {"Æ½ÆÀÆ¾ÆÁÆ¿ÆºÆ»Æ¼Æ¹"};
char PY_mb_po    []  = {"ÆÂÆÃÆÄÆÅÆÈÆÆÆÉÆÇ"};
char PY_mb_pou   []  = {"ÆÊ"};
char PY_mb_pu    []  = {"¸¬ÆÍÆËÆÌÆÎÆĞÆÏÆÑÆÓÆÔÆÒÆÖÆÕÆ×ÆØ"};
char PY_mb_qi    []  = {"ÆßÆãÆŞÆâÆàÆÜÆİÆÚÆÛÆáÆîÆëÆäÆæÆçÆíÆêÆéÆèÆïÆåÆìÆòÆóÆñÆôÆğÆøÆıÆùÆúÆûÆüÆõÆöÆ÷"};
char PY_mb_qia   []  = {"ÆşÇ¡Ç¢"};
char PY_mb_qian  []  = {"Ç§ÇªÇ¤Ç¨Ç¥Ç£Ç¦Ç«Ç©Ç°Ç®Ç¯Ç¬Ç±Ç­Ç³Ç²Ç´Ç·ÇµÇ¶Ç¸"};
char PY_mb_qiang []  = {"ÇºÇ¼Ç¹Ç»Ç¿Ç½Ç¾ÇÀ"};
char PY_mb_qiao  []  = {"ÇÄÇÃÇÂÇÁÇÇÇÈÇÅÇÆÇÉÇÎÇÍÇÏÇÌÇËÇÊ"};
char PY_mb_qie   []  = {"ÇĞÇÑÇÒÇÓÇÔ"};
char PY_mb_qin   []  = {"Ç×ÇÖÇÕÇÛÇØÇÙÇİÇÚÇÜÇŞÇß"};
char PY_mb_qing  []  = {"ÇàÇâÇáÇãÇäÇåÇéÇçÇèÇæÇêÇëÇì"};
char PY_mb_qiong []  = {"ÇîÇí"};
char PY_mb_qiu   []  = {"ÇğÇñÇïÇôÇóÇöÇõÇò"};
char PY_mb_qu    []  = {"ÇøÇúÇıÇüÇùÇûÇ÷ÇşÈ¡È¢È£È¥È¤"};
char PY_mb_quan  []  = {"È¦È«È¨ÈªÈ­È¬È©È§È®È°È¯"};
char PY_mb_que   []  = {"È²È±È³È´È¸È·ÈµÈ¶"};
char PY_mb_qun   []  = {"È¹Èº"};
char PY_mb_ran   []  = {"È»È¼È½È¾"};
char PY_mb_rang  []  = {"È¿ÈÂÈÀÈÁÈÃ"};
char PY_mb_rao   []  = {"ÈÄÈÅÈÆ"};
char PY_mb_re    []  = {"ÈÇÈÈ"};
char PY_mb_ren   []  = {"ÈËÈÊÈÉÈÌÈĞÈÏÈÎÈÒÈÑÈÍ"};
char PY_mb_reng  []  = {"ÈÓÈÔ"};
char PY_mb_ri    []  = {"ÈÕ"};
char PY_mb_rong  []  = {"ÈÖÈŞÈ×ÈÙÈİÈÜÈØÈÛÈÚÈß"};
char PY_mb_rou   []  = {"ÈáÈàÈâ"};
char PY_mb_ru    []  = {"ÈçÈãÈåÈæÈäÈêÈéÈèÈëÈì"};
char PY_mb_ruan  []  = {"ÈîÈí"};
char PY_mb_rui   []  = {"ÈïÈñÈğ"};
char PY_mb_run   []  = {"ÈòÈó"};
char PY_mb_ruo   []  = {"ÈôÈõ"};
char PY_mb_sa    []  = {"ÈöÈ÷Èø"};
char PY_mb_sai   []  = {"ÈûÈùÈúÈü"};
char PY_mb_san   []  = {"ÈıÉ¡É¢Èş"};
char PY_mb_sang  []  = {"É£É¤É¥"};
char PY_mb_sao   []  = {"É¦É§É¨É©"};
char PY_mb_se    []  = {"É«É¬Éª"};
char PY_mb_sen   []  = {"É­"};
char PY_mb_seng  []  = {"É®"};
char PY_mb_sha   []  = {"É±É³É´É°É¯ÉµÉ¶É·ÏÃ"};
char PY_mb_shai  []  = {"É¸É¹"};
char PY_mb_shan  []  = {"É½É¾É¼ÉÀÉºÉ¿ÉÁÉÂÉÇÉ»ÉÈÉÆÉÉÉÃÉÅÉÄÕ¤"};
char PY_mb_shang []  = {"ÉËÉÌÉÊÉÑÉÎÉÍÉÏÉĞ"};
char PY_mb_shao  []  = {"ÉÓÉÒÉÕÉÔÉ×ÉÖÉØÉÙÉÛÉÜÉÚ"};
char PY_mb_she   []  = {"ÉİÉŞÉàÉßÉáÉèÉçÉäÉæÉâÉåÉã"};
char PY_mb_shen  []  = {"ÉêÉìÉíÉëÉğÉïÉéÉîÉñÉòÉóÉôÉöÉõÉøÉ÷Ê²"};
char PY_mb_sheng []  = {"ÉıÉúÉùÉüÊ¤ÉûÉşÊ¡Ê¥Ê¢Ê£"};
char PY_mb_shi   []  = {"ÊÇÊ®Ê¯Ê±Ê¿Ê¶ÊÂÊ³Ê¾Ê½Ê¹Ê¼ÊÒÊÆÊµÊÓÊÔÊ·ÊÊÊ©ÊĞÊ»ÊªËÆ³×Ê¬Ê§ÊÅÊÍÊ¦Ê«Ê¨Ê°Ê´Ê¸ÊºÊÏÊËÊÎÊÑÊÃÊÁÊÉ"};
char PY_mb_shou  []  = {"ÊÕÊÖÊØÊ×ÊÙÊÜÊŞÊÛÊÚÊİ"};
char PY_mb_shu   []  = {"ÊéÊãÊåÊàÊâÊáÊçÊèÊæÊäÊßÊëÊêÊìÊîÊòÊğÊóÊñÊíÊïÊõÊùÊøÊöÊ÷ÊúË¡ÊüÊıÊûÊşÊô"};
char PY_mb_shua  []  = {"Ë¢Ë£"};
char PY_mb_shuai []  = {"Ë¥Ë¤Ë¦Ë§"};
char PY_mb_shuan []  = {"Ë©Ë¨"};
char PY_mb_shuang[]  = {"Ë«ËªË¬"};
char PY_mb_shui  []  = {"Ë­Ë®Ë°Ë¯"};
char PY_mb_shun  []  = {"Ë±Ë³Ë´Ë²"};
char PY_mb_shuo  []  = {"ËµË¸Ë·Ë¶"};
char PY_mb_si    []  = {"ËÄË¿Ë¾Ë½Ë¼Ë¹ËÀËºËÂË»ËÈËÅËÇËÃËÁ"};
char PY_mb_song  []  = {"ËÍËÎËÉËÊËËËÏËĞËÌ"};
char PY_mb_sou   []  = {"ËÔËÑËÒËÓ"};
char PY_mb_su    []  = {"ËÕËÖË×ËßËàËØËÙËÚËÜËİËÛ"};
char PY_mb_suan  []  = {"ËáËâËã"};
char PY_mb_sui   []  = {"ËäËêËçËåËæËèËîËìËéËíËë"};
char PY_mb_sun   []  = {"ËïËğËñ"};
char PY_mb_suo   []  = {"ËôËóËòËõËùË÷ËöËø"};
char PY_mb_ta    []  = {"ËıËûËüËúËşÌ¡Ì¢Ì¤Ì£"};
char PY_mb_tai   []  = {"Ì¥Ì¨Ì§Ì¦Ì«Ì­Ì¬Ì©Ìª"};
char PY_mb_tan   []  = {"Ì®Ì°Ì¯Ì²Ì±Ì³Ì¸ÌµÌ·Ì¶Ì´Ì¹Ì»ÌºÌ¾Ì¿Ì½Ì¼"};
char PY_mb_tang  []  = {"ÌÀÌÆÌÃÌÄÌÁÌÂÌÅÌÇÌÈÌÊÌÉÌÌÌË"};
char PY_mb_tao   []  = {"ÌÎÌĞÌÍÌÏÌÓÌÒÌÕÌÔÌÑÌÖÌ×"};
char PY_mb_te    []  = {"ÌØ"};
char PY_mb_teng  []  = {"ÌÛÌÚÌÜÌÙ"};
char PY_mb_ti    []  = {"ÌŞÌİÌàÌßÌäÌáÌâÌãÌåÌëÌêÌéÌèÌæÌç"};
char PY_mb_tian  []  = {"ÌìÌíÌïÌñÌğÌîÌóÌò"};
char PY_mb_tiao  []  = {"µ÷ÌôÌõÌöÌ÷Ìø"};
char PY_mb_tie   []  = {"ÌùÌúÌû"};
char PY_mb_ting  []  = {"Í£ÌüÍ¡ÌıÌşÍ¢Í¤Í¥Í¦Í§"};
char PY_mb_tong  []  = {"Í¨Í¬Í®Í©Í­Í¯ÍªÍ«Í³Í±Í°Í²Í´"};
char PY_mb_tou   []  = {"ÍµÍ·Í¶Í¸"};
char PY_mb_tu    []  = {"Í¹ÍºÍ»Í¼Í½Í¿Í¾ÍÀÍÁÍÂÍÃ"};
char PY_mb_tuan  []  = {"ÍÄÍÅ"};
char PY_mb_tui   []  = {"ÍÆÍÇÍÈÍËÍÉÍÊ"};
char PY_mb_tun   []  = {"¶ÚÍÌÍÍÍÎ"};
char PY_mb_tuo   []  = {"ÍĞÍÏÍÑÍÔÍÓÍÕÍÒÍ×ÍÖÍØÍÙ"};
char PY_mb_wa    []  = {"ÍÛÍŞÍÚÍİÍÜÍßÍà"};
char PY_mb_wai   []  = {"ÍâÍá"};
char PY_mb_wan   []  = {"ÍòÍêÍæÍíÍäÍëÍåÍãÍèÍçÍéÍğÍìÍñÍïÍîÍó"};
char PY_mb_wang  []  = {"ÍõÍøÍùÍüÍúÍûÍôÍöÍ÷Íı"};
char PY_mb_wei   []  = {"Î£ÍşÎ¢Î¡ÎªÎ¤Î§Î¥Î¦Î¨Î©Î¬Î«Î°Î±Î²Î³Î­Î¯Î®ÎÀÎ´Î»Î¶Î·Î¸Î¾Î½Î¹Î¼ÎµÎ¿Îº"};
char PY_mb_wen   []  = {"ÎÂÎÁÎÄÎÆÎÅÎÃÎÇÎÉÎÈÎÊ"};
char PY_mb_weng  []  = {"ÎÌÎËÎÍ"};
char PY_mb_wo    []  = {"ÎÒÎÖÎÔÎÑÎÕÎĞÎÏÎÓÎÎ"};
char PY_mb_wu    []  = {"ÎåÎâÎóÎŞÎİÎäÎçÎÚÎÛÎØÎ×ÎÜÎÙÎãÎáÎßÎàÎéÎëÎêÎæÎèÎğÎñÎìÎïÎòÎîÎí"};
char PY_mb_xi    []  = {"Ï¦Ï«Î÷ÎüÏ£ÎôÎöÎùÏ¢ÎşÏ¤Ï§Ï©ÎøÎúÏ¬Ï¡ÏªÎıÏ¨ÎõÎûÏ¥Ï°Ï¯Ï®Ï±Ï­Ï´Ï²Ï·ÏµÏ¸Ï¶"};
char PY_mb_xia   []  = {"ÏºÏ¹Ï»ÏÀÏ¿ÏÁÏ¾Ï½Ï¼ÏÂÏÅÏÄ"};
char PY_mb_xian  []  = {"Ï³ÏÉÏÈÏËÏÆÏÇÏÊÏĞÏÒÏÍÏÌÏÑÏÏÏÎÏÓÏÔÏÕÏØÏÖÏßÏŞÏÜÏİÏÚÏÛÏ×ÏÙ"};
char PY_mb_xiang []  = {"ÏçÏàÏãÏáÏæÏäÏåÏâÏêÏéÏèÏíÏìÏëÏòÏïÏîÏóÏñÏğ"};
char PY_mb_xiao  []  = {"ÏüÏûÏôÏõÏúÏöÏùÏıĞ¡ÏşĞ¢Ğ¤ÏøĞ§Ğ£Ğ¦Ğ¥"};
char PY_mb_xie   []  = {"Ğ©Ğ¨ĞªĞ«Ğ­Ğ°Ğ²Ğ±Ğ³Ğ¯Ğ¬Ğ´Ğ¹ĞºĞ¶Ğ¼ĞµĞ»Ğ¸Ğ·"};
char PY_mb_xin   []  = {"ĞÄĞÃĞ¾ĞÁĞÀĞ¿ĞÂĞ½ĞÅĞÆ"};
char PY_mb_xing  []  = {"ĞËĞÇĞÊĞÉĞÈĞÌĞÏĞÎĞÍĞÑĞÓĞÕĞÒĞÔ"};
char PY_mb_xiong []  = {"Ğ×ĞÖĞÙĞÚĞØĞÛĞÜ"};
char PY_mb_xiu   []  = {"ËŞĞİĞŞĞßĞàĞãĞåĞäĞâĞá"};
char PY_mb_xu    []  = {"ĞçĞëĞéĞêĞèĞæĞìĞíĞñĞòĞğĞôĞ÷ĞøĞïĞöĞõĞîÓõ"};
char PY_mb_xuan  []  = {"ĞùĞûĞúĞşĞüĞıÑ¡Ñ¢Ñ¤Ñ£"};
char PY_mb_xue   []  = {"Ñ§Ñ©ÑªÏ÷Ñ¥Ñ¦Ñ¨"};
char PY_mb_xun   []  = {"Ñ°Ñ®Ñ¸Ñ¯Ñ¶Ñ«Ñ¬Ñ²Ñ±Ñ­ÑµÑ´Ñ·Ñ³"};
char PY_mb_ya    []  = {"Ñ½Ñ¹ÑÀÑÇÑÅÑ¾ÑºÑ»Ñ¼Ñ¿ÑÁÑÂÑÄÑÃÑÆÑÈ"};
char PY_mb_yan   []  = {"ÑÊÑÌÑÍÑÉÑËÑÓÑÏÑÔÑÒÑØÑ×ÑĞÑÎÑÖÑÑÑÕÑÙÑÜÑÚÑÛÑİÑáÑåÑâÑäÑçÑŞÑéÑèÑßÑæÑãÑà"};
char PY_mb_yang  []  = {"ÑôÑïÑîÑùÑøÑòÑëÑêÑíÑìÑğÑñÑóÑöÑõÑ÷Ñú"};
char PY_mb_yao   []  = {"½ÄÑıÑüÑûÒ¢Ò¦Ò¤Ò¥Ò¡Ò£ÑşÒ§Ò¨Ò©ÒªÒ«Ô¿"};
char PY_mb_ye    []  = {"Ò¬Ò­Ò¯Ò®Ò²Ò±Ò°ÒµÒ¶Ò·Ò³Ò¹Ò´ÒºÒ¸"};
char PY_mb_yi    []  = {"Ò»ÒÁÒÂÒ½ÒÀÒ¿ÒÇÒÄÒËÒÌÒÈÒÆÒÅÒÉÒÒÒÑÒÔÒÓÒÏÒÎÒåÒÚÒäÒÕÒéÒàÒìÒÛÒÖÒëÒ×ÒßÒæÒêÒİÒâÒçÒáÒãÒíÒÜ"};
char PY_mb_yin   []  = {"ÒòÒõÒöÒğÒñÒôÒóÒ÷ÒúÒùÒøÒüÒıÒûÒşÓ¡"};
char PY_mb_ying  []  = {"Ó¦Ó¢Ó¤Ó§Ó£Ó¥Ó­Ó¯Ó«Ó¨Ó©ÓªÓ¬Ó®Ó±Ó°Ó³Ó²"};
char PY_mb_yo    []  = {"Ó´"};
char PY_mb_yong  []  = {"Ó¶ÓµÓ¸Ó¹ÓºÓ·ÓÀÓ½Ó¾ÓÂÓ¿ÓÁÓ¼Ó»ÓÃ"};
char PY_mb_you   []  = {"ÓÅÓÇÓÄÓÆÓÈÓÉÓÌÓÊÓÍÓËÓÎÓÑÓĞÓÏÓÖÓÒÓ×ÓÓÓÕÓÔ"};
char PY_mb_yu    []  = {"ÓØÓÙÓåÓÚÓèÓàÓÛÓãÓáÓéÓæÓçÓäÓâÓŞÓÜÓİÓßÓëÓîÓìÓğÓêÓíÓïÓñÔ¦ÓóÓıÓôÓüÓøÔ¡Ô¤ÓòÓûÓ÷Ô¢ÓùÔ£ÓöÓúÓşÔ¥"};
char PY_mb_yuan  []  = {"Ô©Ô§Ô¨ÔªÔ±Ô°Ô«Ô­Ô²Ô¬Ô®ÔµÔ´Ô³Ô¯Ô¶Ô·Ô¹ÔºÔ¸"};
char PY_mb_yue   []  = {"Ô»Ô¼ÔÂÔÀÔÃÔÄÔ¾ÔÁÔ½"};
char PY_mb_yun   []  = {"ÔÆÔÈÔÇÔÅÔÊÔÉÔĞÔËÔÎÔÍÔÏÔÌ"};
char PY_mb_za    []  = {"ÔÑÔÓÔÒÕ¦"};
char PY_mb_zai   []  = {"ÔÖÔÕÔÔÔ×ÔØÔÙÔÚ×Ğ"};
char PY_mb_zan   []  = {"ÔÛÔÜÔİÔŞ"};
char PY_mb_zang  []  = {"ÔßÔàÔá"};
char PY_mb_zao   []  = {"ÔâÔãÔäÔçÔæÔéÔèÔåÔîÔíÔìÔëÔïÔê"};
char PY_mb_ze    []  = {"ÔòÔñÔóÔğ"};
char PY_mb_zei   []  = {"Ôô"};
char PY_mb_zen   []  = {"Ôõ"};
char PY_mb_zeng  []  = {"ÔöÔ÷Ôù"};
char PY_mb_zha   []  = {"ÔûÔüÔúÔıÔşÕ¢Õ¡Õ£Õ§Õ©Õ¨Õ¥×õ"};
char PY_mb_zhai  []  = {"Õ«ÕªÕ¬µÔÕ­Õ®Õ¯"};
char PY_mb_zhan  []  = {"Õ´Õ±Õ³Õ²Õ°Õ¶Õ¹ÕµÕ¸Õ·Õ¼Õ½Õ»Õ¾ÕÀÕ¿Õº"};
char PY_mb_zhang []  = {"³¤ÕÅÕÂÕÃÕÄÕÁÕÇÕÆÕÉÕÌÕÊÕÈÕÍÕËÕÏÕÎ"};
char PY_mb_zhao  []  = {"ÕĞÕÑÕÒÕÓÕÙÕ×ÕÔÕÕÕÖÕØ×¦"};
char PY_mb_zhe   []  = {"ÕÚÕÛÕÜÕİÕŞÕßÕàÕâÕãÕá×Å"};
char PY_mb_zhen  []  = {"ÕêÕëÕìÕäÕæÕèÕåÕçÕéÕïÕíÕîÕóÕñÕòÕğÖ¡"};
char PY_mb_zheng []  = {"ÕùÕ÷ÕúÕõÕøÕöÕôÕüÕûÕıÖ¤Ö£ÕşÖ¢"};
char PY_mb_zhi   []  = {"Ö®Ö§Ö­Ö¥Ö¨Ö¦ÖªÖ¯Ö«Ö¬Ö©Ö´Ö¶Ö±ÖµÖ°Ö²Ö³Ö¹Ö»Ö¼Ö·Ö½Ö¸ÖºÖÁÖ¾ÖÆÖÄÖÎÖÊÖÅÖ¿ÖÈÖÂÖÀÖÌÖÏÖÇÖÍÖÉÖÃ"};
char PY_mb_zhong []  = {"ÖĞÖÒÖØÖÕÖÑÖÓÖÔÖ×ÖÖÖÙÖÚ"};
char PY_mb_zhou  []  = {"ÖİÖÛÖßÖÜÖŞÖàÖáÖâÖãÖäÖæÖçÖåÖè"};
char PY_mb_zhu   []  = {"Ö÷×¡×¢×£ÖìÖíÖúÖùÖñÖğÖêÖéÖöÖøÖîÖëÖòÖïÖôÖóÖõÖü×¤ÖûÖşÖı"};
char PY_mb_zhua  []  = {"×¥"};
char PY_mb_zhuai []  = {"×§"};
char PY_mb_zhuan []  = {"×¨×©×ª×«×­"};
char PY_mb_zhuang[]  = {"×±×¯×®×°×³×´´±×²"};
char PY_mb_zhui  []  = {"×·×¹×µ×¶×º×¸"};
char PY_mb_zhun  []  = {"×¼×»"};
char PY_mb_zhuo  []  = {"×¿×¾×½×À×Æ×Â×Ç×Ã×Ä×Á"};
char PY_mb_zi    []  = {"×Î×È×É×Ë×Ê×Í×Ì×Ñ×Ó×Ï×Ò×Ö×Ô×Õ"};
char PY_mb_zong  []  = {"×Ú×Û×Ø×Ù×××Ü×İ"};
char PY_mb_zou   []  = {"×ß×à×Ş×á"};
char PY_mb_zu    []  = {"×â×ã×ä×å×ç×è×é×æ"};
char PY_mb_zuan  []  = {"×¬×ê×ë"};
char PY_mb_zui   []  = {"×ì×î×ï×í"};
char PY_mb_zun   []  = {"×ğ×ñ"};
char PY_mb_zuo   []  = {"×ò×ó×ô×÷×ø×ù×ö"};

//0-396
t9PY_index t9_py_index[] ={
{"0"		,	"0"	    ,	PY_mb_space},
{"200000"	,	"a"	    ,	PY_mb_a},
{"220000"	,	"ba"	,	PY_mb_ba},
{"220000"	,	"ca"	,	PY_mb_ca},
{"224000"	,	"bai"	,	PY_mb_bai},
{"224000"	,	"cai"	,	PY_mb_cai},
{"226000"	,	"ban"	,	PY_mb_ban},
{"226000"	,	"bao"	,	PY_mb_bao},
{"226000"	,	"can"	,	PY_mb_can},
{"226000"	,	"cao"	,	PY_mb_cao},
{"226400"	,	"bang"	,	PY_mb_bang},
{"226400"	,	"cang"	,	PY_mb_cang},
{"230000"	,	"ce"	,	PY_mb_ce},
{"234000"	,	"bei"	,	PY_mb_bei},
{"236000"	,	"ben"	,	PY_mb_ben},
{"236400"	,	"beng"	,	PY_mb_beng},
{"236400"	,	"ceng"	,	PY_mb_ceng},
{"240000"	,	"ai"	,	PY_mb_ai},
{"240000"	,	"bi"	,	PY_mb_bi},
{"240000"	,	"ci"	,	PY_mb_ci},
{"242000"	,	"cha"	,	PY_mb_cha},
{"242400"	,	"chai"	,	PY_mb_chai},
{"242600"	,	"bian"	,	PY_mb_bian},
{"242600"	,	"biao"	,	PY_mb_biao},
{"242600"	,	"chan"	,	PY_mb_chan},
{"242600"	,	"chao"	,	PY_mb_chao},
{"242640"	,	"chang"	,	PY_mb_chang},
{"243000"	,	"bie"	,	PY_mb_bie},
{"243000"	,	"che"	,	PY_mb_che},
{"243600"	,	"chen"	,	PY_mb_chen},
{"243640"	,	"cheng"	,	PY_mb_cheng},
{"244000"	,	"chi"	,	PY_mb_chi},
{"246000"	,	"bin"	,	PY_mb_bin},
{"246400"	,	"bing"	,	PY_mb_bing},
{"246640"	,	"chong"	,	PY_mb_chong},
{"246800"	,	"chou"	,	PY_mb_chou},
{"248000"	,	"chu"	,	PY_mb_chu},
{"248260"	,	"chuan"	,	PY_mb_chuan},
{"248264"	,	"chuang",	PY_mb_chuang},
{"248400"	,	"chuai"	,	PY_mb_chuai},
{"248400"	,	"chui"	,	PY_mb_chui},
{"248400"	,	"chun"	,	PY_mb_chun},
{"248600"	,	"chuo"	,	PY_mb_chuo},
{"260000"	,	"an"	,	PY_mb_an},
{"260000"	,	"ao"	,	PY_mb_ao},
{"260000"	,	"bo"	,	PY_mb_bo},
{"264000"	,	"ang"	,	PY_mb_ang},
{"266400"	,	"cong"	,	PY_mb_cong},
{"268000"	,	"cou"	,	PY_mb_cou},
{"280000"	,	"bu"	,	PY_mb_bu},
{"280000"	,	"cu"	,	PY_mb_cu},
{"282600"	,	"cuan"	,	PY_mb_cuan},
{"284000"	,	"cui"	,	PY_mb_cui},
{"286000"	,	"cun"	,	PY_mb_cun},
{"286000"	,	"cuo"	,	PY_mb_cuo},
{"300000"	,	"e"	    ,	PY_mb_e},
{"320000"	,	"da"	,	PY_mb_da},
{"320000"	,	"fa"	,	PY_mb_fa},
{"324000"	,	"dai"	,	PY_mb_dai},
{"326000"	,	"dan"	,	PY_mb_dan},
{"326000"	,	"dao"	,	PY_mb_dao},
{"326000"	,	"fan"	,	PY_mb_fan},
{"326400"	,	"dang"	,	PY_mb_dang},
{"326400"	,	"fang"	,	PY_mb_fang},
{"330000"	,	"de"	,	PY_mb_de},
{"334000"	,	"fei"	,	PY_mb_fei},
{"336000"	,	"fen"	,	PY_mb_fen},
{"336400"	,	"deng"	,	PY_mb_deng},
{"336400"	,	"feng"	,	PY_mb_feng},
{"340000"	,	"di"	,	PY_mb_di},
{"342600"	,	"dian"	,	PY_mb_dian},
{"342600"	,	"diao"	,	PY_mb_diao},
{"343000"	,	"die"	,	PY_mb_die},
{"346400"	,	"ding"	,	PY_mb_ding},
{"348000"	,	"diu"	,	PY_mb_diu},
{"360000"	,	"en"	,	PY_mb_en},
{"360000"	,	"fo"	,	PY_mb_fo},
{"366400"	,	"dong"	,	PY_mb_dong},
{"368000"	,	"dou"	,	PY_mb_dou},
{"368000"	,	"fou"	,	PY_mb_fou},
{"370000"	,	"er"	,	PY_mb_er},
{"380000"	,	"du"	,	PY_mb_du},
{"380000"	,	"fu"	,	PY_mb_fu},
{"382600"	,	"duan"	,	PY_mb_duan},
{"384000"	,	"dui"	,	PY_mb_dui},
{"386000"	,	"dun"	,	PY_mb_dun},
{"386000"	,	"duo"	,	PY_mb_duo},
//{"400000"	,	"i"	,	PY_mb_space},
{"420000"	,	"ha"	,	PY_mb_ha},
{"420000"	,	"ga"	,	PY_mb_ga},
{"423000"	,	"hai"	,	PY_mb_hai},
{"424000"	,	"gai"	,	PY_mb_gai},
{"426000"	,	"gan"	,	PY_mb_gan},
{"426000"	,	"gao"	,	PY_mb_gao},
{"426000"	,	"han"	,	PY_mb_han},
{"426000"	,	"hao"	,	PY_mb_hao},
{"426400"	,	"gang"	,	PY_mb_gang},
{"426400"	,	"hang"	,	PY_mb_hang},
{"430000"	,	"ge"	,	PY_mb_ge},
{"430000"	,	"he"	,	PY_mb_he},
{"434000"	,	"gei"	,	PY_mb_gei},
{"434000"	,	"hei"	,	PY_mb_hei},
{"436000"	,	"gen"	,	PY_mb_gan},
{"436000"	,	"hen"	,	PY_mb_hen},
{"436400"	,	"geng"	,	PY_mb_geng},
{"436400"	,	"heng"	,	PY_mb_heng},
{"466400"	,	"gong"	,	PY_mb_gong},
{"466400"	,	"hong"	,	PY_mb_hong},
{"468000"	,	"gou"	,	PY_mb_gou},
{"468000"	,	"hou"	,	PY_mb_hou},
{"480000"	,	"gu"	,	PY_mb_gu},
{"480000"	,	"hu"	,	PY_mb_hu},
{"482000"	,	"gua"	,	PY_mb_gua},
{"482000"	,	"hua"	,	PY_mb_hua},
{"482300"	,	"huai"	,	PY_mb_huai},
{"482400"	,	"guai"	,	PY_mb_guai},
{"482600"	,	"guan"	,	PY_mb_guan},
{"482600"	,	"huan"	,	PY_mb_huan},
{"482640"	,	"guang"	,	PY_mb_guang},
{"482640"	,	"huang"	,	PY_mb_huang},
{"484000"	,	"gui"	,	PY_mb_gui},
{"484000"	,	"hui"	,	PY_mb_hui},
{"486000"	,	"gun"	,	PY_mb_gun},
{"486000"	,	"guo"	,	PY_mb_guo},
{"486000"	,	"hun"	,	PY_mb_hun},
{"486000"	,	"huo"	,	PY_mb_huo},
{"520000"	,	"ka"	,	PY_mb_ka},
{"520000"	,	"la"	,	PY_mb_la},
{"524000"	,	"kai"	,	PY_mb_kai},
{"524000"	,	"lai"	,	PY_mb_lai},
{"526000"	,	"kan"	,	PY_mb_kan},
{"526000"	,	"kao"	,	PY_mb_kao},
{"526000"	,	"lan"	,	PY_mb_lan},
{"526000"	,	"lao"	,	PY_mb_lao},
{"526400"	,	"kang"	,	PY_mb_kang},
{"526400"	,	"lang"	,	PY_mb_lang},
{"530000"	,	"ke"	,	PY_mb_ke},
{"530000"	,	"le"	,	PY_mb_le},
{"534000"	,	"lei"	,	PY_mb_lei},
{"536000"	,	"ken"	,	PY_mb_ken},
{"536400"	,	"keng"	,	PY_mb_keng},
{"536600"	,	"leng"	,	PY_mb_leng},
{"540000"	,	"ji"	,	PY_mb_ji},
{"540000"	,	"li"	,	PY_mb_li},
{"542000"	,	"jia"	,	PY_mb_jia},
{"542600"	,	"jian"	,	PY_mb_jian},
{"542600"	,	"jiao"	,	PY_mb_jiao},
{"542600"	,	"lian"	,	PY_mb_lian},
{"542600"	,	"liao"	,	PY_mb_liao},
{"542640"	,	"jiang"	,	PY_mb_jiang},
{"542640"	,	"liang"	,	PY_mb_liang},
{"543000"	,	"jie"	,	PY_mb_jie},
{"543000"	,	"lie"	,	PY_mb_lie},
{"546000"	,	"jin"	,	PY_mb_jin},
{"546000"	,	"lin"	,	PY_mb_lin},
{"546400"	,	"jing"	,	PY_mb_jing},
{"546400"	,	"ling"	,	PY_mb_ling},
{"546640"	,	"jiong"	,	PY_mb_jiong},
{"548000"	,	"jiu"	,	PY_mb_jiu},
{"548000"	,	"liu"	,	PY_mb_liu},
{"566400"	,	"kong"	,	PY_mb_kong},
{"566400"	,	"long"	,	PY_mb_long},
{"568000"	,	"kou"	,	PY_mb_kou},
{"568000"	,	"lou"	,	PY_mb_lou},
{"580000"	,	"ju"	,	PY_mb_ju},
{"580000"	,	"ku"	,	PY_mb_ku},
{"580000"	,	"lu"	,	PY_mb_lu},
{"580000"	,	"lv"	,	PY_mb_lv},
{"582000"	,	"kua"	,	PY_mb_kua},
{"582400"	,	"kuai"	,	PY_mb_kuai},
{"582600"	,	"juan"	,	PY_mb_juan},
{"582600"	,	"kuan"	,	PY_mb_kuan},
{"582600"	,	"luan"	,	PY_mb_luan},
{"582640"	,	"kuang"	,	PY_mb_kuang},
{"583000"	,	"jue"	,	PY_mb_jue},
{"583000"	,	"lue"	,	PY_mb_lue},
{"584000"	,	"kui"	,	PY_mb_kui},
{"586000"	,	"jun"	,	PY_mb_jun},
{"586000"	,	"kun"	,	PY_mb_kun},
{"586000"	,	"kuo"	,	PY_mb_kuo},
{"586000"	,	"lun"	,	PY_mb_lun},
{"586000"	,	"luo"	,	PY_mb_luo},
{"600000"	,	"o"	    ,	PY_mb_o},
{"620000"	,	"ma"	,	PY_mb_ma},
{"620000"	,	"na"	,	PY_mb_na},
{"624000"	,	"mai"	,	PY_mb_mai},
{"624000"	,	"nai"	,	PY_mb_nai},
{"626000"	,	"man"	,	PY_mb_man},
{"626000"	,	"mao"	,	PY_mb_mao},
{"626000"	,	"nan"	,	PY_mb_nan},
{"626000"	,	"nao"	,	PY_mb_nao},
{"626400"	,	"mang"	,	PY_mb_mang},
{"626400"	,	"nang"	,	PY_mb_nang},
{"630000"	,	"me"	,	PY_mb_me},
{"630000"	,	"ne"	,	PY_mb_ne},
{"634000"	,	"mei"	,	PY_mb_mei},
{"634000"	,	"nei"	,	PY_mb_nei},
{"636000"	,	"men"	,	PY_mb_men},
{"636000"	,	"nen"	,	PY_mb_nen},
{"636400"	,	"meng"	,	PY_mb_meng},
{"636400"	,	"neng"	,	PY_mb_neng},
{"640000"	,	"mi"	,	PY_mb_mi},
{"640000"	,	"ni"	,	PY_mb_ni},
{"642600"	,	"mian"	,	PY_mb_mian},
{"642600"	,	"miao"	,	PY_mb_miao},
{"642600"	,	"nian"	,	PY_mb_nian},
{"642600"	,	"niao"	,	PY_mb_niao},
{"642640"	,	"niang"	,	PY_mb_niang},
{"643000"	,	"mie"	,	PY_mb_mie},
{"643000"	,	"nie"	,	PY_mb_nie},
{"646000"	,	"min"	,	PY_mb_min},
{"646000"	,	"nin"	,	PY_mb_nin},
{"646400"	,	"ming"	,	PY_mb_ming},
{"646400"	,	"ning"	,	PY_mb_ning},
{"648000"	,	"miu"	,	PY_mb_miu},
{"648000"	,	"niu"	,	PY_mb_niu},
{"660000"	,	"mo"	,	PY_mb_mo},
{"666400"	,	"nong"	,	PY_mb_nong},
{"668000"	,	"mou"	,	PY_mb_mou},
{"680000"	,	"mu"	,	PY_mb_mu},
{"680000"	,	"nu"	,	PY_mb_nu},
{"680000"	,	"nv"	,	PY_mb_nv},
{"680000"	,	"ou"	,	PY_mb_ou},
{"682600"	,	"nuan"	,	PY_mb_nuan},
{"683000"	,	"nue"	,	PY_mb_nue},
{"686000"	,	"nuo"	,	PY_mb_nuo},
{"720000"	,	"pa"	,	PY_mb_pa},
{"720000"	,	"sa"	,	PY_mb_sa},
{"724000"	,	"pai"	,	PY_mb_pai},
{"724000"	,	"sai"	,	PY_mb_sai},
{"726000"	,	"pan"	,	PY_mb_pan},
{"726000"	,	"pao"	,	PY_mb_pao},
{"726000"	,	"ran"	,	PY_mb_ran},
{"726000"	,	"rao"	,	PY_mb_rao},
{"726000"	,	"sao"	,	PY_mb_sao},
{"726000"	,	"san"	,	PY_mb_san},
{"726400"	,	"pang"	,	PY_mb_pang},
{"726400"	,	"rang"	,	PY_mb_rang},
{"726400"	,	"sang"	,	PY_mb_sang},
{"730000"	,	"re"	,	PY_mb_re},
{"730000"	,	"se"	,	PY_mb_se},
{"734000"	,	"pei"	,	PY_mb_pei},
{"736000"	,	"pen"	,	PY_mb_pen},
{"736000"	,	"ren"	,	PY_mb_ren},
{"736000"	,	"sen"	,	PY_mb_sen},
{"736400"	,	"peng"	,	PY_mb_peng},
{"736400"	,	"reng"	,	PY_mb_reng},
{"736400"	,	"seng"	,	PY_mb_seng},
{"740000"	,	"pi"	,	PY_mb_pi},
{"740000"	,	"qi"	,	PY_mb_qi},
{"740000"	,	"ri"	,	PY_mb_ri},
{"740000"	,	"si"	,	PY_mb_si},
{"742000"	,	"qia"	,	PY_mb_qia},
{"742000"	,	"sha"	,	PY_mb_sha},
{"742400"	,	"shai"	,	PY_mb_shai},
{"742600"	,	"pian"	,	PY_mb_pian},
{"742600"	,	"piao"	,	PY_mb_piao},
{"742600"	,	"qian"	,	PY_mb_qian},
{"742600"	,	"qiao"	,	PY_mb_qiao},
{"742600"	,	"shan"	,	PY_mb_shan},
{"742600"	,	"shao"	,	PY_mb_shao},
{"742640"	,	"qiang"	,	PY_mb_qiang},
{"742640"	,	"shang ",	PY_mb_shang},
{"743000"	,	"pie"	,	PY_mb_pie},
{"743000"	,	"qie"	,	PY_mb_qie},
{"743000"	,	"she"	,	PY_mb_she},
{"743600"	,	"shen"	,	PY_mb_shen},
{"743640"	,	"sheng"	,	PY_mb_sheng},
{"744000"	,	"shi"	,	PY_mb_shi},
{"746000"	,	"pin"	,	PY_mb_pin},
{"746000"	,	"qin"	,	PY_mb_qin},
{"746400"	,	"ping"	,	PY_mb_ping},
{"746400"	,	"qing"	,	PY_mb_qing},
{"746640"	,	"qiong"	,	PY_mb_qiong},
{"746800"	,	"shou"	,	PY_mb_shou},
{"748000"	,	"qiu"	,	PY_mb_qiu},
{"748000"	,	"shu"	,	PY_mb_shu},
{"748200"	,	"shua"	,	PY_mb_shua},
{"748240"	,	"shuai"	,	PY_mb_shuai},
{"748260"	,	"shuan"	,	PY_mb_shuan},
{"748264"	,	"shuang",	PY_mb_shuang},
{"748400"	,	"shui"	,	PY_mb_shui},
{"748600"	,	"shun"	,	PY_mb_shun},
{"748600"	,	"shuo"	,	PY_mb_shuo},
{"760000"	,	"po"	,	PY_mb_po},
{"766400"	,	"rong"	,	PY_mb_rong},
{"766400"	,	"song"	,	PY_mb_song},
{"768000"	,	"pou"	,	PY_mb_pou},
{"768000"	,	"rou"	,	PY_mb_rou},
{"768000"	,	"sou"	,	PY_mb_sou},
{"780000"	,	"pu"	,	PY_mb_pu},
{"780000"	,	"qu"	,	PY_mb_qu},
{"780000"	,	"ru"	,	PY_mb_ru},
{"780000"	,	"su"	,	PY_mb_su},
{"782600"	,	"quan"	,	PY_mb_quan},
{"782600"	,	"ruan"	,	PY_mb_ruan},
{"782600"	,	"suan"	,	PY_mb_suan},
{"783000"	,	"que"	,	PY_mb_que},
{"784000"	,	"rui"	,	PY_mb_rui},
{"784000"	,	"sui"	,	PY_mb_sui},
{"786000"	,	"qun"	,	PY_mb_qun},
{"786000"	,	"run"	,	PY_mb_run},
{"786000"	,	"ruo"	,	PY_mb_ruo},
{"786000"	,	"sun"	,	PY_mb_sun},
{"786000"	,	"suo"	,	PY_mb_suo},
//{"800000"	,	"u"	,	PY_mb_space},
//{"800000"	,	"v"	,	PY_mb_space},
{"820000"	,	"ta"	,	PY_mb_ta},
{"824000"	,	"tai"	,	PY_mb_tai},
{"826000"	,	"tan"	,	PY_mb_tan},
{"826000"	,	"tao"	,	PY_mb_tao},
{"826400"	,	"tang"	,	PY_mb_tang},
{"830000"	,	"te"	,	PY_mb_te},
{"836400"	,	"teng"	,	PY_mb_teng},
{"840000"	,	"ti"	,	PY_mb_ti},
{"842600"	,	"tian"	,	PY_mb_tian},
{"842600"	,	"tiao"	,	PY_mb_tiao},
{"843000"	,	"tie"	,	PY_mb_tie},
{"846400"	,	"ting"	,	PY_mb_ting},
{"866400"	,	"tong"	,	PY_mb_tong},
{"868000"	,	"tou"	,	PY_mb_tou},
{"880000"	,	"tu"	,	PY_mb_tu},
{"882600"	,	"tuan"	,	PY_mb_tuan},
{"884000"	,	"tui"	,	PY_mb_tui},
{"886000"	,	"tun"	,	PY_mb_tun},
{"886000"	,	"tuo"	,	PY_mb_tuo},
{"920000"	,	"wa"	,	PY_mb_wa},
{"920000"	,	"ya"	,	PY_mb_ya},
{"920000"	,	"za"	,	PY_mb_za},
{"924000"	,	"wai"	,	PY_mb_wai},
{"924000"	,	"zai"	,	PY_mb_zai},
{"926000"	,	"wan"	,	PY_mb_wan},
{"926000"	,	"yan"	,	PY_mb_yan},
{"926000"	,	"yao"	,	PY_mb_yao},
{"926000"	,	"zan"	,	PY_mb_zan},
{"926000"	,	"zao"	,	PY_mb_zao},
{"926400"	,	"wang"	,	PY_mb_wang},
{"926400"	,	"yang"	,	PY_mb_yang},
{"926400"	,	"zang"	,	PY_mb_zang},
{"930000"	,	"ye"	,	PY_mb_ye},
{"930000"	,	"ze"	,	PY_mb_ze},
{"934000"	,	"wei"	,	PY_mb_wei},
{"934000"	,	"zei"	,	PY_mb_zei},
{"936000"	,	"wen"	,	PY_mb_wen},
{"936000"	,	"zen"	,	PY_mb_zen},
{"936400"	,	"weng"	,	PY_mb_weng},
{"936400"	,	"zeng"	,	PY_mb_zeng},
{"940000"	,	"xi"	,	PY_mb_xi},
{"940000"	,	"yi"	,	PY_mb_yi},
{"940000"	,	"zi"	,	PY_mb_zi},
{"942000"	,	"xia"	,	PY_mb_xia},
{"942000"	,	"zha"	,	PY_mb_zha},
{"942400"	,	"zhai"	,	PY_mb_zhai},
{"942600"	,	"xian"	,	PY_mb_xiao},
{"942600"	,	"xiao"	,	PY_mb_xiao},
{"942600"	,	"zhan"	,	PY_mb_zhan},
{"942600"	,	"zhao"	,	PY_mb_zhao},
{"942640"	,	"xiang"	,	PY_mb_xiang},
{"942640"	,	"zhang"	,	PY_mb_zhang},
{"943000"	,	"xie"	,	PY_mb_xie},
{"943000"	,	"zhe"	,	PY_mb_zhe},
{"943600"	,	"zhen"	,	PY_mb_zhen},
{"943640"	,	"zheng"	,	PY_mb_zheng},
{"944000"	,	"zhi"	,	PY_mb_zhi},
{"946000"	,	"xin"	,	PY_mb_xin},
{"946000"	,	"yin"	,	PY_mb_yin},
{"946400"	,	"xing"	,	PY_mb_xing},
{"946400"	,	"ying"	,	PY_mb_ying},
{"946640"	,	"xiong"	,	PY_mb_xiong},
{"946640"	,	"zhong"	,	PY_mb_zhong},
{"946800"	,	"zhou"	,	PY_mb_zhou},
{"948000"	,	"xiu"	,	PY_mb_xiu},
{"948000"	,	"zhu"	,	PY_mb_zhu},
{"948200"	,	"zhua"	,	PY_mb_zhua},
{"948240"	,	"zhuai"	,	PY_mb_zhuai},
{"948260"	,	"zhuan"	,	PY_mb_zhuan},
{"948264"	,	"zhuang",	PY_mb_zhuang},
{"948400"	,	"zhui"	,	PY_mb_zhui},
{"948600"	,	"zhun"	,	PY_mb_zhun},
{"948600"	,	"zhuo"	,	PY_mb_zhuo},
{"960000"	,	"wo"	,	PY_mb_wo},
{"960000"	,	"yo"	,	PY_mb_yo},
{"966400"	,	"yong"	,	PY_mb_yong},
{"966400"	,	"zong"	,	PY_mb_zong},
{"968000"	,	"you"	,	PY_mb_you},
{"968000"	,	"zou"	,	PY_mb_zou},
{"980000"	,	"wu"	,	PY_mb_wu},
{"980000"	,	"xu"	,	PY_mb_xu},
{"980000"	,	"yu"	,	PY_mb_yu},
{"980000"	,	"zu"	,	PY_mb_zu},
{"982600"	,	"xuan"	,	PY_mb_xuan},
{"982600"	,	"yuan"	,	PY_mb_yuan},
{"982600"	,	"zuan"	,	PY_mb_zuan},
{"983000"	,	"xue"	,	PY_mb_xue},
{"983000"	,	"yue"	,	PY_mb_yue},
{"984000"	,	"zui"	,	PY_mb_zui},
{"986000"	,	"xun"	,	PY_mb_xun},
{"986000"	,	"yun"	,	PY_mb_yun},
{"986000"	,	"zun"	,	PY_mb_zun},
{"986000"	,	"zuo"	,	PY_mb_zuo},
};

//Ò»¼¶ËÑË÷±í
short t9_local_index1[8]={1,	55,	87,	125,	181,	225,	304,	323};

//¶ş¼¶ËÑË÷±í

short t9_local_index2[8][8]={
{2,		12,		17,		0,	43,		0,	49,		0,},
{56,	64,		69,		0,	75,		80,	81,		0,},
{87,	97,		0,		0,	105,	0,	109,	0,},
{125,	135,	141,	0,	159,	0,	163,	0,},
{182,	192,	200,	0,	215,	0,	218,	0,},
{225,	238,	247,	0,	283,	0,	289,	0,},
{304,	309,	311,	0,	316,	0,	318,	0,},
{323,	336,	344,	0,	377,	0,	383,	0,},
};

char ascii_tab[8][4]={
	{'a','b','c', 0 },
	{'d','e','f', 0 },
	{'g','h','i', 0 },
	{'j','k','l', 0 },
	{'m','n','o', 0 },
	{'p','q','r','s'},
	{'t','u','v', 0 },
	{'w','x','y','z'},
};

                      
//ÊäÈë·¨×ª»»
static void do_switch(t9_input_t*input)
{
	int i;
	for(i=0;i<6;i++)
	{
	  input->mb_index[i]=(t9PY_index*)0;
	  input->pinyin_buf[i]=-1;
	}
	input->pinyin_count=0;
	input->pinyin_selected=0;
	for(i=0;i<14;i++)
	{
	   input->show_buf[i]=0;
	}
	input->show_offset=0;

	switch(input->input_mode)
	{
	case macro_t9_mode_cn :
		input->input_mode=macro_t9_mode_len;break;
	case macro_t9_mode_len:
		input->input_mode=macro_t9_mode_uen;break;
	case macro_t9_mode_uen:
		input->input_mode=macro_t9_mode_num;break;
	case macro_t9_mode_num:
		input->input_mode=macro_t9_mode_cn;break;
	default:
		input->input_mode=macro_t9_mode_cn;break;
	}
}

static void update_struct(t9_input_t*input,short index_begin)
{
	short i;
	char*ptr;
	short count;
	for(i=0;i<6&&(i+index_begin)<397;i++)
	{
		input->mb_index[i]=&input->index[index_begin+i];
	}
	//i--;
	//¸üĞÂÏÔ´æµÄĞÅÏ¢
	if(input->mb_index[input->pinyin_selected]!=(t9PY_index*)0)
	{
		ptr=input->mb_index[input->pinyin_selected]->PY_mb;
		count=pl_strlen(ptr);
		ptr+=input->show_offset; //Æ«ÒÆÁ¿
		count=count-input->show_offset>12?12:count-input->show_offset;
        for(i=0;i<count;i++)
		{
			input->show_buf[i]=*ptr++;
		}
		for(;i<14;i++)
		{
			input->show_buf[i]=0;
		}
	}
}

/*static void update_showbuf(t9_input_t*input)
{
	short i;
	char*ptr;
	short count;
	if(input->mb_index[input->pinyin_selected]!=(t9PY_index*)0)
	{
		ptr=input->mb_index[input->pinyin_selected]->PY_mb;
		count=pl_strlen(ptr);
		ptr+=input->show_offset; //Æ«ÒÆÁ¿
		count=count-input->show_offset>12?12:count-input->show_offset;
        for(i=0;i<count;i++)
		{
			input->show_buf[i]=*ptr++;
		}
		for(;i<14;i++)
		{
			input->show_buf[i]=0;
		}
	}
}*/

bool_t   t9_cn_searchhandler(t9_input_t*input)
{
	char  buf[7]={0,0,0,0,0,0,0};
	int   index_begin;
	int   i,j;
	int   count=0;

	for(i=0;i<6;i++)
	{
		if(input->pinyin_buf[i]>=0){
			buf[i]='2'+input->pinyin_buf[i];
			++count;
		}
		else{
			break;
		}
	}
	if(count>2) //ÊäÈë¸öÊı´óÓÚ2Ê±£¬ÒªÍ¨¹ı±È½Ï×Ö·û´®ÊÇ·ñÏàµÈÀ´
	{
		index_begin=t9_local_index2[input->pinyin_buf[0]][input->pinyin_buf[1]]; //»ñÈ¡Ë÷ÒıµÄÆğÊ¼µØÖ·
		for(i=2;i<count;i++)
		{
			for(j=index_begin;j<397;j++)
			{
				if(input->index[j].t9PY_T9[i]==buf[i]){
					index_begin=j;
					break;
					}
			}
			if(j>=397){
				for(j=i;j<6;j++)
				{
					input->pinyin_buf[j]=-1;//½«´íÎóµÄ¶¼Çå¿ÕÎªÁã¡£
				}
				break;  //Ä³´ÎËÑË÷Ê§°Ü,±íÃ÷¸Ã×éºÏÒÑ¾­³öÏÖÎÊÌâ£¬¹Ê½«ºóÃæµÄºöÂÔ
			}
		}//end for i=2;
		update_struct(input,index_begin);
		return _true;
	}//end if(count>2)
	else if(count==2)
	{
		if(t9_local_index2[input->pinyin_buf[0]][input->pinyin_buf[1]]!=0)
		{
			index_begin=t9_local_index2[input->pinyin_buf[0]][input->pinyin_buf[1]];

			update_struct(input,index_begin);

			return _true;
		}
		else
		{
			 input->pinyin_buf[1]=-1; //½«Õâ¸öÎŞĞ§ÊäÈëÈ¥³ı
			 index_begin=t9_local_index1[input->pinyin_buf[0]];

			 update_struct(input,index_begin);
		     return _true;
		}
	}//end else if
	else if(count==1)
	{
        index_begin=t9_local_index1[input->pinyin_buf[0]];

		update_struct(input,index_begin);
		return _true;
	}
	//ÆäËûÇé¿öÈçelse if(count==0)²»ÓÃ´¦Àí
	return _false;//Î´ÖªÊäÈë£»
}

bool_t t9_cn_keyhandler (t9_input_t*input,short key_id)
{
   short temp;
   short i;
	switch(key_id)
	{
	  case macro_t9_key_0           :
		   return _false;
	  case macro_t9_key_1           :
		   return _false;

	  case macro_t9_key_2           :
	  case macro_t9_key_3           :
	  case macro_t9_key_4           :
	  case macro_t9_key_5           :
	  case macro_t9_key_6           :
	  case macro_t9_key_7           :
	  case macro_t9_key_8           :
	  case macro_t9_key_9           :
		   if(input->pinyin_count<6)//»º´æÃ»Âú
		   {
			  input->pinyin_buf[input->pinyin_count]=key_id-2;//key_id=2Ê±ÊÇË÷Òı±í0ºÍ1µÄ0Î»ÖÃ
			  input->pinyin_count++;
		   }
		   break;

	 case macro_t9_key_space       :
	      return _false;
	 case macro_t9_key_backspace   :
		 if(input->pinyin_count>0)
		 {
			input->pinyin_count--;
			input->pinyin_buf[input->pinyin_count]=-1;//É¾³ıÒ»¸öÆ´Òô
			if(input->pinyin_count==0)//ÒªÊÇÉ¾³ıÁË×îºóÒ»¸öÆ´Òô
			{
			   for(i=0;i<6;i++)
		      {
	             input->pinyin_buf[i]=-1;   //´ËÊıÎª-1Ê±ÊÇÎŞĞ§Öµ£¬ÒòÎªËü»á×÷ÎªË÷ÒıÖµ(0-7)
		         input->mb_index[i]=(t9PY_index *)0;
		      }
		      for(i=0;i<12;i++)
		      {
			     input->show_buf[i]=0;
		      }
		      input->show_offset=0;
		      input->pinyin_count =0;  
		      input->pinyin_selected=0; //¸üĞÂ½á¹¹ĞÅÏ¢£¬×¼±¸ÏÂ´ÎµÄÊäÈë
			}//end if(input->pinyin_count==0)
			
		 }
		 else
		 {    //É¾³ıÊ±Òª¿´ÊÇÒªÉ¾³ıasciiÂë»¹ÊÇºº×Ö£¬»¹Òª¿´»º´æÊÇ·ñÒÑ¾­¿Õ
			 if(input->count>0){ //»º´æ·Ç¿Õ
				input->count--;
				if((unsigned char)input->buf[input->count]>0x7e){  //ÅĞ¶ÏÊÇºº×Ö»¹ÊÇasciiÂë,
                     input->buf[input->count]=0;    //ºº×ÖÉ¾³ıÁ½¸ö×Ö½Ú
			         input->count--;
			         input->buf[input->count]=0; 
				}else{
					input->buf[input->count]=0;  //asciiÂëÉ¾³ıÒ»¸ö×Ö½Ú
				}//end else 1
			 }//end if(input->count>0)
		 }//end else
		 //update_showbuf(input);//¸üĞÂÊı¾İ
		break;

	//case macro_t9_key_enter       :
	//	break;//ÏÈ²»¹Ü
	case macro_t9_key_exit        :
		break;//ÏÈ²»¹Ü
	case macro_t9_key_switch      : 
		do_switch(input);
		break;
	case macro_t9_key_pinyin0     :
	case macro_t9_key_pinyin1     :
	case macro_t9_key_pinyin2     :
	case macro_t9_key_pinyin3     :
	case macro_t9_key_pinyin4     :
	case macro_t9_key_pinyin5     :
		if(input->mb_index[key_id-15]!=(void*)0){  //µ±Ñ¡ÔñÁËÒ»¸ö¿ÕµÄÆ´ÒôÊ±²»´¦Àí
         input->pinyin_selected=key_id-15;
		 input->show_offset=0;//Æ«ÒÆÖØĞÂ±äÎª0
		}
		 break;
	case macro_t9_key_show_forward:  //Ç°½ø·­Ò³£¬Ñ¡ÖĞµÄÆ´ÒôµÄºº×Ö·­¹öÏÔÊ¾
	    input->show_offset+=12;
		if(input->mb_index[input->pinyin_selected]!=(void*)0){   //µ±Ç°ËùÑ¡µÄÆ´ÒôÎªÓĞĞ§Öµ
			 if((short)pl_strlen(input->mb_index[input->pinyin_selected]->PY_mb)<=input->show_offset){
				 input->show_offset-=12;                         //µ±Ç°Æ«ÒÆÁ¿ÊÇ·ñ»¹ÔÚÂë±íµÄÓĞĞ§Öµ·¶Î§ÄÚ
			 }
		 }
		 break;
	case macro_t9_key_show_back   : //ºóÍË·­Ò³
         if(input->show_offset>0)  //input->show_offset==0Ê±ÔÚµÚÒ»Ò³
		 input->show_offset-=12;
		 break;
	case macro_t9_key_word0       :
	case macro_t9_key_word1       :
	case macro_t9_key_word2       :
	case macro_t9_key_word3       :
	case macro_t9_key_word4       :
	case macro_t9_key_word5       :  
		temp=key_id-23;//tempÕâ¸öÊ±ºòÎªµ±Ç°ÏÔÊ¾µÄ6¸ö´ıÑ¡ºº×ÖÖĞµÄºÅÂë
		temp<<=1;//temp´ÓÆ«ÒÆ±äÎª×Ö½ÚÆ«ÒÆ
		if(input->show_buf[temp]!=0&&input->count<macro_t9_max_input_count)//Õâ¸öÑ¡ÏîÓĞĞ§
		{
		  input->buf[input->count]=input->show_buf[temp];
		  input->count++;
          input->buf[input->count]=input->show_buf[temp+1];
		  input->count++;//countÊÇ×Ö½ÚÊı£¬¶øtempÊÇ×ÖÆ«ÒÆ
		  
		  for(i=0;i<6;i++)
		  {
	        input->pinyin_buf[i]=-1;   //´ËÊıÎª-1Ê±ÊÇÎŞĞ§Öµ£¬ÒòÎªËü»á×÷ÎªË÷ÒıÖµ(0-7)
		    input->mb_index[i]=(t9PY_index *)0;
		  }
		  for(i=0;i<12;i++)
		  {
			  input->show_buf[i]=0;
		  }
		  input->show_offset=0;
		  input->pinyin_count =0;  
		  input->pinyin_selected=0; //¸üĞÂ½á¹¹ĞÅÏ¢£¬×¼±¸ÏÂ´ÎµÄÊäÈë
		}

		break;
	default:return _false;
	}

	return _true;
}

bool_t t9_en_keyhandler (t9_input_t*input,short key_id)
{
   short i;
	switch(key_id)
	{
	  case macro_t9_key_0           :
	  case macro_t9_key_1           :
        if(input->input_mode==macro_t9_mode_num){
            if(input->count<macro_t9_max_input_count){
			   input->buf[input->count]=key_id+48;//×ª»¯³ÉasciiÂë
			   input->count++;
			}
		}
		break;
	  case macro_t9_key_abc         : /*macro_t9_key_2*/
	  case macro_t9_key_def         : /*macro_t9_key_3*/
	  case macro_t9_key_ghi         : /*macro_t9_key_4*/ 
	  case macro_t9_key_jkl         : /*macro_t9_key_5*/ 
	  case macro_t9_key_mno         : /*macro_t9_key_6*/
	  case macro_t9_key_pqrs        : /*macro_t9_key_7*/
	  case macro_t9_key_tuv         : /*macro_t9_key_8*/
	  case macro_t9_key_wxyz        : /*macro_t9_key_9*/
		if(input->input_mode==macro_t9_mode_len){
			for(i=0;i<4;i++)
			{
				input->show_buf[i]=ascii_tab[key_id-2][i];//Ğ¡Ğ´×ÖÄ¸
			}

		}else if(input->input_mode==macro_t9_mode_uen){
			for(i=0;i<3;i++)
			{
				input->show_buf[i]=ascii_tab[key_id-2][i]-32;//´óĞ´×ÖÄ¸
			}
			if(ascii_tab[key_id-2][3]!=0){
				input->show_buf[3]=ascii_tab[key_id-2][3]-32;
			}else{
				input->show_buf[3]=0;
			}

		}else if(input->input_mode==macro_t9_mode_num)
		{
			if(input->count<macro_t9_max_input_count){
				input->buf[input->count]=key_id+48;//×ª»¯³ÉasciiÂë
				input->count++;
			}
		}
		break;
	 case macro_t9_key_space       :
	      return _false;
	 case macro_t9_key_backspace   :
			 if(input->count>0)
			 { //»º´æ·Ç¿Õ
				input->count--;
				if((unsigned char)input->buf[input->count]>0x7e){  //ÅĞ¶ÏÊÇºº×Ö»¹ÊÇasciiÂë,
                     input->buf[input->count]=0;    //ºº×ÖÉ¾³ıÁ½¸ö×Ö½Ú
			         input->count--;
			         input->buf[input->count]=0; 
				}else{
					input->buf[input->count]=0;  //asciiÂëÉ¾³ıÒ»¸ö×Ö½Ú
				}//end else 1
			 }//end if(input->count>0)
		break;

	case macro_t9_key_enter       :
		break;//ÏÈ²»¹Ü
	case macro_t9_key_exit        :
		break;//ÏÈ²»¹Ü
	case macro_t9_key_switch      :
		do_switch(input);
		break;//ÏÈ²»¹Ü
	case macro_t9_key_pinyin0     :
	case macro_t9_key_pinyin1     :
	case macro_t9_key_pinyin2     :
	case macro_t9_key_pinyin3     :
		if(input->input_mode==macro_t9_mode_len||
		   input->input_mode==macro_t9_mode_uen)
		{
		   if(input->show_buf[key_id-15]>0&&\
		      input->count<macro_t9_max_input_count){
		      input->buf[input->count]=input->show_buf[key_id-15]; 
		      input->count++;
		   }
		}
		break;  
	default:return _false;
	}
	return _true;
}




void t9_initialize(t9_input_t*input,t9PY_index*index)
{
	int i;
	for(i=0;i<macro_t9_max_input_count;i++)
	{
		input->buf[i]=0;
	}
	input->count=0;
	input->index=index;
	input->input_mode=macro_t9_mode_cn;
	for(i=0;i<6;i++)
	{
	  input->mb_index[i]=(t9PY_index*)0;
	  input->pinyin_buf[i]=-1;
	}
	input->pinyin_count=0;
	input->pinyin_selected=0;
	for(i=0;i<14;i++)
	{
	   input->show_buf[i]=0;
	}
	input->show_offset=0;
}







