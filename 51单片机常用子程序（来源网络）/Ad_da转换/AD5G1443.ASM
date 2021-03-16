;;;;;5G14433A/D转换器中断程序
;;;；；；使用INT1中断
;;;；；；将采取的结果的千，百，十，个位数据分别放在RAM中21H-24H单元中





INTL1:MOV A,P1
      JNB ACC.4,INTL1
      JB ACC.0,ERR
      JB ACC.3,L2
      MOV 21H,#01H
      AJMP L3
   L2:MOV 21H,#00H
   L3:MOV A,P1
      JNB ACC.5,L3
      MOV R0,#22H
      XCHD A,@R0
   L4:MOV A,P1
      JNB ACC.6,L4
      INC R0
      XCHD A,@R0
   L5:MOV A,P1
      JNB ACC.7,L5
      INC R0
      XCHD A,@R0
      AJMP L6
  ERR:MOV 20H,#0FH
   L6:RETI                    
      
      