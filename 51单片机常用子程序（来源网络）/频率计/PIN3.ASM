       ORG 0000H
       AJMP MAIN
       ORG  0030H
      
 MAIN:ADDR8279_1 EQU    0BFFFH
      ADDR8279_2 EQU    0BFFEH
 
       MOV      DPTR,#ADDR8279_1
       MOV      A,#0D1H
       MOVX     @DPTR,A
 WAIT1:MOVX     A,@DPTR
       JB       ACC.7,WAIT1
       MOV      A,#00H
       MOVX     @DPTR,A
       MOV      A,#2CH
       MOVX     @DPTR,A

       MOV     TMOD,#05H
   KAI:MOV     TL0,#00H
       MOV     TH0,#00H
      
  KAI1:SETB P1.0
       JB P1.0,KAI2
       SJMP KAI1          
  KAI2:SETB TR0
       SETB P1.0 
       JNB P1.0,PINYU 
       SJMP KAI2
 PINYU:CLR TR0 
       MOV R6,TH0
       MOV R7,TL0
       LCALL  HB2
       MOV 60H,R3
       MOV 61H,R4
       MOV 62H,R5
       LCALL   TRANS
       LCALL   LED
       AJMP KAI    
  
                      
;;;入口条件：待转换的双字节十六进制整数在R6、R7中。
;;出口信息：转换后的三字节ＢＣＤ码整数在R3、R4、R5中。
;;影响资源：PSW、A、R2～R7    堆栈需求：  ２字节

HB2:CLR	A	;;；ＢＣＤ码初始化
	MOV	R3,A
	MOV	R4,A
	MOV	R5,A
	MOV	R2,#10H	;;；转换双字节十六进制整数
HB3:MOV	A,R7	;;；从高端移出待转换数的一位到CY中
	RLC	A
	MOV	R7,A
	MOV	A,R6
	RLC	A
	MOV	R6,A
	MOV	A,R5	;;；ＢＣＤ码带进位自身相加，相当于乘２
	ADDC	A,R5
	DA	A	;;；十进制调整
	MOV	R5,A
	MOV	A,R4
	ADDC	A,R4
	DA	A
	MOV	R4,A
	MOV	A,R3
	ADDC	A,R3
	MOV	R3,A	;;；双字节十六进制数的万位数不超过６，不用调整
	DJNZ	R2,HB3    ;;	；处理完１６ｂｉｔ
	RET
	
TRANS: MOV R0,#62H
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
       
      
      
      
      
   LED:MOV      DPTR,#ADDR8279_1
       MOV      A,#90H
       MOVX      @DPTR,A
       MOV      R1,#40H
       MOV      R7,#06H
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
      END