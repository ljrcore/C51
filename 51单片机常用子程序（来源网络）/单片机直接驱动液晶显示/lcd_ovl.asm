bcd_8:
        mov b,#10
        div ab 
        ret
;*************************************************************
BTOF: INC R0
INC R0
MOV A,@R0
MOV R7,A
DEC R0
MOV A,@R0
MOV R6,A
DEC R0
ORL A,R7
JNZ BTF0
MOV @R0,#41H
RET
BTF0: MOV A,@R0
MOV C,ACC.7
MOV 1DH,C 
CLR 1FH
MOV C,ACC.6 
MOV ACC.7,C
MOV @R0,A
JNC BTF1
ADD A,#19
JC BTF2
MOV @R0,#41H
INC R0
MOV @R0,#0
INC R0
MOV @R0,#0
DEC R0
DEC R0
RET
BTF1: SUBB A,#19
JC BTF2
MOV A,#3FH 
MOV C,1DH
MOV ACC.7,C
MOV @R0,A
INC R0
MOV @R0,#0FFH
INC R0
MOV @R0,#0FFH
DEC R0
DEC R0
RET
BTF2: CLR A 
MOV R4,A
MOV R3,A
MOV R2,#10H 
BTF3: MOV A,R7
ADD A,R7
DA A
MOV R7,A
MOV A,R6
ADDC A,R6
DA A
MOV R6,A
MOV A,R4
RLC A
MOV R4,A
MOV A,R3
RLC A
MOV R3,A
DEC R2
JNB ACC.7,BTF3
MOV A,R6
ADD A,#0B0H
CLR A
ADDC A,R4
MOV R4,A
CLR A
ADDC A,R3
MOV R3,A
JNC BTF4
MOV R3,#80H
INC R2
BTF4: MOV DPTR,#BTFL
MOV A,@R0
ADD A,#19
MOV B,#3
MUL AB
ADD A,DPL
MOV DPL,A
JNC BTF5
INC DPH
BTF5: CLR A 
MOVC A,@A+DPTR
MOV C,ACC.6
MOV ACC.7,C
MOV R5,A
MOV A,#1
MOVC A,@A+DPTR
MOV R6,A
MOV A,#2
MOVC A,@A+DPTR
MOV R7,A
LCALL MUL1 
MOV C,1DH 
MOV 1FH,C
LJMP MOV0
FTOB: INC R0
MOV A,@R0
INC R0
ORL A,@R0
DEC R0
DEC R0
JNZ FTB0
MOV @R0,#41H
RET
FTB0: MOV A,@R0
MOV C,ACC.7
MOV 1DH,C
CLR ACC.7
MOV @R0,A
LCALL MVR0
MOV DPTR,#BFL0
MOV B,#0 
MOV A,R2
JNB ACC.7,FTB1
MOV DPTR,#BTFL
MOV B,#0EDH 
ADD A,#16
JNC FTB1
MOV DPTR,#BFLN
MOV B,#0FAH 
FTB1: CLR A 
MOVC A,@A+DPTR
MOV C,ACC.6
MOV ACC.7,C
MOV R5,A
MOV A,#1
MOVC A,@A+DPTR
MOV R6,A
MOV A,#2
MOVC A,@A+DPTR
MOV R7,A
MOV A,R5
CLR C
SUBB A,R2
JB ACC.7,FTB2
JNZ FTB3
MOV A,R6
CLR C
SUBB A,R3
JC FTB2
JNZ FTB3
MOV A,R7
CLR C
SUBB A,R4
JC FTB2
JNZ FTB3
MOV R5,B
INC R5 
MOV R6,#10H 
MOV R7,#0
SJMP FTB6 
FTB2: INC DPTR 
INC DPTR
INC DPTR
INC B 
SJMP FTB1  
FTB3: PUSH B 
LCALL DIV3 
FTB4: MOV A,R2
JZ FTB5
CLR C
LCALL RR1 
SJMP FTB4
FTB5: POP ACC 
MOV R5,A 
LCALL HB2
MOV R6,A
LCALL HB2
MOV R7,A
MOV A,R3
RLC A
CLR A
ADDC A,R7
DA A
MOV R7,A
CLR A
ADDC A,R6
DA A
MOV R6,A
JNC FTB6
MOV R6,#10H
INC R5
FTB6: INC R0 
INC R0
MOV A,R7
MOV @R0,A
DEC R0
MOV A,R6
MOV @R0,A
DEC R0
MOV A,R5
MOV C,1DH 
MOV ACC.7,C
MOV @R0,A 
RET
HB2: MOV A,R4 
MOV B,#100
MUL AB
MOV R4,A
MOV A,B
XCH A,R3
MOV B,#100
MUL AB

