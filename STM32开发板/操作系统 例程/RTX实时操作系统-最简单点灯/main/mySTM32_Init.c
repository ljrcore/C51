#include <stm32f10x_lib.h>                        // STM32F10x Library Definitions
#include "STM32_Reg.h"

//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------

//=========================================================================== Clock Configuration
// <e0> Clock Configuration
//   <h> Clock Control Register Configuration (RCC_CR)
//     <e1.24> PLLON: PLL enable         
//       <i> Default: PLL Disabled
//       <o2.18..21> PLLMUL: PLL Multiplication Factor
//         <i> Default: PLLSRC * 2
//                       <0=> PLLSRC * 2
//                       <1=> PLLSRC * 3
//                       <2=> PLLSRC * 4
//                       <3=> PLLSRC * 5
//                       <4=> PLLSRC * 6
//                       <5=> PLLSRC * 7
//                       <6=> PLLSRC * 8
//                       <7=> PLLSRC * 9
//                       <8=> PLLSRC * 10
//                       <9=> PLLSRC * 11
//                       <10=> PLLSRC * 12
//                       <11=> PLLSRC * 13
//                       <12=> PLLSRC * 14
//                       <13=> PLLSRC * 15
//                       <14=> PLLSRC * 16
//       <o2.17> PLLXTPRE: HSE divider for PLL entry
//         <i> Default: HSE
//                       <0=> HSE
//                       <1=> HSE / 2
//       <o2.16> PLLSRC: PLL entry clock source         
//         <i> Default: HSI/2
//                       <0=> HSI / 2
//                       <1=> HSE (PLLXTPRE output)
//     </e>
//     <o1.19> CSSON: Clock Security System enable
//       <i> Default: Clock detector OFF
//     <o1.18> HSEBYP: External High Speed clock Bypass
//       <i> Default: HSE oscillator not bypassed
//     <o1.16> HSEON: External High Speed clock enable 
//       <i> Default: HSE oscillator OFF
//     <o1.3..7> HSITRIM: Internal High Speed clock trimming  <0-31>
//       <i> Default: 0
//     <o1.0> HSION: Internal High Speed clock enable
//       <i> Default: internal 8MHz RC oscillator OFF
//   </h>
//   <h> Clock Configuration Register Configuration (RCC_CFGR)
//     <o2.24..26> MCO: Microcontroller Clock Output   
//       <i> Default: MCO = noClock
//                     <0=> MCO = noClock
//                     <4=> MCO = SYSCLK
//                     <5=> MCO = HSI
//                     <6=> MCO = HSE
//                     <7=> MCO = PLLCLK / 2
//     <o2.22> USBPRE: USB prescaler
//       <i> Default: USBCLK = PLLCLK / 1.5
//                     <0=> USBCLK = PLLCLK / 1.5
//                     <1=> USBCLK = PLLCLK
//     <o2.14..15> ADCPRE: ADC prescaler
//       <i> Default: ADCCLK=PCLK2 / 2
//                     <0=> ADCCLK = PCLK2 / 2
//                     <1=> ADCCLK = PCLK2 / 4
//                     <2=> ADCCLK = PCLK2 / 6
//                     <3=> ADCCLK = PCLK2 / 8
//     <o2.11..13> PPRE2: APB High speed prescaler (APB2)
//       <i> Default: PCLK2 = HCLK
//                     <0=> PCLK2 = HCLK
//                     <4=> PCLK2 = HCLK / 2 
//                     <5=> PCLK2 = HCLK / 4 
//                     <6=> PCLK2 = HCLK / 8 
//                     <7=> PCLK2 = HCLK / 16 
//     <o2.8..10> PPRE1: APB Low speed prescaler (APB1) 
//       <i> Default: PCLK1 = HCLK
//                     <0=> PCLK1 = HCLK
//                     <4=> PCLK1 = HCLK / 2 
//                     <5=> PCLK1 = HCLK / 4 
//                     <6=> PCLK1 = HCLK / 8 
//                     <7=> PCLK1 = HCLK / 16 
//     <o2.4..7> HPRE: AHB prescaler 
//       <i> Default: HCLK = SYSCLK
//                     <0=> HCLK = SYSCLK
//                     <8=> HCLK = SYSCLK / 2
//                     <9=> HCLK = SYSCLK / 4
//                     <10=> HCLK = SYSCLK / 8
//                     <11=> HCLK = SYSCLK / 16
//                     <12=> HCLK = SYSCLK / 64
//                     <13=> HCLK = SYSCLK / 128
//                     <14=> HCLK = SYSCLK / 256
//                     <15=> HCLK = SYSCLK / 512
//     <o2.0..1> SW: System Clock Switch
//       <i> Default: SYSCLK = HSE
//                     <0=> SYSCLK = HSI
//                     <1=> SYSCLK = HSE
//                     <2=> SYSCLK = PLLCLK
//   </h>
//   <o3>HSE: External High Speed Clock [Hz] <4000000-16000000>
//   <i> clock value for the used External High Speed Clock (4MHz <= HSE <= 16MHz).
//   <i> Default: 8000000  (8MHz)
// </e> End of Clock Configuration
#define __CLOCK_SETUP              1
#define __RCC_CR_VAL               0x01010082
#define __RCC_CFGR_VAL             0x001D8402
#define __HSE                      8000000

//=========================================================================== Independent Watchdog Configuration
// <e0> Independent Watchdog Configuration
//   <o1> IWDG period [us] <125-32000000:125>
//   <i> Set the timer period for Independent Watchdog.
//   <i> Default: 1000000  (1s)
// </e>

#define __IWDG_SETUP              0
#define __IWDG_PERIOD             0x000F4240

