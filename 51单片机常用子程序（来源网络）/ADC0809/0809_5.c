/*硬件部分由AT89C51,MAX232，ADC0809，NF555组成，555用来产生ADC0809的CLK，
现在好像是300多K，输入电压直接加在ADC0809的IN0，因为我只用一路所以ADC0809的
A、B、C三个进址我直接接地。ADC0809的ALE和StartART我连在一起由单片机的P3.4控制。*/

#include <reg51.h>
sbit Start =P3^4;
sbit eoc=P3^3;
void delay(unsigned int count)
{ unsigned int i,j;
  for(i=0;i<count;i++)
  for(j=0;j<count;j++);
}
void send(unsigned char k)
{SBUF=k;
 while(!TI);
 TI=0;
}
unsigned char ad()
{ unsigned char temp;
  Start=0;
  Start=1;
  Start=0;
  while(!eoc);
  temp=P1;
  return(temp);
}
main()
{unsigned char temp;
 SCON=0x50;
 TMOD=0x20;
 TH1=0x0f3;
 TL1=0x0f3;         //2400bps
 EA=1;
 TR1=1;
 while(1)
 {
  temp=ad();
  send(temp); 
 }
}

/*VB端我已做好接收处理，希望你给提点建设！ 

程序中没有必要使用EOC管脚，可以直接用延时等待就可以了，我以前用EOC曾经有过教训 [李竹君]*/
 

