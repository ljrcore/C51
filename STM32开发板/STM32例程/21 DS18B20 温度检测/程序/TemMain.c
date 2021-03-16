 /*******************************************************************************
*  标题:                  试验数码管上显示温度                                  *
*																			    *
*********************************************************************************
* 目的： 1.通过本例程了解 DLASS18b20的基本原理和使用 ,理解并掌握18B20驱动程序的编写	*
*        2.了解掌握“一线”总线接口的工作原理及一般编程方法。 					*
* 现象：   插上18B20 观察数码管的实际温度显示
* 连接： 用排线将JP8(P0口) 与 J12 连接在数码管上可以看温度显示					*
* 																				*
* 建议： 不要延时等待，用定时中断实现时序，来提高程序处理速度                   *
* 请学员认真消化本例程，懂DLASS18b20在C语言中的操作                       	    *
********************************************************************************/
#include "stm32f10x_lib.h"


 /********************************硬件接口定义*********************************/
#define    LS138A  GPIO_Pin_5 //=P2^2;       //管脚定义
#define    LS138B  GPIO_Pin_4 //=P2^3;
#define    LS138C  GPIO_Pin_3 //=P2^4; 


/******************************** 变量定义 ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
ErrorStatus HSEStartUpStatus;

//此表为 LED 的字模, 共阴数码管 0-9  - 
unsigned char  Disp_Tab[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40}; 
u32  LedOut[7],LedNumVal;
u8 Count;
static vu32 TimingDelay;



/*********************************声明函数 -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void SysTick_Configuration(void);
void HC595SendData(unsigned char SendVal);
void NOP(void);
extern GetTemp(void);						      //声明引用外部函数
extern unsigned int   Temperature;	              // 声明引用外部变量
void delay(unsigned int i);
void Tim_Setting(void);
void Delay_us(u32 nTime);


main()
{    unsigned char i; 	
	
	#ifdef DEBUG
//	debug();  //在线调试使用
	#endif
	
	RCC_Configuration();      //系统时钟配置函数 
	
	NVIC_Configuration();     //NVIC配置函数 
	
    SysTick_Configuration();   //Systick配置函数
	
	Tim_Setting();	  //调用事件设定函数
	
	//启动GPIO模块时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB1Periph_TIM2 | RCC_APB2Periph_AFIO, ENABLE);
	//把调试设置普通IO口
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);  
	                        
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All; //所有GPIO为同一类型端口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //输出的最大频率为50HZ
	GPIO_Init(GPIOA, &GPIO_InitStructure);   //初始化GPIOA端口
	GPIO_Init(GPIOB, &GPIO_InitStructure);   //初始化GPIOB端口

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; //将DS18B20设为16脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  //开漏输出	 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //输出的最大频率为50HZ
	GPIO_Init(GPIOA, &GPIO_InitStructure);   //初始化GPIOA端口

 
	
	GPIO_Write(GPIOA,0xffff);  //将GPIOA 16个端口全部置为高电平
	GPIO_Write(GPIOB,0xffff);  //将GPIOB 16个端口全部置为高电
   
    

    while(1)
   {	
	  GetTemp();

   	  /********以下将读18b20的数据送到LED数码管显示*************/
      LedNumVal=Temperature;      //把实际温度送到LedNumVal变量中

	  LedOut[0]=Disp_Tab[LedNumVal%10000/1000];
      LedOut[1]=Disp_Tab[LedNumVal%1000/100];
      LedOut[2]=Disp_Tab[LedNumVal%100/10];	 //十位
      LedOut[3]=Disp_Tab[LedNumVal%10];    //个位
  	  
    for(i=0; i<4; i++) 
	  {		
	GPIOA->BSRR = LedOut[i] & 0x00FF;   
    GPIOA->BRR = (~LedOut[i]) & 0x00FF;
	  			 	 	  	
		switch(i)					  
         {	    	  //138译码
			case 0:	  //0 0 0 
			GPIO_ResetBits(GPIOB, LS138A);
			GPIO_ResetBits(GPIOB, LS138B);
			GPIO_ResetBits(GPIOB, LS138C);
			break;         
            case 1:	 //1 0 0 
			GPIO_SetBits(GPIOB, LS138A);
			GPIO_ResetBits(GPIOB, LS138B);
			GPIO_ResetBits(GPIOB, LS138C);
			 break;             	
            case 2:	 //0 1 0
			GPIO_ResetBits(GPIOB, LS138A);
			GPIO_SetBits(GPIOB, LS138B);
			GPIO_ResetBits(GPIOB, LS138C);
			break; 
            case 3:	 //1 1 0
			GPIO_SetBits(GPIOB, LS138A);
			GPIO_SetBits(GPIOB, LS138B);
			GPIO_ResetBits(GPIOB, LS138C);
			break; 

         }
		 
		Delay_us(2);
	  }

    }
}

void Tim_Setting(void)
{
  	/*-----------------------------------------------------------------------------*/

  /***772M下定时值的计算（（1+预分频TIM_Prescaler）/72*(1+定时周期TIM_Period)）*/
 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //配置RCC，使能TIMx

  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 7199;  //时钟预分频数 例如:时钟频率=72/(时钟预分频+1)  
  
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; ////定时器模式 向上计数  

  TIM_TimeBaseStructure.TIM_Period = 9999;//自动重装载寄存器周期的值(定时时间)累计 0xFFFF个频率后产生个更新或者中断(也是说定时时间到)

  TIM_TimeBaseStructure.TIM_ClockDivision = 0; ////时间分割值  

  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //初始化定时器2

  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //打开中断 溢出中断  


  TIM_Cmd(TIM2, ENABLE);  //打开定时器

  /* Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1, ENABLE);


}

/******************************************************************************
*
*                         精准延时函数
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
*                        定时中断处理函数
*
*******************************************************************************/
void TIM2_IRQHandler(void)
{
  
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)  //检测制定的中断是否发生

  {

     TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //清除中断处理位。

     Count++ ;
	 

   }
}

/*******************************************************************************
*
*                         系统Systick 中断处理函数
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


void SysTick_Configuration(void)   
{   
  /*  设置AHB时钟为SysTick时钟*/  
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);  //采用8分频 
  
  /* 设置SysTicks中断抢占优先级 3， 从优先级0*/  
  NVIC_SystemHandlerPriorityConfig(SystemHandler_SysTick, 3, 0);   
      
  /* 每1ms发生一次SysTick中断 在72M的时钟下*/  
  SysTick_SetReload(9);     //该参数取值必须在1和0x00FFFFFF之间	 9/(72000 000/8)= 1us  1微秒计数    
  
  /* 开启SysTick中断 */  
  SysTick_ITConfig(ENABLE);   
}  


/*******************************************************************************
*                             NVIC配置函数
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

  
       /* 开启定时器2 */
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






