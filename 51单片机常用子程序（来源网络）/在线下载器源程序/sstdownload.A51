;sst89c58下载器，使用keilc51的debug调试器下载。
;将本程序编译后写入sst89c58，并编程为remap 4kbytes。该芯片即有了keil环境下载功能。
;当p1.0拉低时，启动时进入下载程序，进入下载程序后将会自动删除block0。p1.0高电平时进入用户程序。
;进入下载程序后，可以通过串口和keil的仿真环境连通，波特率自动调节。
;选择load HEX文件，即可将程序下载到sst89c58的低端32keeprom中。除了7e00-7fffh被占用了。
;程序编写：丁丁 2000.12.26
;个人主页：http://www.mcu51.com
        sfcf data 0b1h
	sfcm data 0b2h	
	sfal data 0b3h
	sfah data 0b4h
	sfdt data 0b5h
	sfst data 0b6h

        ORG    0F000H
	ljmp disremap ;千万不要删除这句看似没用的程序，至于为什么就想想吧。
disremap:mov sfcf,#11000000b ;disable remap
	
	;jb p1.0,user  ;在这里设置你要用来控制进入iap的管脚

	clr p3.1  ;led指示正在擦除
	lcall clearuser
	 setb p3.1
	ljmp LF026;main
user:   ljmp 0000h
writebyte:  	push acc ;这个子程序是用来写一个eeprom字节的，如果你仅仅是用来iap，也可以将它简化，后面那一大段就可以删了。
		push psw
		push dph
		push dpl
		push b
		push 02h
		push 00h
		push acc    ;保存要写入的数据
		CLR    A   ;测试是否为空0ffh
            	MOVC   A, @A+DPTR
		inc a
		jnz clear_save
w_b_:	pop acc	;如果该位置是空的就直接写入，不用擦除
w1byte:	mov sfah,dph
	mov sfal,dpl
	mov sfdt,a
	mov sfcm,#0eh
t_over:	mov a,sfst
	jb acc.2,T_over
	ajmp endend

clear_save: 	;清除用来暂时保存的rom
		mov sfah,#7fh  
		mov sfal,#00h
		mov sfcm,#0bh
t_c7f_over:	mov a,sfst
		jb acc.2,t_c7f_over 

		;将高端内存搬到暂时保存rom
		mov r2,#00h ;将高端ram搬到7f00rom
		mov r0,#80h ;指向高端ram
t_w1_next:	mov sfah,#7fh
		mov sfal,r2
		mov sfdt,@r0
		mov sfcm,#06h   ;burst write
t_w1_over:	mov a,sfst			
		jb acc.3,t_w1_over
		inc r2
		inc r0
		cjne r0,#0c0h,t_w1_n1 ;write 64
t_w1_over1:	mov a,sfst
		jb acc.2,t_w1_over1
		ajmp t_w1_next
t_w1_n1:	cjne r0,#00h,t_w1_next
t_w1_over2:	mov a,sfst
		jb acc.2,t_w1_over2


		;将被写字节所在扇搬到高端内存
		mov b,dpl  ;save dpl当前字节所在地低端位置b 
		anl dpl,#80h
		mov r0,#80h
save_w0:	clr a
		movc a,@a+dptr
		mov @r0,a
		inc r0
		inc dpl
		cjne r0,#00h,save_w0
		
		;写入当前字节到高端内存
		mov a,b
		orl a,#80h
		mov r0,a
		pop acc
		mov @r0,a

		;擦除原位置扇区
		mov sfah,dph
		mov sfal,b
		mov sfcm,#0bh
t_w1_c1:	mov a,sfst
		jb acc.2,t_w1_c1
		
		
		;将高端内存搬到原位置扇区
		anl b,#80h
		mov r0,#80h ;指向高端ram
t1_w1_next:	mov sfah,dph
		mov sfal,b
		mov sfdt,@r0
		mov sfcm,#06h   ;burst write
t1_w1_over:	mov a,sfst			
		jb acc.3,t1_w1_over
		inc b
		inc r0
		cjne r0,#0c0h,t1_w1_n1 ;write 64
t1_w1_over1:	mov a,sfst
		jb acc.2,t1_w1_over1
		ajmp t1_w1_next
t1_w1_n1:	cjne r0,#00h,t1_w1_next
t1_w1_over2:	mov a,sfst
		jb acc.2,t1_w1_over2

		;将保存区的内容搬回到高端ram
		mov r0,#80h
		mov dptr,#7f00h
t_w1_b:		clr a
		movc a,@a+dptr
		mov @r0,a
		inc r0
		inc dpl
		cjne r0,#0,t_w1_b

endend:		pop 00h
		pop 02h
		pop b
		pop dpl
		pop dph
		pop psw
		pop acc
		ret


			org 0f200h  ;//////////////////////
LF200:  PUSH   DPL
        PUSH   DPH
        MOV    DPTR, #7E08H
        lcall writebyte
        MOV    A, PSW
        INC    DPTR
        lcall writebyte
        CLR    A
        MOV    PSW, A
        XCH    A, IE
        INC    DPTR
        lcall writebyte
        POP    ACC
        INC    DPTR
        lcall writebyte
        POP    ACC
        INC    DPTR
        lcall writebyte
        POP    ACC
        INC    DPTR
        lcall writebyte
        POP    ACC
        INC    DPTR
        lcall writebyte
        INC    DPTR
        CLR    A
        MOVC   A, @A+DPTR
        XCH    A, SP
        lcall writebyte
        MOV    A, B
        INC    DPTR
        lcall writebyte
        MOV    A, R0
        INC    DPTR
        lcall writebyte
        MOV    R0, #00H
LF232:  INC    R0
        INC    DPTR
        CLR    A
        MOVC   A, @A+DPTR
        XCH    A, @R0
        lcall writebyte
        MOV    A, R0
        CJNE   A, #6FH, LF232
        LCALL  LF0AF
        LCALL  LF2A0
        LCALL  LFBD0
        LCALL  LFAD4
        LCALL  LF9EC
        LCALL  LF9EC
        LCALL  LF9EC
LF251:  LCALL  LFAD4
        MOV    DPTR, #7E0DH
        MOV    A, R0
        lcall writebyte
        INC    DPTR
        MOV    A, R1
        lcall writebyte
        LCALL  LF0A2
        RET    
LF260:  MOV    R2, #01H
LF262:  LCALL  LFBD0
        MOV    R6, 01H
        MOV    R5, 00H
LF269:  LCALL  LFB0C
        CJNE   A, #01H, LF29B
        PUSH   DPH
        PUSH   DPL
        LCALL  LFACA
        CLR    C
        MOV    A, R6
        SUBB   A, R1
        MOV    R4, A
        MOV    A, R5
        SUBB   A, R0
        JNZ    LF28A
        CJNE   R4, #02H, LF281
LF281:  JNC    LF28A
        MOV    28H, #08H
        MOV    A, #01H
        SJMP   LF296
