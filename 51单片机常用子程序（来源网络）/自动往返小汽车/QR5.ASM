             ORG   0000H
             AJMP MAIN
             ORG  001BH
             LJMP  SEVER 
             ORG  0030H
        MAIN:
        TIME1H   EQU   74H               ;;定时器初值
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

        SETB  P1.2
        CLR   P1.3

        MOV  TH1,TIME1H
        MOV  TL1,TIME1L
        SETB  P1.2
        CLR   P1.3
        SETB  TR1
HE: SETB  P1.4
    SETB  P1.5
    SETB  P1.6
    
    ;MOV  A,P1
    ;ANL  A,#00001110B
    ;JNZ    NEXT13
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
    






;.................................................................

QUANSU:SETB  P1.2
       CLR   P1.3
       LCALL  CHAXUN
       JBC    06H,NE26
NE26:JB  P1.4,NEXT23        
       AJMP   QUANSU
NEXT23:JNB   P1.4,NE24 
       AJMP  NEXT23
  NE24:JNB   P1.4,NE25
       AJMP   NE25 
 NE25:INC  JISHU 
       AJMP   JIANSU
;..................................................................

JIANSU:MOV   TIME1H,#0CFH
       MOV   TIME1L,#2CH
       MOV   TIME2H,#92H
       MOV   TIME2L,#7CH

 LOOP30:MOV  TH1,TIME1H
        MOV  TL1,TIME1L
        SETB  P1.2
        CLR   P1.3
        SETB  TR1
HE2: 
    MOV  P1,#10001111B
    MOV  A,P1
    ANL  A,#00001110B
    JNZ  NEXT25
    SJMP  HE2

NEXT25:LCALL   CHAXUN
       JBC     06H,NEXT26
       AJMP  HE2
NEXT26:JNB   P1.4,NE27
       AJMP  NEXT26 
  NE27:JNB  P1.4,NE28
       AJMP  NE27      
  NE28:INC    JISHU   
        LJMP  QUANSU1
;.......................................................................      

QUANSU1:SETB  P1.2
        CLR   P1.3
        
        LCALL  CHAXUN
        JBC    06H,NE29
   NE29:JB    P1.4,NEXT30      
        AJMP   QUANSU1
NEXT30:JNB   P1.4,NE30
        AJMP  NEXT30 
NE30:JNB    P1.4,NE31
     AJMP   NE30
  NE31:INC  JISHU 
       AJMP   JIANSU1
;.....................................................................
JIANSU1:MOV   TIME1H,#0CFH
       MOV   TIME1L,#2CH
       MOV   TIME2H,#92H
       MOV   TIME2L,#7CH

 LOOP40:MOV  TH1,TIME1H
        MOV  TL1,TIME1L
        SETB  P1.2
        CLR   P1.3
        SETB  TR1
HE4:SETB  P1.4
    SETB  P1.5
    SETB  P1.6
     MOV  A,P1
     ANL  A,#00001110B
     JNZ   NEXT32
     SJMP  HE4

NEXT32:LCALL   CHAXUN
       JBC     06H,NEXT33
       AJMP  HE4
NEXT33:INC  JISHU 
       LJMP  STOP   

STOP:CLR   TR1 
        CLR  P1.2
        CLR  P1.3

        MOV     R7,#0C8H      ;; 晶振12MHZ，延时10秒
        CLR     EX0
        MOV     TMOD,#01H
        MOV     TL0,#0B0H
        MOV     TH0,#3CH
        SETB    TR0
   HERE:JBC     TF0,NEXT1
        SJMP    HERE
  NEXT1:MOV     TL0,#0B0H
        MOV     TH0,#3CH
        DJNZ    R7,HERE
        CLR     TR0
        SETB    EX0

;..........................................................................
;$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
        SETB  EA
        SETB  ET1 
        SETB   02H
  
YUXIN2: MOV  TIME1H,#9EH
        MOV  TIME1L ,#58H
        MOV  TIME2H,#9EH
        MOV  TIME2L,#58H 
        SETB  00H
        MOV  TMOD ,#10H

        SETB  P1.3
        CLR   P1.2

        MOV  TH1,TIME1H
        MOV  TL1,TIME1L
        SETB  P1.3
        CLR   P1.2
        SETB  TR1
