; æß’Ò12MHZ£¨—” ±0.01√Î,∑Ω Ω1




  DELAY:CLR     EX0               ;æß’Ò12MHZ£¨—” ±0.01√Î
        MOV     TMOD,#01H
        MOV     TL0,#0D8H
        MOV     TH0,#0F0H
        SETB    TR0
   HERE:JBC     TF0,NEXT1
        SJMP    HERE
  NEXT1:CLR     TR0 
        SETB    EX0
        RET