/*----------------------------------------------------------------------------
 Define  IWDG PR and RLR settings
 *----------------------------------------------------------------------------*/

#if   (__IWDG_PERIOD >  16384000UL)
  #define __IWDG_PR             (6)
  #define __IWDGCLOCK (32000UL/256)

#elif (__IWDG_PERIOD >   8192000UL)
  #define __IWDG_PR             (5)
  #define __IWDGCLOCK (32000UL/128)

//                       5000000
#elif (__IWDG_PERIOD >   4096000UL)
  #define __IWDG_PR             (4)
  #define __IWDGCLOCK  (32000UL/64)
#elif (__IWDG_PERIOD >   2048000UL)
  #define __IWDG_PR             (3)
  #define __IWDGCLOCK  (32000UL/32)
#elif (__IWDG_PERIOD >   1024000UL)
  #define __IWDG_PR             (2)
  #define __IWDGCLOCK  (32000UL/16)
#elif (__IWDG_PERIOD >    512000UL)
  #define __IWDG_PR             (1)
  #define __IWDGCLOCK   (32000UL/8)
#else
  #define __IWDG_PR             (0)
  #define __IWDGCLOCK   (32000UL/4)
#endif
#define __IWGDCLK  (32000UL/(0x04<<__IWDG_PR))
#define __IWDG_RLR (__IWDG_PERIOD*__IWGDCLK/1000000UL-1)


/*----------------------------------------------------------------------------
 Define  IWDG PR and RLR settings
 *----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 STM32 Independent watchdog setup.
 initializes the IWDG register
 *----------------------------------------------------------------------------*/
void stm32_IwdgSetup (void) {

//  RCC->CSR |= (1<<0);                                           // LSI enable, necessary for IWDG
//  while ((RCC->CSR & (1<<1)) == 0);                             // wait till LSI is ready

  IWDG->KR  = 0x5555;                                           // enable write to PR, RLR
  IWDG->PR  = __IWDG_PR;                                        // Init prescaler
  IWDG->RLR = __IWDG_RLR;                                       // Init RLR
  IWDG->KR  = 0xAAA1;                                           // Reload the watchdog
  IWDG->KR  = 0xCCCC;                                           // Start the watchdog
} // end of stm32_IwdgSetup

//定义长延时喂狗5s
#define __LongIWDG_PERIOD         5000000UL
#define __LongIWDG_PR             (4)
#define __LongIWDGCLOCK   (32000UL/64)
#define __LongIWGDCLK  (32000UL/(0x04<<__LongIWDG_PR))
#define __LongIWDG_RLR (__LongIWDG_PERIOD*__LongIWGDCLK/1000000UL-1)

void stm32_IwdgSetupLong (void) {

//  RCC->CSR |= (1<<0);                                           // LSI enable, necessary for IWDG
//  while ((RCC->CSR & (1<<1)) == 0);                             // wait till LSI is ready

  IWDG->KR  = 0x5555;                                           // enable write to PR, RLR
  IWDG->PR  = __LongIWDG_PR;                                        // Init prescaler
  IWDG->RLR = __LongIWDG_RLR;                                       // Init RLR
  IWDG->KR  = 0xAAA1;                                           // Reload the watchdog
  IWDG->KR  = 0xCCCC;                                           // Start the watchdog
} // end of stm32_IwdgSetup

//定义短延时喂狗100ms
#define __ShortIWDG_PERIOD         100000UL
#define __ShortIWDG_PR             (0)
#define __ShortIWDGCLOCK   (32000UL/64)
#define __ShortIWGDCLK  (32000UL/(0x04<<__ShortIWDG_PR))
#define __ShortIWDG_RLR (__ShortIWDG_PERIOD*__ShortIWGDCLK/1000000UL-1)

void stm32_IwdgSetupShort (void) {

//  RCC->CSR |= (1<<0);                                           // LSI enable, necessary for IWDG
//  while ((RCC->CSR & (1<<1)) == 0);                             // wait till LSI is ready

  IWDG->KR  = 0x5555;                                           // enable write to PR, RLR
  IWDG->PR  = __ShortIWDG_PR;                                        // Init prescaler
  IWDG->RLR = __ShortIWDG_RLR;                                       // Init RLR
  IWDG->KR  = 0xAAA1;                                           // Reload the watchdog
  IWDG->KR  = 0xCCCC;                                           // Start the watchdog
} // end of stm32_IwdgSetup

