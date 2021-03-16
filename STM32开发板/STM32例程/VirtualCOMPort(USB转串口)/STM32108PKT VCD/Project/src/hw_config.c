/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : hw_config.c
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

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
#include "stm32f10x_it.h"
#include "usb_lib.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "hw_config.h"
#include "platform_config.h"
#include "usb_pwr.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
USART_InitTypeDef USART_InitStructure;

/* Extern variables ----------------------------------------------------------*/
unsigned char buffer_in[BUFFER_SIZE];
unsigned char buffer_out[BUFFER_SIZE];
unsigned char *volatile pbuffer_in_usart;
unsigned char *volatile pbuffer_in_usb;
unsigned char *pbuffer_out_usart;
unsigned int TimeBase;
volatile unsigned short usart_2_usb_count;
volatile bool usart_2_usb_complete;
extern LINE_CODING linecoding;


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : Set_System
* Description    : Configures Main system clocks & power
* Input          : None.
* Return         : None.
*******************************************************************************/
void Set_System(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Setup the microcontroller system. Initialize the Embedded Flash Interface,  
     initialize the PLL and update the SystemFrequency variable. */
  SystemInit();
  
  /* Enable GPIOA, GPIOD and USART1 clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1  , ENABLE);
  
  /* Enable TIM2 clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    
  /* Configure USART1 Rx (PA.10) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure USART1 Tx (PA.09) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* PA Configure: USB DISCONNECT(PA8) as output */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  
   
  
  pbuffer_in_usart = buffer_in;
  pbuffer_in_usb = buffer_in;
  
  pbuffer_out_usart = buffer_out;
 
}

/*******************************************************************************
* Function Name  : Set_USBClock
* Description    : Configures USB Clock input (48MHz)
* Input          : None.
* Return         : None.
*******************************************************************************/
void Set_USBClock(void)
{
  /* USBCLK = PLLCLK / 1.5 */
  RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);
  /* Enable USB clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
}

/*******************************************************************************
* Function Name  : Enter_LowPowerMode
* Description    : Power-off system clocks and power while entering suspend mode
* Input          : None.
* Return         : None.
*******************************************************************************/
void Enter_LowPowerMode(void)
{
  /* Set the device state to suspend */
  bDeviceState = SUSPENDED;
}

/*******************************************************************************
* Function Name  : Leave_LowPowerMode
* Description    : Restores system clocks and power while exiting suspend mode
* Input          : None.
* Return         : None.
*******************************************************************************/
void Leave_LowPowerMode(void)
{
  DEVICE_INFO *pInfo = &Device_Info;

  /* Set the device state to the correct state */
  if (pInfo->Current_Configuration != 0)
  {
    /* Device configured */
    bDeviceState = CONFIGURED;
  }
  else
  {
    bDeviceState = ATTACHED;
  }
}

/*******************************************************************************
* Function Name  : USB_Interrupts_Config
* Description    : Configures the USB interrupts
* Input          : None.
* Return         : None.
*******************************************************************************/
void USB_Interrupts_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

//#ifdef  VECT_TAB_RAM
#if defined (VECT_TAB_RAM)
  /* Set the Vector Table base location at 0x20000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif 

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Enable USART1 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}



/*******************************************************************************
* Function Name  : USB_Cable_Config.
* Description    : Software Connection/Disconnection of USB Cable.
* Input          : NewState: new state.
* Output         : None.
* Return         : None
*******************************************************************************/
void USB_Cable_Config (FunctionalState NewState)
{
  if (NewState == DISABLE)
  {
    GPIO_ResetBits(GPIOA, GPIO_Pin_7);
  }
  else
  {
    GPIO_SetBits(GPIOA, GPIO_Pin_7);
  }
}

/*******************************************************************************
* Function Name  :  USART_Config_Default.
* Description    :  configure the USART1 with default values.
* Input          :  None.
* Return         :  None.
*******************************************************************************/
void USART_Config_Default(void)
{
  /* USART1 default configuration */
  /* USART1 configured as follow:
        - BaudRate = 9600 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - Parity Odd
        - Hardware flow control desabled
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_9b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_Even;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* Configure the USART1 */
  USART_Init(USART1, &USART_InitStructure);

  /* Enable the USART Receive interrupt */
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}

