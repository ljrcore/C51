       ORG 0000H
       AJMP MAIN
       ORG 0030H
  MAIN:
       ADDR8279_1 EQU    0BFFFH
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
       
       CLR 00H 
       CLR 01H
CHAXUN:LCALL SEACH 
       JBC 00H,MAIN1 
       SJMP CHAXUN 
 MAIN1:SETB IT1
       SETB EA
       SETB EX1
ADC0809:MOV DPTR,#8100H     ;；ADC0809首址
       MOVX @DPTR,A        ;；启动AD转换
  HERE:SETB P1.0
       JNB  P1.0,SEVER1  
       SJMP HERE
SEVER1:MOVX A,@DPTR
       MOV R3,A
       MOV DPTR ,#8000H    ;D/A口地址 
       MOVX @DPTR,A  
       MOV R2,#00H
       MOV R7,#60H
       MOV R6,#09H
       LCALL MULD
       MOV  R7,#0FFH
       LCALL  DV31
       MOV A,R4 
       MOV R6,A 
       MOV A,R5 
       MOV R7,A 
       LCALL HB2
       MOV 35H,R5 
       MOV 34H,R4 
       ACALL TRANS
       LCALL LED
       LCALL SEACH 
       JBC 01H ,NEXT  
       AJMP  ADC0809 
 NEXT:MOV DPTR,#8000H
      MOV A,#00H
      MOVX @DPTR,A
      AJMP MAIN   
   
TRANS: MOV R0,#35H
       MOV R1,#30H
       MOV R6,#02H
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
   
   KEY:MOV  DPTR ,#ADDR8279_1
       MOV  A,#40H
	   MOVX @DPTR,A
	   MOV DPTR,#ADDR8279_2
	   MOVX A,@DPTR
	   ANL A,#3FH

       CJNE A,#0AH,KEY1             
       SETB 00H
       AJMP RETUN    
      
  KEY1:CJNE A,#0BH,RETUN 
       SETB 01H  
 RETUN:RET   
   
 
  
  
  
   ;;; （５）  标号： ＭＵＬＤ    功能：双字节二进制无符号数乘法

;;入口条件：被乘数在R2、R3中，乘数在R6、R7中。
;;出口信息：乘积在R2、R3、R4、R5中。
;;;影响资源：PSW、A、B、R2～R7    堆栈需求：  ２字节

MULD:	MOV	A,R3	;;；计算R3乘R7
	MOV	B,R7
	MUL	AB
	MOV	R4,B         ;;	；暂存部分积
	MOV	R5,A
	MOV	A,R3	  ;; ；计算R3乘R6
	MOV	B,R6
	MUL	AB
	ADD	A,R4	   ;;;；累加部分积
	MOV	R4,A
	CLR	A
	ADDC	A,B
	MOV	R3,A
	MOV	A,R2	;;;；计算R2乘R7
	MOV	B,R7
	MUL	AB
	ADD	A,R4	;;;；累加部分积
	MOV	R4,A
	MOV	A,R3
	ADDC	A,B 
	MOV	R3,A
	CLR	A
	RLC	A
	XCH	A,R2	;;;；计算R2乘R6
	MOV	B,R6
	MUL	AB
	ADD	A,R3	;;;；累加部分积
	MOV	R3,A
	MOV	A,R2
	ADDC	A,B
	MOV	R2,A
	RET
   ;; （９）  标号：  ＤＶ３１    功能：三字节二进制无符号数除以单字节二进制数

;;;入口条件：被除数在R3、R4、R5中，除数在R7中。
;;出口信息：OV=0 时，双字节商在R4、R5中，OV=1 时溢出。
;;影响资源：PSW、A、B、R2～R7    堆栈需求：  ２字节

DV31:	CLR	C
	MOV	A,R3
	SUBB	A,R7
	JC	DV30
	SETB	OV	;;；商溢出
	RET
DV30:	MOV	R2,#10H	      ;;；求R3R4R5／R7－→R4R5
DM23:	CLR	C
	MOV	A,R5
	RLC	A
	MOV	R5,A
	MOV	A,R4
	RLC	A
	MOV	R4,A
	MOV	A,R3
	RLC	A
	MOV	R3,A
	MOV	F0,C
	CLR	C
	SUBB	A,R7
	ANL	C,/F0
	JC	DM24
	MOV	R3,A
	INC	R5
DM24:	DJNZ	R2,DM23
	MOV	A,R3	            ;；四舍五入
	ADD	A,R3
	JC	DM25
	SUBB	A,R7
	JC	DM26
DM25:	INC	R5
	MOV	A,R5
	JNZ	DM26
	INC	R4
DM26:	CLR	OV
	RET            ;;; ；商在R4R5中 
  
 
 ;    （１７）  标号： ＨＢ２   功能：双字节十六进制整数转换成双字节ＢＣＤ码整数

;入口条件：待转换的双字节十六进制整数在R6、R7中。
;出口信息：转换后的三字节ＢＣＤ码整数在R3、R4、R5中。
;;影响资源：PSW、A、R2～R7    堆栈需求：  ２字节

HB2:	CLR	A	    ;；ＢＣＤ码初始化
	MOV	R3,A
	MOV	R4,A
	MOV	R5,A
	MOV	R2,#10H	       ;；转换双字节十六进制整数
HB3:	MOV	A,R7                   ;	；从高端移出待转换数的一位到CY中
	RLC	A
	MOV	R7,A
	MOV	A,R6
	RLC	A
	MOV	R6,A
	MOV	A,R5	               ;；ＢＣＤ码带进位自身相加，相当于乘２
	ADDC	A,R5
	DA	A	                  ;;;;;；十进制调整
	MOV	R5,A
	MOV	A,R4
	ADDC	A,R4
	DA	A
	MOV	R4,A
	MOV	A,R3
	ADDC	A,R3
	MOV	R3,A	                    ;；双字节十六进制数的万位数不超过６，不用调整
	DJNZ	R2,HB3                      ;	；处理完１６ｂｉｔ
	RET 	
   
 
   LED:MOV      DPTR,#ADDR8279_1
       MOV      A,#90H
       MOVX      @DPTR,A
       MOV      R1,#30H
       MOV      R7,#04H
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
SEACH:MOV      DPTR,#ADDR8279_1   
       MOVX     A,@DPTR
       ANL A,#07H
       JZ  RETUN4
       LJMP KEY
RETUN4:RET
END        
                      