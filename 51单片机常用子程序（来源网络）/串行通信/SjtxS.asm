	ORG		0000H
	AJMP	START
	ORG 	0023H
	AJMP	TO_INTSE
	ORG		0030H
START:	MOV 	TMOD,#20H
	MOV 	TL1,#0FDH
	MOV 	TH1,#0FDH
	SETB 	TR1
		
	MOV PCON,#00H
    MOV SCON,#10010000B
    
    MOV R7,#07H
    MOV R1,#40H
    MOV @R1,#01H
LP:	INC	R1 
	MOV @R1,#01H
    DJNZ R7,LP 
    MOV R1,#40H
    MOV R0,#00H
    SETB EA
    SETB ES
    MOVX A,@R1 
    ADD A,#00H
   	MOV C,P
    MOV TB8,C
    MOV SBUF,A
W_MAINA:SJMP W_MAINA
TO_INTSE:JB SCON.0,TO_LOOP
          CLR SCON.1
          SJMP TO_ENDT
TO_LOOP:	CLR SCON.0
          MOV A,SBUF
          SUBB A,#01H
          JC LOOP3
          MOVX A,@R1 
          ADD A,#00H
          MOV C,P
          MOV TB8,C
          MOV SBUF,A
          MOV SBUF,A
          SJMP TO_ENDT
    LOOP3:INC R1
          INC R0
          MOVX A,@R1
          ADD A,#00H
          MOV C,P
          MOV TB8,C
          MOV SBUF,A
          CJNE R0,#08H,TO_ENDT
          CLR ES
   TO_END:RETI       
   END       
	
	
	
	