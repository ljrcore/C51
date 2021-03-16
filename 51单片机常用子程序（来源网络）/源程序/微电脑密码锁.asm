;��������

;	  ΢����������Դ�����嵥
;��  FILE NAME:GJ-03.ASM 
	  
	  ORG  0000H          ;������ڵ�ַ
	  AJMP MAIN
	  ORG  000BH          ;T0�ж���ڵ�ַ    
	  AJMP WT0            ;
	  ORG  001BH          ;T1�ж���ڵ�ַ      
	  AJMP WT1            ;
	  ORG  20H
MAIN:     MOV SP,#40H         ;����ջָ��
	  MOV 20H,#0H         ;��ʱ״̬,
;                  00H-ÿ��0.5msȡ�� (T0�ж�)���ڰ���������ʾ(1KHz)
;                  01H-ÿ��11s��λ   (T0)    ���ڰ���ʱ��������ʱ
;                  02H-ÿ��1min��λ  (T0)    ���ڿ�����ʱ

;                  03H-ÿ��0.5msȡ�� (T1�ж�)���ڱ���1KHz  
;                  04H-ÿ��1.25msȡ��(T1�ж�)���ڱ���400Hz     
;                  05H-KC5min����    (T1)    ���ڱ�����ʱ

	  MOV 21H,#0    ;T0/0.5ms��1/00Hȡ��/X200=100ms��21H /22H��1 
	  MOV 22H,#0    ;WT0/100ms��1/ X10=1s ��22H/23H��1   /01H��λ 
	  MOV 23H,#0    ;WT0/1s��1/ X60=1min ��23H           /02H��λ 

	  MOV 24H,#0    ;T1/0.05ms��1/X10=0.5ms 03Hȡ��/��24H 
	  MOV 25H,#0    ;T1/0.05ms��1/X25=1.25ms 04Hȡ��/��25H/26H��1 
	  MOV 26H,#0    ;WT1/1.25ms��1/X200=250ms ��26H/27H��1 
	  MOV 27H,#0    ;WT1/250ms��1/X200=50s ��27H/28H��1 
	  MOV 28H,#0    ;WT1/50s��1/X6=300s=5min/05H����   

	  MOV 29H,#16H  ;Ԥ������1698
	  MOV 2AH,#98H  ;
	  MOV 2BH,#0    ;��������(��1��2��)
	  MOV 2CH,#0    ;��������(��3��4��)
;                        ��(2BH)=(29H) (2CH)=(2AH)ʱ����,���򱨾�

	  MOV TL0,#5          ;װ�붨ʱ��ֵ(0.05ms)
	  MOV TH0,#5          ;��װ�붨ʱ��ֵ  
	  MOV TL1,#0E6H       ;װ�붨ʱ��ֵ  
	  MOV TH1,#0E6H       ;��װ�붨ʱ��ֵ  
	  MOV TMOD,#22H       ;��T0��T1Ϊ��ʽ2 
	  SETB EA             ;��CPU�ж�
	  SETB ET0            ;����T0�ж�  
	  SETB ET1            ;����T0�ж�  
	  SETB TR0            ;����T0����  
	  CLR  TR1            ;��ֹT1����  
M:        NOP        
	  ACALL KEY
	  MOV A,29H
	  CJNE A,2BH,BJ
	  MOV A,2AH
	  CJNE A,2CH,BJ
	  CLR P3.4            ;������ȷ,P3.4����,����
	  CLR P3.5            ;������ȷ,P3.5����,LED��
	  MOV 23H,#0
          CLR 02H
          JB 02H,$
          SETB P3.4
          SETB P3.5
	  AJMP M
BJ:       SETB 05H            ;�����ӳ���
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
;��ʱ�ӳ���
DL:       MOV R7,#02H
DL1:      MOV R6,#0FFH
DL2:      DJNZ R6,DL2
	  DJNZ R7,DL1
	  RET

;T0�жϷ����ӳ���
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
;T1�жϷ����ӳ���
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

;�������ӳ���
KEY:      NOP
          MOV R1,#0      ;��1��������
	  MOV R2,#0      ;��2��������
	  MOV R3,#0      ;��3��������
	  MOV R4,#0      ;��4��������
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
;����һ�ΰ���״̬
PROC RKEY1
RKEY1:    MOV 23H,#0
	  CLR 02H
	  MOV P1,#0FH    ;0-->P1.4��P1.7
LOOP:     MOV A,P1       ;
	  ANL A,#0FH     ;���θ���λ
	  CJNE A,#0FH,KEY1 ;�м�����,��ת
	  JNB 02H,LOOP
	  MOV R1,#0
	  RET            ;�޼�����,��
;�е�һ�κμ�����
KEY1:     ACALL YY       ;����
	  MOV P1,#0EFH   ;0-->P1.4
	  MOV A,P1       ;����״̬
	  ANL A,#0FH     ;���θ���λ
	  CJNE A,#0EH,K2 ;K1δ����,��ת��K2���·�
	  MOV R1,#1      ;K1����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K2:       CJNE A,#0DH,K3 ;K2δ����,��ת��K3���·�
	  MOV R1,#2      ;K2����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K3:       CJNE A,#0BH,K4 ;K3δ����,��ת��K4���·�
	  MOV R1,#3      ;K3����   ################

	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K4:       CJNE A,#07H,K5 ;K3δ����,��ת��K4���·�
	  MOV R1,#4      ;K4����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K5:       MOV P1,#0DFH   ;0-->P1.5
	  MOV A,P1       ;����״̬
	  ANL A,#0FH     ;���θ���λ
	  CJNE A,#0EH,K6 ;K5δ����,��ת��K6���·�
	  MOV R1,#5      ;K5����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K6:       CJNE A,#0DH,K7 ;K6δ����,��ת��K7���·�
	  MOV R1,#6      ;K6����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K7:       CJNE A,#0BH,K8 ;K7δ����,��ת��K8���·�
	  MOV R1,#7      ;K7����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K8:       CJNE A,#7,K9   ;K8δ����,��ת��K9���·�
	  MOV R1,#8      ;K8����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K9:       MOV P1,#0BFH   ;0-->P1.6
	  MOV A,P1       ;����״̬
	  ANL A,#0FH     ;���θ���λ
	  CJNE A,#0EH,K10 ;K9δ����,��ת��K10���·�
	  MOV R1,#9      ;K9����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K10:      CJNE A,#0DH,K11 ;K10δ����,��ת��K11���·�
	  MOV R1,#0      ;K10����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K11:      CJNE A,#0BH,K12 ;K11δ����,��ת��K12���·�
	  MOV R1,#0BH    ;K11����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K12:      MOV R1,#0CH    ;K12����   ################
	  ACALL DD       ;�ȴ������ͷ�
TORET:	  RET
          END
;���ڶ��ΰ���״̬
PROC RKEY2
RKEY2:    MOV 23H,#0
	  CLR 02H
	  MOV P1,#0FH    ;0-->P1.4��P1.7
LOOP:     MOV A,P1       ;
	  ANL A,#0FH     ;���θ���λ
	  CJNE A,#0FH,KEY1 ;�м�����,��ת
	  JNB 02H,LOOP
	  MOV R1,#0
	  RET            ;�޼�����,��
;�еڶ��κμ�����
KEY1:     ACALL YY       ;����
	  MOV P1,#0EFH   ;0-->P1.4
	  MOV A,P1       ;����״̬
	  ANL A,#0FH     ;���θ���λ
	  CJNE A,#0EH,K2 ;K1δ����,��ת��K2���·�
	  MOV R2,#1      ;K1����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K2:       CJNE A,#0DH,K3 ;K2δ����,��ת��K3���·�
	  MOV R2,#2      ;K2����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K3:       CJNE A,#0BH,K4 ;K3δ����,��ת��K4���·�
	  MOV R2,#3      ;K3����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K4:       CJNE A,#07H,K5 ;K3δ����,��ת��K4���·�
	  MOV R2,#4      ;K4����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K5:       MOV P1,#0DFH   ;0-->P1.5
	  MOV A,P1       ;����״̬
	  ANL A,#0FH     ;���θ���λ
	  CJNE A,#0EH,K6 ;K5δ����,��ת��K6���·�
	  MOV R2,#5      ;K5����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K6:       CJNE A,#0DH,K7 ;K6δ����,��ת��K7���·�
	  MOV R2,#6      ;K6����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K7:       CJNE A,#0BH,K8 ;K7δ����,��ת��K8���·�
	  MOV R2,#7      ;K7����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K8:       CJNE A,#7,K9   ;K8δ����,��ת��K9���·�
	  MOV R2,#8      ;K8����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K9:       MOV P1,#0BFH   ;0-->P1.6
	  MOV A,P1       ;����״̬
	  ANL A,#0FH     ;���θ���λ
	  CJNE A,#0EH,K10 ;K9δ����,��ת��K10���·�
	  MOV R2,#9      ;K9����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K10:      CJNE A,#0DH,K11 ;K10δ����,��ת��K11���·�
	  MOV R2,#0      ;K10����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K11:      CJNE A,#0BH,K12 ;K11δ����,��ת��K12���·�
	  MOV R2,#0BH    ;K11����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K12:      MOV R2,#0CH    ;K12����   ################
	  ACALL DD       ;�ȴ������ͷ�
TORET:	  RET
          END
;�������ΰ���״̬
PROC RKEY3
RKEY3:    MOV 23H,#0
	  CLR 02H
	  MOV P1,#0FH    ;0-->P1.4��P1.7
LOOP:     MOV A,P1       ;
	  ANL A,#0FH     ;���θ���λ
	  CJNE A,#0FH,KEY1 ;�м�����,��ת
	  JNB 02H,LOOP
	  MOV R3,#0
	  RET            ;�޼�����,��
;�е����κμ�����
KEY1:     ACALL YY       ;����
	  MOV P1,#0EFH   ;0-->P1.4
	  MOV A,P1       ;����״̬
	  ANL A,#0FH     ;���θ���λ
	  CJNE A,#0EH,K2 ;K1δ����,��ת��K2���·�
	  MOV R3,#1      ;K1����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K2:       CJNE A,#0DH,K3 ;K2δ����,��ת��K3���·�
	  MOV R3,#2      ;K2����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K3:       CJNE A,#0BH,K4 ;K3δ����,��ת��K4���·�
	  MOV R3,#3      ;K3����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K4:       CJNE A,#07H,K5 ;K3δ����,��ת��K4���·�
	  MOV R3,#4      ;K4����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K5:       MOV P1,#0DFH   ;0-->P1.5
	  MOV A,P1       ;����״̬
	  ANL A,#0FH     ;���θ���λ
	  CJNE A,#0EH,K6 ;K5δ����,��ת��K6���·�
	  MOV R3,#5      ;K5����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K6:       CJNE A,#0DH,K7 ;K6δ����,��ת��K7���·�
	  MOV R3,#6      ;K6����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K7:       CJNE A,#0BH,K8 ;K7δ����,��ת��K8���·�
	  MOV R3,#7      ;K7����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K8:       CJNE A,#7,K9   ;K8δ����,��ת��K9���·�
	  MOV R3,#8      ;K8����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K9:       MOV P1,#0BFH   ;0-->P1.6
	  MOV A,P1       ;����״̬
	  ANL A,#0FH     ;���θ���λ
	  CJNE A,#0EH,K10 ;K9δ����,��ת��K10���·�
	  MOV R3,#9      ;K9����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K10:      CJNE A,#0DH,K11 ;K10δ����,��ת��K11���·�
	  MOV R3,#0      ;K10����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K11:      CJNE A,#0BH,K12 ;K11δ����,��ת��K12���·�
	  MOV R3,#0BH    ;K11����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K12:      MOV R3,#0CH    ;K12����   ################
	  ACALL DD       ;�ȴ������ͷ�
TORET:	  RET
          END
;�����Ĵΰ���״̬
PROC RKEY4
RKEY4:    MOV 23H,#0
	  CLR 02H
	  MOV P1,#0FH    ;0-->P1.4��P1.7
LOOP:     MOV A,P1       ;
	  ANL A,#0FH     ;���θ���λ
	  CJNE A,#0FH,KEY1 ;�м�����,��ת
	  JNB 02H,LOOP
	  MOV R4,#0
	  RET            ;�޼�����,��
;�е��Ĵκμ�����
KEY1:     ACALL YY       ;����
	  MOV P1,#0EFH   ;0-->P1.4
	  MOV A,P1       ;����״̬
	  ANL A,#0FH     ;���θ���λ
	  CJNE A,#0EH,K2 ;K1δ����,��ת��K2���·�
	  MOV R4,#1      ;K1����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K2:       CJNE A,#0DH,K3 ;K2δ����,��ת��K3���·�
	  MOV R4,#2      ;K2����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K3:       CJNE A,#0BH,K4 ;K3δ����,��ת��K4���·�
	  MOV R4,#3      ;K3����   ################

	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K4:       CJNE A,#07H,K5 ;K3δ����,��ת��K4���·�
	  MOV R4,#4      ;K4����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K5:       MOV P1,#0DFH   ;0-->P1.5
	  MOV A,P1       ;����״̬
	  ANL A,#0FH     ;���θ���λ
	  CJNE A,#0EH,K6 ;K5δ����,��ת��K6���·�
	  MOV R4,#5      ;K5����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K6:       CJNE A,#0DH,K7 ;K6δ����,��ת��K7���·�
	  MOV R4,#6      ;K6����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K7:       CJNE A,#0BH,K8 ;K7δ����,��ת��K8���·�
	  MOV R4,#7      ;K7����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K8:       CJNE A,#7,K9   ;K8δ����,��ת��K9���·�
	  MOV R4,#8      ;K8����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K9:       MOV P1,#0BFH   ;0-->P1.6
	  MOV A,P1       ;����״̬
	  ANL A,#0FH     ;���θ���λ
	  CJNE A,#0EH,K10 ;K9δ����,��ת��K10���·�
	  MOV R4,#9      ;K9����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K10:      CJNE A,#0DH,K11 ;K10δ����,��ת��K11���·�
	  MOV R4,#0      ;K10����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K11:      CJNE A,#0BH,K12 ;K11δ����,��ת��K12���·�
	  MOV R4,#0BH    ;K11����   ################
	  ACALL DD       ;�ȴ������ͷ�
	  AJMP TORET
K12:      MOV R4,#0CH    ;K12����   ################
	  ACALL DD       ;�ȴ������ͷ�
TORET:	  RET
          END
DD:	  CJNE A,#0FH,$         
	  RET
	  END

;				--  ������ --
;						99-11
  ������ --
;						99-11
