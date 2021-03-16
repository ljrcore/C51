      ORG    0000H
      AJMP   MAIN
      ORG    0050H
MAIN: MOV    P1,#0FFH
      ACALL  DD3
LOOP: JNB    P3.4,LOOP;判断VT是否有信号
      ACALL  DL;延时防抖动
      JB     P3.4,START;有信号则启动
      AJMP   LOOP;无则返回LOOP
START:JNB    P3.0,XD1;判断D1信号
      ACALL  DL
      JB     P3.0,FDSD;有则进入防盗设定
XD1:  JNB    P3.1,XD2;判断D2信号
      ACALL  DL
      JB     P3.1,JCFD;有则进入解除防盗
XD2:  JNB    P3.2,XD3;判断D3信号
      ACALL  DL
      JB     P3.2,QDNC;有则进入启动暖车
XD3:  JNB    P3.3,XD4;判断D4信号
      ACALL  DL
      JB     P3.3,XCQJ;有则进入寻车求救
XD4:  AJMP   LOOP;无D1-D4的信号则返回LOOP

FDSD: ACALL  BJ;防盗设定程序,先报警
      ACALL  DD3;延时3秒
FD1:  JNB    P3.5,FD2;判断振动信号
      ACALL  DL
      JB     P3.5,BZC;有则进入报警判断程序
FD2:  JNB    P3.7,FD3;判断锁头正电线是否带电
      ACALL  DL
      JB     P3.7,BZC;有则进入报警判断程序
FD3:  JNB    P3.4,FD4;判断VT是否有信号
      ACALL  DL
      JB     P3.4,FH;有则返回
FD4:  AJMP   FD1
BZC:  ACALL  BJ;报警判断程序
      ACALL  DD3
      ACALL  DD2;延时5秒
      JNB    P3.5,BZC1;判断振动信号
      ACALL  DL
      JB     P3.5,BJJ;有则进入连续报警
BZC1: JNB    P3.7,BZC2;判断锁头正电线是否带电
      ACALL  DL
      JB     P3.7,BJJ;有则进入连续报警
BZC2: JNB    P3.4,BZC3;判断VT是否有信号
      ACALL  DL
      JB     P3.4,FH;有则返回
BZC3: AJMP   FD1
BJJ:  ACALL  BJ;连续报警程序
      ACALL  DD1
      JNB    P3.7,BJJ1;判断锁头正电线是否带电
      ACALL  DL
      JB     P3.7,XH;有则进入熄火程序
BJJ1: JNB    P3.4,BJJ2;判断VT是否有信号
      ACALL  DL
      JB     P3.4,FH;有则返回
BJJ2: AJMP   BJJ
XH:   CLR    P1.1;熄火程序
      SETB   P1.2
      ACALL  DD1
      SETB   P1.1
      AJMP   BJJ
FH:   AJMP   MAIN

JCFD: ACALL  BJ;解除防盗程序,先报警2次
      ACALL  DD1
      ACALL  BJ
      CLR    P1.1
      SETB   P1.2
      ACALL  DD1
      AJMP   MAIN

QDNC: CLR    P1.2;启动暖车程序
      CLR    P1.0
      ACALL  DD2
      JB     P3.4,$
      SETB   P1.0
      ACALL  DD3
      AJMP   LOOP

XCQJ: MOV    R3,#0FH;寻车求救程序
XCQJ1:ACALL  BJ
      ACALL  DD1
      JNB    P3.4,XCQJ2;判断VT是否有信号
      ACALL  DL
      JB     P3.4,XCQJ3;有则返回
XCQJ2:DJNZ   R3,XCQJ1
XCQJ3:AJMP   LOOP

DL:   MOV    R6,#01H;按键延时子程序
      DJNZ   R6,$
      RET

DD3:  MOV    R5,#01H;3秒延时子程序
D3:   MOV    R6,#01H
D4:   MOV    R7,#01H
      DJNZ   R7,$
      DJNZ   R6,D4
      DJNZ   R5,D3
      RET

DD2:  MOV    R5,#01H;2秒延时子程序
D5:   MOV    R6,#01H
D6:   MOV    R7,#01H
      DJNZ   R7,$
      DJNZ   R6,D6
      DJNZ   R5,D5
      RET

DD1:  MOV    R6,#01H;1秒延时子程序
D1:   MOV    R7,#01H
      DJNZ   R7,$
      DJNZ   R6,D1
      RET

BJ:   CLR    P1.4;报警延时子程序
      CLR    P1.3
      MOV    R6,#01H
B1:   MOV    R7,#01H
      DJNZ   R7,$
      DJNZ   R6,B1
      SETB   P1.3
      SETB   P1.4
      RET
      
      END
