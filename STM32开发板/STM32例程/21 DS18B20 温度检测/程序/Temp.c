 
 /*************************�˲���Ϊ18B20����������*************************************/

#include "stm32f10x_lib.h"

#define  D18B20    GPIO_Pin_15   //=P3^7;

void Init18b20 (void);
void WriteByte (unsigned char wr);  //���ֽ�д��
void read_bytes (unsigned char j);
unsigned char Temp_CRC (unsigned char j);
void GemTemp (void);
void Config18b20 (void);
void ReadID (void);
void TemperatuerResult(void);
extern void Delay_us(u32 nTime);


unsigned char  flag;
unsigned int   Temperature;
unsigned char  temp_buff[9]; //�洢��ȡ���ֽڣ�read scratchpadΪ9�ֽڣ�read rom IDΪ8�ֽ�
unsigned char  id_buff[8];
unsigned char  *p;
unsigned char  crc_data;
extern u8 Count;


const unsigned char  CrcTable [256]={
0,  94, 188,  226,  97,  63,  221,  131,  194,  156,  126,  32,  163,  253,  31,  65,
157,  195,  33,  127,  252,  162,  64,  30,  95,  1,  227,  189,  62,  96,  130,  220,
35,  125,  159,  193,  66,  28,  254,  160,  225,  191,  93,  3,  128,  222,  60,  98,
190,  224,  2,  92,  223,  129,  99,  61,  124,  34,  192,  158,  29,  67,  161,  255,
70,  24,  250,  164,  39,  121,  155,  197,  132,  218,  56,  102,  229,  187,  89,  7,
219,  133, 103,  57,  186,  228,  6,  88,  25,  71,  165,  251,  120,  38,  196,  154,
101,  59, 217,  135,  4,  90,  184,  230,  167,  249,  27,  69,  198,  152,  122,  36,
248,  166, 68,  26,  153,  199,  37,  123,  58,  100,  134,  216,  91,  5,  231,  185,
140,  210, 48,  110,  237,  179,  81,  15,  78,  16,  242,  172,  47,  113,  147,  205,
17,  79,  173,  243,  112,  46,  204,  146,  211,  141,  111,  49,  178,  236,  14,  80,
175,  241, 19,  77,  206,  144,  114,  44,  109,  51,  209,  143,  12,  82,  176,  238,
50,  108,  142,  208,  83,  13,  239,  177,  240,  174,  76,  18,  145,  207,  45,  115,
202,  148, 118,  40,  171,  245,  23,  73,  8,  86,  180,  234,  105,  55,  213, 139,
87,  9,  235,  181,  54,  104,  138,  212,  149,  203,  41,  119,  244,  170,  72,  22,
233,  183,  85,  11,  136,  214,  52,  106,  43,  117,  151,  201,  74,  20,  246,  168,
116,  42,  200,  150,  21,  75,  169,  247,  182,  232,  10,  84,  215,  137,  107,  53}; 


/************************************************************
*Function:18B20��ʼ��
*parameter:
*Return:
*Modify:
*************************************************************/
void Init18b20 (void)
{

	GPIO_SetBits(GPIOA , D18B20); //�������øߵ�ƽ
	Delay_us(2); //��ʱ2΢��
	GPIO_ResetBits(GPIOA , D18B20);	//�õ�
	Delay_us(490);   //delay 530 uS//80
    GPIO_SetBits(GPIOA , D18B20);	 //�ø�
	Delay_us(100);   //delay 100 uS//14

	if(GPIO_ReadInputDataBit(GPIOA , D18B20)== 0)
		flag = 1;   //detect 1820 success!
	else
		flag = 0;    //detect 1820 fail!
	Delay_us(480);        //��ʱ480΢��
	GPIO_SetBits(GPIOA , D18B20);  //�������øߵ�ƽ
}