ADD A,R3
MOV R3,A
JNC HB21
INC B
HB21: MOV A,B 
MOV B,#10
DIV AB
SWAP A
ORL A,B
RET
BTFL: DB 41H,0ECH,1EH 
DB 45H,93H,93H
DB 48H,0B8H,78H 
DB 4BH,0E6H,96H
DB 4FH,90H,1DH 
DB 52H,0B4H,25H
DB 55H,0E1H,2EH
DB 59H,8CH,0BDH
DB 5CH,0AFH,0ECH
DB 5FH,0DBH,0E7H
DB 63H,89H,70H 
DB 66H,0ABH,0CCH
DB 69H,0D6H,0C0H
BFLN: DB 6DH,86H,38H 
DB 70H,0A7H,0C6H 
DB 73H,0D1H,0B7H 
DB 77H,83H,12H 
DB 7AH,0A3H,0D7H
DB 7DH,0CCH,0CDH
BFL0: DB 1,80H,00H 
DB 4,0A0H,00H 
DB 7,0C8H,00H 
DB 0AH,0FAH,00H
DB 0EH,9CH,40H 
DB 11H,0C3H,50H
DB 14H,0F4H,24H
DB 18H,98H,97H 
DB 1BH,0BEH,0BCH
DB 1EH,0EEH,6BH 
DB 22H,95H,03H 
DB 25H,0BAH,44H
DB 28H,0E8H,0D5h
DB 2CH,91H,85H 
DB 2FH,0B5H,0E6H
DB 32H,0E3H,60H 
DB 36H,8EH,1CH 
DB 39H,31H,0A3H
DB 3CH,0DEH,0BH
DB 40H,8AH,0C7H
FMUL: LCALL MVR0 
MOV A,@R0
XRL A,@R1
RLC A
MOV 1FH,C 
LCALL MUL0
LJMP MOV0 
MUL0: LCALL MVR1
MUL1: MOV A,R3
ORL A,R4
JZ MUL6
MOV A,R6
ORL A,R7
JZ MUL5
MOV A,R7
MOV B,R4
MUL AB
MOV A,B
XCH A,R7
MOV B,R3
MUL AB
ADD A,R7
MOV R7,A
CLR A
ADDC A,B
XCH A,R4
MOV B,R6
MUL AB
ADD A,R7
MOV R7,A
MOV A,B
ADDC A,R4
MOV R4,A
CLR A
RLC A
XCH A,R3
MOV B,R6
MUL AB
ADD A,R4
MOV R4,A
MOV A,B
ADDC A,R3
MOV R3,A
JB ACC.7,MUL2
MOV A,R7 
RLC A
MOV R7,A
LCALL RL1
MUL2: MOV A,R7
JNB ACC.7,MUL3
INC R4
MOV A,R4
JNZ MUL3
INC R3
MOV A,R3
JNZ MUL3
MOV R3,#80H
INC R2
MUL3: MOV A,R2
ADD A,R5
MD: MOV R2,A 
JB ACC.7,MUL4
JNB ACC.6,MUL6
MOV R2,#3FH 
SETB OV
RET
MUL4: JB ACC.6,MUL6
MUL5: CLR A 
MOV R3,A
MOV R4,A
MOV R2,#41H
MUL6: CLR OV
RET

