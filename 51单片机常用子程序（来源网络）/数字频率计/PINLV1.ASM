       ORG 0000H
       AJMP MAIN
       ORG  000BH
       LJMP  SEVER1
       ORG  0030H

 MAIN:
      A8279_1 EQU    0FF82H
      A8279_2 EQU    0FF80H

       MOV      DPTR,#A8279_1                ;8279初始化
       MOV      A,#0D1H
       MOVX     @DPTR,A
 WAIT1:MOVX     A,@DPTR
       JB       ACC.7,WAIT1                       ;
       MOV      A,#00H
       MOVX     @DPTR,A
       MOV      A,#2CH
       MOVX     @DPTR,A

       CLR     00H
       CLR     01H
       CLR	   02H
       CLR     03H
       CLR     04H
       CLR     05H
       CLR     06H
       CLR     07H
       CLR     08H
       CLR     09H


 START:MOV      DPTR,#A8279_1
       MOVX     A,@DPTR
       ANL A,#07H
       JZ  RETUN
       ACALL    KEY
       JBC     00H,MAIN
       JBC     01H,START1
       JBC     02H,START2
       JBC     03H,START3
       JBC     04H,START4
RETUN:AJMP  START
START1:MOV   P1,#0EFH
        LCALL   SEACH1
       JBC     00H,MAIN
       JBC     06H,PINYU61
       JBC     07H,PINYU71
       JBC     08H,PINYU81
       JBC     09H,PINYU91
       AJMP  START1
 PINYU61:LJMP   PINYU6
 PINYU71:LJMP   PINYU7
 PINYU81:LJMP   PINYU8
 PINYU91:LJMP   PINYU9
 START2:MOV  P1,#2FH
         LCALL   SEACH1
        JBC     00H,MAIN
        JBC     06H,ZHOUQI11
        JBC     07H,ZHOUQI21
        JBC     08H,ZHOUQI31
        JBC     09H,RETUN4
 RETUN4:AJMP  START2
 ZHOUQI11:AJMP  ZHOUQI1
 ZHOUQI21:AJMP  ZHOUQI2
 ZHOUQI31:AJMP  ZHOUQI3

 START3:
        LCALL   SEACH1
        JBC    00H ,RETUN16
        LCALL  CEMK
        AJMP    START3
RETUN16:LJMP  MAIN
 START4: LCALL   SEACH1
         JBC    00H ,RETUN15
         LCALL  CEZHANKB
         AJMP    START4
  RETUN15:LJMP   MAIN
PINYU6:LCALL   SEACH1
       JBC   00H ,RETUN11
       MOV  P1,#1EH
       LCALL  ZHQI
       LCALL  PINYU1
       LCALL  TRANS
       LCALL  LED
       AJMP   PINYU6
 RETUN11:AJMP   MAIN
PINYU7:LCALL   SEACH1
       JBC   00H ,RETUN12
       MOV  P1,#1DH
       LCALL  CZS

       LCALL  PINYU2
       LCALL  TRANS
       LCALL   LED
       AJMP    PINYU7
 RETUN12:AJMP   MAIN
PINYU8:LCALL   SEACH1
       JBC   00H ,RETUN13
       MOV  P1,#1BH
       LCALL  CZS
       MOV  35H,#08H
       LCALL  PINYU
       LCALL  TRANS
       LCALL   LED
       AJMP   PINYU8
RETUN13:AJMP   MAIN
PINYU9:LCALL   SEACH1
       JBC   00H ,RETUN14
       MOV  P1,#17H
       LCALL  CZS
       MOV  35H,#32
       LCALL  PINYU
       LCALL  TRANS
       LCALL   LED
       AJMP    PINYU9
 RETUN14:LJMP   MAIN
ZHOUQI1:MOV  P1,#2EH
        LCALL   ZHQI
        LCALL   MUL4
        LCALL   ADD1
        MOV  60H,R2
        MOV  61H,R3
        MOV  62H,R4
        MOV  63H,R5
        LCALL  TRANS
        LCALL   LED
        AJMP   ZHOUQI1
ZHOUQI2:MOV  P1,#2DH
          LCALL   SEACH1
         JBC   00H ,RETUN9
         LCALL  ZHOUQI2_2
         MOV  36H,R3
         MOV  37H,R4
         MOV  38H,R5
         LCALL   HB4      ;转换后的三字节ＢＣＤ码整数在R2,R3、R4、R5中。
         MOV  60H,R2
        MOV  61H,R3
        MOV  62H,R4
        MOV  63H,R5
        LCALL  TRANS
        LCALL   LED
        AJMP   ZHOUQI2
