#include<at89x51.h>
void Delayx1ms(Byte count);
void Ifdemo3(void){Byte FgpulseShort,FgpulseLong,Dutycount;
 while(P1_0==0)						//不为0跳过
		{Delayx1ms(1);				//当检测到P1_0为低电平时计数直到P1_0变高，
	 if(P1_0==0)Dutycount++;		//意在检测低电平宽度
	 }
 if((3<Dutycount)&&(Dutycount<13))	//当Dutycout在3与13之间时
	FgpulseShort=1;
 else if((13<Dutycount)&&(Dutycount<23))//当Dutycountz在13与23之间时
	FgpulseLong=1;
}
