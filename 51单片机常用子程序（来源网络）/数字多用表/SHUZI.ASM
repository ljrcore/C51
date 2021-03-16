ORG   0000H
AJMP  MAIN
            
ORG  0013H
AJMP  DUSHU 
ORG   0030H
MAIN: 
       A8279_1 EQU    0FF82H
       A8279_2 EQU    0FF80H
  
       MOV      DPTR,#A8279_1
       MOV      A,#0D1H
       MOVX     @DPTR,A
  WAIT:MOVX     A,@DPTR
       JB       ACC.7,WAIT  
       MOV      A,#00H
       MOVX     @DPTR,A
       MOV      A,#2CH
       MOVX     @DPTR,A
       
       CLR     09H
       CLR     01H
       CLR	   02H
       CLR     03H
       CLR     04H
       CLR	   05H
      
  
 START:MOV      DPTR,#A8279_1
       MOVX     A,@DPTR
       ANL A,#07H
       JZ  RETUN
       LCALL    KEY
       JBC     09H,RETUN 
       JBC     01H,DIANYA
       JBC     02H,DIANLIOU 
       JBC     03H,SHGY 
       JBC     04H,YOUGY  
       JBC     05H,GYYSH 
              
RETUN:AJMP  START
DIANYA:LJMP DIANYA1
DIANLIOU:LJMP DIANL1
SHGY:LJMP  SHGY1 
YOUGY:LJMP YOUGY1
GYYSH:LJMP  GYYSH1

DIANYA1:LCALL DIANYA2
       MOV  R6,50H
       MOV  R7,51H
       LCALL  HB2                        ;;出口信息：转换后的三字节ＢＣＤ码整数在R3、R4、R5中。
       MOV  50H,R3
       MOV  51H,R4
       MOV  52H,R5 
       MOV  53H,#58H
       LCALL      TRANS
       MOV   53H,#58H
       LCALL  LED_1 
       MOV  54H,#3EH
       MOV  55H,#40H
       MOV  56H,#40H
        MOV  57H,#40H
       ORL 59H,#80H
       LCALL   LED
       LCALL   SEACH 
       JBC   09H,RETUN20 
        JBC   01H,RETUN21 
       JBC   02H,RETUN22
       JBC   03H,RETUN23 
        JBC   04H,RETUN24
        JBC  05H,RETUN25 
       AJMP  DIANYA1
RETUN20:LJMP  MAIN
RETUN21:LJMP  DIANYA1     
RETUN22:LJMP  DIANL1 
RETUN23:LJMP   SHGY1 
RETUN24:LJMP YOUGY1
RETUN25:LJMP   GYYSH1     
        
DIANYA2:CLR P1.0
       MOV  R0,#30H 
       LCALL ADC0809
       LCALL PINJUN
       MOV  50H,R4
       MOV  51H,R5
       MOV  R6,50H
       MOV  R7,51H
       MOV  R2,#4CH
       MOV  R3,#4BH
       LCALL  MULD                 ; 乘积在R2、R3、R4、R5中。
       MOV   R6,#03H
       MOV   R7,#0E8H 
       LCALL  DIVD                  ;：OV=0 时，双字节商在R2、R3中，OV=1 时溢出。
       MOV  50H,R2 
       MOV  51H,R3 
       RET 
DIANL1:LCALL DIANL2   
       MOV  R6,50H
       MOV  R7,51H
       LCALL  HB2                        ;;出口信息：转换后的三字节ＢＣＤ码整数在R3、R4、R5中。
       MOV  50H,R3
       MOV  51H,R4
       MOV  52H,R5 
       MOV  53H,#59H
       LCALL      TRANS
       MOV   53H,#59H
       LCALL  LED_1 
       MOV  54H,#39H
       MOV  55H,#40H
       MOV  56H,#40H
       MOV  57H,#40H
       MOV  58H,#40H
       ORL 5AH,#80H
       LCALL   LED
      
       LCALL   SEACH 
       JBC   09H,RETUN30 
 
       JBC   01H,RETUN31 
       JBC   02H,RETUN32
       JBC   03H,RETUN33 
       JBC   04H,RETUN34
       JBC  05H,RETUN35 
       AJMP  DIANL1
