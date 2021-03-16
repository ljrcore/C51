;FILE NAME:GJ01.ASM ���ܵ�Դ���������嵥

          	ORG  0000H
          	AJMP MAIN
          	ORG  0003H           	;INT0�ж����    
          	AJMP WINT0
          	ORG  000BH          		 ;T0�ж����    
          	AJMP WT0
	ORG  30H
MAIN:     MOV SP,#40H         	;ջָ��
	 MOV 30H,#0	      	;��ʾ������
          	CLR 00H             		;�趨/�ȴ� ״̬��־:
                CLR 01H             		;����/ֹͣ״̬��־: 
                CLR 02H             		;ͨ/��״̬��־
          	CLR 03H             		;���־ T0��ʱ1sʱ��λ
          	CLR 04H             		;�ֱ�־ T0��ʱ1mʱ��λ
          	CLR 05H             		;ʱ��־ T0��ʱ1hʱ��λ
	MOV 21H,#0      		;0.5ms��ʱ�жϼ�������ֵ
	MOV 22H,#0      		;100ms��ʱ����ֵ 
	MOV 23H,#0    		 ;1s��ʱ����ֵ
	MOV 24H,#0    		 ;1m��ʱ����ֵ 
	MOV 25H,#0     		;1h��ʱ����ֵ 
                                                         
	MOV 26H,#5     		;�趨���俪��ʱ��
	MOV 27H,#2    		;�趨����ء�ʱ��
	MOV 28H,#4    		;�趨����ʱ��ʱ��
          	MOV TH0,#05H       	;T0 0.5ms ��ֵ
          	MOV TL0,#05H        	;T0 0.5ms �Զ�װ���ֵ
          	MOV TMOD,#02H       	;T0  ��ʽ2�趨 
          	SETB EA             		;��CPU�ж�
          	SETB ET0            		;����T0�ж�  
          	SETB TR0           		;����T0����  
          	SETB IT0            		;INT0������ʽ����
          	SETB EX0            		;INT0�����ж�
STAR:	 NOP
          	ACALL DM
          	ACALL DH
          	MOV A,28H           		; 28H Ϊ�趨����ʱʱ��
          	MOV 30H,A           		; 30H����ʾ������
          	JNB 01H,WEND        	; 01H=0  ת�Ƶ�ѭ���ȴ�״̬
          	ACALL DSP3          	; ���á�ʱ����ʾ�ӳ��� 
          	JB 02H,WON          	; 02H=1 ת����ͨ��
          	SETB P3.7           		; 
          	AJMP STAR      		;ѭ��
WON:	CLR P3.7            		;
          	AJMP STAR           	;ѭ��
WEND:	CLR P3.1            		;����LED2
          	MOV P1,#0FFH        	;�����Ϩ��
          	JB 00H,STAR         	;��ʱ������ɰ�K1������
          	AJMP WEND           	;ѭ���ȴ�״̬

DM: 	JNB 04H,MRET  		;04H=0  T0 ��ʱ��1minʱ��δ�� 
        	CLR 04H       		;04H=1  T0 ��ʱ��1minʱ�䵽 ��ֱ�־
          	DJNZ 29H,MRET 		;��ͨ�Ͽ���ʱ���Ƿ� δ����ת
          	JB 02H,M01    		;������״̬, ����ͨ״̬,��תΪ��״̬�趨
          	SETB 02H      		; ������״̬, ���Ƕ�״̬,��תΪͨ״̬�趨
         	 MOV A,26H		
          	MOV 29H,A		
          	AJMP MRET		
M01:  	CLR 02H			
          	MOV A,27H		
          	MOV 29H,A		
MRET:	 RET			
				
DH:   	JNB 05H,MRET  		;05H=0  T0 ��ʱ��1hʱ��δ�� ��ת
          	DJNZ 28H,MRET 		;��ʱʱ���Ƿ� δ����ת
          	CLR 01H       		;01H=0  ����ʱ������־
          	CLR TR0       		;��ʱ����ʱ�䵽, ��T0
          	RET
;
DSP1:	  MOV A,26H       		;���俪����ʾ�ӳ���
          	MOV 30H,A 
          	ACALL DSP
          	RET
DSP2:	 MOV A,27H       		;����ء���ʾ�ӳ���
         	 MOV 30H,A 
          	ACALL DSP
          	RET