/************************************************************
*Function:��18B20д��һ���ֽ�
*parameter:
*Return:
*Modify:
*************************************************************/
void WriteByte (unsigned char  wr)  //���ֽ�д��
{
	unsigned char  i;
	for (i=0;i<8;i++)
	{
		GPIO_ResetBits(GPIOA , D18B20);	 //D18B20 = 0;
    	Delay_us(2);
		//D18B20=wr&0x01;
		if(wr&0x01)	GPIO_SetBits(GPIOA , D18B20);
		else  GPIO_ResetBits(GPIOA , D18B20);
		Delay_us(45);   //delay 45 uS //5
		
		GPIO_SetBits(GPIOA , D18B20);  //D18B20=1;
		wr >>= 1;
	}
}

/************************************************************
*Function:��18B20��һ���ֽ�
*parameter:
*Return:
*Modify:
*************************************************************/
unsigned char ReadByte (void)     //��ȡ���ֽ�
{
	unsigned char  i,u=0;
	for(i=0;i<8;i++)
	{		
		GPIO_ResetBits(GPIOA , D18B20);	   	//D18B20 = 0;
		Delay_us (2);
		u >>= 1;
	
		GPIO_SetBits(GPIOA , D18B20);	 	//D18B20 = 1;
		Delay_us (4);
		if(GPIO_ReadInputDataBit(GPIOA , D18B20) == 1)
		u |= 0x80;
		Delay_us (65);
	}
	return(u);
}

/************************************************************
*Function:��18B20
*parameter:
*Return:
*Modify:
*************************************************************/
void read_bytes (unsigned char  j)
{
	 unsigned char  i;
	 for(i=0;i<j;i++)
	 {
		  *p = ReadByte();
		  p++;
	 }
}

/************************************************************
*Function:CRCУ��
*parameter:
*Return:
*Modify:
*************************************************************/
unsigned char Temp_CRC (unsigned char j)
{
   	unsigned char  i,crc_data=0;
  	for(i=0;i<j;i++)  //���У��
    	crc_data = CrcTable[crc_data^temp_buff[i]];
    return (crc_data);
}

/************************************************************
*Function:��ȡ�¶�
*parameter:
*Return:
*Modify:
*************************************************************/
void GemTemp (void)
{
   read_bytes (9);
   if (Temp_CRC(9)==0) //У����ȷ
   {
	    Temperature = temp_buff[1]*0x100 + temp_buff[0];
//	    Temperature *= 0.625;
		Temperature /= 16;
		Delay_us(10);
    }
}

/************************************************************
*Function:�ڲ�����
*parameter:
*Return:
*Modify:
*************************************************************/
void Config18b20 (void)  //�������ñ����޶�ֵ�ͷֱ���
{
     Init18b20();
     WriteByte(0xcc);  //skip rom
     WriteByte(0x4e);  //write scratchpad
     WriteByte(0x19);  //����
     WriteByte(0x1a);  //����
     WriteByte(0x7f);     //set 12 bit (0.125)
     Init18b20();
     WriteByte(0xcc);  //skip rom
     WriteByte(0x48);  //�����趨ֵ
     Init18b20();
     WriteByte(0xcc);  //skip rom
     WriteByte(0xb8);  //�ص��趨ֵ
}

/************************************************************
*Function:��18B20ID
*parameter:
*Return:
*Modify:
*************************************************************/
void ReadID (void)//��ȡ���� id
{
	Init18b20();
	WriteByte(0x33);  //read rom
	read_bytes(8);
}

/************************************************************
*Function:18B20IDȫ����
*parameter:
*Return:
*Modify:
*************************************************************/
void TemperatuerResult(void)
{
  	p = id_buff;
  	ReadID();
  	Config18b20();
	Init18b20 ();
	WriteByte(0xcc);   //skip rom
	WriteByte(0x44);   //Temperature convert

	Init18b20 ();
	WriteByte(0xcc);   //skip rom
	WriteByte(0xbe);   //read Temperature
	p = temp_buff;
	GemTemp();
}


void GetTemp()
{       
     if(Count == 3) //ÿ�� 3s ��ȡ�¶�
	{  Count=0;
	   TemperatuerResult();
	}

}






