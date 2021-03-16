;**************************************
;*          
;*      温度控制程序 w.asm            * 
;*
;*       作者：严天峰                 * 
;* 
;说明：测试程序在KEIL 6。23版本下通过 * 
;你可以无偿使用这些代码，但请标明出处 *
;*********以下为一些伪指令定义*********

;************************
; The code meets all ad7416 family timing requirements when executed by an
; AT89Cx051 microcontroller with a 6 MHz clock. Code modifications may be
; required if a faster clock is substituted.
FADDR           DATA   24H     ; fixed address for Ad7416
zdata           DATA   28H      ; data register
address  DATA   29h      ; low address register
;addr_hi         DATA   2Ah      ; high address register

;
;*******Microcontroller connections to aad7416 OR  AT24C02 serial bus lines.
SCL             EQU    P3.4   ; serial clock
SDA             EQU    P3.5   ; serial data
;******************ad7416 presodo************************


WD_H_KEY  EQU P1.6;
WD_L_KEY  EQU P1.7
H_KEY  EQU P3.2
JDQ    EQU P1.5
H_DATA DATA 50H   ; H_DATA 存放温度报警上限
L_DATA DATA 51H   ; L_DATA 存放温度报警上限
W_DATA DATA 52H
M_DATA DATA 53H
S_H_DATA    DATA 59H
S_L_DATA    DATA 5AH
;M_H    DATA 6BH
;M_L    DATA 6CH
ORG  0000H
AJMP MAIN
ORG 000BH
AJMP TIME_T0
ORG 0040H
TIME_T0:push acc
CLR TR0
MOV TH0,#0
MOV TL0,#0
INC 5FH
MOV A,5FH
XRL A,#20
JZ CLEAR0
RET_T0:
SETB TR0
pop acc
RETI
CLEAR0:
    mov 5fh,#0
    MOV A,W_DATA
;    MOV BCD_DATA,A     
    LCALL HEX_BCD      
    MOV 69H,R5
    MOV 6AH,R6
    MOV 6BH,R7
MOV 6EH,#00h
MOV 6DH,#00h
MOV 6CH,#00h
    AJMP  RET_T0
 
    ORG 0100H
;****************主程序开始*****************
MAIN:MOV SP,#70H
MOV TMOD,#01H
MOV TH0,#0
MOV TL0,#0
CLR ET0
CLR TR0
MOV 6EH,#00h
MOV 6DH,#00h
MOV 6CH,#00h
MOV 6BH,#00h
MOV 6AH,#00h
MOV 69H,#00h
MOV 5FH,#00h  ;5FH存放100MS 单元
MOV H_DATA,#0
MOV L_DATA,#0
;MOV S_H_DATA,#0
;MOV S_L_DATA,#0
MOV W_DATA,#0
;
MOV DPTR,#0FB00H
MOV A,#03H
MOVX @DPTR,A
;
;********read at24c02 from address 00h,01h
;  FADDR SET 90H
  MOV FADDR,#0A0H
  mov address,#00h
;  mov addr_hi,#00h
  mov a,#00h
  lcall rd_rand
  MOV S_H_DATA,A
  
 
  mov address,#01h
;  mov addr_hi,#00h
  mov a,#00h
  lcall rd_rand
  MOV S_L_DATA,A
 
;  FADDR SET 91H
 ;
SETB EA
SETB ET0
SETB TR0
 START_1:
     
    LCALL AD7416     ;call temperature sub _program
;    MOV H_DATA, R7
;    MOV L_DATA, R6
    MOV R0,L_DATA
    MOV R1,H_DATA 
    LCALL DIV25
    MOV W_DATA,R4
;    MOV A,W_DATA
;    MOV BCD_DATA,A     
;    LCALL HEX_BCD      
;    MOV 69H,R5
;    MOV 6AH,R6
;    MOV 6BH,R7
;
;   MOV A,S_DATA
;   LCALL HEX_BCD
;   MOV 69H,A
;    MOV 6AH,B
;;
;    MOV A,M_DATA
;    LCALL HEX_BCD
;    MOV 6BH,A
;    MOV 6CH,B
;    
;    MOV A,H_DATA;
; ;   LCALL HEX_BCD
;    MOV 6DH,A
;    MOV 6EH,B
;
LCALL DIS
LCALL KEY
;  MOV FADDR,#0A0H

