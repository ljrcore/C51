;入口条件：字节数在R7中，被减数在[R0]中，减数在[R1]中。
;出口信息：差在[R0]中，最高位借位在CY中。
;影响资源：PSW、A、R2、R3    堆栈需求：  ６字节

BCDB:	LCALL	NEG1	;减数[R1]十进制取补
	LCALL	BCDA	;按多字节ＢＣＤ码加法处理
	CPL	C	;将补码加法的进位标志转换成借位标志
	MOV	F0,C	;?;そ栉槐曛?
	LCALL	NEG1	;恢复减数[R1]的原始值
	MOV	C,F0    ;恢复借位标志
	RET
NEG1:	MOV	A,R0	;[R1]十进制取补子程序入口
	XCH	A,R1	;交换指针
	XCH	A,R0
	LCALL	NEG	;通过[R0]实现[R1]取补
	MOV	A,R0
	XCH	A,R1	;换回指针
	XCH	A,R0
	RET
;多字节ＢＣＤ码取补
NEG:	MOV	A,R7	;取（字节数减一）至R2中
	DEC	A
	MOV	R2,A
	MOV	A,R0	;?;ぶ刚?
	MOV	R3,A
NEG0:	CLR	C	
	MOV	A,#99H
	SUBB	A,@R0	;按字节十进制取补
	MOV	@R0,A	;存回[R0]中
	INC	R0	;调整数据指针
	DJNZ	R2,NEG0	;处理完（R2）字节
	MOV	A,#9AH	;最低字节单独取补
	SUBB	A,@R0
	MOV	@R0,A
	MOV	A,R3	;恢复指针
	MOV	R0,A
	RET
;多字节BCD码加法
	BCDA:	MOV	A,R7	;取字节数至R2中
	MOV	R2,A
	ADD	A,R0	;初始化数据指针
	MOV	R0,A
	MOV	A,R2
	ADD	A,R1
	MOV	R1,A
	CLR	C
BCD1:	DEC	R0	;调整数据指针
	DEC	R1
	MOV	A,@R0
	ADDC	A,@R1	;按字节相加
	DA	A	;十进制调整
	MOV	@R0,A	;和存回[R0]中
	DJNZ	R2,BCD1	;处理完所有字节
	RET