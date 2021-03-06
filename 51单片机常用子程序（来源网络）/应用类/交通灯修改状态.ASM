	ORG 0000H
	AJMP MAIN
	ORG 0003H
	AJMP INT_1 
	ORG 0030H
 MAIN:	MOV 30H,#14H
	MOV DPTR,#0FF82H
	MOV A,#0D1H
	MOVX @DPTR,A
WAIT:	MOVX A,@DPTR
	JB ACC.7,WAIT
	MOV A,#00H
	MOVX @DPTR,A
	MOV A,#2AH
	SETB EA
	SETB EX0
	CLR IT0
LP1:     MOV DPTR,#0FF82H
	MOVX A,@DPTR
	ANL A,#3FH
	JZ LP1	
	LCALL KEY
  	SJMP LP1
	
START:	MOV R0,#0FH
	MOV P1,R0
	MOV R2,#05H
 LOOP1: LCALL HBCD
	LCALL DISP
	LCALL DELAY1
	LCALL DELAY1
	DJNZ R2,LOOP1
	LCALL HBCD
	LCALL DISP

 NEXT:	MOV R0,#96H
	MOV P1,R0
	MOV R2,#14H
 LOOP2: LCALL HBCD
	LCALL DISP
	LCALL DELAY2
	DJNZ R2,LOOP2
	
	MOV R2,#03H
  SUN1:	MOV R0,#06H
	MOV P1,R0
	LCALL HBCD
	LCALL DISP	
	LCALL DELAY1
	MOV R0,#9FH
	MOV P1,R0
	LCALL DELAY1
	DJNZ R2,SUN1
	MOV R0,#69H
	MOV P1,R0
	MOV R2,#14H
  LOOP3:LCALL DELAY1
	DJNZ R2,LOOP3
	MOV R2,#03H
  SUN2:	MOV R0,#09H
	MOV P1,R0
	LCALL DELAY1
	MOV R0,#06FH
	MOV P1,R0
	LCALL DELAY1
	DJNZ R2,SUN2
	AJMP NEXT


DELAY1: MOV R7,#65H
  DEL1: MOV R6,#46H
  DEL2: MOV R5,#1FH
  DEL3: DJNZ R5,DEL3
	DJNZ R6,DEL2
	DJNZ R7,DEL1
	RET

DELAY2:	MOV R7,#20
	MOV TMOD,#01H
	MOV TL0,#00H
	MOV TH0,#4CH
	SETB TR0
 LAST:	JBC TF0,NEXT1
	SJMP LAST
 NEXT1:	MOV DPTR,#0FF82H
	MOVX A,@DPTR
	ANL A,#07H
	JNZ KEY
	MOV TL0,#00H
	MOV TH0,#4CH
	DJNZ R7,LAST
	CLR TR0
	RET
 
INT_1:	PUSH 2
	PUSH P1
	MOV P1,#0FH
	MOV R2,#0AH
 INT1:	LCALL DELAY1
	DJNZ R2,INT1
	POP P1
	POP 2
	RETI

SEEK:MOV DPTR,#0FF82H
	MOVX A,@DPTR
	ANL A,#3FH
	JZ SEEK
	RET

KEY:    
	LCALL GETKEY
	CJNE A,#0AH,KEY1
	LJMP START
KEY1:   CJNE A,#0BH,KEY2
	LJMP LP1
KEY2:   CJNE A,#0CH,RETURN1
        LCALL SEEK
	LCALL KEY
       CJNE A,#0AH,PTF1
   PTF1:JC NEXT2
        MOV 30H,#00H
        AJMP RETURN1
  NEXT2:SWAP A   
        MOV 30H,A
	LCALL SEEK
	LCALL KEY
        CJNE A,#0AH,PTF2
   PTF2:JC NEXT3
        MOV 30H,#00H
        AJMP RETURN1  
   NEXT3:ORL A,30H
	LCALL BCDH1
RETURN1: RET

GETKEY: MOV A,#40H
      	MOV DPTR,#0FF82H
	MOVX @DPTR,A
	MOV DPTR,#0FF80H
	MOVX A,@DPTR
	ANL A,#3FH
	RET

 BCDH1: MOV B,#10H
	DIV AB
	SWAP A
	MOV 30H,B
	ORL 30H,A
	RET

HBCD:   PUSH ACC
	MOV A,R2
	MOV B,#10
	DIV AB
	MOV 70H,A
	MOV A,B
	MOV 71H,A
	POP ACC
	RET

DISP:	MOV DPTR,#0FF82H
	MOV A,#09H
	MOVX @DPTR,A
	MOV R0,#70H
	MOV R7,#02H
	MOV DPTR,#0FF80H
 LOOP4: MOV A,@R0
	ADD A,#05H
	MOVC A,@A+PC
	MOVX @DPTR,A
	INC R0
	DJNZ R7,LOOP4
	RET
        DB       3FH,06H,5BH,4FH,66H,6DH
        DB       7DH,07H,7FH,6FH 
	END