LF28A:  MOV    A, #12H
        LCALL  LFADF
        MOV    A, #0F1H
        LCALL  LFADF
        MOV    A, #03H
LF296:  POP    DPL
        POP    DPH
        lcall writebyte
LF29B:  INC    R2
        CJNE   R2, #0CH, LF269
        RET    
LF2A0:  MOV    R2, #0BH
LF2A2:  LCALL  LFB0C
        CJNE   A, #03H, LF2B4
        MOV    A, #01H
        lcall writebyte
        LCALL  LFACA
        LCALL  LFADD
        LCALL  LFADD
LF2B4:  DJNZ   R2, LF2A2
LF2B6:  MOV    A, #81H
LF2B8:  SETB   10H
        MOV    R0, A
        SJMP   LF2C1
LF2BD:  MOV    R0, #81H
LF2BF:  CLR    10H
LF2C1:  MOV    DPTR, #7E08H
        CJNE   R0, #0E0H, LF2C9
        SJMP   LF2ED
LF2C9:  INC    DPTR
        CJNE   R0, #0D0H, LF2CF
        SJMP   LF2ED
LF2CF:  INC    DPTR
        CJNE   R0, #0A8H, LF2D5
        SJMP   LF2ED
LF2D5:  INC    DPTR
        CJNE   R0, #83H, LF2DB
        SJMP   LF2ED
LF2DB:  INC    DPTR
        CJNE   R0, #82H, LF2E1
        SJMP   LF2ED
LF2E1:  MOV    DPTR, #7E0FH
        CJNE   R0, #81H, LF2E9
        SJMP   LF2ED
LF2E9:  INC    DPTR
        CJNE   R0, #0F0H, LF2F5
LF2ED:  JB     10H, LF2F2
        lcall writebyte
        RET    
LF2F2:  CLR    A
        MOVC   A, @A+DPTR
        RET    
LF2F5:  MOV    R1, #0E5H
        JB     10H, LF2FC
        MOV    R1, #88H
LF2FC:  PUSH   ACC
        MOV    DPTR, #7EC3H
        MOV    A, R1
        LCALL  LF8F4
        MOV    R1, DPL
        MOV    A, DPH
        XCH    A, R0
        INC    DPTR
        LCALL  LFAF0
        MOV    A, #22H
        LCALL  LFAF0
        MOV    DPL, R1
        MOV    DPH, R0
        CLR    A
        POP    00H
        JMP    @A+DPTR
LF31B:  MOV    A, #0E0H
        LCALL  LF2B8
        MOV    DPL, 2CH    ;///????????
        MOV    DPH, 2BH
        MOVC   A, @A+DPTR
        MOV    R0, #0E0H
        LJMP   LF2BF
LF32C:  LCALL  LF2B6
        PUSH   06H
        MOV    R1, A
        MOV    A, 2CH
        LCALL  LF918
        MOV    A, 2BH
        LCALL  LF918
        MOV    A, R1
        POP    06H
        LJMP   LF2BD
Lf342:			;f342h  data area
        db 01h,06h;AJMP   LF006
        db 0fh;INC    R7
        db 01h,01h;AJMP   0F001H
        db 02h,01h,01h;LJMP   0101H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 23h;RL     A
        db 0ah;INC    R2
        db 13h;RRC    A
        db 01h,01h;AJMP   0F001H
        db 02h,01h,01h;LJMP   0101H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 23h;RL     A
        db 06h;INC    @R0
        db 15h,01h;DEC    01H
        db 02h,02h,01h;LJMP   0201H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 01h,23h;AJMP   LF023
        db 0ah;INC    R2
        db 19h;DEC    R1
        db 01h,02h;AJMP   0F002H
        db 02h,01h,01h;LJMP   0101H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 1eh;DEC    R6
        db 06h;INC    @R0
        db 02h,03h,02h;LJMP   0302H
        db 02h,01h,01h;LJMP   0101H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 1eh;DEC    R6
        db 0ah;INC    R2
        db 02h,03h,02h;LJMP   0302H
        db 02h,01h,01h;LJMP   0101H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 1eh;DEC    R6
        db 06h;INC    @R0
        db 02h,03h,02h;LJMP   0302H
        db 02h,01h,01h;LJMP   0101H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 1eh;DEC    R6
        db 0ah;INC    R2
        db 02h,29h,02h;LJMP   2902H
        db 03h;RR     A
        db 02h,02h,02h;LJMP   0202H
        db 02h,02h,02h;LJMP   0202H
        db 02h,02h,02h;LJMP   0202H
        db 02h,1eh,06h;LJMP   1E06H
        db 02h,25h,01h;LJMP   2501H
        db 03h;RR     A
        db 02h,02h,02h;LJMP   0202H
        db 02h,02h,02h;LJMP   0202H
        db 02h,02h,02h;LJMP   0202H
        db 02h,03h,0ah;LJMP   030AH
        db 02h,01h,02h;LJMP   0102H
        db 02h,01h,01h;LJMP   0101H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 02h,06h,02h;LJMP   0602H
        db 01h,01h;AJMP   0F001H
        db 01h,02h;AJMP   0F002H
        db 02h,02h,02h;LJMP   0202H
        db 02h,02h,02h;LJMP   0202H
        db 02h,02h,02h;LJMP   0202H
        db 02h,0ah,02h;LJMP   0A02H
        db 01h,23h;AJMP   LF023
        db 23h;RL     A
        db 23h;RL     A
        db 23h;RL     A
        db 23h;RL     A
        db 23h;RL     A
        db 23h;RL     A
        db 23h;RL     A
        db 23h;RL     A
        db 23h;RL     A
        db 23h;RL     A
        db 23h;RL     A
        db 02h,06h,02h;LJMP   0602H
        db 01h,01h;AJMP   0F001H
        db 02h,01h,01h;LJMP   0101H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 02h,0ah,02h;LJMP   0A02H
        db 01h,01h;AJMP   0F001H
        db 23h;RL     A
        db 01h,01h;AJMP   0F001H
        db 1eh;DEC    R6
        db 1eh;DEC    R6
        db 1eh;DEC    R6
        db 1eh;DEC    R6
        db 1eh;DEC    R6
        db 1eh;DEC    R6
        db 1eh;DEC    R6
        db 1eh;DEC    R6
        db 01h,06h;AJMP   LF006
        db 01h,01h;AJMP   0F001H
        db 01h,02h;AJMP   0F002H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 01h,0ah;AJMP   LF00A
        db 01h,01h;AJMP   0F001H
        db 01h,02h;AJMP   0F002H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
        db 01h,01h;AJMP   0F001H
Lf442: db 56h,33h,2eh,30h    ;,75h,81h,07h,90h,7eh,08h,0e4h,78h,05h				;f442h code area
Lf446: 	mov sp,#07h ;program start
	mov dptr,#7e08h
	clr a
	mov r0,#05h
