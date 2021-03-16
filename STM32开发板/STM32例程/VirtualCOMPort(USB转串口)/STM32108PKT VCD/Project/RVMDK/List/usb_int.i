#line 1 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\src\\usb_int.c"













 

 
#line 1 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_lib.h"













 

 



 
#line 1 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"





















 



 



 
    


  


 
  


 


       
       











 






 
   





 




 





 

 

 

 






 



 



 




 
typedef enum IRQn
{
 
  NonMaskableInt_IRQn         = -14,     
  MemoryManagement_IRQn       = -12,     
  BusFault_IRQn               = -11,     
  UsageFault_IRQn             = -10,     
  SVCall_IRQn                 = -5,      
  DebugMonitor_IRQn           = -4,      
  PendSV_IRQn                 = -2,      
  SysTick_IRQn                = -1,      

 
  WWDG_IRQn                   = 0,       
  PVD_IRQn                    = 1,       
  TAMPER_IRQn                 = 2,       
  RTC_IRQn                    = 3,       
  FLASH_IRQn                  = 4,       
  RCC_IRQn                    = 5,       
  EXTI0_IRQn                  = 6,       
  EXTI1_IRQn                  = 7,       
  EXTI2_IRQn                  = 8,       
  EXTI3_IRQn                  = 9,       
  EXTI4_IRQn                  = 10,      
  DMA1_Channel1_IRQn          = 11,      
  DMA1_Channel2_IRQn          = 12,      
  DMA1_Channel3_IRQn          = 13,      
  DMA1_Channel4_IRQn          = 14,      
  DMA1_Channel5_IRQn          = 15,      
  DMA1_Channel6_IRQn          = 16,      
  DMA1_Channel7_IRQn          = 17,      
  ADC1_2_IRQn                 = 18,      
  USB_HP_CAN1_TX_IRQn         = 19,      
  USB_LP_CAN1_RX0_IRQn        = 20,      
  CAN1_RX1_IRQn               = 21,      
  CAN1_SCE_IRQn               = 22,      
  EXTI9_5_IRQn                = 23,      
  TIM1_BRK_IRQn               = 24,      
  TIM1_UP_IRQn                = 25,      
  TIM1_TRG_COM_IRQn           = 26,      
  TIM1_CC_IRQn                = 27,      
  TIM2_IRQn                   = 28,      
  TIM3_IRQn                   = 29,      

  TIM4_IRQn                   = 30,      

  I2C1_EV_IRQn                = 31,      
  I2C1_ER_IRQn                = 32,      

  I2C2_EV_IRQn                = 33,      
  I2C2_ER_IRQn                = 34,      

  SPI1_IRQn                   = 35,      
  SPI2_IRQn                   = 36,      
  USART1_IRQn                 = 37,      
  USART2_IRQn                 = 38,      

  USART3_IRQn                 = 39,      

  EXTI15_10_IRQn              = 40,      
  RTCAlarm_IRQn               = 41,      
  USBWakeUp_IRQn              = 42,      

  TIM8_BRK_IRQn               = 43,      
  TIM8_UP_IRQn                = 44,      
  TIM8_TRG_COM_IRQn           = 45,      
  TIM8_CC_IRQn                = 46,      
  ADC3_IRQn                   = 47,      
  FSMC_IRQn                   = 48,      
  SDIO_IRQn                   = 49,      
  TIM5_IRQn                   = 50,      
  SPI3_IRQn                   = 51,      
  UART4_IRQn                  = 52,      
  UART5_IRQn                  = 53,      
  TIM6_IRQn                   = 54,      
  TIM7_IRQn                   = 55,      
  DMA2_Channel1_IRQn          = 56,      
  DMA2_Channel2_IRQn          = 57,      
  DMA2_Channel3_IRQn          = 58,      
  DMA2_Channel4_5_IRQn        = 59       

} IRQn_Type;



 

#line 1 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\core_cm3.h"



















 




















































 

 
 
 
 
 
 
 
 


#line 1 "D:\\Program Files\\KeilARM350\\ARM\\RV31\\INC\\stdint.h"
 
 





 









#line 25 "D:\\Program Files\\KeilARM350\\ARM\\RV31\\INC\\stdint.h"







 

     

     
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;

     
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

     

     
     
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed           int int_least32_t;
typedef   signed       __int64 int_least64_t;

     
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned           int uint_least32_t;
typedef unsigned       __int64 uint_least64_t;

     

     
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;
typedef   signed       __int64 int_fast64_t;

     
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;
typedef unsigned       __int64 uint_fast64_t;

     
typedef   signed           int intptr_t;
typedef unsigned           int uintptr_t;

     
typedef   signed       __int64 intmax_t;
typedef unsigned       __int64 uintmax_t;




     

     





     





     





     

     





     





     





     

     





     





     





     

     


     


     


     

     


     


     


     

     



     



     


     
    
 



#line 196 "D:\\Program Files\\KeilARM350\\ARM\\RV31\\INC\\stdint.h"

     







     










     











#line 260 "D:\\Program Files\\KeilARM350\\ARM\\RV31\\INC\\stdint.h"



 


#line 86 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\core_cm3.h"

















 









 


 





 






 
typedef struct
{
  volatile uint32_t ISER[8];                       
       uint32_t RESERVED0[24];
  volatile uint32_t ICER[8];                       
       uint32_t RSERVED1[24];
  volatile uint32_t ISPR[8];                       
       uint32_t RESERVED2[24];
  volatile uint32_t ICPR[8];                       
       uint32_t RESERVED3[24];
  volatile uint32_t IABR[8];                       
       uint32_t RESERVED4[56];
  volatile uint8_t  IP[240];                       
       uint32_t RESERVED5[644];
  volatile  uint32_t STIR;                          
}  NVIC_Type;


 
typedef struct
{
  volatile const  uint32_t CPUID;                         
  volatile uint32_t ICSR;                          
  volatile uint32_t VTOR;                          
  volatile uint32_t AIRCR;                         
  volatile uint32_t SCR;                           
  volatile uint32_t CCR;                           
  volatile uint8_t  SHP[12];                       
  volatile uint32_t SHCSR;                         
  volatile uint32_t CFSR;                          
  volatile uint32_t HFSR;                          
  volatile uint32_t DFSR;                          
  volatile uint32_t MMFAR;                         
  volatile uint32_t BFAR;                          
  volatile uint32_t AFSR;                          
  volatile const  uint32_t PFR[2];                        
  volatile const  uint32_t DFR;                           
  volatile const  uint32_t ADR;                           
  volatile const  uint32_t MMFR[4];                       
  volatile const  uint32_t ISAR[5];                       
} SCB_Type;


 
typedef struct
{
  volatile uint32_t CTRL;                          
  volatile uint32_t LOAD;                          
  volatile uint32_t VAL;                           
  volatile const  uint32_t CALIB;                         
} SysTick_Type;


 
typedef struct
{
  volatile  union  
  {
    volatile  uint8_t    u8;                        
    volatile  uint16_t   u16;                       
    volatile  uint32_t   u32;                       
  }  PORT [32];                                
       uint32_t RESERVED0[864];
  volatile uint32_t TER;                           
       uint32_t RESERVED1[15];
  volatile uint32_t TPR;                           
       uint32_t RESERVED2[15];
  volatile uint32_t TCR;                           
       uint32_t RESERVED3[29];
  volatile uint32_t IWR;                           
  volatile uint32_t IRR;                           
  volatile uint32_t IMCR;                          
       uint32_t RESERVED4[43];
  volatile uint32_t LAR;                           
  volatile uint32_t LSR;                           
       uint32_t RESERVED5[6];
  volatile const  uint32_t PID4;                          
  volatile const  uint32_t PID5;
  volatile const  uint32_t PID6;
  volatile const  uint32_t PID7;
  volatile const  uint32_t PID0;
  volatile const  uint32_t PID1;
  volatile const  uint32_t PID2;
  volatile const  uint32_t PID3;
  volatile const  uint32_t CID0;
  volatile const  uint32_t CID1;
  volatile const  uint32_t CID2;
  volatile const  uint32_t CID3;
} ITM_Type;


 
typedef struct
{
       uint32_t RESERVED0;
  volatile const  uint32_t ICTR;                          



       uint32_t RESERVED1;

} InterruptType_Type;


 
#line 251 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\core_cm3.h"


 
typedef struct
{
  volatile uint32_t DHCSR;                         
  volatile  uint32_t DCRSR;                         
  volatile uint32_t DCRDR;                         
  volatile uint32_t DEMCR;                         
} CoreDebug_Type;


 
#line 270 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\core_cm3.h"

