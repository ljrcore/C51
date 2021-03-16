          ;串行口方式1的发送和接全双工
          
          
          
          
          MOV TMOD,#20H
          MOV TL1,#0F3H
          MOV TH1,#0F3H
          SETB TR1
          MOV SCON, #50H
          MOV R0,#20H    ;；发送数据首址
          MOV R1,#40H    ; ；接收数据首址
          ACALL SOUT
          SETB ES
          SETB EA
     LOOP:SJMP $
          ;;中断程序
          ORG 0023H
          AJMP SBR1
          ORG 0100H
     SBR1:JNB RI ,SEND
          ACALL SIN
          SJMP NEXT
     SEND:ACALL SOUT
     NEXT:RETI
     SOUT:CLR TI
          MOV A,@R0
          MOV C,P
          CPL C
          MOV ACC.7,C
          INC  R0
          MOV SBUF,A
          RET
      SIN:CLR RI
          MOV A,SBUF
          MOV C,P
          CPL C
          ANL A,#7FH
          MOV @R1,A
          INC R1
          RET
               
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
                