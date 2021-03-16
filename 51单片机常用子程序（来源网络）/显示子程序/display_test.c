#include <reg51.h>   
#define BYTE unsigned char   
#define WORD unsigned int             
const BYTE DATA_7SEG[ ] ={0xc0,0xF9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
BYTE led[4],min,sec,dms;
//delay()________________________________________________
void delay(BYTE t)
{BYTE i;
 for (i=0;i<t;i++);
} 
//delay10ms()____________________________________________
void delay10ms(WORD count)
{WORD i,j,k;
 for(i=0;i<count;i++)
 for(j=0;j<10;j++)
 for(k=0;k<120;k++)
 ;
}
//display()______________________________________________________
void display(void)
{BYTE i;
 for (i=0;i<4;i++)
   {P1=~(1<<i);        //低电平驱位选
    P0=DATA_7SEG[led[i]];
    delay(255);    //about 1.5ms
    }
 P0=0xff;
 P1=0xff;
}
void disp_init(void)
{   BYTE i;
    led[0]=8;
    led[1]=8;
    led[2]=8;
    led[3]=8;
    for(i=0;i<200;i++)
         display();
    delay10ms(100);
    led[0]=0;
    led[1]=1;
    led[2]=2;
    led[3]=3;
    for(i=0;i<50;i++)
         display();
    delay10ms(50);
    led[0]=4;
    led[1]=5;
    led[2]=6;
    led[3]=7;
    for(i=0;i<50;i++)
        display();
    delay10ms(50);
    led[0]=8;
    led[1]=9;
    led[2]=0;
    led[3]=0;
    for(i=0;i<50;i++)
         display();
    delay10ms(50);
}
//Time0()_________________________________________________________
void Time0(void)interrupt 1 using 1
{TL0=0xf0;
 TH0=0xd8;
 TR0=1;
 dms++;
 if(dms>99)
	{ dms=0; 
      sec++;
	  if (sec>59)
	     {sec=0;
	      min++;
	      if(min>59)min=0;
	     }
	}
}
//________________________________________________________________
void main(void)
{ BYTE j;
  P0=0xff;
  P1=0xff;
  P2=0xff;
  P3=0xff;
  TMOD=0X01;
  TL0=0xf0;
  TH0=0xd8;
  ET0=1;
  EA=1;
  disp_init();  //初始化显示
  delay10ms(200);
  TR0=1;
  while(1)
    {	 ET0=0;
         led[3]=min/10;
	     led[2]=min%10;
	     led[1]=sec/10;
	     led[0]=sec%10;
         ET0=1;
         for(j=0;j<10;j++)
             display();
   }
}

