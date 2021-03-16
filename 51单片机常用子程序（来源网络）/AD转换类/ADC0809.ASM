;入口：通道1的模拟量，
;出口：片内RAM开辟一个数据区，用于存放A/D转换结果，
 IN0—IN7的结果
      ;分别存于30H—37H 8个单元中
AD0809:	MOV R1,#01H
	ACALL AD0809_1 
	RET 
AD0809_1:MOV DPTR,#      ;通道地址  
	MOV A,R1             ;送通道号
	MOVX @DPTR,A;启动转换
WAIT:	NOP
	JNB R1.7,WAIT     ;P1.7为EOC信号 为1完成，0，转换中。
	MOVX A,@DPTR ；转换完成
	XCH A,R1
	ADD A,#30H
	XCH A,R1
	MOV @R1,A
	RET    