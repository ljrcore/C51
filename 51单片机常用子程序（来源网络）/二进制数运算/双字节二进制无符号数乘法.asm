;入口条件：被乘数在R2、R3中，乘数在R6、R7中。
;出口信息：乘积在R2、R3、R4、R5中。
;影响资源：PSW、A、B、R2～R7    堆栈需求：  ２字节

MULD:	MOV	A,R3	;计算R3乘R7
	MOV	B,R7
	MUL	AB
	MOV	R4,B	;暂存部分积
	MOV	R5,A
	MOV	A,R3	;计算R3乘R6
	MOV	B,R6
	MUL	AB
	ADD	A,R4	;累加部分积
	MOV	R4,A
	CLR	A
	ADDC	A,B
	MOV	R3,A
	MOV	A,R2	;计算R2乘R7
	MOV	B,R7
	MUL	AB
	ADD	A,R4	;累加部分积
	MOV	R4,A
	MOV	A,R3
	ADDC	A,B
	MOV	R3,A
	CLR	A
	RLC	A
	XCH	A,R2	;计算R2乘R6
	MOV	B,R6
	MUL	AB
	ADD	A,R3	;累加部分积
	MOV	R3,A
	MOV	A,R2
	ADDC	A,B
	MOV	R2,A
	RET
