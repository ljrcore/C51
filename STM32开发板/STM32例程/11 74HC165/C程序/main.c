/*******************************************************************************
*  标题:  用STM32的普通IO模拟SPI时序 驱动74HC165                               *
*  																			   *
* 连接方法：用8PIN排线将JP5与JP6连接 和 JP11（P2）与JP1（LED灯）连接		   *
*			   																   *
* 1. 通过本例程了解74HC165（并入串出） 的基本原理和使用  					   *
* 2.了解掌握SPI总线接口的工作原理及一般编程方法。  							   *
* 3. 懂的用STM32控制74HC165                         	     		           *
* 4. 比较STM32和51的区别   
注意：PB2有BOOT1功能，使用PB2将BOOT1的短路帽断开，但是下程序时需要端接         *

版权所有：普中科技
技术论坛：www.prechin.net                                                      *
********************************************************************************/

#include "stm32f10x_lib.h"

 /********************************硬件接口定义*********************************/
 //SPI 接口
#define  CLK       GPIO_Pin_14  // = P3^6;
#define  IN_PL     GPIO_Pin_6   //= P1^6;    //74HC165  shift load    把数据加载到锁存器中
#define  IN_Dat    GPIO_Pin_7   //= P1^7;    //74HC165  output        数据通过P1.7脚移进单片机内处理

#define  RELAY     GPIO_Pin_4   //= P1^4;
#define  BEEP      GPIO_Pin_5   //= P1^5;


/******************************** 变量定义 ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
ErrorStatus HSEStartUpStatus;

/*********************************声明函数 -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void Delay(vu32 nCount);
unsigned long ReHC74165(void);
void NOP(void);




/*******************************************************************************
                                  主函数
*******************************************************************************/
int main(void)
{
 unsigned char  Input = 0;

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

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  
  GPIO_Write(GPIOA,0xffff);  //将GPIOA 16个端口全部置为高电平
  GPIO_Write(GPIOB,0xffff);  //将GPIOB 16个端口全部置为高电平
  
    while(1)
   {
     Input = ReHC74165();	  //读取165数据
	 GPIO_Write(GPIOB , ~(Input&0x00ff));	 //将165的数据写到PB0-PB7
    
 	}							  

}


/*************************此部分为74HC165的驱动程序使用SPI总线连接*************************************/


/*********************************************************************************************************
** 函数名称:  74HC165
** 功能描述: 
** 管脚描述：请参考相关的芯片资料(学习光盘中以配)
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
      if(GPIO_ReadInputDataBit(GPIOA,IN_Dat) == 1) 	 //从PA7读取165发来的数据
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