#line 277 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\core_cm3.h"










 






#line 304 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\core_cm3.h"


 


 




#line 329 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\core_cm3.h"


   
   
   
   









 
extern uint32_t __get_PSP(void);









 
extern void __set_PSP(uint32_t topOfProcStack);









 
extern uint32_t __get_MSP(void);









 
extern void __set_MSP(uint32_t topOfMainStack);








 
extern uint32_t __REV16(uint16_t value);








 
extern int32_t __REVSH(int16_t value);


#line 495 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\core_cm3.h"









 









 
static __inline uint32_t  __get_BASEPRI(void)
{
  register uint32_t __regBasePri         __asm("basepri");
  return(__regBasePri);
}








 
static __inline void __set_BASEPRI(uint32_t basePri)
{
  register uint32_t __regBasePri         __asm("basepri");
  __regBasePri = (basePri & 0x1ff);
}









 
static __inline uint32_t __get_PRIMASK(void)
{
  register uint32_t __regPriMask         __asm("primask");
  return(__regPriMask);
}








 
static __inline void __set_PRIMASK(uint32_t priMask)
{
  register uint32_t __regPriMask         __asm("primask");
  __regPriMask = (priMask);
}








 
static __inline uint32_t __get_FAULTMASK(void)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  return(__regFaultMask);
}








 
static __inline void __set_FAULTMASK(uint32_t faultMask)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  __regFaultMask = (faultMask & 1);
}








 
static __inline uint32_t __get_CONTROL(void)
{
  register uint32_t __regControl         __asm("control");
  return(__regControl);
}








 
static __inline void __set_CONTROL(uint32_t control)
{
  register uint32_t __regControl         __asm("control");
  __regControl = control;
}





