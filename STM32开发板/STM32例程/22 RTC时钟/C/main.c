/******************** 普中科技  www.prechin.com  *******************************
*                      
*                     STM32内部时钟实验
*  实验目的：  熟悉了解RTC的配置及其读取时间的方法。
*  连接方法：  J17连JP10   J16连JP11
*  实验现象：  看到8位数码管时钟不停地走动
*
*
*******************************************************************************/


#include "stm32f10x_lib.h"


/******************************** 变量定义 ---------------------------------------------------------*/
vu32 TimeDisplay = 0;
ErrorStatus HSEStartUpStatus;
u32 THH = 0, TMM = 0, TSS = 0;

unsigned int jj = 0;
unsigned int  LedNumVal = 0 ,LedNumVal1 = 0;	   //变量定义
//此表为 LED 的字模, 共阴数码管 0-9  - 
unsigned char Disp_Tab[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40};  //段码控制

//此表为8个数码管位选控制, 共阴数码管 1-8个  - 
unsigned char dispbit[8]={0xfe,0xfd,0xfb,0xf7,0xef,0xdF,0xbF,0x7F};    //位选控制   查表的方法控制

unsigned int LedOut[10];		   //变量定义

/*********************************声明函数 -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void USART_Configuration(void);
void RTC_Configuration(void);
void NVIC_Configuration(void);
u32 Time_Regulate(void);
void Time_Adjust(void);
void Time_Show(void);
void Time_Display(u32 TimeVar);
void Delay(vu32 nCount);


/*******************************************************************************
                                  主函数
*******************************************************************************/
int main(void)
{
#ifdef DEBUG
  debug();
#endif

  RCC_Configuration();   //系统时钟配置函数   

  NVIC_Configuration();	 //NVIC配置函数

  GPIO_Configuration();	  //配置GPIO


  if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
  {
    //配置RTC
    RTC_Configuration();

    /* Adjust time by values entred by the user on the hyperterminal */
    Time_Adjust();

     BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
  }
   else
  {
    /* Check if the Power On Reset flag is set */
    if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
   // {
       /* Wait for RTC registers synchronization */
       RTC_WaitForSynchro();

    /* Enable the RTC Second */
    RTC_ITConfig(RTC_IT_SEC, ENABLE);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
  }

#ifdef RTCClockOutput_Enable
  /* Enable PWR and BKP clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);

  /* Disable the Tamper Pin */
  BKP_TamperPinCmd(DISABLE); /* To output RTCCLK/64 on Tamper pin, the tamper
                                 functionality must be disabled */

  /* Enable RTC Clock Output on Tamper Pin */
  BKP_RTCOutputConfig(BKP_RTCOutputSource_CalibClock);
#endif

  //清除复位标志
  RCC_ClearFlag();


 while (1)
{     unsigned int i ;
     
   // if (++jj >= 0x01ff)
   // { LedNumVal1++ ;
   //    jj = 0;
   //  }
      //得到时间并显示
     Time_Display(RTC_GetCounter());

     LedOut[0]=Disp_Tab[THH%100/10];
     LedOut[1]=Disp_Tab[THH%10];
     LedOut[2]=~0XBF; //横线
     LedOut[3]=Disp_Tab[TMM%100/10];
	 
	 LedOut[4]=Disp_Tab[TMM%10];	    
     LedOut[5]=~0XBF;  //横线
     LedOut[6]=Disp_Tab[TSS%100/10];  //十位
     LedOut[7]=Disp_Tab[TSS%10];     //个位	 

	 for( i=0; i<8; i++) 
	 {	 
	    GPIOB->BSRR = LedOut[i]<<8 & 0xFF00;   
        GPIOB->BRR = (~(LedOut[i]<<8)) & 0xFF00;
	         
	    GPIOB->BSRR = dispbit[i] & 0x00FF;   //使用查表法进行位选  
        GPIOB->BRR = (~dispbit[i]) & 0x00FF;
       
        Delay(0x000ff);		 //扫描间隔时间
	 }	
  } //while 
}


void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}



/*******************************************************************************
*                           配置RCC
*******************************************************************************/
void RCC_Configuration(void)
{
  //复位RCC外部设备寄存器到默认值
  RCC_DeInit();

  //打开外部高速晶振
  RCC_HSEConfig(RCC_HSE_ON);

   //等待外部高速时钟准备好
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)   //外部高速时钟已经准别好
  {								    
    //开启FLASH的预取功能
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    //FLASH延迟2个周期
    FLASH_SetLatency(FLASH_Latency_2);
 	
  //配置AHB(HCLK)时钟=SYSCLK
    RCC_HCLKConfig(RCC_SYSCLK_Div1);  
  
   //配置APB2(PCLK2)钟=AHB时钟
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    //配置APB1(PCLK1)钟=AHB 1/2时钟
    RCC_PCLK1Config(RCC_HCLK_Div2);

     //配置PLL时钟 == 外部高速晶体时钟*9  PLLCLK = 8MHz * 9 = 72 MHz 
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    //使能PLL时钟
    RCC_PLLCmd(ENABLE);

   //等待PLL时钟就绪
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

  //配置系统时钟 = PLL时钟
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

   //检查PLL时钟是否作为系统时钟
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }

    //启动GPIO
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB ,ENABLE);

    //启动AFIO
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
                         
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures the nested vectored interrupt controller.
* Input          : None
* Output         : None
* Return         : None
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

  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  /* Enable the RTC Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);


}

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the different GPIO ports.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //引脚频率50M
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_Init(GPIOB, &GPIO_InitStructure);
  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

}

/*******************************************************************************
* Function Name  : RTC_Configuration
* Description    : Configures the RTC.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_Configuration(void)
{ 
  //启用PWR和BKP的时钟（from APB1）
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

    //后备域解锁
  PWR_BackupAccessCmd(ENABLE);

 //备份寄存器模块复位
  BKP_DeInit();

  /* Enable LSE */
  RCC_LSEConfig(RCC_LSE_ON);
 
  //等待稳定
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {}
  //RTC时钟源配置成LSE（外部32.768K）
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

  //RTC开启
  RCC_RTCCLKCmd(ENABLE);

  //开启后需要等待APB1时钟与RTC时钟同步，才能读写寄存器
  RTC_WaitForSynchro();

  //读写寄存器前，要确定上一个操作已经结束
  RTC_WaitForLastTask();
  
    //使能秒中断
  RTC_ITConfig(RTC_IT_SEC, ENABLE);   

  //读写寄存器前，要确定上一个操作已经结束
  RTC_WaitForLastTask();

  //设置RTC分频器，使RTC时钟为1Hz
  //RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1)
  RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */

  //等待寄存器写入完成
  RTC_WaitForLastTask();

    //等待写入完成
  RTC_WaitForLastTask();

}

/*******************************************************************************
* Function Name  : Time_Adjust
* Description    : Adjusts time.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Time_Adjust(void)
{ 
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
  /* Change the current time */
  RTC_SetCounter(12*3600 + 2*60 + 0);
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
}

/*******************************************************************************
* Function Name  : Time_Display
* Description    : Displays the current time.
* Input          : - TimeVar: RTC counter value.
* Output         : None
* Return         : None
*******************************************************************************/
void Time_Display(u32 TimeVar)
{

  /* Compute  hours */
  THH = TimeVar / 3600;
  /* Compute minutes */
  TMM = (TimeVar % 3600) / 60;
  /* Compute seconds */
  TSS = (TimeVar % 3600) % 60;

 }


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
  {}
}


/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
