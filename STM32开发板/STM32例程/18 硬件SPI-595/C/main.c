/*******************************************************************************
*      ����:     STM32Ӳ��SPI����74HC595                                       *
* 																			   *
*   ���ӷ�����JP12������ð�̽�  JP3��JP2 ��8PIN��������					       *													   *
********************************************************************************
*   ����һλ�������ʾ0-F������
*   Ŀ�ģ�1.ͨ���������˽� 74HC595�����벢��������ԭ���ʹ��  		           *
*         2.��Ϥ��STM32Ӳ��SPI�����ü������								   *
*��Ȩ���У����пƼ�														       *
*������̳��www.prechin.net                                                     *                      
********************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

//----------------------------------------------
#define SPI_FLAG_RXNE           SPI_I2S_FLAG_RXNE
#define SPI_FLAG_TXE            SPI_I2S_FLAG_TXE
#define SPI_FLAG_OVR            SPI_I2S_FLAG_OVR
#define SPI_FLAG_BSY            SPI_I2S_FLAG_BSY
//----------------------------------------------
#define SPI_GetFlagStatus       SPI_I2S_GetFlagStatus
#define SPI_SendData            SPI_I2S_SendData
#define SPI_ReceiveData         SPI_I2S_ReceiveData


/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
SPI_InitTypeDef  SPI_InitStructure;
ErrorStatus HSEStartUpStatus;

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void Delay(vu32 nCount);

void SPI_SendByte(u8 byte);
void SPI2_Init(void);
u8 SPI_Send_Byte(u8 dat);


// �˱�Ϊ LED ����ģ          
unsigned char LED7Code[] = {~0x3F,~0x06,~0x5B,~0x4F,~0x66,~0x6D,~0x7D,~0x07,~0x7F,~0x6F,~0x77,~0x7C,~0x39,~0x5E,~0x79,~0x71};


/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{
#ifdef DEBUG
  debug();
#endif
  vu16 Test1=0;

  RCC_Configuration();   //ϵͳʱ�����ú���

  NVIC_Configuration();	 //NVIC���ú���

  //ʹ��APB2��������ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);  //�رյ��� �˿�����ӳ��

  SPI2_Init();
  

   while (1)
  { 
    Test1++; 
    SPI_Send_Byte(LED7Code[Test1%10]); //�������ݵ�SPI����

  }
}



void SPI2_Init(void)
{
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
   
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
  
  /* Configure SPI2 pins: NSS, SCK, MISO and MOSI */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

    /*Configure PA.4(NSS)--------------------------------------------*/
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
  //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  //GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* SPI1 configuration */ 
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����ģʽ
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; //8λ����
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;//SPI_CPOL_High=ģʽ3��ʱ�ӿ���Ϊ�� //SPI_CPOL_Low=ģʽ0��ʱ�ӿ���Ϊ��
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;//SPI_CPHA_2Edge;//SPI_CPHA_1Edge, SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;//SPI_NSS_Soft;//SPI_NSS_Hard
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;//SPI_BaudRatePrescaler_2=18M;//SPI_BaudRatePrescaler_4=9MHz
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//���ݴӸ�λ��ʼ����
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  
  SPI_Init(SPI2, &SPI_InitStructure);
    /*Enable SPI1.NSS as a GPIO*/
  SPI_SSOutputCmd(SPI2, ENABLE);

  /* Enable SPI2  */
  SPI_Cmd(SPI2, ENABLE);   
}


/*******************************************************************************
* Function Name  : SPI_FLASH_SendByte
* Description    : Sends a byte through the SPI interface and return the byte 
*                  received from the SPI bus.
* Input          : byte : byte to send.
* Output         : None
* Return         : The value of the received byte.
*******************************************************************************/
u8 SPI_Send_Byte(u8 dat)
{
  /* Loop while DR register in not emplty */
  while(SPI_GetFlagStatus(SPI2, SPI_FLAG_TXE) == RESET);

  /* Send byte through the SPI2 peripheral */
  SPI_SendData(SPI2, dat);

  /* Wait to receive a byte */
  while(SPI_GetFlagStatus(SPI2, SPI_FLAG_RXNE) == RESET);

  /* Return the byte read from the SPI bus */
  return SPI_ReceiveData(SPI2);
}


/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{   
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);
 	
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
#ifdef  VECT_TAB_RAM  
  /* Set the Vector Table base location at 0x20000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif
}

/*******************************************************************************
* Function Name  : Delay
* Description    : Inserts a delay time.
* Input          : nCount: specifies the delay time length.
* Output         : None
* Return         : None
*******************************************************************************/
void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}

#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
