#include <reg51.h>
#define uchar unsigned char
uchar xdata r_buf[32];
uchar xdata t_buf[32];
uchar r_in,r_out,t_in,t_out;   /*���巢�͡����ա�ָ�롱*/
bit r_full,t_empty,t_done;     /*��������������������գ�������ɱ�־*/
code uchar m[]={"this is a test program\r\n"};
serial()interrupt 4 using 1
{if(RI&&~r_full)               /*�ǽ����ж��ҽ��ջ�����δ��*/
    {r_buf[r_in]=SBUF;        /*����*/
     RI=0;                    /*�[��־*/
     r_in=++r_in&0x1f;        /*�±�+1*/
     if(r_in==r_out)r_full=1; /*�ж��Ƿ�Ҫ��r_full��־*/
     }
 else if (RI&&~t_empty)       /*�Ƿ����ж��ҷ��ͻ�����δ��*/
         {SBUF=t_buf[t_out];  /*����*/
          TI=0;               /*�[��־*/
          t_out=++t_out&0x1f; /*�±�+1*/
          if(t_out==t_in)t_empty=1;/*�ж��Ƿ�Ҫ��t_empty��־*/
          }
 else if (TI)                 /*�Ƿ����ж��ҷ��ͻ������ѿ�*/
         {TI=0;t_done=1;}     /*��t_done��־*/
 }
void loadmsg(uchar code *msg)
{while((*msg!=0)&&((((t_in+1)^t_out)&0x1f)!=0))
      {t_buf[t_in]=*msg;
       msg++;
       t_in=++t_in&0x1f;
       if(t_done)
         {TI=1;
          t_empty=t_done=0;
          }
       }
 }
void process(uchar ch){return;}
void processmsg(void)
{while(((r_out+1)^r_in)!=0)
      {process(r_buf[r_out]);
       r_out=++r_out&0x1f;
       }
}
main()
{TMOD=0x20;TH1=0xfd;TR1=1;SCON=0x50;IE=0x90;
 t_empty=t_done=1;     /*��ʼ��Ϊ��������ɡ�*/
 r_full=0;������������ /*�������*/
 r_out=t_in=t_out=0;   /*���շ������߽�*/
 r_in=1;��������������/*���ա�ָ�롱Ϊ0*/
 for(;;){
         loadmsg(&m);
         processmsg();
         }
}
         
 
  
            
