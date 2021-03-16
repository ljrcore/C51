
// extern void DelayMs(unsigned int);
// extern void Read24c02(unsigned char *RamAddress,unsigned char RomAddress,unsigned char bytes);
// extern void Write24c02(unsigned char *RamAddress,unsigned char RomAddress,unsigned char bytes);

/***************************************************************************/
#include <reg51.h>
#define	WriteDeviceAddress 0xa0
#define	ReadDviceAddress 0xa1

/***************************************************************************/
sbit	SCL=P3^7;
sbit	SDA=P3^6;


/***************************************************************************/
void DelayMs(unsigned int number) {
	unsigned char temp;
	for(;number;number--) {
		for(temp=112;temp!=0;temp--) {
		}
	}
}

/***************************************************************************/
void Start() {
	SDA=1;
	SCL=1;
	SDA=0;
	SCL=0;
}

/***************************************************************************/
void Stop() {
	SCL=0;
	SDA=0;
	SCL=1;
	SDA=1;
}

/***************************************************************************/
void Ack() {
	SDA=0;
	SCL=1;
	SCL=0;
	SDA=1;
}

/***************************************************************************/
void NoAck() {
	SDA=1;
	SCL=1;
	SCL=0;
}

/***************************************************************************/
bit TestAck() {
	bit ErrorBit;
	SDA=1;
	SCL=1;
	ErrorBit=SDA;
	SCL=0;
	return(ErrorBit);
}

/***************************************************************************/
bit Write8Bit(unsigned char input) {
	unsigned char temp;
	for(temp=8;temp!=0;temp--) {
		SDA=(bit)(input&0x80);
		SCL=1;
		SCL=0;
		input=input<<1;
	}
}

/***************************************************************************/
void Write24c02(unsigned char *Wdata,unsigned char RomAddress,unsigned char number) {
	Start();
	Write8Bit(WriteDeviceAddress);
	TestAck();
	Write8Bit(RomAddress);
	TestAck();
	for(;number!=0;number--) {
		Write8Bit(*Wdata);
		TestAck();
		Wdata++;
	}
	Stop();
	DelayMs(10);
}

/***************************************************************************/
unsigned char Read8Bit() {
	unsigned char temp,rbyte=0;
	for(temp=8;temp!=0;temp--) {
		SCL=1;
		rbyte=rbyte<<1;
		rbyte=rbyte|((unsigned char)(SDA));
		SCL=0;
	}
	return(rbyte);
}

/***************************************************************************/
void Read24c02(unsigned char *RamAddress,unsigned char RomAddress,unsigned char bytes) {
	Start();
	Write8Bit(WriteDeviceAddress);
	TestAck();
	Write8Bit(RomAddress);
	TestAck();
	Start();
	Write8Bit(ReadDviceAddress);
	TestAck();
	while(bytes!=1) {
	*RamAddress=Read8Bit();
	Ack();
	RamAddress++;
	bytes--;
	}
	*RamAddress=Read8Bit();
	NoAck();
	Stop();
}

/***************************************************************************/
void main(void)
{
	Byte buf1[]={3,4,5,6,7,8};
	Byte buf2[];
	Write24c02(buf1,0,6);
	Read24c02(buf2,0,6);
	if(buf1[1]==buf2[1])LED1=0;
	if(buf1[2]==buf2[2])LED2=0;
	if(buf1[3]==buf2[3])LED3=0;
	if(buf1[4]==buf2[4])LED4=0;
	while(1);
}