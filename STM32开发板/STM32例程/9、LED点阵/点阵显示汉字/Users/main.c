#include"stm32f10x.h"
#include"include.h"


//点阵显示数组
uint8_t const tab0[] = {0x00, 0x01, 0x00, 0x02, 0x00, 0x04, 0x00, 0x08, 0x00, 0x10, 0x00, 0x20, 0x00, 0x40, 0x00, 0x80,
                             0x01, 0x00, 0x02, 0x00, 0x04, 0x00, 0x08, 0x00, 0x10, 0x00, 0x20, 0x00, 0x40, 0x00, 0x80, 0x00}; 
//--亲--//
uint8_t const tab1[] = {
64,0,128,8,254,31,16,2,32,1,255,63,64,0,64,0,
254,31,64,0,72,6,68,8,82,16,32,0,0,0,0,0};
//--爱--//
uint8_t const tab2[] = {
0,14,252,1,72,8,144,4,254,63,2,16,33,8,252,
31,32,0,224,7,80,2,136,1,68,2,58,28,0,0,0,0};
//--的--//
uint8_t const tab3[] = {
8,2,8,2,4,17,62,63,162,16,98,16,34,17,62,
18,34,18,34,16,34,16,34,16,62,10,34,4,0,0,0,0};
//--顾--//
uint8_t const tab4[] = {
0,16,190,63,2,2,186,31,170,16,170,20,170,20,186,20,
138,20,138,20,170,20,26,10,1,49,193,32,0,0,0,0};
//--客--//
uint8_t const tab5[] = {
64,0,128,0,254,31,34,16,241,11,40,2,68,1,192,1,32,
2,248,63,23,4,16,4,16,4,240,7,0,0,0,0};
//--欢--//
uint8_t const tab6[] = {
0,1,0,1,63,1,32,63,162,32,148,18,84,2,8,2,
8,2,20,5,36,5,162,8,65,16,32,32,0,0,0,0};
//--迎--//
uint8_t const tab7[] = {
2,1,196,16,36,62,32,18,32,18,39,18,36,18,164,18,
100,18,36,26,4,2,10,2,49,0,192,63,0,0,0,0};
//--使--//
uint8_t const tab8[] = {
16,2,16,18,232,63,8,2,204,31,74,18,73,18,200,31,
8,18,72,2,136,2,8,1,136,6,104,56,0,0,0,0};
//--用--//
uint8_t const tab9[] = {
0,8,252,31,132,8,132,8,252,15,132,8,132,8,132,8,
252,15,132,8,132,8,130,8,130,10,129,4,0,0,0,0};
//--开--//
uint8_t const tab10[] = {
0,8,254,31,16,2,16,2,16,2,16,18,255,63,16,2,
16,2,16,2,16,2,8,2,4,2,3,2,0,0,0,0};
//--发--//
uint8_t const tab11[] = {
32,2,36,4,36,4,34,16,254,63,32,0,224,15,80,8,
80,4,136,2,8,1,132,2,98,60,29,16,0,0,0,0};
//--板--//
uint8_t const tab12[] = {
4,8,4,30,196,1,95,0,196,15,68,8,78,9,86,9,
69,5,69,5,68,2,36,5,164,56,84,16,0,0,0,0};
//--∩_∩--//
uint8_t const tab13[] = {
0,0,0,0,60,240,102,156,67,130,0,0,0,0,0,0,
0,0,0,0,48,24,96,8,192,7,0,0,0,0,0,0};

void SetSysClockTo72(void);
void HC595_GPIO_Config(void);
void HC595SendData(  uint8_t BT3, uint8_t BT2,uint8_t BT1,uint8_t BT0);

