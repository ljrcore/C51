

/* Includes ------------------------------------------------------------------*/
#define SYS_GLOBALS
#include "include.h"
#include <absacc.h>
//#include "rtl.h"

  OS_TID LED1;                           
  OS_TID LED2; 

 //  /* Forward declaration of tasks.
__task void init (void) ;
__task void Led2 (void) ;    
  
                     
  

//(0x8000000+0x2000)是应用程序首地址
//必须声明是const
//const uint8  myFlashspace[32]  __at(0x8000000+0x2000+0x1000);



__task void Led2(void)
{

 uint32 i;
   
   
   while(1)
   {       
      
   for(i=0; i<5; i++)
   {
      PB8=0; PB9=0; PB10=0; PB11=0;
      os_dly_wait(100/OS_TIME);//100ms
      PB8=1; PB9=1; PB10=1; PB11=1;
      os_dly_wait(300/OS_TIME);//100ms
   }   
	  
	  
	  
	  
	  PB8=0;
      os_dly_wait(100/OS_TIME);//100ms
      PB8=1;
      os_dly_wait(100/OS_TIME);//100ms
      
      PB9=0;
      os_dly_wait(100/OS_TIME);//100ms
      PB9=1;
      os_dly_wait(100/OS_TIME);//100ms
      
      PB10=0;
      os_dly_wait(100/OS_TIME);//100ms
      PB10=1;
      os_dly_wait(100/OS_TIME);//100ms
      
      PB11=0;
      os_dly_wait(100/OS_TIME);//100ms
      PB11=1;
      os_dly_wait(100/OS_TIME);//100ms

	  os_evt_set(0x0004, LED1);

        //os_tsk_delete_self ();
}
} 



__task void init (void)
 {
 

  LED2 = os_tsk_create(Led2, 1);

  os_tsk_delete_self ();
}



/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{//uint8 i=0;
#ifdef DEBUG
  debug();
#endif
  
//ReStart:  
  /* System Clocks Configuration */
  RCC_Configuration();   

  GPIO_Configuration();
  
  /* NVIC configuration */
  NVIC_Configuration();

  //非RTOS调用该函数
  //SysTick_Init();
  
  os_sys_init (init);

}