LF44F:  lcall writebyte
        INC    DPTR
        DJNZ   R0, LF44F
        MOV    A, #00H
        lcall writebyte
        INC    DPTR
        MOV    A, #00H
        lcall writebyte
        INC    DPTR
        MOV    A, #07H
        lcall writebyte
        INC    DPTR
        CLR    A
        lcall writebyte
        MOV    23H, A
        INC    A
        MOV    24H, A
        MOV    DPTR, #7E00H
        MOV    R1, #00H
        MOV    R0, #0A5H
        LCALL  LF4C3
        MOV    R0, #33H
        LCALL  LF4C3
        MOV    R0, #0CCH
        LCALL  LF4C3
        MOV    A, R1
        JZ     LF48D
        MOV    R2, #0BH
        MOV    R5, #00H
        LCALL  LFB83
        CLR    A
        MOV    30H, A
        MOV    31H, A
        MOV    DPTR, #7E07H
        lcall writebyte
LF48D:  LCALL  LF2A0
LF490:  LCALL  LF890
        CJNE   A, #11H, LF4A0
        MOV    A, 23H
        LCALL  LF884
        CPL    A
        MOV    23H, A
        SJMP   LF490
LF4A0:  CJNE   A, #01H, LF4AA
        MOV    A, 24H
        LCALL  LF884
        SJMP   LF490
LF4AA:  LCALL  LF4AF
        SJMP   LF490
LF4AF:  MOV    25H, A
        DEC    A
        DEC    A
        ANL    A, #0EH
        MOV    DPTR, #Lf8c0
        MOV    R7, A
        MOVC   A, @A+DPTR
        XCH    A, R7
        INC    DPTR
        MOVC   A, @A+DPTR
        MOV    DPH, R7
        MOV    DPL, A
        CLR    A
        JMP    @A+DPTR
LF4C3:  CLR    A
        MOVC   A, @A+DPTR
        XRL    A, R0
        ORL    A, R1
        MOV    R1, A
        MOV    A, R0
        lcall writebyte
        INC    DPTR
        RET    
LF4CC:  MOV    A, #06H
        LCALL  LF884
        MOV    A, 28H
        LCALL  LF884
        MOV    DPTR, #7E03H
        MOV    R0, #04H
LF4DB:  CLR    A
        MOVC   A, @A+DPTR
        LCALL  LF884
        INC    DPTR
        DJNZ   R0, LF4DB
        MOV    A, #04H
        LCALL  LF884
        RET    
        MOV    28H, #00H
        LCALL  LF89C
        MOV    26H, A
        JZ     LF51A
        LCALL  LF89C
        MOV    DPH, A
        LCALL  LF89C
        MOV    DPL, A
        LCALL  LF89C
        MOV    27H, A
LF502:  LCALL  LF89C
        LCALL  LF8D0
        INC    DPTR
        DJNZ   27H, LF502
LF50C:  LCALL  LF89C
        MOV    A, 25H
        JZ     LF516
        MOV    28H, #02H
LF516:  LCALL  LF4CC
        RET    
LF51A:  LCALL  LF89C
        MOV    DPTR, #7E0DH
        lcall writebyte
        INC    DPTR
        LCALL  LF89C
        lcall writebyte
        LCALL  LF89C
        SJMP   LF50C
        MOV    28H, #00H
        LCALL  LF89C
        MOV    26H, A
        LCALL  LF89C
        MOV    DPH, A
        LCALL  LF89C
        MOV    DPL, A
        LCALL  LF89C
        MOV    27H, A
        LCALL  LF89C
        MOV    A, 25H
        JZ     LF550
        MOV    28H, #02H
LF54C:  LCALL  LF4CC
        RET    
LF550:  MOV    25H, #00H
        MOV    A, #02H
        LCALL  LF8B0
        MOV    A, 26H
        JZ     LF56E
LF55C:  LCALL  LF96B
        LCALL  LF8B0
        INC    DPTR
        DJNZ   27H, LF55C
LF566:  CLR    A
        CLR    C
        SUBB   A, 25H
        LCALL  LF8B0
        RET    
LF56E:  MOV    DPTR, #7E0DH
        CLR    A
        MOVC   A, @A+DPTR
        LCALL  LF8B0
        INC    DPTR
        CLR    A
        MOVC   A, @A+DPTR
        LCALL  LF8B0
        SJMP   LF566
        MOV    28H, #00H
        LCALL  LF89C
        MOV    29H, A
        LCALL  LF89C
        MOV    27H, A
        LCALL  LF89C
        MOV    26H, A
        LCALL  LF89C
        MOV    DPH, A
        LCALL  LF89C
        MOV    DPL, A
        LCALL  LF89C
        MOV    A, 25H
        JZ     LF5A8
        MOV    28H, #02H
        LCALL  LF4CC
        RET    
LF5A8:  CLR    A
        CJNE   A, 29H, LF5B2
        LCALL  LFB52
        LJMP   LF4CC
LF5B2:  INC    A
        CJNE   A, 29H, LF5BC
        LCALL  LFB76
        LJMP   LF4CC
LF5BC:  INC    A
        CJNE   A, 29H, LF5C6
        LCALL  LFB72
        LJMP   LF4CC
LF5C6:  INC    A
        CJNE   A, 29H, LF5D0
        LCALL  LFB7A
        LJMP   LF4CC
LF5D0:  LCALL  LFBA7
        LJMP   LF4CC
        MOV    28H, #00H
        LCALL  LF89C
        MOV    29H, A
        LCALL  LF89C
        MOV    27H, A
        LCALL  LF89C
        MOV    26H, A
        LCALL  LF89C
        MOV    DPH, A
        LCALL  LF89C
        MOV    DPL, A
        LCALL  LF89C
        MOV    R2, A
        LCALL  LF89C
        MOV    R0, A
        LCALL  LF89C
        MOV    R1, A
        LCALL  LF89C
        MOV    A, 25H
        JZ     LF60C
        MOV    28H, #02H
        LCALL  LF4CC
        RET    
LF60C:  CLR    A
        CJNE   A, 29H, LF61C
        LCALL  LFCC9
        LCALL  LF093
        JNC    LF61B
        LCALL  LF890
LF61B:  RET    
LF61C:  INC    A
        CJNE   A, 29H, LF623
        LJMP   LF643
LF623:  INC    A
        CJNE   A, 29H, LF62F
        CLR    11H
        LCALL  LFC8D
        LJMP   LF643
LF62F:  CLR    12H
        LCALL  LFC8B
        JB     12H, LF642
        LCALL  LF4CC
        LCALL  LF093
        JNC    LF642
        LCALL  LF890
LF642:  RET    
LF643:  MOV    25H, #00H
        MOV    A, #02H
        LCALL  LF8B0
        MOV    26H, #04H
        MOV    DPH, #00H
        MOV    DPL, #0E0H
        LCALL  LF96B
        LCALL  LF8B0
        MOV    DPL, #0F0H
        LCALL  LF96B
        LCALL  LF8B0
        MOV    DPL, #0D0H
        MOV    2AH, #08H
        LCALL  LF96B
        ANL    A, #18H
        MOV    DPL, A
