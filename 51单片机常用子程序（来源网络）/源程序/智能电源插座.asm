;FILE NAME:GJ01.ASM 智能电源插座程序清单

          	ORG  0000H
          	AJMP MAIN
          	ORG  0003H           	;INT0中断入口    
          	AJMP WINT0
          	ORG  000BH          		 ;T0中断入口    
          	AJMP WT0
	ORG  30H
MAIN:     MOV SP,#40H         	;栈指针
	 MOV 30H,#0	      	;显示缓冲区
          	CLR 00H             		;设定/等待 状态标志:
                CLR 01H             		;工作/停止状态标志: 
                CLR 02H             		;通/断状态标志
          	CLR 03H             		;秒标志 T0定时1s时置位
          	CLR 04H             		;分标志 T0定时1m时置位
          	CLR 05H             		;时标志 T0定时1h时置位
	MOV 21H,#0      		;0.5ms定时中断计数器初值
	MOV 22H,#0      		;100ms定时器初值 
	MOV 23H,#0    		 ;1s定时器初值
	MOV 24H,#0    		 ;1m定时器初值 
	MOV 25H,#0     		;1h定时器初值 
                                                         
	MOV 26H,#5     		;设定“间开”时间
	MOV 27H,#2    		;设定“间关”时间
	MOV 28H,#4    		;设定“延时”时间
          	MOV TH0,#05H       	;T0 0.5ms 初值
          	MOV TL0,#05H        	;T0 0.5ms 自动装入初值
          	MOV TMOD,#02H       	;T0  方式2设定 
          	SETB EA             		;开CPU中断
          	SETB ET0            		;允许T0中断  
          	SETB TR0           		;允许T0计数  
          	SETB IT0            		;INT0触发方式设置
          	SETB EX0            		;INT0请求中断
STAR:	 NOP
          	ACALL DM
          	ACALL DH
          	MOV A,28H           		; 28H 为设定的延时时间
          	MOV 30H,A           		; 30H是显示缓冲区
          	JNB 01H,WEND        	; 01H=0  转移到循环等待状态
          	ACALL DSP3          	; 调用“时”显示子程序 
          	JB 02H,WON          	; 02H=1 转“间通”
          	SETB P3.7           		; 
          	AJMP STAR      		;循环
WON:	CLR P3.7            		;
          	AJMP STAR           	;循环
WEND:	CLR P3.1            		;点亮LED2
          	MOV P1,#0FFH        	;数码管熄灭
          	JB 00H,STAR         	;延时结束后可按K1再设置
          	AJMP WEND           	;循环等待状态

DM: 	JNB 04H,MRET  		;04H=0  T0 定时器1min时间未到 
        	CLR 04H       		;04H=1  T0 定时器1min时间到 清分标志
          	DJNZ 29H,MRET 		;判通断控制时间是否到 未到即转
          	JB 02H,M01    		;判现在状态, 若是通状态,即转为断状态设定
          	SETB 02H      		; 判现在状态, 若是断状态,即转为通状态设定
         	 MOV A,26H		
          	MOV 29H,A		
          	AJMP MRET		
M01:  	CLR 02H			
          	MOV A,27H		
          	MOV 29H,A		
MRET:	 RET			
				
DH:   	JNB 05H,MRET  		;05H=0  T0 定时器1h时间未到 即转
          	DJNZ 28H,MRET 		;延时时间是否到 未到即转
          	CLR 01H       		;01H=0  清延时工作标志
          	CLR TR0       		;延时控制时间到, 关T0
          	RET
;
DSP1:	  MOV A,26H       		;“间开”显示子程序
          	MOV 30H,A 
          	ACALL DSP
          	RET
DSP2:	 MOV A,27H       		;“间关”显示子程序
         	 MOV 30H,A 
          	ACALL DSP
          	RET
DSP3:	MOV A,28H      		 ;“工作”显示子程序
          	MOV 30H,A 
          	ACALL DSP
          	RET
        ;
DSP:	MOV R0,#30H      		;30H  为显示数据缓冲器
	MOV DPTR,#TAB    	;笔划段码表指针
	MOV A,@R0
	MOVC A,@A+DPTR
	MOV P1,A
	ACALL DL
	RET
;
DL:	MOV R7,#02H
DL1:	MOV R6,#0FFH
DL2:	DJNZ R6,DL2
	DJNZ R7,DL1
	RET