RETUN30:LJMP  MAIN
RETUN31:LJMP  DIANYA1     
RETUN32:LJMP  DIANL1 
RETUN33:LJMP   SHGY1 
RETUN34:LJMP YOUGY1
RETUN35:LJMP   GYYSH1    
                                                 
DIANL2:SETB   P1.0
       MOV  R0,#30H 
       LCALL ADC0809
       LCALL PINJUN
       MOV  50H,R4
       MOV  51H,R5
       MOV  R6,50H
       MOV  R7,51H
       MOV  R2,#4CH
       MOV  R3,#4BH
       LCALL  MULD                 ; 乘积在R2、R3、R4、R5中。
       MOV   R6,#27H
       MOV   R7,#10H 
       LCALL  DIVD                  ;：OV=0 时，双字节商在R2、R3中，OV=1 时溢出。
       MOV  50H,R2 
       MOV  51H,R3 
       RET 
       
SHGY1:LCALL  DIANYA2
     MOV    66H,50H
     MOV    67H,51H
     LCALL     DIANL2
     MOV  R2,50H
     MOV  R3,51H
     MOV  R6,66H
     MOV  R7,67H
     LCALL    MULD      ;出口信息：乘积在R2、R3、R4、R5中。
     MOV   R7,#100
     MOV   R6,#00H
     LCALL  DIVD               ;：OV=0 时，双字节商在R2、R3中，OV=1 时溢出。
     MOV  50H,R2
     MOV  51H,R3
     MOV  R6,50H
     MOV  R7,51H
     
     LCALL  HB2
     MOV  50H,R3
     MOV  51H,R4
     MOV  52H,R5  
     MOV  53,#57H
     LCALL      TRANS
     MOV  53H,#57H
      LCALL  LED_1 
      MOV  56H,#40H
      MOV  55H,#40H
      MOV  54H,#73H
      LCALL   LED
       
       LCALL   SEACH
       JBC   09H,RETUN70 
        JBC   01H,RETUN71 
       JBC   02H,RETUN72
       JBC   03H,RETUN73 
        JBC   04H,RETUN74
        JBC  05H,RETUN75 
       AJMP   SHGY1
RETUN70:LJMP  MAIN
RETUN71:LJMP  DIANYA1     
RETUN72:LJMP  DIANL1 
RETUN73:LJMP   SHGY1 
RETUN74:LJMP YOUGY1
RETUN75:LJMP   GYYSH1


YOUGY1:LCALL  DIANYA2
     MOV    66H,50H
     MOV    67H,51H
     LCALL     DIANL2
     MOV  68H,50H
     MOV  69H,51H
     LCALL GYYSH2
     LCALL   BH2
     MOV  R6,68H
     MOV  R7,69H
     LCALL    MULD      ;出口信息：乘积在R2、R3、R4、R5中。
     MOV R6,#00H
     MOV R7,#100
     LCALL  DIVD          ; OV=0 时，双字节商在R2、R3中，OV=1 时溢出。
     MOV  R6,66H
     MOV  R7,67H
     LCALL   MULD        ;乘积在R2、R3、R4、R5中。
     MOV  R6,#27H
     MOV  R7,#10H
     LCALL   DIVD           ; OV=0 时，双字节商在R2、R3中，OV=1 时溢出。
     MOV   50H,R2
     MOV   51H,R3
     
     
       MOV  R6,50H
       MOV  R7,51H
       LCALL  HB2                        ;;出口信息：转换后的三字节ＢＣＤ码整数在R3、R4、R5中。
       MOV  50H,R3
       MOV  51H,R4
       MOV  52H,R5 
       MOV  53H,#57H
       LCALL      TRANS
       MOV   53H,#57H
       LCALL  LED_1 
       MOV  54H,#6EH
       MOV  55H,#40H
       MOV   56H,#40H
       
       
       LCALL   LED
      
       LCALL   SEACH 
       JBC   09H,RETUN90 
 
       JBC   01H,RETUN91 
       JBC   02H,RETUN92
       JBC   03H,RETUN93 
       JBC   04H,RETUN94
       JBC  05H,RETUN95 
       AJMP  YOUGY1
