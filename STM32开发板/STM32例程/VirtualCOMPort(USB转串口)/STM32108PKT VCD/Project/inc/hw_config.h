/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : hw_config.h
* Author             : MCD Application Team
* Version            : V3.0.0
* Date               : 04/06/2009
* Description        : Hardware Configuration & Setup
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

/* Includes ------------------------------------------------------------------*/
#include "usb_type.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
#define MASS_MEMORY_START     0x04002000
#define BULK_MAX_PACKET_SIZE  0x00000040
#define LED_ON                0xF0
#define LED_OFF               0xFF

#define TIMER_ARR_1MS  2999
#define TIMER_ARR_5MS  14999
#define TIMER_ARR_10MS 29999
#define BUFFER_SIZE    1024

typedef enum {
  USART_RECEIVE = 0,
  START_USART2USB,
  WAIT_USART2USB_END,
}USB_USART_STATE;

/* Exported functions ------------------------------------------------------- */
void Set_System(void);
void Set_USBClock(void);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Interrupts_Config(void);
void USART_Config_Default(void);
bool USART_Config(void);
void USB_To_USART_Send_Data(uint8_t* data_buffer, uint8_t Nb_bytes);
void USART_2_USB_Send_Data(void);
void Get_SerialNum(void);

void Timer_Init(uint16_t TimeBase_CCR);
void usart_2_usb_send(void);
void usart_2_usb_waitend(void);

/* External variables --------------------------------------------------------*/
extern volatile USB_USART_STATE usart_2_usb_process;
extern volatile unsigned short usart_2_usb_count;
extern volatile bool usart_2_usb_complete;
extern unsigned char *volatile pbuffer_in_usart;
extern unsigned char *volatile pbuffer_in_usb;
extern unsigned char *pbuffer_out_usart;
extern void usb_2_usart_send_data(void);
extern unsigned char buffer_out[BUFFER_SIZE];

#endif  /*__HW_CONFIG_H*/
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