//=========================================================================== Timer Configuration
// <e0> Timer Configuration
//--------------------------------------------------------------------------- Timer 1 enabled
//   <e1.0> TIM1 : Timer 1 enabled
//     <o4> TIM1 period [us] <1-72000000:10>
//       <i> Set the timer period for Timer 1.
//       <i> Default: 1000  (1ms)
//       <i> Ignored if detailed settings is selected
//     <o7> TIM1 repetition counter <0-255>
//       <i> Set the repetition counter for Timer 1.
//       <i> Default: 0
//       <i> Ignored if detailed settings is selected
//     <e2.0> TIM1 detailed settings
//--------------------------------------------------------------------------- Timer 1 detailed settings
//       <o5> TIM1.PSC: Timer1 Prescaler <0-65535>
//         <i> Set the prescaler for Timer 1.
//       <o6> TIM1.ARR: Timer1 Auto-reload <0-65535>
//         <i> Set the Auto-reload for Timer 1.
//       <o7> TIM1.RCR: Timer1 Repetition Counter <0-255>
//         <i> Set the Repetition Counter for Timer 1.
//
//       <h> Timer 1 Control Register 1 Configuration (TIM1_CR1)
//         <o8.8..9> TIM1_CR1.CKD: Clock division   
//           <i> Default: tDTS = tCK_INT
//           <i> devision ratio between timer clock and dead time
//                     <0=> tDTS = tCK_INT
//                     <1=> tDTS = 2*tCK_INT
//                     <2=> tDTS = 4*tCK_INT
//         <o8.7> TIM1_CR1.ARPE: Auto-reload preload enable
//           <i> Default: Auto-reload preload disenabled
//         <o8.5..6> TIM1_CR1.CMS: Center aligned mode selection   
//           <i> Default: Edge-aligned
//                     <0=> Edge-aligned
//                     <1=> Center-aligned mode1
//                     <2=> Center-aligned mode2
//                     <3=> Center-aligned mode3
//         <o8.4> TIM1_CR1.DIR: Direction
//           <i> Default: DIR = Counter used as up-counter
//           <i> read only if timer is configured as Center-aligned or Encoder mode   
//                     <0=> Counter used as up-counter
//                     <1=> Counter used as down-counter
//         <o8.3> TIM1_CR1.OPM: One pulse mode enable
//           <i> Default: One pulse mode disabled
//         <o8.2> TIM1_CR1.URS: Update request source   
//           <i> Default: URS = Counter over-/underflow, UG bit, Slave mode controller
//                     <0=> Counter over-/underflow, UG bit, Slave mode controller
//                     <1=> Counter over-/underflow
//         <o8.1> TIM1_CR1.UDIS: Update disable
//           <i> Default: Update enabled
//       </h>
//
//       <h> Timer 1 Control Register 2 Configuration (TIM1_CR2)
//         <o9.14> TIM1_CR2.OIS4: Output Idle state4 (OC4 output)   <0-1>
//         <o9.13> TIM1_CR2.OIS3N: Output Idle state3 (OC3N output) <0-1>
//         <o9.12> TIM1_CR2.OIS3: Output Idle state3 (OC3 output)   <0-1>
//         <o9.11> TIM1_CR2.OIS2N: Output Idle state2 (OC2N output) <0-1> 
//         <o9.10> TIM1_CR2.OIS2: Output Idle state2 (OC2 output)   <0-1>
//         <o9.9> TIM1_CR2.OIS1N: Output Idle state1 (OC1N output)
//           <i> Default: OC1 = 0
//                     <0=> OC1N=0 when MOE=0
//                     <1=> OC1N=1 when MOE=0
//         <o9.8> TIM1_CR2.OI1S: Output Idle state1 (OC1 output)  
//           <i> Default: OC1=0
//                     <0=> OC1=0 when MOE=0
//                     <1=> OC1=1 when MOE=0
//         <o9.7> TIM1_CR2.TI1S: TI1 Selection  
//           <i> Default: TIM1CH1 connected to TI1 input
//                     <0=> TIM1CH1 connected to TI1 input
//                     <1=> TIM1CH1,CH2,CH3 connected to TI1 input
//         <o9.4..6> TIM1_CR2.MMS: Master Mode Selection  
//           <i> Default: Reset
//           <i> Select information to be sent in master mode to slave timers for synchronisation
//                     <0=> Reset
//                     <1=> Enable
//                     <2=> Update
//                     <3=> Compare Pulse
//                     <4=> Compare OC1REF iused as TRGO
//                     <5=> Compare OC2REF iused as TRGO
//                     <6=> Compare OC3REF iused as TRGO
//                     <7=> Compare OC4REF iused as TRGO
//         <o9.2> TIM1_CR2.CCUS: Capture/Compare Control Update Selection  
//           <i> Default: setting COM bit
//                     <0=> setting COM bit
//                     <1=> setting COM bit or rising edge TRGI
//         <o9.0> TIM1_CR2.CCPC: Capture/Compare Preloaded Control   
//           <i> Default: CCxE,CCxNE,OCxM not preloaded
//                     <0=> CCxE,CCxNE,OCxM not preloaded
//                     <1=> CCxE,CCxNE,OCxM preloaded
//       </h>
//
//       <h> Timer 1 Slave mode control register Configuration (TIM1_SMC)
//         <o10.15> TIM1_SMCR.ETP: External trigger polarity
//           <i> Default: ETR is non-inverted
//                     <0=> ETR is non-inverted
//                     <1=> ETR is inverted
//         <o10.14> TIM1_SMCR.ECE: External clock mode 2 enabled
//         <o10.12..13> TIM1_SMCR.ETPS: External trigger prescaler  
//           <i> Default: Prescaler OFF
//                     <0=> Prescaler OFF
//                     <1=> fETPR/2
//                     <2=> fETPR/4
//                     <3=> fETPR/8
//         <o10.8..11> TIM1_SMCR.ETF: External trigger filter  
//           <i> Default: No filter
//                     <0=>  No filter
//                     <1=>  fSampling=fCK_INT, N=2
//                     <2=>  fSampling=fCK_INT, N=4
//                     <3=>  fSampling=fCK_INT, N=8
//                     <4=>  fSampling=fDTS/2, N=6
//                     <5=>  fSampling=fDTS/2, N=8
//                     <6=>  fSampling=fDTS/4, N=6
//                     <7=>  fSampling=fDTS/4, N=8
//                     <8=>  fSampling=fDTS/8, N=6
//                     <9=>  fSampling=fDTS/8, N=8
//                     <10=> fSampling=fDTS/16, N=5
//                     <11=> fSampling=fDTS/16, N=6
//                     <12=> fSampling=fDTS/16, N=8
//                     <13=> fSampling=fDTS/32, N=5
//                     <14=> fSampling=fDTS/32, N=6
//                     <15=> fSampling=fDTS/32, N=8
//         <o10.7> TIM1_SMCR.MSM: Delay trigger input  
//         <o10.4..6> TIM1_SMCR.TS: Trigger Selection  
//           <i> Default: Reserved
//                     <0=> Reserved
//                     <1=> TIM2 (ITR1)
//                     <2=> TIM3 (ITR2)
//                     <3=> TIM4 (ITR3)
//                     <4=> TI1 Edge Detector (TI1F_ED)
//                     <5=> Filtered Timer Input 1 (TI1FP1)
//                     <6=> Filtered Timer Input 2 (TI1FP2)
//                     <7=> External Trigger Input (ETRF)
//         <o10.0..2> TIM1_SMCR.SMS: Slave mode selection   
//           <i> Default: Slave mode disabled
//                     <0=> Slave mode disabled
//                     <1=> Encoder mode 1
//                     <2=> Encoder mode 2
//                     <3=> Encoder mode 3
//                     <4=> Reset mode
//                     <5=> Gated mode
//                     <6=> Trigger mode
//                     <7=> External clock mode 1
//       </h>
//
//--------------------------------------------------------------------------- Timer 1 channel 1
//       <h> Channel 1 Configuration
//         <h> Cannel configured as output
//           <o11.7> TIM1_CCMR1.OC1CE: Output Compare 1 Clear enabled  
//           <o11.4..6> TIM1_CCMR1.OC1M: Output Compare 1 Mode  
//             <i> Default: Frozen
//                       <0=>  Frozen
//                       <1=>  Set channel 1 to active level on match
//                       <2=>  Set channel 1 to inactive level on match
//                       <3=>  Toggle 
//                       <4=>  Force inactive level
//                       <5=>  Force active level
//                       <6=>  PWM mode 1
//                       <7=>  PWM mode 2
//           <o11.3> TIM1_CCMR1.OC1PE: Output Compare 1 Preload enabled  
//           <o11.2> TIM1_CCMR1.OC1FE: Output Compare 1 Fast enabled  
//           <o11.0..1> TIM1_CCMR1.CC1S: Capture/compare 1 selection   
//             <i> Default: CC1 configured as output
//                       <0=> CC1 configured as output
//           <o13.3> TIM1_CCER.CC1NP: Capture/compare 1 Complementary output Polarity set  
//             <i> Default: OC1N active high
//                       <0=> OC1N active high
//                       <1=> OC1N active low
//           <o13.2> TIM1_CCER.CC1NE: Capture/compare 1 Complementary output enabled
//             <i> Default: OC1N not active
//                       <0=> OC1N not active
//                       <1=> OC1N is output on corresponding pin
//           <o13.1> TIM1_CCER.CC1P: Capture/compare 1 output Polarity set  
//             <i> Default: OC1 active high
//                       <0=> OC1 active high
//                       <1=> OC1 active low
//           <o13.0>  TIM1_CCER.CC1E: Capture/compare 1 output enabled   
//             <i> Default: OC1 not active
//                       <0=> OC1 not active
//                       <1=> OC1 is output on corresponding pin
//         </h>
//         <h> Channel configured as input
//           <o11.4..7> TIM1_CCMR1.IC1F: Input Capture 1 Filter  
//             <i> Default: No filter
//                       <0=>  No filter
//                       <1=>  fSampling=fCK_INT, N=2
//                       <2=>  fSampling=fCK_INT, N=4
//                       <3=>  fSampling=fCK_INT, N=8
//                       <4=>  fSampling=fDTS/2, N=6
//                       <5=>  fSampling=fDTS/2, N=8
//                       <6=>  fSampling=fDTS/4, N=6
//                       <7=>  fSampling=fDTS/4, N=8
//                       <8=>  fSampling=fDTS/8, N=6
//                       <9=>  fSampling=fDTS/8, N=8
//                       <10=> fSampling=fDTS/16, N=5
//                       <11=> fSampling=fDTS/16, N=6
//                       <12=> fSampling=fDTS/16, N=8
//                       <13=> fSampling=fDTS/32, N=5
//                       <14=> fSampling=fDTS/32, N=6
//                       <15=> fSampling=fDTS/32, N=8
//           <o11.2..3> TIM1_CCMR1.IC1PSC: Input Capture 1 Prescaler  
//             <i> Default: No prescaler
//                       <0=>  No prescaler
//                       <1=>  capture every 2 events
//                       <2=>  capture every 4 events
//                       <3=>  capture every 8 events 
//           <o11.0..1> TIM1_CCMR1.CC1S: Capture/compare 1 selection   
//             <i> Default: CC1 configured as output
//                       <0=> CC1 configured as output
//                       <1=> CC1 configured as input, IC1 mapped on TI1
//                       <2=> CC1 configured as input, IC1 mapped on TI2
//                       <3=> CC1 configured as input, IC1 mapped on TRGI
//           <o13.1>  TIM1_CCER.CC1P: Capture/compare 1 output Polarity set  
//             <i> Default: non-inverted
//                       <0=> non-inverted
//                       <1=> inverted
//           <o13.0>  TIM1_CCER.CC1E: Capture/compare 1 output enabled   
//             <i> Default: Capture disabled
//                       <0=> Capture disabled
//                       <1=> Capture enabled
//         </h>
//       <o14> TIM1_CCR1: Capture/compare register 1 <0-65535>
//         <i> Set the Compare register value for compare register 1.
//         <i> Default: 0
//     </h>
//
//--------------------------------------------------------------------------- Timer 1 channel 2
//       <h> Channel 2 Configuration
//         <h> Cannel configured as output
//           <o11.15> TIM1_CCMR1.OC2CE: Output Compare 2 Clear enabled  
//           <o11.12..14> TIM1_CCMR1.OC2M: Output Compare 2 Mode  
//             <i> Default: Frozen
//                       <0=>  Frozen
//                       <1=>  Set channel 2 to active level on match
//                       <2=>  Set channel 2 to inactive level on match
//                       <3=>  Toggle 
//                       <4=>  Force inactive level
//                       <5=>  Force active level
//                       <6=>  PWM mode 1
//                       <7=>  PWM mode 2
//           <o11.11> TIM1_CCMR1.OC2PE: Output Compare 2 Preload enabled  
//           <o11.10> TIM1_CCMR1.OC2FE: Output Compare 2 Fast enabled  
//           <o11.8..9> TIM1_CCMR1.CC2S: Capture/compare 2 selection   
//             <i> Default: CC2 configured as output
//                       <0=> CC2 configured as output
//           <o13.7> TIM1_CCER.CC2NP: Capture/compare 2 Complementary output Polarity set  
//             <i> Default: OC2N active high
//                       <0=> OC2N active high
//                       <1=> OC2N active low
//           <o13.6> TIM1_CCER.CC2NE: Capture/compare 2 Complementary output enabled
//             <i> Default: OC2N not active
//                       <0=> OC2N not active
//                       <1=> OC2N is output on corresponding pin
//           <o13.5>  TIM1_CCER.CC2P: Capture/compare 2 output Polarity set  
//             <i> Default: OC2 active high
//                       <0=> OC2 active high
//                       <1=> OC2 active low
//           <o13.4>  TIM1_CCER.CC2E: Capture/compare 2 output enabled   
//             <i> Default: OC2 not active
//                       <0=> OC2 not active
//                       <1=> OC2 is output on corresponding pin
//         </h>
//         <h> Channel configured as input
//           <o11.12..15> TIM1_CCMR1.IC2F: Input Capture 2 Filter  
//             <i> Default: No filter
//                       <0=>  No filter
//                       <1=>  fSampling=fCK_INT, N=2
//                       <2=>  fSampling=fCK_INT, N=4
//                       <3=>  fSampling=fCK_INT, N=8
//                       <4=>  fSampling=fDTS/2, N=6
//                       <5=>  fSampling=fDTS/2, N=8
//                       <6=>  fSampling=fDTS/4, N=6
//                       <7=>  fSampling=fDTS/4, N=8
//                       <8=>  fSampling=fDTS/8, N=6
//                       <9=>  fSampling=fDTS/8, N=8
//                       <10=> fSampling=fDTS/16, N=5
//                       <11=> fSampling=fDTS/16, N=6
//                       <12=> fSampling=fDTS/16, N=8
//                       <13=> fSampling=fDTS/32, N=5
//                       <14=> fSampling=fDTS/32, N=6
//                       <15=> fSampling=fDTS/32, N=8
//           <o11.10..11> TIM1_CCMR1.IC2PSC: Input Capture 2 Prescaler  
//             <i> Default: No prescaler
//                       <0=>  No prescaler
//                       <1=>  capture every 2 events
//                       <2=>  capture every 4 events
//                       <3=>  capture every 8 events 
//           <o11.8..9> TIM1_CCMR1.CC2S: Capture/compare 2 selection   
//             <i> Default: CC2 configured as output
//                       <0=> CC2 configured as output
//                       <1=> CC2 configured as input, IC2 mapped on TI2
//                       <2=> CC2 configured as input, IC2 mapped on TI1
//                       <3=> CC2 configured as input, IC2 mapped on TRGI
//           <o13.5>  TIM1_CCER.CC2P: Capture/compare 2 output Polarity set  
//             <i> Default: non-inverted
//                       <0=> non-inverted
//                       <1=> inverted
//           <o13.4>  TIM1_CCER.CC2E: Capture/compare 2 output enabled   
//             <i> Default: Capture disabled
//                       <0=> Capture disabled
//                       <1=> Capture enabled
//         </h>
//       <o15> TIM1_CCR2: Capture/compare register 2 <0-65535>
//         <i> Set the Compare register value for compare register 2.
//         <i> Default: 0
//     </h>
//
//--------------------------------------------------------------------------- Timer 1 channel 3
//       <h> Channel 3 Configuration
//         <h> Cannel configured as output
//           <o12.7> TIM1_CCMR2.OC3CE: Output Compare 3 Clear enabled  
//           <o12.4..6> TIM1_CCMR2.OC3M: Output Compare 3 Mode  
//             <i> Default: Frozen
//                       <0=>  Frozen
//                       <1=>  Set channel 3 to active level on match
//                       <2=>  Set channel 3 to inactive level on match
//                       <3=>  Toggle 
//                       <4=>  Force inactive level
//                       <5=>  Force active level
//                       <6=>  PWM mode 1
//                       <7=>  PWM mode 2
//           <o12.3> TIM1_CCMR2.OC3PE: Output Compare 3 Preload enabled  
//           <o12.2> TIM1_CCMR2.OC3FE: Output Compare 3 Fast enabled  
//           <o12.0..1> TIM1_CCMR2.CC3S: Capture/compare 3 selection   
//             <i> Default: CC3 configured as output
//                       <0=> CC3 configured as output
//           <o13.11> TIM1_CCER.CC3NP: Capture/compare 3 Complementary output Polarity set  
//             <i> Default: OC3N active high
//                       <0=> OC3N active high
//                       <1=> OC3N active low
//           <o13.10> TIM1_CCER.CC3NE: Capture/compare 3 Complementary output enabled
//             <i> Default: OC3N not active
//                       <0=> OC3N not active
//                       <1=> OC3N is output on corresponding pin
//           <o13.9>  TIM1_CCER.CC3P: Capture/compare 3 output Polarity set  
//             <i> Default: OC3 active high
//                       <0=> OC3 active high
//                       <1=> OC3 active low
//           <o13.8>  TIM1_CCER.CC3E: Capture/compare 3 output enabled   
//             <i> Default: OC3 not active
//                       <0=> OC3 not active
//                       <1=> OC3 is output on corresponding pin
//         </h>
//         <h> Channel configured as input
//           <o12.4..7> TIM1_CCMR2.IC3F: Input Capture 3 Filter  
//             <i> Default: No filter
//                       <0=>  No filter
//                       <1=>  fSampling=fCK_INT, N=2
//                       <2=>  fSampling=fCK_INT, N=4
//                       <3=>  fSampling=fCK_INT, N=8
//                       <4=>  fSampling=fDTS/2, N=6
//                       <5=>  fSampling=fDTS/2, N=8
//                       <6=>  fSampling=fDTS/4, N=6
//                       <7=>  fSampling=fDTS/4, N=8
//                       <8=>  fSampling=fDTS/8, N=6
//                       <9=>  fSampling=fDTS/8, N=8
//                       <10=> fSampling=fDTS/16, N=5
//                       <11=> fSampling=fDTS/16, N=6
//                       <12=> fSampling=fDTS/16, N=8
//                       <13=> fSampling=fDTS/32, N=5
//                       <14=> fSampling=fDTS/32, N=6
//                       <15=> fSampling=fDTS/32, N=8
//           <o12.2..3> TIM1_CCMR2.IC3PSC: Input Capture 3 Prescaler  
//             <i> Default: No prescaler
//                       <0=>  No prescaler
//                       <1=>  capture every 2 events
//                       <2=>  capture every 4 events
//                       <3=>  capture every 8 events 
//           <o12.0..1> TIM1_CCMR2.CC3S: Capture/compare 3 selection   
//             <i> Default: CC3 configured as output
//                       <0=> CC3 configured as output
//                       <1=> CC3 configured as input, IC3 mapped on TI3
//                       <2=> CC3 configured as input, IC3 mapped on TI4
//                       <3=> CC3 configured as input, IC3 mapped on TRGI
//           <o13.9>  TIM1_CCER.CC3P: Capture/compare 3 output Polarity set  
//             <i> Default: non-inverted
//                       <0=> non-inverted
//                       <1=> inverted
//           <o13.8>  TIM1_CCER.CC3E: Capture/compare 3 output enabled   
//             <i> Default: Capture disabled
//                       <0=> Capture disabled
//                       <1=> Capture enabled
//         </h>
//       <o16> TIM1_CCR3: Capture/compare register 3 <0-65535>
//         <i> Set the Compare register value for compare register 3.
//         <i> Default: 0
//     </h>
//
//--------------------------------------------------------------------------- Timer 1 channel 4
//       <h> Channel 4 Configuration
//         <h> Cannel configured as output
//           <o12.15> TIM1_CCMR2.OC4CE: Output Compare 4 Clear enabled  
//           <o12.12..14> TIM1_CCMR2.OC4M: Output Compare 4 Mode  
//             <i> Default: Frozen
//                       <0=>  Frozen
//                       <1=>  Set channel 4 to active level on match
//                       <2=>  Set channel 4 to inactive level on match
//                       <3=>  Toggle 
//                       <4=>  Force inactive level
//                       <5=>  Force active level
//                       <6=>  PWM mode 1
//                       <7=>  PWM mode 2
//           <o12.11> TIM1_CCMR2.OC4PE: Output Compare 4 Preload enabled  
//           <o12.10> TIM1_CCMR2.OC4FE: Output Compare 4 Fast enabled  
//           <o12.8..9> TIM1_CCMR2.CC4S: Capture/compare 4 selection   
//             <i> Default: CC4 configured as output
//                       <0=> CC4 configured as output
//           <o13.13>  TIM1_CCER.CC4P: Capture/compare 4 output Polarity set  
//             <i> Default: OC4 active high
//                       <0=> OC4 active high
//                       <1=> OC4 active low
//           <o13.12>  TIM1_CCER.CC4E: Capture/compare 4 output enabled   
//             <i> Default: OC4 not active
//                       <0=> OC4 not active
//                       <1=> OC4 is output on corresponding pin
//         </h>
//         <h> Channel configured as input
//           <o12.12..15> TIM1_CCMR2.IC4F: Input Capture 4 Filter  
//             <i> Default: No filter
//                       <0=>  No filter
//                       <1=>  fSampling=fCK_INT, N=2
//                       <2=>  fSampling=fCK_INT, N=4
//                       <3=>  fSampling=fCK_INT, N=8
//                       <4=>  fSampling=fDTS/2, N=6
//                       <5=>  fSampling=fDTS/2, N=8
//                       <6=>  fSampling=fDTS/4, N=6
//                       <7=>  fSampling=fDTS/4, N=8
//                       <8=>  fSampling=fDTS/8, N=6
//                       <9=>  fSampling=fDTS/8, N=8
//                       <10=> fSampling=fDTS/16, N=5
//                       <11=> fSampling=fDTS/16, N=6
//                       <12=> fSampling=fDTS/16, N=8
//                       <13=> fSampling=fDTS/32, N=5
//                       <14=> fSampling=fDTS/32, N=6
//                       <15=> fSampling=fDTS/32, N=8
//           <o12.10..11> TIM1_CCMR2.IC4PSC: Input Capture 4 Prescaler  
//             <i> Default: No prescaler
//                       <0=>  No prescaler
//                       <1=>  capture every 2 events
//                       <2=>  capture every 4 events
//                       <3=>  capture every 8 events 
//           <o12.8..9> TIM1_CCMR2.CC4S: Capture/compare 4 selection   
//             <i> Default: CC4 configured as output
//                       <0=> CC4 configured as output
//                       <1=> CC4 configured as input, IC4 mapped on TI4
//                       <2=> CC4 configured as input, IC4 mapped on TI3
//                       <3=> CC4 configured as input, IC4 mapped on TRGI
//           <o13.13>  TIM1_CCER.CC4P: Capture/compare 4 output Polarity set  
//             <i> Default: non-inverted
//                       <0=> non-inverted
//                       <1=> inverted
//           <o13.12>  TIM1_CCER.CC4E: Capture/compare 4 output enabled   
//             <i> Default: Capture disabled
//                       <0=> Capture disabled
//                       <1=> Capture enabled
//         </h>
//       <o17> TIM1_CCR4: Capture/compare register 4 <0-65535>
//         <i> Set the Compare register value for compare register 4.
//         <i> Default: 0
//     </h>
//
//       <h> Timer1 Break and dead-time register Configuration (TIM1_BDTR)
//         <o18.15> TIM1_BDTR.MOE: Main Output enabled
//         <o18.14> TIM1_BDTR.AOE: Automatic Output enabled
//         <o18.13> TIM1_BDTR.BKP: Break Polarity active high
//         <o18.12> TIM1_BDTR.BKE: Break Inputs enabled
//         <o18.11> TIM1_BDTR.OSSR: Off-State Selection for Run mode
//           <i> Default: OC/OCN output signal=0
//                     <0=> OC/OCN output signal=0
//                     <1=> OC/OCN output signal=1
//         <o18.10> TIM1_BDTR.OSSI: Off-State Selection for Idle mode
//           <i> Default: OC/OCN output signal=0
//                     <0=> OC/OCN output signal=0
//                     <1=> OC/OCN output signal=1
//         <o18.8..9> TIM1_BDTR.LOCK: Lock Level <0-3>
//           <i> Default: 0 (LOCK OFF)
//         <o18.0..7> TIM1_BDTR.DTG: Dead-Time Generator set-up <0x00-0xFF>   
//       </h>
//
//     </e>
//     <e3.0> TIM1 interrupts
//       <o19.14> TIM1_DIER.TDE: Trigger DMA request enabled
//       <o19.12> TIM1_DIER.CC4DE: Capture/Compare 4 DMA request enabled
//       <o19.11> TIM1_DIER.CC3DE: Capture/Compare 3 DMA request enabled
//       <o19.10> TIM1_DIER.CC2DE: Capture/Compare 2 DMA request enabled
//       <o19.9>  TIM1_DIER.CC1DE: Capture/Compare 1 DMA request enabled
//       <o19.8>  TIM1_DIER.UDE: Update DMA request enabled
//       <o19.7>  TIM1_DIER.BIE: Break interrupt enabled
//       <o19.6>  TIM1_DIER.TIE: Trigger interrupt enabled
//       <o19.5>  TIM1_DIER.COMIE: COM interrupt enabled
//       <o19.4>  TIM1_DIER.CC4IE: Capture/Compare 4 interrupt enabled
//       <o19.3>  TIM1_DIER.CC3IE: Capture/Compare 3 interrupt enabled
//       <o19.2>  TIM1_DIER.CC2IE: Capture/Compare 2 interrupt enabled
//       <o19.1>  TIM1_DIER.CC1IE: Capture/Compare 1 interrupt enabled
//       <o19.0>  TIM1_DIER.UIE: Update interrupt enabled
//     </e>
//   </e>

