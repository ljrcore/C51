/*******************************************************************************
*  ����:     STM32ģ��SPIʱ������74HC595                                       *
* 																			   *
*   ���ӷ�����JP12������ð�̽�  JP3��JP2 ��8PIN��������					       *													   *
********************************************************************************
*   ����һλ�������ʾ0-F������
*   Ŀ�ģ�1.ͨ���������˽� 74HC595�����벢��������ԭ���ʹ��  		           *
*         2.��Ϥ��STM32����595������										   *
          3.�Ƚ�STM32��51������               	       				      	   *					       *
*��Ȩ���У����пƼ�														       *
*������̳��www.prechin.net                                                     *                           *
********************************************************************************/

#include "stm32f10x_lib.h"

 /********************************Ӳ���ӿڶ���*********************************/
 //SPI �ӿ�
//SPI IO
#define MOSIO GPIO_Pin_12  //=P3^4;
#define R_CLK GPIO_Pin_13  //=P3^5;
#define S_CLK GPIO_Pin_14  //=P3^6;


/******************************** �������� ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
ErrorStatus HSEStartUpStatus;
unsigned char HC595SendVal;
vu8 LedNumVal;   

// �˱�Ϊ LED ����ģ          
unsigned char LED7Code[] = {~0x3F,~0x06,~0x5B,~0x4F,~0x66,~0x6D,~0x7D,~0x07,~0x7F,~0x6F,~0x77,~0x7C,~0x39,~0x5E,~0x79,~0x71};


/*********************************�������� -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void Delay(vu32 nCount);
void HC595SendData(unsigned char SendVal);
void NOP(void);


/*******************************************************************************
                                  ������
*******************************************************************************/
int main(void)
{

#ifdef DEBUG
  debug();  //���ߵ���ʹ��
#endif
  
   RCC_Configuration();      //ϵͳʱ�����ú���   

   NVIC_Configuration();     //NVIC���ú���

    //����GPIOģ��ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    //�ѵ���������ͨIO��
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);  
                            
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All; //����GPIOΪͬһ���Ͷ˿�
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //��������Ƶ��Ϊ50HZ
  GPIO_Init(GPIOA, &GPIO_InitStructure);   //��ʼ��GPIOA�˿�
  GPIO_Init(GPIOB, &GPIO_InitStructure);   //��ʼ��GPIOB�˿�

  
  GPIO_Write(GPIOA,0xffff);  //��GPIOA 16���˿�ȫ����Ϊ�ߵ�ƽ
  GPIO_Write(GPIOB,0xffff);  //��GPIOB 16���˿�ȫ����Ϊ�ߵ�ƽ
  
   while (1)
  {
     LedNumVal++;
     HC595SendVal = LED7Code[LedNumVal%16];     //LED7; 	��ʾ0-F  LedNumVal%10 ��ʾ0-9
     HC595SendData(HC595SendVal);
	 Delay(0x3FFFFF);
  }						  

}


/*************************�˲���Ϊ74HC565����������ʹ��ģ��SPI��������*************************************/


/*********************************************************************************************************
** ��������: HC595SendData
** ��������: ��SPI���߷�������
*********************************************************************************************************/
void HC595SendData(unsigned char SendVal)
{  
  unsigned char i;
		
  for(i=0;i<8;i++) 
   {
	if((SendVal<<i)&0x80) GPIO_SetBits(GPIOA, MOSIO); 
	else GPIO_ResetBits(GPIOA, MOSIO);  			
 
	GPIO_ResetBits(GPIOA, S_CLK);   
	NOP();
	NOP();
	GPIO_SetBits(GPIOA, S_CLK);   	
   }
   	
    GPIO_ResetBits(GPIOA, R_CLK);  
    NOP();
    NOP();
    GPIO_SetBits(GPIOA, R_CLK);   //Ƭѡ

}


/*******************************************��ʱ����**********************************/ 
void NOP()
{ vu16 i;
  for(i=0; i<10; i++); 
}

/*******************************************************************************
*                           ����RCC
*******************************************************************************/
void RCC_Configuration(void)
{   
 //��λRCC�ⲿ�豸�Ĵ�����Ĭ��ֵ
  RCC_DeInit();

  //���ⲿ���پ���
  RCC_HSEConfig(RCC_HSE_ON);

   //�ȴ��ⲿ����ʱ��׼����
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)   //�ⲿ����ʱ���Ѿ�׼���
  {								    
    //����FLASH��Ԥȡ����
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    //FLASH�ӳ�2������
    FLASH_SetLatency(FLASH_Latency_2);
 	
  //����AHB(HCLK)ʱ��=SYSCLK
    RCC_HCLKConfig(RCC_SYSCLK_Div1);  
  
   //����APB2(PCLK2)��=AHBʱ��
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    //����APB1(PCLK1)��=AHB 1/2ʱ��
    RCC_PCLK1Config(RCC_HCLK_Div2);

     //����PLLʱ�� == �ⲿ���پ���ʱ��*9  PLLCLK = 8MHz * 9 = 72 MHz 
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    //ʹ��PLLʱ��
    RCC_PLLCmd(ENABLE);

   //�ȴ�PLLʱ�Ӿ���
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

  //����ϵͳʱ�� = PLLʱ��
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

   //���PLLʱ���Ƿ���Ϊϵͳʱ��
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
}

/*******************************************************************************
*                             NVIC���ú���
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
*                              ��ʱ����
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


