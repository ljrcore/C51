;;全双工串行通信，甲机发送
；；工作方式2，每帧11位，第9位为奇偶校验用的补偶位
；；ADDR为数据块首址地址指针
；；发送128字节




          ORG 0000H
          LJMP TO_MAIN
          ORG 0023H
          LJMP TO_INTSE1
  TO_MAIN:MOV PCON,#80H
          MOV SCON,#10010000B
          MOV DPTR,#ADDR
          MOV R0,#00H
          SETB EA
          SETB ES
          MOVX A,@DPTR
          ADD A,#00H
          MOV C,P
          MOV TB8,C
          MOV SBUF,A
  W_MAINA:SJMP W_MAINA
TO_INTSE1:JB SCON.0,TO_LOOP
          CLR SCON.1
          SJMP ENDT
  TO_LOOP:CLR SCON.0
          MOV A,SBUF
          SUBB A,#01H
          JC LOOP3
          MOVX A,@DPTR
          ADD A,#00H
          MOV C,P
          MOV TB8,C
          MOV SBUF,A
          MOV SBUF,A
          SJMP TO_ENDT
    LOOP3:INC DPTR
          INC R0
          MOVX A,@DPTR
          ADD A,#00H
          MOV C,P
          MOV TB8,C
          MOV SBUF,A
          CJNE R0,#80H,TO_ENDT
          CLR ES
   TO_END:RETI             
          
          
          
          
          
          
          
          
                    
                             




TO_INTSE1:         