             ORG   0000H
             AJMP MAIN
             
             ORG  0030H
        MAIN:
        TIME1H   EQU   74H      ;��ʱ����ֵ
        TIME1L   EQU    75H
        TIME2H   EQU    76H
        TIME2L   EQU    77H
        JISHU    EQU    78H
        A8279_1 EQU    0BFFFH
        A8279_2 EQU    0BFFEH

       MOV      DPTR,#A8279_1
       MOV      A,#0D1H
       MOVX     @DPTR,A
  WAIT:MOVX     A,@DPTR
       JB       ACC.7,WAIT
       MOV      A,#00H
       MOVX     @DPTR,A
       MOV      A,#2CH
       MOVX     @DPTR,A

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

       SETB  EA
       SETB  EX0

  START:LCALL  SEACH
        JBC   00H,YUNX
        AJMP   START
   YUNX:MOV  TIME1H,#9EH
        MOV  TIME1L ,#58H
        MOV  TMOD ,#10H

        SETB  P1.0
        CLR   P1.1

 LOOP20:       MOV  TH1,TIME1H
        MOV  TL1,TIME1L
        SETB  P1.0
        CLR   P1.1
        SETB  TR1
HE: JBC  TF1 , NEXT12
    MOV  P1,#10001111B
    MOV  A,P1
    ANL  A,#00001111B
    JNZ    NEXT13
    SJMP  HE

NEXT13:LCALL   CHAXUN
       JBC     06H,NEXT21
       AJMP  HE
NEXT21:LJMP  QUANSU
NEXT12:MOV  TH1,TIME1H
       MOV  TL1,TIME1L
       CLR   P1.0
       CLR   P1.1
HE1: JBC  TF1,  NEXT15
     MOV  P1,#00001111B
     MOV  A,P1
     ANL  A,#00001111B
     JNZ    NEXT14
     SJMP  HE1
NEXT15:AJMP    LOOP20
NEXT14:LCALL  CHAXUN
       JBC    06H,NEXT22
       AJMP  HE1
NEXT22:LJMP  QUANSU





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


QUANSU:SETB  P1.0
       CLR   P1.1
       LCALL  DELAY
       LCALL  CHAXUN
       JBC    06H,NEXT23
       AJMP   QUANSU
NEXT23:AJMP   JIANSU

JIANSU:MOV   TIME1H,#0CFH
       MOV   TIME1L,#2CH
       MOV   TIME2H,#92H
       MOV   TIME2L,#7CH

 LOOP30:MOV  TH1,TIME1H
        MOV  TL1,TIME1L
        SETB  P1.0
        CLR   P1.1
        SETB  TR1
HE2: JBC  TF1,  NEXT24
     MOV  P1,#10001111B
    MOV  A,P1
    ANL  A,#00001111B
    JNZ  NEXT25
    SJMP  HE2

NEXT25:LCALL   CHAXUN
       JBC     06H,NEXT26
       AJMP  HE2
NEXT26:LJMP  QUANSU1
NEXT24:MOV  TH1,TIME2H
       MOV  TL1,TIME2L
       CLR   P1.0
       CLR   P1.1
HE3: JBC  TF1 , NEXT27
     MOV   P1,#00001111B
     MOV  A,P1
     ANL  A,#00001111B
     JNZ   NEXT28
     SJMP  HE3
NEXT27:AJMP    LOOP30
NEXT28:LCALL  CHAXUN
       JBC    06H,NEXT29
       AJMP  HE3
NEXT29:LJMP  QUANSU1

QUANSU1:SETB  P1.0
        CLR   P1.1
        LCALL  DELAY
        LCALL  CHAXUN
        JBC    06H,NEXT30
        AJMP   QUANSU1
NEXT30:AJMP   JIANSU1

JIANSU1:MOV   TIME1H,#0CFH
       MOV   TIME1L,#2CH
       MOV   TIME2H,#92H
       MOV   TIME2L,#7CH

 LOOP40:MOV  TH1,TIME1H
        MOV  TL1,TIME1L
        SETB  P1.0
        CLR   P1.1
        SETB  TR1
HE4: JBC  TF1,  NEXT31
     MOV  P1,#10001111B
     MOV  A,P1
     ANL  A,#00001111B
     JNZ   NEXT32
     SJMP  HE4

NEXT32:LCALL   CHAXUN
       JBC     06H,NEXT33
       AJMP  HE4
NEXT33:LJMP  STOP
NEXT31:MOV  TH1,TIME2H
       MOV  TL1,TIME2L
       CLR   P1.0
       CLR   P1.1
HE5: JBC  TF1 , NEXT34
     MOV  P1,#00001111B
     MOV  A,P1
     ANL  A,#00001111B
     JNZ    NEXT35
     SJMP  HE5
NEXT34:AJMP    LOOP40
NEXT35:LCALL  CHAXUN
       JBC    06H,NEXT40
       AJMP  HE5
NEXT40:LJMP  STOP
STOP:CLR  P1.0
     CLR  P1.1

        MOV     R7,#0C8H      ;; ����12MHZ����ʱ10��
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
        MOV  TIME1H,#9EH
        MOV  TIME1L ,#58H
        MOV  TMOD ,#10H

        SETB  P1.1
        CLR   P1.0

 LOOP220:       MOV  TH1,TIME1H
        MOV  TL1,TIME1L
        SETB  P1.1
        CLR   P1.0
        SETB  TR1
