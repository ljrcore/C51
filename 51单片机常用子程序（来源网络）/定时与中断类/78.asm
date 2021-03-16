       	ORG	0000H
    	AJMP	MAIN  
        ORG     001BH
        AJMP    SERVE
  MAIN:A8279_1 EQU    0FF82H
       A8279_2 EQU    0FF80H
       MOV      DPTR,#A8279_1 
       MOV      A,#0D1H
       MOVX     @DPTR,A
 WAIT1:MOVX     A,@DPTR
       JB       ACC.7,WAIT1
       MOV      A,#00H
       MOVX     @DPTR,A
       MOV      A,#2CH
       MOVX     @DPTR,A
       
       MOV     TMOD,#10H
       MOV     20H,#14H
       CLR  A
       MOV 30H,A 
       MOV 31H,A
       MOV 32H,A
       MOV 33H,A
       SETB  ET1
       SETB  EA
        MOV     TL1,#00H
        MOV     TH1,#4CH
        SETB    TR1
        ACALL  TRANS
	ACALL  LED 
        SJMP    $
         
  SERVE:PUSH PSW
        PUSH ACC  
	LCALL  TRANS
	LCALL  LED 
  
        MOV     TL1,#00H
        MOV     TH1,#4CH
        DJNZ    20H,RETUNT
        MOV     20H,#14H

        MOV A,#01H
        ADD A,33H
        DA A
	    MOV 33H,A
        XRL A,#60H
	    JNZ RETUNT
        MOV 33H,#00H
    
        MOV A,#01H
        ADD A,32H
        DA A
	MOV 32H,A
        XRL A,#60H
	JNZ RETUNT
        MOV 32H,#00H
   
       MOV A,#01H
       ADD A,31H
       DA A
       MOV 31H,A
       XRL A,#25H
       JNZ RETUNT
       MOV 31H,#00H

       MOV A,#01H
       ADD A,30H
       DA A
       MOV 30H,A
       XRL A,#31H
       JNZ RETUNT
       MOV 30H,#00H

RETUNT:ACALL SEACH1
       POP ACC
       POP PSW
       RETI
        
TRANS: MOV R0,#33H
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


  

   LED:MOV      DPTR,#A8279_1
       MOV      A,#90H
       MOVX      @DPTR,A
       MOV      R1,#40H
        
       MOV      R7,#08H
       MOV      DPTR,#7FFEH
  LOOP:MOV      A,@R1
       ADD      A,#17H
       MOVC     A,@A+PC
       MOV      @R1,A
       INC      R1
       DJNZ     R7,LOOP
       MOV      R7,#08H
       MOV      R1,#40H
       ORL   42H,#80H
       ORL   44H,#80H
       ORL   46H,#80H
 LOOP3:MOV  A,@R1
       MOVX @DPTR,A
       INC  R1
       DJNZ R7,LOOP3
          
       RET
       DB       3FH,06H,5BH,4FH,66H,6DH
       DB       7DH,07H,7FH,6FH 
  



   KEY:MOV  DPTR ,#A8279_1
	MOV  A,#40H
	MOVX @DPTR,A
	MOV DPTR,#7FFEH
	MOVX A,@DPTR
	ANL A,#3FH

        CJNE A,#0CH,KEY1             
        CLR  A
        MOV 30H,A 
        MOV 31H,A
        MOV 32H,A
        MOV 33H,A
        AJMP RETUN    
      
   KEY1:CJNE A,#0AH,KEY2
        ACALL SEACH2
        MOV DPTR ,#A8279_2
       	MOVX A,@DPTR
        ANL A,#3FH
        CJNE A,#06H,PTF1
   PTF1:JC NEXT2
        MOV 33H,#00H
        AJMP RETUN
  NEXT2:SWAP A   
        MOV 33H,A
        ACALL SEACH2
        MOV DPTR #A8279_2
       	MOVX A,@DPTR
        ANL A,#3FH
        CJNE A,#0AH,PTF2
   PTF2:JC NEXT3
        MOV 33H,#00H
        AJMP RETUN        
   NEXT3:ORL 33H,A
        AJMP RETUN

   KEY2:CJNE A,#0BH,KEY3
        ACALL SEACH2
        MOV DPTR #A8279_2
       	MOVX A,@DPTR
        ANL A,#3FH
        CJNE A,#06H,PTF3
   PTF3:JC NEXT4
        MOV 32H,#00H
        AJMP RETUN
  NEXT4:SWAP A   
        MOV 32H,A
        ACALL SEACH2
        MOV DPTR #A8279_2
       	MOVX A,@DPTR 
        ANL A,#3FH
        CJNE A,#0AH,PTF4
   PTF4:JC NEXT5
        MOV 32H,#00H
        AJMP RETUN
   NEXT5:ORL 32H,A
        AJMP RETUN     
        
   KEY3:CJNE A,#0DH,KEY4
        ACALL SEACH2
        MOV DPTR #A8279_2
       	MOVX A,@DPTR
        ANL A,#3FH
        SWAP A   
        MOV 31H,A
        ACALL SEACH2
        MOV DPTR #A8279_2
       	MOVX A,@DPTR 
        ANL A,#3FH
        ORL 31H,A
        MOV A,31H
        CJNE A,#25H,PTF6
   PTF6:JC RETUN
        MOV 31H,#00H
        AJMP RETUN
 
   KEY4:CJNE A,#0EH,RETUN
        ACALL SEACH2
        MOV DPTR #A8279_2
       	MOVX A,@DPTR
        ANL A,#3FH
        SWAP A   
        MOV 30H,A
        ACALL SEACH2
        MOV DPTR #A8279_2 
        MOVX A,@DPTR
        ANL A,#3FH
        ORL 30H,A
        MOV A,30H  
        CJNE A,#31H,PTF7
   PTF7:JC RETUN
        MOV 30H,#00H
        
          
  
  RETUN:RET


   
SEACH1:MOV      DPTR,#A8279_1   
       MOVX     A,@DPTR
       ANL A,#07H
       JZ  RETUN4
       LJMP KEY
 RETUN4:RET
SEACH2:MOV      DPTR,#A8279_1   
       MOVX     A,@DPTR
       ANL A,#07H
       JNZ  RETUN3
       SJMP SEACH2
 RETUN3:RET      
END                             