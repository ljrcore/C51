；查询方式的S数据发送和接受程序
COMUN_PC:MOV	DX,3FBH		;设置波特率（8250初始化）
		MOV	AL,80H
		OUT DX,AL
		MOV DX,3F8H
		MOV AL,11
		OUT DX,AL
		MOV DX,3F9H
		MOV AL,0
		OUT DX,AL
		MOV DX,3FBH
		MOV AL,2BH
		OUT DX,AL
		MOV DX,3FCH
		MOV AL,03H
		OUT DX,AL
		MOV DX,3F9H
		MOV AL,0
		OUT DX,AL
		MOV AX,0
		MOV BX,00FFH
		MOV SI ,SOURCE
		MOV DI,DEST
		MOV XD,3FDH
TO_LEEP:MOV CX,2810H
LEEP1:	IN AL,DX
		TEST AL,20H
		JZ LEEP1
		MOV DX ,3F8H		
		MOV AL,UNMBER
		OUT DX,AL
LEEP2:LOOP LEEP2
		MOV DX,3FDH
LEEP3:IN 	AL.DX
		TEST AL,01H
		JZ TO_LEEP
		TEST AL,1EH
		JNZ ERROR
		MOV DX,3F8H
		IN AL,DX
		JNZ ERROR
		MOV DX,3FBH
		MOV AL,3BH
		OUT DX,AL
START:	MOV DX,3FDH
		MOV CX,2801H
SEND:	IN AL,DX
		TEST AL,20H
		JZ SEND
		MOV DX,3F8H
		MOV AL,[SI]
		OUT DX,AL
		ADD AL,AH
		MOV AH,AL
RECV:	LOOP RECV
		MOV	DX,3FD
		IN AL,DX
		TEST AL,01H
		JZ SEND
		TEST AL,IEH
		JNZ ERROR
		MOV DX,3F8H
		IN AL,DX
		MOV [DI],AL
		DEC BX
		JZ END
		INC SI
		INC DI
		JMP START
EPPOR: MOV DX,ODDDSET_ERROR1
		MOV AH,9
		INT 21H
		INT 20H
END:	MOV DX,3FDH
		MOV CX,2810H
END1：	IN AN,DX
		TEST AL,20H
		JZ END1
		MOV DX,3F8H
		MOV AL,AH
		OUT DX,AL
		MOV DX ,3FDH
END2:	LOOP END2
		IN AL,DX
		TEST AL,10H
		JZ END
		MOV DX,3F8H
		IN AL,DX
		IN AL,DX
		AND AL,AL
		JZ END3
		JMP REEOR
END3:INT 28H		
								
		
		