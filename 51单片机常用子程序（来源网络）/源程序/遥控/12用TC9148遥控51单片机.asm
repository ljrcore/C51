;��TC9148ң��MCS-51��Ƭ��Դ����-2001��30��12�� 
;�������ж�����
      ORG    000BH
      LJMP   INT0
      ORG   0013H
      LJMP   INX1
;����Ϊ��ʼ������
MAIN��MOV  89H,#02H      ����TO��ʽ2��ʱ��ʽ
       MOV  8CH,#2EH     ���ö�ʱ����ֵ
       MOV  8AH,#2EH
       SETB  IT1             ����INTO���ش���
       SETB  ET0
       SETB  EX0
       SETB  EA             �����ж�
END�� SJMP  END            ��Ƕ���������򣬴˾䲻Ҫ
;����ΪINT1�жϷ������
INX1��SETB   TRO
      SETB   77H
      MOV   10H,#01H
      MOV   11H,#01H
      MOV   12H,#18H
      CLR EX1
      RETI
;����ΪT0�жϷ������
INT0��PVSH  PSW           �������Ĵ���
       PVSH  A
       PVSH  OPH
       PVSH  OPL
       PVSH  R0
       CPL   77H
       JB 77H,INTE          ��ÿ��������ִ��һ��
       MOV  A,11H         ���жϵ�ǰ״̬
       CJNE  A,#01H,INT1  ��״̬1
       MOV  C,P3.3         ������һ��24λ����
       ACALL  DIN1
       MOV  A,12H
       DEC   A
       MOV  12H,A
       JNZ   INTE
       MOV  12H,#28H
       MOV  11H,#02H
       SJMP  INTE
INT1��CJNE  A,#02H,INT2   ��״̬2
      MOV  C,P3.3           ������5�ο�ʡ��
        JC   INT11         �������м�40λ
        MOV  A,#01H
        ACALL  ERROR
        SJMP  INTE
INT11��MOV  A,12H
       DEC   A
       MOV  12H,A
       JNZ  INTE
       MOV  12H,#18H
       MOV  11H,#03H
       SJMP   INTE
INT2��CJNE  A,#03H,INTE    ��״̬3
       MOV  C,P3.3         ;��2�ζ�����
       ACALL  DIN2
       MOV  A,12H
       DEC  A
       MOV  12H,A
       JNZ  INTE
       MOV  11H,#04H
       CLR  TRO
       MOV  8AH,8CH
       ACALL  DCMP       ���Ƚ����ζ��õ�����
       JNC   INT3
       ACALL  ERROR
       SJMP  INTE
       ACALL  DMPG       �������ݽ���
       JNC  INT4
       ACALL  ERROR
       SJMP  INTE
INT4��ACALL  FUNC        ��������Ӧ�Ĺ����ӳ���
       SETB  EX1
       SJMP  INTE
INTE��POP  R0             ����ջ
       POP  DPL
       POP  DPH
       POP  A
       POP  PSW
       RETI               ���жϷ���
DIN1��MOV  A,32H      ������һ�ζ��õ�������λ����
       RLC  A            ��30H��31H��32H��Ԫ
       MOV  32H,A
       MOV  A,31H
       RLC  A
       MOV  31H,A
       MOV  A,30H
       RLC  A
         MOV  30H,A
         RET
DIN2��MOV  A,35H      ������2�ζ��õ�������λ����33H��34H
       RLC  A            ��35H��Ԫ
       MOV 35H,A
       MOV  A,34H
       RLC  A
       MOV 34H,A
       MOV A,33H
       RLC  A
       MOV  33H,A
       RET
ERROR��CLR  TRO           �����մ��������¿�ʼ
         MOV  8AH 8CH      ���µĽ���
         SETB  EX1
         RET
DCMP��MOV  A,33H         �����ζ������ݽ��бȽ�
       CJNE  A,30H,DC1    �����ӳ���
       MOV  A,34H
       CJNE  A,31H,DC1
       MOV  A,35H
       CJNE  A,32H,DC1
       MOV  A,30H
       ANL  A,#0FEH
       CJNE  A,#10H,DC1
       MOV  R0,#08H
DC2��ACALL  DSW           ���ж������Ƿ���ϣ�2����3������
      XCH  A,30H           �����������������ź�
      RRC  A
      XCH  A,30H
      ACALL  DSW
      RRC  A
      DJNZ  R0,DC2
      JNZ  DC1
      MOV  A,33H
      RRC  A
      MOV  A,30H
      CPL  A
      JNC  DC3             ��żУ��
      JB  P,DC1
      SJMP  DC4
DC3��JNBP DC1
DC4��CLR  C
      MOV  30H,A
         RET
DC1��SETB  C
      MOV  A,#02H
      RET
DSW��CLRC                ����31H��32H��������һλ
       XCH  A,31H
       RRC  A
       XCH  A,31H
       XCH  A,32H
       RRC  A
       XCH  A,32H
       RET
DMPG��MOV  OPTR,#DMB         ���Դ�������н����ӳ���
        MOV  R0,#00H             ���ó���Ӧ�ļ���
DM1��MOV  A,R0
      MOVC  A,@A+DPTR
      JZ  DM2
      CJNE  A,30H,DM3
      INC  R0
      MOV  A,R0
      MOVC  A,@A+DPTR
      CLR  C
      RET
DM2��MOV  A,#03H
      SETB  C
      RET
DM3��INC  R0
      INC  R0
      SJMP  DM1
FUNC��DEC A                 ��������Ӧ���ţ�������Ӧ���ӳ���
       CLR C                  ��ִ�и�����
       MOV  R0,A
       RLC  A
       ADD A,R0
       MOV  DPTR,#ZYB
       JMP  @A+DPTR
ZYB��LJMP  FUNC1    ��ת��ָ���FUNC1~FUNC18���û��Լ���д������
     LJMP  FUNC2    ��������Ĺ��ܣ�������RETָ�����
       .
       .
       .
     LJMP  FUNC18
DMB��DB  20H,01H,10H,02H,08H,03H,04H,04H    ���������Ӧ���ţ�
     DB  02H,05H,01H,06H,41H,07H,42H,08H
     DB  44H,09H,48H,0AH,50H,0BH,60H,0CH
     DB  81H,0DH,82H,0EH,84H,0FH,88H,10H
     DB  90H,11H,A0H,12H,00H,00H
;ע��FUNC1~FUNC18Ϊ�û��Զ���Ĺ����ӳ���,ִ�ж�ӦK1~K18�Ĺ���,Ӧ���б�д,
;�������õĿ���RETָ�����,���򷵻�ʹ��RETָ�
