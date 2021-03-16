#include <reg51.h>
#include <absacc.h>
#define uchar unsigned char
#define uint unsigned int 
#define COM8255 XBYTE[0xdfff]
#define PA8255 XBYTE[0xdffc]
uchar data s[6] _at_ 0x20;
uchar data t[6]={10,8,12,15,9,6};
void delay(i)
uchar i;
{ while(i--);}
main()
{  uchar m;
   uchar n=0,j=0x01;
   for (m=0;m<6;m++) s[m]=t[m];  /*赋值*/
   COM8255=0x82;
   do {
       COM8255=j;
       j=j<<1;
       delay(s[n]);n++;}while(n!=6);
  }
/*我就是定义成全局变量的，要么就只能给其赋初值，要么就只能定义他的绝对地址，两都不能同时用，试过好多方法了，
还是不行。再次感谢您，若我找到好方法了，会贴上来的！
刚才一个网友告诉我笨方法，定义别一个数组，赋值，然后再数组拷贝。凑合还可以用 

不好意思，局我所知好象不行。不过笨法子...... [zilingzhang] [18次] 01-6-27 下午 04:18:21 
 uchar dd[4] _at_ 0x00;
 uchar cc[4]={1,1,1,1};
for(i=0;i<4;i++)
......

*/
