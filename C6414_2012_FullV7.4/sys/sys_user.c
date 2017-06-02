/******************************************************************************
 * 文件名：sys_global.c
 * 功能：  一些系统的全局变量和操作
******************************************************************************/


#include "sys_header/sys_user.h"

//获取数据库的指针
//static database_t*sys_get_database(void);
static void sys_db_clear_unit(uint32_t id   );  //擦除一个数据单元
//static sys_db_write_unit(uint32_t id,void*buf);//写一个数据单元
static void sys_lock_db  (void);
static void sys_unlock_db(void);
static void sys_set_id_map(uint32_t id);
static void sys_clear_id_map(uint32_t id);
static database_t dynamic_db;

inline static void sys_lock_db(void)
{
	extern far LCK_Obj flash_lock;
	
	LCK_pend(&flash_lock,SYS_FOREVER);
}

inline static void sys_unlock_db(void)
{
	extern far LCK_Obj flash_lock;
	
	LCK_post(&flash_lock);
}

 database_t*sys_get_database(void)
{
	return &dynamic_db;
}


void sys_db_clear_unit(uint32_t id)
{
	uint32_t page_addr;
	
//	sys_lock_db();

	flash_select_page(2);

    //用户ID号转化为flash中的页偏移地址
	//page_addr=id*4096+0x64000000;
	page_addr=id*8192+0x64000000;

	flash_erase_sector(page_addr);

	_delay_ms(18);

	//sys_unlock_db();
}


 void sys_db_write_unit(uint32_t id,void*buf)
{
	uint32_t page_addr;
	uint16_t *pBuf1 = (uint16_t *)(buf);
	uint16_t *pBuf2 = pBuf1 + 2048;

	flash_select_page(2);

	//用户ID号转化为flash中的页偏移地址
	//page_addr=id*4096+0x64000000;
	page_addr=id*8192+0x64000000;

    flash_erase_sector(page_addr);
	flash_erase_sector(page_addr+4096);
    _delay_ms(20);
	flash_write_sector(page_addr, buf);
	flash_write_sector(page_addr+4096, pBuf2);
}

static void sys_set_id_map(uint32_t id)
{
	uint32_t rows;
	uint32_t cols;

	database_t*db;
	db=sys_get_database();

	//16*32 = 512 = 1MWord/2KWord
	rows=id>>5;//id除以32
	cols=id&0x0000001f;//对32取余数
	
	db->id_map[rows]|=(1<<cols);
}

static void sys_clear_id_map(uint32_t id)
{
	uint32_t rows;
	uint32_t cols;
    uint32_t tmp;

	database_t*db;
	db=sys_get_database();

	rows=id>>5;//id除以32
	cols=id&0x0000001f;//对32取余数
	
	tmp=~(1<<cols);
	db->id_map[rows]&=tmp;
}


void sys_database_init(void)
{
	uint32_t    i;
	database_t *db;
	user_t     *user;
	uint32_t   *ptrs;
	uint32_t   *ptrd;

	db=sys_get_database();

	db->start_addr    =0x64000000;
	//db->unit_size     =4096;
	db->unit_size     =8192;
	db->all_cnt       =0;
	db->admin_cnt     =0;
	db->user_cnt       =0;
	db->dynamic_start_addr=0x80A00000; //第五页
	db->list_head     =(user_t*)0;
	db->list_current  =(user_t*)0;
    db->list_tail     =(user_t*)0;
    //for(i=0;i<16;i++){
	for(i=0;i<8;i++){
		db->id_map[i]=0;
	}

	//删除ID号数据
	//sys_db_clear_unit(2);

	flash_select_page(2);

	ptrs=(uint32_t*)db->start_addr;
	ptrd=(uint32_t*)db->dynamic_start_addr;

	//1页就为1M word  = 2M byte,每次复制32bit,故/4
	for(i=0;i<(0x00200000/4);i++)
	{
		*ptrd++=*ptrs++;
	}

	//for(i=0;i<512;i++){
	for(i=0;i<256;i++){
		//user=(user_t*)(db->dynamic_start_addr+i*4096);
		user=(user_t*)(db->dynamic_start_addr+i*8192);

		/*非法ID号略过*/
		//if(user->id>=512){
		if(user->id>=256){
			continue;
		}

		//第一个用户
		if(db->list_head==(user_t*)0){
			
			sys_set_id_map(user->id);

			db->list_current=user;
			db->list_head   =user;
			db->list_tail   =user;
			user->pre       =(user_t*)0;
			user->next      =(user_t*)0;
			db->all_cnt++;
			if(user->attribute==macro_db_administrator){
			    db->admin_cnt++;
			}else{
				db->user_cnt++;
			}
			continue;
		}

		//第二个以上的用户
		sys_set_id_map(user->id);
		user->pre=db->list_current;
		db->list_current->next=user;
		user->next=(user_t*)0;
		db->list_current=user;
		db->list_tail=user;
        db->all_cnt++;
		if(user->attribute==macro_db_administrator){
			db->admin_cnt++;
		}else{
			db->user_cnt++;
		}
		
	}//end for ( i=0...
}

