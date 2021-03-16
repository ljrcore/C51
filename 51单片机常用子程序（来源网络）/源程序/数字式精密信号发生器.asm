;��������

;	  ����ʽ�����źŷ�����Դ�����嵥
;��  FILE NAME:GJ-04.ASM 
;    fc=11.0592MHz	  
	  ORG  0000H          ;������ڵ�ַ
	  AJMP MAIN
	  ORG  000BH          ;T0�ж���ڵ�ַ    
	  AJMP WT0            ;

	  ORG  20H
MAIN:     MOV SP,#40H         ;����ջָ��
	  MOV 20H,#0H         ;����״̬��־
;                  00H:  =0ʱΪ����״̬    =1ʱΪ�趨״̬
;                  01H:  =0ʱ�����λΪHz  =1ʱ�����λΪkHz
;                         K5ÿ��1��,01Hȡ��
          MOV 21H,#0          ;��ʱ���� 
;         22H                 ;�趨��ʱ�䳣�� 
           
          MOV 25H,#4          ;��λ��ʾ������ K2���� 
	  MOV 26H,#0          ;ʮλ��ʾ������ K3���� 
	  MOV 27H,#0          ;��λ��ʾ������ K4���� 

	  MOV TMOD,#22H       ;��T0��T1Ϊ��ʽ2 
	  SETB EA             ;��CPU�ж�
	  SETB ET0            ;����T0�ж�  
	  CLR  TR0            ;��ֹT0����  

M:        ACALL K5            ;����
          ACALL K1            ;����
	  JB  00H,WSD         ;K1����,ת�趨

;M1:���400Hz  ;M2:���1000Hz  
M1:       JB  01H,M2          ;01H=0 ����ʾ�����Hz
	                      ;01H=1 ����ʾ�����kHz
	  JB  P3.4,M1ZX       ;P3.4=1��������Ҳ�,תM1ZX
	  MOV TL0,#128        ;400Hz������ʱ��ֵ
	  MOV TH0,#128
	  MOV 22H,#9
          SETB TR0
          AJMP M
M1ZX:	  CLR P3.5            ;LED ��
          MOV TL0,#184        ;400Hz���Ҳ���ʱ��ֵ
	  MOV TH0,#184
	  MOV 22H,#1
          SETB TR0
          AJMP M

M2:       JB  P3.4,M2ZX       ;P3.4=1��������Ҳ�,תM2ZX
	  MOV TL0,#254        ;1000Hz������ʱ��ֵ
	  MOV TH0,#254
	  MOV 22H,#230
          SETB TR0
          AJMP M
M2ZX:	  CLR P3.5
	  MOV TL0,#254        ;1000Hz������ʱ��ֵ
	  MOV TH0,#254
	  MOV 22H,#230
          SETB TR0
          AJMP M
WSD:      CLR 00H             ;����״̬,��K1��־
          ACALL KEYS          ;��K2��K4
          AJMP M
;��ʱ�ӳ���
DL:       MOV R7,#02H
DL1:      MOV R6,#0FFH
DL2:      DJNZ R6,DL2
	  DJNZ R7,DL1
	  RET

;T0�жϷ����ӳ���
WT0:      PUSH ACC
	  PUSH PSW
	  INC 21H   
	  MOV A,21H
	  CJNE A,22H,TORETI  
	  MOV 21H,#0
	  CPL P3.7       ;��P3.7����趨Ƶ�ʵķ���
TORETI:	  POP PSW
	  POP ACC
	  RETI

;K1�������ӳ���
K1:       MOV R0,#10
          MOV A,P3
          ANL A,#0F0H
          MOV P3,A
          MOV P1,#0FFH
K10:      JB P1.0,K11
          SETB 00H
          JNB P1.0,$
          DJNZ R0,K10    ;�ٶ�    
K11:      RET

K5:       MOV R0,#10
          MOV A,P3
          ANL A,#0F0H
          MOV P3,A
          MOV P1,#0FFH
K50:      JB P1.4,K51    ;K5��δ����,����
          CPL 01H        ;K5������,����λ����־ȡ��
          ACALL DSP
          JNB P1.4,$
          ACALL DSP
          DJNZ R0,K50    ;�ٶ�    
K51:      RET

;K2��K4�������ӳ���
KEYS:     MOV R0,#10
          ACALL DSP
          CLR TR0
          MOV A,P3       ;P3.0��P3.2=0 Ϩ�������
	  ANL A,#0F0H    ;P3.3=0 Ϊ������׼��
	  MOV P3,A       
	  MOV P1,#0FFH   ;P1Ϊ����״̬  
KEY0:     MOV A,P1
          ANL A,#1FH
          CJNE A,#1FH,K2 ;�м�����,ת���Ǻμ�
          ACALL DSP
          DJNZ R0,KEY0   ;�޼�����,����10��
          RET            ;�޼�����, ����

K2:       MOV R0,#250
K20:      JB P1.1,K3     ;K2��δ����,ת��K3
          INC 25H        ;K2������,��λ��������1
          MOV A,25H
          CJNE A,#0AH,K22
K21:      ACALL DSP
          JNB P1.1,$
          DJNZ R0,K20    ;�ٶ�    
          AJMP K3
K22:      MOV 25H,#0
          AJMP K21

K3:	  MOV R0,#250
K30:      JB P1.2,K4     ;K3��δ����, ת��K4
          INC 26H        ;K3������, ʮ��λ��������1
          MOV A,26H
          CJNE A,#0AH,K32
K31:      ACALL DSP
          JNB P1.2,$
          DJNZ R0,K30    ;�ٶ�    
          AJMP K4
K32:      MOV 25H,#0
          AJMP K31
K4:       MOV R0,#250
K40:      JB P1.3,TORET  ;K4��δ����,ת��K5
          INC 27H        ;K4������,��λ��������1
          MOV A,27H
          CJNE A,#0AH,K42
K41:      ACALL DSP
          JNB P1.3,$
          DJNZ R0,K40    ;�ٶ�    
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
;�����
TAB:      DB 3FH,06H,5BH,8FH,66H
          DB 6DH,7DH,07H,7FH,67H
	  END	

;			--  ������ --
;						99-11