/*******************************************************************************
* Function Name  :  USART_Config.
* Description    :  Configure the UART 1 according to the linecoding structure.
* Input          :  None.
* Return         :  Configuration status
                    TRUE : configuration done with success
                    FALSE : configuration aborted.
*******************************************************************************/
bool USART_Config(void)
{

  /* set the Stop bit*/
  switch (linecoding.format)
  {
    case 0:
      USART_InitStructure.USART_StopBits = USART_StopBits_1;
      break;
    case 1:
      USART_InitStructure.USART_StopBits = USART_StopBits_1_5;
      break;
    case 2:
      USART_InitStructure.USART_StopBits = USART_StopBits_2;
      break;
    default :
    {
      USART_Config_Default();
      return (FALSE);
    }
  }

  /* set the parity bit*/
  switch (linecoding.paritytype)
  {
    case 0:
      USART_InitStructure.USART_Parity = USART_Parity_No;
      break;
    case 1:
      USART_InitStructure.USART_Parity = USART_Parity_Even;
      break;
    case 2:
      USART_InitStructure.USART_Parity = USART_Parity_Odd;
      break;
    default :
    {
      USART_Config_Default();
      return (FALSE);
    }
  }

  /*set the data type : only 8bits and 9bits is supported */
  switch (linecoding.datatype)
  {
    case 0x07:
      /* With this configuration a parity (Even or Odd) should be set */
      USART_InitStructure.USART_WordLength = USART_WordLength_8b;
      break;
    case 0x08:
      if (USART_InitStructure.USART_Parity == USART_Parity_No)
      {
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
      }
      else 
      {
        USART_InitStructure.USART_WordLength = USART_WordLength_9b;
      }
      
      break;
    default :
    {
      USART_Config_Default();
      return (FALSE);
    }
  }

  if (linecoding.bitrate < 115200) 
    TimeBase = TIMER_ARR_10MS;
  else if (linecoding.bitrate >= 256000)
    TimeBase = TIMER_ARR_1MS;
  else 
    TimeBase = TIMER_ARR_5MS;
  Timer_Init(TimeBase);
  
  USART_InitStructure.USART_BaudRate = linecoding.bitrate;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1, &USART_InitStructure);
  USART_Cmd(USART1, ENABLE);
  return (TRUE);
}

/*******************************************************************************
* Function Name  : USB_To_USART_Send_Data.
* Description    : send the received data from USB to the UART 0.
* Input          : data_buffer: data address.
                   Nb_bytes: number of bytes to send.
* Return         : none.
*******************************************************************************/
void USB_To_USART_Send_Data(uint8_t* data_buffer, uint8_t Nb_bytes)
{
  uint32_t i;

  for (i = 0; i < Nb_bytes; i++)
  {
    USART_SendData(USART1, *(data_buffer + i));
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 
  }
}

/*******************************************************************************
* Function Name  : USART_2_USB_Send_Data.
* Description    : send the received data from UART 0 to USB.
* Input          : None.
* Return         : none.
*******************************************************************************/
void USART_2_USB_Send_Data(void)
{
  if (linecoding.datatype == 7)
  {
    *pbuffer_in_usart++ = USART_ReceiveData(USART1) & 0x7F;
  }
  else if (linecoding.datatype == 8)
  {
    *pbuffer_in_usart++ = USART_ReceiveData(USART1);
  }
  
  if (pbuffer_in_usart == &buffer_in[BUFFER_SIZE])
    pbuffer_in_usart = buffer_in;
}

/*******************************************************************************
* Function Name  : Get_SerialNum.
* Description    : Create the serial number string descriptor.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Get_SerialNum(void)
{
  uint32_t Device_Serial0, Device_Serial1, Device_Serial2;

  Device_Serial0 = *(__IO uint32_t*)(0x1FFFF7E8);
  Device_Serial1 = *(__IO uint32_t*)(0x1FFFF7EC);
  Device_Serial2 = *(__IO uint32_t*)(0x1FFFF7F0);

  if (Device_Serial0 != 0)
  {
    Virtual_Com_Port_StringSerial[2] = (uint8_t)(Device_Serial0 & 0x000000FF);
    Virtual_Com_Port_StringSerial[4] = (uint8_t)((Device_Serial0 & 0x0000FF00) >> 8);
    Virtual_Com_Port_StringSerial[6] = (uint8_t)((Device_Serial0 & 0x00FF0000) >> 16);
    Virtual_Com_Port_StringSerial[8] = (uint8_t)((Device_Serial0 & 0xFF000000) >> 24);

    Virtual_Com_Port_StringSerial[10] = (uint8_t)(Device_Serial1 & 0x000000FF);
    Virtual_Com_Port_StringSerial[12] = (uint8_t)((Device_Serial1 & 0x0000FF00) >> 8);
    Virtual_Com_Port_StringSerial[14] = (uint8_t)((Device_Serial1 & 0x00FF0000) >> 16);
    Virtual_Com_Port_StringSerial[16] = (uint8_t)((Device_Serial1 & 0xFF000000) >> 24);

    Virtual_Com_Port_StringSerial[18] = (uint8_t)(Device_Serial2 & 0x000000FF);
    Virtual_Com_Port_StringSerial[20] = (uint8_t)((Device_Serial2 & 0x0000FF00) >> 8);
    Virtual_Com_Port_StringSerial[22] = (uint8_t)((Device_Serial2 & 0x00FF0000) >> 16);
    Virtual_Com_Port_StringSerial[24] = (uint8_t)((Device_Serial2 & 0xFF000000) >> 24);
  }
}


/*******************************************************************************
* Function Name  : Timer_Init
* Description    : Initiate the TIM2 to generate the xms timebase
* Input          : - ARR()
* Output         : None
* Return         : None
*******************************************************************************/
void Timer_Init(uint16_t Time_ARR)
{
  /* ---------------------------------------------------------------
    TIM2 Configuration: Timing Mode:
    TIM2CLK = 72 MHz, Prescaler = 23, TIM2 counter clock = 3MHz
    TIM2 ARR Register = 14999 => TIM2 Frequency = TIM2 counter clock/(ARR + 1)
    TIM2 Frequency = 200Hz.(5ms)
    TIM2 ARR Register = 29999 => TIM2 Frequency = TIM2 counter clock/(ARR + 1)
    TIM2 Frequency = 100Hz.(10ms)
    TIM2 ARR Register = 2999 => TIM2 Frequency = TIM2 counter clock/(ARR + 1)
    TIM2 Frequency = 1000Hz.(1ms)
  --------------------------------------------------------------- */
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;  
  
  TIM_DeInit(TIM2);         /* deinitiate */
  
  TIM_TimeBaseStructure.TIM_Period = Time_ARR;   /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 23;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;   /* Timing Mode :Channel1 */
  TIM_OC1Init(TIM2, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM2, ENABLE);  

  TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);   /* TIM IT enable */

  TIM_Cmd(TIM2, ENABLE);  /* TIM3 enable counter */
}

