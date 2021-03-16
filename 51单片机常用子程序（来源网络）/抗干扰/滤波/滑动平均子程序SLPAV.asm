;;;滑动平均子程序SLPAV
;；采样为2字节，40次，存放首地址为DATA3，采样数据指针存于7EH中
;；和存于7BH，7CH，7DH中

SLPAV:MOV R0,7EH
       MOV A，R5
       ADD A,7DH
       MOV 7DH,A
       XCH A,R5
       XCH A,@R0
       XCH A,R5
       INC  R0
       MOV A,7CH
       ADDC A,R4
       MOV 7CH,A
       XCH A,R4
       XCH A,@R0
       XCH A,R4
       JNC SLPA0
       INC 7BH
 SLPA0:INC R0
       CJNE R0,#0D0H,SLPA1
       MOV R0,#80H
       JB 7CH,SLPA2
       SETB 7CH
       SJMP SLDIV
 SLPA1:JNB 7CH,ADRET
 SLPA2:MOV A,7DH
       CLR C
       SUBB A,R5
       MOV 7DH,A
       MOV A,7CH
       SUBB A,R4
       MOV 7CH,A
       JNC SLDIV
       DEC 7BH
 SLDIV:MOV R7,7DH
       MOV R6,7CH
       MOV R5,7BH
       MOV R4,#0
       MOV R3,#40
       MOV R2,#0
       LCALL DIV165
 ADRET:MOV 7EH,R0
       RET             
                     
             