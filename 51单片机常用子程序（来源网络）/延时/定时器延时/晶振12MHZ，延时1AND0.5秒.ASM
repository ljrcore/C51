; æß’Ò12MHZ£¨—” ±1√Î,∑Ω Ω1



DELAY1:MOV     R7,#0AH      ;; æß’Ò12MHZ£¨—” ±0.5√Î
        AJMP    DELAY
 DELAY2:MOV     R7,#14H      ;; æß’Ò12MHZ£¨—” ±1√Î
  DELAY:CLR     EX0
        MOV     TMOD,#01H
        MOV     TL0,#0B0H
        MOV     TH0,#3CH
        SETB    TR0
   HERE:JBC     TF0,NEXT1
        SJMP    HERE
  NEXT1:MOV     TL0,#0B0H
        MOV     TH0,#3CH
        DJNZ    R7,HERE
        CLR     TR0
        SETB    EX0
        RET