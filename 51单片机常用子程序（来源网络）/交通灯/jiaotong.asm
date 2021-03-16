	ORG	0000H
	AJMP	MAIN
	ORG	0003H
	AJMP	SEVER
	ORG	0030H
  MAIN:MOV      DPTR,#0FF82H
       MOV      A,#0D1H
       MOVX     @DPTR,A
  WAIT:MOVX     A,@DPTR
       JB       ACC.7,WAIT
       MOV      A,#00H
       MOVX     @DPTR,A
       MOV      A,#2CH
       MOVX     @DPTR,A
   
        SETB	EA
	    SETB	EX0
	    CLR	IT0
        MOV     34H,#00000101B
        MOV	R2,#05H
        MOV     R0,#0FH
	    LCALL	PTFO1
     S1:MOV     34H,#00100000B
	    MOV	R0,#96H
	    MOV	R2,#14H
        LCALL   PTFO1

        MOV     R2,#03H
        MOV     34H,#00000011B
        MOV     35H,#9FH
        MOV     36H,#06H
        LCALL   PTFO2

        MOV     R2,#14H
        MOV     34H,#00100000B
        MOV     R0,#69H
        LCALL   PTFO1

        MOV     R2,#03H
        MOV     34H,#00000011B
        MOV     35H,#6FH
        MOV     36H,#09H
        LCALL   PTFO2
        AJMP    S1
  SEVER:CLR   EX0
        PUSH  34H
        PUSH  30H
        PUSH  31H
        PUSH  PSW
        PUSH  DPH
        PUSH  DPL
        MOV   40H,A
        MOV   41H,R7
        MOV   42H,R1 
        MOV   34H,#00010000B
	    MOV   P1,#0FH
        MOV   R6,#0AH
  LAST1:LCALL PTFO3
        LCALL LED  
        LCALL DELAY2
    	DJNZ R6,LAST1
        MOV     P1,R0
        MOV A,40H
        MOV R7,41H
        MOV R1,42H
        POP  DPL
        POP  DPH
        POP  PSW
        POP  31H
        POP  30H
        POP  34H 
        SETB EX0
        RETI
  
  PTFO1:MOV     P1,R0
        LCALL   PTFO3
        LCALL   LED
        LCALL   DELAY2
        DJNZ    R2,PTFO1
        RET
  PTFO2:MOV     R0,35H
        MOV     P1,R0
        LCALL   PTFO3
        LCALL   LED
        LCALL   DELAY1
        MOV     R0,36H
        MOV     P1,R0
        LCALL   DELAY1
        DJNZ    R2,PTFO2
        RET
 DELAY1:MOV     R7,#0AH
        AJMP    DELAY
 DELAY2:MOV     R7,#14H
  DELAY:CLR     EX0
        MOV     TMOD,#01H
        MOV     TL0,#00H
        MOV     TH0,#4CH
        SETB    TR0
   HERE:JBC     TF0,NEXT1
        SJMP    HERE
  NEXT1:MOV     TL0,#00H
        MOV     TH0,#4CH
        DJNZ    R7,HERE
        CLR     TR0
        SETB    EX0
        RET
  
   LED:MOV      DPTR,#0FF82H
       MOV      A,#90H
       MOVX      @DPTR,A
       MOV      R1,#30H
       MOV      R7,#02H
       MOV      DPTR,#0FF80H
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