#include<at89x51.h>//全部为12MHz晶振
#include<intrins.h>
//************************1ms延时*************************************//
void delayx1ms(Word count)
{Word i,j;
 for(i=0;i<count;i++)
 for(j=0;j<138;j++);
}
//***********************************//
void delayx1ms1(Word count)
{Word j;
 while(count--!=0)
	for(j=0;j<72;j++);
}
//***********************************//
void delay1ms2(Byte count)
{Byte i,j,k;
 for(i=0;i<count;i++)
 for(j=0;j<40;j++)
 for(k=0;k<120;k++)
 ;
}
//************************10ms延时*************************************//
void delayx10ms(Word count)
{Word i,j,k;
 for(i=0;i<count;i++)
 for(j=0;j<10;j+)
 for(k=0;k<120;k++)
 ;
}
void delay10ms1(Word count)
{Word j,k;
 while(count--!=0)
    {for(j=0;j<10;j++)
     for(k=0;k<72;k++)
     ;
    }
}
//*************************50us延时****************************************//
void delay50us(Byte count)
{Byte i,j;
 for(j=0;j<count;j++)
 for(i=0;i<6;i++)
 ;
}
//*************************极短延时****************************************//
void shortdelay(Byte count)
{Byte i,j;
 for(i=0;i<count;i++)
 for(j=0;j<=140;j++)
 _nop_();
}
//*************************利用定时器的延时****************************************//
void timer40msdelay(byte count)
{t40mstimer=count;
 while(t40mstimer!=0);
}
void timer1isr_40ms(void)interrupt 3 using 2
{TH1=clock_40ms & 0xff;
 TL1=clock_40ms >> 8
 TF1=0;
 if(t40mstimer!=0)
 t40mstimer--;
	}