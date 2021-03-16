	ORG	0000H
	AJMP	MAIN
	ORG	0003H
	AJMP	SEVER
	ORG	0030H
  MAIN:ADDR8279_1 EQU    0BFFFH
       ADDR8279_2 EQU    0BFFEH
  
       MOV      DPTR,#ADDR8279_1
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
	   CLR 00H
	   CLR 01H
	    
	   MOV 60H,#05H      ;起始5秒
	   MOV 61H,#05H    ; ;；5秒显示
	   MOV 62H,#14H      ;20秒
	   MOV 63H,#20H     ;；20秒显示
	   MOV 64H,#03H     ;；3秒
	   MOV 65H,#03H     ;；3秒显示 
	   MOV 66H,#0AH     ; ；10秒
	   MOV 67H,#10H     ; ；10秒显示
	    
 MAIN1:LCALL  SEACH1 
       AJMP   START             ;; JBC  00H,START 
	   AJMP MAIN1   
 START:MOV     34H,61H
       MOV	R2,60H
       MOV     R0,#0FH
	   LCALL	PTFO1
    S1:MOV     34H,63H
	   MOV	R0,#96H
	   MOV	R2,62H
       LCALL   PTFO1
         
        MOV     R2,64H
        MOV     34H,65H
        MOV     35H,#9FH
        MOV     36H,#06H
        LCALL   PTFO2

        MOV     R2,62H
        MOV     34H,63H
        MOV     R0,#69H
        LCALL   PTFO1

        MOV     R2,64H
        MOV     34H,65H
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
        MOV   34H,67H
	    MOV   P1,#0FH
        MOV   R6,66H
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
        MOV      DPTR,#ADDR8279_1   
        MOVX     A,@DPTR
        ANL A,#07H
        JZ  NEXT1  
        LCALL  KEY
        JBC  01H,NEXT11 
 NEXT1: DJNZ    R2,PTFO1
        RET
 NEXT11:LCALL  SEACH1
        JBC 00H,NEXT1 
        SJMP NEXT11          
  PTFO2:MOV     R0,35H
        MOV     P1,R0
        LCALL   PTFO3
        LCALL   LED
        LCALL   DELAY1
        MOV     R0,36H
        MOV     P1,R0
        LCALL   DELAY1
        MOV      DPTR,#ADDR8279_1   
        MOVX     A,@DPTR
        ANL A,#07H
        JZ  NEXT2  
        LCALL  KEY
        JBC 01H,NEXT12 
 NEXT2: DJNZ    R2,PTFO2
        RET
 NEXT12:LCALL  SEACH1
        JBC 00H,NEXT2
        SJMP NEXT12          
 DELAY1:MOV     R7,#0AH
        AJMP    DELAY
 DELAY2:MOV     R7,#14H
  DELAY:CLR     EX0
        MOV     TMOD,#01H
        MOV     TL0,#00H
        MOV     TH0,#4CH
        SETB    TR0
   HERE:JBC     TF0,NEXT13
        SJMP    HERE
  NEXT13:MOV     TL0,#00H
         MOV     TH0,#4CH
         DJNZ    R7,HERE
         CLR     TR0
         SETB    EX0
         RET
  
   LED:MOV      DPTR,#ADDR8279_1
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
       
KEY:MOV  DPTR ,#ADDR8279_1
	MOV  A,#40H
	MOVX @DPTR,A
	MOV DPTR,#ADDR8279_2
	MOVX A,@DPTR
	ANL A,#3FH
        
    CJNE A,#0AH,KEY1
    SETB 00H
    AJMP RETUN 
     


KEY1:CJNE A,#0BH,KEY2
     SETB 01H
     AJMP RETUN 
   
KEY2:CJNE A,#0CH,KEY3
     ACALL SEACH2
     MOV DPTR ,#ADDR8279_2
     MOVX A,@DPTR
     ANL A,#3FH
     CJNE A,#09H,ERROR1