#line 1024 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\core_cm3.h"



 










 
static __inline void NVIC_SetPriorityGrouping(uint32_t priority_grouping)
{
  uint32_t reg_value=0;
  
  reg_value  = ((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR;                                                                             
  reg_value &= ~((0xFFFFU << 16) | (0x0F << 8));                                                       
  reg_value  = ((reg_value | (0x5FA << 16) | (priority_grouping << 8)));                          
  ((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR = reg_value;
}









 
static __inline void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ISER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));                              
}









 
static __inline void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ICER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));                              
}










 
static __inline IRQn_Type NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  return((IRQn_Type) (((NVIC_Type *) ((0xE000E000) + 0x0100))->ISPR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F))));          
}









 
static __inline void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ISPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));                              
}









 
static __inline void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ICPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));                              
}










 
static __inline IRQn_Type NVIC_GetActive(IRQn_Type IRQn)
{
  return((IRQn_Type)(((NVIC_Type *) ((0xE000E000) + 0x0100))->IABR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F))));                         
}













 
static __inline void NVIC_SetPriority(IRQn_Type IRQn, int32_t priority)
{
  if(IRQn < 0) {
    ((SCB_Type *) ((0xE000E000) + 0x0D00))->SHP[((uint32_t)(IRQn) & 0xF)-4] = ((priority << (8 - 4)) & 0xff); }   
  else {
    ((NVIC_Type *) ((0xE000E000) + 0x0100))->IP[(uint32_t)(IRQn)] = ((priority << (8 - 4)) & 0xff);    }          
}















 
static __inline uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{

  if(IRQn < 0) {
    return((uint32_t)(((SCB_Type *) ((0xE000E000) + 0x0D00))->SHP[((uint32_t)(IRQn) & 0xF)-4] >> (8 - 4)));  }               
  else {
    return((uint32_t)(((NVIC_Type *) ((0xE000E000) + 0x0100))->IP[(uint32_t)(IRQn)]           >> (8 - 4)));  }               
}



 



 














 
static __inline uint32_t SysTick_Config(uint32_t ticks)
{ 
  if (ticks > ((1<<24) -1))  return (1);                                                 

  ((SysTick_Type *) ((0xE000E000) + 0x0010))->LOAD  =  (ticks & ((1<<24) -1)) - 1;                                          
  NVIC_SetPriority (SysTick_IRQn, (1<<4) - 1);                                
  ((SysTick_Type *) ((0xE000E000) + 0x0010))->VAL   =  (0x00);                                                                  
  ((SysTick_Type *) ((0xE000E000) + 0x0010))->CTRL = (1 << 2) | (1<<0) | (1<<1);     
  return (0);                                                                                
}







 








 
static __inline void NVIC_SystemReset(void)
{
  ((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR  = ((0x5FA << 16) | (((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR & (0x700)) | (1<<2));       
}


 











 
static __inline uint32_t ITM_SendChar (uint32_t ch)
{
  if(ch == '\n') ITM_SendChar('\r');
  
  if ((((CoreDebug_Type *) (0xE000EDF0))->DEMCR & (1 << 24))  &&
      (((ITM_Type *) (0xE0000000))->TCR & 1)                  &&
      (((ITM_Type *) (0xE0000000))->TER & (1UL << 0))  ) 
  {
    while (((ITM_Type *) (0xE0000000))->PORT[0].u32 == 0);
    ((ITM_Type *) (0xE0000000))->PORT[0].u8 = (uint8_t) ch;
  }  
  return (ch);
}



 
#line 197 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"
#line 1 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\system_stm32f10x.h"


















 



 





 



 




 

extern const uint32_t SystemFrequency;                    
extern const uint32_t SystemFrequency_SysClk;             
extern const uint32_t SystemFrequency_AHBClk;             
extern const uint32_t SystemFrequency_APB1Clk;            
extern const uint32_t SystemFrequency_APB2Clk;            



 



 



 



 



 



 
  
extern void SystemInit(void);


 



 
#line 198 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"
#line 199 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



   

 
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;   
typedef const int16_t sc16;   
typedef const int8_t sc8;    

typedef volatile int32_t  vs32;
typedef volatile int16_t  vs16;
typedef volatile int8_t   vs8;

typedef volatile const int32_t vsc32;   
typedef volatile const int16_t vsc16;   
typedef volatile const int8_t vsc8;    

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;   
typedef const uint16_t uc16;   
typedef const uint8_t uc8;    

typedef volatile uint32_t  vu32;
typedef volatile uint16_t vu16;
typedef volatile uint8_t  vu8;

typedef volatile const uint32_t vuc32;   
typedef volatile const uint16_t vuc16;   
typedef volatile const uint8_t vuc8;    

typedef enum {FALSE = 0, TRUE = !FALSE} bool;

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;


typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;



 



    



 

typedef struct
{
  volatile uint32_t SR;
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t SMPR1;
  volatile uint32_t SMPR2;
  volatile uint32_t JOFR1;
  volatile uint32_t JOFR2;
  volatile uint32_t JOFR3;
  volatile uint32_t JOFR4;
  volatile uint32_t HTR;
  volatile uint32_t LTR;
  volatile uint32_t SQR1;
  volatile uint32_t SQR2;
  volatile uint32_t SQR3;
  volatile uint32_t JSQR;
  volatile uint32_t JDR1;
  volatile uint32_t JDR2;
  volatile uint32_t JDR3;
  volatile uint32_t JDR4;
  volatile uint32_t DR;
} ADC_TypeDef;



 

typedef struct
{
  uint32_t  RESERVED0;
  volatile uint16_t DR1;
  uint16_t  RESERVED1;
  volatile uint16_t DR2;
  uint16_t  RESERVED2;
  volatile uint16_t DR3;
  uint16_t  RESERVED3;
  volatile uint16_t DR4;
  uint16_t  RESERVED4;
  volatile uint16_t DR5;
  uint16_t  RESERVED5;
  volatile uint16_t DR6;
  uint16_t  RESERVED6;
  volatile uint16_t DR7;
  uint16_t  RESERVED7;
  volatile uint16_t DR8;
  uint16_t  RESERVED8;
  volatile uint16_t DR9;
  uint16_t  RESERVED9;
  volatile uint16_t DR10;
  uint16_t  RESERVED10; 
  volatile uint16_t RTCCR;
  uint16_t  RESERVED11;
  volatile uint16_t CR;
  uint16_t  RESERVED12;
  volatile uint16_t CSR;
  uint16_t  RESERVED13[5];
  volatile uint16_t DR11;
  uint16_t  RESERVED14;
  volatile uint16_t DR12;
  uint16_t  RESERVED15;
  volatile uint16_t DR13;
  uint16_t  RESERVED16;
  volatile uint16_t DR14;
  uint16_t  RESERVED17;
  volatile uint16_t DR15;
  uint16_t  RESERVED18;
  volatile uint16_t DR16;
  uint16_t  RESERVED19;
  volatile uint16_t DR17;
  uint16_t  RESERVED20;
  volatile uint16_t DR18;
  uint16_t  RESERVED21;
  volatile uint16_t DR19;
  uint16_t  RESERVED22;
  volatile uint16_t DR20;
  uint16_t  RESERVED23;
  volatile uint16_t DR21;
  uint16_t  RESERVED24;
  volatile uint16_t DR22;
  uint16_t  RESERVED25;
  volatile uint16_t DR23;
  uint16_t  RESERVED26;
  volatile uint16_t DR24;
  uint16_t  RESERVED27;
  volatile uint16_t DR25;
  uint16_t  RESERVED28;
  volatile uint16_t DR26;
  uint16_t  RESERVED29;
  volatile uint16_t DR27;
  uint16_t  RESERVED30;
  volatile uint16_t DR28;
  uint16_t  RESERVED31;
  volatile uint16_t DR29;
  uint16_t  RESERVED32;
  volatile uint16_t DR30;
  uint16_t  RESERVED33; 
  volatile uint16_t DR31;
  uint16_t  RESERVED34;
  volatile uint16_t DR32;
  uint16_t  RESERVED35;
  volatile uint16_t DR33;
  uint16_t  RESERVED36;
  volatile uint16_t DR34;
  uint16_t  RESERVED37;
  volatile uint16_t DR35;
  uint16_t  RESERVED38;
  volatile uint16_t DR36;
  uint16_t  RESERVED39;
  volatile uint16_t DR37;
  uint16_t  RESERVED40;
  volatile uint16_t DR38;
  uint16_t  RESERVED41;
  volatile uint16_t DR39;
  uint16_t  RESERVED42;
  volatile uint16_t DR40;
  uint16_t  RESERVED43;
  volatile uint16_t DR41;
  uint16_t  RESERVED44;
  volatile uint16_t DR42;
  uint16_t  RESERVED45;    
} BKP_TypeDef;



 

typedef struct
{
  volatile uint32_t TIR;
  volatile uint32_t TDTR;
  volatile uint32_t TDLR;
  volatile uint32_t TDHR;
} CAN_TxMailBox_TypeDef;



 
  
typedef struct
{
  volatile uint32_t RIR;
  volatile uint32_t RDTR;
  volatile uint32_t RDLR;
  volatile uint32_t RDHR;
} CAN_FIFOMailBox_TypeDef;



 
  
typedef struct
{
  volatile uint32_t FR1;
  volatile uint32_t FR2;
} CAN_FilterRegister_TypeDef;



 
  
typedef struct
{
  volatile uint32_t MCR;
  volatile uint32_t MSR;
  volatile uint32_t TSR;
  volatile uint32_t RF0R;
  volatile uint32_t RF1R;
  volatile uint32_t IER;
  volatile uint32_t ESR;
  volatile uint32_t BTR;
  uint32_t  RESERVED0[88];
  CAN_TxMailBox_TypeDef sTxMailBox[3];
  CAN_FIFOMailBox_TypeDef sFIFOMailBox[2];
  uint32_t  RESERVED1[12];
  volatile uint32_t FMR;
  volatile uint32_t FM1R;
  uint32_t  RESERVED2;
  volatile uint32_t FS1R;
  uint32_t  RESERVED3;
  volatile uint32_t FFA1R;
  uint32_t  RESERVED4;
  volatile uint32_t FA1R;
  uint32_t  RESERVED5[8];
  CAN_FilterRegister_TypeDef sFilterRegister[14];
} CAN_TypeDef;



 

typedef struct
{
  volatile uint32_t DR;
  volatile uint8_t  IDR;
  uint8_t   RESERVED0;
  uint16_t  RESERVED1;
  volatile uint32_t CR;
} CRC_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t SWTRIGR;
  volatile uint32_t DHR12R1;
  volatile uint32_t DHR12L1;
  volatile uint32_t DHR8R1;
  volatile uint32_t DHR12R2;
  volatile uint32_t DHR12L2;
  volatile uint32_t DHR8R2;
  volatile uint32_t DHR12RD;
  volatile uint32_t DHR12LD;
  volatile uint32_t DHR8RD;
  volatile uint32_t DOR1;
  volatile uint32_t DOR2;
} DAC_TypeDef;



 

typedef struct
{
  volatile uint32_t IDCODE;
  volatile uint32_t CR;	
}DBGMCU_TypeDef;



 

typedef struct
{
  volatile uint32_t CCR;
  volatile uint32_t CNDTR;
  volatile uint32_t CPAR;
  volatile uint32_t CMAR;
} DMA_Channel_TypeDef;

typedef struct
{
  volatile uint32_t ISR;
  volatile uint32_t IFCR;
} DMA_TypeDef;



 

typedef struct
{
  volatile uint32_t IMR;
  volatile uint32_t EMR;
  volatile uint32_t RTSR;
  volatile uint32_t FTSR;
  volatile uint32_t SWIER;
  volatile uint32_t PR;
} EXTI_TypeDef;



 

typedef struct
{
  volatile uint32_t ACR;
  volatile uint32_t KEYR;
  volatile uint32_t OPTKEYR;
  volatile uint32_t SR;
  volatile uint32_t CR;
  volatile uint32_t AR;
  volatile uint32_t RESERVED;
  volatile uint32_t OBR;
  volatile uint32_t WRPR;
} FLASH_TypeDef;



 
  
typedef struct
{
  volatile uint16_t RDP;
  volatile uint16_t USER;
  volatile uint16_t Data0;
  volatile uint16_t Data1;
  volatile uint16_t WRP0;
  volatile uint16_t WRP1;
  volatile uint16_t WRP2;
  volatile uint16_t WRP3;
} OB_TypeDef;



 

typedef struct
{
  volatile uint32_t BTCR[8];   
} FSMC_Bank1_TypeDef; 



 
  
typedef struct
{
  volatile uint32_t BWTR[7];
} FSMC_Bank1E_TypeDef;



 
  
typedef struct
{
  volatile uint32_t PCR2;
  volatile uint32_t SR2;
  volatile uint32_t PMEM2;
  volatile uint32_t PATT2;
  uint32_t  RESERVED0;   
  volatile uint32_t ECCR2; 
} FSMC_Bank2_TypeDef;  



 
  
typedef struct
{
  volatile uint32_t PCR3;
  volatile uint32_t SR3;
  volatile uint32_t PMEM3;
  volatile uint32_t PATT3;
  uint32_t  RESERVED0;   
  volatile uint32_t ECCR3; 
} FSMC_Bank3_TypeDef; 



 
  
typedef struct
{
  volatile uint32_t PCR4;
  volatile uint32_t SR4;
  volatile uint32_t PMEM4;
  volatile uint32_t PATT4;
  volatile uint32_t PIO4; 
} FSMC_Bank4_TypeDef; 



 

typedef struct
{
  volatile uint32_t CRL;
  volatile uint32_t CRH;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t BRR;
  volatile uint32_t LCKR;
} GPIO_TypeDef;



 

typedef struct
{
  volatile uint32_t EVCR;
  volatile uint32_t MAPR;
  volatile uint32_t EXTICR[4];
} AFIO_TypeDef;


 

typedef struct
{
  volatile uint16_t CR1;
  uint16_t  RESERVED0;
  volatile uint16_t CR2;
  uint16_t  RESERVED1;
  volatile uint16_t OAR1;
  uint16_t  RESERVED2;
  volatile uint16_t OAR2;
  uint16_t  RESERVED3;
  volatile uint16_t DR;
  uint16_t  RESERVED4;
  volatile uint16_t SR1;
  uint16_t  RESERVED5;
  volatile uint16_t SR2;
  uint16_t  RESERVED6;
  volatile uint16_t CCR;
  uint16_t  RESERVED7;
  volatile uint16_t TRISE;
  uint16_t  RESERVED8;
} I2C_TypeDef;



 

typedef struct
{
  volatile uint32_t KR;
  volatile uint32_t PR;
  volatile uint32_t RLR;
  volatile uint32_t SR;
} IWDG_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CSR;
} PWR_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CFGR;
  volatile uint32_t CIR;
  volatile uint32_t APB2RSTR;
  volatile uint32_t APB1RSTR;
  volatile uint32_t AHBENR;
  volatile uint32_t APB2ENR;
  volatile uint32_t APB1ENR;
  volatile uint32_t BDCR;
  volatile uint32_t CSR;
} RCC_TypeDef;



 

typedef struct
{
  volatile uint16_t CRH;
  uint16_t  RESERVED0;
  volatile uint16_t CRL;
  uint16_t  RESERVED1;
  volatile uint16_t PRLH;
  uint16_t  RESERVED2;
  volatile uint16_t PRLL;
  uint16_t  RESERVED3;
  volatile uint16_t DIVH;
  uint16_t  RESERVED4;
  volatile uint16_t DIVL;
  uint16_t  RESERVED5;
  volatile uint16_t CNTH;
  uint16_t  RESERVED6;
  volatile uint16_t CNTL;
  uint16_t  RESERVED7;
  volatile uint16_t ALRH;
  uint16_t  RESERVED8;
  volatile uint16_t ALRL;
  uint16_t  RESERVED9;
} RTC_TypeDef;



 

typedef struct
{
  volatile uint32_t POWER;
  volatile uint32_t CLKCR;
  volatile uint32_t ARG;
  volatile uint32_t CMD;
  volatile const uint32_t RESPCMD;
  volatile const uint32_t RESP1;
  volatile const uint32_t RESP2;
  volatile const uint32_t RESP3;
  volatile const uint32_t RESP4;
  volatile uint32_t DTIMER;
  volatile uint32_t DLEN;
  volatile uint32_t DCTRL;
  volatile const uint32_t DCOUNT;
  volatile const uint32_t STA;
  volatile uint32_t ICR;
  volatile uint32_t MASK;
  uint32_t  RESERVED0[2];
  volatile const uint32_t FIFOCNT;
  uint32_t  RESERVED1[13];
  volatile uint32_t FIFO;
} SDIO_TypeDef;



 

typedef struct
{
  volatile uint16_t CR1;
  uint16_t  RESERVED0;
  volatile uint16_t CR2;
  uint16_t  RESERVED1;
  volatile uint16_t SR;
  uint16_t  RESERVED2;
  volatile uint16_t DR;
  uint16_t  RESERVED3;
  volatile uint16_t CRCPR;
  uint16_t  RESERVED4;
  volatile uint16_t RXCRCR;
  uint16_t  RESERVED5;
  volatile uint16_t TXCRCR;
  uint16_t  RESERVED6;
  volatile uint16_t I2SCFGR;
  uint16_t  RESERVED7;
  volatile uint16_t I2SPR;
  uint16_t  RESERVED8;  
} SPI_TypeDef;



 

typedef struct
{
  volatile uint16_t CR1;
  uint16_t  RESERVED0;
  volatile uint16_t CR2;
  uint16_t  RESERVED1;
  volatile uint16_t SMCR;
  uint16_t  RESERVED2;
  volatile uint16_t DIER;
  uint16_t  RESERVED3;
  volatile uint16_t SR;
  uint16_t  RESERVED4;
  volatile uint16_t EGR;
  uint16_t  RESERVED5;
  volatile uint16_t CCMR1;
  uint16_t  RESERVED6;
  volatile uint16_t CCMR2;
  uint16_t  RESERVED7;
  volatile uint16_t CCER;
  uint16_t  RESERVED8;
  volatile uint16_t CNT;
  uint16_t  RESERVED9;
  volatile uint16_t PSC;
  uint16_t  RESERVED10;
  volatile uint16_t ARR;
  uint16_t  RESERVED11;
  volatile uint16_t RCR;
  uint16_t  RESERVED12;
  volatile uint16_t CCR1;
  uint16_t  RESERVED13;
  volatile uint16_t CCR2;
  uint16_t  RESERVED14;
  volatile uint16_t CCR3;
  uint16_t  RESERVED15;
  volatile uint16_t CCR4;
  uint16_t  RESERVED16;
  volatile uint16_t BDTR;
  uint16_t  RESERVED17;
  volatile uint16_t DCR;
  uint16_t  RESERVED18;
  volatile uint16_t DMAR;
  uint16_t  RESERVED19;
} TIM_TypeDef;



 
 
typedef struct
{
  volatile uint16_t SR;
  uint16_t  RESERVED0;
  volatile uint16_t DR;
  uint16_t  RESERVED1;
  volatile uint16_t BRR;
  uint16_t  RESERVED2;
  volatile uint16_t CR1;
  uint16_t  RESERVED3;
  volatile uint16_t CR2;
  uint16_t  RESERVED4;
  volatile uint16_t CR3;
  uint16_t  RESERVED5;
  volatile uint16_t GTPR;
  uint16_t  RESERVED6;
} USART_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CFR;
  volatile uint32_t SR;
} WWDG_TypeDef;



 
  


 









 




