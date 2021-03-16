/*----------------------------------------------------------------------------
 *      R T L  -  C A N   D r i v e r
 *----------------------------------------------------------------------------
 *      Name:    CAN_Hw.h
 *      Purpose: Header for CAN Hardware specific module
 *      Rev.:    V3.40
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2008 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "RTX_CAN.h"                  /* CAN Generic functions & defines     */


#ifndef _CAN_HW_H_
#define _CAN_HW_H_

/* Functions defined in module CAN_Hw.c                                      */
CAN_ERROR CAN_hw_setup(U32 ctrl);
CAN_ERROR CAN_hw_init(U32 ctrl, U32 baudrate);
CAN_ERROR CAN_hw_start(U32 ctrl);
CAN_ERROR CAN_hw_tx_empty(U32 ctrl);
CAN_ERROR CAN_hw_wr(U32 ctrl, CAN_msg* msg);
CAN_ERROR CAN_hw_set(U32 ctrl, CAN_msg* msg);
CAN_ERROR CAN_hw_rx_object(U32 ctrl, U32 ch, U32 id, CAN_FORMAT filter_type);
CAN_ERROR CAN_hw_tx_object(U32 ctrl, U32 ch, CAN_FORMAT filter_type);

CAN_ERROR CAN_hw_testmode(U32 ctrl, U32 testmode);

#endif /* _CAN_HW_H_ */


/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/

