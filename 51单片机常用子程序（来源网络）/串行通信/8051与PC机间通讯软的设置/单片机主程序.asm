;;单片机主程序
     ORG 0000H
     AJMP MAIN
     ORG 0023H
     AJMP RECE
     ORG 0040H
MAIN:MOV SP,#60H
     MOV SCON,#50H
     MOV TMOD,#20H
     MOV TH1,#0F3H
     M0V TL1,#0F3H
     MOV PCON,#00H
     SETB TR1
     SETB EA
     SETB ES
  L3:CLR 00H 
     CLR 01H
     CLR 02H
     CLR 03H
     MOV R6,#00H
     MOV DPTR,#1000H
 L2:JB 03H,L1
    SJMP L2
 L1:ACALL SEND 
    AJMP L3
                
     
     
          