LF670:  LCALL  LF96B
        LCALL  LF8B0
        INC    DPTR
        DJNZ   2AH, LF670
        MOV    DPL, #83H
        LCALL  LF96B
        LCALL  LF8B0
        MOV    DPL, #82H
        LCALL  LF96B
        LCALL  LF8B0
        MOV    DPTR, #7E0DH
        CLR    A
LF690:  MOVC   A, @A+DPTR
        LCALL  LF8B0
        INC    DPTR
        CLR    A
        MOVC   A, @A+DPTR
        LCALL  LF8B0
        MOV    DPL, #0D0H
        LCALL  LF96B
        LCALL  LF8B0
        CLR    A
        LCALL  LF8B0
        CLR    A
        LCALL  LF8B0
        CLR    A
        LCALL  LF8B0
        CLR    A
        LCALL  LF8B0
        MOV    DPL, #81H
        LCALL  LF96B
        MOV    DPL, A
        LCALL  LF8B0
        MOV    26H, #01H
LF6C1:  LCALL  LF96B
        LCALL  LF8B0
        DEC    DPL
        DJNZ   27H, LF6C1
        CLR    A
        CLR    C
        SUBB   A, 25H
        LCALL  LF8B0
        RET    
        MOV    28H, #00H
        LCALL  LF89C
        MOV    26H, A
        LCALL  LF89C
        MOV    DPH, A
        LCALL  LF89C
        MOV    DPL, A
        LCALL  LF89C
        INC    A
        MOV    29H, A
        LCALL  LF89C
        INC    A
        MOV    27H, A
        LCALL  LF89C
        MOV    2AH, A
        SJMP   LF6FF
LF6F9:  MOV    A, 2AH
        LCALL  LF8D0
        INC    DPTR
LF6FF:  DJNZ   27H, LF6F9
        DJNZ   29H, LF6F9
        LCALL  LF89C
        MOV    A, 25H
        JZ     LF70F
        MOV    28H, #02H
LF70F:  LCALL  LF4CC
        RET    
        MOV    28H, #00H
        LCALL  LF89C
        MOV    A, 25H
        JZ     LF724
        MOV    28H, #02H
        LCALL  LF4CC
        RET    
LF724:  CLR    11H
        LCALL  LFC8D
        MOV    DPTR, #7E0DH
        CLR    A
        MOVC   A, @A+DPTR
        MOV    R0, A
        INC    DPTR
        CLR    A
        MOVC   A, @A+DPTR
        MOV    R1, A
        MOV    DPTR, #7E03H
        MOV    A, R0
        lcall writebyte
        INC    DPTR
        MOV    A, R1
        lcall writebyte
        MOV    DPH, R0
        MOV    DPL, R1
        MOV    26H, #05H
        LCALL  LF96B
        MOV    DPTR, #7E05H
        lcall writebyte
        LCALL  LF4CC
        RET    
        MOV    28H, #00H
        LCALL  LF89C
        MOV    29H, A
        LCALL  LF89C
        MOV    27H, A
        LCALL  LF89C
        MOV    A, 25H
        JZ     LF767
        MOV    28H, #02H
        LJMP   LF4CC
LF767:  CLR    A
        CJNE   A, 29H, LF771
        ANL    24H, #0FBH
        LJMP   LF4CC
LF771:  INC    A
        CJNE   A, 29H, LF77B
        ORL    24H, #04H
        LJMP   LF4CC
LF77B:  INC    A
        CJNE   A, 29H, LF787
        CLR    A
        MOV    30H, A
        MOV    31H, A
        LJMP   LF4CC
LF787:  MOV    DPL, 30H
        MOV    A, 27H
        JZ     LF797
        CLR    C
        MOV    A, 30H
        SUBB   A, 27H
        MOV    DPL, A
        JNC    LF79E
LF797:  MOV    A, 31H
        JNZ    LF79E
        LJMP   LF4CC
LF79E:  MOV    25H, #00H
        MOV    A, #02H
        LCALL  LF8B0
        MOV    DPH, #6AH
        CLR    A
        MOVC   A, @A+DPTR
        LCALL  LF8B0
        INC    DPH
        CLR    A
        MOVC   A, @A+DPTR
        LCALL  LF8B0
        INC    DPH
        CLR    A
        MOVC   A, @A+DPTR
        LCALL  LF8B0
        INC    DPH
        CLR    A
        MOVC   A, @A+DPTR
        LCALL  LF8B0
        INC    DPH
        CLR    A
        MOVC   A, @A+DPTR
        LCALL  LF8B0
        INC    DPH
        CLR    A
        MOVC   A, @A+DPTR
        LCALL  LF8B0
        INC    DPH
        CLR    A
        MOVC   A, @A+DPTR
        LCALL  LF8B0
        INC    DPH
        CLR    A
        MOVC   A, @A+DPTR
        LCALL  LF8B0
        INC    DPH
        CLR    A
        MOVC   A, @A+DPTR
        LCALL  LF8B0
        INC    DPH
        CLR    A
        MOVC   A, @A+DPTR
        LCALL  LF8B0
        INC    DPH
        CLR    A
        MOVC   A, @A+DPTR
        LCALL  LF8B0
        INC    DPH
        CLR    A
        MOVC   A, @A+DPTR
        LCALL  LF8B0
        INC    DPH
        CLR    A
        MOVC   A, @A+DPTR
        LCALL  LF8B0
        INC    DPH
        CLR    A
        MOVC   A, @A+DPTR
        LCALL  LF8B0
        INC    DPH
        CLR    A
        MOVC   A, @A+DPTR
        LCALL  LF8B0
        INC    DPH
        CLR    A
        MOVC   A, @A+DPTR
        LCALL  LF8B0
        INC    DPH
        CLR    A
        MOVC   A, @A+DPTR
        LCALL  LF8B0
        INC    DPH
        CLR    A
        MOVC   A, @A+DPTR
        LCALL  LF8B0
        INC    DPH
        CLR    A
        MOVC   A, @A+DPTR
        LCALL  LF8B0
        INC    DPH
        CLR    A
        MOVC   A, @A+DPTR
        LCALL  LF8B0
        CLR    A
        CLR    C
        SUBB   A, 25H
        LCALL  LF8B0
        RET    
        MOV    28H, #00H
        LCALL  LF89C
        MOV    29H, A
        LCALL  LF89C
        MOV    A, 25H
        JZ     LF850
        MOV    28H, #02H
        LJMP   LF4CC
LF850:  CLR    A
        CJNE   A, 29H, LF85B
        MOV    DPTR, #7E07H
        lcall writebyte
        LJMP   LF4CC
LF85B:  INC    A
        CJNE   A, 29H, LF866
        MOV    DPTR, #7E07H
        lcall writebyte
        LJMP   LF4CC
LF866:  MOV    R0, #04H
        MOV    DPTR, #LF442
        MOV    R1, #02H