DSP3:	MOV A,28H      		 ;����������ʾ�ӳ���
          	MOV 30H,A 
          	ACALL DSP
          	RET
        ;
DSP:	MOV R0,#30H      		;30H  Ϊ��ʾ���ݻ�����
	MOV DPTR,#TAB    	;�ʻ������ָ��
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
	  INC 21H			;0.5ms   21H��Ϊ0.5ms�ı���
	  MOV A,21H
	  CJNE A,#0C8H,TORETI 	;200D=C8H    0.5msX200=100ms
	  MOV 21H,#0
	  INC 22H  		;100ms     22H��Ϊ 100ms �ı���
	  MOV A,22H
	  CJNE A,#10,TORETI       ;100msX10=1s 
	  MOV 22H,#0		
	  INC 23H  		; 23H��Ϊ 1s �ı���
          SETB 03H                ;ÿ��1���� 03H��λ,Ϊϵͳ�ṩ���ź�
	  MOV A,23H
	  CJNE A,#60,TORETI
	  MOV 23H,#0
	  INC 24H			;1m
	  SETB 04H                ;ÿ��1���� 04H ��λ,Ϊϵͳ�ṩ���ź�   
	  MOV A,24H               
	  CJNE A,#60,TORETI
	  MOV 24H,#0
	  INC 25H  		;1h
	  SETB 05H                ;ÿ��1Сʱ 05H ��λ,Ϊϵͳ�ṩʱ�ź�   
	  MOV A,25H
	  CJNE A,#24,TORETI
	  MOV 25H,#0		
TORETI:   POP PSW
          POP ACC
          RETI
WINT0:    PUSH ACC
          PUSH PSW
          SETB 00H
          CLR EX0          ;���ж�
          CLR TR0          ;�ؼ�����
          ACALL DL         ;����ʱ�ӳ���
          SETB 00H

PK:       JB P3.2,PK3      ;��K1���·�,δ����ת����������״̬��(��K3)
          CLR P3.0         ;LED1 ����   
          SETB P3.1
          JNB P3.2,$       ;��K1(P3.2)�ͷ�    
          JB P3.2,PK2O     ;��K1(P3.2)���·�,δ����ת�����俪���趨(��K2)
          ACALL PK2F       ;K1����,���롰��ء��趨(��K2),
PK1:      JB P3.2,PK3      ;��K1���·�,δ����ת����������״̬��(��K3)   
          JNB P3.2,$       ;��K1�ͷ�    
          ACALL SH         ;�趨��ʱʱ��    
PK3:      JB P3.4,PK       ;��K3���·�,δ����ת����K1״̬   
          CLR P3.7         ;K3����,ϵͳ����
          SETB P3.0        
          SETB P3.1        
          CLR  00H
          SETB TR0          ;��������
          SETB EX0          ;���ж�
          CLR 00H
          POP PSW           ;�ָ��ֳ�  
          POP ACC
          RETI
SH:       CLR P3.0         ;����LED1
          CLR P3.1         ;����LED2
          ACALL DL
          MOV R0,#20H
PK2H1:    JB P3.3,PK2H2    ;��K2(P3.3)���·�,δ�����ٶ�
          MOV A,28H
          CJNE A,#9,PK2H3
          MOV 28,#0
PK2H3:    INC 28H
          ACALL DSP3
          JNB P3.3,$        ;�ȴ�K3�ͷ�
          AJMP PK2H1
PK2H2:    DJNZ R0,PK2H1
          RET

PK2F:     SETB P3.0        ;LED1��
          CLR P3.1         ;LED2��
          ACALL DL
          MOV R0,#20H
PK2F1:    JB P3.3,PK2F2    ;��K2(P3.3)���·�,δ�����ٶ�
          INC 27H
          ACALL DSP1
          JNB P3.3,$        ;�ȴ�K2�ͷ�
          AJMP PK2F1
PK2F2:    DJNZ R0,PK2F1
          RET
          
PK2O:     ACALL DL          ;���俪��ʱ���趨
          MOV R0,#20H         
PK2O1:    JB P3.3,PK2O2     ;��K2(P3.3)���·�,δ�����ٶ�
          INC 26H           ;K2����,���俪��ʱ���1  
          ACALL DSP1        ;  
          JNB P3.3,$        ;�ȴ�K2�ͷ�
          AJMP PK2O1         ;�ٶ�K2  
PK2O2:    DJNZ R0,PK2O1
          AJMP PK

          END



;                                   ---  ������ ---