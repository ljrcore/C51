/*----------------------------------------------------------------------------
 * Name:    STM32_Init.h
 * Purpose: STM32 peripherals initialisation definitions
 * Version: V1.00
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2005-2008 Keil Software. All rights reserved.
 *----------------------------------------------------------------------------
 * History:
 *          V1.00 Initial Version
 *----------------------------------------------------------------------------*/

/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef __MYSTM32_INIT_H
#define __MYSTM32_INIT_H

//extern void stm32_Init (void);

//extern unsigned int stm32_GetPCLK1 (void);
void stm32_IwdgSetup (void);
void stm32_IwdgSetupLong (void);
void stm32_IwdgSetupShort (void);
void stm32_TimerSetup (void);


#endif
