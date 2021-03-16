;电视遥控器的单片机译码程序
;电子报2001年18期12版
        Cs_X1    EQU   26H      ;数据缓冲区字节数
        Cs0_X1   EQU   25H      ;缓冲区一个字节有几位
        U0_X1    EQU   40H      ;数据临时存放字节，存满8位后送2AH~2FH
        N0_M     EQU   1EH      ;键值存放单元
        N0_J     EQU   1FH      ;遥控器识别码
        X1_N1    EQU   2AH      ;连续六个单元，（可位操作）作
        X1_N2    EQU   2BH      ;遥控输入数据缓冲区
        X1_N3    EQU   2CH
        X1_N4    EQU   2DH
        X1_N5    EQU   2EH
        X1_N6    EQU   2FH
        ORG      00H            ;转主程序
        LJMP     REST0
        ORG      13H
        LJMP     INT_X1         ;转外部中断1
        ORG      100H 
REST0:  CLR      EA             ;关中断
        MOV      SP,#60H        ;设置堆栈
        MOV      R0,#50H        ;0~50H清0
        CLR      A
RE_0:   MOV      @R0,A
        DJNZ     R0,RE_0
        MOV      IP,#00H        ;中断优先级
        CLR      TR1            ;关T1
        MOV      TL1,#00H       ;T1时间常数送初值
        MOV      TH1,#00H
        MOV      18H,#2AH       ;在INT1中断服务程序中使用工#3寄存器，R0=2AH
        MOV      Cs0_X1,#06H    ;输入数据取6个字节
        MOV      Cs_X1,#08H     ;每个字节8位
        MOV      N0_M,#0FFH     ;识别码先送FFH，以免在未送数时错当有数
        MOV      A,#1FH         ;选择T1，高4位送01H，低4位不变
        ANL      TMOD,A         ;送T1参数，但不影响其他参数
        SETB     EX1            ;开中断1，INT1
        SETB     IT1            ;INT1下降沿触发
        SETB     EA             ;开中断，等待
LOOP:   LJMP     lOOP
        … 
        …
INT_X1: PUSH     ACC
        PUSH     PSW
        ORL      PSW,#18H       ;取3#区寄存器
        CLR      TR1            ;T1停止计数
        MOV      R2,TH1         ;取T1计数次数
        MOV      R3,TL1
        MOV      R4,#01H        ;0190H~0200H为数据窗口0
        MOV      R5,#90H        ;窗口0的下限
        LCALL    SUB0           ;计数值小于190H吗？
        JC       X1_OUT1        ;<190H，作废
        MOV      R4,#02H        ;窗口0的上限
        MOV      R5,#00H
        MOV      R2,TH1         ;取T1计数次数
        MOV      R3,TL1
        LCALL    SUB0           ;计数值大于200H吗？
        JNC      X1_01          ;>200，去看是否在1的窗口
        CLR      C              ;在窗口0中，清C，移位时移入0
        LJMP     X1_02          ;去移位处理
X1_01:  MOV      R4,#03H        ;窗口1的下限
        MOV      R5,#90H        ;0390H~0400H为窗口1
        MOV      R2,TH1         ;取T1计数次数
        MOV      R3,TL1
        LCALL    SUB0           ;计数值小于390H吗？
        JC       X1_OUT1        ;<0390，作废
        MOV      R4,#04H        ;窗口1的上限
        MOV      R5,#00H        ;#0400
        MOV      R2,TH1	        ;取T1计数次数
        MOV      R3,TL1
        LCALL    SUB0           ;计数值大于#400H吗？
        JNC      X1_OUT1        ;>400H，作废
        SETB     C              ;在窗口1中，将C置1
X1_02:  MOV      A,U0_X1        ;临时存放单元送A
        RLC      A              ;左移，0或1进入D0
        MOV      U0_X1,A        ;新输入的一位数据移入U0_X1单元（40H）
        DJNZ     Cs_X1,X1_OUT1  ;不到8位转走
        MOV      Cs_X1,#08H     ;下一个数据还是8位
        MOV      @R0,U0_X1      ;数据存入@R0
        INC      R0             ;下一个数据存入下一字节
        DJNZ     Cs0_X1,X1_OUT1 ;不够6个数中断返回
        LJMP     X1_10          ;已存满6个数，转去处理
X1_OUT1:MOV      TH1,#00H       ;送T1时间常数
        MOV      TL1,#00H
        SETB     TR1            ;启动T1
        POP      PSW
        POP      ACC
        SETB	 EA             ;开中断，中断返回
        RETI                    ;以下为数据处理程序
X1_10:  MOV      Cs0_X1,#10H    ;最多移位10H次
        MOV      A,X1_N1        ;第一个字节送A
X1S_01: CJNE     A,#0E2H,X1S_00 ;E2H为识别码，（A）不等于#E2H转去移位
        MOV      A,X1_N3        ;（A）=#E2H，第三个字节也等于#E2H吗
X1S_03: CJNE     A,#0E2H,X1S_00	;不等，转去移位
        MOV      A,X1_N4        ;等，再看第二个字节和第四个字节相等吗？
        CJNE     A,X1_N2,X1S_00	;不等，转去移位
        SJMP     X1S_07	        ;识别码，数据全部正确
X1S_00: CLR      C              ;以下为六个字节依次移位
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
        MOV      X1_N1,A        ;移完
        DJNZ     Cs0_X1,X1S_01  ;没移够10H次再去判断
X1S_04: MOV      A,X1_N3        ;已移够10H次，再判断一次
        CJNE     A,X1_N1,X1S_05	;（2AH）不等于（2CH）或不等于#E2H，数据作废
        CJNE     A,#0E2H,X1S_05
        MOV      A,X1_N2        ;（2AH）=（2CH）=#E2H，再看（2BH）=（2DH）吗
        CJNE     A,X1_N4,X1S_05	;不等，转走
X1S_07: MOV      NO_J,X1_N1     ;识别码送N0_J
        MOV      NO_M,X1_N2     ;数据送N0_M
        LCALL    DEL10mS
X1S_06: MOV      Cs_X1,#08H     ;准备接收下一个数据，一个字节8位
        MOV      R0,#2AH        ;下一个数据首地址
        MOV      Cs0_X1,#06H    ;6个字节
        LJMP     X1_OUT1        ;转走
X1S_05: MOV      NO_M,#0FFH     ;数据单元送#FFH
        MOV      NO_J,#00H      ;识别存储单元送#00
        SJMP     X1S_06         ;去准备接收下一个数据
SUB0:   CLR      CY             ;减法子程序
        MOV      A,R3           ;被减数低位送A
        SUBB     A,R5           ;低位减
        JNC      X1_S1          ;没进位，去处理高位减法
        DEC      R2             ;有进位，被减数高位减1
X1_S1:  CLR      CY             ;清C
        MOV      A,R2           ;被减数高位
        SUBB     A,R4           ;减被减数高位
        RET                     ;返回
DEL10mS:MOV      R2,#0FFH       ;延时子程序
DEL_01: MOV      R3,#0FFH
DEL_02: NOP
        NOP
        DJNZ     R3,DEL_02
        DJNZ     R2,DEL_01
        RET
        END