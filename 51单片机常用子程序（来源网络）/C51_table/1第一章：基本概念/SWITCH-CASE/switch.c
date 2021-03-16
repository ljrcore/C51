#include<at89x51.h>
void Switchdemo(void)
{	Byte outputstate;
	switch(outputstate)
	{case 1:
		P1_0=0;
		P1_1=0;
		P1_2=0;
		break; 	//跳出循环
	case 2:
		P1_0=1;
		P1_1=0;
		P1_2=0;
		break;	//跳出循环
	default:
		break;
	}
}
