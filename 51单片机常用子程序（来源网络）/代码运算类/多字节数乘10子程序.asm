;���ֽ�����10�ӳ���D_MUL10
;������������ֽ�����λ�ֽڵ�ַ����R1�У��ֽ�������R7��
;���ڲ�����
;����Ӱ�죺A��R1��R2��R7��B
D_MUL10:	PUSH PSW
	PUSH ACC 
	PUSH B
	CLR C
	MOV R2,#00H
SH10:	MOV A,@R1
	MOV B,#0AH
	PUSH PSW
	ADDC A,R2
	MOV @R1,A
	MOV R2,B
	INC R1
	DJNZ R7,SH10
	MOV @R1,B
	POP B 
	POP ACC
	POP PSW
	RET 