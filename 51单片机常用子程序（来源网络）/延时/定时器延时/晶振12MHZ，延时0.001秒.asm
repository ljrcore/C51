; ����12MHZ����ʱ0.001��,��ʽ1




  DELAY:CLR     EX0               ;����12MHZ����ʱ0.001��
        MOV     TMOD,#01H
        MOV     TL0,#18H
        MOV     TH0,#0FCH
        SETB    TR0
   HERE:JBC     TF0,NEXT1
        SJMP    HERE
  NEXT1:CLR     TR0 
        SETB    EX0
        RET