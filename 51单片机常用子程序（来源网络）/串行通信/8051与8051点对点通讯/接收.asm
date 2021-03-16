      ORG 0000H
      LJMP MAIN 
      ORG 0023H
      LJMP SERVE2
      ORG 2000H
 MAIN:MOV TMOD ,#20H
      MOV TH1,#0F3H
      MOV TL1,#0F3H
      SETB TR1
      MOV PCON,#80H
      MOV SCON,#0D0H
      MOV DPTR,#4000H
      MOV R0,#80H
      SETB ES
      SETB EA
      SJMP $
SERVE2:JBC RI,LOOP
       CLR TI
       SJMP ENDT
 LOOP:MOV A,SBUF
      MOV C,P
      JC LOOP1
      ORL C,RB8
      JC LOOP2
      SJMP LOOP3
LOOP1:ANL C,RB8
      JC LOOP3
LOOP2:MOV A,#0FFH
      MOV SBUF,A
      SJMP ENDT
LOOP3:MOVX @DPTR,A
     MOV A,#00H
     MOV SBUF,A
     INC DPTR
     DJNZ R0,ENDT
     CLR ES
ENDT:RETI
     END     
                                   
      
             