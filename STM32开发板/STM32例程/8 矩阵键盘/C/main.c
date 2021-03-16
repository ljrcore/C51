/***************************���пƼ� www.prechin.com****************************
	                          STM32-�������ʵ��
 ʵ��Ŀ�ģ� ��Ϥ�˽�STM32GPIO�Ĳ����Ϳ⺯����ʹ��
 ���ӷ����� JP8��JP3  JP10��JP4  
 ʵ������	ÿ�������ļ�ֵ��ʾ�ھ�̩������

*******************************************************************************/

#include "stm32f10x_lib.h"

/******************************** �궨�嶨�� ---------------------------------------------------------*/
#define uchar unsigned char	 //��Ķ���������� uchar ���� unsigned char
#define uint  unsigned int	 //��Ķ���������� uint  ���� unsigned int

/******************************** �������� ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
ErrorStatus HSEStartUpStatus;

/*********************************�������� -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void Delay(vu32 nCount);
void delay0(uchar x);      //x*0.14MS
void  keyscan(void);
void  keydown(void);


// �˱�Ϊ LED ����ģ          	   0	  1		2	 3	   4	 5		6	 7		8	 9	  a		  b	   c	d	  e		 f
unsigned char  LED7Code[] = {~0x3F,~0x06,~0x5B,~0x4F,~0x66,~0x6D,~0x7D,~0x07,~0x7F,~0x6F,~0x77,~0x7C,~0x39,~0x5E,~0x79,~0x71};
uchar  dis_buf;            //��ʾ����
uchar  temp;
uchar  key;                //��˳����

/*******************************************************************************
                                  ������
*******************************************************************************/
int main(void)
{ //int retval;
#ifdef DEBUG
  debug();
#endif

  RCC_Configuration(); //ϵͳʱ�����ú���    

  NVIC_Configuration();	 //NVIC���ú���

  //ʹ��APB2��������ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);  //�رյ��� �˿�����ӳ��  ʹ�÷���������ʱ�������ô���

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All; // ѡ�����н�
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //���ó�����ʽ���
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //���ģʽ�� I/O����ٶ� 50M HZ
   GPIO_Init(GPIOA, &GPIO_InitStructure);  //��PA��ʼ��
  
   GPIO_Write(GPIOA,0XFFFF); //��ʼ��PA�˿��� LED����Ϩ��״̬
  
  
    while(1)
    { 
       keydown();	 //���ð����жϼ�����
	   GPIO_Write(GPIOA,LED7Code[dis_buf%16]&0x7f);	//LED7 0x7fΪС���� �����͹����˴�Ҳ�ǲ�һ��;  %16��ʾ���16����
    
    }
 	
}

/*************************************************************
*                                                           *
* ��ʱ�ӳ���                                                *
*                                                           *
*************************************************************/

void  delay(uchar x)
{ uchar j;
    while((x--)!=0)  //CPUִ��x*12��
    { for(j=0;j<125;j++)
         {;}
    }
}

/*************************************************************
*                                                            *
* ��ɨ���ӳ���  (4*3 �ľ���) P0.4 P0.5 P0.6 P0.7Ϊ��         *
*							  P0.1 P0.2 P0.3Ϊ��             *
*                            								 *
*************************************************************/

 void  keyscan(void)
 { 	temp = 0;
    //P1=0xF0;                 //����λ����   ��Ϊ�ߵ�ƽ  ��Ϊ�͵�ƽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 |  GPIO_Pin_9 |  GPIO_Pin_10 |  GPIO_Pin_11 ; // ѡ�����н�
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //���ó�����ʽ���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //���ģʽ�� I/O����ٶ� 50M HZ
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //��PA��ʼ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 |  GPIO_Pin_13 |  GPIO_Pin_14 |  GPIO_Pin_15 ; // ѡ�����н�
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //���ó�����ʽ���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //���ģʽ�� I/O����ٶ� 50M HZ
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //��PA��ʼ��

	GPIO_Write(GPIOB,0XF0FF); //��ʼ���˿�
    delay(1);				 //��ʱ
	//temp=P1;               //��P1�� 
    temp=(GPIO_ReadInputData(GPIOB))>>8&0xF0;	 //��8λ�����ε���λ
    temp=~((temp>>4)|0x00F0); //������λ�Ƶ���λ������ 	  
    if(temp==1)	  // p0.4 ������
        key=1;	  //��һ������ֵ
    else if(temp==2)   // p0.5 ������
        key=2;	 //��2������ֵ
    else if(temp==4)   // p0.6 ������
        key=3;	  //��3������ֵ
    else if(temp==8)   // p0.7 ������
         key=4;	   //��4������ֵ
    else
        key=16;
        
    //P1=0x0F;             //����λ����  ��Ϊ�ߵ�ƽ ��Ϊ�͵�ƽ
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 |  GPIO_Pin_9 |  GPIO_Pin_10 |  GPIO_Pin_11 ; // ѡ�����н�
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //���ó�����ʽ���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //���ģʽ�� I/O����ٶ� 50M HZ
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //��PA��ʼ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 |  GPIO_Pin_13 |  GPIO_Pin_14 |  GPIO_Pin_15 ; // ѡ�����н�
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //���ó�����ʽ���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //���ģʽ�� I/O����ٶ� 50M HZ
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //��PA��ʼ��

	GPIO_Write(GPIOB,0X0FFF);


    delay(1);			 //��ʱ
	//temp=P1;             //��P1��
    temp=(GPIO_ReadInputData(GPIOB)>>8)&0x0F;
    temp=~(temp|0xF0);
	if(temp==1)		   //p0.0  ������
        key=key+0;
    else if(temp==2)		   //p0.1  ������
        key=key+4;
    else if(temp==4)   //p0.2  ������
        key=key+8;
    else if(temp==8)	//p0.3  ������
        key=key+12;
    else
        key=16;	 
    	
     dis_buf = key;	    //��ֵ����ʾ����
     dis_buf = dis_buf & 0x0f;
 
 }

/*************************************************************
*                                                           *
*�жϼ��Ƿ���                                             *
*                                                           *
*************************************************************/

 void  keydown(void)
 {   int retval;
  	//P1=0xF0;       //����4λȫ����1 ����λȫ����0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 |  GPIO_Pin_9 |  GPIO_Pin_10 |  GPIO_Pin_11 ; // ѡ�����н�
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //���ó�����ʽ���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //���ģʽ�� I/O����ٶ� 50M HZ
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //��PA��ʼ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 |  GPIO_Pin_13 |  GPIO_Pin_14 |  GPIO_Pin_15 ; // ѡ�����н�
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //���ó�����ʽ���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //���ģʽ�� I/O����ٶ� 50M HZ
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //��PA��ʼ��
    
	GPIO_Write(GPIOB,0XF0FF);
	//P1!=0xF0
	retval =  GPIO_ReadInputData(GPIOB); //��PB��״̬
	if(retval>>8!=0xF0)  //�жϰ����Ƿ��� �����ť���� ������P1���е�һ���˿�
	{
	  keyscan();  //���ð���ɨ�����
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

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
