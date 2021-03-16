#include <reg51.h>
void delay(void)
{uchar i;
 for(i=200;i>0;i--);
 }
uchar scankb(void)
{uchar sccode,recode;
 P2=0xf0;
 if((P2&0xf0)!=0xf0)//有键按下
   {delay();
    if((P2&0xf0)!=0xf0)//仍然有键按下
   	  {sccode=0xfe;
	   while((sccode&0x10)!=0)//移位没完
	       {P2=sccode;//行扫描开始
		    if((P2&0xf0)!=0xf0)//若在该行
		      {recode=(P2&0xf0)|0x0f;//中间结果
	           P2=0xff;              //关P2
			   return((~sccode)+(~recode));//返回Keyword
		       }
	        else sccode=(sccode<<1)|0x01;//不在该行则扫下一行
		    }
	   }
   }
 return(0);
}
