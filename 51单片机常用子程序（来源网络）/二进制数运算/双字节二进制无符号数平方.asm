;入口条件：待平方数在R2、R3中。
;出口信息：结果在R2、R3、R4、R5中。
;影响资源：PSW、A、B、R2～R5    堆栈需求：  ２字节

MUL2:	MOV	A,R3	;计算R3平方
	MOV	B,A
	MUL	AB
	MOV	R4,B	;暂存部分积
	MOV	R5,A
	MOV	A,R2	;计算R2平方
	MOV	B,A
	MUL	AB
	XCH	A,R3	;暂存部分积，并换出R2和R3
	XCH	A,B
	XCH	A,R2
	MUL	AB	;计算2×R2×R3
	CLR	C
	RLC	A
	XCH	A,B
	RLC	A
	JNC	MU20
	INC	R2	;累加溢出量
MU20:	XCH	A,B	;累加部分积
	ADD	A,R4
	MOV	R4,A
	MOV	A,R3
	ADDC A,B
	MOV	R3,A
	CLR	A
	ADDC	A,R2
	MOV	R2,A
	RET