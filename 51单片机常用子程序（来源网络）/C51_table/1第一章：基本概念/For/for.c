#include<reg51.h>
void Ledon();
void Ledoff();
void Delayx10ms(Byte count);
void ForDemo2(Byte ontime,offtime)
{ Byte i;
  for(i=0;i<3;i++)		//������
	{Ledon();
	 Delayx10ms(ontime);
 	 Ledoff();
	 Delayx10ms(offtime);
	}
}
