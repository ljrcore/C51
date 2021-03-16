;用TC9148遥控MCS-51单片机源程序-2001年30期12版 
;以下置中断向量
      ORG    000BH
      LJMP   INT0
      ORG   0013H
      LJMP   INX1
;以下为初始化程序
MAIN：MOV  89H,#02H      ；置TO方式2定时方式
       MOV  8CH,#2EH     ；置定时器初值
       MOV  8AH,#2EH
       SETB  IT1             ；置INTO边沿触发
       SETB  ET0
       SETB  EX0
       SETB  EA             ；开中断
END： SJMP  END            ；嵌入其他程序，此句不要
;以下为INT1中断服务程序
INX1：SETB   TRO
      SETB   77H
      MOV   10H,#01H
      MOV   11H,#01H
      MOV   12H,#18H
      CLR EX1
      RETI
;以下为T0中断服务程序
INT0：PVSH  PSW           ；保护寄存器
       PVSH  A
       PVSH  OPH
       PVSH  OPL
       PVSH  R0
       CPL   77H
       JB 77H,INTE          ；每两次向下执行一次
       MOV  A,11H         ；判断当前状态
       CJNE  A,#01H,INT1  ；状态1
       MOV  C,P3.3         ；读第一次24位数据
       ACALL  DIN1
       MOV  A,12H
       DEC   A
       MOV  12H,A
       JNZ   INTE
       MOV  12H,#28H
       MOV  11H,#02H
       SJMP  INTE
INT1：CJNE  A,#02H,INT2   ；状态2
      MOV  C,P3.3           ；以下5段可省略
        JC   INT11         ；跳过中间40位
        MOV  A,#01H
        ACALL  ERROR
        SJMP  INTE
INT11：MOV  A,12H
       DEC   A
       MOV  12H,A
       JNZ  INTE
       MOV  12H,#18H
       MOV  11H,#03H
       SJMP   INTE
INT2：CJNE  A,#03H,INTE    ；状态3
       MOV  C,P3.3         ;第2次读数据
       ACALL  DIN2
       MOV  A,12H
       DEC  A
       MOV  12H,A
       JNZ  INTE
       MOV  11H,#04H
       CLR  TRO
       MOV  8AH,8CH
       ACALL  DCMP       ；比较两次读得的数据
       JNC   INT3
       ACALL  ERROR
       SJMP  INTE
       ACALL  DMPG       ；对数据解码
       JNC  INT4
       ACALL  ERROR
       SJMP  INTE
INT4：ACALL  FUNC        ；调用相应的功能子程序
       SETB  EX1
       SJMP  INTE
INTE：POP  R0             ；出栈
       POP  DPL
       POP  DPH
       POP  A
       POP  PSW
       RETI               ；中断返回
DIN1：MOV  A,32H      ；将第一次读得的数据逐位移入
       RLC  A            ；30H，31H，32H单元
       MOV  32H,A
       MOV  A,31H
       RLC  A
       MOV  31H,A
       MOV  A,30H
       RLC  A
         MOV  30H,A
         RET
DIN2：MOV  A,35H      ；将第2次读得的数据逐位移入33H，34H
       RLC  A            ；35H单元
       MOV 35H,A
       MOV  A,34H
       RLC  A
       MOV 34H,A
       MOV A,33H
       RLC  A
       MOV  33H,A
       RET
ERROR：CLR  TRO           ；接收错误则重新开始
         MOV  8AH 8CH      ；新的接收
         SETB  EX1
         RET
DCMP：MOV  A,33H         ；两次读得数据进行比较
       CJNE  A,30H,DC1    ；的子程序
       MOV  A,34H
       CJNE  A,31H,DC1
       MOV  A,35H
       CJNE  A,32H,DC1
       MOV  A,30H
       ANL  A,#0FEH
       CJNE  A,#10H,DC1
       MOV  R0,#08H
DC2：ACALL  DSW           ；判断数据是否符合（2）（3）规则
      XCH  A,30H           ；若是则解出纯编码信号
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
      JNC  DC3             ；偶校验
      JB  P,DC1
      SJMP  DC4
DC3：JNBP DC1
DC4：CLR  C
      MOV  30H,A
         RET
DC1：SETB  C
      MOV  A,#02H
      RET
DSW：CLRC                ；将31H，32H内容右移一位
       XCH  A,31H
       RRC  A
       XCH  A,31H
       XCH  A,32H
       RRC  A
       XCH  A,32H
       RET
DMPG：MOV  OPTR,#DMB         ；对纯编码进行解码子程序
        MOV  R0,#00H             ；得出相应的键号
DM1：MOV  A,R0
      MOVC  A,@A+DPTR
      JZ  DM2
      CJNE  A,30H,DM3
      INC  R0
      MOV  A,R0
      MOVC  A,@A+DPTR
      CLR  C
      RET
DM2：MOV  A,#03H
      SETB  C
      RET
DM3：INC  R0
      INC  R0
      SJMP  DM1
FUNC：DEC A                 ；根据相应键号，调用相应的子程序
       CLR C                  ；执行该命令
       MOV  R0,A
       RLC  A
       ADD A,R0
       MOV  DPTR,#ZYB
       JMP  @A+DPTR
ZYB：LJMP  FUNC1    ；转移指令表，FUNC1~FUNC18由用户自己编写，以完
     LJMP  FUNC2    ；成所需的功能，程序以RET指令结束
       .
       .
       .
     LJMP  FUNC18
DMB：DB  20H,01H,10H,02H,08H,03H,04H,04H    ；编码表（对应键号）
     DB  02H,05H,01H,06H,41H,07H,42H,08H
     DB  44H,09H,48H,0AH,50H,0BH,60H,0CH
     DB  81H,0DH,82H,0EH,84H,0FH,88H,10H
     DB  90H,11H,A0H,12H,00H,00H
;注：FUNC1~FUNC18为用户自定义的功能子程序,执行对应K1~K18的功能,应自行编写,
;若不须用的可用RET指令代替,程序返回使用RET指令。