#line 909 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 926 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



#line 945 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"














 
  


   

#line 1027 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 



 
  
  

 
    
 
 
 

 
 
 
 
 

 



 



 


 
 
 
 
 

 











 
#line 1088 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"




 





 
 
 
 
 

 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 





 



 






 
 
 
 
 

 
#line 1264 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 




 








 










 
#line 1300 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"






 











 










 














 
#line 1360 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"








 






 
#line 1393 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 1410 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 1432 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 1441 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 1458 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 1480 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 








 








   
#line 1509 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
 
 
 
 

 




































































 




































































 
#line 1671 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 1689 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 1707 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 1724 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 1742 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 1761 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 

 






 
#line 1788 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"






 








 









 








 








 









 










 




#line 1863 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"






 





 





 
#line 1889 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 1898 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

   
#line 1907 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 1916 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 





 
#line 1931 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 1940 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

   
#line 1949 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 1958 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 





 
#line 1973 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 1982 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

   
#line 1991 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 2000 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 





 
#line 2015 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 2024 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

   
#line 2033 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 2042 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
 
 
 
 

 





 


 


 




 
 
 
 
 

 
#line 2106 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 2141 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 2176 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 2211 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 2246 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 





 





 





 





 





 





 





 





 






 
#line 2313 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 



 









 
#line 2337 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"




 




 
#line 2353 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 





 
#line 2375 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
 





 
#line 2390 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"
 