void sys_database_init0(void)
{
	uint32_t    i;
	database_t *db;
	//user_t     *user;
	//uint32_t   *ptrs;
	//uint32_t   *ptrd;

	db=sys_get_database();

	db->start_addr    =0x64000000;
	//db->unit_size     =4096;
	db->unit_size     =8192;
	db->all_cnt       =0;
	db->admin_cnt     =0;
	db->user_cnt       =0;
	db->dynamic_start_addr=0x80A00000; //第五页
	db->list_head     =(user_t*)0;
	db->list_current  =(user_t*)0;
    db->list_tail     =(user_t*)0;
    //for(i=0;i<16;i++){
	 for(i=0;i<8;i++){
		db->id_map[i]=0;
	}

	//flash_select_page(2);

	//ptrs=(uint32_t*)db->start_addr;
	//ptrd=(uint32_t*)db->dynamic_start_addr;

	////1页就为1M word  = 2M byte,每次复制32bit,故/4
	//for(i=0;i<(0x00200000/4);i++)
	//{
	//	*ptrd++=*ptrs++;
	//}

	//for(i=0;i<512;i++){
	//	user=(user_t*)(db->dynamic_start_addr+i*4096);

	//	/*非法ID号略过*/
	//	if(user->id>=512){
	//		continue;
	//	}

	//	//第一个用户
	//	if(db->list_head==(user_t*)0){
	//		
	//		sys_set_id_map(user->id);

	//		db->list_current=user;
	//		db->list_head   =user;
	//		db->list_tail   =user;
	//		user->pre       =(user_t*)0;
	//		user->next      =(user_t*)0;
	//		db->all_cnt++;
	//		if(user->attribute==macro_db_administrator){
	//		    db->admin_cnt++;
	//		}else{
	//			db->user_cnt++;
	//		}
	//		continue;
	//	}

	//	//第二个以上的用户
	//	sys_set_id_map(user->id);
	//	user->pre=db->list_current;
	//	db->list_current->next=user;
	//	user->next=(user_t*)0;
	//	db->list_current=user;
	//	db->list_tail=user;
 //       db->all_cnt++;
	//	if(user->attribute==macro_db_administrator){
	//		db->admin_cnt++;
	//	}else{
	//		db->user_cnt++;
	//	}
	//	
	//}//end for ( i=0...
}


//这个函数只是简单地将这个用户连接到用户的列表里面，然后更新到flash。
bool_t  sys_database_add (user_t*user)
{
	database_t*db;
	
	sys_lock_db();

	db=sys_get_database();

	user->pre=db->list_tail;
	
	user->next=(user_t*)0;
	
	db->list_tail->next=user;

	db->list_tail=user;

	//更新到flash中
	sys_db_write_unit(user->id,user);

    if(user->attribute==macro_db_administrator){
       db->admin_cnt++;
    }else{
       db->user_cnt++;
    }
    
    db->all_cnt++;

	sys_unlock_db();

	return _true;
}

/*这个函数只是简单地将一个用户从SDRAM中删除，然后从删除FLASH中的存储*/
bool_t  sys_database_delete  (user_t*user)
{
	database_t *db;

	sys_lock_db();

	db=sys_get_database();

	//系统必须保留至少一个用户
	/*if( (db->all_cnt<=1 ) || ( db->list_head==user ) ){
		return _false;
	}*/
	
	if( db->all_cnt<=1 ){
	    return _false;
	}
	
	///*三种情况：1.在队列尾部，2.在队列中间。3.队列头部*/
	if( db->list_head==user){
	
      db->list_head=db->list_head->next;
      db->list_head->pre=(user_t*)0;
      
    }else if(db->list_tail==user){
        //1要删除的用户在尾部时
		db->list_tail=db->list_tail->pre;
		db->list_tail->next=(user_t*)0;
	}else{
		user->pre->next = user->next; 		
		user->next->pre = user->pre;
	}

//更改用户数量
   	if(user->attribute==macro_db_administrator){
       db->admin_cnt--;
    }else{
       db->user_cnt--;
    }
    
    db->all_cnt--;
    
	sys_db_clear_unit(user->id);

	//将该用户置为无用
	user->id=0xffffffff;
	
	sys_unlock_db();

	return _true;
}