LF86D:  CLR    A
        MOVC   A, @A+DPTR
        MOV    @R1, A
        INC    DPTR
        INC    R1
        DJNZ   R0, LF86D
        MOV    R0, #04H
        MOV    DPTR, #7E03H
        MOV    R1, #02H
LF87B:  MOV    A, @R1
        lcall writebyte
        INC    DPTR
        INC    R1
        DJNZ   R0, LF87B
        LJMP   LF4CC
LF884:  LCALL  LF096
        JNC    LF884
        LCALL  LF09F
        LCALL  LF09C
        RET    
LF890:  LCALL  LF093
        JNC    LF890
        LCALL  LF099
        LCALL  LF0A5
        RET    
LF89C:  LCALL  LF093
        JNC    LF89C
        LCALL  LF099
        LCALL  LF0A5
        PUSH   ACC
        ADD    A, 25H
        MOV    25H, A
        POP    ACC
        RET    
LF8B0:  LCALL  LF096
        JNC    LF8B0
        LCALL  LF09F
        LCALL  LF09C
        ADD    A, 25H
        MOV    25H, A
        RET  

lf8c0: 	db 0f5h,017h,0f5h,05dh,0f5h,0b0h,0f6h,008h
	db 0f7h,006h,0f7h,045h,0f7h,085h,0f8h,073h;  data
	;db 0f4h,0e9h,0f5h,02bh,0f5h,07eh,0f5h,0d6h
	;db 0f6h,0d4h,0f7h,013h,0f7h,04dh,0f8h,03bh;  data		
				;;;end
LF8D0:  MOV    R7, 26H
        CJNE   R7, #01H, LF8D7
        SJMP   LF91D
LF8D7:  CJNE   R7, #02H, LF8DC
        SJMP   LF912
LF8DC:  CJNE   R7, #03H, LF8E1
        SJMP   LF914
LF8E1:  CJNE   R7, #04H, LF8E6
        SJMP   LF91D
LF8E6:  CJNE   R7, #05H, LF8EB
        SJMP   LF8F4
LF8EB:  CJNE   R7, #06H, LF8F0
        SJMP   LF950
LF8F0:  MOV    28H, #0FFH
        RET    
LF8F4:  LCALL  LF0B0
        MOV    R7, A
        CLR    A
        MOVC   A, @A+DPTR
        CJNE   A, 07H, LF8FE
        RET    
LF8FE:  MOV    A, 28H
        JNZ    LF911
        MOV    28H, #03H
        MOV    R0, DPL
        MOV    R1, DPH
        MOV    DPTR, #7E05H
        MOV    A, R1
        lcall writebyte
        INC    DPTR
        MOV    A, R0
        lcall writebyte
LF911:  RET    
LF912:  lcall writebyte
        RET    
LF914:  ;mov dph,P2
	lcall writebyte
	;MOV    R0, DPL
        ;MOVX   @R0, A      ;!!!!!!!
        RET    
LF918:  INC    R1
        MOV    DPL, R1
        MOV    R7, #01H
LF91D:  MOV    R6, A
        MOV    A, DPL
LF920:  CJNE   A, #70H, LF923
LF923:  JC     LF92C
        JB     ACC.7, LF93D
LF928:  MOV    R0, A
        MOV    A, R6
        MOV    @R0, A
        RET    
LF92C:  PUSH   DPL
        PUSH   DPH
        MOV    DPTR, #7E11H
        LCALL  LF9E2
        MOV    A, R6
        lcall writebyte
        POP    DPH
        POP    DPL
        RET    
LF93D:  CJNE   R7, #01H, LF942
        SJMP   LF928
LF942:  PUSH   DPL
        PUSH   DPH
        MOV    R0, A
        MOV    A, R6
        LCALL  LF2BF
        POP    DPH
        POP    DPL
        RET    
LF950:  RRC    A
        MOV    f0, C
        LCALL  LF9D2
        PUSH   ACC
        LCALL  LF99F
        INC    R6
        MOV    R7, 06H
LF95E:  RRC    A
        DJNZ   R7, LF95E
        MOV    C, F0
LF963:  RLC    A
        DJNZ   R6, LF963
        MOV    R6, A
        POP    ACC
        SJMP   LF920

LF96B:  MOV    R7, 26H
        CJNE   R7, #01H, LF972
        SJMP   LF99D
LF972:  CJNE   R7, #02H, LF977
        SJMP   LF992
LF977:  CJNE   R7, #03H, LF97C
        SJMP   LF994
LF97C:  CJNE   R7, #04H, LF981
        SJMP   LF99D
LF981:  CJNE   R7, #05H, LF986
        SJMP   LF98F
LF986:  CJNE   R7, #06H, LF98B
        SJMP   LF9C5
LF98B:  MOV    28H, #0FFH
        RET    
LF98F:  CLR    A
        MOVC   A, @A+DPTR
        RET    
LF992:  CLR    A
        MOVC   A, @A+DPTR
	;MOVX   A, @DPTR    ;!!!!!!
        RET     
LF994:  ;mov dph,P2	
	CLR    A
        MOVC   A, @A+DPTR
	;MOV    R0, DPL
        ;MOVX   A, @R0     ;!!!!!!
        RET    
LF998:  MOV    DPL, R1
        DEC    R1
        MOV    R7, #01H
LF99D:  MOV    A, DPL
LF99F:  CJNE   A, #70H, LF9A2
LF9A2:  JC     LF9AA
        JB     ACC.7, LF9B7
LF9A7:  MOV    R0, A
        MOV    A, @R0
        RET    
LF9AA:  PUSH   DPL
        PUSH   DPH
        MOV    DPTR, #7E11H
        MOVC   A, @A+DPTR
LF9B2:  POP    DPH
        POP    DPL
        RET    
LF9B7:  CJNE   R7, #01H, LF9BC
        SJMP   LF9A7
LF9BC:  PUSH   DPL
        PUSH   DPH
        LCALL  LF2B8
        SJMP   LF9B2
LF9C5:  LCALL  LF9D2
        LCALL  LF99F
        INC    R6
LF9CC:  RRC    A
        DJNZ   R6, LF9CC
        CLR    A
        RLC    A
        RET    
LF9D2:  MOV    A, DPL
        MOV    R6, A
        ANL    A, #07H
        XCH    A, R6
        XRL    A, R6
        JB     ACC.7, LF9E1
        RR     A
        RR     A
        RR     A
        ADD    A, #20H
LF9E1:  RET    
LF9E2:  ADD    A, DPL
        MOV    DPL, A
        CLR    A
        ADDC   A, DPH
        MOV    DPH, A
        RET    
LF9EC:  INC    DPL
        DJNZ   DPL, LF9F3
        DEC    DPH
LF9F3:  DEC    DPL
        RET    
LF9F6:  MOV    DPTR, #0023H ;?????????///
        CLR    A
        MOVC   A, @A+DPTR
        XRL    A, #02H
        JZ     LFA0A
        MOV    A, #02H
        LCALL  LF0B0
        CLR    A
        MOVC   A, @A+DPTR
        XRL    A, #02H
        JNZ    LFA3C