#line 2397 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 




 






 


 


 


 
 
 
 
 

 
#line 2445 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 2466 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 2487 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 2508 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 2529 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 2550 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
 
 
 
 

 
#line 2586 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 2616 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 2626 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"















 
#line 2650 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"















 
#line 2674 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"















 
#line 2698 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"















 
#line 2722 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"















 
#line 2746 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"















 
#line 2770 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"















 


 


 


 


 


 


 


 


 


 



 


 


 



 


 


 


 



 


 


 


 


 
 
 
 
 

 






 
#line 2871 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 2880 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"















  
 
#line 2903 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"


















 








































 


















































 


 


 


 


 


 


 
#line 3038 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 3045 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 3052 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 3059 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"







 
#line 3073 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 3080 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 3087 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 3094 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 3101 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 3108 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 3116 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 3123 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 3130 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 3137 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 3144 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 3151 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 3159 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 3166 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 3173 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 3180 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"





 


 


 


 


 



 
 
 
 
 

 









































 



 


 


 


 


 


 


 



 



 



 


 


 
 
 
 
 

 
















 









#line 3330 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 

























 
#line 3373 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 3387 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 3397 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 




























 





















 




























 





















 
#line 3515 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 


 


 


 


 


 


 


 


 
#line 3550 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"





#line 3561 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 3569 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 3576 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 


 
 
 
 
 

 




 
#line 3598 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 


 


 


 


 


 


 


 


 
 
 
 
 

 


 





 


 



 
 
 
 
 

 
#line 3660 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 
#line 3672 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"







 


 
 
 
 
 

 











#line 3709 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 











#line 3731 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 











#line 3753 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 











#line 3775 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 








































 








































 








































 








































 


































 


































 


































 


































 



























 



























 



























 
#line 4172 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 4181 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 4190 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 4201 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 4211 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 4221 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 4231 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 4242 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 4252 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 4262 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 4272 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 4283 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 4293 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 4303 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 4313 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 4324 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 4334 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 4344 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 4354 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 4365 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 4375 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 4385 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 4395 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 4406 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 4416 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 4426 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 4436 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 4447 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 4457 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 4467 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

#line 4477 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 


 


 
 
 
 
 

 




 












 


 






#line 4525 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 


 


 


 


 


 


 


 


 
















 


 
#line 4595 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 4610 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 4636 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 


 


 
 
 
 
 

 
 























 























 























 























 























 























 























 























 
 
#line 4857 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 4869 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 






 
#line 4886 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



     


 
 


 


 


 


 


 


 


 


 

 


 


 


 


 


 


 


 


 

 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 

 


 


 


 


 


 


 


 


 

 


#line 5030 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 


#line 5042 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 


#line 5054 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 


#line 5066 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 


#line 5078 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 


#line 5090 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 


#line 5102 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 


#line 5114 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 

 


#line 5128 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 


#line 5140 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 


#line 5152 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 


#line 5164 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 


#line 5176 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 


#line 5188 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 


#line 5200 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 


#line 5212 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 


#line 5224 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 


#line 5236 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 


#line 5248 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 


#line 5260 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 


#line 5272 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 


#line 5284 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 


#line 5296 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 


#line 5308 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 
 
 
 
 

 
 
#line 5328 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 5339 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 5357 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"











 





 





 
#line 5395 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 












 
#line 5416 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
 






 




 





 





 






 




 





 





 






   




 





 





 





 




 





 





 





 




 





 





 
 


 
#line 5556 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 5573 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 5590 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 5607 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 5641 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 5675 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 5709 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 5743 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 5777 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 5811 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 5845 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 5879 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 5913 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 5947 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 5981 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 6015 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 6049 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 6083 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 6117 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 6151 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 6185 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 6219 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 6253 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 6287 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 6321 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 6355 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 6389 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 6423 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 6457 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 6491 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 6525 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 6559 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
 
 
 
 

 









#line 6586 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 6594 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 6604 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 


 


 


 


 





















 




 
 
 
 
 

 
#line 6665 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 6674 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"







 



#line 6695 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 



 


 
#line 6720 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 6730 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 




 


 
 
 
 
 

 
#line 6756 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 


 



 
#line 6779 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 6788 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"







 
#line 6807 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
#line 6818 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"



 
 
 
 
 

 


#line 6847 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 









