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
       
       MOV  32H,#0FCH
       MOV  33H,#66H
          
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
       MOV  @DPTR,A 
       MOV TH0 ,32H
       MOV TL0,33H
       SETB  TR0 
HERE:JBC TF0 ,NEXT3 
      SJMP HERE       
NEXT3: MOV  A,#00H
      MOV  DPTR,#8300H
      MOV  @DPTR,A 
      MOV TH0,32H
      MOV TL0,33H
HERE1:JBC TF0,NEXT4
      SJMP HERE1  
      
NEXT4:LCALL SEACH
      JBC 01H,MAIN1 
      JBC  02H,MMM1
      JBC  03H,MMM1
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
     CJNE A,#06H,PTF0
     AJMP  PTFK0
PTF0:CLR C 
     INC      30H
     
     LCALL JIAN  
PTFK0: AJMP RETUN 
KEY5:CJNE A,#0FH,RETUN 
     MOV A,33H
     CJNE A,#01H,PTF1
     AJMP  RETUN  
PTF1: DEC  30H
      
      LCALL JIA 
                    
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
       
       
       
JIA:  MOV A,33H
      ADD A,#99H
      
      MOV 33H,A
      MOV A,32H
      ADDC A,#03H
      MOV 32H,A  
      RET   
 JIAN:CLR C  
      MOV A,33H
      SUBB A,#99H
      MOV 33H,A
      MOV A,32H
      SUBB A,#03H
      MOV 32H,A 
      RET  
 

  
 
  
  
  
 

  
 
 ;    ????????  ?????? ??????   ????????????????????????????????????????????????

;??????????????????????????????????????R6??R7????
;??????????????????????????????????????R3??R4??R5????
;;??????????PSW??A??R2??R7    ??????????  ??????

HB2:MOV R6,#00H
    MOV R7,30H
    CLR	A	    ;????????????????
	MOV	R3,A
	MOV	R4,A
	MOV	R5,A
	MOV	R2,#10H	       ;????????????????????????
HB3:	MOV	A,R7                   ;	????????????????????????????CY??
	RLC	A
	MOV	R7,A
	MOV	A,R6
	RLC	A
	MOV	R6,A
	MOV	A,R5	               ;????????????????????????????????????
	ADDC	A,R5
	DA	A	                  ;;;;;????????????
	MOV	R5,A
	MOV	A,R4
	ADDC	A,R4
	DA	A
	MOV	R4,A
	MOV	A,R3
	ADDC	A,R3
	MOV	R3,A	                    ;????????????????????????????????????????????
	DJNZ	R2,HB3  
	
	MOV 39H,R5                     ;	??????????????????
	RET 	
   
 
   LED:MOV      DPTR,#0FF82H
       MOV      A,#90H
       MOVX      @DPTR,A
       MOV      R1,#40H
       MOV      R7,#01H
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
                      