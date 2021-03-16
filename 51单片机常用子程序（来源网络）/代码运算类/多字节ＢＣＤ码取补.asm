;入口条件：字节数在R7中，操作数在[R0]中。
;出口信息：结果仍在[R0]中。
;影响资源：PSW、A、R2、R3    堆栈需求：  ２字节

NEG:	MOV	A,R7	;取（字节数减一）至R2中
	DEC	A
	MOV	R2,A
	MOV	A,R0  ;	保护指针
	MOV	R3,A
NEG0:	CLR	C	
	MOV	A,#99H
	SUBB	A,@R0	;按字节十进制取补
	MOV	@R0,A	;存回[R0]中
	INC	R0	    ;调整数据指针
	DJNZ	R2,NEG0	;处理完（R2）字节
	MOV	A,#9AH	;最低字节单独取补
	SUBB	A,@R0
	MOV	@R0,A
	MOV	A,R3	;恢复指针
	MOV	R0,A
	RET