#line 6871 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 
 
 
 
 

 









 


 


 





 
#line 6911 "..\\..\\..\\Libraries\\CMSIS\\Core\\CM3\\stm32f10x.h"

 


 









 


 

 



 



 



 



 



 



 



 





 

 

  







 

















 





 

  

 

 
#line 22 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_lib.h"
#line 1 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_type.h"













 

 



 
#line 1 "..\\inc\\usb_conf.h"













 

 



 
 
 
 



 
 
 
 
 


 
 



 
 





 
 
 
 
 
 


 
 
 
 
 
 
 
 

 
 
 
#line 72 "..\\inc\\usb_conf.h"



 







 
#line 22 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_type.h"

 
 




#line 68 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_type.h"
 
 
 



 
#line 23 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_lib.h"
#line 1 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_regs.h"













 

 



 
 
typedef enum _EP_DBUF_DIR
{
   
  EP_DBUF_ERR,
  EP_DBUF_OUT,
  EP_DBUF_IN
}EP_DBUF_DIR;

 
enum EP_BUF_NUM
{
  EP_NOBUF,
  EP_BUF0,
  EP_BUF1
};

 



 
 
 

 

 

 

 

 

 
 
 


 
#line 70 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_regs.h"
 
 
 
#line 81 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_regs.h"





#line 94 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_regs.h"

 
 
 
#line 106 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_regs.h"








 
 
 





 
 
 


 
 
 
 
#line 141 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_regs.h"

 


 
#line 152 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_regs.h"


 


 
#line 165 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_regs.h"

 
#line 174 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_regs.h"
 
 


 


 


 


 


 


 


 


 


 



 









 









 









 
#line 248 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_regs.h"








 
#line 269 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_regs.h"







 










 










 











 











 









 









 











 











 











 









 














 









 










 
#line 431 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_regs.h"

#line 438 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_regs.h"




















 











 










 











 











 












 
#line 527 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_regs.h"

#line 536 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_regs.h"












 




 
extern volatile uint16_t wIstr;   

 
void SetCNTR(uint16_t  );
void SetISTR(uint16_t  );
void SetDADDR(uint16_t  );
void SetBTABLE(uint16_t  );
void SetBTABLE(uint16_t  );
uint16_t GetCNTR(void);
uint16_t GetISTR(void);
uint16_t GetFNR(void);
uint16_t GetDADDR(void);
uint16_t GetBTABLE(void);
void SetENDPOINT(uint8_t  , uint16_t  );
uint16_t GetENDPOINT(uint8_t  );
void SetEPType(uint8_t  , uint16_t  );
uint16_t GetEPType(uint8_t  );
void SetEPTxStatus(uint8_t  , uint16_t  );
void SetEPRxStatus(uint8_t  , uint16_t  );
void SetDouBleBuffEPStall(uint8_t  , uint8_t bDir);
uint16_t GetEPTxStatus(uint8_t  );
uint16_t GetEPRxStatus(uint8_t  );
void SetEPTxValid(uint8_t  );
void SetEPRxValid(uint8_t  );
uint16_t GetTxStallStatus(uint8_t  );
uint16_t GetRxStallStatus(uint8_t  );
void SetEP_KIND(uint8_t  );
void ClearEP_KIND(uint8_t  );
void Set_Status_Out(uint8_t  );
void Clear_Status_Out(uint8_t  );
void SetEPDoubleBuff(uint8_t  );
void ClearEPDoubleBuff(uint8_t  );
void ClearEP_CTR_RX(uint8_t  );
void ClearEP_CTR_TX(uint8_t  );
void ToggleDTOG_RX(uint8_t  );
void ToggleDTOG_TX(uint8_t  );
void ClearDTOG_RX(uint8_t  );
void ClearDTOG_TX(uint8_t  );
void SetEPAddress(uint8_t  , uint8_t  );
uint8_t GetEPAddress(uint8_t  );
void SetEPTxAddr(uint8_t  , uint16_t  );
void SetEPRxAddr(uint8_t  , uint16_t  );
uint16_t GetEPTxAddr(uint8_t  );
uint16_t GetEPRxAddr(uint8_t  );
void SetEPCountRxReg(uint32_t *  , uint16_t  );
void SetEPTxCount(uint8_t  , uint16_t  );
void SetEPRxCount(uint8_t  , uint16_t  );
uint16_t GetEPTxCount(uint8_t  );
uint16_t GetEPRxCount(uint8_t  );
void SetEPDblBuf0Addr(uint8_t  , uint16_t  );
void SetEPDblBuf1Addr(uint8_t  , uint16_t  );
void SetEPDblBuffAddr(uint8_t  , uint16_t  , uint16_t  );
uint16_t GetEPDblBuf0Addr(uint8_t  );
uint16_t GetEPDblBuf1Addr(uint8_t  );
void SetEPDblBuffCount(uint8_t  , uint8_t  , uint16_t  );
void SetEPDblBuf0Count(uint8_t  , uint8_t  , uint16_t  );
void SetEPDblBuf1Count(uint8_t  , uint8_t  , uint16_t  );
uint16_t GetEPDblBuf0Count(uint8_t  );
uint16_t GetEPDblBuf1Count(uint8_t  );
EP_DBUF_DIR GetEPDblBufDir(uint8_t  );
void FreeUserBuffer(uint8_t bEpNum , uint8_t bDir);
uint16_t ToWord(uint8_t, uint8_t);
uint16_t ByteSwap(uint16_t);



 
#line 24 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_lib.h"
#line 1 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_def.h"













 

 



 
 
typedef enum _RECIPIENT_TYPE
{
  DEVICE_RECIPIENT,      
  INTERFACE_RECIPIENT,   
  ENDPOINT_RECIPIENT,    
  OTHER_RECIPIENT
} RECIPIENT_TYPE;


typedef enum _STANDARD_REQUESTS
{
  GET_STATUS = 0,
  CLEAR_FEATURE,
  RESERVED1,
  SET_FEATURE,
  RESERVED2,
  SET_ADDRESS,
  GET_DESCRIPTOR,
  SET_DESCRIPTOR,
  GET_CONFIGURATION,
  SET_CONFIGURATION,
  GET_INTERFACE,
  SET_INTERFACE,
  TOTAL_sREQUEST,   
  SYNCH_FRAME = 12
} STANDARD_REQUESTS;

 
typedef enum _DESCRIPTOR_TYPE
{
  DEVICE_DESCRIPTOR = 1,
  CONFIG_DESCRIPTOR,
  STRING_DESCRIPTOR,
  INTERFACE_DESCRIPTOR,
  ENDPOINT_DESCRIPTOR
} DESCRIPTOR_TYPE;

 
typedef enum _FEATURE_SELECTOR
{
  ENDPOINT_STALL,
  DEVICE_REMOTE_WAKEUP
} FEATURE_SELECTOR;

 
 







 
 



 
#line 25 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_lib.h"
#line 1 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_core.h"













 

 



 
 
typedef enum _CONTROL_STATE
{
  WAIT_SETUP,        
  SETTING_UP,        
  IN_DATA,           
  OUT_DATA,          
  LAST_IN_DATA,      
  LAST_OUT_DATA,     
  WAIT_STATUS_IN,    
  WAIT_STATUS_OUT,   
  STALLED,           
  PAUSE              
} CONTROL_STATE;     

