#ifndef  __INCLUDE_H
#define __INCLUDE_H

//--定义MOSI--//
#define MOSI_CLR GPIO_ResetBits(GPIOA, GPIO_Pin_12)
#define MOSI_SET GPIO_SetBits(GPIOA, GPIO_Pin_12)

//--定义S_CLK--//
#define S_CLK_CLR GPIO_ResetBits(GPIOA, GPIO_Pin_14)
#define S_CLK_SET GPIO_SetBits(GPIOA, GPIO_Pin_14)

//--定义R_CLK--//
#define R_CLK_CLR GPIO_ResetBits(GPIOA, GPIO_Pin_13)
#define R_CLK_SET GPIO_SetBits(GPIOA, GPIO_Pin_13)

#endif