RETUN90:LJMP  MAIN
RETUN91:LJMP  DIANYA1     
RETUN92:LJMP  DIANL1 
RETUN93:LJMP   SHGY1 
RETUN94:LJMP YOUGY1
RETUN95:LJMP   GYYSH1    
   
     
   
GYYSH1: LCALL  GYYSH2
        MOV  50H,#00H
        MOV  51H,R2 
        MOV  52H,R3  
        MOV  53H,#57H
        LCALL      TRANS
       MOV   53H,#57H
       LCALL  LED_1 
       MOV  54H,#6EH
       MOV  55H,#73H
       MOV  56H,#40H
       MOV  5BH,#0BFH
 
    
       LCALL   LED
      
       LCALL   SEACH 
       JBC   09H,RETUN80 
 
       JBC   01H,RETUN81 
       JBC   02H,RETUN82
       JBC   03H,RETUN83 
       JBC   04H,RETUN84
       JBC  05H,RETUN85 
       AJMP  GYYSH1  
RETUN80:LJMP  MAIN
RETUN81:LJMP  DIANYA1     
RETUN82:LJMP  DIANL1 
RETUN83:LJMP   SHGY1 
RETUN84:LJMP YOUGY1
RETUN85:LJMP   GYYSH1    
                                             

GYYSH2:   ;LCALL  ZHQI
       ;MOV   51H,TL0
      ; MOV   50H,TH0
        LCALL  XWCH 
            
        MOV		R2,TH1
		MOV		R3,TL1
		MOV		R6,#00H		    	;计数值-查表偏移量计算
		MOV		R7,#0AH
		ACALL	MULD                   ;出口信息：乘积在R2、R3、R4、R5中。
		MOV		R6,#00H
		MOV		R7,#7DH
		ACALL	DIVD  
		MOV		60H,R3
		
		
    	MOV		DPTR,#TAB1		;查表得余弦值
		MOV		A,60H
		MOVC	A,@A+DPTR
		MOV		R3,A
		MOV		DPTR,#TAB2
		MOV		A,60H 
MOVC	A,@A+DPTR
		MOV		R2,A
        MOV  60H,R2
        MOV  61H,R3                   	;	ACALL	BH2				;余弦值BCD转为HEX
		 
		RET 

           
       
          
   
 ZHQI:                   ;0.1hz_1khz测量,测周期 ;16进制
       MOV     TMOD,#01H
       MOV     TL0,#00H
       MOV     TH0,#00H
       
       
       SETB    P3.5
    GDP1:   MOV     C,P3.5
       JC     GDP1
   DDP1: MOV   C,P3.5
       JNC  DDP1
       SETB  TR0

 GDP2:   MOV     C,P3.5
       JC     GDP2
                    ; DDP2: MOV   C,P3.5
                    ;    JNC  DDP2
       CLR   TR0
       RET     
     
 XWCH:                   ;0.1hz_1khz测量,测周期 ;16进制
       MOV     TMOD,#10H
       MOV     TL1,#00H
       MOV     TH1,#00H
       
       
       SETB    P3.5
   GDP6:   MOV     C,P3.5
       JC     GDP6    
   DDP6: MOV   C,P3.5
       JNC  DDP6
  
       SETB  TR1 

 GDP7:   MOV     C,P3.5
      JC     GDP7
  ; DDP2: MOV   C,P3.5
     ;  JNC  DDP2
       CLR   TR1 
       RET           
        

 KEY:MOV  DPTR ,#A8279_1
	MOV  A,#40H
	MOVX @DPTR,A
	MOV DPTR,#A8279_2
	MOVX A,@DPTR
	ANL A,#3FH

    CJNE A,#09H,KEY1
        SETB 09H
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


     
     