FDIV: INC R0
MOV A,@R0
INC R0
ORL A,@R0
DEC R0
DEC R0
JNZ DIV1
MOV @R0,#41H
CLR OV
RET
DIV1: INC R1
MOV A,@R1
INC R1 
ORL A,@R1
DEC R1
DEC R1 
JNZ DIV2 
SETB OV
RET 
DIV2: LCALL MVR0
MOV A,@R0
XRL A,@R1 
RLC A
MOV 1FH,C
LCALL MVR1 
LCALL DIV3
LJMP MOV0 
DIV3: CLR C 
MOV A,R4
SUBB A,R7
MOV A,R3
SUBB A,R6
JC DIV4
LCALL RR1 
SJMP DIV3
DIV4: CLR A 
XCH A,R0
PUSH ACC
CLR A
XCH A,R1
PUSH ACC
MOV A,R2
PUSH ACC
MOV B,#10H 
DIV5: CLR C
MOV A,R1
RLC A
MOV R1,A
MOV A,R0
RLC A
MOV R0,A
MOV A,R4
RLC A
MOV R4,A
XCH A,R3
RLC A
XCH A,R3
MOV F0,C
CLR C
SUBB A,R7
MOV R2,A
MOV A,R3
SUBB A,R6
ANL C,/F0
JC DIV6
MOV R3,A
MOV A,R2
MOV R4,A
INC R1
DIV6: DJNZ B,DIV5
MOV A,R6
CLR C
RRC A
SUBB A,R3
CLR A
ADDC A,R1 
MOV R4,A
CLR A
ADDC A,R0
MOV R3,A
POP ACC
MOV R2,A
POP ACC
MOV R1,A
POP ACC
MOV R0,A
MOV A,R2
CLR C
SUBB A,R5
LCALL MD 
LJMP RLN 
FMOV: INC R0
INC R0
INC R1
INC R1
MOV A,@R1
MOV @R0,A
DEC R0
DEC R1
MOV A,@R1
MOV @R0,A
DEC R0
DEC R1
MOV A,@R1
MOV @R0,A
RET
FCMP: MOV A,@R0 
XRL A,@R1
JNB ACC.7,CMP2
MOV A,@R0 
RLC A
MOV A,#0FFH
RET 
CMP2: MOV A,@R1 
MOV C,ACC.6
MOV ACC.7,C
MOV B,A
MOV A,@R0
MOV C,ACC.7
MOV F0,C 
MOV C,ACC.6
MOV ACC.7,C
CLR C 
SUBB A,B
JZ CMP6
RLC A 
JNB F0,CMP5
CPL C 
CMP5: MOV A,#0FFH 
RET 
CMP6: INC R0 
INC R0
INC R1
INC R1
CLR C
MOV A,@R0
SUBB A,@R1
MOV B,A 
DEC R0
DEC R1
MOV A,@R0
SUBB A,@R1
DEC R0
DEC R1
ORL A,B 
JZ CMP7
JNB F0,CMP7
CPL C 
CMP7: RET
FADD: CLR F0 
SJMP AS 
FSUB: SETB F0 
AS: LCALL MVR1 
MOV C,F0 
RRC A
XRL A,@R1
MOV C,ACC.7
ASN: MOV 1EH,C 
XRL A,@R0 
RLC A
MOV F0,C 
LCALL MVR0 
LCALL AS1 
MOV0: INC R0 
INC R0
MOV A,R4 
MOV @R0,A
DEC R0
MOV A,R3 
MOV @R0,A
DEC R0
MOV A,R2 
MOV C,1FH 
MOV ACC.7,C 
MOV @R0,A
CLR ACC.7 
CLR OV 
CJNE A,#3FH,MV01
SETB OV 
MV01: MOV A,@R0 
RET
MVR0: MOV A,@R0 
MOV C,ACC.7 
MOV 1FH,C
MOV C,ACC.6 
MOV ACC.7,C
MOV R2,A 
INC R0
MOV A,@R0 
MOV R3,A
INC R0
MOV A,@R0 
MOV R4,A
DEC R0 
DEC R0
RET
MVR1: MOV A,@R1 
MOV C,ACC.7 
MOV 1EH,C
MOV C,ACC.6 
MOV ACC.7,C
MOV R5,A 
INC R1
MOV A,@R1 
MOV R6,A
INC R1
MOV A,@R1 
MOV R7,A
DEC R1 
DEC R1
RET
AS1: MOV A,R6 
ORL A,R7
JZ AS2 
MOV A,R3 
ORL A,R4
JNZ EQ1
MOV A,R6 
MOV R3,A
MOV A,R7
MOV R4,A
MOV A,R5
MOV R2,A
MOV C,1EH
MOV 1FH,C
AS2: RET
EQ1: MOV A,R2 
XRL A,R5
JZ AS4 
JB ACC.7,EQ3
MOV A,R2 
CLR C
SUBB A,R5
JC EQ4
EQ2: CLR C 
MOV A,R6 
RRC A
MOV R6,A
MOV A,R7
RRC A
MOV R7,A
INC R5 
ORL A,R6 
JNZ EQ1 
MOV A,R2 
MOV R5,A
SJMP AS4
EQ3: MOV A,R2 
JNB ACC.7,EQ2
EQ4: CLR C
LCALL RR1 
ORL A,R3 
JNZ EQ1 
MOV A,R5 
MOV R2,A
AS4: JB F0,AS5 
MOV A,R4 
ADD A,R7
MOV R4,A
MOV A,R3 
ADDC A,R6
MOV R3,A
JNC AS2
LJMP RR1 
AS5: CLR C 
MOV A,R4
SUBB A,R7
MOV B,A
MOV A,R3
SUBB A,R6
JC AS6
MOV R4,B 
MOV R3,A
LJMP RLN 
AS6: CPL 1FH 
CLR C 
MOV A,R7
SUBB A,R4
MOV R4,A
MOV A,R6
SUBB A,R3
MOV R3,A
RLN: MOV A,R3 
ORL A,R4 
JNZ RLN1
MOV R2,#0C1H
RET 
RLN1: MOV A,R3
JB ACC.7,RLN2
CLR C 
LCALL RL1
SJMP RLN 
RLN2: CLR OV 
RET
RL1: MOV A,R4 
RLC A 
MOV R4,A
MOV A,R3
RLC A
MOV R3,A
DEC R2 
CJNE R2,#0C0H,RL1E
CLR A
MOV R3,A 
MOV R4,A
MOV R2,#0C1H
RL1E: CLR OV
RET
RR1: MOV A,R3 
RRC A 
MOV R3,A
MOV A,R4
RRC A
MOV R4,A
INC R2 
CLR OV 
CJNE R2,#40H,RR1E
MOV R2,#3FH 
SETB OV
RR1E: RET
DTOF: MOV R2,A ;；按整数的位数初始化阶码
MOV A,@R0 ;；将定点数作尾数
MOV R3,A
INC R0
MOV A,@R0
MOV R4,A
DEC R0
LCALL RLN ;；进行规格化
LJMP MOV0 ;；传送结果到[R0]中
FTOD: LCALL MVR0 ;；将[R0]传送到第一工作区
MOV A,R2
JZ FTD4 ;；阶码为零，纯小数
JB ACC.7,FTD4;；阶码为负，纯小数
SETB C
SUBB A,#10H
JC FTD1
SETB OV ;；阶码大于１６，溢出
RET
FTD1: SETB C
MOV A,R2
SUBB A,#8 ;；阶码大于８否？
JC FTD3
FTD2: MOV B,#10H ;；阶码大于８，按双字节整数转换
LCALL FTD8
SETB F0 ;；设立双字节整数标志
CLR C
CLR OV
RET
FTD3: MOV B,#8 ;；按一字节整数一字节小数转换
LCALL FTD8
SETB C ;；设立一字节整数一字节小数标志
CLR F0
CLR OV
RET
FTD4: MOV B,#0 ;；按纯小数转换
LCALL FTD8
CLR OV ;；设立纯小数标志
CLR F0
CLR C
RET
FTD8: MOV A,R2 ;；按规定的整数位数进行右规
CJNE A,B,FTD9
MOV A,R3 ;；将双字节结果传送到[R0]中
MOV @R0,A
INC R0
MOV A,R4
MOV @R0,A
DEC R0
RET 
FTD9: CLR C
LCALL RR1 ;；右规一次
SJMP FTD8
FINT: LCALL MVR0 
LCALL INT 
LJMP MOV0 
INT: MOV A,R3
ORL A,R4
JNZ INTA
CLR 1FH 
MOV R2,#41H
RET 
INTA: MOV A,R2
JZ INTB
JB ACC.7,INTB
CLR C
SUBB A,#10H
JC INTD
RET 
INTB: CLR A
MOV R4,A
MOV C,1FH
RRC A
MOV R3,A
RL A
MOV R2,A
JNZ INTC
MOV R2,#41H
INTC: RET
INTD: CLR F0
INTE: CLR C
LCALL RR1 
ORL C,F0
MOV F0,C
CJNE R2,#10H,INTE
JNB F0,INTF 
JNB 1FH,INTF
INC R4 
MOV A,R4
JNZ INTF
INC R3
INTF: LJMP RLN 
;eeprom_ctrl
;********************
rdee:
                call star_ee
        ;*************************      
                mov a,dph
        ;**************************2001.7.17
                rl a
                orl a,#slaw                     
        ;**************************2001.7.17
                call w1bt
                call cack
                jb f0,rdee_end
                mov a,dpl
                call w1bt
                call cack
                jb f0,rdee_end
                call star_ee
        ;*************************      
                mov a,dph
        ;**************************2001.7.17
                rl a
                orl a,#slar                     
        ;**************************2001.7.17
                call w1bt
                call cack
                jb f0,rdee_end
                call r1bt
                ;call mack
                call mnack
                call stop_ee
        ;***********************2001.7.22       
                clr ee_f
                ret
