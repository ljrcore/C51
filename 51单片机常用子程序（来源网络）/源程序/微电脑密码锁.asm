;憘拑櫫泭

;	  微电脑密码锁源程序清单
;拕  FILE NAME:GJ-03.ASM 
	  
	  ORG  0000H          ;程序入口地址
	  AJMP MAIN
	  ORG  000BH          ;T0中断入口地址    
	  AJMP WT0            ;
	  ORG  001BH          ;T1中断入口地址      
	  AJMP WT1            ;
	  ORG  20H
MAIN:     MOV SP,#40H         ;设置栈指针
	  MOV 20H,#0H         ;定时状态,
;                  00H-每隔0.5ms取反 (T0中断)用于按健音响提示(1KHz)
;                  01H-每隔11s置位   (T0)    用于按健时的音响延时
;                  02H-每隔1min置位  (T0)    用于开锁延时

;                  03H-每隔0.5ms取反 (T1中断)用于报警1KHz  
;                  04H-每隔1.25ms取反(T1中断)用于报警400Hz     
;                  05H-KC5min清零    (T1)    用于报警延时

	  MOV 21H,#0    ;T0/0.5ms加1/00H取反/X200=100ms清21H /22H加1 
	  MOV 22H,#0    ;WT0/100ms加1/ X10=1s 清22H/23H加1   /01H置位 
	  MOV 23H,#0    ;WT0/1s加1/ X60=1min 清23H           /02H置位 

	  MOV 24H,#0    ;T1/0.05ms加1/X10=0.5ms 03H取反/清24H 
	  MOV 25H,#0    ;T1/0.05ms加1/X25=1.25ms 04H取反/清25H/26H加1 
	  MOV 26H,#0    ;WT1/1.25ms加1/X200=250ms 清26H/27H加1 
	  MOV 27H,#0    ;WT1/250ms加1/X200=50s 清27H/28H加1 
	  MOV 28H,#0    ;WT1/50s加1/X6=300s=5min/05H清零   

	  MOV 29H,#16H  ;预设密码1698
	  MOV 2AH,#98H  ;
	  MOV 2BH,#0    ;按健键码(第1、2次)
	  MOV 2CH,#0    ;按健键码(第3、4次)
;                        当(2BH)=(29H) (2CH)=(2AH)时开锁,否则报警

	  MOV TL0,#5          ;装入定时初值(0.05ms)
	  MOV TH0,#5          ;重装入定时初值  
	  MOV TL1,#0E6H       ;装入定时初值  
	  MOV TH1,#0E6H       ;重装入定时初值  
	  MOV TMOD,#22H       ;设T0、T1为方式2 
	  SETB EA             ;开CPU中断
	  SETB ET0            ;允许T0中断  
	  SETB ET1            ;允许T0中断  
	  SETB TR0            ;允许T0计数  
	  CLR  TR1            ;禁止T1计数  
M:        NOP        
	  ACALL KEY
	  MOV A,29H
	  CJNE A,2BH,BJ
	  MOV A,2AH
	  CJNE A,2CH,BJ
	  CLR P3.4            ;按健正确,P3.4清零,开锁
	  CLR P3.5            ;按健正确,P3.5清零,LED亮
	  MOV 23H,#0
          CLR 02H
          JB 02H,$
          SETB P3.4
          SETB P3.5
	  AJMP M
BJ:       SETB 05H            ;报警子程序
	  SETB TR1
	  JB 05H,$
	  CLR TR1
	  MOV 24H,#0   
	  MOV 25H,#0   
	  MOV 26H,#0   
	  MOV 27H,#0   
	  MOV 28H,#0   
	  AJMP M
YY:	  JNB 01H,$
	  SETB TR1
	  JB 01H,$
	  CLR TR1
	  RET
;延时子程序
DL:       MOV R7,#02H
DL1:      MOV R6,#0FFH
DL2:      DJNZ R6,DL2
	  DJNZ R7,DL1
	  RET

;T0中断服务子程序
WT0:      PUSH ACC
	  PUSH PSW
	  INC 21H                 ;0.5ms
	  MOV A,21H
	  CJNE A,#0C8H,TORETI     ;200D=C8H
	  MOV 21H,#0
	  INC 22H                 ;100ms
	  MOV A,22H
	  CJNE A,#10,TORETI
	  MOV 22H,#0              
	  INC 23H
	  MOV A,23H
          CJNE A,#60,TORETI
          MOV 23H,#0
	  SETB 02H
