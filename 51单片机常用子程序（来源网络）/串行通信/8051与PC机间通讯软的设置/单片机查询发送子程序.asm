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
      MOV DPTR,#1000H
SEND1:MOVX A,@DPTR
      MOV SBUF,A
      JNB TI
      CLR TI
      ADD A,R6
      MOV R6,A
      INC DPTR
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
SEND2:MOV DPTR,#1000H
      MOV R6,#00H
      MOV A,R3
      MOV R7,A
      AJMP SEND1
                  