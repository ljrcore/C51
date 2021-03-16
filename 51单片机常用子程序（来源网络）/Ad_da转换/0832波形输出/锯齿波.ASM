;·´Ïà¾â³Ý²¨
       MOV  DPTR,#0DFFFH
  DA1:MOV  R6,#80H
  DA2:MOV  A,R6
      MOVX   @DPTR,A
      DJNZ   R6,DA2
      AJMP    DA1
  
  
  
 ;ÕýÏò¾â³Ý²¨ 
       MOV  DPTR,#0DFFFH
  DA1:MOV  R6,#80H
  DA2:MOV  A,R6
      MOVX  @DPTR,A
      INC  R6
      CJNE   R6,#0FFH,DA2
      AJMP   DA1    
      
      
 ;Ë«Ïò¾â³Ý²¨
         MOV DPTR,#0DFFFH
         MOV  R6,#00H
   DA1:MOV  A,R6
       MOVX  @DPTR,A
       INC   R6
       AJMP   DA1                       