ADC0809:
      
        CLR 06H
        
        MOV R7,#18H
        SETB EA 
        SETB IT1
        SETB EX1
        MOV DPTR,#8200H     ;；DAC0809首址
        MOVX @DPTR,A        ;；启动AD转换
  HERE:JBC 06H,RETUN56 
         SJMP HERE
 RETUN56:CLR  EA
         CLR EX1 
           RET       
 DUSHU:MOVX A,@DPTR
          MOV  @R0,A
          INC R0
          DJNZ R7,NT0 
          SETB  06H 
     NT0: 
           RETI
           
 ;;;将片内RAM30H-42H中的数据按从小到大的顺序排序
 



QUE:CLR 00H
    MOV R3,#18         ;;;；18个数据循环次数
    MOV R0,#30H
    MOV A,@R0
 L2:INC R0
    MOV R2,A
    SUBB A,@R0
    MOV A,R2
    JC L1
    SETB 00H
    XCH A,@R0
    DEC R0
    XCH A,@R0
    INC R0
 L1:MOV A,@R0
    DJNZ R3,L2
    JB 00H,QUE
    RET 
JIAO:MOV R0,#31H
     MOV  R7,#16
     MOV 45H,#00H
     MOV 46H,#00H    
KP1: MOV A,@R0
     ADD A,46H
     MOV 46H,A               
     MOV A,#00H
     ADDC A,45H
     MOV  45H,A
     INC  R0
     DJNZ  R7,KP1 
     RET 
PINJUN:                          ;LCALL  QUE
       LCALL  JIAO
       
       MOV R3,#00H
       MOV R4,45H
       MOV R5,46H
       MOV R7,#10H
       LCALL DV31               ;OV=0 时，双字节商在R4、R5中，OV=1 时溢出。
       
       RET 
       
    ;（２１）标号：  ＢＨ２   功能：双字节ＢＣＤ码整数转换成双字节十六进制整数

;入口条件：待转换的双字节ＢＣＤ码整数在R2、R3中。
;出口信息：转换后的双字节十六进制整数仍在R2、R3中。
;影响资源：PSW、A、B、R2、R3、R4    堆栈需求：  ４字节

BH2:	MOV	A,R3	;；将低字节转换成十六进制
	LCALL	BCDH
	MOV	R3,A
	MOV	A,R2	;；将高字节转换成十六进制
	LCALL	BCDH
	MOV	B,#100	;；扩大一百倍
	MUL	AB
	ADD	A,R3	;；和低字节按十六进制相加
	MOV	R3,A
	CLR	A
	ADDC	A,B
	MOV	R2,A
	RET
      
   ; （２０）标号：ＢＣＤＨ    功能：单字节ＢＣＤ码整数转换成单字节十六进制整数

;入口条件：待转换的单字节ＢＣＤ码整数在累加器A中。
;出口信息：转换后的单字节十六进制整数仍在累加器A中。
;影响资源：PSW、A、B、R4    堆栈需求：  ２字节

BCDH:	MOV	B,#10H	;；分离十位和个位
	DIV	AB
	MOV	R4,B	;；暂存个位
	MOV	B,#10	;；将十位转换成十六进制
	MUL	AB
	ADD	A,R4	;；按十六进制加上个位
	RET

           
            ; ； （９）  标号：  ＤＶ３１    功能：三字节二进制无符号数除以单字节二进制数

;入口条件：被除数在R3、R4、R5中，除数在R7中。
;出口信息：OV=0 时，双字节商在R4、R5中，OV=1 时溢出。
;影响资源：PSW、A、B、R2～R7    堆栈需求：  ２字节

DV31:	CLR	C
	MOV	A,R3
	SUBB	A,R7
	JC	DV30
	SETB	OV	             ;；商溢出
	RET
DV30:	MOV	R2,#10H	           ;；求R3R4R5／R7－→R4R5
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
	MOV	A,R3	                           ;；四舍五入
	ADD	A,R3
	JC	DM25
	SUBB	A,R7
	JC	DM26
DM25:	INC	R5
	MOV	A,R5
	JNZ	DM26
	INC	R4