rdee_end:
                setb ee_f
                ;sjmp rdee
                ret

star_ee:
                setb sda
                setb scl
                nop
                nop
                clr  sda
                nop
                nop
                clr  scl
                ret
stop_ee:
                clr  sda
                setb scl
                nop
                nop
                setb sda
                ret
mack:
                clr  sda
                setb scl
                nop
                nop
                clr  scl
                setb sda
                ret
mnack:
                setb sda
                setb scl
                nop
                nop
                clr  scl
                clr  sda
                ret
cack:
                setb sda
                setb scl
                nop
                nop
                clr f0
                jnb sda,cend
                setb f0
        cend:
                clr scl
                ret
w1bt:
                mov r7,#08d
        wlp:
                rlc a
                jc wr1
        wr0:
                clr sda
                setb scl
                nop
                nop
                clr scl;********
                jmp wlp1
        wr1:
                setb sda
                setb scl
                nop
                nop
                clr scl
                clr sda
        wlp1:
                nop
                djnz r7,wlp
                ret
r1bt:
                mov r7,#08d
        rlp:
                setb sda
                setb scl
                nop
                nop
                jnb sda ,rd0
        rd1:
                setb c
                rlc a
                clr scl
                jmp rlp1
        rd0:
                clr c
                rlc a
                clr scl
        rlp1:
                nop
                djnz r7,rlp
                ret
