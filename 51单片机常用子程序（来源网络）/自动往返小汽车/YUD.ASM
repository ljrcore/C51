           ORG   0000H
             AJMP MAIN
             ORG  001BH
             LJMP  SEVER 
             ORG  0030H
        MAIN:
        TIME1H   EQU   74H               ;;¶¨Ê±Æ÷³õÖµ
        TIME1L   EQU   75H
        TIME2H   EQU   76H
        TIME2L   EQU   77H
        JISHU    EQU   78H
        

       CLR   00H
       CLR   01H
       CLR   02H
       CLR   03H
       CLR   04H
       CLR   05H
       CLR   06H
       CLR   07H
       CLR   08H
       CLR   09H
       CLR   10H
       CLR   78H
       SETB  EA
       SETB  ET1 
         
  
   YUNX:SETB  01H
        MOV  TIME1H,#9EH
        MOV  TIME1L ,#58H
        MOV  TIME2H,#9EH
        MOV  TIME2L,#58H 
        SETB  00H
        MOV  TMOD ,#10H

        SETB  P1.0
        CLR   P1.1

        MOV  TH1,TIME1H
        MOV  TL1,TIME1L
        SETB  P1.0
        CLR   P1.1
        SETB  TR1
HE: SETB  P1.4
    SETB  P1.5
    SETB  P1.6
    
    MOV  A,P1
    ANL  A,#00001110B
    JNZ    NEXT13
    SJMP  HE

NEXT13:LCALL   CHAXUN
       JBC     06H,NEXT21
       AJMP  HE
NEXT21:JNB   P1.4,DDP 
        AJMP NEXT21
 DDP:JNB   P1.4,DDP1 
     AJMP   DDP
DDP1:INC JISHU 
     MOV A,79H
     CJNE A,#02H,FANHUI 
    LJMP  QUANSU
 FANHUI:AJMP YUNX
    