LFA0A:  INC    DPTR
        CLR    A
        MOVC   A, @A+DPTR
        XRL    A, #0FAH
        JZ     LFA22
        CLR    A
        MOVC   A, @A+DPTR
        XRL    A, #0FAH
        JZ     LFA22
        MOV    A, #0FAH
        LCALL  LF0B0
        CLR    A
        MOVC   A, @A+DPTR
        XRL    A, #0FAH
        JNZ    LFA3C
LFA22:  INC    DPTR
        CLR    A
        MOVC   A, @A+DPTR
        XRL    A, #99H
        JZ     LFA3A
        CLR    A
        MOVC   A, @A+DPTR
        XRL    A, #7CH
        JZ     LFA3A
        MOV    A, #99H
        LCALL  LF0B0
        CLR    A
        MOVC   A, @A+DPTR
        XRL    A, #99H
        JNZ    LFA3C
LFA3A:  CLR    C
        RET    
LFA3C:  SETB   C
        RET   
 
LFA3E:  LCALL  LF0A8
        LCALL  LF0A2
        MOV    A, SP
        ADD    A, #0FAH
        XCH    A, R0
        MOV    DPH, @R0
        INC    R0
        MOV    DPL, @R0
        INC    DPTR
        INC    DPTR
        INC    DPTR
        MOV    @R0, DPL
        DEC    R0
        MOV    @R0, DPH
        XCH    A, R0
        POP    PSW
        POP    DPH
        POP    DPL
        POP    ACC
        LCALL  LFA65
        LJMP   LF200
LFA65:  RETI 
  
LFA66:  LCALL  LF096
        JNC    LFA66
        LCALL  LF09F
        LCALL  LF0AB
        MOV    DPTR, #7E0AH
        CLR    A
        MOVC   A, @A+DPTR
        ORL    A, #80H
        ORL    A, IE
        lcall writebyte
        RET    

        PUSH   ACC
        PUSH   DPL
        PUSH   DPH
        PUSH   PSW
        MOV    PSW, #00H
        MOV    DPTR, #7E07H
        CLR    A
        MOVC   A, @A+DPTR
        JNZ    LFAA4
        POP    PSW
        POP    DPH
        POP    DPL
        POP    ACC
        LJMP   8023H
        PUSH   ACC
        PUSH   DPL
        PUSH   DPH
        PUSH   PSW
        MOV    PSW, #00H
LFAA4:  LCALL  LF093
        JC     LFAAC
        LJMP   LFABE
LFAAC:  LCALL  LF099
        LCALL  LF0A5
        CJNE   A, #11H, LFAB8
        LJMP   LFABE
LFAB8:  CJNE   A, #1BH, LFABE
        LJMP   LFA3E
LFABE:  LCALL  LF09F
        POP    PSW
        POP    DPH
        POP    DPL
        POP    ACC
        RETI   

LFACA:  INC    DPTR
LFACB:  CLR    A
        MOVC   A, @A+DPTR
        MOV    R0, A
        INC    DPTR
        CLR    A
        MOVC   A, @A+DPTR
        MOV    R1, A
        INC    DPTR
        RET    
LFAD4:  XCH    A, R0
        XCH    A, DPH
        XCH    A, R0
        XCH    A, R1
        XCH    A, DPL
        XCH    A, R1
        RET    
LFADD:  CLR    A
        MOVC   A, @A+DPTR
LFADF:  MOV    R3, A
        LCALL  LFAD4
        CLR    A
        MOVC   A, @A+DPTR
        XCH    A, R3
        LCALL  LFAF0
        LCALL  LFAD4
        MOV    A, R3
        lcall writebyte
        INC    DPTR
        RET    
LFAF0:  LCALL  LF8F4
        INC    DPTR
        RET    
LFAF5:  MOV    28H, A
        MOV    R0, DPL
        MOV    R1, DPH
        MOV    DPTR, #7E03H
        MOV    A, 27H
        lcall writebyte
        INC    DPTR
        MOV    A, 26H
        lcall writebyte
        INC    DPTR
        MOV    A, R1
        lcall writebyte
        INC    DPTR
        MOV    A, R0
        lcall writebyte
        RET    
LFB0C:  MOV    A, R2
        MOV    B, #06H
        MUL    AB
        MOV    DPTR, #7E7BH
        LCALL  LF9E2
        CLR    A
        MOVC   A, @A+DPTR
        RET    
LFB1A:  MOV    R2, #00H
LFB1C:  INC    R2
        LCALL  LFB0C
        CJNE   A, 00H, LFB25
        CPL    C
        RET    
LFB25:  CJNE   R2, #0AH, LFB1C
        RET    
LFB29:  MOV    R6, DPH
        MOV    R7, DPL
        MOV    R2, #0AH
LFB2F:  LCALL  LFB0C
        JZ     LFB4F
        LCALL  LFACA
        CLR    C
        SUBB   A, R7
        MOV    R3, A
        MOV    A, R0
        SUBB   A, R6
        JNZ    LFB40
        SJMP   LFB49
LFB40:  CLR    C
        MOV    A, R7
        SUBB   A, R1
        MOV    R3, A
        MOV    A, R6
        SUBB   A, R0
        CLR    C
        JNZ    LFB4F
LFB49:  CJNE   R3, #02H, LFB4C
LFB4C:  JNC    LFB4F
        RET    
LFB4F:  DJNZ   R2, LFB2F
        RET    
LFB52:  LCALL  LFB29
        MOV    A, #04H
        JC     LFAF5
        MOV    R0, #00H
        LCALL  LFB1A
        MOV    A, #05H
        JNC    LFAF5
        DEC    R2
        MOV    27H, R2
LFB65:  MOV    A, #01H
LFB67:  lcall writebyte
        INC    DPTR
        MOV    A, R6
        lcall writebyte
        INC    DPTR
        MOV    A, R7
        lcall writebyte
        CLR    A
        LJMP   LFAF5
LFB72:  MOV    R5, #01H
        SJMP   LFB7C
LFB76:  MOV    R5, #02H
        SJMP   LFB7C
LFB7A:  MOV    R5, #00H
LFB7C:  MOV    A, 27H
        CJNE   A, #80H, LFB91
        MOV    R2, #0AH
LFB83:  LCALL  LFB0C
        JZ     LFB8A
        MOV    A, R5
        lcall writebyte
LFB8A:  DJNZ   R2, LFB83
        RET    
LFB8D:  MOV    A, R0
        LJMP   LFAF5
LFB91:  MOV    R0, #07H
        CJNE   A, #0AH, LFB96
LFB96:  JNC    LFB8D
        MOV    R2, A
        INC    R2
        LCALL  LFB0C
        MOV    R0, #06H
        JZ     LFB8D
        MOV    A, R5
        lcall writebyte
        CLR    A
        LJMP   LFAF5
