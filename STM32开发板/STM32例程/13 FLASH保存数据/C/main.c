/******************** 普中科技 www.prechin.com ********************
* 
*                         FLASH保存数据实验
* 实验目的：  熟悉FLASH及其操作
*
* 连接方法： 参考 “连接方法” 图片演示
*
* 实验现象： 用K1设定一个数据， 先用K2擦除指定FLASH扇区 再按K3保存数据 
*            再按K4把数据调到数码管显示，与先前设定的数据对比下。
*            也可以关掉电源后开机，按K4即可显示先前保存的数据
*
*******************************************************************************/


#include "stm32f10x_lib.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define FLASH_PAGE_SIZE    ((u16)0x400)   //USE_STM3210B
#define StartAddr          ((u32)0x08008000)
#define EndAddr            ((u32)0x0800C000)



/******************************** 变量定义 ------------------------------------*/
u32 EraseCounter = 0x00, Address = 0x00;
u32 Data;
vu32 NbrOfPage = 0x00;
volatile FLASH_Status FLASHStatus;
volatile TestStatus MemoryProgramStatus;
ErrorStatus HSEStartUpStatus;
bool EraseFlag  = FALSE , ProgramFlag = FALSE;

unsigned int jj = 0;
unsigned int  LedNumVal = 0 ,LedNumVal1 = 0;	   //变量定义
//此表为 LED 的字模, 共阴数码管 0-9  - 
unsigned char Disp_Tab[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40};  //段码控制

//此表为8个数码管位选控制, 共阴数码管 1-8个  - 
unsigned char dispbit[8]={0xfe,0xfd,0xfb,0xf7,0xef,0xdF,0xbF,0x7F};    //位选控制   查表的方法控制

unsigned int LedOut[10];		   //变量定义

/*********************************声明函数 -----------------------------------------------*/
void NVIC_Configuration(void);
void RCC_Configuration(void);
void GPIO_Configuration(void);
void Delay(vu32 nCount);
    
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{
#ifdef DEBUG
  debug();
#endif

  FLASHStatus = FLASH_COMPLETE;
  MemoryProgramStatus = PASSED;
  Data = 0x15041979;
  
  RCC_Configuration();  //配置系统时钟

  NVIC_Configuration();	 //配置NVIC中断

  FLASH_Unlock(); //解锁FLASH 编程擦除控制器

  GPIO_Configuration();	  //配置GPIO

  /* Define the number of page to be erased */
  NbrOfPage = (EndAddr - StartAddr) / FLASH_PAGE_SIZE;

    //清除所有标志标志
  FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	  
  /*  FLASH Word program of data 0x15041979 at addresses defined by StartAddr and EndAddr*/
   
  
  while (1)
  {
     
    unsigned int i ;
     
    if (++jj >= 0x00ff && GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0)
     { LedNumVal1++ ;
       jj = 0;
       EraseFlag = FALSE;
	   ProgramFlag = FALSE;
     }
   //GPIO_Pin_6 擦出FLASH按钮
   if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 0 && !EraseFlag) 
   { 
     /* 清除FLASH待处理的标志位 */
     FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	
     FLASHStatus = FLASH_ErasePage(StartAddr);
     EraseFlag = TRUE; //做了个擦出标志，FLASH可擦除的寿命有限，以免当按钮按住不放时反复擦除FLASH.
    
    }//if
   
   //GPIO_Pin_5 保存数据到FLASH按钮
   if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2) == 0 && !ProgramFlag ) 
   {    Address = StartAddr;
	    FLASHStatus = FLASH_ProgramWord(Address, LedNumVal1);
		ProgramFlag = TRUE;
	
   }//if
    //GPIO_Pin_4 从FLASH中读出数据按钮
   if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3) == 0) 
   {
      Address = StartAddr;
      LedNumVal =  (*(vu32*) Address);
   
    }//if
         
     LedOut[0]=Disp_Tab[LedNumVal%10000/1000];
     LedOut[1]=Disp_Tab[LedNumVal%1000/100];
     LedOut[2]=Disp_Tab[LedNumVal%100/10];
     LedOut[3]=Disp_Tab[LedNumVal%10];
	 
	 LedOut[4]=Disp_Tab[LedNumVal1%100000/1000];	    
     LedOut[5]=Disp_Tab[LedNumVal1%1000/100];
     LedOut[6]=Disp_Tab[LedNumVal1%100/10];  //十位
     LedOut[7]=Disp_Tab[LedNumVal1%10];     //个位	 

	 for( i=0; i<8; i++) 
	 {	 
	    GPIOB->BSRR = LedOut[i]<<8 & 0xFF00;   
        GPIOB->BRR = (~(LedOut[i]<<8)) & 0xFF00;


         //使用查表法进行位选 
	    GPIOB->BSRR = dispbit[i] & 0x00FF;   
        GPIOB->BRR = (~dispbit[i]) & 0x00FF;
       
        Delay(0x000ff);		 //扫描间隔时间
	 }	
   
  }
}

void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
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
  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

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
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{   
 //复位RCC外部设备寄存器到默认值
  RCC_DeInit();  

  //打开外部高速晶振
  RCC_HSEConfig(RCC_HSE_ON); 

 //等待外部高速时钟准备好
  HSEStartUpStatus = RCC_WaitForHSEStartUp(); 

  //外部高速时钟已经准别好
  if(HSEStartUpStatus == SUCCESS)  
  {
    
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

   
    FLASH_SetLatency(FLASH_Latency_2);
  
   //配置AHB(HCLK)时钟=SYSCLK
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
  
    //配置APB2(PCLK2)钟=AHB时钟
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    //配置APB1(PCLK1)钟=AHB 1/2时钟
    RCC_PCLK1Config(RCC_HCLK_Div2);  

    //配置ADC时钟=PCLK2 1/4
    RCC_ADCCLKConfig(RCC_PCLK2_Div4); 
  
    //配置PLL时钟 == 外部高速晶体时钟*9
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9); 
    
	//配置ADC时钟= PCLK2/4
    RCC_ADCCLKConfig(RCC_PCLK2_Div4);

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

  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
