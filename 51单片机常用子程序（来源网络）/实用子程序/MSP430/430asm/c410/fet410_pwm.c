/***********************************************************************/
/*  pwm413.c                                               2000-05-11  */
/*                                                                     */
/*             Demo to Test Timer_A PWM Functions                      */
/*                                                                     */
/* This simple program demonstrates the PWM Generation including dead  */
/* band Generation with Timer_A on pin P1.2 and P2.0                  */
/* The duty cycle will be changed after every full PWM period. When    */
/* a lowpass filter is connected, a triangular signal can be seen.     */
/*                                                                     */
/* Following Timer_A registers have been used:                         */
/*   TACNT:  up/down mode, 2x3 groups of TBCCRx                        */
/*   TACCRO: PWM period                                                */
/*   TACCR1: duty cycle for PWM at P1.2                                */
/*   TACCR2: duty cycle for PWM at P2.0                                */
/*                                                                     */
/*  Texas Instruments Incorporated                                     */
/***********************************************************************/
#include  "MSP430x41x.H"          // Standard Equations


#define PWM_step 5          /* stepwidth to change PWM */
#define PWM_freq 2000       /* define PWM period */
#define PWM_dead 50         /* define dead-band of PWM signal */

#define UP  0               /* PWM status definition */
#define DOWN 1


/***********************************************************************/
/* Makro definition                                                    */
/***********************************************************************/
/* --- void WD_Timer( void )  -----------------------------------------*/
#define WD_Timer()                                \
  WDTCTL=0x5A18;   /* initialize WD as Timer */   \
  IE1|=0x01;       /* enable WDT interrupt */     \


/***********************************************************************/
/* global Variable definition */
/***********************************************************************/
unsigned int PWM_period;
unsigned int PWM12_duty;
unsigned char PWM_status;

/***********************************************************************/
/* Function declaration */
/***********************************************************************/
void PWM12_init( unsigned int period, unsigned int duty );
void PWM12_update( void );


/***********************************************************************/
/* PWM12_init                                                          */
/* initializes Timer_A in up/down mode and select 2x3 groups of CCR to */
/* generate two PWM signals with CCR1 and CCR2. CCR0 defines period.   */
/* Timer_A overflow (TBR goes from CCR0 to 0) will update PWM          */
/***********************************************************************/
void PWM12_init( unsigned int period, unsigned int duty )
{
  CCR0=period;        /* load period register */
  CCR1=duty;          /* load duty cycle register CCR1 */
  CCR2=duty+PWM_dead; /* load duty cycle register CCR2 + dead band */
  CCTL0=0;
  CCTL1=0x02C0;       /* TBCCTL1 is master */
  CCTL2=0x0240;
  TACTL=0x2236;         /* start Timer_A and enable overflow interrupt */
}


/***********************************************************************/
/* main */
/***********************************************************************/
void main( void )
{
 FLL_CTL0 |= XCAP10PF;     // Set load Cap. for Cristal = 6pF
                           // (10pF + 2pF(Pad)) / 2
 WD_Timer();

 P1DIR|=0x01;             /* P1.0 is test output for LED */
 P1SEL|=0x04;             /* select P1.2 for PWM output */
 P1DIR|=0x04;             /* select P1.2 for output */
 P2SEL|=0x01;             /* select P2.0 for PWM output */
 P2DIR|=0x01;             /* select P2.0 for output */
 
 PWM_status=UP;           /* start with UP direction */
 PWM_period=PWM_freq/2;   /* initialize PWM period = PWM_freq/2 */
 PWM12_duty=PWM_freq/4;   /* start with 50% PWM duty cycle */
 PWM12_init( PWM_period, PWM12_duty );  
 _EINT();                 /* enable global interrupts */
 
 LPM0;                    /* switch CPU off */

} /* end of main */



/***********************************************************************/
/* Watchdog interrupt service routine                                  */
/***********************************************************************/
interrupt [WDT_VECTOR] void WD( void )
{
  static unsigned short LED_count=0;

  LED_count ++;
  if( LED_count >= 10 )
  {
   P1OUT^=0x01;          /* toggle P1.0 output to detect sw is running */
   LED_count=0;
  } 
}


/***********************************************************************/
/* Timer_A3 Interrupt Vector (TAIV) handler */
/***********************************************************************/
interrupt [TIMERA1_VECTOR] void Timer_A(void)
{
 switch( TAIV )
 {
   case  2: break;              /* CCR1 */
   case  4: break;              /* CCR2 */
   case  6: break;              /* CCR3 */
   case  8: break;              /* CCR4 */
   case 10: PWM12_update();     /* Timer_A3 overflow */
            break;
 }
}


/***********************************************************************/
/* Timer_A3 Timer Overflow  Interrupt Service Routine                  */
/* updates PWM_duty cycle register CCR1 and CCR2                       */
/***********************************************************************/
void PWM12_update( void )
{
/* --- check PWM ranges -----------------------------------------------*/
    if( PWM12_duty >= PWM_period )  
    { 
      PWM_status = DOWN;
    }  
    if( PWM12_duty == 0 )
    {
      PWM_status = UP;
    }  
    
/* --- calculate new PWM duty cycle -----------------------------------*/
  if( PWM_status == UP )
  { 
    PWM12_duty+=PWM_step;
    CCR1=PWM12_duty;
    CCR2=PWM12_duty+PWM_dead;
  }  

  if( PWM_status == DOWN )
  { 
    PWM12_duty-=PWM_step;
    CCR1=PWM12_duty;
    CCR2=PWM12_duty+PWM_dead;
  }  

  if( CCR2 > PWM_period )
    CCR2=PWM_period;
    
}
