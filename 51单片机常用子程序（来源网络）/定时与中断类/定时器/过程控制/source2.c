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
   for (m=0;m<6;m++) s[m]=t[m];  /*��ֵ*/
   COM8255=0x82;
   do {
       COM8255=j;
       j=j<<1;
       delay(s[n]);n++;}while(n!=6);
  }
/*�Ҿ��Ƕ����ȫ�ֱ����ģ�Ҫô��ֻ�ܸ��丳��ֵ��Ҫô��ֻ�ܶ������ľ��Ե�ַ����������ͬʱ�ã��Թ��ö෽���ˣ�
���ǲ��С��ٴθ�л���������ҵ��÷����ˣ����������ģ�
�ղ�һ�����Ѹ����ұ������������һ�����飬��ֵ��Ȼ�������鿽�����պϻ������� 

������˼��������֪�����С�����������...... [zilingzhang] [18��] 01-6-27 ���� 04:18:21 
 uchar dd[4] _at_ 0x00;
 uchar cc[4]={1,1,1,1};
for(i=0;i<4;i++)
......

*/