;DELAY:  MOV 36H,#64H
;DELAY1: MOV 37H,#31H
;DELAY2: DJNZ 37H,DELAY2
;        DJNZ 36H,DELAY1
;        RET
;
TAB:      DB 0C0H,0F9H,0A4H,0B0H,99H ;0,1,2,3,4
          DB 92H,82H,0F8H,80H,90H    ;5,6,7,8,9
          DB 88H,83H,0C6H,0A1H,0F3H  ;A,b,C,d,E,F

WT0:      PUSH ACC
          PUSH PSW
	  INC 21H			;0.5ms   21H中为0.5ms的倍数
	  MOV A,21H
	  CJNE A,#0C8H,TORETI 	;200D=C8H    0.5msX200=100ms
	  MOV 21H,#0
	  INC 22H  		;100ms     22H中为 100ms 的倍数
	  MOV A,22H
	  CJNE A,#10,TORETI       ;100msX10=1s 
	  MOV 22H,#0		
	  INC 23H  		; 23H中为 1s 的倍数
          SETB 03H                ;每隔1秒钟 03H置位,为系统提供秒信号
	  MOV A,23H
	  CJNE A,#60,TORETI
	  MOV 23H,#0
	  INC 24H			;1m
	  SETB 04H                ;每隔1分钟 04H 置位,为系统提供分信号   
	  MOV A,24H               
	  CJNE A,#60,TORETI
	  MOV 24H,#0
	  INC 25H  		;1h
	  SETB 05H                ;每隔1小时 05H 置位,为系统提供时信号   
	  MOV A,25H
	  CJNE A,#24,TORETI
	  MOV 25H,#0		
TORETI:   POP PSW
          POP ACC
          RETI
WINT0:    PUSH ACC
          PUSH PSW
          SETB 00H
          CLR EX0          ;关中断
          CLR TR0          ;关计数器
          ACALL DL         ;调延时子程序
          SETB 00H

PK:       JB P3.2,PK3      ;判K1按下否,未按则转到“待启动状态”(判K3)
          CLR P3.0         ;LED1 点亮   
          SETB P3.1
          JNB P3.2,$       ;待K1(P3.2)释放    
          JB P3.2,PK2O     ;判K1(P3.2)按下否,未按则转到“间开”设定(判K2)
          ACALL PK2F       ;K1按下,进入“间关”设定(判K2),
PK1:      JB P3.2,PK3      ;判K1按下否,未按则转到“待启动状态”(判K3)   
          JNB P3.2,$       ;待K1释放    
          ACALL SH         ;设定延时时间    
PK3:      JB P3.4,PK       ;判K3按下否,未按则转到判K1状态   
          CLR P3.7         ;K3按下,系统启动
          SETB P3.0        
          SETB P3.1        
          CLR  00H
          SETB TR0          ;开计数器
          SETB EX0          ;开中断
          CLR 00H
          POP PSW           ;恢复现场  
          POP ACC
          RETI
SH:       CLR P3.0         ;点亮LED1
          CLR P3.1         ;点亮LED2
          ACALL DL
          MOV R0,#20H
PK2H1:    JB P3.3,PK2H2    ;判K2(P3.3)按下否,未按下再读
          MOV A,28H
          CJNE A,#9,PK2H3
          MOV 28,#0
PK2H3:    INC 28H
          ACALL DSP3
          JNB P3.3,$        ;等待K3释放
          AJMP PK2H1
PK2H2:    DJNZ R0,PK2H1
          RET

PK2F:     SETB P3.0        ;LED1灭
          CLR P3.1         ;LED2亮
          ACALL DL
          MOV R0,#20H
PK2F1:    JB P3.3,PK2F2    ;判K2(P3.3)按下否,未按下再读
          INC 27H
          ACALL DSP1
          JNB P3.3,$        ;等待K2释放
          AJMP PK2F1
PK2F2:    DJNZ R0,PK2F1
          RET
          
PK2O:     ACALL DL          ;“间开”时间设定
          MOV R0,#20H         
PK2O1:    JB P3.3,PK2O2     ;判K2(P3.3)按下否,未按下再读
          INC 26H           ;K2按下,“间开”时间加1  
          ACALL DSP1        ;  
          JNB P3.3,$        ;等待K2释放
          AJMP PK2O1         ;再读K2  
PK2O2:    DJNZ R0,PK2O1
          AJMP PK

          END



;                                   ---  王爱廉 ---