// </e> End of Timer Configuration
#define __TIMER_SETUP             0                       //  0
#define __TIMER_USED              0x0001                  //  1
#define __TIMER_DETAILS           0x0000                  //  2
#define __TIMER_INTERRUPTS        0x0001                  //  3
#define __TIM1_PERIOD             0x003E8                 //  4
#define __TIM1_PSC                0x0000                  //  5
#define __TIM1_ARR                0x0004                  //  6
#define __TIM1_RCR                0x0000                  //  7
#define __TIM1_CR1                0x0004                  //  8
#define __TIM1_CR2                0x0000                  //  9
#define __TIM1_SMCR               0x0000                  // 10
#define __TIM1_CCMR1              0x0061                  // 11
#define __TIM1_CCMR2              0x0068                  // 12
#define __TIM1_CCER               0x0000                  // 13
#define __TIM1_CCR1               0x0000                  // 14
#define __TIM1_CCR2               0x0000                  // 15
#define __TIM1_CCR3               0x0000                  // 16
#define __TIM1_CCR4               0x0000                  // 17
#define __TIM1_BDTR               0x0000                  // 18
#define __TIM1_DIER               0x0001                  // 19

/*----------------------------------------------------------------------------
  DEFINES
 *----------------------------------------------------------------------------*/