LFBA7:  MOV    A, 27H
        MOV    R0, #07H
        CJNE   A, #0AH, LFBAE
LFBAE:  JNC    LFB8D
        MOV    B, #06H
        MUL    AB
        MOV    R7, A
        MOV    DPTR, #7E81H
        MOVC   A, @A+DPTR
        MOV    27H, A
        INC    R7
        MOV    A, R7
        MOVC   A, @A+DPTR
        MOV    R0, A
        INC    R7
        MOV    A, R7
        MOVC   A, @A+DPTR
        MOV    R1, A
        INC    R7
        MOV    A, R7
        MOVC   A, @A+DPTR
        MOV    26H, A
        MOV    DPH, R0
        MOV    DPL, R1
        CLR    A
        LJMP   LFAF5
LFBD0:  MOV    DPTR, #7E0DH
        LJMP   LFACB
LFBD6:  MOV    A, R4
        MOV    DPTR, #LF342 ;??????
        MOVC   A, @A+DPTR
        ANL    A, #0FCH
        MOV    DPTR, #LFBE1 ;??????!!!!!
        JMP    @A+DPTR
Lfbe1:  LJMP   LFE89
        NOP    
        LJMP   LFC47
        NOP    
        LJMP   LFC41
        NOP    
        LJMP   LFC3C
        NOP    
        LJMP   LFC36
        NOP    
        LJMP   LFC24
        NOP    
        LJMP   LFC20
        NOP    
        LJMP   LFE73
        NOP    
        LJMP   LFE77
        NOP    
        LJMP   LF31B
        NOP    
        MOV    A, #0E0H
        LCALL  LF2B8
        MOV    R0, A
        INC    DPTR
        INC    DPTR
        INC    DPTR
        CLR    A
        MOVC   A, @A+DPTR
        MOV    R1, A
        INC    DPTR
        CLR    A
        MOVC   A, @A+DPTR
        ADD    A, R0
        MOV    2CH, A
        CLR    A
        ADDC   A, R1
        MOV    2BH, A
        RET    
LFC20:  LCALL  LFC24
        RETI   
LFC24:  LCALL  LF2B6
        MOV    R1, A
        LCALL  LF998
        MOV    2BH, A
        LCALL  LF998
        MOV    2CH, A
        MOV    A, R1
        LJMP   LF2BD
LFC36:  JB     11H, LFC57
        LCALL  LF32C
LFC3C:  MOV    2BH, R5
        MOV    2CH, R6
        RET    
LFC41:  JB     11H, LFC57
        LCALL  LF32C
LFC47:  MOV    A, R4
        RR     A
        SWAP   A
        ANL    A, #07H
        XCH    A, 2BH
        ANL    A, #0F8H
        ORL    A, 2BH
        MOV    2BH, A
        MOV    2CH, R5
        RET    
LFC57:  MOV    R6, 2BH
        MOV    R7, 2CH
        MOV    R2, #0BH
        LCALL  LFB0C
        LCALL  LFB65
        MOV    A, 24H
        ANL    A, #04H
        JZ     LFC6C
        LJMP   LFC74
LFC6C:  MOV    R2, #0BH
        LCALL  LF262
        LJMP   LFEB1
LFC74:  LCALL  LF4CC
        SETB   12H
        CLR    11H
        SJMP   LFC80
LFC7D:  LCALL  LFDA2
LFC80:  LCALL  LFC96
        MOV    R2, #0AH
        LCALL  LFD86
        JNC    LFC7D
        RET    
LFC8B:  SETB   11H
LFC8D:  MOV    A, 24H
        ANL    A, #04H
        JZ     LFC96
        LCALL  LFDA2
LFC96:  LCALL  LFBD0
        MOV    2BH, R0
        MOV    2CH, R1
        LCALL  LFAD4
        CLR    A
        MOVC   A, @A+DPTR
        MOV    R4, A
        INC    DPTR
        CLR    A
        MOVC   A, @A+DPTR
        MOV    R5, A
        INC    DPTR
        CLR    A
        MOVC   A, @A+DPTR
        MOV    R6, A
        MOV    A, R4
        MOV    DPTR, #LF342 ;?????????!!!!!
        MOVC   A, @A+DPTR
        ANL    A, #03H
        MOV    R2, A
        ADD    A, 2CH
        MOV    2CH, A
        CLR    A
        ADDC   A, 2BH
        MOV    2BH, A
        LCALL  LFBD6
        MOV    DPL, 2CH
        MOV    DPH, 2BH
        LCALL  LF251
        RET    
LFCC9:  MOV    A, 26H
        JZ     LFCD8
        PUSH   00H
        PUSH   01H
        LCALL  LF251
        POP    01H
        POP    00H
LFCD8:  LCALL  LFAD4
        MOV    R5, #00H
        MOV    A, R2
        JZ     LFCE5
        LCALL  LFB29
        MOV    R5, #01H
LFCE5:  MOV    R2, #0BH
        LCALL  LFB0C
        MOV    A, R5
        LCALL  LFB67
        MOV    A, 24H
        ANL    A, #04H
        JZ     LFCF7
        LJMP   LFD0F
LFCF7:  LCALL  LF260
        MOV    A, 28H
        JZ     LFD0B
        XRL    A, #03H
        JNZ    LFD0B
        LCALL  LF2A0
        LCALL  LF4CC
        SETB   12H
        RET    
LFD0B:  LCALL  LFEB1
        RET    
LFD0F:  LCALL  LF4CC
        ANL    3AH, #00H
        MOV    DPTR, #7E07H
        CLR    A
        MOVC   A, @A+DPTR
        JNZ    LFD25
LFD1C:  LCALL  LFC8D
        LCALL  LFD84
        JNC    LFD1C
        RET    
LFD25:  LCALL  LF093
        JNC    LFD7B
        LCALL  LF890
        MOV    R0, A
        MOV    A, 3AH
        INC    3AH
        JZ     LFD3F
        DEC    A
        JZ     LFD4B
        DEC    A
        JZ     LFD52
        DEC    A
        JZ     LFD59
        SJMP   LFD78
LFD3F:  CJNE   R0, #1BH, LFD43
        RET    
LFD43:  CJNE   R0, #04H, LFD78
        LCALL  LF884
        SJMP   LFD7B
LFD4B:  MOV    26H, R0
        LCALL  LF884
        SJMP   LFD7B
LFD52:  MOV    3BH, R0
        LCALL  LF884
        SJMP   LFD7B
LFD59:  MOV    DPL, R0
        LCALL  LF884
        MOV    DPH, 3BH
        MOV    A, 26H
        JNZ    LFD72
        MOV    DPTR, #7E0DH
        CLR    A
        MOVC   A, @A+DPTR
        LCALL  LF884
        INC    DPTR
        CLR    A
        MOVC   A, @A+DPTR
        SJMP   LFD75
LFD72:  LCALL  LF96B
LFD75:  LCALL  LF884
LFD78:  ANL    3AH, #00H
LFD7B:  LCALL  LFC8D
        LCALL  LFD84
        JNC    LFD25
        RET    
