/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : usb_endp.c
* Author             : MCD Application Team
* Version            : V3.0.0
* Date               : 04/06/2009
* Description        : Endpoint routines
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_mem.h"
#include "hw_config.h"
#include "usb_istr.h"
#include "stm32f10x_usart.h"

__IO uint32_t count_out = 0;
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : EP3_IN_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP3_OUT_Callback(void)
{
  count_out = GetEPRxCount(ENDP3);
  PMAToUserBufferCopy(buffer_out, ENDP3_RXADDR, count_out);
  pbuffer_out_usart = buffer_out;
  USART_ITConfig(USART1, USART_IT_TXE, ENABLE);    
}

/*******************************************************************************
* Function Name  : EP1_IN_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP1_IN_Callback(void)
{
  unsigned char *ptemp;
  unsigned int temp1;
    switch (usart_2_usb_process)
    {
      case USART_RECEIVE:
        break;
      case START_USART2USB:
        break;
      case WAIT_USART2USB_END:
        if (usart_2_usb_count == 0){
          usart_2_usb_complete = TRUE;
        }
        else {
          if (usart_2_usb_count > VIRTUAL_COM_PORT_DATA_SIZE){
            ptemp = pbuffer_in_usb;
            UserToPMABufferCopy(ptemp, ENDP1_TXADDR, VIRTUAL_COM_PORT_DATA_SIZE);
            SetEPTxCount(ENDP1, VIRTUAL_COM_PORT_DATA_SIZE);
            usart_2_usb_count -= VIRTUAL_COM_PORT_DATA_SIZE;
            pbuffer_in_usb += VIRTUAL_COM_PORT_DATA_SIZE;
            SetEPTxValid(ENDP1); 
          }
          else {
            ptemp = pbuffer_in_usb;
            UserToPMABufferCopy(ptemp, ENDP1_TXADDR, usart_2_usb_count);
            SetEPTxCount(ENDP1, usart_2_usb_count);
            temp1 = (unsigned int)usart_2_usb_count;
            pbuffer_in_usb += temp1;
            usart_2_usb_count = 0;    
            SetEPTxValid(ENDP1); 
          }
        }
        break;
      default:
        break;
    }
}

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/

