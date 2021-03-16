#include <absacc.h>
#include <reg51.h>
#define IN6 XBYTE[0x7ffe]
sbit ad_busy=P3^3;
uchar idata ad[20];

void ad0809(p,n)
 uchar idata *p;
 uchar n;  //通道数为n
{  uchar i;
   uchar xdata *ad_adr;
   ad_adr=&IN6;    
   for (i=0;i<n;i++)
    { *ad_adr=0;
      i=i;
      i=i;
      while (ad_busy==0);
      *p++=*ad_adr;
    }
}
main()
{ 
  ad0809(ad,20);
}