user_t* sys_database_get_next(void       )
{
	database_t *db;

	db=sys_get_database();

	if(db->all_cnt<=1){

		return (user_t*)0;

	}else if(db->list_current==db->list_tail){

		db->list_current=db->list_head;
		return (user_t*)0;

	}else{

		db->list_current=db->list_current->next;
		return db->list_current;

	}//end else {
}


user_t* sys_database_get_pre (void       )
{
	database_t*db;

	db=sys_get_database();

	if(db->all_cnt<=1){
		return (user_t*)0;

	}else if( db->list_current==db->list_head ){

		db->list_current=db->list_tail;
		return (user_t*)0;

	}else{
		db->list_current=db->list_current->pre;
		return db->list_current;
	}//end else {
}


user_t* sys_database_get_head(void       )
{
	database_t*db;

	db=sys_get_database();

	return db->list_head;
}

user_t* sys_database_get_tail(void       )
{
	database_t*db;

	db=sys_get_database();

	return db->list_tail;
}


void    sys_database_go_to_head(void)
{
	database_t*db;

	db=sys_get_database();

	db->list_current=db->list_head;
}

void    sys_database_go_to_tail(void)
{
	database_t*db;

	db=sys_get_database();

	db->list_current=db->list_tail;
}

uint32_t sys_database_malloc_id  (void       )
{
	uint32_t i,j;
	database_t*db;
	uint32_t id;

	id=0xffffffff;

	db=sys_get_database();

	//for(i=0;i<16;i++)
	for (i = 0; i < 8; i++)
	{
		if(db->id_map[i]!=0xffffffff){
            for(j=0;j<32;j++){
				if(( db->id_map[i] & (1<<j) )==0){
					db->id_map[i]|=(1<<j);
					id=i*32+j;
					return id;
				}//end if ( (db->id_map...
			}//end for ( j=0...
		}//end if ( db->id...
	}//end for ( i=0...
	return id;
}

void  sys_database_free_id (uint32_t id)
{
	sys_clear_id_map(id);
}

user_t*  sys_database_malloc_user(uint32_t id)
{
	database_t*db;

	user_t*user;

	db=sys_get_database();

	//user=(user_t*)(db->dynamic_start_addr+id*4096);
	user=(user_t*)(db->dynamic_start_addr+id*8096);

	return user;	
}



/*user指向的数据结构不在SDRAM用户信息的队列中，必须先拷贝到队列中*/
bool_t sys_user_register(user_t*user)
{
	uint32_t*ptrs;
	uint32_t*ptrd;
    uint32_t id;
    uint32_t i;

	//先为此用户分配一个id号
	id=sys_database_malloc_id();
	//id = 0x0;
	if(id==0xffffffff){
		return _false;
	}

	//获取该id号的内存指针
	ptrd=(uint32_t*)sys_database_malloc_user(id);
	ptrs=(uint32_t*)user;
   
   user->id=id;
   //到这里user的数据必须要全部初始化好
   //拷贝数据
	//for(i=0;i<1024;i++){
   for(i=0;i<2048;i++){
		*ptrd++=*ptrs++;
	}
    //更新数据到数据库
    //ptrd-=1024;
	ptrd-=2048;
	return sys_database_add((user_t*)ptrd);
}


/*注销一个用户的信息*/
bool_t sys_user_unregister(user_t*user)
{
    sys_database_free_id(user->id);
	return sys_database_delete(user);
}

/*检测是否是普通用户*/
bool_t sys_is_normal_user(user_t*user)
{
	if(user->attribute==macro_db_normal_user){
		return _true;
	}else{
		return _false;
	}
}
/*检测一个用户是否是管理员*/
bool_t sys_is_administrator(user_t*user)
{
	if(user->attribute==macro_db_administrator){
		return _true;
	}
	else{
		return _false;
	}
}


