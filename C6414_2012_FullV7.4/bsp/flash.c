
#include "bsp_header\z_flash.h"


/****************************************************************************
* 名    称：flash_select_page(uint8_t page_num)
* 功    能：flash选页
* 入口参数：page_num		页码 0--3
* 出口参数：无
* 说    明：配合CPLD
* 调用方法：flash_select_page(1) ;
****************************************************************************/
void flash_select_page(uint8_t page_num)
{
    switch(page_num)
    {
       case 0: FLASH_PAGE_0 ; break ;
       case 1: FLASH_PAGE_1 ; break ;
       case 2: FLASH_PAGE_2 ; break ;
       case 3: FLASH_PAGE_3 ; break ;
       default:FLASH_PAGE_1 ; break ;
    }
}
/****************************************************************************
* 名    称：lash_init(void)
* 功    能：flash初始化 选中第一页 （第0页用于固化程序和字库）
* 入口参数：无
* 出口参数：无
* 说    明：配合CPLD
* 调用方法：flash_init(void);
****************************************************************************/
void flash_init(void)
{
    //默认选中第一页数据。
    flash_select_page(1);
}
/****************************************************************************
* 名    称：int32_t flash_polling_check(uint32_t addr)
* 功    能：flash轮询检忙
* 入口参数：addr		地址
* 出口参数：无
* 说    明：
* 调用方法：if (flash_polling_check(sector_addr));
****************************************************************************/
static int32_t flash_polling_check(uint32_t addr)
{
	uint16_t CurrData;
	uint32_t TimeOut = 0;

	while (TimeOut < FLASH_TIMEOUT)	//MAX_TIMEOUT=0x07FFFFFF
	{
		CurrData = *(volatile uint16_t *)(addr);
		CurrData = CurrData & 0x0080;//read DQ7
		if (CurrData == 0x0080)
		{
			return TRUE;
		}
		TimeOut++;
	}
	return FALSE;
}
/****************************************************************************
* 名    称：flash_reset_chip(void)
* 功    能：ID Exit\CFI Exit\Sec ID Exit
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：flash_reset_chip();
****************************************************************************/
void  flash_reset_chip(void)
{
	*sysAddress(0x555) = 0x00AA;  // write data 0x00AA to device addr 0x555
    *sysAddress(0x2AA) = 0x0055;  // write data 0x0055 to device addr 0x2AA
    *sysAddress(0x555) = 0x00F0;  // write data 0x00F0 to device addr 0x555
}
/****************************************************************************
* 名    称：flash_check_chip(void)
* 功    能：读取ID号判断是否正常
* 入口参数：无
* 出口参数：TRUE  or  FALSE
* 说    明：
* 调用方法：if(flash_check_chip());
****************************************************************************/
int32_t flash_check_chip(void)
{
	uint16_t id1 = 0;  //SST Manufacturer's ID code
	uint16_t id2 = 0;  //SST39VF6401B device code
	
    //Issue the Software Product ID code to 39VF640XB
    *sysAddress(0x555) = 0x00AA;  // write data 0x00AA to device addr 0x555
    *sysAddress(0x2AA) = 0x0055;  // write data 0x0055 to device addr 0x2AA
    *sysAddress(0x555) = 0x0090;  // write data 0x0090 to device addr 0x555
	//Tida Max 150ns for SST39VF6401B
    _delay_us(1);
	id1 = *sysAddress(0x0000);
	id2 = *sysAddress(0x0001);
    //Returning the SST39VF640X to the normal operation.
	flash_reset_chip();

	if ((id1==0x00BF) && (id2==0x236D))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
/****************************************************************************
* 名    称：flash_erase_sector(uint32_t sector_addr)
* 功    能：段擦除
* 入口参数：sector_addr  段地址 ，在段内的任何地址
* 出口参数：TRUE  or  FALSE
* 说    明：sector_addr 最小为 FLASH_BASE_ADDR	:0x64000000
*           在某个段地址范围内时擦除该段
*			在调用该函数之前一定要先选择页码
* 调用方法：flash_erase_sector(0x64000000);
****************************************************************************/
int32_t flash_erase_sector(uint32_t sector_addr)
{
	int32_t  i;
	//get the start address of the sector
	sector_addr &= 0xFFFFF800;
	//Issue the Sector Erase command to 39VF640X
	*sysAddress(0x555) = 0x00AA;     // write data 0x00AA to device addr 0x555
	*sysAddress(0x2AA) = 0x0055;     // write data 0x0055 to device addr 0x2AA
	*sysAddress(0x555) = 0x0080;     // write data 0x0080 to device addr 0x555
	*sysAddress(0x555) = 0x00AA;     // write data 0x00AA to device addr 0x555
	*sysAddress(0x2AA) = 0x0055;     // write data 0x0055 to device addr 0x2AA
	//write data 0x0050 to device sector addr
	*(volatile uint16_t *)sector_addr = 0x0050;

	if (flash_polling_check(sector_addr))
	{	//check sector erase succeed or not
		for (i = 0; i < FLASH_SECTOR_SIZE; i += 2)
		{
			if (*(volatile uint16_t *)(sector_addr + i) != 0xFFFF)
			{
				return FALSE;
			}
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
/****************************************************************************
* 名    称：flash_erase_block(uint32_t block_addr)
* 功    能：块擦除
* 入口参数：block_addr  块地址 ，在块内的任何地址
* 出口参数：TRUE  or  FALSE
* 说    明：sector_addr 最小为 FLASH_BASE_ADDR	:0x64000000
*           在某个块地址范围内时擦除该段
* 调用方法：flash_erase_block(0x64000000);
****************************************************************************/
int32_t flash_erase_block(uint32_t block_addr)
{
	int32_t  i;
	//get the start address of the block
	block_addr &= 0xFFFF8000;
	//Issue the Block Erase command to 39VF640X
	*sysAddress(0x555) = 0x00AA;     // write data 0x00AA to device addr 0x555
	*sysAddress(0x2AA) = 0x0055;     // write data 0x0055 to device addr 0x2AA
	*sysAddress(0x555) = 0x0080;     // write data 0x0080 to device addr 0x555
	*sysAddress(0x555) = 0x00AA;     // write data 0x00AA to device addr 0x555
	*sysAddress(0x2AA) = 0x0055;     // write data 0x0055 to device addr 0x2AA
	//write data 0x0030 to device block addr
	*(volatile uint16_t *)block_addr = 0x0030;

	if (flash_polling_check(block_addr))
	{	//check block erase succeed or not
		for (i = 0; i < FLASH_BLOCK_SIZE; i += 2)
		{
			if (*(volatile uint16_t *)(block_addr + i) != 0xFFFF)
			{
				return FALSE;
			}
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
/****************************************************************************
* 名    称：flash_erase_chip(void)
* 功    能：片擦除
* 入口参数：无
* 出口参数：TRUE  or  FALSE
* 说    明：
* 调用方法：flash_erase_chip();
****************************************************************************/
int32_t flash_erase_chip(void)
{
	//Issue the Chip Erase command to 39VF640X
	*sysAddress(0x555) = 0x00AA;     // write data 0x00AA to device addr 0x555
	*sysAddress(0x2AA) = 0x0055;     // write data 0x0055 to device addr 0x2AA
	*sysAddress(0x555) = 0x0080;     // write data 0x0080 to device addr 0x555
	*sysAddress(0x555) = 0x00AA;     // write data 0x00AA to device addr 0x555
	*sysAddress(0x2AA) = 0x0055;     // write data 0x0055 to device addr 0x2AA
	*sysAddress(0x555) = 0x0010;     // write data 0x0010 to device addr 0x555

	if (flash_polling_check(0))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
/****************************************************************************
* 名    称：flash_write_word(uint32_t addr, uint16_t data)
* 功    能：往flash地址写一个字：16bit
* 入口参数：addr		地址
*          data		数据
* 出口参数：TRUE  or  FALSE
* 说    明：
* 调用方法：flash_write_word(0x64000000, 0x5555);
****************************************************************************/
int32_t flash_write_word(uint32_t addr, uint16_t data)
{
    uint32_t TimeOut = 0;
	addr &= 0xFFFFFFFE;
	
    *sysAddress(0x555) = 0x00AA; // write data 0x00AA to device addr 0x555
    *sysAddress(0x2AA) = 0x0055; // write data 0x0055 to device addr 0x2AA
    *sysAddress(0x555) = 0x00A0; // write data 0x00A0 to device addr 0x555
	// transfer the WORD to destination
	*(volatile uint16_t *)addr = data;

    while (*(volatile uint16_t *)addr != data)
	{
		if (++TimeOut > FLASH_TIMEOUT)
		{
		    return FALSE;
		}
	}
	return TRUE;
}
/****************************************************************************
* 名    称：flash_write_sector(uint32_t addr ,uint16_t *pSrc)
* 功    能：往flash地址写一个段：4K Bytes
* 入口参数：addr		地址
*          *pSrc	数组首地址
* 出口参数：TRUE  or  FALSE
* 说    明：
* 调用方法：flash_write_sector(0x64000000, (uint16_t*)gImage_pic);
****************************************************************************/
int32_t flash_write_sector(uint32_t addr ,uint16_t *pSrc)
{
	uint32_t i;
    uint16_t *pBuf = pSrc;
	addr &= 0xFFFFF800;
	
	for (i = 0; i < FLASH_SECTOR_SIZE; i ++)
	{
		if (flash_write_word(addr + i*2, *pBuf))
		{
		   pBuf++;
		}
		else
		{
			return FALSE;
		}
	}
	return TRUE;  
}
/****************************************************************************
* 名    称：flash_write_block(uint32_t addr,uint16_t *pSrc)
* 功    能：往flash地址写一个段：64K Bytes
* 入口参数：addr		地址
*          *pSrc	数组首地址
* 出口参数：TRUE  or  FALSE
* 说    明：
* 调用方法：flash_write_block(0x64000000, (uint16_t*)gImage_pic);
****************************************************************************/
int32_t flash_write_block(uint32_t addr,uint16_t *pSrc)
{
	uint32_t i;
    uint16_t *pBuf = pSrc;
	addr &= 0xFFFF8000;
	
	for (i = 0; i < FLASH_BLOCK_SIZE; i++)
	{
		if (flash_write_word(addr + i*2, *pBuf))
		{
		   pBuf++;
		}
		else
		{
			return FALSE;
		}
	}
	return TRUE; 
}
/****************************************************************************
* 名    称：flash_read_byte(uint32_t addr)
* 功    能：从flash地址读取一个字节
* 入口参数：addr		地址
* 出口参数：
* 说    明：
* 调用方法：
****************************************************************************/
uint8_t flash_read_byte(uint32_t addr)
{
	return (*(volatile uint8_t *)addr);
}
/****************************************************************************
* 名    称：flash_read_word(uint32_t addr)
* 功    能：从flash地址读取一个字
* 入口参数：addr		地址
* 出口参数：
* 说    明：
* 调用方法：
****************************************************************************/
uint16_t flash_read_word(uint32_t addr)
{
	addr &= 0xFFFFFFFE;
	return (*(volatile uint16_t *)addr);
}











