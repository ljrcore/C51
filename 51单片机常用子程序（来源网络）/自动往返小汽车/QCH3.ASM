     ORG   0000H
     AJMP  MAIN
     ORG   0030H
MAIN:

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
 YUNX:
           ;（3）中速
             ;正转
       SETB  P1.0
       CLR   P1.1 
       LCALL  DELAY3       

 LOOP5:SETB  P1.0
       CLR   P1.1
       MOV  71H,#10
LOOP2:MOV 70H,#200
LOOP1:MOV  P1,#10001111B
      JB   P1.4,NEXT1
      JB   P1.5,NEXT2
      JB   P1.6,NEXT3
      JB   P1.7,NEXT4
      JB   P2.7,NEXT5

      DJNZ  70H,LOOP1
      DJNZ 71H,LOOP2


       CLR   P1.0
       CLR   P1.1
       MOV  71H,#10
LOOP4:MOV 70H,#200
LOOP3:MOV  P1,#00001111B
      JB   P1.4,NEXT6
      JB   P1.5,NEXT7
      JB   P1.6,NEXT8
      JB   P1.7,NEXT9
      JB   P2.7,NEXT10

      DJNZ  70H,LOOP3
      DJNZ 71H,LOOP4
AJMP   LOOP5
 NEXT1:JB  P1.4,XINH1
       AJMP  LOOP1
 NEXT2:AJMP  LOOP1

 NEXT3:AJMP  LOOP1
 NEXT4:AJMP  LOOP1
 NEXT5:AJMP  LOOP1
 NEXT6:JB  P1.4,XINH1
       AJMP  LOOP3
 NEXT7:AJMP  LOOP3
 NEXT8:AJMP  LOOP3
 NEXT9:AJMP  LOOP3
 NEXT10:AJMP  LOOP3

 XINH1:AJMP   QUANSU1
 ;.........................................................................
 QUANSU1:SETB   P1.0
         CLR    P1.1
         LCALL   DELAY
   LOOP6:MOV    P1,#01001111B
         JB   P1.4,NEXT11
         JB   P1.5,NEXT12
         JB   P1.6,NEXT13
         JB   P1.7,NEXT14
         JB   P2.7,NEXT15
         AJMP   LOOP6
NEXT11:JB   P1.4,XINH2
       AJMP  LOOP6
NEXT12:AJMP  LOOP6
NEXT13:AJMP  LOOP6
NEXT14:AJMP  LOOP6
NEXT15:AJMP  LOOP6
XINH2:AJMP   JIANSU1
;...................................................................................
JIANSU1:
                                         ;慢速
       LCALL  DELAY3
 LOOP7:SETB  P1.0
       CLR   P1.1
       MOV  71H,#10
LOOP11:MOV 70H,#100
LOOP10:MOV  P1,#10001111B
      JB   P1.4,NEXT16
      JB   P1.5,NEXT17
      JB   P1.6,NEXT18
      JB   P1.7,NEXT19
      JB   P2.7,NEXT20

      DJNZ  70H,LOOP10
      DJNZ 71H,LOOP11


       CLR   P1.0
       CLR   P1.1
       MOV  71H,#10
LOOP9:MOV 70H,#300
LOOP8:MOV  P1,#00001111B
      JB   P1.4,NEXT21
      JB   P1.5,NEXT22
      JB   P1.6,NEXT23
      JB   P1.7,NEXT24
      JB   P2.7,NEXT25

      DJNZ  70H,LOOP8
      DJNZ 71H,LOOP9
AJMP   LOOP7
 NEXT16:JB  P1.4,XINH3
       AJMP  LOOP10
 NEXT17:AJMP  LOOP10

 NEXT18:AJMP  LOOP10
 NEXT19:AJMP  LOOP10
 NEXT20:AJMP  LOOP10
 NEXT21:JB  P1.4,XINH3
       AJMP  LOOP8
 NEXT22:AJMP  LOOP8
 NEXT23:AJMP  LOOP8
 NEXT24:AJMP  LOOP8
 NEXT25:AJMP  LOOP8
 XINH3: AJMP     QUANSU2
 
;;.............................................................................................................
 QUANSU2:
         SETB   P1.0
         CLR    P1.1
         LCALL  DELAY
   LOOP12:MOV    P1,#01001111B
         JB   P1.4,NEXT26
         JB   P1.5,NEXT27
         JB   P1.6,NEXT28
         JB   P1.7,NEXT29
         JB   P2.7,NEXT30
         AJMP   LOOP12
NEXT26:JB   P1.4,XINH4
       AJMP  LOOP6
NEXT27:AJMP  LOOP6
NEXT28:AJMP  LOOP6
NEXT29:AJMP  LOOP6
NEXT30:AJMP  LOOP6
XINH4:AJMP   JIANSU2


;......................................................................................
JIANSU2:            ;（3）中速
             ;正转
