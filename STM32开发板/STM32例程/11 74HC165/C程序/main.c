/*******************************************************************************
*  ����:  ��STM32����ͨIOģ��SPIʱ�� ����74HC165                               *
*  																			   *
* ���ӷ�������8PIN���߽�JP5��JP6���� �� JP11��P2����JP1��LED�ƣ�����		   *
*			   																   *
* 1. ͨ���������˽�74HC165�����봮���� �Ļ���ԭ���ʹ��  					   *
* 2.�˽�����SPI���߽ӿڵĹ���ԭ��һ���̷�����  							   *
* 3. ������STM32����74HC165                         	     		           *
* 4. �Ƚ�STM32��51������   
ע�⣺PB2��BOOT1���ܣ�ʹ��PB2��BOOT1�Ķ�·ñ�Ͽ��������³���ʱ��Ҫ�˽�         *

��Ȩ���У����пƼ�
������̳��www.prechin.net                                                      *
********************************************************************************/

#include "stm32f10x_lib.h"

 /********************************Ӳ���ӿڶ���*********************************/
 //SPI �ӿ�
#define  CLK       GPIO_Pin_14  // = P3^6;
#define  IN_PL     GPIO_Pin_6   //= P1^6;    //74HC165  shift load    �����ݼ��ص���������
#define  IN_Dat    GPIO_Pin_7   //= P1^7;    //74HC165  output        ����ͨ��P1.7���ƽ���Ƭ���ڴ���

#define  RELAY     GPIO_Pin_4   //= P1^4;
#define  BEEP      GPIO_Pin_5   //= P1^5;


/******************************** �������� ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
ErrorStatus HSEStartUpStatus;

/*********************************�������� -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void Delay(vu32 nCount);
unsigned long ReHC74165(void);
void NOP(void);




/*******************************************************************************
                                  ������
*******************************************************************************/
int main(void)
{
 unsigned char  Input = 0;

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

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  
  GPIO_Write(GPIOA,0xffff);  //��GPIOA 16���˿�ȫ����Ϊ�ߵ�ƽ
  GPIO_Write(GPIOB,0xffff);  //��GPIOB 16���˿�ȫ����Ϊ�ߵ�ƽ
  
    while(1)
   {
     Input = ReHC74165();	  //��ȡ165����
	 GPIO_Write(GPIOB , ~(Input&0x00ff));	 //��165������д��PB0-PB7
    
 	}							  

}


/*************************�˲���Ϊ74HC165����������ʹ��SPI��������*************************************/


/*********************************************************************************************************
** ��������:  74HC165
** ��������: 
** �ܽ���������ο���ص�оƬ����(ѧϰ����������)
*********************************************************************************************************/
unsigned long ReHC74165(void)
{  
  unsigned char i ;
  unsigned char indata ;
		
   //IN_PL=0;
   GPIO_ResetBits(GPIOA , IN_PL);
   NOP();
   NOP();
   //IN_PL=1;
   GPIO_SetBits(GPIOA , IN_PL);
   NOP();
   NOP();
          
   indata=0xff;     
   for(i=0; i<8; i++)
    { 
	  indata=indata<<1;
      if(GPIO_ReadInputDataBit(GPIOA,IN_Dat) == 1) 	 //��PA7��ȡ165����������
	  indata=indata+1;
 	  
	  //CLK=1;
	  GPIO_SetBits(GPIOA , CLK);  
      NOP();
	  NOP();
	       //CLK=0;
	  GPIO_ResetBits(GPIOA , CLK);
	  NOP();
	  NOP();
	  
	} 
   
   return(indata);	 //
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


