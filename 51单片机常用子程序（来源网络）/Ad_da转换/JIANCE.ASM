;;;ADC0809八路巡回检测系统
；；； 将读数依次存放在片外数据存储器A0-A7H单元



    MAIN:MOV R0,#0A0H   ；数据存储器首址
         MOV R2,#08H
         SETB IT1
         SETB EA
         SETB EX1
         MOV DPTR,#7FF8H     ；DAC0809首址
         MOVX @DPTR,A        ；启动AD转换
    HERE:SJMP HERE
    INT1:MOVX A,@DPTR
         MOVX @R0,A
         INC DPTR
         INC R0
         DJNZ R2,DONE
         RETI
   DONE:MOVX @DPTR,A
        RETI                