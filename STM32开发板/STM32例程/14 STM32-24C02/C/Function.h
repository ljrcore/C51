#include "stm32f10x_lib.h"


/****funtion.h������������***********/

extern u8 ack;

//ʱ����ʱ����
extern void Delay_us(u32 nTime);

//�����ߺ���
extern void Start_I2c(void);

//�������ߺ���  
extern void Stop_I2c(void);

//Ӧ���Ӻ���
extern void Ack_I2c(u8 a);

//�ֽ����ݷ��ͺ���
extern void  SendByte(unsigned char  c);

//���ӵ�ַ���Ͷ��ֽ����ݺ���               
extern u8 ISendStr(unsigned char sla,unsigned char suba,unsigned char *s,unsigned char no) ;

//���ӵ�ַ���Ͷ��ֽ����ݺ���   
extern u8 ISendStrExt(unsigned char sla,unsigned char *s,unsigned char no);

//���ӵ�ַ���ֽ����ݺ���               
extern unsigned char RcvByte(void);

//���ӵ�ַ��ȡ���ֽ����ݺ���               
extern u8 IRcvStr(unsigned char sla,unsigned char suba,unsigned char *s,unsigned char no);

//���ӵ�ַ��ȡ���ֽ����ݺ���               
extern u8 IRcvStrExt(unsigned char sla,unsigned char *s,unsigned char no);





