/****************************************************************************************
                          PS2 �����Լ���ʵ��											*
���ӷ��� �� P0����J12���� �ο�����ñ�öŰ�������������P3.2  ������P1.6  ���� 		    *
ʹ�÷�����  ���ⲿ�ж϶�ȡPS2���̵����� �������������ʾ���˳���ֻ�������ּ��̡�	    *
 																						*
���ఴ�������û�����������չ��Ϊ�˳���򵥱����Ķ���ѧϰ��������û��ʹ����żУ�飬	    *
У�������������ӡ�           	*														*
														         	                    *
*****************************************************************************************/

#include<reg52.h>       

sbit LS138A=P2^2;  
sbit LS138B=P2^3;
sbit LS138C=P2^4; 

sbit BEEP = P1^5;

sbit Key_Data = P1^6 ;   //�����������
sbit Key_CLK = P3^2;     //ʹ���ⲿ�ж�

/******************************************************************/
/*                    ��������                                    */
/******************************************************************/
void Decode(unsigned char ScanCode);  //�����ӳ���
void delay(unsigned int i);      //��������
void display();
void beep();


// �˱�Ϊ LED ����ģ            // 0    1    2    3    4    5    6   7    8    9    A    b    c    d    E    -    L   P    U    Hidden  _ (20)
unsigned char code Disp_Tab[] = { ~0xC0,~0xF9,~0xA4,~0xB0,~0x99,~0x92,~0x82,~0xF8,~0x80,~0x90,~0x88,~0x83,~0xC6,~0xA1,~0x86,~0xbf,~0xc7,~0x8c,~0xc1, ~0xff,  ~0xf7 }; 
bit BF;          			
unsigned char KeyV;
unsigned char LedNumVal  ;
int KEY_val,IntNum;

/******************************************************************/
/*                    ������                                      */
/******************************************************************/
void main()
{

IT1 = 0;                              //���ⲿ�ж�1Ϊ�͵�ƽ����
EA = 1;                               //�ⲿ�жϿ�
EX0 = 1;                              //���ж�

  while(1)
 {
   if (BF)
    {  
	if (KeyV != 240)  beep();  
	  
       Decode(KeyV);	//����
	   
	  }
    else
      EA = 1; //���ж�	 
	  display();
 }

}

/******************************************************************/
/*                    �ⲿ�ж϶�����Ϣ                            */
/******************************************************************/
void Keyboard_out(void) interrupt 0
{
if ((IntNum > 0) && (IntNum < 9))
   { 
	KeyV = KeyV >> 1;                //����������ǵ�>>�ߣ������һ����������һλ
	if (Key_Data)
    	KeyV = KeyV | 0x80;          //������������Ϊ1ʱ�����λ
	}
	IntNum++;
	while (!Key_CLK);                //�ȴ�PS/2CLK����

	if (IntNum > 10)
	   { 
 		IntNum = 0;                  //���ж�11�κ��ʾһ֡�������꣬�����׼����һ�ν���
 		BF = 1;                      //��ʶ���ַ���������
		EA = 0;                      //���жϵ���ʾ����ٿ��ж� 
		}

  }

/******************************************************************/
/*                    ������Ϣ                                    */
/******************************************************************/
void Decode(unsigned char ScanCode) //ע��:��SHIFT+GΪ12H 34H F0H 34H F0H 12H��Ҳ����˵shift��ͨ��+G��ͨ��+shift�Ķ���+G�Ķ���
{
    
  	switch (ScanCode)
			{
			case 0x70 :             // ���յ�0xF0��Key_UP��1��ʾ���뿪ʼ
				KEY_val = 0;
				break;

			case 0x69 :             
				KEY_val = 1;
				break;

			case 0x72 :             
				KEY_val = 2;
				break;

			case 0x7A :             
			    KEY_val = 3;
				break;

			case 0x6B :             
				KEY_val = 4;
				break;

			case 0x73 :             
				KEY_val = 5;
				break;

			case 0x74 :             
				KEY_val = 6;
				break;

			case 0x6c :             
				KEY_val = 7;
				break;

			case 0x75 :             
				KEY_val = 8;
				break;

			case 0x7d :             
				KEY_val = 9;
				break;

		   case 0x71 :
		                
			//	dot = 0X7F;
				break;
	
	}
 	
  
BF = 0; //��ʶ�ַ��������� 	
} 


/***************************************************************************************/
void display( )
{
   unsigned char i;
   unsigned int LedOut[8];
 
   LedNumVal = KEY_val ;

	 //��ʾ��ֵ
	 LedOut[0]=Disp_Tab[KeyV%10000/1000];
     LedOut[1]=Disp_Tab[KeyV%1000/100];
     LedOut[2]=Disp_Tab[KeyV%100/10];
     LedOut[3]=Disp_Tab[KeyV%10];
	 
	 //��ʾ��Ӧ���ַ�
	 LedOut[4]=Disp_Tab[LedNumVal%10000/1000];	   //ǧλ
     LedOut[5]=Disp_Tab[LedNumVal%1000/100];  //��λ��С����
     LedOut[6]=Disp_Tab[LedNumVal%100/10];		   //ʮλ
     LedOut[7]=Disp_Tab[LedNumVal%10];             //��λ
	  
	
	 for( i=0; i<8; i++) 
	 {	 P0 = LedOut[i];
			
	  switch(i)					  
	     {	    
			case 0:LS138A=0; LS138B=0; LS138C=0; break;         
	        case 1:LS138A=1; LS138B=0; LS138C=0; break;             	
	        case 2:LS138A=0; LS138B=1; LS138C=0; break; 
	        case 3:LS138A=1; LS138B=1; LS138C=0; break; 
			case 4:LS138A=0; LS138B=0; LS138C=1; break;
			case 5:LS138A=1; LS138B=0; LS138C=1; break;
			case 6:LS138A=0; LS138B=1; LS138C=1; break;
			case 7:LS138A=1; LS138B=1; LS138C=1; break;
			
	     }
		 
		delay(50);
	  }
 
}

/***************************************************************************************
��ʱ����																			   *
****************************************************************************************/
void delay(unsigned int i)
{
    char j;
    for(i; i > 0; i--)
        for(j = 200; j > 0; j--);
}

/***************************************************************************************
����������																			   *
****************************************************************************************/
void beep()
{
  unsigned char i;
  for (i=0;i<255;i++)
   {
   delay(5);
   BEEP=!BEEP;                 //BEEPȡ��
   } 
  BEEP=1;                      //�رշ�����
}

