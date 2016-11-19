#include <reg51.h>
#include "ir_lcd.h"

unsigned char first_prompt[9]= "Password:";
unsigned char new_prompt[13]= "New Password:";
unsigned char new_again_prompt[9]= "Re-enter:";
unsigned char chnge_prmpt_string[16]= "Change:Y(1)/N(0)";


sbit  buzzer = P3^5;
#define LED    P0
sbit  back_light_LCD = P2^4;	
unsigned char password_in[4]="****";
unsigned char password_st[4]="1234";
unsigned int  password_in_len= 0;
unsigned int  password_new_len   = 0;
unsigned int  password_newcfr_len =0;
unsigned char password_new[4]="****";
unsigned char password_newcfr[4]="****";
unsigned char prev_key_in, buffer;

void display_init()
{
		temp1=0x01; lcd_comm(); delay(100);		
		for(i=0;i<9;i++)
			{
				temp2 = (first_prompt[i]);
				lcd_data();
				delay(500);
			}
		temp1 = 0xC0; lcd_comm(); delay(100);
		temp1 = 0x0F; lcd_comm(); delay(150);
			for(i=0;i<4;i++)
			{
				temp2 = (password_in[i] );
				lcd_data();
				delay(500);
			}
		temp1 = 0xC0; lcd_comm(); delay(100);
		temp1 = 0x0F; lcd_comm(); delay(150);
		}


void ports_init(void)
	{
		P3_2 = 1;
		back_light_LCD= 1;
	}	


void display_chng_prompt()
{
	temp1=0x01; lcd_comm(); delay(100);
	for(i=0;i<16;i++)
	{
		temp2 = (chnge_prmpt_string[i]);
		lcd_data();
		delay(500);
	}
	temp1 = 0xC0; lcd_comm(); delay(100);
	temp1 = 0x0F; lcd_comm(); delay(150);
}

void display_newpass_prompt()
{
	temp1=0x01; lcd_comm(); delay(100);		
	for(i=0;i<13;i++)
	{
		temp2 = (new_prompt[i]);
		lcd_data();
		delay(500);
	}
	temp1 = 0xC0; lcd_comm(); delay(100);
	temp1 = 0x0F; lcd_comm(); delay(150);
}

void display_newpasscfr_prompt()
{
	temp1=0x01; lcd_comm(); delay(100);		
	for(i=0;i<9;i++)
	{
		temp2 = (new_again_prompt[i]);
		lcd_data();
		delay(500);
	}
	temp1 = 0xC0; lcd_comm(); delay(100);
	temp1 = 0x0F; lcd_comm(); delay(150);
}
void get_in_password()
{
	while(password_in_len<4)
			{
				buffer = remote();
				if (buffer!='X')
				{
					password_in[password_in_len]=buffer;
					password_in_len++;
					delay(10000);
				}
				temp1 = 0xC0; lcd_comm(); delay(100);
				temp1 = 0x0F; lcd_comm(); delay(150);
				for(i=0;i<password_in_len;i++)
				{
					temp2 = (password_in[i]);
					lcd_data();
					delay(500);
				}
			}
	
}
void get_new_password()
{
	while(password_new_len<4)
			{
				buffer = remote();
				if (buffer!='X')
				{
					password_new[password_new_len]=buffer;
					password_new_len++;
					delay(10000);
				}
				temp1 = 0xC0; lcd_comm(); delay(100);
				temp1 = 0x0F; lcd_comm(); delay(150);
				for(i=0;i<password_new_len;i++)
				{
					temp2 = (password_new[i]);
					lcd_data();
					delay(500);
				}
			}
}

void get_newcfr_password()
{
	while(password_newcfr_len<4)
			{
				buffer = remote();
				if (buffer!='X')
				{
					password_newcfr[password_newcfr_len]=buffer;
					password_newcfr_len++;
					delay(10000);
				}
				temp1 = 0xC0; lcd_comm(); delay(100);
				temp1 = 0x0F; lcd_comm(); delay(150);
				for(i=0;i<password_newcfr_len;i++)
				{
					temp2 = (password_newcfr[i]);
					lcd_data();
					delay(500);
				}
			}
}

void password_in_invalidate()
{
	password_in[0]='*';
  password_in[1]='*';
	password_in[2]='*';
  password_in[3]='*';
	password_in_len=0;
}

void password_new_invalidate()
{
	password_new[0]='*';
  password_new[1]='*';
	password_new[2]='*';
  password_new[3]='*';
	password_new_len=0;
	password_newcfr[0]='*';
  password_newcfr[1]='*';
	password_newcfr[2]='*';
  password_newcfr[3]='*';
	password_newcfr_len=0;
}	
void main(void)
{
		unsigned int i=0;
		ports_init();
		lcd_init();
		display_init();

			password_prmpt:
												  get_in_password();
													delay(10000);
			
			password_compare: 
													
													for(i=0;i<4;i++)
													{
														if(password_in[i]!=password_st[i])
														{
															buzzer = 0;
															delay(10000);
															buzzer = 1;
															password_in_invalidate();
															display_init();
															goto password_prmpt;
														}
													}
			password_input_true:
														password_in_invalidate();
														LED = 0x55;
														delay(25000);
													  LED =0xFF;
														display_chng_prompt();				
														buffer='X';
													
														while((buffer!='1')&&(buffer!='0'))
														{
															buffer=remote();
														}
														if(buffer=='1')
														{
															delay(10000);
															display_newpass_prompt();
															get_new_password();
															delay(10000);
															display_newpasscfr_prompt();
															get_newcfr_password();
															for(i=0;i<4;i++)
															{
																if(password_new[i]!=password_newcfr[i])
																{
																	buzzer = 0;
															    delay(10000);
															    buzzer = 1;
																	password_new_invalidate();
																	display_init();
																	goto password_prmpt;
																}
															}
															for(i=0;i<4;i++)
															{
																password_st[i]=password_new[i];
															}
																LED = 0x55;
														    delay(25000);
													      LED =0xFF;
														  password_new_invalidate();
															display_init();
															goto password_prmpt;
														}

														else
														{
															display_init();
															goto password_prmpt;
														}
				
			}