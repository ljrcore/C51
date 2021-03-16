/*响应中断后查询P1口作为转向依据 */
#include<reg51.h>
#define uchar unsigned char
unsigned char status;
bit flag;
void service_int1()interrupt 2 using 2     /*INT1中断服务程序*/
{                                          /*使用第二组寄存器*/
flag=1;
status=P1;
}
void main(void)
{
uchar a,b,c,d;
IP=0x04;                   /*INT1置为高级中断*/
IE=0x84;                   /*INT1，CPU开中断*/

for(;;)
   {
   if(flag)
     {
      switch(status)
	        {             
            case 0:a=1;break;
	        case 1:b=0;break;
	        case 2:c=0;break;
	        case 3:d=0;break;
	        default:a=10;break;
	         }
	     flag=0;
      }
    }
}