START7:LCALL   DELAY3
 LOOP13:SETB  P1.0
       CLR   P1.1
       MOV  71H,#10
LOOP15:MOV 70H,#200
LOOP14:MOV  P1,#10001111B
      JB   P1.4,NEXT31
      JB   P1.5,NEXT32
      JB   P1.6,NEXT33
      JB   P1.7,NEXT34
      JB   P2.7,NEXT35

      DJNZ  70H,LOOP14
      DJNZ 71H,LOOP15


       CLR   P1.0
       CLR   P1.1
       MOV  71H,#10
LOOP16:MOV 70H,#200
LOOP17:MOV  P1,#00001111B
      JB   P1.4,NEXT36
      JB   P1.5,NEXT37
      JB   P1.6,NEXT38
      JB   P1.7,NEXT39
      JB   P2.7,NEXT40

      DJNZ  70H,LOOP17
      DJNZ 71H,LOOP16
AJMP   LOOP13
 NEXT31:JB  P1.4,XINH5
        AJMP  LOOP14
 NEXT32:AJMP  LOOP14

 NEXT33:AJMP  LOOP14
 NEXT34:AJMP  LOOP14
 NEXT35:AJMP  LOOP14
 NEXT36:JB  P1.4,XINH5
       AJMP  LOOP17
 NEXT37:AJMP  LOOP17
 NEXT38:AJMP  LOOP17
 NEXT39:AJMP  LOOP17
 NEXT40:AJMP  LOOP17

 XINH5:AJMP  STOP1
;....................................................................................................
STOP1:CLR  P1.0
      CLR   P1.1
      ;;晶振12MHZ,延时10秒


       MOV  R7,#10
DELAY1:MOV 72H,#100
LOOP21:MOV 71H,#100
LOOP19:MOV 70H,#47
LOOP18:DJNZ 70H,LOOP18
       NOP
       DJNZ 71H,LOOP19
       MOV 70H,#46
LOOP20:DJNZ 70H,LOOP20
       NOP
       DJNZ 72H,LOOP21
       MOV 70H,#48
LOOP22:DJNZ 70H,LOOP22
       DJNZ  R7,DELAY1

;....................................................................................................
;$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
  ;（3）中速
             ;反转
        SETB  P1.0
        SETB  P1.1
        LCALL DELAY3 
 LOOPF5:SETB  P1.0
       CLR   P1.1
       MOV  71H,#10
LOOPF2:MOV 70H,#200
LOOPF1:MOV  P1,#10001111B
      JB   P1.4,NEXTF1
      JB   P1.5,NEXTF2
      JB   P1.6,NEXTF3
      JB   P1.7,NEXTF4
      JB   P2.7,NEXTF5

      DJNZ  70H,LOOPF1
      DJNZ 71H,LOOPF2


       CLR   P1.0
       CLR   P1.1
       MOV  71H,#10
LOOPF4:MOV 70H,#200
LOOPF3:MOV  P1,#00001111B
      JB   P1.4,NEXTF6
      JB   P1.5,NEXTF7
      JB   P1.6,NEXTF8
      JB   P1.7,NEXTF9
      JB   P2.7,NEXTF10

      DJNZ  70H,LOOPF3
      DJNZ 71H,LOOPF4
AJMP   LOOPF5
 NEXTF1:JB  P1.4,XINHF1
       AJMP  LOOPF1
 NEXTF2:AJMP  LOOPF1

 NEXTF3:AJMP  LOOPF1
 NEXTF4:AJMP  LOOPF1
 NEXTF5:AJMP  LOOPF1
 NEXTF6:JB  P1.4,XINHF1
       AJMP  LOOPF3
 NEXTF7:AJMP  LOOPF3
 NEXTF8:AJMP  LOOPF3
 NEXTF9:AJMP  LOOPF3
 NEXTF10:AJMP  LOOPF3

 XINHF1:AJMP   QUANSUF1
 ;.........................................................................
 QUANSUF1:SETB   P1.0
         CLR    P1.1
         LCALL   DELAY
   LOOPF6:MOV    P1,#01001111B
         JB   P1.4,NEXTF11
         JB   P1.5,NEXTF12
         JB   P1.6,NEXTF13
         JB   P1.7,NEXTF14
         JB   P2.7,NEXTF15
         AJMP   LOOP6
NEXTF11:JB   P1.4,XINHF2
       AJMP  LOOPF6
NEXTF12:AJMP  LOOPF6
NEXTF13:AJMP  LOOPF6
NEXTF14:AJMP  LOOPF6
NEXTF15:AJMP  LOOPF6
XINHF2:AJMP   JIANSUF1
;...................................................................................
JIANSUF1:
                                         ;慢速
       LCALL  DELAY3
 LOOPF7:SETB  P1.0
       CLR   P1.1
       MOV  71H,#10