;mov address,#00h
 ; mov addr_hi,#00h
;  mov a,#00h
;  MOV ZDATA,S_H_DATA
;  lcall wr_byte

;  mov address,#01h
;  mov a,#00h
;  MOV ZDATA,S_L_DATA
;  lcall wr_byte
;  LCALL CONTROL
  AJMP START_1

;***********显示子程序*****************
DIS:PUSH ACC
MOV DPTR,#0FB00H
MOV A,#03H
MOVX @DPTR,A
YLED:MOV R0,#6EH
MOV R3,#01H
MOV A,R3
YB:MOV DPTR,#0FB01H
MOVX @DPTR,A
INC DPTR
MOV A,@R0
ADD A,#11H
MOVC A,@A+PC
MOVX @DPTR,A
LCALL DELL
DEC R0
MOV A,R3
JB ACC.5,EEND
RL A
MOV R3,A
SJMP YB
NOP
NOP
EEND:AJMP S_END
BD: DB 3FH,06H,5BH,4FH,66H,6DH
BD1: DB 7DH,07H,7FH,6FH,77H,7CH
BD2: DB 39H,5EH,79H,71H,73H,3EH
BD3: DB 31H,6EH,1CH,23H,40H,03H
S_END:POP ACC
RET
;**********end display*********************

;***********delay program******************
DELL:MOV R7,#04H
DEL:MOV R6,#0E7H
NN:DJNZ R6,NN
DJNZ R7,DEL
RET
;******************************************   

;***************key（按键） program *******
KEY:
    clr  tr0
    JB WD_H_KEY,L_SET
    LCALL DELL
    JB WD_H_KEY,L_SET
    INC S_H_DATA
    MOV A,S_H_DATA
    CJNE A,#7FH,S_DIS
    MOV S_H_DATA,#00H
S_DIS:
    
    MOV A,S_H_DATA
    LCALL HEX_BCD      
    MOV 69H,R5
    MOV 6aH,R6
    MOV 6BH,R7
;    MOV A,S_H_DATA
;    LCALL HEX_BCD
;    MOV 69H,A
;    MOV 6AH,B
MOV FADDR,#0A0H  
 mov address,#00h
 ; mov addr_hi,#00h
  mov a,#00h
  MOV ZDATA,S_H_DATA
  lcall wr_byte
S_REP:LCALL DIS
    JNB WD_H_KEY,S_REP
;
L_SET:
    JB WD_L_KEY,SET_END
    LCALL DELL
    JB WD_L_KEY,SET_END
    INC S_L_DATA
    MOV A,S_L_DATA
    CJNE A,#7FH,M_DIS
    MOV S_L_DATA,#00H
M_DIS:
    MOV A,S_L_DATA
    LCALL HEX_BCD
    MOV 6cH,R5
    MOV 6dH,R6
    MOV 6eH,R7

  MOV FADDR,#0A0H
  mov address,#01h
 ; mov addr_hi,#00h
  mov a,#00h
  MOV ZDATA,S_L_DATA
  lcall wr_byte
;    MOV 6BH,A
;    MOV 6CH,B
M_REP:LCALL DIS
     JNB WD_L_KEY,M_REP
;
;H_SET:
;    JB H_KEY,SET_END
;    LCALL DELL
;    JB H_KEY,SET_END
;    INC H_DATA
;    MOV A,H_DATA
;    CJNE A,#60,H_DIS
;    MOV H_DATA,#00H
;H_DIS:MOV A,H_DATA
;    LCALL HEX_BCD
;    MOV 6DH,A
;    MOV 6EH,B
;H_REP:LCALL DIS
;    JNB H_KEY,H_REP
;
SET_END:setb  tr0
RET
;***********key（按键） program 结束***

;*****************CONTROL JDQ*********
CONTROL:
    MOV A,W_DATA
    CJNE A,S_H_DATA,COMPARE1
OPEN1:CLR JDQ
    AJMP CON_END
COMPARE1:
    JNC  OPEN1
    MOV A,W_DATA 
    CJNE A,S_L_DATA,COMPARE2
OPEN2:CLR JDQ
    AJMP CON_END
COMPARE2:
    JC OPEN2
    SETB JDQ
CON_END:RET
RET    
;***********CONTROL JDQ END*************8      

;
;************HEX_BCD 转换子程序**********
;IN ACC, OUT :R5 R6 R7
HEX_BCD:MOV B,#10
        DIV AB
        MOV R5,B
;       MOV A,B
        MOV B,#10
        DIV AB
        MOV R6,B
        MOV R7,A
        RET 
;**********ad7416 samping************
ad7416:     
    MOV FADDR,#090H
                mov address,#00h
        ii:     mov a,#01h      ;logcal address 
                lcall rd_rand
                CLR C
                RLC A
                MOV 20H.1,C
		RLC A
                MOV 20H.0,C 
;                mov 4dh,a
;                MOV 20H.1,C      
;                clr c         
;                RLC A
;                MOV 20h.0,C
                anl a,#11111100b
                mov L_DATA,A
;                MOV 20H.0,C
;                MOV C,F0
;                MOV ACC.1,C
                MOV A,20H 
                ANL A,#00000011B
                MOV H_DATA,A                
; ret
                
;                MOV ADDr_lo,#0                  
;                mov address,#00h　;;  Ad7416　温度寄存器地址为０1Ｈ
;                 mov a,#00h 
;                lcall rd_rand
;                mov a,r6
;                anl a,#00111111b
;                rl a
;                rl a
;                mov b,a
;                mov a,r7
;                rl a
;                rl a
;                mov r7,a
;                mov a,b
;                orl a,r7
;                mov r6,a  
;                mov a,b
;                anl a,#00000011b
;                mov r7,a            ;r7放置AD7416温度值高2位,r6放置低8位
;                CLR C
ret
;
wr_byte:NOP
;        ; AT24Cxx Byte Write function.
;        ; Called with programmable address in A, byte address in
;        ; register pair ADDR_HI:ADDR_LO, data in register XDATA.
;        ; Does not wait for write cycle to complete.
;        ; Returns CY set to indicate that the bus is not available
;        ; or that the addressed device failed to acknowledge.
;        ; Destroys A.
                LCALL    start
		jc	x49		; abort if bus not available
		rl	a		; programmable address to bits 3:1
		orl	a, FADDR	; add fixed address
		clr	acc.0		; specify write operation
                LCALL    shout           ; send device address
		jc	x48		; abort if no acknowledge
;                mov     a, addr_hi      ; send high byte of address
;                LCALL    shout           ;
;                jc      x48             ; abort if no acknowledge
;
		mov	a, address	; send low byte of address
                LCALL    shout           ;
		jc	x48		; abort if no acknowledge
;
		mov	a, zdata	; get data
                LCALL    shout           ; send data
		jc	x48		; abort if no acknowledge
;
		clr	c		; clear error flag
        x48:    LCALL    stop
        x49:    ret
;

rd_curr:NOP
;
;        ; AT24Cxx Current Address Read function.
;        ; Called with programmable address in A. Returns data in A.
;        ; Returns CY set to indicate that the bus is not available
;        ; or that the addressed device failed to acknowledge.
;
                LCALL    start
		jc	x45		; abort if bus not available
;
		rl	a		; programmable address to bits 3:1
		orl	a, FADDR	; add fixed address
		setb	acc.0		; specify read operation
                LCALL    shout           ; send device address
		jc	x44		; abort if no acknowledge
;
                LCALL    shin            ; receive data byte
                LCALL    NAK             ; do not acknowledge byte
		clr	c		; clear error flag
        x44:    LCALL    stop
        x45:    ret
;
rd_rand:NOP
;                 AT24Cxx Random Read function.
;                 Called with programmable address in A, byte address in
;                 register pair ADDR_HI:ADDR_LO. Returns data in A.
;                 Returns CY set to indicate that the bus is not available
;                 or that the addressed device failed to acknowledge.
;
		push	b
		mov	b, a		; save copy of programmable address
;
;                          Send dummy write command to set internal address.
;
                LCALL    start
		jc	x47		; abort if bus not available
;
		rl	a		; programmable address to bits 3:1
		orl	a, FADDR	; add fixed address
		clr	acc.0		; specify write operation
                LCALL    shout           ; send device address
		jc	x46		; abort if no acknowledge
;
 		mov	a, address	; send low byte of address
                LCALL    shout           ;
		jc	x46		; abort if no acknowledge
;
;                ; Call Current Address Read function.
;
		mov	a, b		; get programmable address
                LCALL    rd_curr
                Ljmp     x47             ; exit
        x46:    LCALL    stop
        x47:    pop     b
		ret
;
start:NOP
; Send START, defined as high-to-low SDA with SCL high.
; Return with SCL, SDA low.
; Returns CY set if bus is not available.
;
		setb	SDA
		setb	SCL
;
; Verify bus available.
;
		jnb	SDA, x40	; jump if not high
		jnb	SCL, x40	; jump if not high
;
		nop			; enforce setup delay and cycle delay
		clr	SDA
		nop			; enforce hold delay
		nop			;
;		nop			;
;		nop			;;
;		nop			;
		clr	SCL
;
		clr	c		; clear error flag
                Ljmp     x41
        x40:    setb    c               ; set error flag
        x41:    ret
;
;
stop: NOP
;
;        ; Send STOP, defined as low-to-high SDA with SCL high.
;        ; SCL expected low on entry. Return with SCL, SDA high.
;
		clr	SDA
		nop			; enforce SCL low and data setup
		nop
		setb	SCL
		nop			; enforce setup delay
		nop			;
;		nop			;
;		nop			;
;		nop			;
		setb	SDA
		ret
;
;
shout:NOP
;
;        ; Shift out a byte to the AT24Cxx, most significant bit first.
;        ; SCL, SDA expected low on entry. Return with SCL low.
;        ; Called with data to send in A.
;        ; Returns CY set to indicate failure by slave to acknowledge.
;        ; Destroys A.
;
		push	b
		mov	b, #8		; bit counter
        x42:    NOP
		rlc	a		; move bit into CY
		mov	SDA, c		; output bit
		nop			; enforce SCL low and data setup
		setb	SCL		; raise clock
		nop			; enforce SCL high
		nop			;
;		nop			;
;		nop			;
		clr	SCL		; drop clock
		djnz	b, x42		; next bit
;
		setb	SDA		; release SDA for ACK
		nop			; enforce SCL low and tAA
		nop			;
		setb	SCL		; raise ACK clock
		nop			; enforce SCL high
		nop			;
;		nop			;
;		nop			;
		mov	c, SDA		; get ACK bit
		clr	SCL		; drop ACK clock
;
		pop	b
		ret
;
;
shin:NOP
;
;        ; Shift in a byte from the AT24Cxx, most significant bit first.
;        ; SCL expected low on entry. Return with SCL low.
;        ; Returns received data byte in A.
;
		setb	SDA		; make SDA an input
;
		push	b
		mov	b, #8		; bit count
        x43:    nop                     ; enforce SCL low and data setup
		nop			;
;		nop			;
		setb	SCL		; raise clock
		nop			; enforce SCL high
		nop			;
		mov	c, SDA		; input bit
		rlc	a		; move bit into byte
		clr	SCL		; drop clock
		djnz	b, x43		; next bit
;
		pop	b
		ret
;
NAK: NOP
;        ; Clock out a negative acknowledge bit (high).
;        ; SCL expected low on entry. Return with SCL low, SDA high.
		setb	SDA		; NAK bit
		nop			; enforce SCL low and data setup
		nop			;
		setb	SCL		; raise clock
		nop			; enforce SCL high
		nop			;
;		nop			;
;		nop			;
		clr	SCL		; drop clock
		ret
;


;**************div4 subprogram***********
;DIVEND in r0,r1,DIVSOR 4,out r5,r4,
dIV25:NOP      ;TDATA DATA 25
    MOV R3, #4
    MOV R2,#00H
    MOV R4,#00H
    MOV R5,#00H
    MOV R7,#10H
CHU55:MOV A,R0
    ADD A,R0
    MOV R0,A
    MOV A,R1
    ADDC A,R1
    MOV R1,A
    MOV A,R2
    ADDC A,R2
    MOV R2,A
    MOV A,R4
    ADD A,R4
    MOV R4,A
    MOV A,R5
    ADDC A,R5
    MOV R5,A
    CJNE R2,#4,LOOP05
LOOP05:JC LOOP15
     MOV A,R2
     SUBB A,R3
     MOV R2,A
     MOV A,R4
     ADD A,#01H
     MOV R4,A
     MOV A,R5
     ADDC A,#00H
     MOV R5,A
LOOP15:DJNZ R7,CHU55
      RET
;;**************************

;************结束 OK ********** *******
END        
;**********-----所有程序结束----*****