/****************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/

int main(void)
{
	uint8_t k; 
	uint32_t i, ms;

	SetSysClockTo72();
	HC595_GPIO_Config();
	i = 0x5FF; //定义一个字显示的时间长度
	while(1)
	{
		//--显示"亲"--//
		for(ms = i; ms > 0; ms--)
		{
			for(k = 0; k < 16; k++)										
			{	 
				HC595SendData(~tab1[2*k +1],~tab1[2*k],tab0[2*k],tab0[2*k + 1]);
			} 		 
		}

		//--清屏--//
		HC595SendData(0xff,0xff,0,0);										  							    
		
		//--显示“爱”--//
		for(ms = i; ms > 0; ms--)
		{
			for(k = 0; k < 16; k++)											    
			{	 
				HC595SendData(~tab2[2*k +1],~tab2[2*k],tab0[2*k],tab0[2*k + 1]); 		 
			}
		}
		
		//--清屏--//
		HC595SendData(0xff,0xff,0,0);								      	
		
		//--显示“的”--//
		for(ms = i; ms > 0; ms--)
		{
			for(k = 0; k < 16; k++)												
			{	 
				HC595SendData(~tab3[2*k +1],~tab3[2*k],tab0[2*k],tab0[2*k + 1]); 		 
			}
		}
		
		//--清屏--//	
		HC595SendData(0xff,0xff,0,0); 	
		
		//--显示“顾”--//
		for(ms = i; ms > 0; ms--)
		{
			for(k = 0; k < 16; k++)						
			{	 
				HC595SendData(~tab4[2*k +1],~tab4[2*k],tab0[2*k],tab0[2*k + 1]); 		 
			}
		}
		
		//--清屏--//	
		HC595SendData(0xff,0xff,0,0);								      	  	
																			 
		//--显示“客”--//
		for(ms = i; ms > 0; ms--)
		{
			for(k = 0; k < 16; k++)												
			{	 
				HC595SendData(~tab5[2*k +1],~tab5[2*k],tab0[2*k],tab0[2*k + 1]); 		 
			}
		}
		
		//--清屏--//	
		HC595SendData(0xff,0xff,0,0);								      	 	
	
	    //--显示“欢”--//
		for(ms = i; ms > 0; ms--)
		{
			for(k = 0; k < 16; k++)												//欢
			{	 
				HC595SendData(~tab6[2*k +1],~tab6[2*k],tab0[2*k],tab0[2*k + 1]); 		 
			}
		}

		//--清屏--//	
		HC595SendData(0xff,0xff,0,0);					      	
	
	    //--显示“迎”--//
		for(ms = i; ms > 0; ms--)
		{
			for(k = 0; k < 16; k++)							
			{	 
				HC595SendData(~tab7[2*k +1],~tab7[2*k],tab0[2*k],tab0[2*k + 1]); 		 
			}
		}

		//--清屏--//	
		HC595SendData(0xff,0xff,0,0);					    
		
		//--显示“使”--//
		for(ms = i; ms > 0; ms--)
		{
			for(k = 0; k < 16; k++)							
			{	 
				HC595SendData(~tab8[2*k +1],~tab8[2*k],tab0[2*k],tab0[2*k + 1]); 		 
			}
		}

		//--清屏--//	
		HC595SendData(0xff,0xff,0,0);								
		
		//--显示“用”--//	
		for(ms = i; ms > 0; ms--)
		{
			for(k = 0; k < 16; k++)						
			{	 
				HC595SendData(~tab9[2*k +1],~tab9[2*k],tab0[2*k],tab0[2*k + 1]); 		 
			}
		}

		//--清屏--//	
		HC595SendData(0xff,0xff,0,0);
		//--显示“开”--//	
		for(ms = i; ms > 0; ms--)
		{
			for(k = 0; k < 16; k++)						
			{	 
				HC595SendData(~tab10[2*k +1],~tab10[2*k],tab0[2*k],tab0[2*k + 1]); 		 
			}
		}

		//--清屏--//	
		HC595SendData(0xff,0xff,0,0);
		//--显示“发”--//	
		for(ms = i; ms > 0; ms--)
		{
			for(k = 0; k < 16; k++)						
			{	 
				HC595SendData(~tab11[2*k +1],~tab11[2*k],tab0[2*k],tab0[2*k + 1]); 		 
			}
		}

		//--清屏--//	
		HC595SendData(0xff,0xff,0,0);
 
		//--显示"板"--//	
		for(ms = i; ms > 0; ms--)
		{
			for(k = 0; k < 16; k++)						
			{	 
				HC595SendData(~tab12[2*k +1],~tab12[2*k],tab0[2*k],tab0[2*k + 1]); 		 
			}
		}

		//--清屏--//	
		HC595SendData(0xff,0xff,0,0);

		//--显示"∩_∩"--//	
		for(ms = i; ms > 0; ms--)
		{
			for(k = 0; k < 16; k++)						
			{	 
				HC595SendData(~tab13[2*k +1],~tab13[2*k],tab0[2*k],tab0[2*k + 1]); 		 
			}
		}

		//--清屏--//	
		HC595SendData(0xff,0xff,0,0);										  							    
	}
}

/****************************************************************************
* Function Name  : SetSysClockTo72
* Description    : Sets System clock frequency to 72MHz and configure HCLK, PCLK2 
*                * and PCLK1 prescalers.
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/

void SetSysClockTo72(void)
{
  ErrorStatus HSEStartUpStatus;
  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/   
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if (HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);
 
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

#ifdef STM32F10X_CL
    /* Configure PLLs *********************************************************/
    /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */
    RCC_PREDIV2Config(RCC_PREDIV2_Div5);
    RCC_PLL2Config(RCC_PLL2Mul_8);

    /* Enable PLL2 */
    RCC_PLL2Cmd(ENABLE);

    /* Wait till PLL2 is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLL2RDY) == RESET)
    {}

    /* PLL configuration: PLLCLK = (PLL2 / 5) * 9 = 72 MHz */ 
    RCC_PREDIV1Config(RCC_PREDIV1_Source_PLL2, RCC_PREDIV1_Div5);
    RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);
