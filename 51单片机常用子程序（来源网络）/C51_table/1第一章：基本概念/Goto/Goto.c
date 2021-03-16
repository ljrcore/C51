#include<reg51.h>
#include<intrins.h>
void Ledon();
void Ledoff();
void Delayx10ms(Byte count);
void GotoDemo(void)
{	bit Fgerror;	Byte i;
	Ledon();
	Delayx10ms(50);
	if(Fgerror) goto error;//只能在函数内部跳转，不能跳到"good"标号
	Ledoff();
	Delayx10ms(50);
error:
	i++;
}
void function (void)
{
good:
 _nop_();
}