#define CFGR_SWS_MASK       0x0000000C             // Mask for used SYSCLK
#define CFGR_SW_MASK        0x00000003             // Mask for used SYSCLK
#define CFGR_PLLMULL_MASK   0x003C0000             // Mask for PLL multiplier
#define CFGR_PLLXTPRE_MASK  0x00020000             // Mask for PLL HSE devider
#define CFGR_PLLSRC_MASK    0x00010000             // Mask for PLL clock source
#define CFGR_HPRE_MASK      0x000000F0             // Mask for AHB prescaler
#define CFGR_PRE1_MASK      0x00000700             // Mask for APB1 prescaler     
#define CFGR_PRE2_MASK      0x00003800             // Mask for APB2 prescaler 

/*----------------------------------------------------------------------------
 Define SYSCLK
 *----------------------------------------------------------------------------*/
#define __HSI 8000000UL
//#define __HSE 8000000UL
#define __PLLMULL (((__RCC_CFGR_VAL & CFGR_PLLMULL_MASK) >> 18) + 2)

#if   ((__RCC_CFGR_VAL & CFGR_SW_MASK) == 0x00) 
  #define __SYSCLK   __HSI                        // HSI is used as system clock
#elif ((__RCC_CFGR_VAL & CFGR_SW_MASK) == 0x01)
  #define __SYSCLK   __HSE                        // HSE is used as system clock
