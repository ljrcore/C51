#include<reg51.h>
#define Byte unsigned char
#define Word unsigned int
Byte DisplayState;
Byte DISPLAY_TABLE10[];

void Delayx1ms(Byte count);

void IfDemo1(void)
{	Byte i,j;
	if(DisplayState<10)
		for(i=0;i<5;i++)				//һ��ɨ�裨5��LED��
			{j=5*DisplayState;			//
			 P2=DISPLAY_TABLE10[j+i];
			 P1=0x01<<i;
			 Delayx1ms(3);
             }
}

