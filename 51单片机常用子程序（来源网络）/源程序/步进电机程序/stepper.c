/*
 * STEPPER.C
 * sweeping stepper's rotor cw and cww 400 steps
 * Copyright (c) 1999 by W.Sirichote
 */

#include c:\mc51\8051io.h  /* include i/o header file */
#include c:\mc51\8051reg.h

register unsigned char j,flag1,temp;
register unsigned int cw_n,ccw_n;

unsigned char step[8]={0x80,0xc0,0x40,0x60,0x20,0x30,0x10,0x90}
#define n 400

/* flag1 mask byte
   0x01  run cw()
   0x02  run ccw()
*/

main()

{
  flag1=0;
  serinit(9600);
  disable();  /* no need timer interrupt */
  cw_n = n;    /* initial step number for cw */
  flag1 |=0x01; /* initial enable cw() */

 while(1){  
  {
    tick_wait();  /* wait for 10ms elapsed */

    energize();   /* round-robin execution the following tasks every 10ms */
    cw();
    ccw();
  }
        }

}

cw(){
       if((flag1&0x01)!=0)
       {
        cw_n--;       /* decrement cw step number */
        if (cw_n !=0)
         j++;         /* if not zero increment index j */
         else
         {flag1&=~0x01; /* disable cw() execution */
          ccw_n = n;    /* reload step number to ccw counter */
          flag1 |=0x02; /* enable cww() execution */
          }
       }
         
}

ccw(){
       if((flag1&0x02)!=0)
       {
        ccw_n--;       /* decremnet ccw step number */
        if (ccw_n !=0)
         j--;          /* if not zero decrement index j */
         else
         {flag1&=~0x02; /* disable ccw() executon */
          cw_n = n;     /* reload step number to cw counter */
          flag1 |=0x01; /* enable cw() execution */
          }
       }
         
}

tick_wait(){   /* cputick was replaced by simpler ASM code 10ms wait */

    asm" JNB TCON.5,*";   /* wait for TF0 set */
    asm" CLR TCON.5";     /* clear TF0 for further set */
    asm" ORL TH0,#$DC";   /* reload TH0 with $DC, TL0 = 0 */
}

energize(){

    P1 = step[(j&0x07)];  /* only step 0-7 needed */
}
