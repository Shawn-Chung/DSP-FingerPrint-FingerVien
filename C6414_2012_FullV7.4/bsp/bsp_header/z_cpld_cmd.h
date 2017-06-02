

#ifndef __CPLD_CMD_H__
#define __CPLD_CMD_H__


#define CPLD_CMD( cmd )         ( ( *( uint16_t * ) 0x6C0CCCC0 ) = cmd )


/*----- Flash Page Select -------*/
#define FLASH_PAGE_0     		 CPLD_CMD(0x11)
#define FLASH_PAGE_1    		 CPLD_CMD(0x12)
#define FLASH_PAGE_2     		 CPLD_CMD(0x13)
#define FLASH_PAGE_3     		 CPLD_CMD(0x14)

/*----- LCD Backlight Command ----*/
#define LCD_BAKCLIGHT_ON         CPLD_CMD(0x21)
#define LCD_BAKCLIGHT_OFF        CPLD_CMD(0x22)

#define LCD_SET			         CPLD_CMD(0x23)// µ ±œ‘ æ
#define LCD_SAVE_IMAGE			 CPLD_CMD(0x24)//¥ÊÕº∆¨
#define LCD_RT_DISPLAY		     CPLD_CMD(0x2B)//
//#define LCD_DSP_OK			     CPLD_CMD(0x2d)//
#define LCD_SAVE_TO_RT		     ( *( uint16_t * ) 0x6C0000c0 = 0x00 )
#define AL422B_DATA				 ( *( uint16_t * ) 0x6C044440 )

#define LCD_CMD_BEGIN		     CPLD_CMD(0x25)//
#define LCD_DATA_BEGIN			 CPLD_CMD(0x26)//
#define LCD_TRANSFER_END		 CPLD_CMD(0x27)
#define LCD_INSIDE_RESET		 CPLD_CMD(0x28)
#define _74HC573_LE_H			 CPLD_CMD(0x29)
#define _74HC573_LE_L			 CPLD_CMD(0x2A)
/*----- Buzzer Command -----------*/
#define BUZZER_ON                CPLD_CMD(0x31)
#define BUZZER_OFF               CPLD_CMD(0x32)
#define BUZZER_TIP             	 CPLD_CMD(0x33)

/*----- FIFO Command -------------*/
#define FIFO_MASTER_RESET_ON     CPLD_CMD(0x41)
#define FIFO_MASTER_RESET_OFF    CPLD_CMD(0x42)
#define FIFO_PARTIAL_RESET_ON    CPLD_CMD(0x43)
#define FIFO_PARTIAL_RESET_OFF   CPLD_CMD(0x44)
#define FIFO_RETRANSMIT_ON       CPLD_CMD(0x45)
#define FIFO_RETRANSMIT_OFF      CPLD_CMD(0x46)
#define FIFO_WRITE_ON            CPLD_CMD(0x47)
#define FIFO_WRITE_OFF           CPLD_CMD(0x48)

/*----- GT23L32S4W CS Command ----*/
#define GT23L32S4W_CS_ON         CPLD_CMD(0x51)
#define GT23L32S4W_CS_OFF        CPLD_CMD(0x52)

/*----- LED Power Command --------*/
#define VISUAL_LED_POWER_ON      CPLD_CMD(0x61)
#define VISUAL_LED_POWER_OFF     CPLD_CMD(0x62)

/*----- Image Capture Command --------*/
#define FINGER_VEIN_CAPTURE      CPLD_CMD(0x71)
#define FINGER_PRINT_CAPTURE     CPLD_CMD(0x72)

/*----- KEY Reset Command --------*/
#define KEY_RESET_ON     		 CPLD_CMD(0x81)


/*----- I2C Command --------*/
#define I2C_ADDR		         ( *( uint16_t * ) 0x6C080040 )
#define I2C_DATA                 ( *( uint16_t * ) 0x6C080080 )

#define FINGER_I2C_ON     		 CPLD_CMD(0x91)
#define VISUAL_I2C_ON     		 CPLD_CMD(0x92)



#define LIGHT_UP     			 CPLD_CMD(0xA1) 
#define LIGHT_DOWN     			 CPLD_CMD(0xA2)






#endif /* __CPLD_CMD_H__ */





