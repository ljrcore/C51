#include<at89x51.h>
void Delayx1ms(Byte count);
void Ifdemo3(void){Byte FgpulseShort,FgpulseLong,Dutycount;
 while(P1_0==0)						//��Ϊ0����
		{Delayx1ms(1);				//����⵽P1_0Ϊ�͵�ƽʱ����ֱ��P1_0��ߣ�
	 if(P1_0==0)Dutycount++;		//���ڼ��͵�ƽ���
	 }
 if((3<Dutycount)&&(Dutycount<13))	//��Dutycout��3��13֮��ʱ
	FgpulseShort=1;
 else if((13<Dutycount)&&(Dutycount<23))//��Dutycountz��13��23֮��ʱ
	FgpulseLong=1;
}
