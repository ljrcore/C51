/*----------------------------------------------------------------------------
编译器版本：MDK3.5
注意：做CAN总线实验时，请将电压跳到5V
 *---------------------------------------------------------------------------*/

#include <RTL.h>                      /* RTX kernel functions & defines      */
#include <stm32f10x_lib.h>            /* STM32F10x Library Definitions       */
#include "STM32_Reg.h"                /* STM32 register and bit Definitions  */
#include "STM32_Init.h"               /* STM32 Initialization                */
#include "CAN_Hw.h"                   /* STM32 CAN HW adaption layer         */
#include "RTX_CAN.h"                  /* CAN Generic functions & defines     */ 


//-----------------------------------------------------------------------------------------------------
//别名区    ADDRESS=0x4200 0000 + (0x0001 100C*0x20) + (bitx*4)	;bitx:第x位
// 把“位带地址＋位序号”转换别名地址宏
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
//把该地址转换成一个指针
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))

#define BIT_ADDR(addr, bitnum)   MEM_ADDR( BITBAND(addr, bitnum)  )

#define GPIOA_ODR    (GPIOA_BASE+12) //0x4001080C
#define GPIOB_ODR    (GPIOB_BASE+12) //0x40010C0C
#define GPIOC_ODR    (GPIOC_BASE+12) //0x4001100C
#define GPIOD_ODR    (GPIOD_BASE+12) //0x4001140C
#define GPIOE_ODR    (GPIOE_BASE+12) //0x4001180C

#define GPIOA_IDR    (GPIOA_BASE+8) //0x4001080C
#define GPIOB_IDR    (GPIOB_BASE+8) //0x40010C0C
#define GPIOC_IDR    (GPIOC_BASE+8) //0x4001100C
#define GPIOD_IDR    (GPIOD_BASE+8) //0x4001140C
#define GPIOE_IDR    (GPIOE_BASE+8) //0x4001180C


//定义LED
#define PB5   BIT_ADDR(GPIOB_ODR, 5) //输出
#define PB6   BIT_ADDR(GPIOB_ODR, 6) //输出
#define PB7   BIT_ADDR(GPIOB_ODR, 7) //输出


__task void task_init(void);
__task void task_send_CAN(void);
__task void task_rece_CAN(void);

/*----------------------------------------------------------------------------
 *  Task 0: Initializes and starts other tasks
 *---------------------------------------------------------------------------*/

__task void task_init(void)
{
   os_tsk_create(task_send_CAN, 3);   /* Start          transmit task        */
   os_tsk_create(task_rece_CAN, 4);   /* Start           receive task        */
   os_tsk_delete_self();               /* End      initialization task        */
}

/*----------------------------------------------------------------------------
 *  Task 1: Sends message with input value in data[0] over CAN periodically
 *---------------------------------------------------------------------------*/

__task void task_send_CAN(void)
{U32 i, j;
	
   /* Initialize message  = { ID, {data[0] .. data[7]}, LEN, CHANNEL, FORMAT, TYPE } */
   CAN_msg msg_send =
   {
      33, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 4, 1,
      STANDARD_FORMAT, DATA_FRAME
   };

   CAN_init(1, 500000);               /* CAN controller 1 init, 500 kbit/s   */

   /* Transmit object does not have to be enabled                             */
   //CAN_rx_object(1, 0,  33, STANDARD_FORMAT);
   CAN_rx_object(1, 0, msg_send.id, msg_send.format);     /* Enable reception of     */
   /* message on controller 1, channel is */
   /* not used for STM32 (can be set to   */
   /* whatever value), with standard id 33*/

   /* The activation of test mode in line below is used for enabling 
      self-testing mode when CAN controller receives the message it sends so 
      program functionality can be tested without another CAN device          */
   /* COMMENT THE LINE BELOW TO ENABLE DEVICE TO PARTICIPATE IN CAN NETWORK   */
   //软件仿真使用环回模式
   //CAN_hw_testmode(1, CAN_BTR_SILM | CAN_BTR_LBKM); /* Loopback and           */
   
   //硬件仿真使用正常模式
   CAN_hw_testmode(1, 0); //正常模式
   /* Silent Mode (self-test)*/

   CAN_start(1);                      /* Start controller 1                  */
   os_dly_wait(10);                  

   for (; ;)
   {
      for(i=0; i<10; i++)
      {
         msg_send.data[0]=0;
         msg_send.data[1]=0;
         msg_send.data[2]=0;
         msg_send.data[3]=0;
         
         CAN_send(1, &msg_send, 0x0F00);  /* Send msg_send on controller 1       */
         os_dly_wait(10);
         
         msg_send.data[0]=1;
         msg_send.data[1]=1;
         msg_send.data[2]=1;
         msg_send.data[3]=1;
         
         CAN_send(1, &msg_send, 0x0F00);  /* Send msg_send on controller 1       */
         os_dly_wait(10);
      }
      
      msg_send.data[0]=0;
      msg_send.data[1]=0;
      msg_send.data[2]=0;
      msg_send.data[3]=0;
      CAN_send(1, &msg_send, 0x0F00);  /* Send msg_send on controller 1       */
      os_dly_wait(10);
      
      for(j=0; j<5; j++)
      {
         for(i=0; i<4; i++)
         {
            msg_send.data[0]=0;
            msg_send.data[1]=0;
            msg_send.data[2]=0;
            msg_send.data[3]=0;
            
            msg_send.data[i]=1;
            
            CAN_send(1, &msg_send, 0x0F00);  /* Send msg_send on controller 1       */
            os_dly_wait(10);
         }
      }
      
      for(j=0; j<5; j++)
      {
         for(i=0; i<4; i++)
         {
            msg_send.data[0]=0;
            msg_send.data[1]=0;
            msg_send.data[2]=0;
            msg_send.data[3]=0;
            
            msg_send.data[3-i]=1;
            
            CAN_send(1, &msg_send, 0x0F00);  /* Send msg_send on controller 1       */
            os_dly_wait(10);
         }
      }
   }
}

/*----------------------------------------------------------------------------
 *  Task 2: Received CAN message
 *---------------------------------------------------------------------------*/

__task void task_rece_CAN(void)
{
   CAN_msg msg_rece;
   U8  PB5CPL=0;

   for (; ;)
   {
      /* When message arrives store received value to global variable Rx_val   */
      if (CAN_receive(1, &msg_rece, 0x00FF) == CAN_OK)
      {
         if(msg_rece.data[0]==0) //PB6状态
            PB6=0;
         else
            PB6=1;
         
         if(msg_rece.data[1]==0) //PB7状态
            PB7=0;
         else
            PB7=1;
      }

	  //运行闪烁
	  PB5CPL=~PB5CPL;	  
	  if(PB5CPL) PB5=1;
	  else PB5=0;
   }
}



/*----------------------------------------------------------------------------
 *        Main: Initialize and start RTX Kernel
 *---------------------------------------------------------------------------*/

int main(void)
{
   /* Program execution starts here       */

   stm32_Init();                      /* STM32 setup                         */

   os_sys_init(task_init);            /* Initialize OS and start init task   */
}


/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
