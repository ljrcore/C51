#include <reg51.h>
#define uchar unsigned char
uchar xdata r_buf[32];
uchar xdata t_buf[32];
uchar r_in,r_out,t_in,t_out;   /*定义发送、接收“指针”*/
bit r_full,t_empty,t_done;     /*定义接收区满，发送区空，发送完成标志*/
code uchar m[]={"this is a test program\r\n"};
serial()interrupt 4 using 1
{if(RI&&~r_full)               /*是接收中断且接收缓冲区未满*/
    {r_buf[r_in]=SBUF;        /*接收*/
     RI=0;                    /*淸标志*/
     r_in=++r_in&0x1f;        /*下标+1*/
     if(r_in==r_out)r_full=1; /*判断是否要置r_full标志*/
     }
 else if (RI&&~t_empty)       /*是发送中断且发送缓冲区未空*/
         {SBUF=t_buf[t_out];  /*接收*/
          TI=0;               /*淸标志*/
          t_out=++t_out&0x1f; /*下标+1*/
          if(t_out==t_in)t_empty=1;/*判断是否要置t_empty标志*/
          }
 else if (TI)                 /*是发送中断且发送缓冲区已空*/
         {TI=0;t_done=1;}     /*置t_done标志*/
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
 t_empty=t_done=1;     /*初始化为“发送完成“*/
 r_full=0;　　　　　　 /*允许接收*/
 r_out=t_in=t_out=0;   /*接收发送区边界*/
 r_in=1;　　　　　　　/*接收“指针”为0*/
 for(;;){
         loadmsg(&m);
         processmsg();
         }
}
         
 
  
            