#else
    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
#endif

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock configuration.
       User can add here some const to deal with this error */    

    /* Go to infinite loop */
    while (1)
    {
    }
  }
}

/*******************************************************************************
* 函 数 名         : HC595_GPIO_Config
* 函数功能		   : 初始化SPI使用的IO口
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void HC595_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	//--打开LED使用的GPIO的时钟使能--//
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	//--初始化相应的GPIO--//
	GPIO_Init(GPIOA, &GPIO_InitStructure);	 //初始化GPIO_LED
}

/*******************************************************************************
* 函 数 名         : HC595SendData
* 函数功能		   : 通过595发送四个字节的数据
* 输    入         : BT3：第四个595输出数值
*                  * BT2: 第三个595输出数值
*                  * BT1：第二个595输出数值
*                  * BT0：第一个595输出数值
* 输    出         : 无
*******************************************************************************/

void HC595SendData(  uint8_t BT3, uint8_t BT2,uint8_t BT1,uint8_t BT0)
{  
	uint8_t i;
	
	//--发送第一个字节--//
	for(i=0;i<8;i++)
	{
		if(BT3 >> 7)	 //从高位到低位
		{
			MOSI_SET;
		}
		else
		{
			MOSI_CLR;
		}
		BT3 <<= 1;

		S_CLK_CLR;
		S_CLK_SET;		
	}

	//--发送第一个字节--//
	for(i=0;i<8;i++)
	{
		if(BT2 >> 7)	 //从高位到低位
		{
			MOSI_SET;
		}
		else
		{
			MOSI_CLR;
		}
		BT2 <<= 1;

		S_CLK_CLR;

		S_CLK_SET;			
	}

	//--发送第一个字节--//
	for(i=0;i<8;i++)
	{		
		if(BT1 >> 7)	 //从高位到低位
		{
			MOSI_SET;
		}
		else
		{
			MOSI_CLR;
		}
		BT1 <<= 1;

		S_CLK_CLR;
		S_CLK_SET;		
	
	}

	//--发送第一个字节--//
	for(i=0;i<8;i++)
	{
		if(BT0 >> 7)	 //从高位到低位
		{
			MOSI_SET;
		}
		else
		{
			MOSI_CLR;
		}
		BT0 <<= 1;

		S_CLK_CLR;
		S_CLK_SET;		

	}
   
	//--输出--//
	R_CLK_CLR; //set dataline low
	R_CLK_SET; //片选
}
