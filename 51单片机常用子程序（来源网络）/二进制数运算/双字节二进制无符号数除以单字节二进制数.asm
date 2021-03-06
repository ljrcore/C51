;入口条件：被除数在R4、R5中，除数在R7中。
;出口信息：OV=0 时，单字节商在R3中，OV=1 时溢出。
;影响资源：PSW、A、R3～R7    堆栈需求：  ２字节

D457:	CLR	C
	MOV	A,R4
	SUBB	A,R7
	JC	DV50
	SETB	OV	;商溢出
	RET
DV50:	MOV	R6,#8	;求平均值（R4R5／R7－→R3）
DV51:	MOV	A,R5
	RLC	A
	MOV	R5,A
	MOV	A,R4
	RLC	A
	MOV	R4,A
	MOV	F0,C
	CLR	C
	SUBB	A,R7
	ANL	C,/F0
	JC	DV52
	MOV	R4,A
DV52:	CPL	C
	MOV	A,R3
	RLC	A
	MOV	R3,A
	DJNZ	R6,DV51
	MOV	A,R4	;四舍五入
	ADD	A,R4
	JC	DV53
	SUBB	A,R7
	JC	DV54
DV53:	INC	R3
DV54:	CLR	OV
	RET
