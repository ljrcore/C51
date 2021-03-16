 ADDR8279_1 EQU    0FF82H   ;8279命令\状态口
 ADDR8279_2 EQU    0FF80H    ;8279数据口
 
 
 
 
 
  LED:MOV      DPTR,#ADDR8279_1
       MOV      A,#0D1H
       MOVX     @DPTR,A
  WAIT:MOVX     A,@DPTR
       JB       ACC.7,WAIT
       MOV      A,#00H
       MOVX     @DPTR,A
       MOV      A,#2CH
       MOVX     @DPTR,A

     
     
       MOV      DPTR,#ADDR8279_1
       MOV      A,#90H
       MOVX      @DPTR,A
       MOV      R1,#30H
       MOV      R7,#02H
       MOV      DPTR,#ADDR8279_2
  LOOP:MOV      A,@R1
       ADD      A,#05H
       MOVC     A,@A+PC
       MOVX     @DPTR,A
       INC      R1
       DJNZ     R7,LOOP
       RET
       DB       3FH,06H,5BH,4FH,66H,6DH
       DB       7DH,07H,7FH,6FH 
 PTFO3:MOV      A, 34H
       CLR      C
       SUBB     A,#01H
       JNB      PSW.6,NEXT
       CLR      C
       SUBB     A,#06H
  NEXT:MOV      34H,A
       ANL      A,#0FH
       MOV      30H,A
       MOV      A,34H
       ANL      A,#0F0H
       SWAP     A
       MOV     31H,A
       RET     
  END                             