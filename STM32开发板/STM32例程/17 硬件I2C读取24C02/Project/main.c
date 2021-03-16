/*******************************************************************************
 ���⣺                  Ӳ��I2C��дEEPROM����(��ť����)							   *
********************************************************************************
																			   *
������ѧԱ����һ������Ϥ�����գ��洢оƬAT2402���Ĳ������б���Ͷ�ȡ���� 	   *			   
�˽�����STM32Ӳ��I2C���߽ӿڱ�̷�����								           *
                                                                               *		  
���߲�����P1��JP8���� ����ܣ�JP12��										   *
          P1��JP10 ���� ����������JP5��										   *
																			   *
���������	��1����ť����      ��2����ť��ȡ							       *
��    ��	��׽�仯�����ݱ��浽AT24C02��									   *									   *		  	   
ϣ��ѧԱ�����������������,�����ñ����Դ������EEPROM��						   *							  
********************************************************************************/
#include "i2c_ee.h"

 /********************************Ӳ���ӿڶ���*********************************/
#define    LS138A  GPIO_Pin_5 //=P2^2;       //138�������ܽŶ���
#define    LS138B  GPIO_Pin_4 //=P2^3;
#define    LS138C  GPIO_Pin_3 //=P2^4; 

/********************************�궨��*********************************/
#define    Save      GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_8)//P0^0;	 //����
#define    Read      GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_9)//P0^1;	 //��ȡ
#define    LS138a(x)  x ? GPIO_SetBits(GPIOB, LS138A): GPIO_ResetBits(GPIOB, LS138A)
#define    LS138b(x)  x ? GPIO_SetBits(GPIOB, LS138B): GPIO_ResetBits(GPIOB, LS138B)
#define    LS138c(x)  x ? GPIO_SetBits(GPIOB, LS138C): GPIO_ResetBits(GPIOB, LS138C)

#define EEPROM_WriteAddress1    0x05
#define EEPROM_ReadAddress1     0x05

/******************************** �������� ---------------------------------------------------------*/
unsigned long D[16], LedOut[8],LedNumVal , LedNumVal1;
unsigned char Count1 , Count2 , save_flag = 1 , read_flag = 1;

//�˱�Ϊ LED ����ģ, ��������� 0-9  - 
unsigned char  Disp_Tab[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40}; 
  

/*********************************�������� -----------------------------------------------*/
void RCC_Configuration(void);
void Delay(vu32 nCount);


int main(void)
{
  RCC_Configuration(); //����ϵͳʱ��

  I2C_EE_Init();  //��ʼ��I2C
  
  //I2C_EE_WaitEepromStandbyState(); //�ȴ�EEPROM���ȶ�״̬
   
  while (1)
  {	unsigned char i;
	
	if(Read  == 0 && read_flag)	   //�ڶ�����ť��ȡ����
	{ 
	    I2C_EE_BufferRead(&Count2, EEPROM_ReadAddress1, 1); 
	    read_flag = 0;
		save_flag = 1;	     
	 }

	   //========================IIC ����
	   if(Save == 0 && save_flag)    //��һ����ť��������
	   { 
		I2C_EE_BufferWrite(&Count1, EEPROM_WriteAddress1, 1); 
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

	  Count1++;
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
		   Delay(0x0AFFF);
	  }



  }
}


void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval : None
  */
void RCC_Configuration(void)
{
  /* Setup the microcontroller system. Initialize the Embedded Flash Interface,  
     initialize the PLL and update the SystemFrequency variable. */
  SystemInit();

/* Enable peripheral clocks --------------------------------------------------*/
  /* GPIOB Periph clock enable */
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

	//����GPIOģ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	//�ѵ���������ͨIO��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);

  /* I2C1 Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

