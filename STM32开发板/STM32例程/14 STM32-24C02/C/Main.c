/*******************************************************************************
 ���⣺                  EEPROM��д����(��ť����)							   *
********************************************************************************
																			   *
������ѧԱ����һ������Ϥ�����գ��洢оƬAT2402���Ĳ������б���Ͷ�ȡ���� 	   *			   
�˽�����I2C���߽ӿڵĹ���ԭ��һ���̷�����								   *
                                                                               *		  
���߲�����P1��JP8���� ����ܣ�JP12��										   *
          P1��JP10 ���� ����������JP5��										   *
																			   *
���������	��1����ť����      ��2����ť��ȡ							       *
��    ��	��׽�仯�����ݱ��浽AT24C02��									   *									   *		  	   
ϣ��ѧԱ�����������������,�����ñ����Դ������EEPROM��						   *							  
********************************************************************************/

#include "stm32f10x_lib.h"
#include"Function.h"


 /********************************Ӳ���ӿڶ���*********************************/
#define    LS138A  GPIO_Pin_5 //=P2^2;       //138�������ܽŶ���
#define    LS138B  GPIO_Pin_4 //=P2^3;
#define    LS138C  GPIO_Pin_3 //=P2^4; 


/********************************�궨��*********************************/
#define    Save      GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_8)//P1^0;	 //����
#define    Read      GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_9)//P1^1;	 //��ȡ
#define    LS138a(x)  x ? GPIO_SetBits(GPIOB, LS138A): GPIO_ResetBits(GPIOB, LS138A)
#define    LS138b(x)  x ? GPIO_SetBits(GPIOB, LS138B): GPIO_ResetBits(GPIOB, LS138B)
#define    LS138c(x)  x ? GPIO_SetBits(GPIOB, LS138C): GPIO_ResetBits(GPIOB, LS138C)

#define  AT24C02 0xa0  //AT24C02 ��ַ



/******************************** �������� ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;     //GPIO
ErrorStatus HSEStartUpStatus;

unsigned char Count1 , Count2 , save_flag = 1 , read_flag = 1;
unsigned long D[16], LedOut[8],LedNumVal , LedNumVal1;
unsigned int  USEC;
static vu32 TimingDelay;

//�˱�Ϊ LED ����ģ, ��������� 0-9  - 
unsigned char  Disp_Tab[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40}; 

/*********************************�������� -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void SysTick_Configuration(void);
void Delay_us(u32 nTime);

 main()
 { 	unsigned char i;
	unsigned char pDat[8];
	
	#ifdef DEBUG
	debug();  //���ߵ���ʹ��
	#endif
	
	RCC_Configuration();      //ϵͳʱ�����ú��� 
	
	NVIC_Configuration();     //NVIC���ú��� 
	
    SysTick_Configuration();   //Systick���ú���
	
	
	//����GPIOģ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB1Periph_TIM2 | RCC_APB2Periph_AFIO, ENABLE);
	//�ѵ���������ͨIO��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);  
	                        
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All; //����GPIOΪͬһ���Ͷ˿�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //��������Ƶ��Ϊ50HZ
	GPIO_Init(GPIOA, &GPIO_InitStructure);   //��ʼ��GPIOA�˿�
	GPIO_Init(GPIOB, &GPIO_InitStructure);   //��ʼ��GPIOB�˿�

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //��������	 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //��������Ƶ��Ϊ50HZ
	GPIO_Init(GPIOB, &GPIO_InitStructure);   //��ʼ��GPIOA�˿�

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7  ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  //��©���	 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //��������Ƶ��Ϊ50HZ
	GPIO_Init(GPIOB, &GPIO_InitStructure);   //��ʼ��GPIOA�˿�
	
	GPIO_Write(GPIOA,0xffff);  //��GPIOA 16���˿�ȫ����Ϊ�ߵ�ƽ
	GPIO_Write(GPIOB,0xffff);  //��GPIOB 16���˿�ȫ����Ϊ�ߵ�

   while(1)
   {
		 //========================IIC ��ȡ
	if(Read  == 0 && read_flag)	   //�ڶ�����ť��ȡ����
	{ 
	  IRcvStr(AT24C02, 0 , &pDat[0], 8); 
	  for (i=0; i<4; i++)
	  {
		D[14+i]=pDat[i*2+0]+pDat[i*2+1]*0x100;
		Count2 = D[14];
	   }
	    read_flag = 0;
		save_flag = 1;	     
	 }

	   //========================IIC ����
	   if(Save == 0 && save_flag)    //��һ����ť��������
	   { 
	      D[14]= Count1;
		 for (i=0; i<4; i++)
	     {
		   pDat[i*2+0]=D[14+i];
		   pDat[i*2+1]=D[14+i]>>8;
		 }
	     ISendStr(AT24C02, 0 , &pDat[0], 8); 
		 read_flag = 1;
		 save_flag = 0;
       }


	  /********���½�2402�б���������͵�LED�������ʾ*************/
      LedNumVal=Count2;
	  LedOut[0]=Disp_Tab[LedNumVal%10000/1000];
      LedOut[1]=Disp_Tab[LedNumVal%1000/100];
      LedOut[2]=Disp_Tab[LedNumVal%100/10]|0x80;
      LedOut[3]=Disp_Tab[LedNumVal%10];
	  
	  LedNumVal1=Count1;
	  LedOut[4]=Disp_Tab[LedNumVal1%10000/1000];
      LedOut[5]=Disp_Tab[LedNumVal1%1000/100];
      LedOut[6]=Disp_Tab[LedNumVal1%100/10]|0x80;
      LedOut[7]=Disp_Tab[LedNumVal1%10];  
  	  
      for(i=0; i<8; i++) 
  	  {		
     	GPIOA->BSRR = LedOut[i] & 0x00FF;   
        GPIOA->BRR = (~LedOut[i]) & 0x00FF;
	  			 	 	  	
		switch(i)					  
         {	    	  //138����
			case 0:	  //0 0 0 
			LS138a(0);	 LS138b(0);  LS138c(0);
			break;         
            case 1:	 //1 0 0 
			LS138a(1);	 LS138b(0);  LS138c(0);
			 break;             	
            case 2:	 //0 1 0
			LS138a(0);	 LS138b(1);  LS138c(0);
			break; 
            case 3:	 //1 1 0
			LS138a(1);	 LS138b(1);  LS138c(0);
			break;
			
			case 4:	 //0 0 1
			LS138a(0);	 LS138b(0);  LS138c(1);
			break; 
			
			case 5:	 //1 0 1
			LS138a(1);	 LS138b(0);  LS138c(1);
			break; 

			case 6:	 //0 1 1
			LS138a(0);	 LS138b(1);  LS138c(1);
			break;

			case 7:	 //1 1 1
			LS138a(1);	 LS138b(1);  LS138c(1);
			break;

			
		 
         }
		    Delay_us(700); 
	  }

	}
   
}

/******************************************************************************
*
*                         ��׼��ʱ����
*
**********************************************************************************/
void Delay_us(u32 nTime)
{
  /* Enable the SysTick Counter */
  SysTick_CounterCmd(SysTick_Counter_Enable);
  
  TimingDelay = nTime;

  while(TimingDelay != 0);

  /* Disable SysTick Counter */
  SysTick_CounterCmd(SysTick_Counter_Disable);
  /* Clear SysTick Counter */
  SysTick_CounterCmd(SysTick_Counter_Clear);
}

/*******************************************************************************
*
*                         ϵͳSystick �жϴ�����
*
*******************************************************************************/
void SysTick_Handler(void)   
{   
     if (TimingDelay != 0x00)
  { 
    TimingDelay--;
	
  }

  if(USEC++ == 1000000)
  {	 USEC = 0;
	 Count1++;
   }

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


void SysTick_Configuration(void)   
{   
  /*  ����AHBʱ��ΪSysTickʱ��*/  
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);  //����8��Ƶ 
  
  /* ����SysTicks�ж���ռ���ȼ� 3�� �����ȼ�0*/  
  NVIC_SystemHandlerPriorityConfig(SystemHandler_SysTick, 3, 0);   
      
  /* ÿ1ms����һ��SysTick�ж� ��72M��ʱ����*/  
  SysTick_SetReload(9);     //1΢���������
  
  /* ����SysTick�ж� */  
  SysTick_ITConfig(ENABLE);   
}  


/*******************************************************************************
*                             NVIC���ú���
*******************************************************************************/
void NVIC_Configuration(void)
{
 NVIC_InitTypeDef NVIC_InitStructure;
#ifdef  VECT_TAB_RAM  
  /* Set the Vector Table base location at 0x20000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif

  
       /* ������ʱ��2 */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
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