LFD84:  MOV    R2, #00H
LFD86:  LCALL  LFBD0
LFD89:  INC    R2
        CJNE   R2, #0CH, LFD8E
        RET    
LFD8E:  LCALL  LFB0C
        CJNE   A, #01H, LFD89
        INC    DPTR
        CLR    A
        MOVC   A, @A+DPTR
        CJNE   A, 00H, LFD89
        INC    DPTR
        CLR    A
        MOVC   A, @A+DPTR
        CJNE   A, 01H, LFD89
        CPL    C
        RET    
LFDA2:  ret 
LFE64:  MOV    A, #12H
        LCALL  LFAF0
        MOV    A, #0F1H
        LCALL  LFAF0
        MOV    A, #00H
        LJMP   LFAF0
LFE73:  MOV    06H, R5
        MOV    R5, #03H
LFE77:  MOV    R7, #00H
        MOV    A, R6
        MOV    R6, #03H
        JNB    ACC.7, LFE80
        DEC    R7
LFE80:  ADD    A, 2CH
        MOV    2EH, A
        MOV    A, R7
        ADDC   A, 2BH
        MOV    2DH, A
LFE89:  MOV    DPTR, #7EC3H
        LCALL  LF251
        LCALL  LFAD4
        MOV    R0, #04H
LFE94:  MOV    A, @R0
        LCALL  LFAF0
        INC    R0
        DJNZ   R2, LFE94
        LCALL  LFE64
        MOV    2FH, DPL
        LCALL  LFE64
        LCALL  LFED9
        CJNE   A, 2FH, LFEB0
        MOV    2CH, 2EH
        MOV    2BH, 2DH
LFEB0:  RET    
LFEB1:  MOV    DPTR, #7E07H
        CLR    A
        MOVC   A, @A+DPTR
        JZ     LFED4
        LCALL  LF9F6
        JNC    LFECA
        LCALL  LF2A0
        MOV    A, #64H
        MOV    28H, A
        LCALL  LF4CC
        SETB   12H
        RET    
LFECA:  LCALL  LF4CC
        SETB   12H
        LCALL  LFA66
        SJMP   LFED9
LFED4:  LCALL  LF4CC
        SETB   12H
LFED9:  LCALL  LF09F
        LCALL  LF0AE
        MOV    DPTR, #7E80H
        MOV    R0, #6FH
LFEE4:  CLR    A
        MOVC   A, @A+DPTR
        XCH    A, @R0
        lcall writebyte
        INC    DPL
        DJNZ   DPL, LFEEF
        DEC    DPH
LFEEF:  DEC    DPL
        DJNZ   R0, LFEE4
        CLR    A
        MOVC   A, @A+DPTR
        MOV    R0, A
        MOV    DPTR, #7E10H
        CLR    A
        MOVC   A, @A+DPTR
        MOV    B, A
        MOV    DPTR, #7E0FH
        CLR    A
        MOVC   A, @A+DPTR
        XCH    A, SP
        lcall writebyte
        MOV    DPTR, #7E0EH
        CLR    A
        MOVC   A, @A+DPTR
        PUSH   ACC
        MOV    DPTR, #7E0DH
        CLR    A
        MOVC   A, @A+DPTR
        PUSH   ACC
        MOV    DPTR, #7E0CH
        CLR    A
        MOVC   A, @A+DPTR
        PUSH   ACC
        MOV    DPTR, #7E0BH
        CLR    A
        MOVC   A, @A+DPTR
        PUSH   ACC
        MOV    DPTR, #7E0AH
        CLR    A
        MOVC   A, @A+DPTR
        MOV    IE, A
        MOV    DPTR, #7E09H
        CLR    A
        MOVC   A, @A+DPTR
        MOV    DPTR, #7E08H
        MOV    PSW, A
        CLR    A
        MOVC   A, @A+DPTR
        POP    DPH
        POP    DPL
        RET    
   

LF026:  CLR    A ;//main
        MOV    0CBH, A
        MOV    0CAH, A
        MOV    0CCH, A
        MOV    0CDH, A
        MOV    0C9H, A
        MOV    0c8h, A
LF033:  JB     P3.0, LF033
LF036:  JNB    P3.0, LF036
        SETB   0c8h.2
LF03B:  JNB    P3.0, LF041
        JNB    0c8h.7, LF03B
LF041:  JNB    P3.0, LF041
LF044:  JNB    P3.0, LF04A
        JNB    0c8h.7, LF044
LF04A:  JNB    P3.0, LF04A
        CLR    0c8h.2
        JB     0c8h.7, LF026
        MOV    R7, 0CCH
        MOV    R6, 0CDH
        MOV    A, R6
        CLR    C
        RRC    A
        MOV    R4, A
        MOV    A, R7
        RRC    A
        ADD    A, R7
        MOV    R7, A
        MOV    A, R4
        ADDC   A, R6
        MOV    R6, A
        MOV    A, R7
        ADD    A, #10H
        MOV    R7, A
        CLR    A
        ADDC   A, R6
        MOV    R6, A
        MOV    A, R7
        MOV    R0, #05H
LF06B:  XCH    A, R6
        CLR    C
        RRC    A
        XCH    A, R6
        RRC    A
        DJNZ   R0, LF06B
        MOV    R7, A
        CLR    C
        CLR    A
        SUBB   A, R7
        MOV    0CAH, A
        MOV    0CCH, A
        CLR    A
        SUBB   A, R6
        MOV    0CBH, A
        MOV    0CDH, A
        MOV    0c8h, #34H
        MOV    SCON, #5AH
LF086:  clr    ri; SCON.RI
LF088:  JNB    ri,LF088
        MOV    A, SBUF
        CJNE   A, #11H, LF086
        LJMP   LF446 ;start

LF093:  MOV    C, ri;SCON.RI
        RET    
LF096:  MOV    C, ti;SCON.TI
        RET    
LF099:  MOV    A, SBUF
        RET    
LF09C:  MOV    SBUF, A
        RET    
LF09F:  CLR    ti;SCON.TI
        RET    
LF0A2:  SETB   ti;SCON.TI
        RET    
LF0A5:  CLR    ri;SCON.RI
        RET    
LF0A8:  CLR    ES
        RET    
LF0AB:  SETB   ES
        RET    
LF0AE:  RET    
LF0AF:  RET    
LF0B0:  lcall writebyte
        RET  

clearuser:mov r2,#0h
clear_0:mov sfal,#0 ;0000-7d00h
	mov sfah,r2
	mov sfcm,#0bh
clear_1:mov a,sfst
	jb acc.2,clear_1
	inc r2
	cjne r2,#7eh,clear_0
	mov r2,#0h
clear_2:mov sfal,#80h
	mov sfah,r2
	mov sfcm,#0bh
clear_3:mov a,sfst
	jb acc.2,clear_3
	inc r2
	cjne r2,#7eh,clear_2
	ret


        END

