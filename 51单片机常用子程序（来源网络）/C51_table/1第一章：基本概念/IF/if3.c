#include<at89x51.h>
void Ledon(void);
void Ledoff(void);
void Ifdemo3(void)
{Byte Fgpulse;
 if(Fgpulse==0)
	{if(P1_7==0)
		{Fgpulse=1;
		 Ledon();
		 }
	 else
		{Fgpulse=0;
		 Ledoff();
		 }
	 }
 else
	{if(P1_7!=0)
		Fgpulse=0;
	}
}
