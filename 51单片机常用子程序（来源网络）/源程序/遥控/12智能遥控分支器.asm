;智能遥控分支器的单片机程序设计源程序-2001年31期12版
;1．分支分配器程序段：
;存储器用的是24c02集成电路
;控制部分：                          
PUSH ACC
MOV TL0,#80H 
MOV TH0,#0FBH 
MOV A,APBCL
CJNE A,#0BDH, BTT
MOV P1,#55H
AJMP DTE
BTT:
JNB 20H.0,DTA
CLR 20H.0
MOV A,PC1
ORL A,#55H
MOV P1,A
AJMP DTE
DTA:
SETB 20H.0
MOV A,PC1
MOV P1,A
DTE: 
NOP
POP ACC
SETB TR0
RETI
;读存储器：
ACALL ISTA
MOV A,#0A0H
ACALL IWRBYT
ACALL IACK
MOV A,STARTADD
ACALL IWRBYT
ACALL IACK
ACALL ISTA
MOV A,#0A1H
ACALL IWRBYT
ACALL IACK
ACALL IRDBYT
MOV DATABUF,A
ACALL IACK
ACALL ISTOP
RET
;写存储器：
ACALL ISTA
MOV A,#0A0H
ACALL IWRBYT
ACALL IACK
MOV A,STARTADD
ACALL IWRBYT
ACALL IACK
MOV A,DATABUF
ACALL IWRBYT
ACALL IACK
ACALL ISTOP
RET
;启动信号：
ISTA:
SETB ISDA
NOP
NOP
SETB ISCL
NOP
NOP
CLR ISDA
NOP
CLR ISCL
RET
;停止信号：
ISTOP:
CLR ISDA
NOP
NOP
SETB ISCL
NOP
NOP 
SETB ISDA
NOP
NOP 
CLR ISCL
RET
;应答信号： 
ICACK:
SETB ISDA
NOP
NOP
SETB ISCL
NOP
NOP
CLR ISCL
RET
;写字节：
IWRBYT:
MOV R7,#08H
WLP:
RLC A
MOV ISDA,C
NOP
NOP
SETB ISCL
NOP
CLR ISCL
DJNZ R7,WLP
RET
;读字节： 
IRDBYT:
MOV R7,#08H
SETB ISDA
RLP:
CLR ISCL
NOP
NOP
SETB ISCL
NOP
NOP
MOV C,ISDA
RLC A
DJNZ R7,RLP
RET
;2．供电器部分程序段：
;存储器用的25045
;取红外线：
SETB P3.7
JNB P3.7,W0
RET
W0:
MOV 10H,#00H
MOV R1,#22H
W1:
JB P3.7,W3 
ACALL C_DAT
CJNE A,#0D0H,H0
AJMP H3
H0:
JNC H3
ACALL RDOG 
AJMP W1
W2:
JNB P3.7,W4 
ACALL C_DAT
CJNE A,#0D0H,H1
AJMP H3
H1:
JNC H3
ACALL RDOG 
AJMP W2 
W3: 
MOV @R1,10H
INC R1
MOV 10H,#00H
CJNE R1,#2EH,W2 
AJMP H4
W4: 
CJNE R1,#2EH,W1 
H4: 
ACALL D_DAT
H3:
RET
C_DAT:
MOV A,10H
INC A
MOV 10H,A 
MOV R3,#05H
DJNZ R3,$
RET
;发送子程序：
ACALL RDOG 
PUSH 05H
PUSH 00H
MOV R6,#09H 
S_DAT0:
MOV R5,#02H 
S_DAT1:
ACALL RDOG 
MOV SBUF,#0CDH
JNB TI,$
CLR TI
DJNZ R5,S_DAT1 
MOV R5,#03H 
MOV R0,#RE_ADD+2
S_DAT2: 
ACALL RDOG
MOV SBUF,@R0
JNB TI,$
CLR TI
INC R0
DJNZ R5,S_DAT2
MOV A,RE_ADD+2
XRL A,RE_ADD+3
XRL A,RE_ADD+4
CLR ACC.7
ACALL RDOG 
MOV SBUF,A
JNB TI,$
CLR TI
DJNZ R6,S_DAT0 
POP 00H
POP 05H
ACALL RDOG
;数据显示： 
MOVC A,@A+DPTR
CLR DISP_CK
NOP
MOV B,#8
DISP1: 
RRC A
MOV DISP_DA,C
NOP
NOP
SETB DISP_CK
NOP
NOP
NOP
NOP
NOP
NOP
CLR DISP_CK
DJNZ B,DISP1
;读写存储器：
WRSR_C: 
CLR SCK
CLR CS
MOV A,#WRSR
ACALL OUTBYT
MOV A,#STATUS
ACALL OUTBYT
CLR SCK
SETB CS
ACALL WIP_P 
RET
WRSR_P:
CLR SCK
CLR CS
MOV A,#1
ACALL OUTBYT
MOV A,#STATUS
ACALL OUTBYT
CLR SCK
SETB CS
ACALL WIP_P 
RET
WREN_C: 
CLR SCK
CLR CS
MOV A,#WREN
ACALL OUTBYT
CLR SCK
SETB CS
RET
WRDI_C:
CLR SCK
CLR CS
MOV A,#WRDI
ACALL OUTBYT
CLR SCK
SETB CS
RET 
RDSR_C: 
CLR SCK
CLR CS
MOV A,#RDSR
ACALL OUTBYT
ACALL INBYT
CLR SCK
SETB CS
RET
WR_BYTE:
NOP
SETB WP
ACALL DELAY
ACALL WRSR_P
ACALL WREN_C
ACALL RDOG
NOP
MOV DPL,R4
MOV DPH,#0
CLR SCK
CLR CS
MOV A,#WRITE
MOV B,DPH
MOV C,B.0
MOV ACC.3,C
ACALL OUTBYT
MOV A,DPL
ACALL OUTBYT
ACALL OUTBYT
CLR SCK
SETB CS
ACALL WIP_P
ACALL RDOG
ACALL DELAY
CLR WP
NOP
ACALL WRDI_C
ACALL DELAY
ACALL WRSR_C
RET
WR_ADD:
NOP
SETB WP
ACALL DELAY
ACALL WRSR_P
ACALL WREN_C
ACALL RDOG
MOV DPTR,#P_ADDR
CLR SCK
CLR CS
MOV A,#WRITE
MOV B,DPH
MOV C,B.0
MOV ACC.3,C
ACALL OUTBYT
MOV A,DPL
ACALL OUTBYT
MOV A,RE_ADD
ACALL OUTBYT
NOP
MOV A,RE_ADD+1
ACALL OUTBYT
NOP
CLR SCK
SETB CS
ACALL WIP_P
ACALL RDOG
ACALL DELAY
CLR WP
NOP
ACALL WRDI_C
ACALL DELAY
ACALL WRSR_C
RET
RD_ZNADST:
ACALL RDOG
NOP
MOV DPL,ZNDD
MOV DPH,#0
NOP
CLR SCK
CLR CS
MOV A,#READ
MOV B,DPH
MOV C,B.0
MOV ACC.3,C
ACALL OUTBYT
MOV A,DPL
ACALL OUTBYT
NOP
ACALL INBYT
MOV ZNST,A
NOP
CLR SCK
SETB CS
RET
RE_NBYTE:
NOP
MOV DPTR,#P_ADDR
MOV R1,#ADD1
MOV R6,#06H
NOP
CLR SCK
CLR CS
MOV A,#READ
MOV B,DPH
MOV C,B.0
MOV ACC.3,C
ACALL OUTBYT
MOV A,DPL
ACALL OUTBYT
REV_N1:
NOP
ACALL INBYT
MOV @R1,A
INC R1
NOP
NOP
DJNZ R6,REV_N1
NOP
CLR SCK
SETB CS
RET
WR_ZNADST:
NOP
SETB WP
ACALL DELAY
ACALL WRSR_P
ACALL WREN_C
ACALL RDOG
MOV DPL,ZNDD
MOV DPH,#0
CLR SCK
CLR CS
MOV A,#WRITE
MOV B,DPH
MOV C,B.0
MOV ACC.3,C
ACALL OUTBYT
MOV A,DPL
ACALL OUTBYT
MOV A,ZNST
ACALL OUTBYT
NOP
CLR SCK
SETB CS
ACALL WIP_P
ACALL RDOG
ACALL DELAY
CLR WP
NOP
ACALL WRDI_C
ACALL DELAY
ACALL WRSR_C
RET
RDOG:
NOP
CLR CS
NOP
SETB CS
NOP
RET
WIP_P:
MOV R1,#MAX
WIP_P1:
NOP
ACALL RDSR_C
JNB ACC.0,WIP_P2
DJNZ R1,WIP_P1
WIP_P2:
NOP
RET
OUTBYT:
MOV R0,#8
OUTBY1:
NOP
CLR SCK
NOP
RLC A
MOV SDI,C
SETB SCK
NOP
DJNZ R0,OUTBY1
CLR SDI
RET
INBYT:
MOV R0,#8
INBYT1:
NOP
SETB SCK
NOP
NOP
CLR SCK
NOP
NOP
MOV C,SO
RLC A
DJNZ R0,INBYT1
RET