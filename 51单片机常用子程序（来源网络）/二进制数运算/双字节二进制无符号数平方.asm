;�����������ƽ������R2��R3�С�
;������Ϣ�������R2��R3��R4��R5�С�
;Ӱ����Դ��PSW��A��B��R2��R5    ��ջ����  ���ֽ�

MUL2:	MOV	A,R3	;����R3ƽ��
	MOV	B,A
	MUL	AB
	MOV	R4,B	;�ݴ沿�ֻ�
	MOV	R5,A
	MOV	A,R2	;����R2ƽ��
	MOV	B,A
	MUL	AB
	XCH	A,R3	;�ݴ沿�ֻ���������R2��R3
	XCH	A,B
	XCH	A,R2
	MUL	AB	;����2��R2��R3
	CLR	C
	RLC	A
	XCH	A,B
	RLC	A
	JNC	MU20
	INC	R2	;�ۼ������
MU20:	XCH	A,B	;�ۼӲ��ֻ�
	ADD	A,R4
	MOV	R4,A
	MOV	A,R3
	ADDC A,B
	MOV	R3,A
	CLR	A
	ADDC	A,R2
	MOV	R2,A
	RET