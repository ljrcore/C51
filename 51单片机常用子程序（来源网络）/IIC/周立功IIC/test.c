#include <reg52.h>
#include <intrins.h>
#include "2402.h"             
#define  WC24C02 0xA0            /*定义器件地址*/
#define  WRADR   0x00             /*指定操作地址*/
#define  RDADR   0x00             /*指定写入数据*/

main()
{
unsigned char	p[5]={0x0c,0x02,0x04,0x00,0x02};
unsigned char   q[5];
bit bp;
bp=ISendStr(WC24C02,WRADR,p,5);
bp=IRcvStr(WC24C02,RDADR,q,5);
while(1);
}
