       ORG 0000H
       AJMP MAIN
       ORG 0030H
  MAIN:MOV      DPTR,#0FF82H
       MOV      A,#0D1H
       MOVX     @DPTR,A
  WAIT:MOVX     A,@DPTR
       JB       ACC.7,WAIT
       MOV      A,#00H
       MOVX     @DPTR,A
       MOV      A,#2CH
       MOVX     @DPTR,A
       
MAIN1:MOV TMOD ,#01H
       CLR 00H     ;标志位
       CLR 01H
       CLR 02H
       CLR 03H
       
       MOV 45H,#01H  
       MOV 30H,#10H          ;电机控制端
       MOV 31H,#00H
       
       MOV 32H,#0F2H     ;；定时器数值
       MOV 33H,#7FH
       MOV 34H,#0FFH
       MOV 35H,#0FFH
       
       MOV 36H,#04H        ;显示数值
       MOV 37H,#0B0H
CHAXUN:LCALL SEACH 
       JBC 00H,MAIN2 
       SJMP CHAXUN 
 MAIN2:LCALL HB2 
       LCALL TRANS
       LCALL LED       
 START:MOV P1,30H
       MOV TH0 ,32H
       MOV TL0,33H
       SETB  TR0 
HERE:JBC TF0 ,NEXT3 
      SJMP HERE       
NEXT3: MOV  P1,31H
      MOV TH0,34H
      MOV TL0,35H
HERE1:JBC TF0,NEXT4
      SJMP HERE1  
      
                
NEXT4:LCALL SEACH
      JBC 01H,MAIN1 
      AJMP START      
 
 SEACH:MOV      DPTR,#0FF82H   
       MOVX     A,@DPTR
       ANL A,#07H
       JZ  RETUN4
       LJMP KEY
RETUN4:RET
   KEY:MOV  DPTR ,#0FF82H
       MOV  A,#40H
	   MOVX @DPTR,A
	   MOV DPTR,#0FF80H
	   MOVX A,@DPTR
	   ANL A,#3FH

       CJNE A,#0AH,KEY1             
       SETB 00H
       AJMP RETUN    
      
  KEY1:CJNE A,#0BH,KEY2
       SETB 01H 
       AJMP RETUN 
 KEY2:CJNE A,#0CH,KEY3
       MOV 45H,#00H
       MOV 30H,#20H
       MOV P1,#00H
       LCALL DELAY1 
       SETB 02H 
       AJMP RETUN 
 KEY3:CJNE A,#0DH,KEY4
      MOV 45H,#01H
      MOV 30H,#10H
      SETB 03H 
      MOV P1,#00H
      LCALL DELAY1 
      AJMP RETUN    
KEY4:CJNE A,#0EH,KEY5
     MOV A,33H
     CJNE A,#7FH,PTF0
      MOV  A,32H
    CJNE  A,#0F2H,PTF0   
     AJMP  PTFK0
PTF0:MOV A,33H
     CLR C 
     SUBB  A,#90H
     MOV 33H,A
     MOV A,32H
     SUBB A,#00H
     MOV  32H,A 
     MOV A,35H 
     ADD A,#90H
     MOV 35H,A
     MOV A,34H
     ADDC  A,#00H
     MOV  34H,A  
     LCALL JIA  
PTFK0: AJMP RETUN 
KEY5:CJNE A,#0FH,RETUN 
     MOV A,33H
     CJNE A,#0FFH,PTF1
     MOV  A,32H
     CJNE A,#0FFH,PTF1 
     AJMP  RETUN  
PTF1:MOV  A,33H 
     ADD A,#90H
     MOV 33H,A
     MOV A,32H
     ADDC A,#00H
     MOV 32H,A 
     MOV A,35H 
     CLR C
     SUBB A,#90H
     MOV 35H,A
     MOV A,34H
     SUBB A,#00H
     MOV  34H,A 
     LCALL JIAN 
                    
 RETUN:LCALL HB2 
       LCALL TRANS
       LCALL LED   
       RET          
 
 
  DELAY1:MOV     R7,#14H

        MOV     TMOD,#01H
        MOV     TL0,#00H
        MOV     TH0,#4CH
        SETB    TR0
   HERE2:JBC     TF0,NEXT7
        SJMP    HERE2
  NEXT7:MOV     TL0,#00H
        MOV     TH0,#4CH
        DJNZ    R7,HERE2
        CLR     TR0
       
        RET
 
       
    
      
 

   
TRANS: MOV R0,#39H
       MOV R1,#40H
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
       
       
       
JIA:  MOV A,37H
      ADD A,#50
      
      MOV 37H,A
      MOV A,36H
      ADDC A,#00
      MOV 36H,A  
      RET   
 JIAN:CLR C  
      MOV A,37H
      SUBB A,#50
      MOV 37H,A
      MOV A,36H
      SUBB A,#00
      MOV 36H,A 
      RET  
 

  
 
  
  
  
 

  
 
 ;    （１７）  标号： ＨＢ２   功能：双字节十六进制整数转换成双字节ＢＣＤ码整数

;入口条件：待转换的双字节十六进制整数在R6、R7中。
;出口信息：转换后的三字节ＢＣＤ码整数在R3、R4、R5中。
;;影响资源：PSW、A、R2～R7    堆栈需求：  ２字节

HB2:MOV R6,36H
    MOV R7,37H
    CLR	A	    ;；ＢＣＤ码初始化
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
	DJNZ	R2,HB3  
	MOV 38H,R4
	MOV 39H,R5                     ;	；处理完１６ｂｉｔ
	RET 	
   
 
   LED:MOV      DPTR,#0FF82H
       MOV      A,#90H
       MOVX      @DPTR,A
       MOV      R1,#40H
       MOV      R7,#04H
       MOV      DPTR,#0FF80H
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
                      