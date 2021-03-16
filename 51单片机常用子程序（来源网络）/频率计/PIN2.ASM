      ORG 0000H
      AJMP MAIN
      ORG  0030H
 MAIN:ADDR8279_1 EQU    0BFFFH
       ADDR8279_2 EQU    0BFFEH
 
      MOV     60H,#00H
      MOV     61H,#00H
      MOV     62H,#00H
      MOV     TMOD,#15H
      MOV     TL0,#00H
      MOV     TH0,#00H
         
      MOV     R7,#14H
      
      MOV     TL1,#00H
      MOV     TH1,#4CH
      SETB TR1
      SETB TR0  
 HERE:JBC     TF1,NEXT1
      SJMP    HERE
NEXT1:MOV     TL1,#00H
      MOV     TH1,#4CH
      DJNZ    R7,HERE
      CLR     TR0
      CLR     TR1
      AJMP    PINYU
PINYU:MOV R6,TH0
      MOV R7,TL0
      JNB TF0 ,NEXT2
      MOV 60H,#06H
      MOV 61H,#55H
      MOV 62H,#36H     
      CLR TF0
 
NEXT2:LCALL  HB2
      MOV    R7,#03H
      MOV    65H,R3
      MOV    66H,R4
      MOV    67H,R5
      MOV    R0,#60H
      MOV    R1,#65H
      LCALL BCDA 
      LCALL TRANS
      LCALL LED
      AJMP MAIN
          

  ;;（１）  标号：  ＢＣＤＡ    功能：多字节ＢＣＤ码加法

;;入口条件：字节数在R7中，被加数在[R0]中，加数在[R1]中。
;;出口信息：和在[R0]中，最高位进位在CY中。
;;;影响资源：PSW、A、R2    堆栈需求：  ２字节

BCDA:	MOV	A,R7	;;；取字节数至R2中
	MOV	R2,A
	ADD	A,R0	;;；初始化数据指针
	MOV	R0,A
	MOV	A,R2
	ADD	A,R1
	MOV	R1,A
	CLR	C
BCD1:	DEC	R0	;;；调整数据指针
	DEC	R1
	MOV	A,@R0
	ADDC	A,@R1	;;；按字节相加
	DA	A	;;；十进制调整
	MOV	@R0,A	;;；和存回[R0]中
	DJNZ	R2,BCD1	;;；处理完所有字节
	RET






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