#elif ((__RCC_CFGR_VAL & CFGR_SW_MASK) == 0x02)
  #if (__RCC_CFGR_VAL & CFGR_PLLSRC_MASK)         // HSE is PLL clock source
    #if (__RCC_CFGR_VAL & CFGR_PLLXTPRE_MASK)     // HSE/2 is used
      #define __SYSCLK  ((__HSE >> 1) * __PLLMULL)// SYSCLK = HSE/2 * pllmull
    #else                                         // HSE is used
      #define __SYSCLK  ((__HSE >> 0) * __PLLMULL)// SYSCLK = HSE   * pllmul
    #endif  
  #else                                           // HSI/2 is PLL clock source
    #define __SYSCLK  ((__HSI >> 1) * __PLLMULL)  // SYSCLK = HSI/2 * pllmul
  #endif
#else
   #error "ask for help"
#endif

/*----------------------------------------------------------------------------
 Define  HCLK
 *----------------------------------------------------------------------------*/
#define __HCLKPRESC  ((__RCC_CFGR_VAL & CFGR_HPRE_MASK) >> 4)
#if (__HCLKPRESC & 0x08)
  #define __HCLK        (__SYSCLK >> ((__HCLKPRESC & 0x07)+1))
#else
  #define __HCLK        (__SYSCLK)