ERROR1:JC NEXT3
        MOV 61H,#05H
        AJMP RETUN
  NEXT3:SWAP A   
        MOV 61H,A
        ACALL SEACH2
        MOV DPTR, #ADDR8279_2
       	MOVX A,@DPTR 
        ANL A,#3FH
        CJNE A,#09H,ERROR2
   ERROR2:JC   NEXT4 
        MOV 61H,#05H
        AJMP RETUN
  NEXT4:ORL 61H,A 
        MOV A,61H
        LCALL BCDH
        MOV 60H,A 
        AJMP RETUN 
           
 KEY3:CJNE A,#0DH,KEY4
     ACALL SEACH2
     MOV DPTR, #ADDR8279_2
     MOVX A,@DPTR
     ANL A,#3FH
     CJNE A,#09H,ERROR3
ERROR3:JC NEXT5
        MOV 63H,#20H
        AJMP RETUN
  NEXT5:SWAP A   
        MOV 63H,A
        ACALL SEACH2
        MOV DPTR ,#ADDR8279_2
       	MOVX A,@DPTR 
        ANL A,#3FH
        CJNE A,#09H,ERROR4
 ERROR4:JC   NEXT6 
        MOV 63H,#20H
        AJMP RETUN
  NEXT6:ORL 63H,A 
        MOV A,63H
        LCALL BCDH
        MOV 62H,A 
        AJMP RETUN   
        
 KEY4:CJNE A,#0EH,KEY5
     ACALL SEACH2
     MOV DPTR ,#ADDR8279_2
     MOVX A,@DPTR
     ANL A,#3FH
     CJNE A,#09H,ERROR5
ERROR5:JC NEXT7
        MOV 65H,#03H
        AJMP RETUN
  NEXT7:SWAP A   
        MOV 65H,A
        ACALL SEACH2
        MOV DPTR ,#ADDR8279_2
       	MOVX A,@DPTR 
        ANL A,#3FH
        CJNE A,#09H,ERROR6
  ERROR6:JC   NEXT8 
        MOV 65H,#03H
        AJMP RETUN
  NEXT8:ORL 65H,A 
        MOV A,65H
        LCALL BCDH
        MOV 64H,A 
        AJMP RETUN 
        
 KEY5:CJNE A,#0FH,RETUN 
     ACALL SEACH2
     MOV DPTR ,#ADDR8279_2
     MOVX A,@DPTR
     ANL A,#3FH
     CJNE A,#09H,ERROR7
ERROR7:JC NEXT9
        MOV 67H,#10H
        AJMP RETUN
  NEXT9:SWAP A   
        MOV 67H,A
        ACALL SEACH2
        MOV DPTR, #ADDR8279_2
       	MOVX A,@DPTR 
        ANL A,#3FH
        CJNE A,#09H,ERROR8
ERROR8:JC   NEXT10
        MOV 67H,#10H
        AJMP RETUN
  NEXT10:ORL 67H,A 
        MOV A,67H
        LCALL BCDH
        MOV 66H,A 
        AJMP RETUN                       
 RETUN: RET
      
  
SEACH1:MOV      DPTR,#ADDR8279_1   
       MOVX     A,@DPTR
       ANL A,#07H
       JZ  RETUN1  
       LJMP KEY
RETUN1:RET 
SEACH2:MOV      DPTR,#ADDR8279_1   
       MOVX     A,@DPTR
       ANL A,#07H
       JNZ  RETUN3
       SJMP SEACH2
RETUN3:RET     
    ;;（２０）标号：ＢＣＤＨ    功能：单字节ＢＣＤ码整数转换成单字节十六进制整数

;;入口条件：待转换的单字节ＢＣＤ码整数在累加器A中。
;;;出口信息：转换后的单字节十六进制整数仍在累加器A中。
;;;;;影响资源：PSW、A、B、R4    堆栈需求：  ２字节

BCDH:	MOV	B,#10H	;;；分离十位和个位
	DIV	AB
	MOV	R4,B	;;；暂存个位
	MOV	B,#10	;;;；将十位转换成十六进制
	MUL	AB
	ADD	A,R4	;;;;;；按十六进制加上个位
	RET

       
END                             