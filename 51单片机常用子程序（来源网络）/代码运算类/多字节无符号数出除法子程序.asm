;���ֽ��޷������������ӳ���D_NIDIV
;����������������ĵ�λ��ַ����R0�У�������R1��
;���ڲ������̴��ڱ�����������������Ϊ0����A����0������A����0FFH ,R3����ֽ�����
;����Ӱ�죺A,R7,R6,R5,R4,R0,R1,R3,
D_NIDIV:	MOV A,R0
	MOV R4,A
	MOV A,R1
	MOV R5,A
	MOV A,R3
	MOV R7,A
	LCALL N_ZERO
	JZ TO_SA41
	MOV A,R5
	MOV R1,A
	MOV A,R7
	MOV R3,A 
	LCALL D_NIDIV1
	MOV A,#0FFH
	MOV A,R7
	MOV R3,A
TO_SA41:	RET
N_ZERO:	MOV A,@R1
	JNZ SF40END
	INC R1
	DJNZ R3,N_ZERO
SF40END:	RET 