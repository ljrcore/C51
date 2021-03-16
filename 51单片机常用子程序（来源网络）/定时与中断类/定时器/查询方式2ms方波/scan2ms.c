/*fosc=12MHz,要求P2.0输出T=2ms的方波.*/
/*使用查询方式*/
#include <reg51.H>
sbit p2_0=P2^0;
main()
{TMOD=0X01;TR0=1;
 for(;;)
 {TH0=-1000/256;
  TL0=-1000%256;
  do{}while(!TF0);
  p2_0=!p2_0;
  TF0=0;
  }
 }