DM26:	CLR	OV
	RET                                       ;；商在R4R5中 
	
	
    ;（５）  标号： ＭＵＬＤ    功能：双字节二进制无符号数乘法

;入口条件：被乘数在R2、R3中，乘数在R6、R7中。
;出口信息：乘积在R2、R3、R4、R5中。
;影响资源：PSW、A、B、R2～R7    堆栈需求：  ２字节

MULD:	MOV	A,R3	;；计算R3乘R7
	MOV	B,R7
	MUL	AB
	MOV	R4,B	;；暂存部分积
	MOV	R5,A
	MOV	A,R3	;；计算R3乘R6
	MOV	B,R6
	MUL	AB
	ADD	A,R4	;;；累加部分积
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
	ADD	A,R3	         ;；累加部分积
	MOV	R3,A
	MOV	A,R2
	ADDC	A,B
	MOV	R2,A
	RET
  ;  （７）  标号：  ＤＩＶＤ    功能：双字节二进制无符号数除法

;入口条件：被除数在R2、R3、R4、R5中，除数在R6、R7中。
;出口信息：OV=0 时，双字节商在R2、R3中，OV=1 时溢出。
;影响资源：PSW、A、B、R1～R7    堆栈需求：  ２字节

DIVD:	CLR	C	                     ;；比较被除数和除数
	MOV	A,R3	
	SUBB	A,R7
	MOV	A,R2
	SUBB	A,R6
	JC	DVD1
	SETB	OV      ;	；溢出
	RET
DVD1:	MOV	B,#10H	            ;；计算双字节商
DVD2:	CLR	C	               ;；部分商和余数同时左移一位
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
	MOV	F0,C	             ;；保存溢出位
	CLR	C
	SUBB	A,R7	          ;；计算（R2R3－R6R7）
	MOV	R1,A
	MOV	A,R2
	SUBB	A,R6
	ANL	C,/F0	              ;；结果判断
	JC	DVD3
	MOV	R2,A	          ;；够减，存放新的余数
	MOV	A,R1
	MOV	R3,A
	INC	R5	                   ;；商的低位置一
DVD3:	DJNZ	B,DVD2	;；计算完十六位商（R4R5）
	MOV	A,R4           ;	；将商移到R2R3中
	MOV	R2,A
	MOV	A,R5
	MOV	R3,A
	CLR	OV	  ;；设立成功标志
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


          

    
      
SEACH:MOV      DPTR,#A8279_1   
       MOVX     A,@DPTR
       ANL A,#07H
       JZ  RETUN4
       LJMP  KEY
       
RETUN4:RET 
 
   

   
  
 TRANS:MOV R0,#52H
       MOV R1,53H
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
   
  
  

LED:MOV DPTR,#A8279_1
    MOV      A,#90H
    MOVX      @DPTR,A
    MOV      R0,#54H
    MOV  R7,#08H
    MOV  DPTR,#A8279_2
LOOP2:    MOV A,@R0
    MOVX     @DPTR,A
    INC      R0 
    DJNZ     R7,LOOP2
    RET 
                      
LED_1:MOV R0,53H
      MOV R7,#06H
      MOV DPTR,#TAB
LOOP1:MOV A,@R0
      MOVC A,@A+DPTR
      MOV @R0,A
      INC  R0
      DJNZ R7,LOOP1
      RET
  TAB:DB       3FH,06H,5BH,4FH,66H,6DH
      DB       7DH,07H,7FH,6FH,77H,7CH
      DB       39H,5EH,79H,71H         