RETUN9:LJMP   MAIN
ZHOUQI3:MOV  P1,#2BH
         LCALL   SEACH1
        JBC   00H ,RETUN10
        LCALL  ZHOUQI2_2
        MOV  36H,R3
        MOV  37H,R4
        MOV  38H,R5
        MOV  R0,#36H
        MOV  R7,#08H            ;分频系数
        LCALL     MULD3_1
        MOV  60H,R2
        MOV  61H,R3
        MOV  62H,R4
        MOV  63H,R5
        LCALL  TRANS
        LCALL   LED
        AJMP    ZHOUQI3
 RETUN10:AJMP   MAIN
ZHOUQI2_2:
        LCALL   CZS
        MOV   A,76H
        ;CJNE   A,#00H,NEXT12
       ;AJMP  NEXT13
        
        LCALL   MUL4
        LCALL   ADD1
        MOV  60H,R2
        MOV  61H,R3
        MOV  62H,R4
        MOV  63H,R5
        CJNE R3,#00H,NEXT14
        MOV   76H,#01H
        MOV   69H,76H
        AJMP   NEXT15
 NEXT14:JC  NEXT15
        MOV 76H,#08H
        MOV 69H,76H
        MOV R7,#08H
        LCALL   DV31         ;双字节商在R4、R5中
         MOV  62H,R4
        MOV  63H,R5
 NEXT15:
        MOV   A,R4
        MOV   R6,A
        MOV   A,R5
        MOV   R7,A

        MOV   R2,#00H
        MOV   R3,#0FH
        MOV   R4,#42H
        MOV   R5,#40H
        LCALL DIVD       ; 双字节商在R2、R3中，OV=1 时溢出
        MOV  62H,R2
        MOV  63H,R3 
        MOV  R6,#00H
        MOV  R7,76H
        JNB  OV,NEXT16
        MOV   R6,62H
        MOV   R7,63H
        MOV   R2,#00H        ;存入10000
        MOV   R3,#00H
        MOV   R4,#27H
        MOV   R5,#10H
        LCALL  DIVD          ; 双字节商在R2、R3中，OV=1 时溢出

NEXT16:MOV  A,69H
       CJNE A,#01H,NEXT32
       AJMP   NEXT33  
 NEXT32:       MOV  R6,#00H
        MOV   R7,#69H
        LCALL  DIVD 
NEXT33:    MOV  R7,#64H
        
        
        MOV  R6,#00H
         
        LCALL  MULD          ;：乘积在R2、R3、R4、R5中。
        RET


 CEMK:  MOV    P1,#4DH
        LCALL  MAIKUAN
        LCALL   HB4     ;转换后的三字节ＢＣＤ码整数在R2,R3、R4、R5中。
        MOV  60H,R2
        MOV  61H,R3
        MOV  62H,R4
        MOV  63H,R5

        LCALL  TRANS
        LCALL   LED
        RET
CEZHANKB:MOV    P1,#8DH
       LCALL   ZHQI
       LCALL   MUL4
       LCALL   ADD1          ; ;结果在R2.R3.R4.R5中
       MOV  70H,R2
       MOV   71H,R3
       MOV   72H,R4
       MOV   73H,R5


       LCALL  MAIKUAN        ;;结果在36,37,38H中
       MOV    R6,37H
       MOV    R7,38H
       MOV    R2,#03H
       MOV    R3,#0E8H
       LCALL   MULD          ; 乘积在R2、R3、R4、R5中。
       MOV    R6,72H
       MOV    R7,73H
       LCALL   DIVD        ; 双字节商在R2、R3中，OV=1 时溢出。
       MOV    R2,72H
       MOV    R3,73H
       MOV   R6,72H
       MOV   R7,73H
       LCALL   HB2        ;转换后的三字节ＢＣＤ码整数在R3、R4、R5中。
       MOV  60H,#00H
       MOV  61H,R3
       MOV  62H,R4
       MOV  63H,R5
       LCALL  TRANS
       LCALL   LED
       RET

