;双字节乘法子程序H2MUL_SUB,Page 6
;入口条件：被乘数放在20H,21H;乘数放在22H,23H；乘数位数放在2AH
;出口条件：积数放在R4,R5,R6,R7
;影响参数：A,R0,R1,R2,R4,R5,R6,R7 
H2MUL_SUB:	MOV R0,20H;
	MOV R1,21H
	MOV R2,22H
	MOV R3,23H
	MOV R4,#00H
	MOV R5,#00H
	MOV R6,#00H
	MOV R7,#00H
	MOV 2AH,#10H
LOOP_D_M:	MOV A,R4
	ADD A,R4
	MOV R4,A
	MOV A,R5
	ADDC A,R5
	MOV R5,A
	MOV A,R6
	ADDC A,R6
	MOV R6,A 
	MOV A,R7
	ADDC A,R7
	MOV R7,A
	MOV A,R2
	ADD A,R2
	MOV R2,A
	MOV A,R3
	ADDC A,R3
	MOV R3,A
	JNC TO_LOOP0
	MOV A,R4
	ADD A,R0
	MOV R4,A
	MOV A,R5
	ADDC A,R1
	MOV R5,A
	MOV A,R6 
	ADDC A,#00H
	MOV R6,A
	MOV A,R7 
	ADDC A,#00H
	MOV R7,A 
TO_LOOP0:	DJNZ 2AH,LOOP_D_M
	RET


	