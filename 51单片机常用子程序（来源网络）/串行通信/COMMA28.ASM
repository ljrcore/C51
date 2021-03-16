;;全双工串行通信，机发送
;；；工作方式2，每帧11位，第9位为奇偶校验用的补偶位
;；；ADDR1为数据块首址地址指针
;；；接收128字节

           ORG 0000H
           LJMP TO_MAINR
           ORG 0023H
           LJMP TO_INTSE2
           ORG 1000H
  TO_MAINR:MOV PCON,#80H
           MOV SCON,#10010000B
           MOV DPTR,ADDR1
           MOV R0,#00H
           SETB EA
           SETB ES
  W_MAIN_B:SJMP   W_MAIN_B
 TO_INTSE2:JB SCON.0,TO_LOOPR
           CLR SCON.1
           SJMP TO_ENDTR
  TO_LOOPR:CLR SCON.0
           MOV A,SBUF
           ADD A,#00H
           MOV C,P
           JC TO_LOOP1
           ORL C,RB8
           JC TO_LOOP2
           SJMP TO_LOOP3
  TO_LOOP1:ANL C ,RB8
           JC TO_LOOP3
  TO_LOOP2:MOV A,#0FFH
           MOV SBUF,A
           SJMP TO_ENDTR
  TO_LOOP3:MOVX @DPTR,A
           MOV A,00H
           MOV SBUF,A
           INC R0
           INC DPTR
           CJNE R0,#80H,TO_ENDTR
           CLR  ES
  TO_ENDTR:RETI         
                                                                              