KEY:MOV  DPTR ,#A8279_1
	MOV  A,#40H
	MOVX @DPTR,A
	MOV DPTR,#A8279_2
	MOVX A,@DPTR
	ANL A,#3FH

    CJNE A,#00H,KEY1
        SETB 00H
        LJMP RETUN1
   KEY1:CJNE A,#01H,KEY2
        SETB 01H
        LJMP RETUN1
  KEY2:CJNE  A,#02H,KEY3
       SETB  02H
       AJMP  RETUN1
 KEY3:CJNE A,#03H,KEY4
        SETB 03H
        LJMP RETUN1

 KEY4:CJNE A,#04H,KEY5
        SETB 04H
        LJMP RETUN1
  KEY5:CJNE A,#05H,RETUN1
        SETB 05H

 RETUN1:RET
 KEY_1:MOV  DPTR ,#A8279_1
	MOV  A,#40H
	MOVX @DPTR,A
	MOV DPTR,#A8279_2
	MOVX A,@DPTR
	ANL A,#3FH

    CJNE A,#00H,KEY_11
        SETB 00H
        LJMP RETUN2
   KEY_11:CJNE A,#06H,KEY_12
        SETB 06H
        LJMP RETUN2
  KEY_12:CJNE  A,#07H,KEY_13
       SETB  07H
       AJMP  RETUN2
 KEY_13:CJNE A,#08H,KEY_14
        SETB 08H
        LJMP RETUN2

 KEY_14:CJNE A,#09H,RETUN2
        SETB 09H



 RETUN2:RET
		
 ZHQI:                   ;0.1hz_1khz测量,测周期 ;16进制
       MOV     TMOD,#01H
       MOV     TL0,#00H
       MOV     TH0,#00H
       SETB    EA
       SETB    ET0
       MOV  76H,#00H
       SETB    P3.5
    GDP1:   MOV     C,P3.5
       JC     GDP1
   DDP1: MOV   C,P3.5
       JNC  DDP1
       SETB  TR0

 GDP2:   MOV     C,P3.5
       JC     GDP2
   DDP2: MOV   C,P3.5
       JNC  DDP2
       CLR   TR0
       CLR   TR1
       MOV   A,TH0
       MOV   TH1,A
       MOV   A,TL0
       MOV    TL1,A  
       RET

 PINYU1:                 ;0.1hz_1khz测量；结果在让，r4,r5 中 ;16进制
       LCALL   MUL4
       LCALL   ADD1
       MOV   30H,#00H
       MOV   31H,#00H
       MOV   32H,#0FFH
       MOV   33H,#0FFH
       
       LCALL        BIJIAO
       JB    20H,BIJIAO2 
       MOV  34H,R4
       MOV   35H,R5
       MOV  R6,34H
       MOV  R7,35H
       MOV  R2,#00H
       MOV  R3,#0FH
       MOV  R4,#42H
       MOV  R5,#40H
       LCALL DIVD       ; OV=0 时，双字节商在R2、R3中，OV=1 时溢出。
       MOV    A,R2 
       MOV   R6,A
       MOV A,R3 
       MOV R7,A
       AJMP  NEXT30 
BIJIAO2:MOV  30H,#00H
       MOV  31H,#0FH
       MOV  32H,#42H
       MOV  33H,#40H  
       LCALL        BIJIAO  
       JB    20H,BIJIAO3
       MOV  R7,#100
       LCALL   DV31            ;OV=0 时，双字节商在R4、R5中，OV=1 时溢出。
       MOV  34H,R4
       MOV   35H,R5
       MOV  R6,34H
       MOV  R7,35H
       MOV  R2,#00H
       MOV  R3,#0FH
       MOV  R4,#42H
       MOV  R5,#40H
      
       LCALL DIVD       ; OV=0 时，双字节商在R2、R3中，OV=1 时溢出。
       MOV  34H,R2 
       MOV   35H,R3 
       MOV  R6,34H
       MOV  R7,35H
       MOV  R3,#00H
       MOV  R4,34H
       MOV  R5,35H
       MOV  R7,#100
       LCALL  DV31       ;OV=0 时，双字节商在R4、R5中，OV=1 时溢出。
       MOV  34H,R4
       MOV   35H,R5
       MOV  R6,34H
       MOV  R7,35H
       AJMP  NEXT30 
BIJIAO3:
       MOV  R7,#0E8H
       MOV  R6,#03H
       LCALL   DIVD             ; OV=0 时，双字节商在R2、R3中，OV=1 时溢出。
       MOV  34H,R2 
       MOV   35H,R3 
       MOV  R6,34H
       MOV  R7,35H
       MOV  R2,#00H
       MOV  R3,#98H
       MOV  R4,#96H
       MOV  R5,#80H
      
       LCALL DIVD       ; OV=0 时，双字节商在R2、R3中，OV=1 时溢出。
       
       MOV  34H,R2 
       MOV   35H,R3 
       MOV  R6,34H
       MOV  R7,35H
       MOV  R2,#00H
       MOV  R3,#00H
       MOV  R4,34H
       MOV  R5,35H
       MOV  R7,#0E8H
       MOV  R6,#03H
       LCALL  DIVD         ; OV=0 时，双字节商在R2、R3中，OV=1 时溢出。
       
       MOV  34H,R2 
       MOV   35H,R3 
       MOV  R6,34H
       MOV  R7,35H
              
   NEXT30:      LCALL HB2
       MOV 60H,#00H
       MOV 61H,R3
       MOV 62H,R4
       MOV 63H,R5
       CLR   ET0
       RET

 SEVER1:INC 76H
        RETI
CZS:                                         ;测1秒钟的周期数
       MOV     TMOD,#51H
       MOV     TL0,#00H
       MOV     TH0,#4CH
       MOV    76H,#00H
       MOV     R7,#14H

       MOV     TL1,#00H
       MOV     TH1,#00H
       SETB TR1
       SETB TR0
 HERE:JBC     TF0 ,NEXT1
      JBC     TF1,NEXT20 
      SJMP    HERE
NEXT20:INC   76H
       AJMP  HERE
NEXT1:MOV     TL0,#00H
      MOV     TH0,#4CH
      
      DJNZ    R7,HERE
      CLR     TR0
      CLR     TR1
      RET


 PINYU2:                                            ;测频率1k_0.5mhz
      MOV   A,76H
      CJNE   A,#00H,NEXT2
      MOV   65H,#00H
      MOV   66H,#00H
      MOV   67H,#00H
      AJMP  NEXT3
NEXT2:
      MOV  R6,76H
      
      MOV   R0,#65H
      MOV   R7,#03H
      MOV    R1,#50H
      MOV  65H,#00H
      MOV   66H,#00H
      MOV   67H,#00H
NEXT4: MOV   50H,#06H
      MOV   51H,#55H
      MOV   52H,#36H

      LCALL  BCDA
      DJNZ   R6,NEXT4

NEXT3:  MOV R6,TH1
       MOV R7,TL1
      LCALL  HB2
      MOV    R7,#03H
      MOV   50H,R3
      MOV   51H,R4
      MOV    52H,R5
      MOV    R0,#65H
      MOV    R1,#50H
      LCALL  BCDA
      MOV    60H,#00H           ;结果在65,66,67h中BCD码
      MOV    61H,65H
      MOV     62H,66H
      MOV    63H,67H
      RET

PINYU:
       MOV  30H,TH0
       MOV  31H,TL0
       MOV   A,76H
      ;CJNE   A,#00H,NEXT5
      ;AJMP  NEXT6
       ;CLR  TF0
       LCALL   MUL4
       LCALL   ADD1
       MOV  65H,R2
       MOV  66H,R3
       MOV  67H,R4
       MOV  68H,R5
       MOV  R0,#66H
       MOV R7,35H          ;乘以分频系数
       LCALL    MULD3_1
       MOV  36H,R3
       MOV  37H,R4
       MOV  38H,R5
       LCALL   HB4     ;转换后的三字节ＢＣＤ码整数在R2,R3、R4、R5中。
       MOV  60H,R2
       MOV  61H,R3
       MOV  62H,R4
       MOV  63H,R5
       RET

    MAIKUAN:                   ;测量,测脉宽
       MOV     TMOD,#01H
       MOV     TL0,#00H
       MOV     TH0,#00H
       SETB    EA
       SETB    ET0
       MOV  76H,#00H
       SETB    P3.5
    GDP5:   MOV     C,P3.5
       JC     GDP5
   DDP5: MOV   C,P3.5
       JNC  DDP5
       SETB  TR0

 GDP6:   MOV     C,P3.5
       JC     GDP6
       CLR   TR0
      ; MOV  A,B
      ; CJNE  A,#00H,NEXT6
       ;AJMP  NEXT7
       MOV   A,TH0
       MOV   TH1,A
       MOV    A,TL0
       MOV    TL1,A
       CLR   ET0
       LCALL  MUL4
       LCALL  ADD1
       MOV  36H,R3
       MOV  37H,R4
       MOV  38H,R5
       RET


 MUL4: MOV R2,#0FFH
       MOV R3,#0FFH
       MOV R6,#00H
       MOV R7,76H
       

       LCALL MULD   
       MOV   A,76H 
       ADD   A,R5
       MOV   R5,A
       MOV   A,#00H
       ADDC  A,R4
       MOV   R4,A
       MOV   A,#00H
       ADDC   A,R3
       MOV    R3,A
       MOV    A,#00H
       ADDC   A,R2        ;结果在R2.R3.R4.R5中

       RET

  ADD1:     MOV    A,TL1
       ADD    A,R5
       MOV    R5,A
       MOV   A,TH1
       ADDC  A,R4
       MOV   R4,A
       MOV   A,#00H
       ADDC  A,R3
       MOV   R3,A
       MOV  A,#00H
       ADDC  A,R2
       MOV   R2,A            ;结果在R2.R3.R4.R5中
       RET
BIJIAO:MOV  A,R2     ;比较30h,31h,32h,33h与r2,r3,r4,r5中数据的大小，大，20H=0，
       CJNE  A,30H,TEND
       MOV  A,R3
       CJNE  A,31H,TEND
       MOV  A,R4
       CJNE A,32H,TEND
       MOV  A,R5
       CJNE  A,33H,TEND
  TEND:JC   BJ1
       SETB  20H
       AJMP   TEND2
   BJ1:CLR   20H
   TEND2:RET                   
      ;  （５）  标号： ＭＵＬＤ    功能：双字节二进制无符号数乘法

;入口条件：被乘数在R2、R3中，乘数在R6、R7中。
;出口信息：乘积在R2、R3、R4、R5中。
;影响资源：PSW、A、B、R2～R7    堆栈需求：  ２字节

MULD:MOV	A,R3	;；计算R3乘R7
	MOV	B,R7
	MUL	AB
	MOV	R4,B	;；暂存部分积
	MOV	R5,A
	MOV	A,R3	;；计算R3乘R6
	MOV	B,R6
	MUL	AB
	ADD	A,R4	;；累加部分积
	MOV	R4,A
	CLR	A
	ADDC	A,B
	MOV	R3,A
	MOV	A,R2	;；计算R2乘R7
	MOV	B,R7
	MUL	AB
	ADD	A,R4	;；累加部分积
	MOV	R4,A
	MOV	A,R3
	ADDC	A,B
	MOV	R3,A
	CLR	A
	RLC	A
	XCH	A,R2	;；计算R2乘R6
	MOV	B,R6
	MUL	AB
	ADD	A,R3	;；累加部分积
	MOV	R3,A
	MOV	A,R2
	ADDC	A,B
	MOV	R2,A
	RET


   ;  （９）  标号：  ＤＶ３１    功能：三字节二进制无符号数除以单字节二进制数

;入口条件：被除数在R3、R4、R5中，除数在R7中。
;出口信息：OV=0 时，双字节商在R4、R5中，OV=1 时溢出。
;影响资源：PSW、A、B、R2～R7    堆栈需求：  ２字节

DV31:	CLR	C
	MOV	A,R3
	SUBB	A,R7
	JC	DV30
	SETB	OV	;；商溢出
	RET
DV30:	MOV	R2,#10H	;;；求R3R4R5／R7－→R4R5
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
	MOV	A,R3	;;；四舍五入
	ADD	A,R3
	JC	DM25
	SUBB	A,R7
	JC	DM26
DM25:	INC	R5
	MOV	A,R5
	JNZ	DM26
	INC	R4
DM26:	CLR	OV
	RET             ;；商在R4R5中
	    ;（７）  标号：  ＤＩＶＤ    功能：双字节二进制无符号数除法

;入口条件：被除数在R2、R3、R4、R5中，除数在R6、R7中。
;出口信息：OV=0 时，双字节商在R2、R3中，OV=1 时溢出。
;影响资源：PSW、A、B、R1～R7    堆栈需求：  ２字节

