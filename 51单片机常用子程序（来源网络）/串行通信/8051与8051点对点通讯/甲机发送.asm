ORG 0000H 
LJMP MIAN
ORG 0023H
LJMP SERVE1
ORG 2000H
MAIN:MOV TMOD,#20H
      MOV TH1,#0F3H
      MOV TL1,#0F3H
      SETB TR1
      MOV PCON ,#80H
      MOV SCON,#0D0H
      MOV DPTR,#4000H
      MOV R0,#80H
      SETB ES
      SETB EA
      MOVX A,@DPTR
      MOV C,P
      MOV TB8,C
      MOV SBUF,A
      SJMP $
SERVE1:JBC RI,LOOP
       CLR TI
       SJMP ENDT
  LOOP:MOV A,SBUF 
       CLR C
       SUBB A,#01H
       JC LOOP1
       MOVX A,@DPTR
       MOV C,P
       MOV TB8,C
       MOV SBUF,A
       SJMP ENDT
 LOOP1:INC DPTR
       MOVX A,@DPTR
       MOV C,P
       MOV TB8,C
       MOV SBUF,A     
       DJNZ R0,ENDT
       CLR ES
  ENDT:RETI
       END        
                    