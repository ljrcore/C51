      ORG    0000H
      AJMP   MAIN
      ORG    0050H
MAIN: MOV    P1,#0FFH
      ACALL  DD3
LOOP: JNB    P3.4,LOOP;�ж�VT�Ƿ����ź�
      ACALL  DL;��ʱ������
      JB     P3.4,START;���ź�������
      AJMP   LOOP;���򷵻�LOOP
START:JNB    P3.0,XD1;�ж�D1�ź�
      ACALL  DL
      JB     P3.0,FDSD;�����������趨
XD1:  JNB    P3.1,XD2;�ж�D2�ź�
      ACALL  DL
      JB     P3.1,JCFD;�������������
XD2:  JNB    P3.2,XD3;�ж�D3�ź�
      ACALL  DL
      JB     P3.2,QDNC;�����������ů��
XD3:  JNB    P3.3,XD4;�ж�D4�ź�
      ACALL  DL
      JB     P3.3,XCQJ;�������Ѱ�����
XD4:  AJMP   LOOP;��D1-D4���ź��򷵻�LOOP

FDSD: ACALL  BJ;�����趨����,�ȱ���
      ACALL  DD3;��ʱ3��
FD1:  JNB    P3.5,FD2;�ж����ź�
      ACALL  DL
      JB     P3.5,BZC;������뱨���жϳ���
FD2:  JNB    P3.7,FD3;�ж���ͷ�������Ƿ����
      ACALL  DL
      JB     P3.7,BZC;������뱨���жϳ���
FD3:  JNB    P3.4,FD4;�ж�VT�Ƿ����ź�
      ACALL  DL
      JB     P3.4,FH;���򷵻�
FD4:  AJMP   FD1
BZC:  ACALL  BJ;�����жϳ���
      ACALL  DD3
      ACALL  DD2;��ʱ5��
      JNB    P3.5,BZC1;�ж����ź�
      ACALL  DL
      JB     P3.5,BJJ;���������������
BZC1: JNB    P3.7,BZC2;�ж���ͷ�������Ƿ����
      ACALL  DL
      JB     P3.7,BJJ;���������������
BZC2: JNB    P3.4,BZC3;�ж�VT�Ƿ����ź�
      ACALL  DL
      JB     P3.4,FH;���򷵻�
BZC3: AJMP   FD1
BJJ:  ACALL  BJ;������������
      ACALL  DD1
      JNB    P3.7,BJJ1;�ж���ͷ�������Ƿ����
      ACALL  DL
      JB     P3.7,XH;�������Ϩ�����
BJJ1: JNB    P3.4,BJJ2;�ж�VT�Ƿ����ź�
      ACALL  DL
      JB     P3.4,FH;���򷵻�
BJJ2: AJMP   BJJ
XH:   CLR    P1.1;Ϩ�����
      SETB   P1.2
      ACALL  DD1
      SETB   P1.1
      AJMP   BJJ
FH:   AJMP   MAIN

JCFD: ACALL  BJ;�����������,�ȱ���2��
      ACALL  DD1
      ACALL  BJ
      CLR    P1.1
      SETB   P1.2
      ACALL  DD1
      AJMP   MAIN

QDNC: CLR    P1.2;����ů������
      CLR    P1.0
      ACALL  DD2
      JB     P3.4,$
      SETB   P1.0
      ACALL  DD3
      AJMP   LOOP

XCQJ: MOV    R3,#0FH;Ѱ����ȳ���
XCQJ1:ACALL  BJ
      ACALL  DD1
      JNB    P3.4,XCQJ2;�ж�VT�Ƿ����ź�
      ACALL  DL
      JB     P3.4,XCQJ3;���򷵻�
XCQJ2:DJNZ   R3,XCQJ1
XCQJ3:AJMP   LOOP

DL:   MOV    R6,#01H;������ʱ�ӳ���
      DJNZ   R6,$
      RET

DD3:  MOV    R5,#01H;3����ʱ�ӳ���
D3:   MOV    R6,#01H
D4:   MOV    R7,#01H
      DJNZ   R7,$
      DJNZ   R6,D4
      DJNZ   R5,D3
      RET

DD2:  MOV    R5,#01H;2����ʱ�ӳ���
D5:   MOV    R6,#01H
D6:   MOV    R7,#01H
      DJNZ   R7,$
      DJNZ   R6,D6
      DJNZ   R5,D5
      RET

DD1:  MOV    R6,#01H;1����ʱ�ӳ���
D1:   MOV    R7,#01H
      DJNZ   R7,$
      DJNZ   R6,D1
      RET

BJ:   CLR    P1.4;������ʱ�ӳ���
      CLR    P1.3
      MOV    R6,#01H
B1:   MOV    R7,#01H
      DJNZ   R7,$
      DJNZ   R6,B1
      SETB   P1.3
      SETB   P1.4
      RET
      
      END