wree:
                call star_ee
        ;*************************      
                mov a,dph
        ;**************************2001.7.17
                rl a
                orl a,#slaw                     
        ;**************************2001.7.17
                call w1bt
                call cack
                jb f0,wree_end
                mov a,dpl
                call w1bt
                call cack
                jb f0,wree_end
                mov a,r4
                call w1bt
                call cack
                jb f0,wree_end
                call stop_ee                                                            
         	call timer_20ms
                clr ee_f
                ret
wree_end:
                setb ee_f       
                ret
read_int:
		mov r7,#menu_no
		mov dptr,#int_asc
		mov r0,#dt1_dat
	   read1:     
		clr a
		movc a,@a+dptr
		mov @r0,a
		inc r0
		inc dptr
		djnz r7,read1
		mov r7,#14
		mov r0,#fo1
	df1:
		push 07h
		call btof
		pop 07h
		inc r0
		inc r0
		inc r0
		djnz r7,df1             
		ret
int_asc:                
;** dt1_4;dt3=w_adj_1;dt4=frist; fd1_4;fh1,fh2=fd3,4 
	db 01,01,xu,frist_no,1,1,0,0;
;********* ch bps addres dp da del_t *********
	db 00,03,0,1,0,0
;*************** f0,k,b,c,l,h,fs ****************
	db 41h,00h,00h, 41h,00h,00h;ch1_fo=0

	db 7eh,40h,00h, 7eh,40h,00h;ch1_k=0.04

	;db 01h,40h,00h, 02h,40h,00h;ch1_b
	db 80h,40h,00h, 80h,40h,00h;ch1_b=-0.4
	
	db 41h,00h,00h, 41h,00h,00h;ch1_c=0
	db 02h,20h,00h, 02h,20h,00h;ch1_l=20 
	db 02h,80h,00h, 02h,80h,00h;ch1_h=80
	db 03h,10h,00h, 03h,10h,00h;ch1_fs=100   
	;  ch1           ch2       
;****************************************************
wr_int: 
		mov dptr,#dt1_dat_ee
		mov r2,#menu_no
		mov r0,#dt1_dat
		jmp clr_wk
;***************************************                
	clr_wk:
		call rdee
		xrl a,@r0
		jz wr_0
		mov a,@r0
		mov r4,a
		push 00h
		push 02h
		call wree
		pop 02h
		pop 00h
	wr_0:
		;mov a,r2
		;mov b,#5
		;div ab
		;mov a,b
		;jnz wr_11
		;push 02h
		;call led
		;pop 02h
	wr_11:	
		inc dptr
		inc r0
		djnz r2,clr_wk
		ret
;**********************************
read_ee:
		mov r2,#menu_no
		mov r0,#dt1_dat
		mov dptr,#dt1_dat_ee
	read_1:
		push 00h
		call rdee
		pop 00h
		mov @r0,a
		inc r0
		inc dptr
		jb ee_f ,read_ef1
		djnz r2,read_1          
		ret
read_ef1:
		call read_int
		call led_blk
		mov r3,#40
		mov led1,#0eh
		mov led2,#0eh
		mov led3,#2
		mov led4,#4
	read_ef2:
		call beep_del
		djnz r3,read_ef2
		ret
