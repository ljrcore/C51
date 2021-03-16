      ORG 0000H
      AJMP MAIN
      ORG  0030H
  MAIN:ADDR8279_1 EQU    0BFFFH
       ADDR8279_2 EQU    0BFFEH
  
       MOV      DPTR,#ADDR8279_1
       MOV      A,#0D1H
       MOVX     @DPTR,A
 WAIT1:MOVX     A,@DPTR
       JB       ACC.7,WAIT1
       MOV      A,#00H
       MOVX     @DPTR,A
       MOV      A,#2CH
       MOVX     @DPTR,A
  DDDD:MOV      DPTR,#ADDR8279_1   
       MOVX     A,@DPTR
       ANL A,#07H
       JZ  DDDD
       LJMP KEY 
        
  FFFF:MOV     60H,#00H
       MOV     61H,#00H
       MOV     62H,#00H
       MOV     TMOD,#15H
       MOV     TL0,#00H
       MOV     TH0,#00H
         
       MOV     R7,#14H
      
       MOV     TL1,#00H
       MOV     TH1,#4CH
       SETB TR1
       SETB TR0  
 HERE:JBC     TF1,NEXT1
      
      SJMP    HERE

NEXT1:MOV     TL1,#00H
      MOV     TH1,#4CH
      DJNZ    R7,HERE
      CLR     TR0
      CLR     TR1
      AJMP    PINYU
PINYU:MOV R6,TH0
      MOV R7,TL0
      JNB     TF0,NEXT2         
      MOV 60H,#06H
      MOV 61H,#55H
      MOV 62H,#36H 
      CLR  TF0   
      
NEXT2:LCALL  HB2
      MOV    R7,#03H
      MOV    65H,R3
      MOV    66H,R4
      MOV    67H,R5
      MOV    R0,#60H
      MOV    R1,#65H
      LCALL BCDA 
      LCALL TRANS
      LCALL LED
      MOV      DPTR,#ADDR8279_1   
      MOVX     A,@DPTR
      ANL A,#07H
      JZ  RETUN5
      LJMP KEY
RETUN5:AJMP FFFF

KEY:MOV  DPTR ,#ADDR8279_1
	MOV  A,#40H
	MOVX @DPTR,A
	MOV DPTR,#ADDR8279_2
	MOVX A,@DPTR
	ANL A,#3FH

        CJNE A,#0AH,KEY1        
        LJMP FFFF
   KEY1:CJNE A,#0BH,KEY2   
        LJMP KAI
   KEY2:AJMP  MAIN     

   KAI:MOV     TMOD,#01H
  KAI0:MOV     TL0,#00H
       MOV     TH0,#00H
      
  KAI1:SETB P1.0
       
       JB P1.0,KAI2
       SJMP KAI1          
  KAI2:SETB TR0
       SETB P1.0 
       
       JNB P1.0,KAI3 
       SJMP KAI2
  KAI3:CLR TR0 
       MOV R6,TH0
       MOV R7,TL0
       LCALL  HB2
       MOV 60H,R3
       MOV 61H,R4
       MOV 62H,R5
       LCALL   TRANS
       LCALL   LED
       MOV      DPTR,#ADDR8279_1   
       MOVX     A,@DPTR
       ANL A,#07H
       JZ  RETUN6
       LJMP KEY
 RETUN6:AJMP KAI0    
  ;;������  ��ţ�  �£ãģ�    ���ܣ����ֽڣ£ã���ӷ�

;;����������ֽ�����R7�У���������[R0]�У�������[R1]�С�
;;������Ϣ������[R0]�У����λ��λ��CY�С�
;;;Ӱ����Դ��PSW��A��R2    ��ջ����  ���ֽ�

BCDA:	MOV	A,R7	;;��ȡ�ֽ�����R2��
	MOV	R2,A
	ADD	A,R0	;;����ʼ������ָ��
	MOV	R0,A
	MOV	A,R2
	ADD	A,R1
	MOV	R1,A
	CLR	C
BCD1:	DEC	R0	;;����������ָ��
	DEC	R1
	MOV	A,@R0
	ADDC	A,@R1	;;�����ֽ����
	DA	A	;;��ʮ���Ƶ���
	MOV	@R0,A	;;���ʹ��[R0]��
	DJNZ	R2,BCD1	;;�������������ֽ�
	RET






;;;�����������ת����˫�ֽ�ʮ������������R6��R7�С�
;;������Ϣ��ת��������ֽڣ£ã���������R3��R4��R5�С�
;;Ӱ����Դ��PSW��A��R2��R7    ��ջ����  ���ֽ�

HB2:CLR	A	;;���£ã����ʼ��
	MOV	R3,A
	MOV	R4,A
	MOV	R5,A
	MOV	R2,#10H	;;��ת��˫�ֽ�ʮ����������
HB3:MOV	A,R7	;;���Ӹ߶��Ƴ���ת������һλ��CY��
	RLC	A
	MOV	R7,A
	MOV	A,R6
	RLC	A
	MOV	R6,A
	MOV	A,R5	;;���£ã������λ������ӣ��൱�ڳˣ�
	ADDC	A,R5
	DA	A	;;��ʮ���Ƶ���
	MOV	R5,A
	MOV	A,R4
	ADDC	A,R4
	DA	A
	MOV	R4,A
	MOV	A,R3
	ADDC	A,R3
	MOV	R3,A	;;��˫�ֽ�ʮ������������λ���������������õ���
	DJNZ	R2,HB3    ;;	�������꣱������
	RET
	
TRANS: MOV R0,#62H
       MOV R1,#40H
       MOV R6,#03H
  LAST:MOV      A,@R0
       ANL      A,#0FH
       MOV      @R1,A
       MOV      A,@R0
       ANL      A,#0F0H
       SWAP     A
       INC  R1
       MOV      @R1,A
       INC  R1
       DEC R0
       DJNZ R6,LAST
       RET
       
  LED:MOV      DPTR,#ADDR8279_1
       MOV      A,#90H
       MOVX      @DPTR,A
       MOV      R1,#40H
       MOV      R7,#06H
       MOV      DPTR,#ADDR8279_2
  LOOP:MOV      A,@R1
       ADD      A,#05H
       MOVC     A,@A+PC
       MOVX     @DPTR,A 
       INC      R1
       DJNZ     R7,LOOP
       RET
       DB       3FH,06H,5BH,4FH,66H,6DH
       DB       7DH,07H,7FH,6FH 
     	
END	    
SEACH1:MOV      DPTR,#ADDR8279_1   
       MOVX     A,@DPTR
       ANL A,#07H
       JZ  RETUN4
       LJMP KEY
 RETUN4:RET
END
 
        
        
  


 

