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
       CLR 00H 
       CLR 01H
       CLR 02H
       CLR 03H
       
       MOV 50H,#10H
       MOV 51H,#02H
       MOV 52H,#04H
       MOV 53H,#08H  
       
       MOV  30H,#01H
       
       MOV  32H,#200
      
          
       MOV  31H,#01H
       
CHAXUN:LCALL SEACH 
       JBC 00H,MAIN2 
       SJMP CHAXUN 
       
 MAIN2:LCALL HB2 
       LCALL TRANS
       LCALL LED 
       MOV  R0,#50H
       MOV  R7,#04H  
            
 START:MOV  A,@R0
       MOV  DPTR,#8300H
       MOVX   @DPTR,A 
       MOV 72H,32H
       LCALL  DELAY 
              
      MOV  A,#00H
      MOV   DPTR,#8300H
      MOVX   @DPTR,A 
      MOV  72H,32H
      LCALL  DELAY 
      
NEXT4:LCALL SEACH
      JBC 01H,MAIN1 
      JBC  02H,MMM1
      JBC  03H,MMM1
      JBC  04H,MMM1
      INC  R0 
      DJNZ   R7,START
      MOV   R0,#50H
      MOV   R7,#04H
      AJMP  START 
      
MMM1:MOV  R0,#50H
     MOV  R7,#04H
     AJMP   START             
 
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
       
       MOV 50H,#08H
       MOV 51H,#04H
       MOV 52H,#02H
       MOV 53H,#10H
       SETB 02H 
       AJMP RETUN 
 KEY3:CJNE A,#0DH,KEY4
      MOV 50H,#10H
      MOV 51H,#02H
      MOV 52H,#04H
      MOV 53H,#08H 
      SETB  03H  
      AJMP RETUN    
KEY4:CJNE A,#0EH,KEY5
     MOV A,30H
     CJNE A,#14H,PTF0
     AJMP  PTFK0
PTF0:CLR C 
     INC      30H
     MOV  A,32H
     CLR  C 
     SUBB A,#10
     MOV 32H,A
     SETB 04H
          
     
PTFK0: AJMP RETUN 
KEY5:CJNE A,#0FH,RETUN 
     MOV A,30H
     CJNE A,#01H,PTF1
     AJMP  RETUN  
PTF1: DEC  30H
      MOV A,32H
      CLR C
      ADD A,#10
      MOV 32H,A 
      SETB  04H                   
 RETUN: 
       LCALL HB2 
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
       MOV R6,#01H
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

  
  
 

  
 
 ;    （１７）  标号： ＨＢ２   功能：双字节十六进制整数转换成双字节ＢＣＤ码整数

;入口条件：待转换的双字节十六进制整数在R6、R7中。
;出口信息：转换后的三字节ＢＣＤ码整数在R3、R4、R5中。
;;影响资源：PSW、A、R2～R7    堆栈需求：  ２字节

HB2:MOV R6,#00H
    MOV R7,30H
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
	
	MOV 39H,R5                     ;	；处理完１６ｂｉｔ
	RET 	
	
	;;晶振12MHZ,延时0.25秒



DELAY:
LOOP3:MOV 71H,#50
LOOP1:MOV 70H,#02
LOOP0:DJNZ 70H,LOOP0
      DJNZ 71H,LOOP1
      ;MOV 70H,#46
     ;LOOP2:DJNZ 70H,LOOP2
      NOP
      DJNZ 72H,LOOP3
  
      RET 
   
 
   LED:MOV      DPTR,#0FF82H
       MOV      A,#90H
       MOVX      @DPTR,A
       MOV      R1,#40H
       MOV      R7,#02H
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
                      

















    