/*********************************************************************
**文 件 名：led.h
**版本信息：
**创 建 人：思良月
**完成时间：2013年7月3日
**摘    要：
*********************************************************************/

#ifndef __LED_H
#define __LED_H

#include<stm32f10x.h>

/****重定义使用的IO口*****/
#define RCC_LED 		((uint32_t)0x00000008)// GPIOB的使能
#define GPIO_LED		GPIOB	              //使用的是GPIOB
#define PIN_LED 		((uint16_t)0xFF00)	  //IO口操作一次16位，
#define GPIOMODE_LED	((uint8_t)0x03)		  //选择8种模式中的一种

/****初始化Led使用的IO****/
void Led_Init(void);

/****点亮一盏LED的函数*********/
#define PIN_LED1 		((uint16_t)0x8000)
void LED1(uint8_t status);

/******点亮LED的函数***********/
void Led_Sets(uint8_t data);

#endif