/*******************************************************************************
* Function Name  : USART_2_USB_Send.
* Description    : send the received data from UART 0 to USB.
* Input          : None.
* Return         : none.
*******************************************************************************/
volatile USB_USART_STATE usart_2_usb_process;
void usart_2_usb_send(void)
{
  unsigned char *ptemp = NULL;
  unsigned char * temp1;
  unsigned int temp2;
  if (pbuffer_in_usb == &buffer_in[BUFFER_SIZE])
    pbuffer_in_usb = buffer_in;
  temp1 = pbuffer_in_usart;
  if(pbuffer_in_usb == temp1) {
    usart_2_usb_process = WAIT_USART2USB_END;        // no data needed to send from USB
    usart_2_usb_complete = TRUE;
    return;
  }
  else if(pbuffer_in_usb > temp1) {  // if the pbuffer_in_usart is rollback
    usart_2_usb_count = &buffer_in[BUFFER_SIZE] - pbuffer_in_usb;
  }
  else {
    temp2 = (unsigned int)pbuffer_in_usart;
    temp2 = temp2 - (unsigned int)pbuffer_in_usb;
    usart_2_usb_count = temp2;
  }
  
  if (usart_2_usb_count > VIRTUAL_COM_PORT_DATA_SIZE){
    ptemp = pbuffer_in_usb;
    UserToPMABufferCopy(ptemp, ENDP1_TXADDR, VIRTUAL_COM_PORT_DATA_SIZE);
    SetEPTxCount(ENDP1, VIRTUAL_COM_PORT_DATA_SIZE);
    usart_2_usb_count -= VIRTUAL_COM_PORT_DATA_SIZE;
    pbuffer_in_usb += VIRTUAL_COM_PORT_DATA_SIZE;
  }
  else {
    ptemp = pbuffer_in_usb;
    UserToPMABufferCopy(ptemp, ENDP1_TXADDR, usart_2_usb_count);
    SetEPTxCount(ENDP1, usart_2_usb_count);
    temp2 = usart_2_usb_count;
    pbuffer_in_usb += temp2;
    usart_2_usb_count = 0;    
  }
  
  usart_2_usb_process = WAIT_USART2USB_END; 
  SetEPTxValid(ENDP1); 
}

/*******************************************************************************
* Function Name  : usart_2_usb_waitend.
* Description    : waitting the flag set by the usb interrupt to indicate the end
                   of the usb transmission.
* Input          : None.
* Return         : none.
*******************************************************************************/
#define CR1_CEN_Set                 ((uint16_t)0x0001)
void usart_2_usb_waitend(void)
{
  if (usart_2_usb_complete == TRUE){
    usart_2_usb_process = USART_RECEIVE;     
    TIM2->CR1 |= CR1_CEN_Set;       // enable timer
    usart_2_usb_complete = FALSE;
  }
  else {
  }
}


/*******************************************************************************
* Function Name  : usb_2_usart_send_data.
* Description    : start the usart sending operation which is called by the usart interrupt
* Input          : None.
* Return         : none.
*******************************************************************************/
extern __IO uint32_t count_out;
void usb_2_usart_send_data(void)
{
  if (count_out == 0) {
    USART_ITConfig(USART1, USART_IT_TXE, DISABLE); 
    SetEPRxValid(ENDP3);
  }
  else {
    USART1->DR = *pbuffer_out_usart & (uint16_t)0x01FF;
    pbuffer_out_usart++;
    count_out--;
  }
}
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
