/*Ӳ��������AT89C51,MAX232��ADC0809��NF555��ɣ�555��������ADC0809��CLK��
���ں�����300��K�������ѹֱ�Ӽ���ADC0809��IN0����Ϊ��ֻ��һ·����ADC0809��
A��B��C������ַ��ֱ�ӽӵء�ADC0809��ALE��StartART������һ���ɵ�Ƭ����P3.4���ơ�*/

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

/*VB���������ý��մ���ϣ�������㽨�裡 

������û�б�Ҫʹ��EOC�ܽţ�����ֱ������ʱ�ȴ��Ϳ����ˣ�����ǰ��EOC�����й���ѵ [�����]*/
 

