#ifndef __TOUCH_H
#define __TOUCH_H

//---����ͷ�ļ�---//
#include<reg51.h>
#include<intrins.h>

//---�ض���ؼ���---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint  unsigned int
#endif

//---������������---//
typedef struct 
{
	uint x;
	uint y;
} XPT_XY;

extern XPT_XY xpt_xy;

//---����оƬ�����ֽ�---//
#define XPT_CMD_X	0xD0    //��ȡX�������
#define XPT_CMD_Y	0x90	//��ȡY�������

//---����ʹ�õ�IO��---//
sbit TOUCH_DOUT = P2^0;	  //���
sbit TOUCH_CLK  = P2^1;	  //ʱ��
sbit TOUCH_DIN  = P2^2;	  //����
sbit TOUCH_CS   = P2^3;	  //Ƭѡ
sbit TOUCH_PEN  = P2^4;	  //��ⴥ������Ӧ�ź�

//---����ȫ�ֺ���---//
void TOUCH_SPI_Start(void);
void TOUCH_SPI_Write(uchar dat);
uint TOUCH_SPI_Read(void);
uint TOUCH_XPT_ReadData(uchar cmd);
uchar TOUCH_XPT_ReadXY(void);



#endif


//#ifndef __TOUCH_H
//#define __TOUCH_H
//
////---����ͷ�ļ�---//
//#include<reg51.h>
//#include<intrins.h>
//#include"gui.h"
//
////---�ض���ؼ���---//
//#ifndef uchar
//#define uchar unsigned char
//#endif
//
//#ifndef uint
//#define uint  unsigned int
//#endif
//
//#ifndef ulong
//#define ulong  unsigned long
//#endif
//
////---������������---//
//typedef struct 
//{
//	uint x;
//	uint y;
//} XPT_XY;
//
////--- ƫ�ƽṹ�� ---//
//typedef struct{   
//    int xOffset;
//    int yOffset; 
//    float xFactor;
//    float yFactor;
//} PosTypeDef;
//
//extern XPT_XY xpt_xy;
//extern PosTypeDef TouchAdj; //����һ��������������У������
//
//
////--- ���ô������Ķ�Ӧ��ϵ ---//
////--- ��LCDx��ӦADx��LCDy��ӦADy������Сֵ�����Ͻ�ʱ������Ϊ0 ---//
////--- ��LCDx��ӦADy��LCDy��ӦADx������Сֵ�����½�ʱ������Ϊ1 ---//
////--- LCD_TOUCH_TYPEΪ0ʱ��Ҫ�Լ��ֶ�У������Ϊ1ʱ�����ó��������ṩ������У�� ---//
//# define LCD_TOUCH_TYPE 1   
//
////--- ����У���������� ---//
//#define LCD_ADJX_MIN ((uint)10)                        //��ȡ�ĸ������СXֵ
//#define LCD_ADJX_MAX ((uint)TFT_XMAX - LCD_ADJX_MIN) //��ȡ�ĸ�������Xֵ
//#define LCD_ADJY_MIN ((uint)10)                        //��ȡ�ĸ������СYֵ
//#define LCD_ADJY_MAX ((uint)TFT_YMAX - LCD_ADJY_MIN) //��ȡ�ĸ�������Yֵ
//
//#define LCD_ADJ_MUX  ((uint)1)                     //ƫ�������ı�������
//
//#define LCD_ADJx (LCD_ADJX_MAX - LCD_ADJY_MIN)         //��ȡ����Ŀ��
//#define LCD_ADJy (LCD_ADJY_MAX - LCD_ADJY_MIN)         //��ȡ����ĸ߶�
//#define ADJ_CHECK_DELAY {for(i=0; i<0x0FFF; i++);}     //�����ǵ���ʱ��С
//
////---����оƬ�����ֽ�---//
//#define XPT_CMD_X	0xD0    //��ȡX�������
//#define XPT_CMD_Y	0x90	//��ȡY�������
//
////---����ʹ�õ�IO��---//
//sbit TOUCH_DOUT = P2^0;	  //���
//sbit TOUCH_CLK  = P2^1;	  //ʱ��
//sbit TOUCH_DIN  = P2^2;	  //����
//sbit TOUCH_CS   = P2^3;	  //Ƭѡ
//sbit TOUCH_PEN  = P2^4;	  //��ⴥ������Ӧ�ź�
//
//
//
////---����ȫ�ֺ���---//
//void TOUCH_SPI_Start(void);
//void TOUCH_SPI_Write(uchar dat);
//uint TOUCH_SPI_Read(void);
//uint TOUCH_XPT_ReadData(uchar cmd);
//uchar TOUCH_XPT_ReadXY(void);
//void TOUCH_Adjust(void);
//
//
//
//#endif
