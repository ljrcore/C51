;����ң�����ĵ�Ƭ���������
;���ӱ�2001��18��12��
        Cs_X1    EQU   26H      ;���ݻ������ֽ���
        Cs0_X1   EQU   25H      ;������һ���ֽ��м�λ
        U0_X1    EQU   40H      ;������ʱ����ֽڣ�����8λ����2AH~2FH
        N0_M     EQU   1EH      ;��ֵ��ŵ�Ԫ
        N0_J     EQU   1FH      ;ң����ʶ����
        X1_N1    EQU   2AH      ;����������Ԫ������λ��������
        X1_N2    EQU   2BH      ;ң���������ݻ�����
        X1_N3    EQU   2CH
        X1_N4    EQU   2DH
        X1_N5    EQU   2EH
        X1_N6    EQU   2FH
        ORG      00H            ;ת������
        LJMP     REST0
        ORG      13H
        LJMP     INT_X1         ;ת�ⲿ�ж�1
        ORG      100H 
REST0:  CLR      EA             ;���ж�
        MOV      SP,#60H        ;���ö�ջ
        MOV      R0,#50H        ;0~50H��0
        CLR      A
RE_0:   MOV      @R0,A
        DJNZ     R0,RE_0
        MOV      IP,#00H        ;�ж����ȼ�
        CLR      TR1            ;��T1
        MOV      TL1,#00H       ;T1ʱ�䳣���ͳ�ֵ
        MOV      TH1,#00H
        MOV      18H,#2AH       ;��INT1�жϷ��������ʹ�ù�#3�Ĵ�����R0=2AH
        MOV      Cs0_X1,#06H    ;��������ȡ6���ֽ�
        MOV      Cs_X1,#08H     ;ÿ���ֽ�8λ
        MOV      N0_M,#0FFH     ;ʶ��������FFH��������δ����ʱ������
        MOV      A,#1FH         ;ѡ��T1����4λ��01H����4λ����
        ANL      TMOD,A         ;��T1����������Ӱ����������
        SETB     EX1            ;���ж�1��INT1
        SETB     IT1            ;INT1�½��ش���
        SETB     EA             ;���жϣ��ȴ�
LOOP:   LJMP     lOOP
        �� 
        ��
INT_X1: PUSH     ACC
        PUSH     PSW
        ORL      PSW,#18H       ;ȡ3#���Ĵ���
        CLR      TR1            ;T1ֹͣ����
        MOV      R2,TH1         ;ȡT1��������
        MOV      R3,TL1
        MOV      R4,#01H        ;0190H~0200HΪ���ݴ���0
        MOV      R5,#90H        ;����0������
        LCALL    SUB0           ;����ֵС��190H��
        JC       X1_OUT1        ;<190H������
        MOV      R4,#02H        ;����0������
        MOV      R5,#00H
        MOV      R2,TH1         ;ȡT1��������
        MOV      R3,TL1
        LCALL    SUB0           ;����ֵ����200H��
        JNC      X1_01          ;>200��ȥ���Ƿ���1�Ĵ���
        CLR      C              ;�ڴ���0�У���C����λʱ����0
        LJMP     X1_02          ;ȥ��λ����
X1_01:  MOV      R4,#03H        ;����1������
        MOV      R5,#90H        ;0390H~0400HΪ����1
        MOV      R2,TH1         ;ȡT1��������
        MOV      R3,TL1
        LCALL    SUB0           ;����ֵС��390H��
        JC       X1_OUT1        ;<0390������
        MOV      R4,#04H        ;����1������
        MOV      R5,#00H        ;#0400
        MOV      R2,TH1	        ;ȡT1��������
        MOV      R3,TL1
        LCALL    SUB0           ;����ֵ����#400H��
        JNC      X1_OUT1        ;>400H������
        SETB     C              ;�ڴ���1�У���C��1