HEH: JBC  TF1,  NEXT212
    MOV   P1,#01001111B
    MOV  A,P1
    ANL  A,#00001111B
    JNZ   NEXT213
    SJMP  HEH

NEXT213:LCALL   CHAXUN
       JBC     06H,NEXT221
       AJMP  HEH
NEXT221:LJMP  QUANSU2
NEXT212:MOV  TH1,TIME1H
       MOV  TL1,TIME1L
       CLR   P1.1
       CLR   P1.0
HEH1: JBC  TF1 , NEXT215
     MOV    P1,#00001111B
     MOV  A,P1
     ANL  A,#00001111B
     JNZ   NEXT214
     SJMP  HEH1
NEXT215:AJMP    LOOP220
NEXT214:LCALL  CHAXUN
       JBC    06H,NEXT222
       AJMP  HEH1
NEXT222:LJMP  QUANSU2







QUANSU2:SETB  P1.1
       CLR   P1.0
       LCALL  DELAY
       LCALL  CHAXUN
       JBC    06H,NEXT223
       AJMP   QUANSU
NEXT223:AJMP   JIANSU2

JIANSU2:MOV   TIME1H,#0CFH
       MOV   TIME1L,#2CH
       MOV   TIME2H,#92H
       MOV   TIME2L,#7CH

 LOOP230:MOV  TH1,TIME1H
         MOV  TL1,TIME1L
         SETB  P1.1
         CLR   P1.0
         SETB  TR1
HEH2: JBC  TF1 , NEXT224
    MOV  P1,#01001111B
    MOV  A,P1
    ANL  A,#00001111B
    JNZ   NEXT225
    AJMP  HEH2

NEXT225:LCALL   CHAXUN
       JBC     06H,NEXT226
       AJMP  HEH2
NEXT226:LJMP  QUANSU3
NEXT224:MOV  TH1,TIME2H
       MOV  TL1,TIME2L
       CLR   P1.1
       CLR   P1.0
HEH3: JBC  TF1,  NEXT227
     MOV  P1,#00001111B
     MOV  A,P1
     ANL  A,#00001111B
     JNZ    NEXT228
     SJMP  HEH3
NEXT227:AJMP    LOOP230
NEXT228:LCALL  CHAXUN
       JBC    06H,NEXT229
       AJMP  HEH3
NEXT229:LJMP  QUANSU3

QUANSU3:SETB  P1.1
        CLR   P1.0
        LCALL  DELAY
        LCALL  CHAXUN
        JBC    06H,NEXT230
        AJMP   QUANSU3
NEXT230:AJMP   JIANSU3

JIANSU3:MOV   TIME1H,#0CFH
       MOV   TIME1L,#2CH
       MOV   TIME2H,#92H
       MOV   TIME2L,#7CH

 LOOP240:MOV  TH1,TIME1H
        MOV  TL1,TIME1L
        SETB  P1.1
        CLR   P1.0
        SETB  TR1
HEH4: JBC  TF1 , NEXT231
     MOV    P1,#01001111B
     MOV  A,P1
     ANL  A,#00001111B
     JNZ   NEXT232
     SJMP  HEH4

NEXT232:LCALL   CHAXUN
       JBC     06H,NEXT233
       AJMP  HEH4
NEXT233:LJMP  STOP1
NEXT231:MOV  TH1,TIME2H
       MOV  TL1,TIME2L
       CLR   P1.1
       CLR   P1.0
HEH5: JBC  TF1 , NEXT234
     MOV   P1,#00001111B
     MOV  A,P1
     ANL  A,#00001111B
     JNZ    NEXT235
     SJMP  HEH5
NEXT234:AJMP    LOOP240
NEXT235:LCALL  CHAXUN
       JBC    06H,NEXT240
       AJMP  HEH5
NEXT240:LJMP  STOP1
STOP1:CLR  P1.1
       CLR  P1.0
LJMP    MAIN
;.............................................................................................

 ;;����12MHZ,��ʱ0.5��



DELAY:MOV 72H,#100
LOOP3:MOV 71H,#100
LOOP1:MOV 70H,#22
LOOP0:DJNZ 70H,LOOP0
      NOP
      DJNZ 71H,LOOP1
      MOV 70H,#46
LOOP2:DJNZ 70H,LOOP2
      NOP
      DJNZ 72H,LOOP3
      MOV 70H,#48
LOOP4:DJNZ 70H,LOOP4
      RET


SEACH:MOV      DPTR,#A8279_1
       MOVX     A,@DPTR
       ANL A,#07H
       JZ  RETUN4
       ACALL  KEY
       ACALL  LED
RETUN4:RET




   KEY:MOV  DPTR ,#A8279_1
       MOV  A,#40H
	   MOVX @DPTR,A
	   MOV DPTR,#A8279_2
	   MOVX A,@DPTR
	   ANL A,#3FH
       MOV 30H,A

 RETUN:RET



   LED:MOV      DPTR,#A8279_1
       MOV      A,#90H
       MOVX      @DPTR,A
       MOV      R1,#30H
       MOV      R7,#01H
       MOV      DPTR,#A8279_2
  LOOP:MOV      A,@R1
       ADD      A,#05H
       MOVC     A,@A+PC
       MOVX     @DPTR,A
       INC      R1
       DJNZ     R7,LOOP
       RET
       DB       3FH,06H,5BH,4FH,66H,6DH
       DB       7DH,07H,7FH,6FH,77H,7CH
       DB       39H,5EH,79H,71H

END