LOOPF11:MOV 70H,#100
LOOPF10:MOV  P1,#10001111B
      JB   P1.4,NEXTF16
      JB   P1.5,NEXTF17
      JB   P1.6,NEXTF18
      JB   P1.7,NEXTF19
      JB   P2.7,NEXTF20

      DJNZ  70H,LOOPF10
      DJNZ 71H,LOOPF11


       CLR   P1.0
       CLR   P1.1
       MOV  71H,#10
LOOPF9:MOV 70H,#300
LOOPF8:MOV  P1,#00001111B
      JB   P1.4,NEXTF21
      JB   P1.5,NEXTF22
      JB   P1.6,NEXTF23
      JB   P1.7,NEXTF24
      JB   P2.7,NEXTF25

      DJNZ  70H,LOOPF8
      DJNZ 71H,LOOPF9
AJMP   LOOPF7
 NEXTF16:JB  P1.4,XINHF3
       AJMP  LOOPF10
 NEXTF17:AJMP  LOOPF10

 NEXTF18:AJMP  LOOPF10
 NEXTF19:AJMP  LOOPF10
 NEXTF20:AJMP  LOOPF10
 NEXTF21:JB  P1.4,XINHF3
       AJMP  LOOPF8
 NEXTF22:AJMP  LOOPF8
 NEXTF23:AJMP  LOOPF8
 NEXTF24:AJMP  LOOPF8
 NEXTF25:AJMP  LOOPF8
 XINHF3:  AJMP QUANSUF2
;.............................................................................................................
 QUANSUF2:SETB   P1.0
         CLR    P1.1
         LCALL  DELAY
   LOOPF12:MOV    P1,#01001111B
         JB   P1.4,NEXTF26
         JB   P1.5,NEXTF27
         JB   P1.6,NEXTF28
         JB   P1.7,NEXTF29
         JB   P2.7,NEXTF30
         AJMP   LOOPF12
NEXTF26:JB   P1.4,XINHF4
       AJMP  LOOP6
NEXTF27:AJMP  LOOPF6
NEXTF28:AJMP  LOOPF6
NEXTF29:AJMP  LOOPF6
NEXTF30:AJMP  LOOPF6
XINHF4:AJMP   JIANSUF2


;......................................................................................
 JIANSUF2:           ;（3）中速
             ;正转
STARTF7:LCALL   DELAY3
 LOOPF13:SETB  P1.0
       CLR   P1.1
       MOV  71H,#10
LOOPF15:MOV 70H,#200
LOOPF14:MOV  P1,#10001111B
      JB   P1.4,NEXTF31
      JB   P1.5,NEXTF32
      JB   P1.6,NEXTF33
      JB   P1.7,NEXTF34
      JB   P2.7,NEXTF35

      DJNZ  70H,LOOPF14
      DJNZ 71H,LOOPF15


       CLR   P1.0
       CLR   P1.1
       MOV  71H,#10
LOOPF16:MOV 70H,#200
LOOPF17:MOV  P1,#00001111B
      JB   P1.4,NEXTF36
      JB   P1.5,NEXTF37
      JB   P1.6,NEXTF38
      JB   P1.7,NEXTF39
      JB   P2.7,NEXTF40

      DJNZ  70H,LOOPF17
      DJNZ 71H,LOOPF16
AJMP   LOOPF13
 NEXTF31:JB  P1.4,XINHF5
        AJMP  LOOPF14
 NEXTF32:AJMP  LOOPF14

 NEXTF33:AJMP  LOOPF14
 NEXTF34:AJMP  LOOPF14
 NEXTF35:AJMP  LOOPF14
 NEXTF36:JB  P1.4,XINHF5
       AJMP  LOOPF17
 NEXTF37:AJMP  LOOPF17
 NEXTF38:AJMP  LOOPF17
 NEXTF39:AJMP  LOOPF17
 NEXTF40:AJMP  LOOPF17

 XINHF5:AJMP  STOPF1
;....................................................................................................
STOPF1:CLR  P1.0
      CLR   P1.1
GGG:SJMP   GGG
;.....................................................................................................



















 ;;晶振12MHZ,延时0.25秒



DELAY3:MOV 72H,#100
LOOP31:MOV 71H,#100
LOOP29:MOV 70H,#10
LOOP28:DJNZ 70H,LOOP28
      DJNZ 71H,LOOP29
      MOV 70H,#46
LOOP30:DJNZ 70H,LOOP30
      NOP
      DJNZ 72H,LOOP31
      MOV 70H,#48
LOOP32:DJNZ 70H,LOOP32
       RET

 ;;晶振12MHZ,延时0.5秒



DELAY:MOV 72H,#100
LOOP26:MOV 71H,#100
LOOP24:MOV 70H,#22
LOOP23:DJNZ 70H,LOOP23
      NOP
      DJNZ 71H,LOOP24
      MOV 70H,#46
LOOP25:DJNZ 70H,LOOP25
      NOP
      DJNZ 72H,LOOP26
      MOV 70H,#48
LOOP27:DJNZ 70H,LOOP27
      RET


 




  
 
END
