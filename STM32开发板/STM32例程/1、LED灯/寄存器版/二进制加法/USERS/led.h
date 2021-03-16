/*********************************************************************
**�� �� ����led.h
**�汾��Ϣ��
**�� �� �ˣ�˼����
**���ʱ�䣺2013��7��3��
**ժ    Ҫ��
*********************************************************************/

#ifndef __LED_H
#define __LED_H

#include<stm32f10x.h>

/****�ض���ʹ�õ�IO��*****/
#define RCC_LED 		((uint32_t)0x00000008)// GPIOB��ʹ��
#define GPIO_LED		GPIOB	              //ʹ�õ���GPIOB
#define PIN_LED 		((uint16_t)0xFF00)	  //IO�ڲ���һ��16λ��
#define GPIOMODE_LED	((uint8_t)0x03)		  //ѡ��8��ģʽ�е�һ��

/****��ʼ��Ledʹ�õ�IO****/
void Led_Init(void);

/****����һյLED�ĺ���*********/
#define PIN_LED1 		((uint16_t)0x8000)
void LED1(uint8_t status);

/******����LED�ĺ���***********/
void Led_Sets(uint8_t data);

#endif