TORETI:	  POP PSW
	  POP ACC
	  RETI
;T1中断服务子程序
WT1:      PUSH ACC
	  PUSH PSW
	  INC 24H                 ;0.05ms
	  MOV A,24H
	  CJNE A,#10,WT11         ;X10=0.5ms
	  CPL P3.2
	  MOV 24H,#0
WT11:     INC 25H                 
	  MOV A,25H
	  CJNE A,#25,TORETI
	  MOV 25H,#0  
	  CPL P3.3                
	  INC 26H
	  MOV A,26H
	  CJNE A,#200,TORETI
	  MOV 26H,#0
	  INC 27H
	  MOV A,27H
	  CJNE A,#200,TORETI
	  MOV 27H,#0
	  INC 28H
	  MOV A,28H
	  CJNE A,#6,TORETI
	  MOV 28H,#0
	  CLR 05H
	  POP PSW
	  POP ACC
	  RETI

;键处理子程序
KEY:      NOP
          MOV R1,#0      ;第1个按健码
	  MOV R2,#0      ;第2个按健码
	  MOV R3,#0      ;第3个按健码
	  MOV R4,#0      ;第4个按健码
	  ACALL RKEY1
	  ACALL RKEY2
	  ACALL RKEY3
	  ACALL RKEY4
	  MOV A,R2
	  SWAP A
	  MOV 2BH,A
	  MOV R0,#2BH
	  MOV A,R1
	  XCHD A,@R0

	  MOV A,R4
	  SWAP A
	  MOV 2CH,A
	  MOV R0,#2CH
	  MOV A,R3
	  XCHD A,@R0
	  RET
;读第一次按健状态
PROC RKEY1
RKEY1:    MOV 23H,#0
	  CLR 02H
	  MOV P1,#0FH    ;0-->P1.4￣P1.7
LOOP:     MOV A,P1       ;
	  ANL A,#0FH     ;屏蔽高四位
	  CJNE A,#0FH,KEY1 ;有键按下,则转
	  JNB 02H,LOOP
	  MOV R1,#0
	  RET            ;无键按下,则返
;判第一次何键按下
KEY1:     ACALL YY       ;鸣响
	  MOV P1,#0EFH   ;0-->P1.4
	  MOV A,P1       ;读键状态
	  ANL A,#0FH     ;屏蔽高四位
	  CJNE A,#0EH,K2 ;K1未按下,则转判K2按下否
	  MOV R1,#1      ;K1按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K2:       CJNE A,#0DH,K3 ;K2未按下,则转判K3按下否
	  MOV R1,#2      ;K2按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K3:       CJNE A,#0BH,K4 ;K3未按下,则转判K4按下否
	  MOV R1,#3      ;K3按下   ################

	  ACALL DD       ;等待按健释放
	  AJMP TORET
K4:       CJNE A,#07H,K5 ;K3未按下,则转判K4按下否
	  MOV R1,#4      ;K4按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K5:       MOV P1,#0DFH   ;0-->P1.5
	  MOV A,P1       ;读键状态
	  ANL A,#0FH     ;屏蔽高四位
	  CJNE A,#0EH,K6 ;K5未按下,则转判K6按下否
	  MOV R1,#5      ;K5按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K6:       CJNE A,#0DH,K7 ;K6未按下,则转判K7按下否
	  MOV R1,#6      ;K6按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K7:       CJNE A,#0BH,K8 ;K7未按下,则转判K8按下否
	  MOV R1,#7      ;K7按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K8:       CJNE A,#7,K9   ;K8未按下,则转判K9按下否
	  MOV R1,#8      ;K8按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K9:       MOV P1,#0BFH   ;0-->P1.6
	  MOV A,P1       ;读键状态
	  ANL A,#0FH     ;屏蔽高四位
	  CJNE A,#0EH,K10 ;K9未按下,则转判K10按下否
	  MOV R1,#9      ;K9按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K10:      CJNE A,#0DH,K11 ;K10未按下,则转判K11按下否
	  MOV R1,#0      ;K10按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K11:      CJNE A,#0BH,K12 ;K11未按下,则转判K12按下否
	  MOV R1,#0BH    ;K11按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K12:      MOV R1,#0CH    ;K12按下   ################
	  ACALL DD       ;等待按健释放