typedef struct OneDescriptor
{
  uint8_t *Descriptor;
  uint16_t Descriptor_Size;
}
ONE_DESCRIPTOR, *PONE_DESCRIPTOR;


 
typedef enum _RESULT
{
  USB_SUCCESS = 0,     
  USB_ERROR,
  USB_UNSUPPORT,
  USB_NOT_READY       
 
} RESULT;


 
typedef struct _ENDPOINT_INFO
{
  




















 
  uint16_t  Usb_wLength;
  uint16_t  Usb_wOffset;
  uint16_t  PacketSize;
  uint8_t   *(*CopyData)(uint16_t Length);
}ENDPOINT_INFO;

 

typedef struct _DEVICE
{
  uint8_t Total_Endpoint;      
  uint8_t Total_Configuration; 
}
DEVICE;

typedef union
{
  uint16_t w;
  struct BW
  {
    uint8_t bb1;
    uint8_t bb0;
  }
  bw;
} uint16_t_uint8_t;

typedef struct _DEVICE_INFO
{
  uint8_t USBbmRequestType;        
  uint8_t USBbRequest;             
  uint16_t_uint8_t USBwValues;          
  uint16_t_uint8_t USBwIndexs;          
  uint16_t_uint8_t USBwLengths;         

  uint8_t ControlState;            
  uint8_t Current_Feature;
  uint8_t Current_Configuration;    
  uint8_t Current_Interface;        
  uint8_t Current_AlternateSetting;
 

  ENDPOINT_INFO Ctrl_Info;
}DEVICE_INFO;

typedef struct _DEVICE_PROP
{
  void (*Init)(void);         
  void (*Reset)(void);        

   
  void (*Process_Status_IN)(void);
  void (*Process_Status_OUT)(void);

   
  













 
  RESULT (*Class_Data_Setup)(uint8_t RequestNo);

   
  






 
  RESULT (*Class_NoData_Setup)(uint8_t RequestNo);

  





 

  RESULT  (*Class_Get_Interface_Setting)(uint8_t Interface, uint8_t AlternateSetting);

  uint8_t* (*GetDeviceDescriptor)(uint16_t Length);
  uint8_t* (*GetConfigDescriptor)(uint16_t Length);
  uint8_t* (*GetStringDescriptor)(uint16_t Length);

  uint8_t* RxEP_buffer;
  uint8_t MaxPacketSize;

}DEVICE_PROP;

typedef struct _USER_STANDARD_REQUESTS
{
  void (*User_GetConfiguration)(void);        
  void (*User_SetConfiguration)(void);        
  void (*User_GetInterface)(void);            
  void (*User_SetInterface)(void);            
  void (*User_GetStatus)(void);               
  void (*User_ClearFeature)(void);            
  void (*User_SetEndPointFeature)(void);      
  void (*User_SetDeviceFeature)(void);        
  void (*User_SetDeviceAddress)(void);        
}
USER_STANDARD_REQUESTS;

 





#line 210 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_core.h"

 
 
uint8_t Setup0_Process(void);
uint8_t Post0_Process(void);
uint8_t Out0_Process(void);
uint8_t In0_Process(void);

RESULT Standard_SetEndPointFeature(void);
RESULT Standard_SetDeviceFeature(void);

uint8_t *Standard_GetConfiguration(uint16_t Length);
RESULT Standard_SetConfiguration(void);
uint8_t *Standard_GetInterface(uint16_t Length);
RESULT Standard_SetInterface(void);
uint8_t *Standard_GetDescriptorData(uint16_t Length, PONE_DESCRIPTOR pDesc);

uint8_t *Standard_GetStatus(uint16_t Length);
RESULT Standard_ClearFeature(void);
void SetDeviceAddress(uint8_t);
void NOP_Process(void);

extern DEVICE_PROP Device_Property;
extern  USER_STANDARD_REQUESTS User_Standard_Requests;
extern  DEVICE  Device_Table;
extern DEVICE_INFO Device_Info;

 
extern uint16_t SaveRState;
extern uint16_t SaveTState;



 
#line 26 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_lib.h"
#line 1 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_init.h"













 

 



 
 
 
 
 
void USB_Init(void);

 
 
extern uint8_t	EPindex;
 
 
 
 
extern DEVICE_INFO*	pInformation;
 
 
extern DEVICE_PROP*	pProperty;
 
 
 
 
extern USER_STANDARD_REQUESTS *pUser_Standard_Requests;

extern uint16_t	SaveState ;
extern uint16_t wInterrupt_Mask;



 
#line 27 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_lib.h"
#line 1 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_mem.h"













 

 



 
 
 
 
 
void UserToPMABufferCopy(uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes);
void PMAToUserBufferCopy(uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes);

 



 
#line 28 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_lib.h"
#line 1 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_int.h"














 

 



 
 
 
 
 
void CTR_LP(void);
void CTR_HP(void);

 



 
#line 29 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\inc\\usb_lib.h"

 
 
 
 
 



 
#line 18 "..\\..\\..\\Libraries\\STM32_USB-FS-Device_Driver\\src\\usb_int.c"

 
 
 
 
