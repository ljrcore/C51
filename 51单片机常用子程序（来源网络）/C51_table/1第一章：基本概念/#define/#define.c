#include <at89x51.h>
/************************定义常量**********************************/
#define clock_base 		1
#define clock_40ms 		(65536-40000*clock_base)
#define clock_4096us 	(65536-4096*clock_base)
#define clock_5000us	(65536-5000*clock_base)
#define clock_10000us	(65536-10000*clock_base)
/************************定义函数**********************************/
#define hibyte_ref(addr)	(*((Byte*) & addr))	//？对addr取址后转换为指针并取出该单元的数
#define lobyte_ref(addr)	(*((Byte*) & addr))
#define makeword(a,b)		((((Word)(a))<<8)+(Word)(b))//两个单字节合并为一个双字节
#define hibyte(a)			((Byte)((a)>>8))
#define lobyte(a)			((Byte)((a)&0xff))
/******************************************************************/
void main(void)
{Byte i,j,m,n,p,q;
 Byte *hhl={0x11,0x22};
 hibyte(i);
 lobyte(j);
 hibyte_ref(m);
 lobyte_ref(n);
 makeword(p,q);
}

