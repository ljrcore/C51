 
;��ȥ��ֵƽ���˲�10�β���������Ϊ���ֽڴ����A��

;��r3�д�����ֵ��r5 �д����Сֵ��r6r7�д�Ž��




DAV:CLR A
     MOV R3,A
     MOV R6,A
     MOV R7,A
     MOV R5,#0FFH
     MOV R0,#0AH
DAV1:LCALL RDXP
     MOV R1,A
     ADD A,R7
     MOV R7,A
     MOV A,R6
     ADDC A,#00H
     MOV R6,A
     CLR C
     MOV A,R3
     SUBB A,R1
     JNC DAV2
     MOV A,R1
     MOV R3,A
DAV2:CLR C
     MOV A,R1
     SUBB A,R5
     JNC DAV3
     MOV A,R1
     MOV R5,A
DAV3:DJNZ R0,DAV1
     CLR C
     MOV A,R7
     SUBB A,R3
     MOV R7,A
     MOV A,R6
     SUBB A,#00H
     MOV R6,A
     CLR C
     MOV A,R7
     SUBB A,R5
     MOV R7,A
     MOV A,R6
     SUBB A,#00H
     MOV R6,A
     CLR C
     
     MOV R0,#03H     ;;;;����λ����
YICH:CLR C 
     MOV A,R6
     RRC A
     MOV R6,A
     MOV A,R7
     RRC A
     MOV R7,A
     DJNZ R0,YICH   
     RET   

           

