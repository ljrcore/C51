	ORG 0000H
	LJMP START
	ORG 000BH
	INC 20H ;中断服务,中断计数器加1
	MOV TH0,#0D8H
	MOV TL0,#0EFH ;12M晶振，形成10毫秒中断
	RETI
START: 
	MOV SP,#50H
	MOV TH0,#0D8H
	MOV TL0,#0EFH
	MOV TMOD,#01H
	MOV IE,#82H
MUSIC0:
	NOP
	MOV DPTR,#DAT ;表头地址送DPTR
	MOV 20H,#00H ;中断计数器清0
MUSIC1:
	NOP
	CLR A
	MOVC A,@A+DPTR ;查表取代码
	JZ END0 ;是00H,则结束
	CJNE A,#0FFH,MUSIC5 ;如果是休止符，往下执行
	LJMP MUSIC3
MUSIC5:
	NOP
	MOV R6,A ;R6=18H音符的频率
	INC DPTR; DPTR加一
	MOV A,#0
	MOVC A,@A+DPTR ;取节拍代码送R7
	MOV R7,A ;R7=30H音符发音的时间
	SETB TR0 ;启动计数 
MUSIC2:
	NOP
	CPL P3.0 ;P3.0是音乐输出引脚
	MOV A,R6
	MOV R3,A ;R3=R6=18H
	LCALL DEL
	MOV A,R7
	CJNE A,20H,MUSIC2 ;中断计数器(20H)=R7否?
	;不等,则继续循环
	MOV 20H,#00H ;等于,则取下一代码
	INC DPTR
	LJMP MUSIC1
MUSIC3:
	NOP ;休止100毫秒
	CLR TR0 
	MOV R2,#0DH ;R2=13
MUSIC4:
	NOP
	MOV R3,#0FFH ;R3=255
	LCALL DEL
	DJNZ R2,MUSIC4
	INC DPTR
	LJMP MUSIC1
END0:
	NOP
	MOV R2,#0FFH ;歌曲结束,延时1秒后继续
MUSIC6:
	MOV R3,#00H
	LCALL DEL
	DJNZ R2,MUSIC6
	LJMP MUSIC0
DEL:
	NOP
DEL3: 
	MOV R4,#02H
DEL4: 
	NOP
	DJNZ R4,DEL4
	NOP
	DJNZ R3,DEL3
	RET
	NOP
DAT: 
	DB 18H, 30H, 1CH, 10H
	DB 20H, 40H, 1CH, 10H 
	DB 18H, 10H, 20H, 10H
	DB 1CH, 10H, 18H, 40H
	DB 1CH, 20H, 20H, 20H
	DB 1CH, 20H, 18H, 20H 
	DB 20H, 80H, 0FFH, 20H
	DB 30H, 1CH, 10H , 18H
	DB 20H, 15H, 20H , 1CH
	DB 20H, 20H, 20H , 26H
	DB 40H, 20H , 20H , 2BH
	DB 20H, 26H, 20H , 20H 
	DB 20H, 30H , 80H , 0FFH
	DB 20H, 20H, 1CH , 10H
	DB 18H, 10H, 20H , 20H
	DB 26H, 20H , 2BH , 20H
	DB 30H, 20H , 2BH , 40H
	DB 20H, 20H , 1CH , 10H
	DB 18H, 10H, 20H, 20H
	DB 26H, 20H , 2BH, 20H
	DB 30H, 20H, 2BH , 40H
	DB 20H, 30H, 1CH , 10H
	DB 18H, 20H , 15H , 20H
	DB 1CH, 20H , 20H , 20H
	DB 26H, 40H, 20H , 20H 
	DB 2BH, 20H, 26H , 20H 
	DB 20H, 20H, 30H , 80H
	DB 20H, 30H, 1CH , 10H
	DB 20H, 10H, 1CH , 10H
	DB 20H, 20H, 26H , 20H
	DB 2BH, 20H, 30H , 20H
	DB 2BH, 40H, 20H , 15H
	DB 1FH, 05H, 20H , 10H
	DB 1CH, 10H, 20H , 20H
	DB 26H, 20H, 2BH , 20H
	DB 30H, 20H, 2BH , 40H
	DB 20H, 30H, 1CH , 10H
	DB 18H, 20H , 15H , 20H
	DB 1CH, 20H , 20H , 20H
	DB 26H, 40H, 20H , 20H
	DB 2BH, 20H, 26H , 20H
	DB 20H, 20H, 30H, 30H 
	DB 20H, 30H, 1CH, 10H
	DB 18H, 40H, 1CH, 20H
	DB 20H, 20H, 26H, 40H
	DB 13H, 60H, 18H , 20H
	DB 15H, 40H, 13H , 40H
	DB 18H, 80H, 00H
	end

