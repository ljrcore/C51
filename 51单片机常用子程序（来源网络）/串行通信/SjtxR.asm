	ORG		0000H
	AJMP	MAIN 
	ORG 	0023H
	AJMP	TO_INTR
	ORG		0030H
MAIN:	MOV	DPTR,#0FF82H
	MOV 	A,#0D1H
	MOVX 	@DPTR,A
DEN:	MOVX 	A,@DPTR
	JB 	ACC.7,DEN 
	MOV 	A,#00H
	MOVX 	@DPTR,A
	MOV 	A,#2AH
	MOVX 	@DPTR,A
	
	MOV 	TMOD,#20H
	MOV 	TL1,#0FDH
	MOV 	TH1,#0FDH
	SETB 	TR1
		
	MOV PCON,#00H
    MOV SCON,#10010000B
    MOV R1,#50H
    MOV R0,#00H
    SETB EA
    SETB ES 
    
    W_MAIN_B:SJMP   W_MAIN_B
 TO_INTR:JB SCON.0,TO_LOOPR
           CLR SCON.1
           SJMP TO_ENDTR
  TO_LOOPR:CLR SCON.0
           MOV A,SBUF
           ADD A,#00H
           MOV C,P
           JC TO_LOOP1
           ORL C,RB8
           JC TO_LOOP2
           SJMP TO_LOOP3
  TO_LOOP1:ANL C ,RB8
           JC TO_LOOP3
  TO_LOOP2:MOV A,#0FFH
           MOV SBUF,A
           SJMP TO_ENDTR
  TO_LOOP3:MOVX @R1,A
           MOV A,00H
           MOV SBUF,A
           INC R0
           INC R1 
           CJNE R0,#08H,TO_ENDTR
           CLR  ES
  TO_ENDTR:ACALL 	DISP 
  	RETI            
disp:	MOV 	DPTR,#0FF82H
	MOV 	A,#90H
	MOVX 	@DPTR,A
	MOV 	R0,#50H
	MOV 	R5,#08H
	MOV 	DPTR,#0FF80H
DL0:	MOV 	A,@R0
	ADD 	A,#05H 
	MOVC 	A,@A+PC
	MOVX 	@DPTR,A 
	INC 	R0
	DJNZ 	R5,DL0
	RET
TAB:	DB 3FH,06H,5BH,4FH,66H
	DB 6DH,7DH,07H,7FH,6FH
    END 