#endif

/*----------------------------------------------------------------------------
 Define  PCLK2
 *----------------------------------------------------------------------------*/
#define __PCLK2PRESC  ((__RCC_CFGR_VAL & CFGR_PRE2_MASK) >> 11)
#if (__PCLK2PRESC & 0x04)
  #define __PCLK2       (__HCLK >> ((__PCLK2PRESC & 0x03)+1))
#else
  #define __PCLK2       (__HCLK)
#endif

/*----------------------------------------------------------------------------
 Define  TIM1CLK
 *----------------------------------------------------------------------------*/
#if (__PCLK2PRESC & 0x04)
  #define __TIM1CLK     (2*__PCLK2)
#else
  #define __TIM1CLK     (__PCLK2)
#endif

/*----------------------------------------------------------------------------
 Define Timer PSC and ARR settings
 *----------------------------------------------------------------------------*/
#define __VAL(__TIMCLK, __PERIOD) ((__TIMCLK/1000000UL)*__PERIOD)
//#define __PSC(__TIMCLK, __PERIOD) ((__VAL(__TIMCLK, __PERIOD)-1)>>15)
#define __PSC(__TIMCLK, __PERIOD)  (((__VAL(__TIMCLK, __PERIOD)+49999UL)/50000UL) - 1)
#define __ARR(__TIMCLK, __PERIOD) ((__VAL(__TIMCLK, __PERIOD)/(__PSC(__TIMCLK, __PERIOD)+1)) - 1)


