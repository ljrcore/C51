  ORG 0000H
      AJMP MAIN
      ORG  0030H
 MAIN:MOV     30H,#00H
      MOV     31H,#00H
      MOV     32H,#00H
      MOV     TMOD,#15H
      MOV     TL0,#00H
      MOV     TH0,#00H
      MOV     TL1,#00H
      MOV     TH1,#4CH      
      MOV     R7,#14H
      SETB TR1
      SETB TR0  
HERE:JBC     TF1,NEXT1
      SJMP    HERE
NEXT1:MOV     TL1,#00H
      MOV     TH1,#4CH
      DJNZ    R7,HERE
      CLR     TR0
      CLR     TR1

	  MOV R6,TH0
      MOV R7,TL0
 
      LCALL  HB2
      MOV    30H,R3
      MOV    31H,R4
      MOV    32H,R5
      LCALL TRANS
      LCALL DIR
      AJMP MAIN
         


HB2:CLR	A	
	MOV	R3,A
	MOV	R4,A
	MOV	R5,A
	MOV	R2,#10H	
HB3:MOV	A,R7	
	RLC	A
	MOV	R7,A
	MOV	A,R6
	RLC	A
	MOV	R6,A
	MOV	A,R5	
	ADDC	A,R5
	DA	A	
	MOV	R5,A
	MOV	A,R4
	ADDC	A,R4
	DA	A
	MOV	R4,A
	MOV	A,R3
	ADDC	A,R3
	MOV	R3,A	
	DJNZ	R2,HB3    
	RET
	
TRANS: MOV R0,#32H
       MOV R1,#40H
       MOV R6,#03H
  LAST:MOV      A,@R0
       ANL      A,#0FH
       MOV      @R1,A
       MOV      A,@R0
       ANL      A,#0F0H
       SWAP     A
       INC  R1
       MOV      @R1,A
       INC  R1
       DEC R0
       DJNZ R6,LAST
       RET
 
  DIR:MOV      DPTR,#0FF82H
       MOV      A,#0D1H
       MOVX     @DPTR,A
  LP:	MOVX     A,@DPTR
       JB       ACC.7,LP
       MOV      A,#00H
       MOVX     @DPTR,A
       MOV      A,#2AH
       MOVX     @DPTR,A

       MOV      DPTR,#0FF82H
       MOV      A,#90H
       MOVX      @DPTR,A
       MOV      R1,#40H
       MOV      R7,#06H
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

END