X1_02:  MOV      A,U0_X1        ;��ʱ��ŵ�Ԫ��A
        RLC      A              ;���ƣ�0��1����D0
        MOV      U0_X1,A        ;�������һλ��������U0_X1��Ԫ��40H��
        DJNZ     Cs_X1,X1_OUT1  ;����8λת��
        MOV      Cs_X1,#08H     ;��һ�����ݻ���8λ
        MOV      @R0,U0_X1      ;���ݴ���@R0
        INC      R0             ;��һ�����ݴ�����һ�ֽ�
        DJNZ     Cs0_X1,X1_OUT1 ;����6�����жϷ���
        LJMP     X1_10          ;�Ѵ���6������תȥ����
X1_OUT1:MOV      TH1,#00H       ;��T1ʱ�䳣��
        MOV      TL1,#00H
        SETB     TR1            ;����T1
        POP      PSW
        POP      ACC
        SETB	 EA             ;���жϣ��жϷ���
        RETI                    ;����Ϊ���ݴ������
X1_10:  MOV      Cs0_X1,#10H    ;�����λ10H��
        MOV      A,X1_N1        ;��һ���ֽ���A
X1S_01: CJNE     A,#0E2H,X1S_00 ;E2HΪʶ���룬��A��������#E2Hתȥ��λ
        MOV      A,X1_N3        ;��A��=#E2H���������ֽ�Ҳ����#E2H��
X1S_03: CJNE     A,#0E2H,X1S_00	;���ȣ�תȥ��λ
        MOV      A,X1_N4        ;�ȣ��ٿ��ڶ����ֽں͵��ĸ��ֽ������
        CJNE     A,X1_N2,X1S_00	;���ȣ�תȥ��λ
        SJMP     X1S_07	        ;ʶ���룬����ȫ����ȷ
X1S_00: CLR      C              ;����Ϊ�����ֽ�������λ
        MOV      A,X1_N6
        RLC      A
        MOV      X1_N6,A
        MOV      A,X1_N5
        RLC      A
        MOV      X1_N5,A
        MOV      A,X1_N4
        RLC      A
        MOV      X1_N4,A
        MOV      A,X1_N3
        RLC      A
        MOV      X1_N3,A
        MOV      A,X1_N2
        RLC      A
        MOV      X1_N2,A
        MOV      A,X1_N1
        RLC      A
        MOV      X1_N1,A        ;����
        DJNZ     Cs0_X1,X1S_01  ;û�ƹ�10H����ȥ�ж�
X1S_04: MOV      A,X1_N3        ;���ƹ�10H�Σ����ж�һ��
        CJNE     A,X1_N1,X1S_05	;��2AH�������ڣ�2CH���򲻵���#E2H����������
        CJNE     A,#0E2H,X1S_05
        MOV      A,X1_N2        ;��2AH��=��2CH��=#E2H���ٿ���2BH��=��2DH����
        CJNE     A,X1_N4,X1S_05	;���ȣ�ת��
X1S_07: MOV      NO_J,X1_N1     ;ʶ������N0_J
        MOV      NO_M,X1_N2     ;������N0_M
        LCALL    DEL10mS
X1S_06: MOV      Cs_X1,#08H     ;׼��������һ�����ݣ�һ���ֽ�8λ
        MOV      R0,#2AH        ;��һ�������׵�ַ
        MOV      Cs0_X1,#06H    ;6���ֽ�
        LJMP     X1_OUT1        ;ת��
X1S_05: MOV      NO_M,#0FFH     ;���ݵ�Ԫ��#FFH
        MOV      NO_J,#00H      ;ʶ��洢��Ԫ��#00
        SJMP     X1S_06         ;ȥ׼��������һ������
SUB0:   CLR      CY             ;�����ӳ���
        MOV      A,R3           ;��������λ��A
        SUBB     A,R5           ;��λ��
        JNC      X1_S1          ;û��λ��ȥ�����λ����
        DEC      R2             ;�н�λ����������λ��1
X1_S1:  CLR      CY             ;��C
        MOV      A,R2           ;��������λ
        SUBB     A,R4           ;����������λ
        RET                     ;����
DEL10mS:MOV      R2,#0FFH       ;��ʱ�ӳ���
DEL_01: MOV      R3,#0FFH
DEL_02: NOP
        NOP
        DJNZ     R3,DEL_02
        DJNZ     R2,DEL_01
        RET
        END