/*----------------------------------------------------------------------------
 STM32 Timer setup.
 initializes the Timer register
 *----------------------------------------------------------------------------*/
void stm32_TimerSetup (void) 
{
  
  if (__TIMER_USED & 0x01) {                                // TIM1 used
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;                     // enable clock for TIM1

    TIM1->PSC = __PSC(__TIM1CLK, __TIM1_PERIOD);            // set prescaler
    TIM1->ARR = __ARR(__TIM1CLK, __TIM1_PERIOD);            // set auto-reload
    TIM1->RCR = __TIM1_RCR;                                 // set repetition counter

    TIM1->CR1 = 0;                                          // reset command register 1
    TIM1->CR2 = 0;                                          // reset command register 2

    if (__TIMER_DETAILS & 0x01) {                           // detailed settings used
      TIM1->PSC = __TIM1_PSC;                               // set prescaler
      TIM1->ARR = __TIM1_ARR;                               // set auto-reload

      TIM1->CCR1  = __TIM1_CCR1;                            //
      TIM1->CCR2  = __TIM1_CCR2;                            //
      TIM1->CCR3  = __TIM1_CCR3;                            //
      TIM1->CCR4  = __TIM1_CCR4;                            //
      TIM1->CCMR1 = __TIM1_CCMR1;                           //
      TIM1->CCMR2 = __TIM1_CCMR2;                           //
      TIM1->CCER  = __TIM1_CCER;                            // set capture/compare enable register
      TIM1->SMCR  = __TIM1_SMCR;                            // set slave mode control register

      TIM1->CR1 = __TIM1_CR1;                               // set command register 1
      TIM1->CR2 = __TIM1_CR2;                               // set command register 2
    }

    if (__TIMER_INTERRUPTS & 0x01) {                        // interrupts used
      TIM1->DIER = __TIM1_DIER;                             // enable interrupt
      NVIC->ISER[0] |= (1 << (TIM1_UP_IRQChannel & 0x1F));  // enable interrupt
    }

    TIM1->CR1 |= TIMX_CR1_CEN;                              // enable timer
  } // end TIM1 used
  
} // end of stm32_TimSetup


