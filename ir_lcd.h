	/* The key pressed in the remote handset will be displayed on the LCD screen second line. */

	#include "lcd.h"

	int i=0,count=0,count1=0;
  unsigned char byte=0x00,recv_arr[6],key='0',key_obtnd = 0,key_ret = 0 ;
	unsigned char temp1=0x00;
	unsigned char temp2;

	unsigned char keypress(void);

	bit one_flag = 0;
	bit zero_flag = 0;
	bit p13flg = 0;
	bit p31flg = 0;
	sbit P3_2=P3^2;//sensor input line

	sbit P1_4=P1^4;//sensor input line
	sbit P1_5=P1^5;//sensor input line
	
	void comm_init(void)
	{
			TMOD = 0x01;
			TL0 = 0x99;	TH0 = 0x86;
			TCON = 0x00;	
	} 
	extern unsigned char remote(void)  //to detect the remote key & store the data in array
		{
			comm_init();
			zero_flag=1;
			one_flag=0;
			count1 = 0;
			
			while(P3_2==1); 
			TF0=0;//clear timer0 flag 
			TR0=1;//timer0 run control
			count=8;
			if( !P3_2) //if P3_2 is low //to get 1st zero after timer start
				{
					byte = byte >> 1;
					byte &= 0x7f;
					count--;
				}	
				while(count>0)
					{
						while(zero_flag)
							{
								if(TF0)  
									{ 
										TF0=0;
										recv_arr[3] = (recv_arr[3])&(0x07);//to get lsb of last byte
										key_obtnd = 0xff;//after collecting all byte come out of the loop
										break;
									}
								for(i=0;i<=105;i++)//for 1100 timer count,as we found from test program 
																//wrote for calculatin time for each bits
									{
										if(P3_2==1)
											{     
												p13flg = 1;
												break;
											}
									}
		
				if(!p13flg )
					{
						if( !P3_2)
							{	
								byte = byte >> 1;
								byte &= 0x7f;

						count--; 
						if(count == 0)
						{
							recv_arr[count1] = byte;
							count1=count1+1;
							byte = 0;
							count = 8;
						}
										 
						}
										
					}// end of if(!p13flg )
			 else 
				{
					if(P3_2)
					{
										 byte = byte >> 1;
									 byte |= 0x80;

						count--;
						if(count == 0)
						{
							recv_arr[count1] = byte;
							count1=count1+1;
							byte = 0;
							count = 8;

						}
					}
				}//end of else part of if(!p13flg )
					if(p13flg )
						{
							p13flg = 0;
							break;
						}

			
			} //end of while (zero_flag)

			if(key_obtnd)
				break;
			 zero_flag=0;
			 one_flag=1;
			 p31flg = 1;
			 while(one_flag)
				{
						 
							if(TF0)  
							{ 
									TF0=0;
							recv_arr[3] = (recv_arr[3])&(0x07);//to get lsb of last byte
					 key_obtnd = 0xff;
								break;	//after collecting all byte come out of the loop
							 }

						 for(i=0;i<=80;i++)//for 800 timer count,as we found from test program 
																//wrote for calculatin time for each bits
							{
							
							if(P3_2==0)
						{
							p31flg = 0;
							break;
									}
						}

				if(p31flg )
				{
						if( P3_2)
					{		
						byte = byte >> 1;
									byte |= 0x80;
													
						count--;
						if(count == 0)
						{
							recv_arr[count1] = byte;
							count1=count1+1;
							byte = 0;
							count = 8;
						}
						}
					}//end of if(p31flg ) 
			 else 
				{
					if( !P3_2)
					{
						byte = byte >> 1;
									byte &= 0x7f;
					
						count--;  
						if(count == 0)
						{
							recv_arr[count1] = byte;
							count1=count1+1;
							byte = 0;
							count = 8;
						}
						}
				}//end of else part of if(p31flg ) 
				if(!p31flg)
					{
						p31flg = 1;
						break;
					}
				
			}   //end of while(one_flag	)
			 
		if(key_obtnd)
				break;
			 zero_flag=1;
			 one_flag=0;
				 p13flg=0;

		}//end of while ( count > 0)

		key_obtnd = 0;
		
		TF0 = 0;
		TR0 = 0;
		recv_arr[count1++] = byte;
		
		key_ret = keypress(); 
		
		/* temp1 = 0xC7;
		lcd_comm();
		temp2 = key_ret;
		lcd_data(); */
		return key_ret;
	 }


	unsigned char keypress(void) //to check which key is pressed
	{ 
		if((recv_arr[2]==0X55)&& (recv_arr[3]==0X05))
				{
						key='0';          //key 0
				} 
		else if( (recv_arr[2]==0X55)&& (recv_arr[3]==0X03))
				{
						key='1';          //key 1 
				}  
		else if( (recv_arr[2]==0XD5)&& (recv_arr[3]==0X04))
				{
						key='2';          //key 2
				} 
		else if( (recv_arr[2]==0XD5)&& (recv_arr[3]==0X02))
				{
						key='3';          //key 3
				} 
		else if( (recv_arr[2]==0X35)&& (recv_arr[3]==0X05))
				{
						key='4';          //key 4 
				} 
		else if( (recv_arr[2]==0X35)&& (recv_arr[3]==0X03))
				{  
						key='5';          //key 5 
				}
		else if( (recv_arr[2]==0XB5)&& (recv_arr[3]==0X04))
				{
						key='6';          //key 6  
				} 
	 
		else if( (recv_arr[2]==0XB5)&& (recv_arr[3]==0X02))
				{
						key='7';          //key 7
				} 
		else if( (recv_arr[2]==0X4D)&& (recv_arr[3]==0X05))
				{
						key='8';          //key 8 
				} 
		else if( (recv_arr[2]==0X4D)&& (recv_arr[3]==0X03))
				{
						key='9';          //key 9
				} 
		else              
					{    
							key='X';          //if any other key is pressed
					}
	 
		return(key);

	}// end of key_press rtn - returns the key pressed