;��ȥ��ֵƽ���˲�10�β���������Ϊ˫�ֽڴ����BA��

;��r2r3�д�����ֵ��r4r5 �д����Сֵ��r6r7�д�Ž��



   DAV:CLR A
       MOV R2,A
       MOV R3,A
       MOV R6,A
       MOV R7,A
       MOV R4,#3FH
       MOV R5,#0FFH
       MOV R0,#0AH
  DAV1:LCALL RDXP          ;;;��A/D-��B��A�����ò����ӳ���
       MOV R1,A
       ADD A,R7
       MOV R7,A
       MOV A,B
       ADDC A,R6
       MOV R6,A
       CLR C
       MOV A,R3
       SUBB A,R1
       MOV A,R2
       SUBB A,B
       JNC DAV2
       MOV A,R1
       MOV R3,A
       MOV R2,B
  DAV2:CLR C
       MOV A,R1
       SUBB A,R5
       MOV A,B
       SUBB A,R4
       JNC DAV3
       MOV A,R1
       MOV R5,A
       MOV R4,B
  DAV3:DJNZ R0,DAV1

       MOV 62H,R6
       MOV 63H,R7
      
       CLR C
       MOV A,R7
       SUBB A,R3
       MOV R7,A
       MOV A,R6
       SUBB A,R2
       MOV R6,A
     
       CLR C
       MOV A,R7
       SUBB A,R5
       MOV R7,A
       MOV A,R6
       SUBB A,R4
       MOV R6,A
   
       MOV R0,#03H     ;;;;����λ����
YICHU1:CLR C 
       MOV A,R6
       RRC A
       MOV R6,A
       MOV A,R7
       RRC A
       MOV R7,A
       DJNZ R0,YICHU1
       RET
     
     

    
        
               
     