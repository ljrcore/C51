#include <reg51.h>
void delay(void)
{uchar i;
 for(i=200;i>0;i--);
 }
uchar scankb(void)
{uchar sccode,recode;
 P2=0xf0;
 if((P2&0xf0)!=0xf0)//�м�����
   {delay();
    if((P2&0xf0)!=0xf0)//��Ȼ�м�����
   	  {sccode=0xfe;
	   while((sccode&0x10)!=0)//��λû��
	       {P2=sccode;//��ɨ�迪ʼ
		    if((P2&0xf0)!=0xf0)//���ڸ���
		      {recode=(P2&0xf0)|0x0f;//�м���
	           P2=0xff;              //��P2
			   return((~sccode)+(~recode));//����Keyword
		       }
	        else sccode=(sccode<<1)|0x01;//���ڸ�����ɨ��һ��
		    }
	   }
   }
 return(0);
}
