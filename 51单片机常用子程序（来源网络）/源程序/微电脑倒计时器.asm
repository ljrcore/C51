
;  FILE NAME:GJ-02.ASM 


          ORG  0000H          ;程序入口地址
          AJMP MAIN
          ORG  0003H          ;外部中断INT0入口地址  
          AJMP PINT0          ;转中断服务子程序
          ORG  000BH          ;T0中断入口    
          AJMP WT0            ;定时器T0入口地址
	  ORG  20H
MAIN:     MOV SP,#40H         ;设置栈指针
          MOV 20H,#0H       ;把定时数据单元清零   
	  MOV 21H,#0          
	  MOV 22H,#0     
	  MOV 23H,#15     
	  MOV 24H,#0     
          MOV TH0,#5          ;装入定时初值
          MOV TL0,#5   
          MOV TMOD,#02H       ;设T0为方式2 
          SETB EA             ;开CPU中断
          SETB ET0            ;允许T0中断  
          CLR  TR0            ;启动T0计数  
          SETB IT0            ;设定INT0触发方式
          SETB EX0            ;INT0请求中断
	  MOV 34H,#1
	  MOV 35H,#5
	  NOP   	      ;第二位显示数据  │
M:	  NOP        
 	  ACALL LED
 	  ACALL SON
 	  JNB 00H,M 
MM: 	  NOP
	  ACALL ZH1
	  ACALL DSP
          ACALL LED
          AJMP M

;显示子程序
DSP:	  MOV R7,#0AFH
DSP0:     MOV R0,#30H
	  MOV DPTR,#TAB
  	  NOP
	  MOV A,@R0
	  MOVC A,@A+DPTR
RX1:	  MOV P1,A
	  CLR P3.0
          DJNZ R7,RX1
          MOV R7,#0afh
	  INC R0
	  MOV P1,#0FFH
          SETB P3.0
	  MOV A,@R0
	  MOVC A,@A+DPTR
RX2:	  MOV P1,A
	  CLR P3.1
          DJNZ R7,RX2
          MOV R7,#8
          SETB P3.1
;          DJNZ R7,DSP0
	  RET
DSP1:	  MOV R7,#0FH
DSP01:    MOV R0,#34H
	  MOV DPTR,#TAB
	  MOV A,@R0
	  MOVC A,@A+DPTR
RX01:	  MOV P1,A
	  CLR P3.1
	  DJNZ R7,$
	  MOV R7,#0FH
	  INC R0
          SETB P3.1
	  MOV A,@R0
	  MOVC A,@A+DPTR
	  MOV P1,A
	  CLR P3.0
          DJNZ R7,$
          SETB P3.0
	  RET
ZH1:	  MOV R2,#0	
	  MOV R3,23H
	  ACALL BCD
	  MOV A,R6
	  ANL A,#0FH
	  MOV 30H,A
	  MOV A,R6
	  ANL A,#0F0H
	  SWAP A
	  MOV 31H,A
	  RET

;十进制转换为二进制子程序
DTOB:	  
          MOV 32H,#0
          MOV 33H,#0
          MOV R0,#32H
          MOV R2,#3
          ACALL IDTB
          MOV A,R4
          MOV 23H,A
          RET
IDTB:	MOV   R3,#0
	MOV   A,@R0
	MOV   R4,A
IDTL:	MOV   A,R4
	MOV   B,#10
	MUL   AB
	MOV   R4,A
	MOV   B,#10
	XCH   A,B
	XCH   A,R3
	MUL   AB
	ADD   A,R3
	XCH   A,R4
	INC   R0
	ADD   A,@R0
	XCH   A,R4
	ADDC  A,#0
	MOV   R3,A
	DJNZ  R2,IDTL
	RET

;二进制数转换为十进制数子程序
BCD:    CLR   A       
	MOV   R4,A
	MOV   R5,A
	MOV   R6,A
	MOV   R7,#16
IBTL2:  CLR   C
	MOV   A,R3
	RLC   A
	MOV   R3,A
	MOV   A,R2
	RLC   A
	MOV   R2,A
	MOV   A,R6
	ADDC  A,R6
	DA    A
	MOV   R6,A
	MOV   A,R5
	ADDC  A,R5
	DA    A
	MOV   R5,A
	MOV   A,R4
	ADDC  A,R4
	DA    A
	MOV   R4,A
	DJNZ  R7,IBTL2
	RET

;延时子程序
DL:	MOV R7,#02H
DL1:	MOV R6,#0FFH
DL2:	DJNZ R6,DL2
	DJNZ R7,DL1
	RET

;外部中断服务子程序
PINT0:    CLR EX0
	  PUSH ACC
          PUSH PSW
          SETB P3.5
          ACALL DSP1
PK:	  JB P3.2,TOEXT
pk0:	  acall dsp1       
	  JNB P3.2,pk0
PK2:      JB P3.3,PK3      ;判K2按下否,未按则转到判K3状态   
	  ACALL DSP1
	  INC 34H
	  MOV A,34H
	  CJNE A,#0AH,PK22	
	  MOV 34H,#0
PK22:     ACALL DSP1       ;K2按下,30H加1
	  JNB P3.3,PK22
          AJMP PK2
PK3:      ACALL DSP1
	  JB P3.4,PK1      ;判K3按下否,未按则转到判K1状态   
	  INC 35H
	  MOV A,35H
	  CJNE A,#0AH,PK33
	  MOV 35H,#0
PK33:     ACALL DSP1
	  JNB P3.4,PK33	
          AJMP PK3
PK1:      ACALL DSP1
          JB P3.2,PK2       ;K1未按则转判K2和K3   
pk10:	  acall dsp1		
	  JNB P3.2,pk10
          ACALL DTOB
	  SETB 00H
TOEXT:	  SETB EX0          ;开中断
          SETB TR0
          POP PSW           ;恢复现场  
          POP ACC
          RETI
LED:      JB 01H,LED0
          CLR P3.5
          RET
LED0:     SETB P3.5
          RET
SON:	  JB 02H,SON0
	  CLR P3.7	;
	  RET
SON0:	  SETB P3.7	;
	  RET	  	
;段码表
TAB:    DB 0C0H,0F9H,0A4H,0B0H,99H
        DB 92H,82H,0F8H,80H,90H

;定时中断服务子程序
WT0:    PUSH ACC
        PUSH PSW
	INC 21H			;0.5ms
	MOV A,21H
	CJNE A,#0C8H,TORETI 	;200D=C8H
	MOV 21H,#0
	INC 22H  		;100ms
	MOV A,22H
	CJNE A,#10,TORETI
	MOV 22H,#0		
	DEC 23H
	MOV A,23H
;	CJNE A,#60,TORETI
;	MOV 23H,#0
;	DEC 24H
	CPL 01H
;	MOV A,24H
	CJNE A,#0,TORETI
	CLR TR0
	SETB 02H
	CLR 01H
	CLR 00H
TORETI: POP PSW
        POP ACC
        RETI
	END
