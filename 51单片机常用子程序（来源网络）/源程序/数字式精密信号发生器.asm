;憘拑櫫泭

;	  数字式精密信号发生器源程序清单
;拕  FILE NAME:GJ-04.ASM 
;    fc=11.0592MHz	  
	  ORG  0000H          ;程序入口地址
	  AJMP MAIN
	  ORG  000BH          ;T0中断入口地址    
	  AJMP WT0            ;

	  ORG  20H
MAIN:     MOV SP,#40H         ;设置栈指针
	  MOV 20H,#0H         ;工作状态标志
;                  00H:  =0时为工作状态    =1时为设定状态
;                  01H:  =0时输出单位为Hz  =1时输出单位为kHz
;                         K5每按1次,01H取反
          MOV 21H,#0          ;定时常数 
;         22H                 ;设定的时间常数 
           
          MOV 25H,#4          ;百位显示缓冲区 K2设置 
	  MOV 26H,#0          ;十位显示缓冲区 K3设置 
	  MOV 27H,#0          ;个位显示缓冲区 K4设置 

	  MOV TMOD,#22H       ;设T0、T1为方式2 
	  SETB EA             ;开CPU中断
	  SETB ET0            ;允许T0中断  
	  CLR  TR0            ;禁止T0计数  

M:        ACALL K5            ;读键
          ACALL K1            ;读键
	  JB  00H,WSD         ;K1按下,转设定

;M1:输出400Hz  ;M2:输出1000Hz  
M1:       JB  01H,M2          ;01H=0 则显示并输出Hz
	                      ;01H=1 则显示并输出kHz
	  JB  P3.4,M1ZX       ;P3.4=1则输出正弦波,转M1ZX
	  MOV TL0,#128        ;400Hz方波定时初值
	  MOV TH0,#128
	  MOV 22H,#9
          SETB TR0
          AJMP M
M1ZX:	  CLR P3.5            ;LED 亮
          MOV TL0,#184        ;400Hz正弦波定时初值
	  MOV TH0,#184
	  MOV 22H,#1
          SETB TR0
          AJMP M

M2:       JB  P3.4,M2ZX       ;P3.4=1则输出正弦波,转M2ZX
	  MOV TL0,#254        ;1000Hz方波定时初值
	  MOV TH0,#254
	  MOV 22H,#230
          SETB TR0
          AJMP M
M2ZX:	  CLR P3.5
	  MOV TL0,#254        ;1000Hz方波定时初值
	  MOV TH0,#254
	  MOV 22H,#230
          SETB TR0
          AJMP M
WSD:      CLR 00H             ;设置状态,清K1标志
          ACALL KEYS          ;读K2￣K4
          AJMP M
;延时子程序
DL:       MOV R7,#02H
DL1:      MOV R6,#0FFH
DL2:      DJNZ R6,DL2
	  DJNZ R7,DL1
	  RET

;T0中断服务子程序
WT0:      PUSH ACC
	  PUSH PSW
	  INC 21H   
	  MOV A,21H
	  CJNE A,22H,TORETI  
	  MOV 21H,#0
	  CPL P3.7       ;从P3.7输出设定频率的方波
TORETI:	  POP PSW
	  POP ACC
	  RETI

;K1键处理子程序
K1:       MOV R0,#10
          MOV A,P3
          ANL A,#0F0H
          MOV P3,A
          MOV P1,#0FFH
K10:      JB P1.0,K11
          SETB 00H
          JNB P1.0,$
          DJNZ R0,K10    ;再读    
K11:      RET

K5:       MOV R0,#10
          MOV A,P3
          ANL A,#0F0H
          MOV P3,A
          MOV P1,#0FFH
K50:      JB P1.4,K51    ;K5键未按下,返回
          CPL 01H        ;K5键按下,“单位”标志取反
          ACALL DSP
          JNB P1.4,$
          ACALL DSP
          DJNZ R0,K50    ;再读    
K51:      RET

;K2￣K4键处理子程序
KEYS:     MOV R0,#10
          ACALL DSP
          CLR TR0
          MOV A,P3       ;P3.0￣P3.2=0 熄灭数码管
	  ANL A,#0F0H    ;P3.3=0 为读键作准备
	  MOV P3,A       
	  MOV P1,#0FFH   ;P1为输入状态  
KEY0:     MOV A,P1
          ANL A,#1FH
          CJNE A,#1FH,K2 ;有键按下,转判是何键
          ACALL DSP
          DJNZ R0,KEY0   ;无键按下,连读10次
          RET            ;无键按下, 返回

K2:       MOV R0,#250
K20:      JB P1.1,K3     ;K2键未按下,转读K3
          INC 25H        ;K2键按下,百位缓冲区加1
          MOV A,25H
          CJNE A,#0AH,K22
K21:      ACALL DSP
          JNB P1.1,$
          DJNZ R0,K20    ;再读    
          AJMP K3
K22:      MOV 25H,#0
          AJMP K21

K3:	  MOV R0,#250
K30:      JB P1.2,K4     ;K3键未按下, 转读K4
          INC 26H        ;K3键按下, 十百位缓冲区加1
          MOV A,26H
          CJNE A,#0AH,K32
K31:      ACALL DSP
          JNB P1.2,$
          DJNZ R0,K30    ;再读    
          AJMP K4
K32:      MOV 25H,#0
          AJMP K31
K4:       MOV R0,#250
K40:      JB P1.3,TORET  ;K4键未按下,转读K5
          INC 27H        ;K4键按下,个位缓冲区加1
          MOV A,27H
          CJNE A,#0AH,K42
K41:      ACALL DSP
          JNB P1.3,$
          DJNZ R0,K40    ;再读    
TORET:    RET
K42:      MOV 27H,#0
          AJMP K41

DSP :     MOV R1,10
          MOV R0,25H
          MOV A,P3
          ANL A,#0F8H
          MOV P3,A
          MOV DPTR,#TAB

          MOV A,@R0
          MOVC A,@A+DPTR
          MOV P1,A
          SETB P3.2
          ACALL DL

          INC R0
          MOV A,@R0
          MOVC A,@A+DPTR
          CLR P3.2
          MOV P1,A
          SETB P3.1
          ACALL DL

          INC R0
          MOV A,@R0
          MOVC A,@A+DPTR
          CLR P3.1
          MOV P1,A
          SETB P3.0
          ACALL DL
          DJNZ R1,DSP
          RET
;段码表
TAB:      DB 3FH,06H,5BH,8FH,66H
          DB 6DH,7DH,07H,7FH,67H
	  END	

;			--  王爱廉 --
;						99-11