HEJ: SETB  P1.4
    SETB  P1.5
    SETB  P1.6
    
    MOV  A,P1
    ANL  A,#00001110B
    JNZ    NEXTJ13
    SJMP  HEJ

NEXTJ13:LCALL   CHAXUN
       JBC     06H,NEXTJ21
       AJMP  HE
NEXTJ21:JNB   P1.4,DDPJ 
        AJMP NEXT21
 DDPJ:JNB   P1.4,DDPJ1 
     AJMP   DDPJ
DDPJ1:   INC  JISHU 
     MOV  A,JISHU 
  CJNE  A,#08H,FANHUI2   
  LJMP  QUANSUJ
FANHUI2:AJMP  YUXIN2





CHAXUN:JB   P1.4,NEXT16
       JB   P1.5,NEXT17
       JB   P1.6,NEXT18
       JB   P1.7,NEXT19
       JB   P2.6,NEXT20
       RET
NEXT16:SETB   06H
       INC  JISHU
       RET
NEXT17:SETB   07H
       RET
NEXT18:SETB   08H
       RET
NEXT19:SETB   09H
       RET
NEXT20:SETB   10H
       RET
;.................................................................

QUANSUJ:SETB  P1.3
       CLR   P1.2
       LCALL  CHAXUN
       JBC    06H,NEJ26
NEJ26:JB  P1.4,NEXTJ23        
       AJMP   QUANSUJ
NEXTJ23:JNB   P1.4,NEJ24 
       AJMP  NEXTJ23
  NEJ24:JNB   P1.4,NEJ25
       AJMP   NE25 
 NEJ25: AJMP   JIANSUJ
;..................................................................
JIANSUJ:MOV   TIME1H,#0CFH
       MOV   TIME1L,#2CH
       MOV   TIME2H,#92H
       MOV   TIME2L,#7CH

 LOOPJ30:MOV  TH1,TIME1H
        MOV  TL1,TIME1L
        SETB  P1.3
        CLR   P1.2
        SETB  TR1
HEJ2: 
    MOV  P1,#10001111B
    MOV  A,P1
    ANL  A,#00001110B
    JNZ  NEXTJ25
    SJMP  HEJ2

NEXTJ25:LCALL   CHAXUN
       JBC     06H,NEXTJ26
       AJMP  HEJ2
NEXTJ26:JNB   P1.4,NEJ27
       AJMP  NEXT26 
  NEJ27:JNB  P1.4,NEJ28
       AJMP  NEJ27      
  NEJ28:     LJMP  QUANSUJ1
;.......................................................................      

QUANSUJ1:SETB  P1.3
        CLR   P1.2
        
        LCALL  CHAXUN
        JBC    06H,NEJ29
   NEJ29:JB    P1.4,NEXTJ30      
        AJMP   QUANSUJ1
NEXTJ30:JNB   P1.4,NEJ30
        AJMP  NEXTJ30 
NEJ30:JNB    P1.4,NEJ31
     AJMP   NE30
  NEJ31:AJMP   JIANSUJ1
;.....................................................................
JIANSUJ1:MOV   TIME1H,#0CFH
       MOV   TIME1L,#2CH
       MOV   TIME2H,#92H
       MOV   TIME2L,#7CH

 LOOPJ40:MOV  TH1,TIME1H
        MOV  TL1,TIME1L
        SETB  P1.3
        CLR   P1.2
        SETB  TR1
HEJ4:SETB  P1.4
    SETB  P1.5
    SETB  P1.6
     MOV  A,P1
     ANL  A,#00001110B
     JNZ   NEXTJ32
     SJMP  HEJ4

NEXTJ32:LCALL   CHAXUN
       JBC     06H,NEXTJ33
       AJMP  HEJ4
NEXTJ33:LJMP  STOP1

STOP1:CLR   TR1 
        CLR  P1.2
        CLR  P1.3

      
  HERE9:SJMP  HERE9
;.............................................................................................



SEVER:JB 00H,SHUJU1
      MOV  TH1,TIME1H
      MOV  TL1,TIME1L 
      JB  02H,DK1 
      SETB P1.2
      CLR  P1.3
      SETB  00H
      RETI 
 DK1:SETB  P1.3
     CLR   P1.2  
     SETB  00H 
     RETI
SHUJU1:MOV  TH1,TIME2H
       MOV  TL1,TIME2L
       
       CLR  P1.2
       CLR  P1.3
       CLR  00H
       RETI     

END

