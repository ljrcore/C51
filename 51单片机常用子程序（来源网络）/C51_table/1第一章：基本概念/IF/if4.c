#include<at89x51.h>
void Ledon(void);
void Ledoff(void);
void Ifdemo4(void)
{Byte Ledcount;
 if(Ledcount<6)			//Ledcount<6¡¡µ∆
	Ledon();
 else if(Ledcount<11)	//6°‹Ledcoun<11√µ∆
	Ledoff();
 else if(Ledcount<16)	//11°‹Ledount<16¡¡µ∆
	Ledon();
 else if(Ledcount<68)	//16°‹Ledcount<68√µ∆
	Ledoff();
 else					//Ledcount>68«Â¡„
	Ledcount=0;
}
