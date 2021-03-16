;;;;右移位除



 YICHU:MOV R0,#03H     ;;;;；移位次数
YICHU1:CLR C 
       MOV A,R6
       RRC A
       MOV R6,A
       MOV A,R7
       RRC A
       MOV R7,A
       DJNZ R0,YICHU1
       RET