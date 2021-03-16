/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2006; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                           MASTER INCLUDES
*
*                                     ST Microelectronics STM32
*                                              with the
*                                   STM3210B-EVAL Evaluation Board
*
* Filename      : includes.h
* Version       : V1.10
* Programmer(s) : BAN
*********************************************************************************************************
*/

#ifndef  __INCLUDES_H__
#define  __INCLUDES_H__

#include  <stdio.h>
#include  <string.h>
#include  <ctype.h>
#include  <stdlib.h>
#include  <stdarg.h>

//#include  <ucos_ii.h>
#include  "..\uCOS-II\Source\ucos_ii.h"

//#include  <cpu.h>
#include  "..\uC-CPU\ARM-Cortex-M3\cpu.h"

//#include  <lib_def.h>
//#include  <lib_mem.h>
//#include  <lib_str.h>
#include  "..\uC-LIB\lib_def.h"
#include  "..\uC-LIB\lib_mem.h"
#include  "..\uC-LIB\lib_str.h"

#include  <stm32f10x_conf.h>
#include  <stm32f10x_lib.h>
#include "stm32f10x_map.h"
#include "STM32_Reg.h"

#include "MyType.h"

#include  "config.h"
#include  "app_cfg.h"

#include  "..\usart\COM.h"

#include  "..\BSP\bsp.h"



#endif

