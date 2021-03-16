#include<absacc.h>
#include<reg51.h>
#define IN0 XBYTE[0x7ff8]   /*AD0809的通道0的*/
sbit ad_busy=P3^3;           /*EOC状态*/
void ad0809(uchar idata *x) 
{uchar i;
 uchar xdata *ad_adr;
 ad_adr=&IN0;
 for(i=0;i<8;i++)           /*处理8通道*/
    {*ad_adr=0;             /*启动转换*/
     i=i;                   /*延时等待EOC变低*/
     i=i;
     while(ad_busy==0);     /*查询等待转换结束*/
     x[i]=*ad_adr;          /*存转换结果*/
     ad_adr++;              /*下一通道*/
     }
 }
void main(void)
{static uchar idata ad[10];
 ad0809(ad);
}