DIVD:	CLR	C	;；比较被除数和除数
	MOV	A,R3
	SUBB	A,R7
	MOV	A,R2
	SUBB	A,R6
	JC	DVD1
	SETB	OV	;；溢出
	RET
DVD1:	MOV	B,#10H	;；计算双字节商
DVD2:	CLR	C	;；部分商和余数同时左移一位
	MOV	A,R5
	RLC	A
	MOV	R5,A
	MOV	A,R4
	RLC	A
	MOV	R4,A
	MOV	A,R3
	RLC	A
	MOV	R3,A
	XCH	A,R2
	RLC	A
	XCH	A,R2
	MOV	F0,C	;；保存溢出位
	CLR	C
	SUBB	A,R7	;;；计算（R2R3－R6R7）
	MOV	R1,A
	MOV	A,R2
	SUBB	A,R6
	ANL	C,/F0                 	;；结果判断
	JC	DVD3
	MOV	R2,A            	;；够减，存放新的余数
	MOV	A,R1
	MOV	R3,A
	INC	R5	                  ;；商的低位置一
DVD3:	DJNZ	B,DVD2	      ;；计算完十六位商（R4R5）
	MOV	A,R4	            ;；将商移到R2R3中
	MOV	R2,A
	MOV	A,R5
	MOV	R3,A
	CLR	OV	;；设立成功标志
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

    ;（５）  标号： ＭＵＬＤ    功能：3字节二进制无符号数乘法

;入口条件：被乘数在R7中，乘数在[R0]中。
;出口信息：乘积在R2、R3、R4、R5中。
;影响资源：PSW、A、B、R2～R7    堆栈需求：  ２字节

MULD3_1:INC R0
     INC  R0
    MOV	A,R7 	;；计算乘
	MOV	B,@R0
	MUL	AB
	MOV	R4,B	;；暂存部分积
	MOV	R5,A
	MOV	A,R7 	;；计算乘
	DEC  R0
	MOV	B,@R0
	MUL	AB
	ADD	A,R4	;；累加部分积
	MOV	R4,A
	CLR	A
	ADDC	A,B
	MOV	R3,A
	MOV	A,R7	;；计算乘
	DEC R0
	MOV	B,@R0
	MUL	AB
	ADD	A,R3 	;；累加部分积
	MOV	R3,A
	CLR A
	ADDC  A,B
	MOV  R2,A
	RET

   ;   （１７）  标号： ＨＢ4   功能：3字节十六进制整数转换成双字节ＢＣＤ码整数

;入口条件：待转换的双字节十六进制整数在36,37,38H  中。
;出口信息：转换后的三字节ＢＣＤ码整数在R2,R3、R4、R5中。
;影响资源：PSW、A、R2～R7    堆栈需求：  ２字节

HB4:CLR	A	;;；ＢＣＤ码初始化
	MOV	R3,A
	MOV	R4,A
	MOV	R5,A
	MOV  R2,A
	MOV	R7,#18H	       ;；转换3字节十六进制整数
HB5:	MOV	A,38H   ;	；从高端移出待转换数的一位到CY中
	RLC	A
	MOV	38H,A
	MOV	A,37H
	RLC	A
	MOV	37H,A
	MOV	A,36H   ;	；从高端移出待转换数的一位到CY中
	RLC	A
	MOV	36H,A

	MOV	A,R5	    ;；ＢＣＤ码带进位自身相加，相当于乘２
	ADDC	A,R5
	DA	A	;；十进制调整
	MOV	R5,A
	MOV	A,R4
	ADDC	A,R4
	DA	A
	MOV	R4,A
	MOV	A,R3
	ADDC	A,R3
	DA  A
	MOV	R3,A
	MOV	A,R2
	ADDC	A,R2
	DA	A
	MOV	R2,A 	          ;；双字节十六进制数的万位数不超过６，不用调整
	DJNZ	R7,HB5	;；处理完１６ｂｉｔ
	RET
TRANS: MOV R0,#63H
       MOV R1,#40H
       MOV R6,#04H
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
SEACH1:MOV      DPTR,#A8279_1
       MOVX     A,@DPTR
       ANL A,#07H
       JZ  RETUN8
       LJMP KEY_1
 RETUN8:RET

  LED:MOV      DPTR,#A8279_1
       MOV      A,#90H
       MOVX      @DPTR,A
       MOV      R1,#40H
       MOV      R7,#08H
       MOV      DPTR,#A8279_2
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















