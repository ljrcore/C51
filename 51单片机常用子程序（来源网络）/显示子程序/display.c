#include <reg51.h>   
#define uchar unsigned char   
#define uint unsigned int             
const uchar DATA_7SEG[ ] ={0xc0,0xcf,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
uchar led[4],min,sec;
//delay()________________________________________________
void delay(uchar t)
{uchar i;
 for (i=0;i<t;i++);
} 
//delay10ms()____________________________________________
void delay10ms(uint count)
{uint i,j,k;
 for(i=0;i<count;i++)
 for(j=0;j<10;j++)
 for(k=0;k<120;k++)
 ;
}
//display()______________________________________________________
void display(void)
{uchar i;
 for (i=0;i<4;i++)
   {P1=~(1<<i);        //低电平驱位选
    P0=DATA_7SEG[led[i]];
    delay(255);    //about 1.5ms
    }
 P0=0xff;
 P1=0xff;
}
void disp_init(void)
{   uchar i;
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
//time0()_________________________________________________________
void time0(void)interrupt 1 using 1
{



}



//________________________________________________________________
void main(void)
{ uint i,j,temp;
  P0=0xff;
  P1=0xff;
  P2=0xff;
  P3=0xff;
  for(;;)
    {disp_init();  //初始化显示
     delay10ms(200);
     for (i=0;i<1000;i++)
	    {led[3]=i/1000;
         temp%=1000;
	     led[2]=temp/100;
		 temp%=100;
	     led[1]=temp/10;
	     led[0]=temp%10;
         for(j=0;j<50;j++)
             display();
		}
   }
}

