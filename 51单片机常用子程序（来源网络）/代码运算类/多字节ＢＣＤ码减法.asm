;����������ֽ�����R7�У���������[R0]�У�������[R1]�С�
;������Ϣ������[R0]�У����λ��λ��CY�С�
;Ӱ����Դ��PSW��A��R2��R3    ��ջ����  ���ֽ�

BCDB:	LCALL	NEG1	;����[R1]ʮ����ȡ��
	LCALL	BCDA	;�����ֽڣ£ã���ӷ�����
	CPL	C	;������ӷ��Ľ�λ��־ת���ɽ�λ��־
	MOV	F0,C	;�;���λ��־
	LCALL	NEG1	;�ָ�����[R1]��ԭʼֵ
	MOV	C,F0    ;�ָ���λ��־
	RET
NEG1:	MOV	A,R0	;[R1]ʮ����ȡ���ӳ������
	XCH	A,R1	;����ָ��
	XCH	A,R0
	LCALL	NEG	;ͨ��[R0]ʵ��[R1]ȡ��
	MOV	A,R0
	XCH	A,R1	;����ָ��
	XCH	A,R0
	RET
;���ֽڣ£ã���ȡ��
NEG:	MOV	A,R7	;ȡ���ֽ�����һ����R2��
	DEC	A
	MOV	R2,A
	MOV	A,R0	;�;�ָ��
	MOV	R3,A
NEG0:	CLR	C	
	MOV	A,#99H
	SUBB	A,@R0	;���ֽ�ʮ����ȡ��
	MOV	@R0,A	;���[R0]��
	INC	R0	;��������ָ��
	DJNZ	R2,NEG0	;�����꣨R2���ֽ�
	MOV	A,#9AH	;����ֽڵ���ȡ��
	SUBB	A,@R0
	MOV	@R0,A
	MOV	A,R3	;�ָ�ָ��
	MOV	R0,A
	RET
;���ֽ�BCD��ӷ�
	BCDA:	MOV	A,R7	;ȡ�ֽ�����R2��
	MOV	R2,A
	ADD	A,R0	;��ʼ������ָ��
	MOV	R0,A
	MOV	A,R2
	ADD	A,R1
	MOV	R1,A
	CLR	C
BCD1:	DEC	R0	;��������ָ��
	DEC	R1
	MOV	A,@R0
	ADDC	A,@R1	;���ֽ����
	DA	A	;ʮ���Ƶ���
	MOV	@R0,A	;�ʹ��[R0]��
	DJNZ	R2,BCD1	;�����������ֽ�
	RET