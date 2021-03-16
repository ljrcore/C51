#include <VI2C_C51.H>             /*包含VI2C软件包*/
#include <reg52.h>
#include <intrins.h>
#define  WC24C02 0xA0            /*定义器件地址*/
#define  WRADR   0x00             /*指定操作地址*/
#define  RDADR   0x00             /*指定写入数据*/
main()
{
unsigned char	p[5]={1,2,3,4,5};
unsigned char   q[5];
bit bp;
bp=ISendStr(WC24C02,WRADR,p,5);

bp=IRcvStr(WC24C02,RDADR,q,5);
while(1);
}
