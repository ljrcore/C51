      ;; ����128�����ݣ��������ݾ�Ϊ���ֽڣ�����ָ��ΪDATA_B1������DATA_B2��ʼ�ĵ�ַ��Ԫ�У�����Ӧ�Ŀ���������0820H��ʼ�ĵ�ַ��Ԫ�У���Ӧ�����������ݴӴ�С���С�����R4��R5�����ݲ��ұȽϽӽ���һ�����ݣ����ҳ���Ӧ�����������
      ;;;;�����嵥��
    DATA_B1  EQU  0204H		;������ָ��
    DATA_B2  EQU  0200H		; ����ַ
RAED_ROM:MOV    DPTR,#DATA_B1   ;��������ָ��
	MOV	R2,#40H		;��ʼ��
	MOV	R3,#05H		;��ʼ��
LINE1:  CLR	C
	MOV	A,R2		;��R2���ݳ�2����R2
	RR	A		;R2����һλ
	MOV	R2,A
	CLR	A
	MOVC	A,@A+DPTR
	SUBB	A,R5
	MOV	A,#01H
	MOVC	A,@A+DPTR
	SUBB	A,R4		;DPTR���ݼ�1����R4,R5��
	JC	LINE2		    ;���н�λתLINE2ִ��
	MOV	A,DPL
	ADD	A,R2
	MOV	DPL,A
	MOV	A,DPH
	ADDC	A,#00H
	MOV	DPH,A		;����DPTR)+(R2)�͵�DPTR��
	SJMP	LINE3		;תLINE3ִ��
LINE2��CLR	C
	MOV	A,DPL
	SUBB	A,R2
	MOV	DPL,A
	MOV	A.DPH
	SUBB	A,#00H
	MOV	DPH,A		;����DPTR)��(R2)�͵�DPTR��
LINE3:DJNZ 	R3,LINE1	;R3��Ϊ0��תLINE1ִ��
	CLR	A
	CLR	C
	MOVC	A,@A+DPTR
	SUBB	A,R5
	MOV	A,#01H
	MOVC	A,@A+DPTR
 	SUBB	A,R4		;��DPTR)��(R4R5)�н�λ��
	JNC	LINE4		;�޽�λ��תLINE4ִ��
	CLR	C
	MOV	A,DPL
	SUBB	A,R2
	MOV	DPL,A
	MOV	A,DPH
	SUBB	A,#00H
	MOV	DPH,A		;��DPTR)��(R2)�͵�DPTR��
LINE4:	MOV	A,#80H
	MOVC	A,@A+DPTR
	MOV	R6,A
	RET

