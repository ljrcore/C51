#include <VI2C_C51.H>             /*����VI2C�����*/
#include <reg52.h>
#include <intrins.h>
#define  WC24C02 0xA0            /*����������ַ*/
#define  WRADR   0x00             /*ָ��������ַ*/
#define  RDADR   0x00             /*ָ��д������*/
main()
{
unsigned char	p[5]={1,2,3,4,5};
unsigned char   q[5];
bit bp;
bp=ISendStr(WC24C02,WRADR,p,5);

bp=IRcvStr(WC24C02,RDADR,q,5);
while(1);
}
