#include "led.h"
/****************************************************************************
* Function Name  : LED_Init
* Description    : Configures the used GPIO of LED .
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = PIN_LED;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	/*��LEDʹ�õ�GPIO��ʱ��ʹ��*/
	RCC_APB2PeriphClockCmd(RCC_LED, ENABLE);

	/*��ʼ����Ӧ��GPIO*/
	GPIO_Init(GPIO_LED, &GPIO_InitStructure);	 //��ʼ��GPIO_LED

}
/****************************************************************************
* Function Name  : LED_Sets
* Description    : ����LED��״̬��������ֻ������8λ����STM32һ�ε�����16λ����
*���ȶ�ȡ��д�롣
* Input          : data 
* Output         : None
* Return         : None
****************************************************************************/

void LED_Sets(uint8_t data)
{
	uint16_t setValue;

	setValue = GPIO_ReadOutputData(GPIO_LED);
	setValue &= 0x00ff;//����ʹ�õ���16λ�еĸ�8λ					
	setValue |= (uint16_t)data << 8;

	GPIO_Write(GPIO_LED,setValue);
}
