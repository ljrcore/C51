; æß’Ò12MHZ£¨—” ±0.05√Î,∑Ω Ω1




  DELAY:CLR     EX0               ;æß’Ò12MHZ£¨—” ±0.05√Î
        MOV     TMOD,#01H
        MOV     TL0,#0B0H
        MOV     TH0,#3CH
        SETB    TR0
   HERE:JBC     TF0,NEXT1
        SJMP    HERE
  NEXT1:
        CLR     TR0
        SETB    EX0
        RET