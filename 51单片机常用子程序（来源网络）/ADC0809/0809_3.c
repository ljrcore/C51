#include<absacc.h>
#include<reg51.h>
#define IN0 XBYTE[0x7ff8]   /*AD0809��ͨ��0��*/
sbit ad_busy=P3^3;           /*EOC״̬*/
void ad0809(uchar idata *x) 
{uchar i;
 uchar xdata *ad_adr;
 ad_adr=&IN0;
 for(i=0;i<8;i++)           /*����8ͨ��*/
    {*ad_adr=0;             /*����ת��*/
     i=i;                   /*��ʱ�ȴ�EOC���*/
     i=i;
     while(ad_busy==0);     /*��ѯ�ȴ�ת������*/
     x[i]=*ad_adr;          /*��ת�����*/
     ad_adr++;              /*��һͨ��*/
     }
 }
void main(void)
{static uchar idata ad[10];
 ad0809(ad);
}

