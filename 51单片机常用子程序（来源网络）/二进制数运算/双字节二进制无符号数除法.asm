
;入口条件：被乘数在R2、R3中，乘数在R6、R7中。
;出口信息：乘积在R2、R3、R4、R5中。
;影响资源：PSW、A、B、R2～R7    堆栈需求：  ４字节

MULS:	MOV	R4,#0             	;清零R4R5
	MOV	R5,#0
	LCALL	MDS	            ;计算结果的符号和两个操作数的绝对值
	LCALL	MULD         	;计算两个绝对值的乘积
	SJMP	MDSE          	;用补码表示结果
MDS:	CLR	F0	             ;结果符号初始化
	MOV	A,R6             	;判断第二操作数的符号
	JNB	ACC.7,MDS1            ;为正，不必处理
	CPL	F0	                 ;为负，结果符号取反
	XCH	A,R7             	 ;第二操作数取补，得到其绝对值
	CPL	A
	ADD	A,#1
	XCH	A,R7
	CPL	A
	ADDC	A,#0
	MOV	R6,A
MDS1:	MOV	A,R2	              ;判断第一操作数或运算结果的符号
	JNB	ACC.7,MDS3              ;为正，不必处理
	CPL	F0	                    ;为负，结果符号取反
MDS2:	MOV	A,R5             	;求第一操作数的绝对值或运算结果的补码
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
MDS3:	CLR	OV	;运算成功
	RET
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
MDSE:	JB	F0,MDS2	;用补码表示结果
	CLR	OV	;结果为正，原码即补码，计算成功
	RET
MDS:	CLR	F0	;结果符号初始化
	MOV	A,R6	;判断第二操作数的符号
	JNB	ACC.7,MDS1        ;为正，不必处理
	CPL	F0	          ;为负，结果符号取反
	XCH	A,R7	       ;第二操作数取补，得到其绝对值
	CPL	A
	ADD	A,#1
	XCH	A,R7
	CPL	A
	ADDC	A,#0
	MOV	R6,A
MDS1:	MOV	A,R2        	;判断第一操作数或运算结果的符号
	JNB	ACC.7,MDS3          ;为正，不必处理
	CPL	F0	               ;为负，结果符号取反
MDS2:	MOV	A,R5	           ;求第一操作数的绝对值或运算结果的补码
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
MDS3:	CLR	OV	;运算成功
	RET
