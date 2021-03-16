 ORG   0000H
 AJMP MAIN
 ORG  0030H
MAIN:
      WORDADRR EQU   30H          ;WORDADRR EQU   30H
      DATEADDR EQU   30H
      MOV A,#01H
      MOV R7,#08H
      MOV R1,#30H
  KK:    MOV @R1,A
      INC A
      INC R1
      DJNZ R7,KK
     ACALL WRITE

      MOV 72H,#100
LOOP3:MOV 71H,#100
LOOP1:MOV 70H,#47
LOOP0:DJNZ 70H,LOOP0
      NOP
      DJNZ 71H,LOOP1
      MOV 70H,#46
LOOP2:DJNZ 70H,LOOP2
      NOP
      DJNZ 72H,LOOP3
      MOV 70H,#48
LOOP4:DJNZ 70H,LOOP4


     ACALL READ_8
     LJMP RETURN



  WRITE:ACALL     STA   ;8字节发送
      MOV A,#0A0H
      ACALL SLA8
      ACALL CACK
      JNB  ACC.1 ,PP1
      LJMP ERR

 PP1: MOV  A,#WORDADRR
     ACALL   SLA8
     ACALL   CACK
      JNB  ACC.1,PP2
      LJMP    ERR
   PP2:MOV R0,#DATEADDR
       MOV R6,#08H
   PP4: MOV A,@R0
      ACALL SLA8
      ACALL CACK
      JNB  ACC.1,PP3
      LJMP ERR
   PP3:INC R0
      DJNZ R6,PP4
      ACALL   STOP
RET

READ_8:ACALL STA          ;序列读8字节
       MOV A,#0A0H
       ACALL SLA8
       ACALL CACK
        JNB  ACC.1,PP5
      LJMP ERR
   PP5:MOV A,#WORDADRR
      ACALL SLA8
      ACALL  CACK
       JNB  ACC.1,PP6
      LJMP ERR
   PP6:ACALL STA
      MOV A,#0A1H
      ACALL  SLA8
      ACALL  CACK
       JNB  ACC.1,PP7
      LJMP ERR
   PP7: MOV R0,#40H
       MOV R6,#07H
  PP9:     ACALL RLA8

      MOV @R0 ,A
      
     

      ACALL MACK
      
     ;  JNB  ACC.1,PP8
     ; LJMP ERR
    PP8: INC R0
        DJNZ R6,PP9
       ACALL RLA8
        MOV @R0 ,A
        ACALL MNACK
        ACALL STOP
        RET

SLA8:	MOV R7,#08H      ;发送8 位
BACK:  
        RLC		A
	JC		NEXT
	ACALL	MACK
        AJMP    LOOP23
NEXT:	ACALL	MNACK
LOOP23:	DJNZ	R7,BACK
	RET


RLA8:	MOV R7,#08H
             ;接收8位
 BACK1: SETB  P1.1
        SETB  P1.0
        NOP
        NOP
        NOP
        NOP
        MOV C,P1.1
 	  RLC 		A
          CLR P1.0

       DJNZ	R7,BACK1
       ;CLR   P1.0
       RET


STA:	SETB	P1.1          ; ；启动
	SETB	P1.0
	NOP
	NOP
	NOP
	NOP
	CLR		P1.1
	NOP
	NOP
	NOP
	NOP
	CLR 	P1.0
	RET

STOP:	CLR		P1.1     ;停止
	SETB		P1.0
	NOP
	NOP
	NOP
	NOP
	SETB	P1.1
	NOP
	NOP
	NOP
	NOP
	NOP
	CLR		P1.1
	CLR		P1.0
	RET

CACK:
     SETB P1.1       ;接收应答信号
     SETB P1.0
     NOP
     NOP
     NOP
     NOP
     NOP
     MOV A,P1
    JNB ACC.1,CEND
     AJMP CACK
 CEND:CLR P1.0
      NOP
      RET

MACK:	CLR		P1.1     ;发0/应答位
	SETB	P1.0
	NOP
	NOP
	NOP
	NOP
	CLR		P1.0
	SETB 		P1.1
	RET

MNACK:	SETB	P1.1      ; ；发1/非应答信号
	SETB	P1.0
	NOP
	NOP
	NOP
	NOP
	CLR		P1.0
	CLR		P1.1
	RET
ERR:AJMP RETURN
RETURN:
       END