TORET:	  RET
          END
;读第二次按健状态
PROC RKEY2
RKEY2:    MOV 23H,#0
	  CLR 02H
	  MOV P1,#0FH    ;0-->P1.4￣P1.7
LOOP:     MOV A,P1       ;
	  ANL A,#0FH     ;屏蔽高四位
	  CJNE A,#0FH,KEY1 ;有键按下,则转
	  JNB 02H,LOOP
	  MOV R1,#0
	  RET            ;无键按下,则返
;判第二次何键按下
KEY1:     ACALL YY       ;鸣响
	  MOV P1,#0EFH   ;0-->P1.4
	  MOV A,P1       ;读键状态
	  ANL A,#0FH     ;屏蔽高四位
	  CJNE A,#0EH,K2 ;K1未按下,则转判K2按下否
	  MOV R2,#1      ;K1按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K2:       CJNE A,#0DH,K3 ;K2未按下,则转判K3按下否
	  MOV R2,#2      ;K2按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K3:       CJNE A,#0BH,K4 ;K3未按下,则转判K4按下否
	  MOV R2,#3      ;K3按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K4:       CJNE A,#07H,K5 ;K3未按下,则转判K4按下否
	  MOV R2,#4      ;K4按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K5:       MOV P1,#0DFH   ;0-->P1.5
	  MOV A,P1       ;读键状态
	  ANL A,#0FH     ;屏蔽高四位
	  CJNE A,#0EH,K6 ;K5未按下,则转判K6按下否
	  MOV R2,#5      ;K5按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K6:       CJNE A,#0DH,K7 ;K6未按下,则转判K7按下否
	  MOV R2,#6      ;K6按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K7:       CJNE A,#0BH,K8 ;K7未按下,则转判K8按下否
	  MOV R2,#7      ;K7按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K8:       CJNE A,#7,K9   ;K8未按下,则转判K9按下否
	  MOV R2,#8      ;K8按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K9:       MOV P1,#0BFH   ;0-->P1.6
	  MOV A,P1       ;读键状态
	  ANL A,#0FH     ;屏蔽高四位
	  CJNE A,#0EH,K10 ;K9未按下,则转判K10按下否
	  MOV R2,#9      ;K9按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K10:      CJNE A,#0DH,K11 ;K10未按下,则转判K11按下否
	  MOV R2,#0      ;K10按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K11:      CJNE A,#0BH,K12 ;K11未按下,则转判K12按下否
	  MOV R2,#0BH    ;K11按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K12:      MOV R2,#0CH    ;K12按下   ################
	  ACALL DD       ;等待按健释放
TORET:	  RET
          END
;读第三次按健状态
PROC RKEY3
RKEY3:    MOV 23H,#0
	  CLR 02H
	  MOV P1,#0FH    ;0-->P1.4￣P1.7
LOOP:     MOV A,P1       ;
	  ANL A,#0FH     ;屏蔽高四位
	  CJNE A,#0FH,KEY1 ;有键按下,则转
	  JNB 02H,LOOP
	  MOV R3,#0
	  RET            ;无键按下,则返
