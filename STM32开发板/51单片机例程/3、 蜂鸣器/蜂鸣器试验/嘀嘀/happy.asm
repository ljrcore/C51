



		ORG	0000H			;αָ�ָ�������8000H��ʼ���
		AJMP	MAIN			;��תָ�������ת��MAIN��

		ORG	0100H			;αָ�ָ�����³����8100H��ʼ���
MAIN:
		MOV	SP,#60			;����ջָ�븳��ֵ
LOOP:		ACALL	MUSIC
		AJMP	LOOP


;***********************
;��������������ӳ���
;**********************
MUSIC:
		MOV	R5,#60H			;��������
MIC:
		CPL	P1.5
		ACALL	DELAY5MS		;��������
		DJNZ	R5,MIC
		RET


;***************
;��ʱ�ӳ���
;***************
DELAY5MS:
		    MOV	R7,#3H
DELAY0:		MOV	R6,#40H
DELAY1:		DJNZ	R6,DELAY1
	     	DJNZ	R7,DELAY0
	    	RET
		;
		END

