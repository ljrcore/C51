
;�����������������R2��R3�У�������R6��R7�С�
;������Ϣ���˻���R2��R3��R4��R5�С�
;Ӱ����Դ��PSW��A��B��R2��R7    ��ջ����  ���ֽ�

MULS:	MOV	R4,#0             	;����R4R5
	MOV	R5,#0
	LCALL	MDS	            ;�������ķ��ź������������ľ���ֵ
	LCALL	MULD         	;������������ֵ�ĳ˻�
	SJMP	MDSE          	;�ò����ʾ���
MDS:	CLR	F0	             ;������ų�ʼ��
	MOV	A,R6             	;�жϵڶ��������ķ���
	JNB	ACC.7,MDS1            ;Ϊ�������ش���
	CPL	F0	                 ;Ϊ�����������ȡ��
	XCH	A,R7             	 ;�ڶ�������ȡ�����õ������ֵ
	CPL	A
	ADD	A,#1
	XCH	A,R7
	CPL	A
	ADDC	A,#0
	MOV	R6,A
MDS1:	MOV	A,R2	              ;�жϵ�һ���������������ķ���
	JNB	ACC.7,MDS3              ;Ϊ�������ش���
	CPL	F0	                    ;Ϊ�����������ȡ��
MDS2:	MOV	A,R5             	;���һ�������ľ���ֵ���������Ĳ���
	CPL	A
	ADD	A,#1
	MOV	R5,A
	MOV	A,R4
	CPL	A
	ADDC	A,#0
	MOV	R4,A
	MOV	A,R3
	CPL	A
	ADDC	A,#0
	MOV	R3,A
	MOV	A,R2
	CPL	A
	ADDC	A,#0
	MOV	R2,A
MDS3:	CLR	OV	;����ɹ�
	RET
MULD:	MOV	A,R3	;����R3��R7
	MOV	B,R7
	MUL	AB
	MOV	R4,B	;�ݴ沿�ֻ�
	MOV	R5,A
	MOV	A,R3	;����R3��R6
	MOV	B,R6
	MUL	AB
	ADD	A,R4	;�ۼӲ��ֻ�
	MOV	R4,A
	CLR	A
	ADDC	A,B
	MOV	R3,A
	MOV	A,R2	;����R2��R7
	MOV	B,R7
	MUL	AB
	ADD	A,R4	;�ۼӲ��ֻ�
	MOV	R4,A
	MOV	A,R3
	ADDC	A,B
	MOV	R3,A
	CLR	A
	RLC	A
	XCH	A,R2	;����R2��R6
	MOV	B,R6
	MUL	AB
	ADD	A,R3	;�ۼӲ��ֻ�
	MOV	R3,A
	MOV	A,R2
	ADDC	A,B
	MOV	R2,A
	RET
MDSE:	JB	F0,MDS2	;�ò����ʾ���
	CLR	OV	;���Ϊ����ԭ�뼴���룬����ɹ�
	RET
MDS:	CLR	F0	;������ų�ʼ��
	MOV	A,R6	;�жϵڶ��������ķ���
	JNB	ACC.7,MDS1        ;Ϊ�������ش���
	CPL	F0	          ;Ϊ�����������ȡ��
	XCH	A,R7	       ;�ڶ�������ȡ�����õ������ֵ
	CPL	A
	ADD	A,#1
	XCH	A,R7
	CPL	A
	ADDC	A,#0
	MOV	R6,A
MDS1:	MOV	A,R2        	;�жϵ�һ���������������ķ���
	JNB	ACC.7,MDS3          ;Ϊ�������ش���
	CPL	F0	               ;Ϊ�����������ȡ��
MDS2:	MOV	A,R5	           ;���һ�������ľ���ֵ���������Ĳ���
	CPL	A
	ADD	A,#1
	MOV	R5,A
	MOV	A,R4
	CPL	A
	ADDC	A,#0
	MOV	R4,A
	MOV	A,R3
	CPL	A
	ADDC	A,#0
	MOV	R3,A
	MOV	A,R2
	CPL	A
	ADDC	A,#0
	MOV	R2,A
MDS3:	CLR	OV	;����ɹ�
	RET
