#include<reg51.h>
void Ledon();
void Ledoff();
void IfDemo2(void)
{Byte Ledcount;
 if(Ledcount<26)//如果还没有亮26次继续亮
	{Ledon();
	 Ledcount++;
	 }
 else			//否则灭灯
	Ledoff();
}
