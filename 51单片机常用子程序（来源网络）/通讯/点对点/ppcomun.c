#include<reg51.h>
#define uchar unsigned char
#define TR 1
uchar idata buf[10];
uchar pf;
void init(void)
{TMOD=0X20;                    /*��ʱ��ʽ2*/
TH1=0XE8;                      /*������*/
TL1=0XE8;
PCON=0X00;
TR1=1;
SCON=0X50;
}
void send(uchar idata *d)
{uchar i;
 do{SBUF=0XAA;                 /*���������ź�*/
    while(TI==0);TI=0;         /*�ȴ����ͳ�ȥ*/
    while(RI==0);RI=0;         /*�ȴ�B���ش�*/
    }while((SBUF^0xbb)!=0);    /*B��δ׼����,��������*/
 do{pf=0;                          /*��У���*/
    for(i=0;i<16;i++)              
       {SBUF=d[i];                 
        pf+=d[i];                  /*��У���*/
        while(TI==0);TI=0;         
        }
    SBUF=pf;                       /*����У���,���ȴ�B���ش�*/
    while(TI==0);TI=0;
    while(RI==0);RI=0;
   }while(SBUF!=0);                /*�ش����,�ط�*/
}
void receive(uchar idata *d)
{ uchar i;
  do{while(RI==0);RI=0;}
  while((SBUF^0xaa)!=0);           /*�ж�A����������*/
  SBUF=0xbb;                       /*��Ӧ���ź�*/
  while(TI==0);TI=0;
  while(1)
      {pf=0;                       /*��У���*/
       for(i=0;i<16;i++)
          {while(RI==0);RI=0;
           d[i]=SBUF;
           pf+=d[i];               /*������*/
          }
       while(RI==0);RI=0;          /*����A��У���*/
       if((SBUF^pf)==0)            /*�Ƚ�У���*/    
         {SBUF=0x00;break;}        /*��ͬ����00��*/
       else{SBUF=0xff;             /*������FF�������½���*/
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
    
    
 