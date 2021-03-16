;;10位串行输出D/A转换器TLC5615
;;


           ORG   0500H
           DIN BIT  P1.4         ；定义I/O口
           SCLK BIT  P1.7
           D/A_CS BIT  P1.5
           DOUT BIT  P1.6
           DA_DATAH  EQU 30H     ;定义D/A的数据区
           DA_DATAL  EQU 31H
   TLC5615:CLR D/A_CS              ；；设置CS 为低电平
           ACALL    A_DELAY2       ；延时
           MOV R6,#08H
C_DA_LOOH:LCALL  A_DELAY2
          MOV A,DA_DATAH   ；装入高八位
          RLC A            ；从最高位D/A寄存器中移
          MOV DIN,C
          SETB SCLK
          MOV  DA_DATAH,A
          ACALL    A_DELAY2
          CLR  SCLK
          DJNZ R6,C_DA_LOOH
          MOV R6,#08H           
C_DA_LOOL:MOV A,DA_DATAL      ；装入低八位
          RLC A
          MOV DIN,C
          SETB SCLK
          MOV  DA_DATAL,A 
          LCALL  A_DELAY2                  
          CLR  SCLK
          DJNZ R6,C_DA_LOOL
          SETB D/A_CS
          RET