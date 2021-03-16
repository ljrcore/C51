      ;; 设有128个数据，所有数据均为二字节，数据指针为DATA_B1表格放于DATA_B2开始的地址单元中，所对应的控制量放于0820H开始的地址单元中，对应控制量的数据从大到小排列。根据R4、R5的内容查找比较接近的一个数据，再找出对应表格的最后结果。
      ;;;;程序清单：
    DATA_B1  EQU  0204H		;；数据指针
    DATA_B2  EQU  0200H		; 表格地址
RAED_ROM:MOV    DPTR,#DATA_B1   ;设置数据指针
	MOV	R2,#40H		;初始化
	MOV	R3,#05H		;初始化
LINE1:  CLR	C
	MOV	A,R2		;将R2内容除2再送R2
	RR	A		;R2右移一位
	MOV	R2,A
	CLR	A
	MOVC	A,@A+DPTR
	SUBB	A,R5
	MOV	A,#01H
	MOVC	A,@A+DPTR
	SUBB	A,R4		;DPTR内容减1并送R4,R5中
	JC	LINE2		    ;；有借位转LINE2执行
	MOV	A,DPL
	ADD	A,R2
	MOV	DPL,A
	MOV	A,DPH
	ADDC	A,#00H
	MOV	DPH,A		;将（DPTR)+(R2)送到DPTR中
	SJMP	LINE3		;转LINE3执行
LINE2：CLR	C
	MOV	A,DPL
	SUBB	A,R2
	MOV	DPL,A
	MOV	A.DPH
	SUBB	A,#00H
	MOV	DPH,A		;将（DPTR)－(R2)送到DPTR中
LINE3:DJNZ 	R3,LINE1	;R3不为0，转LINE1执行
	CLR	A
	CLR	C
	MOVC	A,@A+DPTR
	SUBB	A,R5
	MOV	A,#01H
	MOVC	A,@A+DPTR
 	SUBB	A,R4		;（DPTR)－(R4R5)有进位吗？
	JNC	LINE4		;无进位，转LINE4执行
	CLR	C
	MOV	A,DPL
	SUBB	A,R2
	MOV	DPL,A
	MOV	A,DPH
	SUBB	A,#00H
	MOV	DPH,A		;（DPTR)－(R2)送到DPTR中
LINE4:	MOV	A,#80H
	MOVC	A,@A+DPTR
	MOV	R6,A
	RET

