/**********************************************************************************
*  ����:       ************* STM32 ģ��I2C-DA-AD����*******************           *
*																				  *
*   1.ͨ���������˽Ⲣ����AD-DAת��оƬ�Ļ���ԭ���ʹ�� 						  *
*   2.�˽�����I2C���߽ӿڵĹ���ԭ��һ���̷�����								  *
*   																			  *
*    ���ӷ�����JP10 ��P0����J12���������� 								          *
*    																			  *
* ͨ���ı�ѧϰ���ϵ�2����λ����Ӧ��2��ģ�����룬ʵ��ģ�����룬ѧԱ�۲�����ܵ�����*
�仯���																		  *
* ͨ����AD0��λ����ʵ��ģ������--ģ�������ѧԱ�۲�ѧϰ����DA��LED�����ȱ仯	  *			  *
*				  *																  *
           	                                                                      *
��ѧԱ�������������̣�����AD-DA ��C�����еĲ���Ӧ��                       	      *
***********************************************************************************/

#include "stm32f10x_lib.h"	 
#include"Function.h"

 /********************************Ӳ���ӿڶ���*********************************/
#define    LS138A  GPIO_Pin_5 //=P2^2;       //138�������ܽŶ���
#define    LS138B  GPIO_Pin_4 //=P2^3;
#define    LS138C  GPIO_Pin_3 //=P2^4; 


/********************************�궨��*********************************/
#define    LS138a(x)  x ? GPIO_SetBits(GPIOB, LS138A): GPIO_ResetBits(GPIOB, LS138A)
#define    LS138b(x)  x ? GPIO_SetBits(GPIOB, LS138B): GPIO_ResetBits(GPIOB, LS138B)
#define    LS138c(x)  x ? GPIO_SetBits(GPIOB, LS138C): GPIO_ResetBits(GPIOB, LS138C)

#define  PCF8591 0x90    //PCF8591 ��ַ



/******************************** �������� ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;     //GPIO
ErrorStatus HSEStartUpStatus;

unsigned long D[16], LedOut[8];
unsigned char AD_CHANNEL;
static vu32 TimingDelay;

//�˱�Ϊ LED ����ģ, ��������� 0-9  - 
unsigned char  Disp_Tab[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40}; 

/*********************************�������� -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void SysTick_Configuration(void);
void Delay_us(u32 nTime);
u8 DACconversion(unsigned char sla,unsigned char c,  unsigned char Val);
u8 ISendByte(unsigned char sla,unsigned char c);
u8 IRcvByte(unsigned char sla);

 main()
 { 	unsigned char i;
	
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

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 |GPIO_Pin_10 |GPIO_Pin_11   ;
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
	   /********����AD-DA����*************/  
	   switch(AD_CHANNEL)
	   {
	     case 0: ISendByte(PCF8591,0x41);
	             D[0]=IRcvByte(PCF8591)*2;  //ADC0 ģ��ת��1  �Ŵ�2����ʾ
				 break;  
	 
		 case 1: ISendByte(PCF8591,0x42);
	             D[1]=IRcvByte(PCF8591)*2;  //ADC1  ģ��ת��2
				 break;  
	
		 case 2: ISendByte(PCF8591,0x43);
	             D[2]=IRcvByte(PCF8591)*2;  //ADC2	ģ��ת��3
				 break;  
	
		 case 3: ISendByte(PCF8591,0x40);
	             D[3]=IRcvByte(PCF8591)*2;  //ADC3   ģ��ת��4
				 break;  
	
		 case 4: DACconversion(PCF8591,0x40, D[4]/4); //DAC	  ��ģת��
		         break;
	   }
	
		      // D[4]=400;  //����--->>ģ�����
			  D[4]=D[0]*4;  //   ��ģ������ �������ź� ͨ����ģת�����
	   if(++AD_CHANNEL>4) AD_CHANNEL=0;
	
	 /********���½�AD��ֵ�͵�LED�������ʾ*************/
    
	  LedOut[0]=Disp_Tab[D[0]%10000/1000];
      LedOut[1]=Disp_Tab[D[0]%1000/100];
      LedOut[2]=Disp_Tab[D[0]%100/10]|0x80;
      LedOut[3]=Disp_Tab[D[0]%10];
	  
	  LedOut[4]=Disp_Tab[D[0]%10000/1000];
      LedOut[5]=Disp_Tab[D[0]%1000/100];
      LedOut[6]=Disp_Tab[D[0]%100/10]|0x80;
      LedOut[7]=Disp_Tab[D[0]%10];  
  	  
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
		Delay_us(600); 
	  }

	}
   
}



/*******************************************************************
DAC �任, ת������               
*******************************************************************/
u8 DACconversion(unsigned char sla,unsigned char c,  unsigned char Val)
{
   Start_I2c();              //��������
   SendByte(sla);            //����������ַ
   if(ack==0)return(0);
   SendByte(c);              //���Ϳ����ֽ�
   if(ack==0)return(0);
   SendByte(Val);            //����DAC����ֵ  
   if(ack==0)return(0);
   Stop_I2c();               //��������
   return(1);
}

/*******************************************************************
ADC�����ֽ�[����]���ݺ���               
*******************************************************************/
u8 ISendByte(unsigned char sla,unsigned char c)
{
   Start_I2c();              //��������
   SendByte(sla);            //����������ַ
   if(ack==0)return(0);
   SendByte(c);              //��������
   if(ack==0)return(0);
   Stop_I2c();               //��������
   return(1);
}

/*******************************************************************
ADC���ֽ����ݺ���               
*******************************************************************/
unsigned char IRcvByte(unsigned char sla)
{  unsigned char c;

   Start_I2c();          //��������
   SendByte(sla+1);      //����������ַ
   if(ack==0)return(0);
   c=RcvByte();          //��ȡ����0

   Ack_I2c(1);           //���ͷǾʹ�λ
   Stop_I2c();           //��������
   return(c);
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
