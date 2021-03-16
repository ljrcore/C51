#include<reg51.h>
#define uchar unsigned char
#define TR 1
uchar idata buf[10];
uchar pf;
void init(void)
{TMOD=0X20;                    /*定时方式2*/
TH1=0XE8;                      /*波特率*/
TL1=0XE8;
PCON=0X00;
TR1=1;
SCON=0X50;
}
void send(uchar idata *d)
{uchar i;
 do{SBUF=0XAA;                 /*发送联络信号*/
    while(TI==0);TI=0;         /*等待发送出去*/
    while(RI==0);RI=0;         /*等待B机回答*/
    }while((SBUF^0xbb)!=0);    /*B机未准备好,继续联络*/
 do{pf=0;                          /*清校验和*/
    for(i=0;i<16;i++)              
       {SBUF=d[i];                 
        pf+=d[i];                  /*求校验和*/
        while(TI==0);TI=0;         
        }
    SBUF=pf;                       /*发送校验和,并等待B机回答*/
    while(TI==0);TI=0;
    while(RI==0);RI=0;
   }while(SBUF!=0);                /*回答出错,重发*/
}
void receive(uchar idata *d)
{ uchar i;
  do{while(RI==0);RI=0;}
  while((SBUF^0xaa)!=0);           /*判断A机有无请求*/
  SBUF=0xbb;                       /*发应答信号*/
  while(TI==0);TI=0;
  while(1)
      {pf=0;                       /*清校验和*/
       for(i=0;i<16;i++)
          {while(RI==0);RI=0;
           d[i]=SBUF;
           pf+=d[i];               /*求检验和*/
          }
       while(RI==0);RI=0;          /*接收A机校验和*/
       if((SBUF^pf)==0)            /*比较校验和*/    
         {SBUF=0x00;break;}        /*相同发“00”*/
       else{SBUF=0xff;             /*出错发“FF”，重新接收*/
            while(TI==0);TI=0;
           }
      }
}
void main(void)
{
 init();
 if(TR==0){send(buf);}
 else{receive(buf);}
}
    
    
 