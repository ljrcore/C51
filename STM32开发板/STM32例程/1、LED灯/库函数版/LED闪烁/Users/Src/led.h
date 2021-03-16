#ifndef __LED_H_
#define __LED_H_

#include"stm32f10x.h"
/*************������ʹ�õ�IO��**************/
#define RCC_LED 	RCC_APB2Periph_GPIOB	
#define GPIO_LED 	GPIOB
/**************8λLED��IO�ڶ���************/
#define PIN_LED 	(GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12\
|GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15)
/**************����LED��IO�ڶ���***********/
#define PIN_LED1 	GPIO_Pin_15

/**********��IOʱ�Ӻͳ�ʼ��GPIO**********/
void LED_Init(void);
/**********���ð�λLED��״̬***************/
void LED_Sets(uint8_t data);
/**********LED�򿪻��߹رյĺ��� **********/
#define LED1(a) if(a)\
GPIO_WriteBit(GPIO_LED, PIN_LED1, Bit_SET);\
else GPIO_WriteBit(GPIO_LED, PIN_LED1, Bit_RESET);

#endif
