;入口条件：字节数在R7中，操作数在[R0]中。
;出口信息：结果仍在[R0]中，移出的十进制最高位在R3中。
;影响资源：PSW、A、R2、R3    堆栈需求：  ２字节

BRLN:	MOV	A,R7	;取字节数至R2中
   	MOV	R2,A
	ADD	A,R0	;初始化数据指针
	MOV	R0,A
	MOV	R3,#0	;工作单元初始化
BRL1:	DEC	R0	;调整数据指针
	MOV	A,@R0	;取一字节
	SWAP	A	;交换十进制高低位
	MOV	@R0,A	;存回
	MOV	A,R3	;取低字节移出的十进制高位
	XCHD	A,@R0	;换出本字节的十进制高位
	MOV	R3,A	;保存本字节的十进制高位
	DJNZ	R2,BRL1	;处理完所有字节
	RET
