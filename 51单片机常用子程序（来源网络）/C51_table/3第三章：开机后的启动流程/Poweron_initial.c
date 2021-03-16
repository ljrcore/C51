#include <at89x51.h>
#define Byte unsigned char
#define clock_40ms (65536-40000)
Byte idata Ledcount,Outputstate,Dutycount,keydata;
//***************************initialcpu********************************************//
void initialcpu(void)
{IE=0;	
PSW=0;
IP=0X0B;
TMOD=0X15;
TR0=0;
TR1=1;
IT0=1;
TL0=0XFF;
TH0=0XFF;
TL1=clock_40ms & 0xff;	//clock_40ms=(65536-40000) for 12MHz
TH1=clock_40ms >> 8;
}
//**************************initialcpuIO*******************************************//
void initialcpuIO()
{P0=0xff;
 P1=0xff;
 P2=0xff;
 P3=0xff;
 P1_0=0;
 P3_1=0;
}
//**************************initialeeprom******************************************//
Byte hibyte(Byte version_id);
Byte Lobyte(Byte version_id);
void eepromwrite(Byte adress,Byte num);
void initialeeprom(void)
{Byte code eeprom_default_table1[][6]={
	 {0x11,0x12,0x13,0x14,0x15,0x16},
	 {0x81,0x82,0x83,0x84,0x85,0x86},
	 {0xc1,0xc2,0xc3,0xc4,0xc5,0xc6}
	 								  };
 Byte code eeprom_default_table2[]={
	  0x80,0x00,
	  0x0f,0x10,0x10,0x00,
	  0x01,0x00,0x00,0x00,
	  0x00,0x00
	  								};
Byte i,j;
Byte datapointer;
Byte version_adr;
Byte version_id;
Byte trmbuf[8];
for(i=0;i<3;i++)
	{datapointer=eeprom_default_table1[i];
	for(j=0;j<6;j++)
		trmbuf[j+1]=*(datapointer+j);//C51编译器不支持这种取值运算◎◎◎◎◎◎◎◎！！！
	eepromwrite(i*6,6);
	}
for(i=0;i<12;i++)
	{trmbuf[i+1]=eeprom_default_table2[i];
	eepromwrite(0x80,12);
	trmbuf[1]=hibyte(version_id);
	trmbuf[2]=lobyte(version_id);
	eepromwrite(version_adr,2);
	}
//***************************initialvariable**************************************//
void initialvarialble(void)
{Ledcount=0;
 Outputstate=0xff;
 Dutycount=0;
 keydata=0;
}
//**************************Poweron_initial***************************************//

void Poweron_initial (void)
{initialcpu();
 initialcpuIO();
 eepromread(version_adr,2);//上电检查eeprom ID
 if((trmbuf[0]!=hibyte(version_id))||(trmbuf[1]!=lobyte(version_id))
	 initialeeprom();
 initialvariable();//初始化变量
}
