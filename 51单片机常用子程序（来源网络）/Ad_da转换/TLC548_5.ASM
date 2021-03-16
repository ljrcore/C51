;八位串行输出A/D转换器TLC548/549

         CS BIT P1.7      ；P1.7为a/d的片选信号
         AD_DATA EQU 20H  ；定义存放的数据区
TLC548AD:CLR CS
         ACALL AD_TSU
         CLR RI
         SETB REN
   WI_RI:JNB RI,WI_RI
         CLR REN
         CLR RI
         SETB CS
         MOV A,SBUF
         MOV AD_DATA,A
         RET
  AD_TSU:MOV 1FH,R6      ；延时子程序
         MOV R6,#02H
 AD_TS_1:DJNZ R6,AD_TS_1
         MOV R6,1FH
         RET                      