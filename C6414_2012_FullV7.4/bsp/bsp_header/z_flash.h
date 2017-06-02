#ifndef __FLASH_H__
#define __FLASH_H__

#include "z_cpld_cmd.h"
#include "z_mytype.h"


#define FLASH_TIMEOUT			0x07FFFFFF

/*------the informations of the flash chip SST39VF6401B------*/
#define FLASH_CHIP_SIZE			0x00400000  //  4M Words
#define FLASH_PAGE_SIZE			0x00100000  //  1M Words
#define FLASH_BLOCK_SIZE		0x00008000  // 32K Words
#define FLASH_SECTOR_SIZE		0x00000800  //  2K Words
/*------每一页的空间分配--------------------------------------*/
#define FLASH_BLOCK_COUNT		0x00000020  //  每页32 Blocks
#define FLASH_SECTOR_COUNT		0x00000200  //  每页512 Sectors
#define FLASH_BASE_ADDR			0x64000000  //  每页的起始地址

/*-----------setting the address to fit the system-----------*/
#define sysAddress(offset) ((volatile uint16_t*)(FLASH_BASE_ADDR + (((uint32_t)offset)<<1)))


void flash_select_page(uint8_t page_num) ;
void flash_init(void) ;
void  flash_reset_chip(void) ;
int32_t flash_check_chip(void) ;
static int32_t flash_polling_check(uint32_t addr) ;
int32_t flash_erase_sector(uint32_t sector_addr) ;
int32_t flash_erase_block(uint32_t block_addr) ;
int32_t flash_erase_chip(void) ;
int32_t flash_write_word(uint32_t addr, uint16_t data) ;
int32_t flash_write_sector(uint32_t addr ,uint16_t *pSrc) ;
int32_t flash_write_block(uint32_t addr,uint16_t *pSrc) ;
uint8_t flash_read_byte(uint32_t addr) ;
uint16_t flash_read_word(uint32_t addr) ;






#endif

