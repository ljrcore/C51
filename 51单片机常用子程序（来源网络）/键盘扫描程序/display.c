#include <reg51.h>                   
const uchar DATA_7SEG[ ] ={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                           0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
uchar led[6] ={1,2,3,4,5,6}; //��ʾ1,2,3,4,5,6                      
void delay(uchar t)                    
{uchar i;
 for (i=0;i<t;i++);
} 
//_______________________________________________________________
void display(void)                       
{uchar i;
 for(;;)
   {for (i=0;i<6;i++)
      {P3=~(0x01<<i);          //λѡ��λ
       P1=DATA_7SEG[led[i]];   //�Ͷ���
       delay(1000);
       }
    P1=0x00;//����ʾ
    P3=0xff;
	}
}

