#include<at89x51.h>
void Ledon(void);
void Ledoff(void);
void Ifdemo4(void)
{Byte Ledcount;
 if(Ledcount<6)			//Ledcount<6����
	Ledon();
 else if(Ledcount<11)	//6��Ledcoun<11���
	Ledoff();
 else if(Ledcount<16)	//11��Ledount<16����
	Ledon();
 else if(Ledcount<68)	//16��Ledcount<68���
	Ledoff();
 else					//Ledcount>68����
	Ledcount=0;
}
