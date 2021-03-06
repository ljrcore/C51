/*******************************************************************************
*  标题:     STM32模拟SPI时序驱动74HC595                                       *
* 																			   *
*   连接方法：JP12用条线冒短接  JP3和JP2 用8PIN排线连接					       *													   *
********************************************************************************
*   现象：一位数码管显示0-F的数字
*   目的：1.通过本例程了解 74HC595（串入并出）基本原理和使用  		           *
*         2.熟悉用STM32控制595程序处理										   *
          3.比较STM32与51的区别               	       				      	   *					       *
*版权所有：普中科技														       *
*技术论坛：www.prechin.net                                                     *                           *
********************************************************************************/

#include "stm32f10x_lib.h"

 /********************************硬件接口定义*********************************/
 //SPI 接口
//SPI IO
#define MOSIO GPIO_Pin_12  //=P3^4;
#define R_CLK GPIO_Pin_13  //=P3^5;
#define S_CLK GPIO_Pin_14  //=P3^6;


/******************************** 变量定义 ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
ErrorStatus HSEStartUpStatus;
unsigned char HC595SendVal;
vu8 LedNumVal;   

// 此表为 LED 的字模          
unsigned char LED7Code[] = {~0x3F,~0x06,~0x5B,~0x4F,~0x66,~0x6D,~0x7D,~0x07,~0x7F,~0x6F,~0x77,~0x7C,~0x39,~0x5E,~0x79,~0x71};


/*********************************声明函数 -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void Delay(vu32 nCount);
void HC595SendData(unsigned char SendVal);
void NOP(void);


/*******************************************************************************
                                  主函数
*******************************************************************************/
int main(void)
{

#ifdef DEBUG
  debug();  //在线调试使用
#endif
  
   RCC_Configuration();      //系统时钟配置函数   

   NVIC_Configuration();     //NVIC配置函数

    //启动GPIO模块时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    //把调试设置普通IO口
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);  
                            
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All; //所有GPIO为同一类型端口
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //输出的最大频率为50HZ
  GPIO_Init(GPIOA, &GPIO_InitStructure);   //初始化GPIOA端口
  GPIO_Init(GPIOB, &GPIO_InitStructure);   //初始化GPIOB端口

  
  GPIO_Write(GPIOA,0xffff);  //将GPIOA 16个端口全部置为高电平
  GPIO_Write(GPIOB,0xffff);  //将GPIOB 16个端口全部置为高电平
  
   while (1)
  {
     LedNumVal++;
     HC595SendVal = LED7Code[LedNumVal%16];     //LED7; 	显示0-F  LedNumVal%10 显示0-9
     HC595SendData(HC595SendVal);
	 Delay(0x3FFFFF);
  }						  

}


/*************************此部分为74HC565的驱动程序使用模拟SPI总线连接*************************************/


/*********************************************************************************************************
** 函数名称: HC595SendData
** 功能描述: 向SPI总线发送数据
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
    GPIO_SetBits(GPIOA, R_CLK);   //片选

}


/*******************************************延时函数**********************************/ 
void NOP()
{ vu16 i;
  for(i=0; i<10; i++); 
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
}

/*******************************************************************************
*                             NVIC配置函数
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
*                              延时函数
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