;***********三角函数值表*************************
 TAB1:	   DB    99H,99H,98H,97H,95H,92H,89H,85H
	     	DB    80H,75H,69H,63H,56H,48H,40H,31H
	     	DB    21H,11H,00H,89H,77H,64H,51H,37H
	     	DB    23H,08H,92H,76H,59H,42H,24H,05H
	     	DB    86H,67H,46H,25H,03H,81H,58H,35H
	     	DB    11H,86H,61H,35H,09H,82H,54H,26H
	     	DB    98H,69H,39H,08H,78H,46H,14H,81H
	     	DB    48H,15H,80H,45H,10H,74H,38H,01H
	     	DB    63H,25H,86H,47H,07H,67H,26H,85H
	     	DB    43H,01H,58H,15H,71H,26H,81H,36H
	     	DB    90H,44H,97H,49H,02H,53H,04H,55H
	     	DB    05H,55H,04H,53H,01H,49H,96H,43H
	     	DB    90H,36H,81H,26H,71H,15H,59H,03H
	     	DB    45H,88H,30H,72H,13H,54H,94H,35H
	     	DB    74H,14H,52H,91H,29H,67H,04H,41H
	     	DB    78H,14H,50H,86H,21H,56H,90H,24H
	     	DB    58H,92H,25H,58H,90H,23H,55H,86H
	     	DB    18H,49H,79H,10H,40H,70H,99H,29H
	     	DB    58H,87H,15H,43H,71H,99H,27H,54H
	     	DB    81H,08H,35H,61H,87H,13H,39H,65H
	     	DB    90H,15H,40H,65H,90H,14H,39H,63H
	     	DB    87H,11H,34H,58H,81H,05H,28H,51H
	     	DB    74H,97H,19H,42H,64H,87H,09H,31H
	     	DB    53H,75H,97H,19H,41H,63H,85H,06H
	     	DB    28H,50H,71H,93H,14H,36H,57H,79H
	     	DB    00H
	     	DW    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
            DW    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
  TAB2:     DB    99H,99H,99H,99H,99H,99H,99H,99H
	     	DB    99H,99H,99H,99H,99H,99H,99H,99H
	     	DB    99H,99H,99H,98H,98H,98H,98H,98H
	     	DB    98H,98H,97H,97H,97H,97H,97H,97H
	     	DB    96H,96H,96H,96H,96H,95H,95H,95H
	     	DB    95H,94H,94H,94H,94H,93H,93H,93H
	     	DB    92H,92H,92H,92H,91H,91H,91H,90H
	     	DB    90H,90H,89H,89H,89H,88H,88H,88H
	     	DB    87H,87H,86H,86H,86H,85H,85H,84H
	     	DB    84H,84H,83H,83H,82H,82H,81H,81H
	     	DB    80H,80H,79H,79H,79H,78H,78H,77H
	     	DB    77H,76H,76H,75H,75H,74H,73H,73H
	     	DB    72H,72H,71H,71H,70H,70H,69H,69H
	     	DB    68H,67H,67H,66H,66H,65H,64H,64H
	     	DB    63H,63H,62H,61H,61H,60H,60H,59H
	     	DB    58H,58H,57H,56H,56H,55H,54H,54H
	     	DB    53H,52H,52H,51H,50H,50H,49H,48H
	     	DB    48H,47H,46H,46H,45H,44H,43H,43H
	     	DB    42H,41H,41H,40H,39H,38H,38H,37H
	     	DB    36H,36H,35H,34H,33H,33H,32H,31H
	     	DB    30H,30H,29H,28H,27H,27H,26H,25H
	     	DB    24H,24H,23H,22H,21H,21H,20H,19H
	     	DB    18H,17H,17H,16H,15H,14H,14H,13H
	     	DB    12H,11H,10H,10H,09H,08H,07H,07H
	     	DB    06H,05H,04H,03H,03H,02H,01H,00H
	     	DB    00H
	     	DW    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	     	DW    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
;		**********THE PROGRAMME END**********
	END     



END 




 LED:MOV      DPTR,#A8279_1
       MOV      A,#90H
       MOVX      @DPTR,A
       MOV      R1,#54H
       MOV      R7,#06H
       MOV      DPTR,#A8279_2
  LOOP:MOV      A,@R1
       ADD      A,#05H
       MOVC     A,@A+PC
       MOVX     @DPTR,A
       INC      R1
       DJNZ     R7,LOOP
       RET
       DB       3FH,06H,5BH,4FH,66H,6DH
       DB       7DH,07H,7FH,6FH,77H,7CH
       DB       39H,5EH,79H,71H   

END        






    
     