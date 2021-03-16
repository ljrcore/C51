;Èý½Ç²¨
      MOV  DPTR,#0DFFFH
DA1:MOV  R6,#80H
DA2:MOV A,R6
    MOVX   @DPTR,A
    INC  R6
    CJNE   R6,#0FFH,DA2
DA3:DEC  R6
    MOV  A,R6
    MOVX   @DPTR,A
    CJNE   R6,#80H,DA3
    AJMP   DA1     
              