; ����12MHZ����ʱ0.01��,��ʽ1




  DELAY:CLR     EX0               ;����12MHZ����ʱ0.01��
        MOV     TMOD,#01H
        MOV     TL0,#0D8H
        MOV     TH0,#0F0H
        SETB    TR0
   HERE:JBC     TF0,NEXT1
        SJMP    HERE
  NEXT1:CLR     TR0 
        SETB    EX0
        RET