uint16_t SaveRState;
uint16_t SaveTState;

 
extern void (*pEpInt_IN[7])(void);     
extern void (*pEpInt_OUT[7])(void);    

 
 








 
void CTR_LP(void)
{
  uint32_t wEPVal = 0;
   
  while (((wIstr = ((uint16_t) *((volatile unsigned *)((0x40005C00L) + 0x44)))) & (0x8000)) != 0)
  {
    (*((volatile unsigned *)((0x40005C00L) + 0x44)) = (uint16_t)(uint16_t)(~(0x8000)));  
     
    EPindex = (uint8_t)(wIstr & (0x000F));
    if (EPindex == 0)
    {
       
       
       

       
       
      SaveRState = ((uint16_t)((uint16_t)(*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0)))) & (0x3000));
      SaveTState = ((uint16_t)((uint16_t)(*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0)))) & (0x0030));
      { register uint16_t _wRegVal; _wRegVal = ((uint16_t)(*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0)))) & ((0x3000)|((0x8000)|(0x0800)|(0x0600)|(0x0100)|(0x0080)|(0x000F))); if(((0x1000) & (0x2000))!= 0) _wRegVal ^= (0x1000); if(((0x2000) & (0x2000))!= 0) _wRegVal ^= (0x2000); (*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0))= (uint16_t)_wRegVal); };
      { register uint16_t _wRegVal; _wRegVal = ((uint16_t)(*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0)))) & ((0x0030)|((0x8000)|(0x0800)|(0x0600)|(0x0100)|(0x0080)|(0x000F))); if(((0x0010) & (0x0020))!= 0) _wRegVal ^= (0x0010); if(((0x0020) & (0x0020))!= 0) _wRegVal ^= (0x0020); (*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0))= (uint16_t)_wRegVal); };


       

      if ((wIstr & (0x0010)) == 0)
      {
         

         
         


        ((*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0))= (uint16_t)((uint16_t)(*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0)))) & 0xFF7F & ((0x8000)|(0x0800)|(0x0600)|(0x0100)|(0x0080)|(0x000F))));
        In0_Process();

            
          { register uint16_t _wRegVal; _wRegVal = ((uint16_t)(*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0)))) & ((0x3000)|((0x8000)|(0x0800)|(0x0600)|(0x0100)|(0x0080)|(0x000F))); if(((0x1000) & SaveRState)!= 0) _wRegVal ^= (0x1000); if(((0x2000) & SaveRState)!= 0) _wRegVal ^= (0x2000); (*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0))= (uint16_t)_wRegVal); };
          { register uint16_t _wRegVal; _wRegVal = ((uint16_t)(*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0)))) & ((0x0030)|((0x8000)|(0x0800)|(0x0600)|(0x0100)|(0x0080)|(0x000F))); if(((0x0010) & SaveTState)!= 0) _wRegVal ^= (0x0010); if(((0x0020) & SaveTState)!= 0) _wRegVal ^= (0x0020); (*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0))= (uint16_t)_wRegVal); };
          return;
      }
      else
      {
         

         
         

        wEPVal = ((uint16_t)(*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0))));
        if ((wEPVal & (0x0080)) != 0)
        {
          ((*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0))= (uint16_t)((uint16_t)(*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0)))) & 0xFF7F & ((0x8000)|(0x0800)|(0x0600)|(0x0100)|(0x0080)|(0x000F))));
          In0_Process();
           
          { register uint16_t _wRegVal; _wRegVal = ((uint16_t)(*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0)))) & ((0x3000)|((0x8000)|(0x0800)|(0x0600)|(0x0100)|(0x0080)|(0x000F))); if(((0x1000) & SaveRState)!= 0) _wRegVal ^= (0x1000); if(((0x2000) & SaveRState)!= 0) _wRegVal ^= (0x2000); (*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0))= (uint16_t)_wRegVal); };
          { register uint16_t _wRegVal; _wRegVal = ((uint16_t)(*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0)))) & ((0x0030)|((0x8000)|(0x0800)|(0x0600)|(0x0100)|(0x0080)|(0x000F))); if(((0x0010) & SaveTState)!= 0) _wRegVal ^= (0x0010); if(((0x0020) & SaveTState)!= 0) _wRegVal ^= (0x0020); (*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0))= (uint16_t)_wRegVal); };
          return;
        }
        else if ((wEPVal &(0x0800)) != 0)
        {
          ((*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0))= (uint16_t)((uint16_t)(*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0)))) & 0x7FFF & ((0x8000)|(0x0800)|(0x0600)|(0x0100)|(0x0080)|(0x000F))));  
          Setup0_Process();
           
          { register uint16_t _wRegVal; _wRegVal = ((uint16_t)(*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0)))) & ((0x3000)|((0x8000)|(0x0800)|(0x0600)|(0x0100)|(0x0080)|(0x000F))); if(((0x1000) & SaveRState)!= 0) _wRegVal ^= (0x1000); if(((0x2000) & SaveRState)!= 0) _wRegVal ^= (0x2000); (*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0))= (uint16_t)_wRegVal); };
          { register uint16_t _wRegVal; _wRegVal = ((uint16_t)(*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0)))) & ((0x0030)|((0x8000)|(0x0800)|(0x0600)|(0x0100)|(0x0080)|(0x000F))); if(((0x0010) & SaveTState)!= 0) _wRegVal ^= (0x0010); if(((0x0020) & SaveTState)!= 0) _wRegVal ^= (0x0020); (*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0))= (uint16_t)_wRegVal); };
          return;
        }

        else if ((wEPVal & (0x8000)) != 0)
        {
          ((*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0))= (uint16_t)((uint16_t)(*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0)))) & 0x7FFF & ((0x8000)|(0x0800)|(0x0600)|(0x0100)|(0x0080)|(0x000F))));
          Out0_Process();
           
          { register uint16_t _wRegVal; _wRegVal = ((uint16_t)(*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0)))) & ((0x3000)|((0x8000)|(0x0800)|(0x0600)|(0x0100)|(0x0080)|(0x000F))); if(((0x1000) & SaveRState)!= 0) _wRegVal ^= (0x1000); if(((0x2000) & SaveRState)!= 0) _wRegVal ^= (0x2000); (*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0))= (uint16_t)_wRegVal); };
          { register uint16_t _wRegVal; _wRegVal = ((uint16_t)(*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0)))) & ((0x0030)|((0x8000)|(0x0800)|(0x0600)|(0x0100)|(0x0080)|(0x000F))); if(((0x0010) & SaveTState)!= 0) _wRegVal ^= (0x0010); if(((0x0020) & SaveTState)!= 0) _wRegVal ^= (0x0020); (*(((volatile unsigned *)((0x40005C00L))) + ((uint8_t)0))= (uint16_t)_wRegVal); };
          return;
        }
      }
    } 
    else
    {
       

       
      wEPVal = ((uint16_t)(*(((volatile unsigned *)((0x40005C00L))) + EPindex)));
      if ((wEPVal & (0x8000)) != 0)
      {
         
        ((*(((volatile unsigned *)((0x40005C00L))) + EPindex)= (uint16_t)((uint16_t)(*(((volatile unsigned *)((0x40005C00L))) + EPindex))) & 0x7FFF & ((0x8000)|(0x0800)|(0x0600)|(0x0100)|(0x0080)|(0x000F))));

         
        (*pEpInt_OUT[EPindex-1])();

      }  

      if ((wEPVal & (0x0080)) != 0)
      {
         
        ((*(((volatile unsigned *)((0x40005C00L))) + EPindex)= (uint16_t)((uint16_t)(*(((volatile unsigned *)((0x40005C00L))) + EPindex))) & 0xFF7F & ((0x8000)|(0x0800)|(0x0600)|(0x0100)|(0x0080)|(0x000F))));

         
        (*pEpInt_IN[EPindex-1])();
      }  

    } 

  } 
}








 
void CTR_HP(void)
{
  uint32_t wEPVal = 0;

  while (((wIstr = ((uint16_t) *((volatile unsigned *)((0x40005C00L) + 0x44)))) & (0x8000)) != 0)
  {
    (*((volatile unsigned *)((0x40005C00L) + 0x44)) = (uint16_t)(uint16_t)(~(0x8000)));  
     
    EPindex = (uint8_t)(wIstr & (0x000F));
     
    wEPVal = ((uint16_t)(*(((volatile unsigned *)((0x40005C00L))) + EPindex)));
    if ((wEPVal & (0x8000)) != 0)
    {
       
      ((*(((volatile unsigned *)((0x40005C00L))) + EPindex)= (uint16_t)((uint16_t)(*(((volatile unsigned *)((0x40005C00L))) + EPindex))) & 0x7FFF & ((0x8000)|(0x0800)|(0x0600)|(0x0100)|(0x0080)|(0x000F))));

       
      (*pEpInt_OUT[EPindex-1])();

    }  
    else if ((wEPVal & (0x0080)) != 0)
    {
       
      ((*(((volatile unsigned *)((0x40005C00L))) + EPindex)= (uint16_t)((uint16_t)(*(((volatile unsigned *)((0x40005C00L))) + EPindex))) & 0xFF7F & ((0x8000)|(0x0800)|(0x0600)|(0x0100)|(0x0080)|(0x000F))));

       
      (*pEpInt_IN[EPindex-1])();


    }  

  } 
}

 
