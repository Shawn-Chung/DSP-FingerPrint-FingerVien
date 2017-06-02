


#include "bsp_header\z_I2C_master.h"
#include <csl_irq.h>  

uint8_t		cmos_end = 0 ;

void write_cmos_sensor(uint16_t addr, uint16_t para)
{
	cmos_end = 0 ; 
	I2C_ADDR = addr ;
	_delay_ms(1);
	I2C_DATA = para ;
	_delay_ms(1);
	while ( !cmos_end ) ;
	cmos_end = 0 ;
}

void cmos_CF400G_init()
{

//	write_cmos_sensor(	0x12  ,0x80); //Common Control A: Reset all registers to default values
//	write_cmos_sensor(	0x12  ,0x44); //14 Common Control A
	
	write_cmos_sensor(	0x00  ,0x10); //00 AGC Gain control
//	write_cmos_sensor(	0x03  ,0xF4); //84 Color saturation value		
//	write_cmos_sensor(	0x04  ,0x30); //34 Color hue control				  	
 //	write_cmos_sensor(	0x05  ,0x3E); //3E Pre-Amplifier gain				  	
	write_cmos_sensor(	0x06  ,0x28); //80 Brightness setting 
	write_cmos_sensor(	0x10  ,0x28);
			
/**/write_cmos_sensor(	0x11  ,0x40); //00 Data Format and Internal Clock 
		
/**///	write_cmos_sensor(	0x12  ,0x04); //14 Common Control A
/**/write_cmos_sensor(	0x13  ,0x00); //A3 Common Control B:ITU-656 disable 00
/**/write_cmos_sensor(	0x14  ,0x00); //04 Common Control C
/**/write_cmos_sensor(	0x15  ,0xC0); //00 Common Control D
	write_cmos_sensor(	0x17  ,0x1A);
	write_cmos_sensor(	0x18  ,0xBA);
	write_cmos_sensor(	0x19  ,0x03);
	write_cmos_sensor(	0x1A  ,0xF3);
	write_cmos_sensor(	0x1B  ,0x00);
	
//	write_cmos_sensor(	0x1F  ,0x01); //01 Output Format Format Control
	
	write_cmos_sensor(	0x20  ,0xc0); //C0 Common Control E
	
	write_cmos_sensor(	0x24  ,0x10); //10 AGC/AEC – Stable Operating Region – Upper Limit
	write_cmos_sensor(	0x25  ,0x8A); //8A AGC/AEC – Stable Operating Region – Lower Limit
/**/write_cmos_sensor(	0x26  ,0x00); //A2 Common Control F
	write_cmos_sensor(	0x27  ,0xE2); //E2 Common Control G
/**/write_cmos_sensor(	0x28  ,0x60); //20 Common Control H
	write_cmos_sensor(	0x2A  ,0x00); //00 Output Format – Frame Rate Adjust High
	write_cmos_sensor(	0x2B  ,0x00); //00 Data Format – Frame Rate Adjust Setting LSB
	write_cmos_sensor(	0x2D  ,0x04); //81 Common Control J
//	write_cmos_sensor(	0x2F  ,0x9D);
//	write_cmos_sensor(	0x30  ,0x00);
//	write_cmos_sensor(	0x31  ,0xC4);
						  
/**/write_cmos_sensor(	0x60  ,0x00); //06 Signal Process Control B 
//	write_cmos_sensor(	0x61  ,0xE0);
//	write_cmos_sensor(	0x62  ,0x88);
//	write_cmos_sensor(	0x63  ,0x11);
//	write_cmos_sensor(	0x64  ,0x89);
//	write_cmos_sensor(	0x65  ,0x00);
//	write_cmos_sensor(	0x67  ,0x94);
//	write_cmos_sensor(	0x68  ,0x7A);
//	write_cmos_sensor(	0x69  ,0x08);
/**/	
//	write_cmos_sensor(	0x6C  ,0x11); //11 Color Matrix – RGB Crosstalk Compensation – R Channel		   
//	write_cmos_sensor(	0x6D  ,0x33); //01 Color Matrix – RGB Crosstalk Compensation – G Channel
/**///	write_cmos_sensor(	0x6E  ,0x22); //06 Color Matrix – RGB Crosstalk Compensation– B Channel		 
//	write_cmos_sensor(	0x6F  ,0x00);
	write_cmos_sensor(	0x70  ,0x00);	 
	write_cmos_sensor(	0x71  ,0x00); //00 Common Mode Control L
	write_cmos_sensor(	0x72  ,0x10); //10 Data Format – HSYNC Rising Edge Delay LSB
	write_cmos_sensor(	0x73  ,0x50); //50 Data Format – HSYNC Falling Edge Delay LSB
	write_cmos_sensor(	0x74  ,0x20); //20 Common Mode Control M
	write_cmos_sensor(	0x75  ,0x00); //02 Common Mode Control N
	write_cmos_sensor(	0x76  ,0x00); //00 Common Mode Control O
//	write_cmos_sensor(	0x77  ,0xB5);

}
void cmos_D0307_init()
{
	//========= close output
	write_cmos_sensor(	0x43  ,0x00); 
	write_cmos_sensor(	0x44  ,0xa2); 
	
	//========= close some functions
	// open them after configure their parmameters
	write_cmos_sensor(	0x40  ,0x10); 
	write_cmos_sensor(	0x41  ,0x00); 			
	write_cmos_sensor(	0x42  ,0x10); //10//90 Debug_mode (data_delay_half_2pclk使能）否则不能读取FIFO时 				  	
/**/write_cmos_sensor(	0x47  ,0x00); //mode1,				  	
	write_cmos_sensor(	0x48  ,0xc3); //mode2, 	
	write_cmos_sensor(	0x49  ,0x00); //dither_mode 		
	write_cmos_sensor(	0x4a  ,0x00); //clock_gating_en
	write_cmos_sensor(	0x4b  ,0x00); //mode_reg3
/**/write_cmos_sensor(	0x4E  ,0x23); //sync mode
	write_cmos_sensor(	0x4F  ,0x01); //AWB, AEC, every N frame	
	
	//========= frame timing
	write_cmos_sensor(	0x01  ,0x6a); //HB
	write_cmos_sensor(	0x02  ,0x70); //VB 0x70
	write_cmos_sensor(	0x1C  ,0x00); //Vs_st
	write_cmos_sensor(	0x1D  ,0x00); //Vs_et
	write_cmos_sensor(	0x10  ,0x00); //high 4 bits of VB, HB
	write_cmos_sensor(	0x11  ,0x05); //row_tail,  AD_pipe_number
	
	
	//========= windowing
	write_cmos_sensor(	0x05  ,0x00); //row_start
	write_cmos_sensor(	0x06  ,0x00);
	write_cmos_sensor(	0x07  ,0x00); //col start
	write_cmos_sensor(	0x08  ,0x00); 
	write_cmos_sensor(	0x09  ,0x01); //win height
	write_cmos_sensor(	0x0A  ,0xE8);
	write_cmos_sensor(	0x0B  ,0x02); //win width, pixel array only 640
	write_cmos_sensor(	0x0C  ,0x80);
	
	//========= analog
	write_cmos_sensor(	0x0D  ,0x22); //rsh_width
					  
/**/	write_cmos_sensor(	0x0E  ,0x02); //CISCTL mode2,  
/**/	write_cmos_sensor(	0x0F  ,0x32); //32  CISCTL mode1 ///////////////////////////////////////
			  
	write_cmos_sensor(	0x12  ,0x70); //7 hrst, 6_4 darsg,
/**/	write_cmos_sensor(	0x13  ,0x00); //7 CISCTL_restart, 0 apwd /////////////////////////////////
	write_cmos_sensor(	0x14  ,0x00); //NA
	write_cmos_sensor(	0x15  ,0xba); //7_4 vref
	write_cmos_sensor(	0x16  ,0x13); //5to4 _coln_r,  __1to0__da18
	write_cmos_sensor(	0x17  ,0x52); //opa_r, ref_r, sRef_r
	write_cmos_sensor(	0x18  ,0xc0); //analog_mode, best case for left band.
	
	write_cmos_sensor(	0x1E  ,0x0d); //tsp_width 		   
	write_cmos_sensor(	0x1F  ,0x32); //sh_delay
	
	//========= offset
/**/	write_cmos_sensor(	0x47  ,0x00);  //7__test_image, __6__fixed_pga, __5__auto_DN, __4__CbCr_fix, 
				//__3to2__dark_sequence, __1__allow_pclk_vcync, __0__LSC_test_image
	write_cmos_sensor(	0x19  ,0x06);  //pga_o			 
	write_cmos_sensor(	0x1a  ,0x06);  //pga_e			 
	
	write_cmos_sensor(	0x31  ,0x00);  //4	//pga_oFFset ,	 high 8bits of 11bits
	write_cmos_sensor(	0x3B  ,0x00);  //global_oFFset, low 8bits of 11bits
	
/**/	write_cmos_sensor(	0x59  ,0x0f);  //offset_mode 	
	write_cmos_sensor(	0x58  ,0x88);  //DARK_VALUE_RATIO_G,  DARK_VALUE_RATIO_RB
	write_cmos_sensor(	0x57  ,0x08);  //DARK_CURRENT_RATE
	write_cmos_sensor(	0x56  ,0x77);  //PGA_OFFSET_EVEN_RATIO, PGA_OFFSET_ODD_RATIO
	
	//========= blk
/**/	write_cmos_sensor(	0x35  ,0xd8);  //blk_mode

	write_cmos_sensor(	0x36  ,0x40);  
	
	write_cmos_sensor(	0x3C  ,0x00); 
	write_cmos_sensor(	0x3D  ,0x00); 
	write_cmos_sensor(	0x3E  ,0x00); 
	write_cmos_sensor(	0x3F  ,0x00); 
	
	write_cmos_sensor(	0xb5  ,0x70); 
	write_cmos_sensor(	0xb6  ,0x40); 
	write_cmos_sensor(	0xb7  ,0x00); 
	write_cmos_sensor(	0xb8  ,0x38); 
	write_cmos_sensor(	0xb9  ,0xc3); 		  
	write_cmos_sensor(	0xba  ,0x0f); 
	
	write_cmos_sensor(	0x7e  ,0x35); 
	write_cmos_sensor(	0x7f  ,0x86); 
	
/**/	write_cmos_sensor(	0x5c  ,0x68); //78
/**/	write_cmos_sensor(	0x5d  ,0x78); //88
	
	
	//========= manual_gain 
	write_cmos_sensor(	0x61  ,0x80); //manual_gain_g1	
	write_cmos_sensor(	0x63  ,0x80); //manual_gain_r
	write_cmos_sensor(	0x65  ,0x98); //manual_gai_b, 0xa0=1.25, 0x98=1.1875
	write_cmos_sensor(	0x67  ,0x80); //manual_gain_g2
/**/	write_cmos_sensor(	0x68  ,0x18); //global_manual_gain	 2.4bits
	
	//=========CC _R
/**/	write_cmos_sensor(	0x69  ,0x58);  //54
/**/	write_cmos_sensor(	0x6A  ,0xf6);  //ff
/**/	write_cmos_sensor(	0x6B  ,0xfb);  //fe
/**/	write_cmos_sensor(	0x6C  ,0xf4);  //ff
/**/	write_cmos_sensor(	0x6D  ,0x5a);  //5f
/**/	write_cmos_sensor(	0x6E  ,0xe6);  //e1

/**/	write_cmos_sensor(	0x6f  ,0x00); 	//手册上没有这个寄存器
	
	//=========lsc							  
	write_cmos_sensor(	0x70  ,0x14); 
	write_cmos_sensor(	0x71  ,0x1c); 
	write_cmos_sensor(	0x72  ,0x20); 
	
	write_cmos_sensor(	0x73  ,0x10); 	
	write_cmos_sensor(	0x74  ,0x3c); 
	write_cmos_sensor(	0x75  ,0x52); 
	
	//=========dn																			 
/**/	write_cmos_sensor(	0x7d  ,0x2f);  //dn_mode   	
	write_cmos_sensor(	0x80  ,0x0c); //when auto_dn, check 7e,7f
	write_cmos_sensor(	0x81  ,0x0c);
	write_cmos_sensor(	0x82  ,0x44);
																						
	//dd																		   
	write_cmos_sensor(	0x83  ,0x18);  //DD_TH1 					  
	write_cmos_sensor(	0x84  ,0x18);  //DD_TH2 					  
	write_cmos_sensor(	0x85  ,0x04);  //DD_TH3 																							  
/**/	write_cmos_sensor(	0x87  ,0x34);  //32 b DNDD_low_range X16,  DNDD_low_range_C_weight_center					
	
	   
	//=========intp-ee																		   
/**/	write_cmos_sensor(	0x88  ,0x04);  													   
/**/	write_cmos_sensor(	0x89  ,0x01);  										  
/**/	write_cmos_sensor(	0x8a  ,0x60);//60  										   
/**/	write_cmos_sensor(	0x8b  ,0x60);//60  										   
	write_cmos_sensor(	0x8c  ,0x07);  												 				  
																					  
	write_cmos_sensor(	0x50  ,0x0c);   						   		
/**/	write_cmos_sensor(	0x5f  ,0x3c); 																					 
																					 
	write_cmos_sensor(	0x8e  ,0x02);  															  
	write_cmos_sensor(	0x86  ,0x02);  																  
																					
	write_cmos_sensor(	0x51  ,0x20);  																
	write_cmos_sensor(	0x52  ,0x08);  
	write_cmos_sensor(	0x53  ,0x00); 
	
	
	//========= YCP 
	//contrast_center																			  
	write_cmos_sensor(	0x77  ,0x80); //contrast_center 																  
	write_cmos_sensor(	0x78  ,0x00); //fixed_Cb																		  
	write_cmos_sensor(	0x79  ,0x00); //fixed_Cr																		  
	write_cmos_sensor(	0x7a  ,0x00); //luma_offset 																																							
	write_cmos_sensor(	0x7b  ,0x40); //hue_cos 																		  
	write_cmos_sensor(	0x7c  ,0x00); //hue_sin 																		  
																							 
	//saturation																				  
	write_cmos_sensor(	0xa0  ,0x40); //global_saturation
	write_cmos_sensor(	0xa1  ,0x40); //luma_contrast																	  
/**/	write_cmos_sensor(	0xa2  ,0x34); //saturation_Cb																	  
/**/	write_cmos_sensor(	0xa3  ,0x34); //saturation_Cr
																				
	write_cmos_sensor(	0xa4  ,0xc8); 																  
	write_cmos_sensor(	0xa5  ,0x02); 
	write_cmos_sensor(	0xa6  ,0x28); 																			  
	write_cmos_sensor(	0xa7  ,0x02); 
	
	//skin																								  
	write_cmos_sensor(	0xa8  ,0xee); 															  
	write_cmos_sensor(	0xa9  ,0x12); 															  
	write_cmos_sensor(	0xaa  ,0x01); 														  
	write_cmos_sensor(	0xab  ,0x20); 													  
	write_cmos_sensor(	0xac  ,0xf0); 														  
	write_cmos_sensor(	0xad  ,0x10); 															  
		
	//========= ABS
/**/	write_cmos_sensor(	0xae  ,0x18); 
	write_cmos_sensor(	0xaf  ,0x74); 
	write_cmos_sensor(	0xb0  ,0xe0); 	  
	write_cmos_sensor(	0xb1  ,0x20); 
	write_cmos_sensor(	0xb2  ,0x6c); 
	write_cmos_sensor(	0xb3  ,0x40); 
	write_cmos_sensor(	0xb4  ,0x04); 
		
	//========= AWB 
	write_cmos_sensor(	0xbb  ,0x42); 
	write_cmos_sensor(	0xbc  ,0x60); 
	write_cmos_sensor(	0xbd  ,0x50); 
	write_cmos_sensor(	0xbe  ,0x50); 
	
	write_cmos_sensor(	0xbf  ,0x0c); 
	write_cmos_sensor(	0xc0  ,0x06); 
	write_cmos_sensor(	0xc1  ,0x70); 
/**/	write_cmos_sensor(	0xc2  ,0xf1);  //f4
	write_cmos_sensor(	0xc3  ,0x40); 
/**/	write_cmos_sensor(	0xc4  ,0x20); //18
	write_cmos_sensor(	0xc5  ,0x33); 
	write_cmos_sensor(	0xc6  ,0x1d);   

	write_cmos_sensor(	0xca  ,0x70); 
	write_cmos_sensor(	0xcb  ,0x70); 
	write_cmos_sensor(	0xcc  ,0x78);
	
	write_cmos_sensor(	0xcd  ,0x80); //R_ratio 									 
/**/	write_cmos_sensor(	0xce  ,0x80); //G_ratio  , cold_white white 								   
	write_cmos_sensor(	0xcf  ,0x80); //B_ratio  	
	
	//=========  aecT  
	write_cmos_sensor(	0x20  ,0x02); 
	write_cmos_sensor(	0x21  ,0xc0); 
	write_cmos_sensor(	0x22  ,0x60);    
	write_cmos_sensor(	0x23  ,0x88); 
	write_cmos_sensor(	0x24  ,0x96); 
	write_cmos_sensor(	0x25  ,0x30); 
	write_cmos_sensor(	0x26  ,0xd0); 
	write_cmos_sensor(	0x27  ,0x00); 
	
/**/	write_cmos_sensor(	0x28  ,0x01); //AEC_exp_level_1bit11to8   
/**/	write_cmos_sensor(	0x29  ,0xf4); //AEC_exp_level_1bit7to0	  
/**/	write_cmos_sensor(	0x2a  ,0x02); //AEC_exp_level_2bit11to8   
/**/	write_cmos_sensor(	0x2b  ,0xbc); //AEC_exp_level_2bit7to0			 
/**/	write_cmos_sensor(	0x2c  ,0x03); //AEC_exp_level_3bit11to8   659 - 8FPS,  8ca - 6FPS  //	 
/**/	write_cmos_sensor(	0x2d  ,0xe8); //AEC_exp_level_3bit7to0			 
/**/	write_cmos_sensor(	0x2e  ,0x09); //AEC_exp_level_4bit11to8   4FPS 
/**/	write_cmos_sensor(	0x2f  ,0xc4); //AEC_exp_level_4bit7to0	 
	
	write_cmos_sensor(	0x30  ,0x20); 						  
	write_cmos_sensor(	0x31  ,0x00); 					   
	write_cmos_sensor(	0x32  ,0x1c); 
	write_cmos_sensor(	0x33  ,0x90); 			  
	write_cmos_sensor(	0x34  ,0x10);	
	
	write_cmos_sensor(	0xd0  ,0x34); 
			   
/**/	write_cmos_sensor(	0xd1  ,0x50); //AEC_target_Y						   
	write_cmos_sensor(	0xd2  ,0xf2); 	  
	write_cmos_sensor(	0xd4  ,0x96); 
	write_cmos_sensor(	0xd5  ,0x10); 
	write_cmos_sensor(	0xd6  ,0x96); //antiflicker_step 					   
/**/	write_cmos_sensor(	0xd7  ,0x10); //AEC_exp_time_min 			   
	write_cmos_sensor(	0xd8  ,0x02); 
			   
/**/	write_cmos_sensor(	0xdd  ,0x12); 
	  															
	//========= measure window										
	write_cmos_sensor(	0xe0  ,0x03); 						 
	write_cmos_sensor(	0xe1  ,0x02); 							 
	write_cmos_sensor(	0xe2  ,0x27); 								 
	write_cmos_sensor(	0xe3  ,0x1e); 				 
	write_cmos_sensor(	0xe8  ,0x3b); 					 
	write_cmos_sensor(	0xe9  ,0x6e); 						 
	write_cmos_sensor(	0xea  ,0x2c); 					 
	write_cmos_sensor(	0xeb  ,0x50); 					 
	write_cmos_sensor(	0xec  ,0x73); 		 
	
	//========= close_frame													
	write_cmos_sensor(	0xed  ,0x00); //close_frame_num1 ,can be use to reduce FPS				 
	write_cmos_sensor(	0xee  ,0x00); //close_frame_num2  
	write_cmos_sensor(	0xef  ,0x00); //close_frame_num
	
	// page1
	write_cmos_sensor(	0xf0  ,0x01); //select page1 
	
	write_cmos_sensor(	0x00  ,0x20); 							  
	write_cmos_sensor(	0x01  ,0x20); 							  
	write_cmos_sensor(	0x02  ,0x20); 									
	write_cmos_sensor(	0x03  ,0x20); 							
	write_cmos_sensor(	0x04  ,0x78); 
	write_cmos_sensor(	0x05  ,0x78); 					 
	write_cmos_sensor(	0x06  ,0x78); 								  
	write_cmos_sensor(	0x07  ,0x78); 									 
	
	
	
	write_cmos_sensor(	0x10  ,0x04); 						  
	write_cmos_sensor(	0x11  ,0x04);							  
	write_cmos_sensor(	0x12  ,0x04); 						  
	write_cmos_sensor(	0x13  ,0x04); 							  
	write_cmos_sensor(	0x14  ,0x01); 							  
	write_cmos_sensor(	0x15  ,0x01); 							  
	write_cmos_sensor(	0x16  ,0x01); 						 
	write_cmos_sensor(	0x17  ,0x01); 						 
		  
													 
	write_cmos_sensor(	0x20  ,0x00); 					  
	write_cmos_sensor(	0x21  ,0x00); 					  
	write_cmos_sensor(	0x22  ,0x00); 						  
	write_cmos_sensor(	0x23  ,0x00); 						  
	write_cmos_sensor(	0x24  ,0x00); 					  
	write_cmos_sensor(	0x25  ,0x00); 						  
	write_cmos_sensor(	0x26  ,0x00); 					  
	write_cmos_sensor(	0x27  ,0x00);  						  
	
	write_cmos_sensor(	0x40  ,0x11); 
	
	//=============================lscP 
	write_cmos_sensor(	0x45  ,0x06); 	 
	write_cmos_sensor(	0x46  ,0x06); 			 
	write_cmos_sensor(	0x47  ,0x05); 
	
	write_cmos_sensor(	0x48  ,0x04); 	
	write_cmos_sensor(	0x49  ,0x03); 		 
	write_cmos_sensor(	0x4a  ,0x03); 
	

	write_cmos_sensor(	0x62  ,0xd8); 
	write_cmos_sensor(	0x63  ,0x24); 
	write_cmos_sensor(	0x64  ,0x24); 
	write_cmos_sensor(	0x65  ,0x24); 
	write_cmos_sensor(	0x66  ,0xd8); 
	write_cmos_sensor(	0x67  ,0x24);
	
	write_cmos_sensor(	0x5a  ,0x00); 
	write_cmos_sensor(	0x5b  ,0x00); 
	write_cmos_sensor(	0x5c  ,0x00); 
	write_cmos_sensor(	0x5d  ,0x00); 
	write_cmos_sensor(	0x5e  ,0x00); 
	write_cmos_sensor(	0x5f  ,0x00); 
	
	
	//============================= ccP 
	
	write_cmos_sensor(	0x69  ,0x03); //cc_mode
		  
	//CC_G
	write_cmos_sensor(	0x70  ,0x5d); 
	write_cmos_sensor(	0x71  ,0xed); 
	write_cmos_sensor(	0x72  ,0xff); 
	write_cmos_sensor(	0x73  ,0xe5); 
	write_cmos_sensor(	0x74  ,0x5f); 
	write_cmos_sensor(	0x75  ,0xe6); 
	
      //CC_B
	write_cmos_sensor(	0x76  ,0x41); 
	write_cmos_sensor(	0x77  ,0xef); 
	write_cmos_sensor(	0x78  ,0xff); 
	write_cmos_sensor(	0x79  ,0xff); 
	write_cmos_sensor(	0x7a  ,0x5f); 
	write_cmos_sensor(	0x7b  ,0xfa); 	 
	
	
	//============================= AGP
	
	write_cmos_sensor(	0x7e  ,0x00);  
	write_cmos_sensor(	0x7f  ,0x00);  
	write_cmos_sensor(	0x80  ,0xc8);  
	write_cmos_sensor(	0x81  ,0x06);  
	write_cmos_sensor(	0x82  ,0x08);  
	
	write_cmos_sensor(	0x83  ,0x23);  
	write_cmos_sensor(	0x84  ,0x38);  
	write_cmos_sensor(	0x85  ,0x4F);  
	write_cmos_sensor(	0x86  ,0x61);  
	write_cmos_sensor(	0x87  ,0x72);  
	write_cmos_sensor(	0x88  ,0x80);  
	write_cmos_sensor(	0x89  ,0x8D);  
	write_cmos_sensor(	0x8a  ,0xA2);  
	write_cmos_sensor(	0x8b  ,0xB2);  
	write_cmos_sensor(	0x8c  ,0xC0);  
	write_cmos_sensor(	0x8d  ,0xCA);  
	write_cmos_sensor(	0x8e  ,0xD3);  
	write_cmos_sensor(	0x8f  ,0xDB);  
	write_cmos_sensor(	0x90  ,0xE2);  
	write_cmos_sensor(	0x91  ,0xED);  
	write_cmos_sensor(	0x92  ,0xF6);  
	write_cmos_sensor(	0x93  ,0xFD);  
	
	//about gamma1 is hex r oct
	write_cmos_sensor(	0x94  ,0x04);  
	write_cmos_sensor(	0x95  ,0x0E);  
	write_cmos_sensor(	0x96  ,0x1B);  
	write_cmos_sensor(	0x97  ,0x28);  
	write_cmos_sensor(	0x98  ,0x35);  
	write_cmos_sensor(	0x99  ,0x41);  
	write_cmos_sensor(	0x9a  ,0x4E);  
	write_cmos_sensor(	0x9b  ,0x67);  
	write_cmos_sensor(	0x9c  ,0x7E);  
	write_cmos_sensor(	0x9d  ,0x94);  
	write_cmos_sensor(	0x9e  ,0xA7);  
	write_cmos_sensor(	0x9f  ,0xBA);  
	write_cmos_sensor(	0xa0  ,0xC8);  
	write_cmos_sensor(	0xa1  ,0xD4);  
	write_cmos_sensor(	0xa2  ,0xE7);  
	write_cmos_sensor(	0xa3  ,0xF4);  
	write_cmos_sensor(	0xa4  ,0xFA); 
	
	//========= open functions	
	write_cmos_sensor(	0xf0  ,0x00); //set back to page0	
																		  
	write_cmos_sensor(	0x45  ,0x27);
	write_cmos_sensor(	0x40  ,0x7e); 
	write_cmos_sensor(	0x41  ,0x2F);
/**/	write_cmos_sensor(	0x47  ,0x2c); 	
	
	//=========delay 200ms
	_delay_ms(200);
	//=========open output
/**/	write_cmos_sensor(	0x43  ,0x40);
/**/	write_cmos_sensor(	0x44  ,0xf2); ///e2//f2
}
void cmos_write_end (void)
{
	cmos_end = 1 ;
}


