;����������ֽ�����R7�У���������[R0]�С�
;������Ϣ���������[R0]�С�
;Ӱ����Դ��PSW��A��R2��R3    ��ջ����  ���ֽ�

NEG:	MOV	A,R7	;ȡ���ֽ�����һ����R2��
	DEC	A
	MOV	R2,A
	MOV	A,R0  ;	����ָ��
	MOV	R3,A
NEG0:	CLR	C	
	MOV	A,#99H
	SUBB	A,@R0	;���ֽ�ʮ����ȡ��
	MOV	@R0,A	;���[R0]��
	INC	R0	    ;��������ָ��
	DJNZ	R2,NEG0	;�����꣨R2���ֽ�
	MOV	A,#9AH	;����ֽڵ���ȡ��
	SUBB	A,@R0
	MOV	@R0,A
	MOV	A,R3	;�ָ�ָ��
	MOV	R0,A
	RET
