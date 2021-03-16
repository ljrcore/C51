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
      MOVX @DPTR,A
      ADD A,R6
      MOV R6,A
      INC DPTR 
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
RECE8:MOV DPTR,#1000H
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
      
                                          