;判第三次何键按下
KEY1:     ACALL YY       ;鸣响
	  MOV P1,#0EFH   ;0-->P1.4
	  MOV A,P1       ;读键状态
	  ANL A,#0FH     ;屏蔽高四位
	  CJNE A,#0EH,K2 ;K1未按下,则转判K2按下否
	  MOV R3,#1      ;K1按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K2:       CJNE A,#0DH,K3 ;K2未按下,则转判K3按下否
	  MOV R3,#2      ;K2按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K3:       CJNE A,#0BH,K4 ;K3未按下,则转判K4按下否
	  MOV R3,#3      ;K3按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K4:       CJNE A,#07H,K5 ;K3未按下,则转判K4按下否
	  MOV R3,#4      ;K4按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K5:       MOV P1,#0DFH   ;0-->P1.5
	  MOV A,P1       ;读键状态
	  ANL A,#0FH     ;屏蔽高四位
	  CJNE A,#0EH,K6 ;K5未按下,则转判K6按下否
	  MOV R3,#5      ;K5按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K6:       CJNE A,#0DH,K7 ;K6未按下,则转判K7按下否
	  MOV R3,#6      ;K6按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K7:       CJNE A,#0BH,K8 ;K7未按下,则转判K8按下否
	  MOV R3,#7      ;K7按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K8:       CJNE A,#7,K9   ;K8未按下,则转判K9按下否
	  MOV R3,#8      ;K8按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K9:       MOV P1,#0BFH   ;0-->P1.6
	  MOV A,P1       ;读键状态
	  ANL A,#0FH     ;屏蔽高四位
	  CJNE A,#0EH,K10 ;K9未按下,则转判K10按下否
	  MOV R3,#9      ;K9按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K10:      CJNE A,#0DH,K11 ;K10未按下,则转判K11按下否
	  MOV R3,#0      ;K10按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K11:      CJNE A,#0BH,K12 ;K11未按下,则转判K12按下否
	  MOV R3,#0BH    ;K11按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K12:      MOV R3,#0CH    ;K12按下   ################
	  ACALL DD       ;等待按健释放
TORET:	  RET
          END
;读第四次按健状态
PROC RKEY4
RKEY4:    MOV 23H,#0
	  CLR 02H
	  MOV P1,#0FH    ;0-->P1.4￣P1.7
LOOP:     MOV A,P1       ;
	  ANL A,#0FH     ;屏蔽高四位
	  CJNE A,#0FH,KEY1 ;有键按下,则转
	  JNB 02H,LOOP
	  MOV R4,#0
	  RET            ;无键按下,则返
;判第四次何键按下
KEY1:     ACALL YY       ;鸣响
	  MOV P1,#0EFH   ;0-->P1.4
	  MOV A,P1       ;读键状态
	  ANL A,#0FH     ;屏蔽高四位
	  CJNE A,#0EH,K2 ;K1未按下,则转判K2按下否
	  MOV R4,#1      ;K1按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K2:       CJNE A,#0DH,K3 ;K2未按下,则转判K3按下否
	  MOV R4,#2      ;K2按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K3:       CJNE A,#0BH,K4 ;K3未按下,则转判K4按下否
	  MOV R4,#3      ;K3按下   ################

	  ACALL DD       ;等待按健释放
	  AJMP TORET
K4:       CJNE A,#07H,K5 ;K3未按下,则转判K4按下否
	  MOV R4,#4      ;K4按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K5:       MOV P1,#0DFH   ;0-->P1.5
	  MOV A,P1       ;读键状态
	  ANL A,#0FH     ;屏蔽高四位
	  CJNE A,#0EH,K6 ;K5未按下,则转判K6按下否
	  MOV R4,#5      ;K5按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K6:       CJNE A,#0DH,K7 ;K6未按下,则转判K7按下否
	  MOV R4,#6      ;K6按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K7:       CJNE A,#0BH,K8 ;K7未按下,则转判K8按下否
	  MOV R4,#7      ;K7按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K8:       CJNE A,#7,K9   ;K8未按下,则转判K9按下否
	  MOV R4,#8      ;K8按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K9:       MOV P1,#0BFH   ;0-->P1.6
	  MOV A,P1       ;读键状态
	  ANL A,#0FH     ;屏蔽高四位
	  CJNE A,#0EH,K10 ;K9未按下,则转判K10按下否
	  MOV R4,#9      ;K9按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K10:      CJNE A,#0DH,K11 ;K10未按下,则转判K11按下否
	  MOV R4,#0      ;K10按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K11:      CJNE A,#0BH,K12 ;K11未按下,则转判K12按下否
	  MOV R4,#0BH    ;K11按下   ################
	  ACALL DD       ;等待按健释放
	  AJMP TORET
K12:      MOV R4,#0CH    ;K12按下   ################
	  ACALL DD       ;等待按健释放
TORET:	  RET
          END
DD:	  CJNE A,#0FH,$         
	  RET
	  END

;				--  王爱廉 --
;						99-11
  王爱廉 --
;						99-11
