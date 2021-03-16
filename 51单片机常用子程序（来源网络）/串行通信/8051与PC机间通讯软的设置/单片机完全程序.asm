;;单片机主程序
     ORG 0000H
     AJMP MAIN
     ORG 0023H
     AJMP RECE
     ORG 0040H
MAIN:  MOV      DPTR,#0BFFFH
       MOV      A,#0D1H
       MOVX     @DPTR,A
  WAIT:MOVX     A,@DPTR
       JB       ACC.7,WAIT
       MOV      A,#00H
       MOVX     @DPTR,A
       MOV      A,#2CH
       MOVX     @DPTR,A




     MOV SP,#60H
     MOV SCON,#50H
     MOV TMOD,#20H
     MOV TH1,#0E5H
     MOV  TL1,#0E5H
     MOV PCON,#00H
     SETB TR1
     SETB EA
     SETB ES
  L3:CLR 00H 
     CLR 01H
     CLR 02H
     CLR 03H
     MOV R6,#00H
     MOV R1 ,#30H
 L2:JB 03H,L1
    SJMP L2
 L1:ACALL SEND 
    AJMP L3
    
 ;;单片机接收中断子程序
 RECE:CLR ES
      CLR RI
      JB 00H,RECE1
      MOV A,SBUF
      CJNE A,#3FH,RECE2
      MOV A ,#2EH
      MOV SBUF,A
      JNB TI,$
      CLR TI
      SETB 00H
      SETB ES
      RETI
RECE2:MOV A,#24H
      MOV SBUF,A
      JNB TI,$
      CLR TI
      SETB ES
      RETI
RECE1:JB 01H,RECE4
      MOV A,SBUF
      MOV R7,A
      MOV R3,A
      SETB 01H
      SETB ES
      RETI
RECE4:JB 02H,RECE5
      MOV A,SBUF
      MOV @R0 ,A
      MOV B,A 
      LCALL LED 
      ADD A,R6
      MOV R6,A
      INC R0  
      DJNZ R7,RECE7
      SETB 02H
RECE7:SETB ES
      RETI
RECE5:MOV A,SBUF 
      CJNE A,06H,RECE8
      MOV A,#4FH
      MOV SBUF,A
      JNB TI,$
      CLR TI
      SETB 03H
      SETB ES
      RETI
RECE8:MOV R0 ,#30H
      MOV R6,#00H
      MOV A,R3
      MOV R7,A
      MOV A,#46H
      MOV SBUF ,A
      JNB TI,$
      CLR TI
      CLR 02H
      SETB ES
      RETI
      
   ;单片机查询发送子程序
 SEND:MOV A,#3FH
      MOV SBUF,A
      JNB TI,$
      CLR TI
      JNB RI,$
      CLR RI
      MOV A,SBUF
      CJNE A,#2EH,SEND
      
      MOV A,R7
      MOV R3,A
      MOV SBUF,A
      JNB TI,$
      CLR TI
      MOV R6,#00H
      MOV R0 ,#30H
SEND1:MOV A,@R0 
      MOV SBUF,A
      JNB TI,$
      CLR TI
      ADD A,R6
      MOV R6,A
      INC R0 
      DJNZ R7,SEND1
      MOV  A,R6
      MOV SBUF,A
      JNB TI,$
      CLR TI
      JNB RI,$
      CLR RI
      MOV A,SBUF
      CJNE A,#46H,SEND2
      RET
SEND2:MOV R0 ,#30H
      MOV R6,#00H
      MOV A,R3
      MOV R7,A
      AJMP SEND1
      
      


  LED: MOV      DPTR,#0BFFFH
       MOV      A,#90H
       MOVX      @DPTR,A
       
       MOV      R7,#01H
       MOV      DPTR,#0BFFEH
  LOOP:MOV A,B 
       ADD      A,#05H
       MOVC     A,@A+PC
       MOVX     @DPTR,A
       INC      R1
       DJNZ     R7,LOOP
       RET
       DB       3FH,06H,5BH,4FH,66H,6DH
       DB       7DH,07H,7FH,6FH 
 
  END                                  
                                                   