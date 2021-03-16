			;***************
			;lcd_program   2002.4.13
			;***************
			send_no     equ  08h
			dot_bit     equ  send_no
			t_20ms      equ  dot_bit+1
			T_1S        EQU  t_20ms+1H
			LED_power   EQU  t_1s+1h
			key_data    equ  led_power+1h
			ch_no_temp  equ  key_data+1h
			tp_100ms    equ  ch_no_temp+1
			beep        equ  tp_100ms+1h
			test_no     equ  beep+1h
			t_30ms      equ  test_no+1h
			beep1       equ  t_30ms+1h
			N1          equ  beep1+1h
			n2          equ  N1+1h
			hl_out      equ  n2+1
			fd2_temp    equ  hl_out+1h
			fd1_temp    equ  fd2_temp+3h
			led_ch      equ  fd1_temp+3
			sec_bak     equ  led_ch+1
			h_l_out     equ  sec_bak+1
			fs_out      equ  h_l_out+1
;*********************************************************
			set_data    equ  24h
			t_250ms     equ  set_data+1
			addres_bak  equ  t_250ms+1
			sec         equ  addres_bak+1
			m_count     equ  sec+1
		;*************************************                                  
			LED1      EQU   m_count+1h
			LED2      EQU   led1+1h
			LED3      EQU   led2+1h
			LED4      EQU   led3+1h
			led5      equ   led4+1
			led6      equ   led5+1
			led7      equ   led6+1
			led8      equ   led7+1
			led9      equ   led8+1
			led10     equ   led9+1

			fh1_bak   equ  led10+1
			fh2_bak   equ  fh1_bak+1 
						
			kb_data   equ  fh2_bak+1;***********
			kc_data   equ  kb_data+1
			led0_bak  equ  kc_data+1
			led1_bak  equ  led0_bak+1
			led2_bak  equ  led1_bak+1
			led3_bak  equ  led2_bak+1
			led4_bak  equ  led3_bak+1
			fs1_no    equ  led4_bak+1
			fs2_no    equ  fs1_no+2h
	;***************  send to rs_485******************************
			rs_no     equ  21d 
			y1        equ  fs2_no+2
			y2        equ  y1+3h
			y3        equ  y2+3h
			y4        equ  y3+3h
	;*********************************************
			dt1_dat   equ  y4+3
			dt2_dat   equ  dt1_dat+1
			dt3_dat   equ  dt2_dat+1
			dt4_dat   equ  dt3_dat+1

			w_adj_1   equ  dt3_dat
			frist     equ  w_adj_1+1

			fd1_dat   equ  frist+1
			fd2_dat   equ  fd1_dat+1
			fd3_dat   equ  fd2_dat+1
			fd4_dat   equ  fd3_dat+1
;**************************************************2002.4.1
			fh1       equ  fd3_dat
			fh2       equ  fh1+1
;**************************************************2002.4.1
			ch_no     equ  fh2+1
			bps       equ  ch_no+1h
			addres    equ  bps+1h
			dp_dat    equ  addres+1h;dp=1 500ms,dp=0 250ms
			da_no     equ  dp_dat+1h;in menu2
			del_t     equ  da_no+1
	;*******************************************
			fo1       equ  del_t+1
			fo2       equ  fo1+3h
		;****************************************
			k1        equ  fo2+3h     
			k2        equ  k1+3h      
		;***************************************
			b1        equ  k2+3h
			b2        equ  b1+3h
		;***************************************
			c1        equ  b2+3h
			c2        equ  c1+3h
		;************************************
			l1        equ  c2+3h
			l2        equ  l1+3h
		;*************************************
			h1        equ  l2+3h
			h2        equ  h1+3h
		;*************************************                  
			fs1       equ  h2+3h
			fs2       equ  fs1+3h
			menu_no   equ  56d
		;**************************************
			pc1       equ  fs2+3
			pc21      equ  pc1+20;;10
			lcd_buf   equ  pc21+1
			p0_buf    equ  lcd_buf+12
			p2_buf    equ  p0_buf+8
			p3_buf    equ  p2_buf+8
			p0_buf_bak equ p3_buf+8
			p2_buf_bak equ p0_buf_bak+8
			p3_buf_bak equ p2_buf_bak+8
			sp_data    equ p3_buf_bak+8          
		;**************************************                                                         
		;eeprom_adress:         
			ch_ee_no     equ  14d
			dt1_dat_ee   equ  00h
			dt2_dat_ee   equ  dt1_dat_ee+1
			dt3_dat_ee   equ  dt2_dat_ee+1
			dt4_dat_ee   equ  dt3_dat_ee+1
;************************* 2002.4.1 ********************
			w_adj_1_ee  equ  dt3_dat_ee                       
			frist_ee    equ  w_adj_1_ee+1
;************************* 2002.4.1 ********************
			fd1_dat_ee   equ  frist_ee+1
			fd2_dat_ee   equ  fd1_dat_ee+1
			fd3_dat_ee   equ  fd2_dat_ee+1
			fd4_dat_ee   equ  fd3_dat_ee+1
;********************************************************
			fh1_ee      equ  fd3_dat_ee
			fh2_ee      equ  fh1_ee+1
;********************************************************
			ch_no_ee     equ  fh2_ee+1 
	;*********************************************
			bps_ee      equ  ch_no_ee+1h
			addres_ee   equ  bps_ee+1h
			dp_dat_ee   equ  addres_ee+1h
			en_dat_ee   equ  dp_dat_ee+1h
			del_t_ee    equ  en_dat_ee+1h
		;*****************************************
			fo1_ee     equ  del_t_ee+1
			fo2_ee     equ  fo1_ee+3h
		;****************************************
			k1_ee      equ  fo2_ee+3h       
			k2_ee      equ  k1_ee+3h        
		;***************************************
			b1_ee      equ  k2_ee+3h
			b2_ee      equ  b1_ee+3h
		;***************************************
			c1_ee      equ  b2_ee+3h
			c2_ee      equ  c1_ee+3h
		;************************************
			l1_ee      equ  c2_ee+3h
			l2_ee      equ  l1_ee+3h
		;*************************************
			h1_ee      equ  l2_ee+3h
			h2_ee      equ  h1_ee+3h
		;*************************************                  
			fs1_ee     equ  h2_ee+3h
			fs2_ee     equ  fs1_ee+3h
		;***************************************                
		;LED_ERR: 10 10 10 10 B 
		;         4  3  2  1 _WAY
		;         HL HL HL HL ;H=>OVER;L=>LOW
		;         11=>NO WORK   
		       fff_f     bit  00h
		       FL_500MS  BIT  Fff_f+1H
		       FL_250MS  BIT  Fff_f+2H
		       dot_f     BIT  Fff_f+3H
		       set_f     bit  dot_f+1h  
		       set1_f    bit  set_f+1   
			;*****************************
			ha_over     bit  set1_f+1h
			ha_over1    bit  ha_over+1h
			pc_f    bit  ha_over1+1h
			key_you_f   bit  pc_f+1h
			ha_f        bit  key_you_f+1h
			menu1_over  bit  ha_f+1h
			ha_fl       bit  menu1_over+1h                                           
			TEST_F      BIT  ha_fl+1H
			key_over    bit test_f+1h
			rs_485_f    bit key_over+1h
			set_clk_f   bit rs_485_f+1h
			sq1_f       bit set_clk_f+1h                                             
			sq_f        bit sq1_f+1h
			kd_over     bit sq_f+1
			ee_f        bit kd_over+1
			test_ok     bit ee_f+1
			card_f      bit test_ok+1
			turn_f	    bit card_f+1
			llc_f       bit turn_f+1
;*************************************************
			lamp_out   bit llc_f+1
			ee24_out   bit lamp_out+1
			beep_out   bit ee24_out+1
			ch_max         equ  01d 
			cmp_no         equ  01d 
			da_l           equ  00h
	;**************************************************		
			back_x         equ  30d
			lcd_t          equ  0ffh
			pass_1         equ  09h 
			pass_2         equ  08h 
			pass_3         equ  07h
			sn_pass1       equ  01h
			sn_pass2       equ  02h ;sn_password=123
			sn_pass3       equ  03h
;********************************************************
			bright_x       equ  0ffh
			del_t_x        equ  0b0h
			pass_no        equ  04d;
			frist_no       equ  69d
			xu             equ  50
	
			card_power    bit p2.1
			card_test_f   bit p2.0
			;key_f        bit p2.7
		;***********************************
			rs_led     bit p2.7
		;*********************************2001.6.4
			l1_out     bit p2.0
			h1_out     bit p2.1
			l2_out     bit p1.1
			h2_out     bit p1.2
	;*******************************************2002.3.20		
			rs_en      bit p3.2
		;***********************************
			ch_a       bit p1.3
			
			;ch_b       bit p1.7
			
			sda        bit p3.6 ;sda
			scl        bit p3.7 ;scl                       
			
			si_lcd     bit p2.2
			sck_lcd    bit p2.4                     
			
			si_da      bit p3.5
			ck_da      bit p3.4
			cs_da      bit p3.3
			rck_f      bit p2.6
			rck_m      bit p2.5
			rck_r      bit p2.3
			
;******************************************************************
			T_H_100ms      EQU  0f8H  ;f755H=>2.5MS
			T_L_100ms      EQU  1eH  ;11.0592mhz
			TIMER_no       EQU  100D    ;230400uS=250ms     
			key_da         equ  0f0h ;#11110000b
			max            equ  39d
			max1           equ  34d
;******************************************************************
		;************* eeprom  ********************         
			slar        equ 0a1h
			slaw        equ 0a0h
		;****************************************
			black     equ  1Ch
			l_led     equ  11h
			o_led     equ  15h
			u_led     equ  1Bh
			r_led     equ  18h
			QQ_led    equ  1dh
			p_led     equ  16h
			a_led     equ  0ah
			UU_led    equ  1ah
			s_led     equ  19h
			e_led     equ  0eh      
			tt_led    equ  1fh
			ff_led    equ  1eh
			c_led     equ  0ch
			h_led     equ  10h
			b_led     equ  0bh
			d_led     equ  0dh
			f_led     equ  0fh                                                                                                                      
			nn_led    equ  12h
			n_led     equ  13h
			yo_led    equ  2ch
;************************************************************************                       
			oRG  0000H;            ;
			     AJMP start            
			ORG  0003H;            ;
			     reti;ljmp int0
			ORG  000BH             ;
			     LJMP T0           ;
			ORG  0013H    
			     reti              ;
			ORG  001BH             ;
			     reti        ;
			ORG  0023H             ;
			     jmp rs_485;RETI
			ORG  002bH             ;
				clr tf2
              			setb test_f ;2001.5.24
				reti
;**************************************
start:   
		mov p0,#0aah
		mov a,#0e8h
str1:
		MOV b,#0ffh       ;
		MOV  R0,#01H       ;
cR:             INC R0            ;
		MOV @R0,#00d         ;
		djnz b,cr     
		dec a
		jnz str1
;******************************2002.5.5
		setb beep_out
;*****************************

		mov sp,#sp_data
		call read_ee
		call int_ctrl
		mov a,frist
		cjne a,#frist_no,int_go_1
		sjmp go_2
       int_go_1:      
		call read_int
		call wr_int
go_2:
		call bps_int            
		call jb_ch_max;2002.3.20
		call de_10s
		;sjmp go_2
		mov frist,#0
		;jmp set_clock
		;jmp set_al4
		;call pass_set
		;call set_menu2
		;call timer_20ms
		;call set_fh12
;***************************************************
;   MINI_Pragram
;***********************************************
STAR_BI:
		call clock
		call led_jmp
		call send_pc
		call led
		call key_bord1
		call key_del
		call set_menu
		mov set_data,#0
		call back
		call key_jmp
		call y1_count 
		call card_wr
		;call pass_set
		;call set_menu2
		;call timer_20ms
SJMP STAR_BI
;********************************
;bps=0:0.3k
;bps=1:0.6k
;bps=2:1.2k
;bps=3:2.4k
;bps=4:4.8k
;bps=5:9.6k
;bps=6:19.2k
bps_int:
;********************************************
		mov a,pcon
		anl a,#01111111b
		mov pcon,a
		mov dptr,#bps_asc
		mov a,bps
		cjne a,#06h,bb_1
		mov a,pcon
		orl a,#10000000b
		mov pcon,a
		mov a,#0fdh  ;***********************
		sjmp bb_2
	bb_1:   movc a,@a+dptr
	bb_2:   
		mov th1,a
		mov tl1,a       
		setb tr1
		ret
jb_ch_max:
;***************** jb ch_no >ch_max *********
		mov a,ch_no
		cjne a,#ch_max,cch1
		sjmp cch2	
	cch1:
		jc cch2	
		mov ch_no,#ch_max
		call wr_int
	cch2:
		ret
bps_asc:
	db 0a0h,0d0h,0e8h,0f4h,0fah,0fdh
	db 'li jie by 2001.10.27'
;************** INT_CTRL
int_ctrl:
		MOV T_1S,#TIMER_no
		mov t_250ms ,#4
		mov m_count ,#0
		mov w_adj_1,#xu 

		;******************
		clr rs_en
		setb ren

		;mov tp_100ms,#tp_ms
		mov addres_bak,addres
		setb et2
		setb et0
		MOV TMOD,#00100001B;**********2001.5.24
		mov t2con ,#00000011b;20001.5.24
		MOV TH2 ,#00h;T_H_10ms
		MOV TL2 ,#00h;T_L_10ms
		mov rcap2l,#0
		mov rcap2h,#0
		MOV SCON,#11110000b     ;mode 3  2001.6.7
		call add_w
		setb pt0
		setb pt2
		clr ps
		setb ea 
		setb tr2
		setb tr0
		  ret         
;*********************************************          
timer_20ms:
		mov r2,#del_t_x
	time0:
		mov b,#020h
		djnz b,$		
		call clock
		djnz r2,time0
		RET     
				
include"d:\lcd\lcd_ovl.asm"
;********************************* 2001.5.16
de_10s:
		mov beep,sec
		mov dptr,#del_asc
		mov a,del_t
		movc a,@a+dptr
		mov r7,a        ;read del_t 5s,10s,20s,30s
del_1:
		push 07h
		call clock
		call led_blk
		mov led1,#p_led
		jb fl_250ms,del_22

		mov led2,#r_led
		mov led3,#0eh
		mov led4,#p_led
		
		;mov led5,#5h;p_led
		;mov led6,#6h;r_led
		;mov led7,#7h;0eh
		;mov led8,#9h;p_led
		call led
	del_22:
		pop 07h
		mov a,beep
		add a,r7
		call sec_ct
		cjne a,b,d_ha5
		sjmp del_2
	d_ha5:
		jc del_1
del_2:          
		setb es                 
		ret
;******************************************    
	add_w:
		clr tr0
		mov a,#T_L_100ms
		add a, w_adj_1 ;*******have 5 order
		mov tl0 ,a
		mov a,#T_H_100ms
	;*************************      
	       addc a,#00h;
	;*************************      
		mov th0,a               
;***********************************************
;		MOV T_1S,#TIMER_no
		ret
;*************************************************
;
t0:
		clr tr0
		push a
		push psw
		push b          
		call p0_lcd_out
		call add_w
		;sjmp t0_end1
		djnz t_1s ,t0_end1
		dec t_250ms
		cpl fl_250ms
		mov a,t_250ms
		mov b,#02
		div ab
		mov a,b
		jnz t0_n1
		cpl fl_500ms    
	t0_n1:  
		mov b,dp_dat
		inc b            ;b=1 250ms b=2 500ms
		mov a,t_250ms
		div ab
		mov a,b
		jnz turn_ch1
		call turn_ch
		setb tr2
		sjmp t0_end2
	turn_ch1:
		;nop
		;nop
		call nop1
t0_end2:
		MOV T_1S,#TIMER_no

t0_end1:
		setb tr0                
		pop b
		pop psw
		pop a
		reti    
		
turn_ch:
		clr tr2
		;cpl turn_f
		;jb turn_f,tu11
		mov N1,th2
		mov n2,tl2
	;***********************2001.9.22       
		setb test_ok
	;***********************        
		mov test_no,ch_no_temp
	;****************************** 
		jnb set_f ,turn_1
		mul ab
		nop
		sjmp tu1
	turn_1:	
		mov a,ch_no_temp
		inc a
		mov b,ch_no
		inc b
		cjne a,b, tu1_2
	tu1_3:
		clr a
		sjmp tu1_4
	tu1_2:
		jnc tu1_3 
	tu1_4:
		mov ch_no_temp,a
	tu1:	
		mov a,ch_no_temp
		mov c,acc.0
		;setb c
		mov ch_a,c
		;mov c,acc.1
		;mov ch_b,c
 		clr p1.0
		mov b,#050
		djnz b,$
		setb p1.0
		
	tur12:
		clr a
		mov th2,a
		mov tl2,a
		ret

nop1:
		mov b,#043h
		djnz b,$
		ret

;*********************************black led
led_blk:
		mov r7,#10
		mov r0,#led1
		mov a,#black
	bl_1:
		mov @r0,a
		inc r0
		djnz r7,bl_1
		ret
;***********led_jmp
led_jmp:
		call led_blk
		call y1_led
		call flash_way
		mov a,led_power
		jnz led_jmp1
		ret
led_jmp1:
		;**************1,2,3,4,5,6
		;**************ch,bps,addres,dp,en,del_t                
		cjne a,#6,le11          
	le12:
		call led_menu1
		jnb set1_f,le121
		jb fl_250ms ,le121
		mov a,led_power
		cjne a,#02,le12_2
		mov led2,#black	
	le12_2:	
		mov a,#black
		mov led3,a
		mov led4,a
	le121:
		ret
	le11:
		jc le12                 
		cjne a ,#10d,le22
	le23:
		mov r1,#dt1_dat
		mov b,#10d
		call cout_dt
		jbc sq_f,conw31
		call conw3
		mov led2,#0dh
		mov led3,#tt_led
		jnb set1_f,le23_1
		jb fl_250ms,le23_1
		mov led4,#black
	le23_1:
		ret
	blk_14:
		mov a,#black
		mov led1,a
		mov led2,a
		mov led3,a
		mov led4,a
		ret
	conw31:	
		jmp blk_14
	le22:
		jc le23
		cjne a ,#14d,le33
	le34:
		mov led_power,#19
		ret
;*************************************		
		mov r1,#fd1_dat
		mov b,#14d
		call cout_dt
		jbc sq_f,conw3_1
		call conw3
		mov led2,#0fh ;led'fd'
		mov led3,#0dh
		jnb set1_f,le23_2
		jb fl_250ms,le23_2
		mov led4,#black
	le23_2:
		ret
	conw3_1:
		jmp blk_14
	le33:
		jc le34
		cjne a ,#18d,le43
	le44:
		mov led_power,#19
		sjmp le444
	le43:
		jc le44
	le444:
		cjne a ,#22d,le53
		nop
	le54:
		mov led2,#0fh
		mov led3,#o_led
		mov b,#22d
		mov r1,#fo1
		jmp led_flhc
	le53:
		jc le54
		cjne a ,#26d,le63
	le64:
		mov b,#26d
		mov led2,#0fh
		mov led3,#5h
		mov r1,#fs1
		jmp led_flhc
	le63:
		jc le64
		cjne a ,#30d,le73
	le74:
		mov b,#30d
		mov led3,#black
		mov led2,#l_led
		mov r1,#l1
		jmp led_flhc
	le73:
		jc le74
		cjne a ,#34d,le83
	le84:
		mov b,#34d
		mov r1,#h1
		mov led3,#black
		mov led2,#h_led
		jmp led_flhc
	le83:
		jc le84
		cjne a ,#38d,le93
	le94:
		mov b,#38d
		mov r1,#c1
		mov led3,#black
		mov led2,#c_led
		jmp led_flhc
	le93:
		jc le94
		ret
led_menu1:
		mov r0,#ch_no
		mov a,led_power
		dec a
		add a,r0
		mov r0,a    ;count ram_addres for ch,bps
		;************addres,dp,en,del_t
		mov a,led_power
		cjne a,#1,lee1
		mov led1,#c_led
		mov led2,#h_led
		mov led3,#black
		mov led4,@r0
		inc led4   ;ch_no(0-1)
		ret             
	lee1:
		cjne a,#2,lee2          
		mov led1,#0bh
		mov dptr,#bps1_asc
		mov a,bps
		cjne a,#06,lee1_11
		mov led2,#1h
		mov led3,#29h
		mov led4,#2h
		ret
	lee1_11:
		movc a,@a+dptr
		call bcd_8
		add a,#20h
		mov led3,a
		mov led4,b
		mov led2,#black
		ret
	bps1_asc:
		db 3d,6d,12d,24d,48d,96d
;********************************************************
	lee2:
		cjne a,#3,lee3          
		mov led1,#0dh
		mov led2,#r_led
		mov led3,#black
		mov a,@r0   ;addres(0-64)
		call bcd_8
		mov led4,b
		jz lee22
		mov led3,a
	lee22:  
		ret
	lee3:
		cjne a,#4,lee4          
		mov led1,#0dh
		mov led2,#p_led
		mov led3,#black
		mov led4,#h_led
		mov a,@r0   ;dp(0-1)l:slow h:high
		jz lee3_end
		mov led4,#l_led
	lee3_end:
		ret
	lee4:
		cjne a,#5,lee5          
		mov led1,#0dh;2001.10.16 change da out
		mov led2,#0ah;
		mov led3,#black
		mov led4,@r0   ;en(0-1)
		inc led4
		ret
	lee5:
		cjne a,#6,lee6          
		mov dptr,#del_asc
		mov led1,#tt_led
		mov led2,#black
		mov led3,#black
		mov a,@r0   ;del_t(0-3)
		movc a,@a+dptr
		call bcd_8
		mov led4,b
		jz lee52
		mov led3,a
	lee52:
		ret
	del_asc:
		db 1,10d,20d,30d
	lee6:
		ret             
		;************led "ch"                                                           
	cout_dt:        
		;clr c
		mov a,led_power
		add a,#03
		subb a,b
		mov led_ch,a      ;2001.10.18
		cjne a,ch_no,conw1
	conw21:
		;clr c	
		sjmp conw2
	conw1:
		jc conw21
		;************
		;mov a,b
		;add a,#04
		setb sq_f
		inc b
		mov led_power,b
		ret             
		;*************
	conw2:
		add a,r1
		mov r1,a    ;count dt
		ret
	conw3:  
		mov a,@r1
		mov led4,a
		mov led1,led_ch
		inc led1
		ret
;**********************************************                         
		;;keY_jmp mov sec_bak,sec
		proc led_flhc
	led_flhc:
		call cout_dt
		jbc sq_f,led_fl12
		call conw3
		mov a,#black
		mov led4,a
		jmp flash_y1
	led_fl12:
		jmp blk_14
		end

		proc flash_y1
	flash_y1:
		jb fl_250ms,led_d2
		mov led1,a
		mov led2,a
		mov led3,a
	led_d2:
		jb sq1_f,led_d22
		mov a,sec_bak
		add a,#2
		call sec_ct
		cjne a,b,led_d1
	led_d22:	
		;mov r1,#fo1
		mov a,led_ch
		mov b,#03
		mul ab
		add a,r1
		subb a,led_ch				
		mov r1,a
		jnb set_f,led_de1 
		mov led_ch,ch_no_temp
	led_de1:	
		mov r3,led_ch
		inc r3         ;r3=>ch_no
		setb sq1_f
		call ff_mov
		;jnb set1_f,led_d1
		;jb fl_250ms,led_d1
		;call blk_14
	led_d1:
		ret
		end
;&*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
led_y:
	mov r0,#fd2_temp
	call fmov
	push 03h  ;r3=ch_no
	call ftob
	pop 03h

yy_led:
	mov r1,#led1
	dec r1
	mov r7,#02
inled:  
	inc r1
	inc r0           ;to y1 (h)
	mov a,@r0
	anl a,#0f0h  ;h1=>led1
	swap a
	mov @r1,a
	mov a,@r0
	anl a,#0fh  ;h2=>led2
	inc r1
	mov @r1,a
	djnz r7,inled
;**********************jb sgn 2001.9.14
	mov a,fd2_temp+1
	orl a,fd2_temp+2
	jnz zq1
zer_data:
	mov led1,#20h
	mov led2,#0h
	mov led3,#0h
	mov led4,#0h
	jmp yy_dot
zq1:
	mov a,fd2_temp
	jb acc.7,zq2
	call z_data
	jmp yy_dot
zq2:    
	call f_data
	jmp yy_dot
;*************************************
z_data:
		mov r0,#fd2_temp
		mov a,@r0
		jnz zz1
		;0.1
		mov a,#01d
		call ddot
		ret                             
	zz1:
		cjne a,#04d,zz2
		mov a,led4
		add a,#20h
		mov led4,a
		  ret   
	zz3:
		mov r1,#led1
		add a,r1
		dec a      ;-1 rrl bit 
		mov r1,a
		mov a,@r1
		add a,#20h  ;dot bit
		mov @r1,a   ;2001.4.19
		ret
	zz2:
		jc zz3  
		cjne a,#10d,zz4
	zz5:
		;***********************************
	led999:
		mov led1,#9
		mov led2,#9
		mov led3,#9
		mov led4,#29h
		ret             
	zz4:
		jc zz5
		cjne a,#7fh,zz6
		mov a,#02d
		call ddot
		ret     
	zz6:
		cjne a,#7eh,zz8
		mov a,#03d
		call ddot
		ret
	zz8:
		jmp zer_data
;******************************************
ddot:
		mov r5,a
	ddot1:  
		mov led4,led3
		mov led3,led2
		mov led2,led1
		mov led1,#00h ;??????????2001.9.20
		djnz r5,ddot1
		mov led1,#20h
		ret
;**********************************
f_data:
		mov r0,#fd2_temp
		mov a,@r0
		clr acc.7
		mov @r0,a
		call z_data
		mov a,led4
		cjne a,#20h,fsd1
	fds2:
		mov led3,a
		sjmp fsd3	
	fsd1:
		jnc fds2	
	fsd3:
		mov led4,led3
		mov led3,led2
		mov led2,led1
		mov led1,#ff_led  ;"1"=>led1
		ret
;***************************************
yy_dot:
		;jb set1_f,fd_cu_end      
		mov r5,#00d
		mov r1,#led4    
		mov r6,#04d
	dds4:
		mov a,@r1
		cjne a,#20h,dds1
	dds2:   sjmp dds3       
	dds1:   jnc dds2
		inc r5
		dec r1
		djnz r6,dds4                                                            
	dds3:
		mov r1,#dt1_dat
		mov a,r3          ;r3=ch_no+1
		dec a             ;2001.9.27
		add a,r1
		mov r1,a
		clr c
		mov a,r5
		subb a,@r1
		jz yy_dot_end
		mov r4,a       ;r4=1,2,3
		jc yy_dot_end 
		;***************0.5=>1
		;mov a,r4
		;clr c
		;mov a,#led4
		;inc a
		;subb a,r4
		;mov r0,a       ;r0=> 0.5
		;mov b,a        ;r0=>b
		;mov a,@r0
	les11:
		mov led4,led3  ;led3=>led4
		mov led3,#black
		mov led3,led2   ;led2
		mov led2,#black
		mov led2,led1
		mov led1,#black
		djnz r4,les11
yy_dot_end :
		mov a,led4
		cjne a,#20h,f_d2
	f_d1:
		clr c
		subb a,#20h
		mov led4,a
		sjmp f_d3			
	f_d2:
		jnc f_d1	

;*****************************
;fd count
f_d3:	
	mov a,r3              ;r3=ch+no
	dec a
	mov r0,#fd1_dat
	add a,r0
	mov r0,a
	mov a,@r0
	;****************************
	mov b,led4     ;a-k+[2*k/d]*d;k=mod(a/d)
	xch a,b
	div ab
	mov a,led4
	clr c
	subb a,b
	mov led4,a
fd_cu_end:      
	ret
;*****************************************ch_no to led
y1_led:
		mov r3,ch_no
		inc r3
	y1_led1:
		mov r1,#y1
		mov a,r3
		dec a
		mov b,#03
		mul ab
		add a,r1
		mov r1,a
	;************************       
		call led_y
		mov r0,#led1
		mov a,r3
		dec a
		mov b,#4
		mul ab
		add a,r0
		mov r0,a
		mov @r0,led1
		inc r0
		mov @r0,led2
		inc r0
		mov @r0,led3
		inc r0
		mov @r0,led4
		djnz r3 ,y1_led1                                                                
		ret
;********************************************
;********************************
	clr_led0_bak:
		clr fff_f
		clr a
		mov led0_bak,#ff_led
		mov led1_bak,a
		mov led2_bak,a
		mov led3_bak,a
		mov led4_bak,a
		ret
;******************************
;jbc menu1_over ,mnb
led_cl0:
		mov a,kb_data
		cjne a,#01,ll24
		ret
din_dot:
;****************** add dot to led_bak ****************
		mov a,led_ch;  led_power =>led_ch 2001.10.18
		mov r0,#dt1_dat
		add a,r0
		mov r0,a
		mov a,#03
		clr c
		subb a,@r0
		add a,r1
		mov r1,a
		mov a,@r1
		add a,#20h
		mov @r1,a
		ret
;*****************************************
	ll24:
		mov led4,led4_bak
		mov led3,led3_bak
		mov led2,led2_bak
		mov led1,led1_bak
		mov r1,#led1
		call din_dot
	;************************jb fff_f
		mov a,kb_data
		cjne a,#02,ll23
		mov led4,led0_bak
		mov led3,#l_led
		mov led2,#o_led
		mov led1,#p_led
		jb fl_250ms,led_cl_end
		mov led4,#black
		ret     
	ll23:
	;************************flash
		mov r0,#led1
		dec r0
		mov a,kb_data
		dec a
		dec a
		;dec a       ;2001.10.18
		add a,r0
		mov r0,a
		jb fl_250ms  ,led_cl_end
		mov @r0,#black
led_cl_end:
		ret
;************************************
jj_zer:
		clr menu1_over
		mov r7,#04d
		mov r0,#led1_bak
	jj_z1:
		mov a,@r0
		jnz jj_zer_end                          
		inc r0
		djnz r7,jj_z1
		setb menu1_over
jj_zer_end:
		ret

	kill_0:
		mov a,led1_bak
		jnz new1
		mov led1_bak,led2_bak
		mov led2_bak,led3_bak
		mov led3_bak,led4_bak
		mov led4_bak,#00h
		sjmp kill_0
	new1:
		ret     

	norml:  
		mov a,led1_bak
		swap a
		orl a,led2_bak
		mov fd1_temp+1,a
		;****************
		mov a,led3_bak
		swap a
		orl a,led4_bak
		mov fd1_temp+2,a
	;**************************
		mov a,led0_bak
		cjne a,#black,ja1q                      
		clr c
		sjmp ja2q       
	ja1q:
		setb c
					
	ja2q:   mov a,dot_bit
		mov acc.7,c
		mov fd1_temp,a
		mov r0,#fd1_temp
		jmp btof
;******************************         
		proc d_f_data
d_f_data:
		call jj_zer
		jnb menu1_over ,dc1
		ret
		;************add dot to led4_bak
	dc1:
		mov r7,#04
		mov r0,#led1_bak
	dot10:
		mov a,@r0
		cjne a,#20h,dot1
		sjmp dot2
	dot1:   
		jnc dot2
		inc r0
		djnz r7,dot10
	;************************* add dot led4_bak     
		add a,#20h
		mov led4_bak,a
	dot2:
		call kill_0
	;********** jb led1_bak=20h *******
		mov a,led1_bak
		cjne a,#20h,dot_1
		sjmp dot_0
	dot_1:
		mov dot_bit,#00
		mov r7,#04d
		mov r0,#led1_bak
	dot_12:
		inc dot_bit
		mov a,@r0
		cjne a,#20h,ghh0
		sjmp dot_11  ;!!1       ;lxl<1  
	ghh0:
		jnc dot_11
		inc r0
		djnz r7,dot_12   
		dec r0
	dot_11:
		clr c
		subb a,#20h ;led_n_bak -20h
		mov @r0,a   ;clr dot
;********************* norml led1_mak led4_bak ********
		jmp norml
;******************* over *******************
dot_0:
		mov r7,#03d
		mov r0,#led2_bak
		mov dot_bit,#80h
	dfo1:
		mov a,@r0
		jnz dfo2
		inc r0
		dec dot_bit
		djnz r7,dfo1
		mov fd1_temp,#41h
		mov fd1_temp+1,#0h
		mov fd1_temp+2,#0h
		ret  ;all 0.000
	dfo2:
		mov a,dot_bit
		cjne a,#80h,dfo3
		mov dot_bit,#00
	dfo3:   
		mov led1_bak,#0
		call kill_0             
		jmp norml
		end
;***********************************
;  kb (1-5)
		proc kb_ctrl
	kb_ctrl:
		setb kd_over
		mov a,kb_data
		;dec a
		dec a
		jnz ka_s1
		clr dot_f
	ka_s1:
		mov a,kc_data
		mov b,#02d
		div ab
		mov a,b
		jnz ka_d1       ;0=>dot data    
		setb dot_f      
	ka_d1:
		inc kb_data
		mov a,kb_data
		cjne a,#07d,cc_q1
		mov kb_data,#01h        
		
		jb set_f,ka_d11
		call kbb_jmp
		sjmp ka_d12
	ka_d11:	
		call kbbs_jmp
	ka_d12:	
		call clr_led0_bak
	cc_q1:                  
		mov kc_data,#01h
		ret     
		end
;kc up 1
	kc_up:  
		jnb kd_over ,kb_d5
		mov a,kb_data
		dec a
		dec a
		jnz kb_d1
		cpl fff_f
		mov led0_bak,#black
		jb fff_f ,kb_d5
		mov led0_bak,#ff_led
		sjmp kb_d5
	kb_d1:
		inc kc_data
		mov a,kc_data
		cjne a,#11d,kb_d4
		mov kc_data,#01d
	kb_d4:
		call dat_al
kb_d5:
		ret
;***************************************************
dat_al:
		mov r0,#led1_bak
		mov a,kb_data ;(kb_data:1--6)
		dec a
		dec a
		add a,R0
		dec a
		mov r0,a
		;mov a,@r0
		;cjne a,#20h,daf11
		;sjmp daf12      
	daf11:  
		;jc daf13
	daf12:
		;mov a,kc_data
		;add a,#20h      
		;sjmp daf14
	daf13:  
		mov a,kc_data
	daf14:
		dec a
		mov @r0,a
		ret
;********************************
		proc kb_jmp
kb_jmp:
		jb set1_f,kb0_1
		;clr sq1_f           ;2001.10.18
		;************;ka        
		;call clr_kd
		;******************
		ret
	kb0_1:
		mov sec_bak,sec
		mov a,led_power
	;************** add 'dr' dec 1 ************
		cjne a,#03,kb30_1
		dec addres
		mov a,addres
		cjne a,#0ffh,kb30_2
		mov addres,#64	
	kb30_2:
		ret	
		
	kb30_1:	
		
		cjne a,#18,kb1 ;************!!!!!!!!!!!!!
	kb12:   
		jmp kb_ctrl
	kb1:    
		jnc kb12
		ret
		end

	cu_r1:
		mov a,led_ch
		mov b,#03
		mul ab
		add a,r1
		mov r1,a
		ret
				
		proc kbb_jmp
kbb_jmp:
		mov a,LED_power
		jnz kbb1
		ret
	kbb1:
		cjne a,#022,kbb2
	kbb1_1: 
		mov b,#22
		call cout_dt
		mov r1,#fo1
		call cu_r1
		jmp fd_ram      
	kbb2:
		jc kbb1_1
		cjne a,#26,kbb4
	kbb2_1: 
		mov b,#26
		call cout_dt
		mov r1,#fs1
		call cu_r1
		jmp fd_ram      
	kbb4:
		jc kbb2_1
		cjne a,#30,kbb7
	kbb4_1: 
		mov b,#30
		call cout_dt
		mov r1,#l1
		call cu_r1
		jmp fd_ram      
	kbb7:
		jc kbb4_1
		cjne a,#34,kbb8
	kbb7_1: 
		mov b,#34
		call cout_dt
		mov r1,#h1
		call cu_r1
		jmp fd_ram      
	kbb8:
		jc kbb7_1
		cjne a,#38,kbb9
	kbb8_1: 
		mov b,#38
		call cout_dt
		mov r1,#c1
		call cu_r1
		jmp fd_ram      
	kbb9:
		jc kbb8_1
		ret
		end
;************************************
		proc jj_ha_f
jj_ha_f:
		mov a,ch_no
		inc a
		rl a
		mov r7,a
		mov a,h_l_out
	jj_ha1:
		rrc a
		jc jj_ha2                       
		djnz r7,jj_ha1          
		clr ha_over
		jb ha_fl,jj_ha4
		sjmp jj_ha3
	jj_ha2:
		jb ha_fl,jj_ha4
		jb ha_over ,jj_ha3
		mov beep,sec
		clr beep_out
		setb ha_fl      
		sjmp jj_ha3
	jj_ha4:
		mov a,beep
		add a,#03d
		call sec_ct
		cjne a,b,jj_ha5
	jj_ha6:
		setb beep_out
		setb ha_over
		clr  ha_fl
		sjmp jj_ha3
	jj_ha5:                         
		jnc jj_ha6      
		mov c,fl_250ms
		mov beep_out,c
	jj_ha3:
		ret
		end             

		proc jj_ha
jj_ha:
		mov a,ch_no
		inc a
		rl a
		mov r7,a
		mov a,fs_out
	jj_ha1:
		rrc a
		jc jj_ha2                       
		djnz r7,jj_ha1          
		clr ha_over1
		jb ha_f ,jj_ha4
		sjmp jj_ha3
	jj_ha2:
		jb ha_f,jj_ha4
		jb ha_over1 ,jj_ha3
		mov beep1,sec
		clr beep_out
		setb ha_f       
		sjmp jj_ha3
	jj_ha4:
		mov a,beep1
		add a,#03d
		call sec_ct
		cjne a,b,jj_ha5
	jj_ha6:
		setb beep_out
		setb ha_over1
		clr  ha_f
		sjmp jj_ha3
	jj_ha5:                         
		jnc jj_ha6      
	jj_ha3:
		ret
		end             
;**************************************
f_fo_fs:
		mov r0,#fs1_no
		call f_fa1
		mov r1,#fo1
		call f_fa2
		mov a,r3
		mov r4,a                
		mov r1,#fs1
		call f_fa21
		mov r0,#fs1_no
		call f_fa3
led_err_out:
		mov r0,#fs1_no
		call err_do
		mov a,ch_no
		mov dptr,#err_asc
		movc a,@a+dptr
		orl a,r4
		mov fs_out,a
		ret

	fg_ad1: 
		mov a,test_no;;;;;;ch_no_temp
		rl a
		add a,r0
		mov r0,a
		ret
	y1_add1:
		mov a,r0
		mov r1,a
		call cu_y1
		mov a,r1
		mov r0,a
		ret
;********************************
f_fa1:
		call fg_ad1
		mov a,@r0
		mov b,a
		anl a,#00001111b
		mov r3,a             ;fo=>r3
		mov a,b
		swap a
		anl a,#00001111b
		mov r2,a            ;fs=>r2
		mov r0,#y1
		jmp y1_add1
;************************************
	fg_ad:  
		mov a,test_no;;;;;;ch_no_temp
		mov b,#03d
		mul ab
		add a,r1
		mov r1,a
	;***************************    
		mov a,test_no;;;;;;;ch_no_temp
		jmp fcmp
;*************************************
		proc f_fa2
 f_fa2:
		call fg_ad
		jc up_1
		mov r3,#00h
		sjmp up_2                                                               
	up_1:
		inc r3
		mov a,r3
		lcall nu_5
		mov r3,a
	up_2:
		ret
		end

		proc f_fa21
 f_fa21:

		call fg_ad
		jnc up_1
		mov r2,#00h
		sjmp up_2                                                               
	up_1:
		inc r2
		mov a,r2
		call nu_5
		mov r2,a
	up_2:
		ret
		end

	nu_5:   
		mov b,#cmp_no
		inc b
		cjne a,b,nuc1
		sjmp nuc2
	nuc1:   
		jc nu_51                
	nuc2:
		mov a,#cmp_no      
	nu_51:  ret
f_fa3:
		mov a,r2
		swap a
		anl a,#0f0h
		orl a,r4
		mov b,a                                                                         

		call fg_ad1

		mov @r0,b
		ret
;*************************************
f_l_h:
		;mov r0,#f1_temp
		;mov @r0,#04h
		;inc r0
		;mov @r0,#30h
		;inc r0
		;mov @r0,#00h
		;mov r0,#f1_temp
		;lcall btof
		;mov ch_no_temp ,#00d
		;mov r7,#05d
;*************************************
		mov r0,#fs1_no
		inc r0
		call f_fa1
		mov r1,#l1
		call f_fa2
		mov a,r3
		mov r4,a                
		mov r1,#h1
		call f_fa21
		mov r0,#fs1_no
		inc r0
		call f_fa3
p0_out:
		mov r0,#fs1_no
		inc r0              ;h,l=>byt
		call err_do
		mov a,ch_no
		mov dptr,#err_asc
		movc a,@a+dptr
		orl a,r4
		;mov fs_out,a
		cpl a
		mov b,a
		mov dptr,#err_asc
		mov a,ch_no
		movc a,@a+dptr
		orl a,b
;*************************************
		cpl a      ;out_wei=1
		;mov led24,a
		mov h_l_out,a
		cpl a
		mov c,acc.0
		mov l1_out,c
		mov c,acc.1
		mov h1_out,c
		mov c,acc.2
		mov l2_out,c
		mov c,acc.3
		mov h2_out,c
		ret
err_asc:
	db 11111100b;1 ch
	db 11110000b;2 ch
	db 11000000b;3 ch
	db 00000000b;4 ch
;****************************************
err_do: 
		mov r7,ch_no
		inc r7
		mov r4,#00d     
	cop_4:
		mov a,r7
		dec a
		rl a
		add a,r0
		mov r1,a
		mov a,@r1
		swap a
		mov b,a
		mov r6,#02d
	cop_3:
		anl a,#0fh
		cjne a,#cmp_no ,cop_1
		sjmp cop_31
	cop_1:  jc  cop_2
	
	cop_31:
		setb c
		sjmp cop_12
	cop_2:
		clr c   
	cop_12:
		mov a,r4
		rlc a
		mov r4,a
		mov a,b
		swap a
		djnz r6,cop_3
		djnz r7,cop_4
		ret             
;*************************************
;y1=k1*f1+b1
	cu_y1:
		mov a,test_no
		mov b,#03
		mul ab
		add a,r1
		mov r1,a
		ret
y1_count:       
		jb set1_f,y1_c12
		call jj_ha_f ;*****2001.5.27
		call jj_ha
	y1_c12:
		jbc test_ok ,y1_c1
		ret
	y1_c1:  
		call count_hz
		mov r1,#k1
		call cu_y1
	;******************************
		;mov r0,#fd1_temp    ;fhz into fd1_temp
		call fmul      ;k1*f1  
	
		mov r1,#b1
		call cu_y1
		call fadd      ;k1*f1+b1
		;call ftob	
	;*****************************************
	;jb c1-y1=>y1  
	;*******************************************2001.6.1
		mov r1,#c1   ;jb c1=0
		call cu_y1
		inc r1
		mov a,@r1
		inc r1
		orl a,@r1
		jz not_subb
;***********************************************
		mov r1,#c1   ;jb c1=0
		call cu_y1
		mov r0,#fd1_temp
		call fsub     ;y1=y1-c1  y1=-1
		mov a,@r0
		cpl acc.7
		mov @r0,a
;****************************************!!!!!!!!!!!
	not_subb:       
		mov r1,#y1
		call cu_y1
		mov a,r1
		mov r0,a   ;r0=> y1
		mov r1,#fd1_temp
		call fmov   ;[f1_temp]=>[yn]
		call f_fo_fs
		call f_l_h
		jmp da_out
count_hz:
		mov fd2_temp,#01h
		mov fd2_temp+1,#40h
		mov fd2_temp+2,#00h ;x_l=4,2 f=n*x_l
		mov r0,#fd2_temp
		call btof
		mov a,dp_dat    ;250ms ,500ms
		jz cou1                 
		mov fd2_temp,#01h
		mov fd2_temp+1,#20h
		mov fd2_temp+2,#00h ;x_l=4,2 f=n*x_l
		mov r0,#fd2_temp
		call btof
	cou1:
		jnb test_f ,cou2
		setb c
		mov a,n1
		rrc a
		mov n1,a
		mov a,n2
		rrc a
		mov n2,a
	cou2:
		mov fd1_temp,n1
		mov fd1_temp+1,n2
		mov fd1_temp+2,#0
		;*************** 2002.4.1
		mov n1,#0
		mov n2,#0
		;************************
		clr 1fh
		mov a,#16d
		mov r0,#fd1_temp   ;n1=h,n2=l
		call dtof
		mov r1,#fd2_temp
		call fmul          ;r0=fd1_temp =hz
		jbc test_f,cou3
		ret
	cou3:
		mov fd2_temp,#01h
		mov fd2_temp+1,#20h
		mov fd2_temp+2,#00h ;x_l=4,2 f=n*x_l
		mov r0,#fd2_temp
		call btof
		mov r0,#fd1_temp
		mov r1,#fd2_temp
		jmp fmul
;************************************
fd_ram:
		push 01h
		mov r1,#led1_bak  ;2001.10.18
		call din_dot
		call d_f_data
		pop 01h
		jb menu1_over ,fd_ram_end
		mov @r1,fd1_temp                                
		inc r1
		mov @r1,fd1_temp+1                              
		inc r1
		mov @r1,fd1_temp+2                              
		ret	
	fd_ram_end:
		mov @r1,#41h                                
		inc r1
		mov @r1,#0                              
		inc r1
		mov @r1,#0                              
		ret	
;**************************
	ff_mov:
		call led_y
		jnb kd_over ,ff_d5
		call led_cl0
	ff_d5:
		ret
;************************************
		proc key_jmp
key_jmp:
		mov a,key_data
		mov key_data,#00h
		jz key_d
		cjne a,#01,key_a
		clr sq1_f           ;2001.10.18
		;************;ka        
		call clr_kd
		;******************
		mov sec_bak,sec
		inc led_power
		mov a,#36d ;const
		add a,ch_no
		mov b,a
		mov a,led_power
		cjne a,b,key_a0
	key_a1:
		mov led_power,#01h
		ret	
	key_a0:
		jnc key_a1
		ret     
	key_a:  
		cjne a,#02,key_b
		jmp kb_jmp      ;kb
	key_b:
		cjne a,#03,key_c
		jmp kc_jmp      ;kc
	key_c:
		cjne a,#04,key_d
		mov a,led_power
		jz key_d
		jnb set1_f,key_c1
		mov addres_bak,addres
		call bps_int            
	;*************************
		mov led_power,frist
		mov frist,#frist_no;2001.10.26	
		call wr_int
	key_c1:
		clr a
		mov led_power,a
		mov frist,a
		clr set1_f
		setb es
		jmp clr_kd
key_d:
		ret
		end

	clr_kd:
		mov kb_data,#01d
		mov kc_data,#01d
		clr kd_over
		jmp clr_led0_bak
;****************************************
		proc kc_jmp
kc_jmp:
		jb set1_f,kcc1
	kcc0:
		ret                             
;**************************************
	kcc1:
;**************************************
		mov sec_bak,sec
		mov a,led_power
		cjne a,#6,kc2
	kc2_12:
		mov r0,#ch_no
		sjmp fid
	kc2:
		jc kc2_12
;************************************** 
		cjne a,#10,kc21
	kc21_1:
		mov r1,#dt1_dat
		mov b,#10d
		call cout_dt
		inc @r1
		mov a,@r1
		cjne a,#4,kc21_2
		mov @r1,#0
	kc21_2:
		ret                     
	kc21:   
		jc kc21_1
;**************************************         
		cjne a,#14,kc3
	kc22_1:
		mov r1,#fd1_dat
		mov b,#14d
		call cout_dt
		inc @r1
		mov a,@r1
		cjne a,#03,kc21_4
		mov @r1,#05
	kc21_4: 
		mov a,@r1
		cjne a,#6,kc21_3
		mov @r1,#1
	kc21_3:
		ret                     
;********************* al1_al4 **************
	kc3:
		jc kc22_1
		cjne a,#18,kc4
		ret
	kc4:
		jc kc21_3
;***************************** fs,fo    
		jmp kc_up
		end
;**********************************
	fid:
		;push a
		dec a
		mov b,a
		add a,r0
		mov r0,a   ;point to addres
		mov a,b
		mov dptr,#fd_asc
		movc a,@a+dptr
		mov b,a                                 
		;pop a
		;*********************
		;cjne a,#01,fi1
		;mov a,@r0
		;inc a
		;anl a,#ch_max
		;sjmp kc22
		;clr a
;********************************************
	fi1:
		mov a,@r0
		inc a
		inc b
		cjne a,b,kc22
		clr a
	kc22:
		mov @r0,a       
		ret     
fd_asc:
	db ch_max,06h,64d,1d,ch_max,3d;  2002.1.31
;         ch_no,bps,addres,dp_dat,da_no,del_t
;********************************************
;flash 1_way_l "lo  ovr"
FLASH_WAY:
	mov r7,#04h
	mov r6,#00h
	mov a,fs_out
fl_w1:
	push a  
	anl a ,#00000011b
;*****************************************              
		cjne a,#01,fl_w2
way_k1_3:   ;led_"low"
		call jj_led_ad
		;mov @r0,#black
		;inc r0
		mov @r0,#l_led;"L"
		INC R0
		mov @r0,#o_led ;"0"
		inc r0
		mov @r0,#black
		jb fl_250ms ,fl_w3
		call fl_blk
		sjmp fl_w3
	fl_w2:
		cjne a,#02,fl_w3
		call jj_led_ad   ;led "over"
		mov @r0,#o_led;led=>O
		inc r0
		mov @r0,#u_led;"u"
		INC R0
		mov @r0,#r_led ;"r"
		jb fl_250ms ,fl_w3
		call fl_blk
	fl_w3:
		pop a
		rr a
		rr a
		inc r6
		djnz r7,fl_w1
		ret             
;*******************************************
	fl_blk: 
		mov a,#black  ;led=>black
		mov @r0,a
		dec r0
		mov @r0,a
		dec r0
		mov @r0,a
		dec r0
		mov @r0,a     ;led1=>black
		ret
	jj_led_ad:      
		mov r0,#led1
		mov a,r6
		mov b,#04d
		mul ab
		add a,r0
		mov r0,a
		mov a,r6
		;inc a
		mov a,#black
		mov @r0,a
		inc r0
		ret
;###############################################
set_menu:
		mov a,set_data
		jnz set_m1
		ret
	set_m1:
		cjne a,#01,set_m2
		mov set_data,#0
		ret
		;jmp set_clock
	set_m2:
		cjne a,#02,set_m3
		cpl lamp_out
		mov set_data,#0
		ret
		;jmp set_fh12
	set_m3:
		cjne a,#03,set_m4
		mov led_power,#01
		mov sec_bak,sec
		setb set1_f
		call led_jmp
		;call jj_sf
		clr es
		mov set_data,#0
		ret
	set_m4:
		cjne a,#04,set_m5
		jmp pass_set
	set_m5:
		ret     
;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&			
;*****************************
kcs_jmp:
		call jj_z
		jz kcs_10
		ret		;??????????
	kcs_10:
		jmp kc_up
	jj_z:
		mov a,LED_power;(1, 2 ,3, 4 ,5)
		mov b,#02      ;a/b =0 =>2,4
		div ab
		mov a,b
		ret
		
		proc kbs_jmp
kbs_jmp:
		call jj_z
		jz kbs_10
		ret		;??????????
	kbs_10:
		jmp kb_ctrl
		end
;**************************************				
		proc kbbs_jmp
kbbs_jmp:
		mov a,led_power
		cjne a,#2,kbb2
		mov r1,#y1
		jmp fd_ram      
	kbb2:
		cjne a,#3,kbb4
		ret
	kbb4:
		cjne a,#4,kbb7
		mov r1,#y2
		jmp fd_ram      
	kbb7:
		ret
		end
	clr_ff:
		mov a,#ff_led
		mov led1_bak,#p_led
		mov led2_bak,a
		mov led3_bak,a
		mov led4_bak,a
		ret
;**************************************
		proc pass_set
pass_set:
		clr a
		mov fh1_bak,a
		mov fh2_bak,a ;2002.3.20
		mov kc_data,a

		clr menu1_over
		mov set_data,#0
		call clr_ff
		call clr_led2		
		mov sec_bak,#pass_no
		call led_blk
	pass1:
		call clock
		call led_blk
		call clr_led2
		call key_jmpp
		call y1_count
		jb menu1_over,pass1_end
		jbc card_f ,pass2_end
		mov a,sec_bak
		jnz pass1
		mov set_data,#0
		ret
		end
pass1_end:
		call beep_del
		call set_menu2
		mov set_data,#0
		ret		
;**********************************
beep_del:
		mov r7,#02
		clr beep_out
	beep1_1:
		push 07h
		call timer_20ms
		call timer_20ms
		call timer_20ms
		pop 07h
		djnz r7,beep1_1
		setb beep_out		
		ret
;***********************************		
pass2_end:
		;******turn off card power *****
		;setb card_power
		call beep_del
		;jnb card_test_f,$  ;*******card used
		jmp set_fh12   ;2002.1.31
		;jmp beep_del
;*************************************		
key_jmpp:
		mov a,key_data
		jnz kp1	
		ret	
	kp1:
		cjne a,#01,kp2;ka
		call clr_ff
		ret						
	kp2:
		cjne a,#02,kp3;kb
		mov kc_data,#0
		inc set_data
		mov a,set_data
		cjne a,#03,kp2_1
		mov set_data,#0	
	kp2_1:
		ret			
	kp3:
		cjne a,#03,kp4;kc
		inc kc_data
		mov a,kc_data
		cjne a,#10,kp3_1
		mov kc_data,#0	
	kp3_1:
		mov r0,#led2_bak
		jmp jj_led2_bak
	kp4:
		cjne a,#04,kp5;kd
		mov a,led2_bak
		xrl a,#pass_1
		jz kp41
		sjmp sec_1
	kp41:
		mov a,led3_bak
		xrl a,#pass_2
		jz kp42
		sjmp sec_1
	kp42:
		mov a,led4_bak
		xrl a,#pass_3
		jz kp43
	sec_1:
;****************** take off card ************2001.9.28
		mov a,led2_bak
		xrl a,#sn_pass1
		jz kp51
		sjmp sec_2				
	kp51:
		mov a,led3_bak
		xrl a,#sn_pass2
		jz kp52
		sjmp sec_2				
		
	kp52:
		mov a,led4_bak
		xrl a,#sn_pass3
		jz kp53
	sec_2:	
		dec sec_bak
		jmp clr_led2

	kp53:
		setb card_f
		ret	
	kp43:
		setb menu1_over
	kp5:
		ret		

	clr_led2:
		call led_pass
		call led
		call key_bord1
		call key_del
		ret	
;**********************************
	jj_led2_bak:
		mov a,set_data
		add a,r0
		mov r0,a
		mov @r0,kc_data
		ret			
led_pass:
		mov led1,led1_bak
		mov led2,led2_bak
		mov led3,led3_bak
		mov led4,led4_bak
		jb fl_250ms,led_pass1
		mov r0,#led2
		call jj_led2_bak
		mov @r0,#black
led_pass1:
		ret
jj_card:
		jb card_test_f,jj_card_end
		call timer_20ms
		call timer_20ms
		jb card_test_f,jj_card_end
		call beep_del
		clr card_power
		ret
	jj_card_end:
		setb card_power
		ret	
		
card_wr:
		jnb card_power,card_wr_1
		ret	
card_wr_1:		
		;********* write data to card ******
		;
		ret
;******************************************
rs_485:
		push a
		push b
		push psw
		push 00h
		jbc ri ,rec_s1
		clr ren
		clr ti
		jnb rs_485_f,rs4_1
		mov r0,#y1
		jnb pc_f,rs11_1
		mov r0,#pc1
	rs11_1:
		call sbuf_out		
		mov a,send_no
		cjne a,#rs_no,rs_485_end  ;****2001.5.29
		clr rs_485_f
		sjmp rs_485_end
	rs4_1:
		clr ti  
		clr rs_485_f
		clr rs_en               
		setb rs_led  ;*******2001.6.4
		setb ren
		mov send_no,#00d
		clr pc_f
		sjmp rs_485_end
	rec_s1:
	;*************************2001.6.7
		clr tb8
		clr rb8
		mov a,sbuf
		mov b,addres_bak
		cjne a,b,rs_4
		setb tb8
	;********************
		mov r0,#pc1
		setb pc_f
		sjmp rs_41
	rs_4:
		xch a,b
		setb acc.7
		xch a,b              ;send asc addres =addres+128
		cjne a,b,rs_485_end
		mov r0,#y1
		clr pc_f
	rs_41:
		clr rs_led
		clr ti
		setb rs_en
		mov send_no,#00h
		call sbuf_out
		clr ren
		setb rs_485_f
rs_485_end:
		pop 00h
		pop psw
		pop b
		pop a
		reti
;************************************
	sbuf_out:
		mov b,#05d
		djnz b,$
		
		mov a,send_no
		add a,r0
		mov r0,a
		mov a,@r0
		mov sbuf,a
		inc send_no
		ret
;*********************************
back:
		mov a,led_power
		jz bk_3
		mov a,sec_bak
		add a,#back_x
		call sec_ct
		cjne a,b,bk_3
		mov key_data,#04d
	bk_3:
		ret		
;***************************************
key_del:
		mov a,key_data
		jnz kl_12
		mov a,frist
		jnz kl_13
		ret
	kl_13:
		mov key_data,frist
		mov frist,#0
		clr key_over		
		jmp beep_del
	kl_12:	
		jnb key_over,kl11
		mov a,t_30ms
		add a,#03
		call sec_ct
		cjne a,b,key_del_end
		clr key_over		
		jmp set_key
	kl11:
		mov t_30ms,sec
		setb key_over
key_del_end:
		call sf_a
		cjne a,#key_da,sfg_12
		clr key_over		
		jmp beep_del
	sfg_12:
		mov frist,key_data
		mov key_data,#0
		ret

;******************************************
key_bord1:
		call re_k
		mov a,key_data
		jz key_bord1_end
key_bord1_end:
		;setb key_f
		ret

	sec_ct:
		mov b,#60d
		div ab
		mov a,sec
		ret
set_key:
	mov a,key_data
	cjne a,#01h,set_cc1
	mov set_data,#01d
	ret
set_cc1:
	cjne a,#02h,set_cc2
	mov set_data,#02d
	ret
set_cc2:
	cjne a,#03h,set_cc3
	mov set_data,#03d
	ret     
set_cc3:
	cjne a,#04h,sf_beep
	mov set_data,#04d
	ret
;******************************
re_k:   
		mov key_data,#00h
		mov a,p1
		anl a ,#key_da;11110000b
		cjne a,#key_da,you_key
re_k_end:       
		ret
you_key:
		call timer_20ms
		call timer_20ms
		call timer_20ms
		mov a,p1
		anl a ,#key_da
		cjne a,#key_da,you_key1
		ret                                   
you_key1:
	jb acc.7,key_kb
	mov key_data,#01h
key_kb: 
	jb acc.6,key_kb1
	mov key_data,#02h
key_kb1: 
	jb acc.5,key_kb2
	mov key_data,#03h
key_kb2: 
	jb acc.4,sf_key0
	mov key_data,#04h
sf_key0:
	ret             
sf_key:
		call sf_a
		cjne a,#key_da,sf_key
		jmp beep_del
sf_a:
		mov a,p1
		;setb key_f
		anl a ,#key_da
		ret
;************************************
sf_beep:
		jmp beep_del
jj_sf:
		mov a,p1
		anl a ,#key_da
		cjne a,#key_da,jj_sf
		mov key_data,#0
		mov frist,#0
		ret

;^&&^&^&^&^&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
clr_y1:
		mov r0,#y1
		mov r7,#12
	set_clr2:
		mov @r0,#0
		inc r0
		djnz r7,set_clr2               
		ret
set_menu2:
		mov led_power,#01
		call clr_kd
		;mov ka_data,#01
		setb set_f
		clr a
		mov key_data,a
		mov ch_no_temp,a
		call clr_y1
		mov sec_bak,sec
		clr sq1_f
		clr es
		mov frist,#0
		call led_blk
menu22:
		call clock
		call f1_count
		call led_blk
		call led_s4
		call led
		call key_bord1
		call key_del
		call key_s3
		mov a,led_power
		jnz menu22
		call clr_kd
		clr set_f
		;mov set_data,#0
		mov ch_no_temp,#0               
		mov frist,#0
		setb es
		ret
f1_count:
		jbc test_ok,f1_co10
		ret
	;***********************		
	f1_co10:
		call count_hz	
		mov a,led_power
		cjne a,#3,f1_co2
	f1_co3:
		mov r1,#fd1_temp
		mov r0,#y3
		call fmov          ;f1 to y3
		sjmp f1_co4	
	f1_co2:
		cjne a,#5,f1_co4
		mov r1,#fd1_temp
		mov r0,#y4
		call fmov          ;f2 to y4
	f1_co4:
		call f_khz
		ret
;**********************************
		proc key_s3
key_s3:
		mov a,key_data
		jnz ky_s1
		ret	
	ky_s1:
		cjne a,#01,kys2  ;ka
		call clr_kd
		clr sq1_f
		mov sec_bak,sec
		inc led_power
		mov a,led_power
		cjne a,#6,ky1_1
		;***************
		;mov led_power,#01
		call count_k_b
		mov led_power,#01
	ky1_1:
		ret
	kys2:
		cjne a,#02,kys3 ;kb
		jmp kbs_jmp
	kys3:
		cjne a,#03,kys4 ;kc
		mov a,led_power
		cjne a,#01,kys30
		inc ch_no_temp
		mov a,ch_no_temp
		mov b,ch_no
		inc b
		cjne a,b ,kys32
		mov ch_no_temp,#0	
	kys32:			
		ret
	kys30:
		jmp kcs_jmp
	kys4:
		cjne a,#04,kys5 ;kd
		mov led_power,#0
		call clr_kd
	kys5:
		ret
		end
;**********************************************
		proc led_s4
led_s4:
		mov a,led_power
		cjne a,#1,le_s01
;************** 2002.1.20************	
		mov a,ch_no
		jnz le012_1				
		inc led_power
		ret
;*************************************
	le012_1:
		mov led1,#0ch
		mov led2,#r_led
		mov led3,#black
		mov led4,#black	
		jb fl_250ms,le012
		mov led4,ch_no_temp
		inc led4
	le012:
		ret	
	le_s01:	
		cjne a,#2,le_s1
		mov led1,ch_no_temp
		inc led1
		mov led2,#yo_led
		mov led3,#1
		mov a,#black
		mov led4,a
		mov r1,#y1
		mov led_ch,#0
		call flash_y1
		sjmp le_s5

	le_s1:
		cjne a,#03,le_s2
		mov led1,ch_no_temp
		inc led1
		mov led2,#0fh
		mov led3,#1
		mov a,#black
		mov led4,a
		mov r1,#fd1_temp
		mov led_ch,#0
		call flash_y1
		sjmp le_s5
	
	le_s2:
		cjne a,#04,le_s3
		mov led1,ch_no_temp
		inc led1
		mov led2,#yo_led
		mov led3,#2
		mov a,#black
		mov led4,a
		mov r1,#y2
		mov led_ch,#0
		call flash_y1
		sjmp le_s5
	le_s3:
		cjne a,#05,le_s5
		mov led1,ch_no_temp
		inc led1
		mov led2,#0fh
		mov led3,#2
		mov a,#black
		mov led4,a
		mov  r1,#fd1_temp
		;*******************
		mov led_ch,#0
		call flash_y1
	le_s5:
		mov led_ch,ch_no_temp
		ret
		end
;*************************************
	count_k_b:
	;******************** couny k b
		mov r1,#y4
		mov r0,#fd1_temp ;fd1_temp=y4
		call fmov
		mov r1,#y3
		call fsub       ;f2-f1=fd1_temp
		mov r0,#y2
		mov r1,#y1
		call fsub       ;y2-y1=y2
		mov r1,#fd1_temp
		call fdiv       ;y2=k
		;***********
		;***********
	;********************* k to k1
		mov r0,#k1
		call jj_ar	
		mov r1,#y2
		call fmov
	;********* wr ee ***********
		mov r0,#k1_ee
		call jj_ar
		mov dpl,a
		mov dph,#0
		mov r2,#3
		mov r0,#k1
		call jj_ar	
		call clr_wk
	;***********************
		mov r0,#y2
		mov r1,#y3   ;y3=f1
		call fmul     ;k*f1
		mov r1,#y2
		mov r0,#y1
		call fsub     ;y-k*f=b
		;***********
		mov r0,#b1
		call jj_ar
		mov r1,#y1
		call fmov
		mov r0,#b1_ee
		call jj_ar
		mov dpl,a
		mov dph,#0
		mov r2,#3
		mov r0,#b1
		call jj_ar	
		call clr_wk
		call clr_y1
		ret
jj_ar:
		mov a,ch_no_temp		
		mov b,#03
		mul ab
		add a,r0
		mov r0,a  ;r0 to k1
		ret
;********************************
	f_khz:		
		mov r0,#fd1_temp
		call fmov         ;f1,f2 to fd1_temp
		;***********
		;***********
		mov fd2_temp,#04h
		mov fd2_temp+1,#10h
		mov fd2_temp+2,#00h
		mov r0,#fd2_temp
		call btof
		mov r0,#fd1_temp
		mov r1,#fd2_temp
		call fdiv
		mov r1,#fd1_temp   ;f1/1000 to led
		ret
;****************** 0 asc 48 ,9 asc 57 ******
send_pc:
		jb rs_485_f ,se_end
		jb set1_f ,se_end
		clr es
		clr f0
		mov r0,#led1
		mov r1,#pc1
		mov r6,#21
	se_c1:
		mov @r1,#32
		inc r1
		djnz r6 ,se_c1
;*********************************
		mov r1,#pc21
		mov a,ch_no
		inc a
		mov r6,a
		add a,#48  ;ch_no 1-4
		mov @r1,a
	;&&&&&&&&&&&&&&&&&&&&&&&&&	
		mov r1,#pc1
	se000:
		mov r7,#4
	se00:				
		mov a,@r0
		cjne a,#black,se1
		mov @r1,#32	
		sjmp se3_2 	
	se1:
		cjne a,#ff_led,se2
		mov @r1,#45	
		sjmp se3_2 	
	se2:
        	cjne a,#20h,se3
	se31:
		clr c
		subb a,#20h
		add a ,#48
		mov @r1,a
		inc r1
		mov @r1,#46;dot to led
		setb f0
		sjmp se3_2	
	se3:
		jnc se31		
		add a ,#48
		mov @r1,a
	se3_2:
		inc r1
		inc r0
		djnz r7,se00
		jbc f0,se09
		mov @r1,#46
		inc r1
	se09:
		djnz r6,se000
		setb es
	se_end:
		ret
;************************************
clock:
                mov a,t_250ms
		cjne a,#0ffh,clk1
		sjmp clk2
	clk1:	
                jnz clock_end           
	clk2:
                mov t_250ms ,#04d
                inc sec
                mov a,sec
                cjne a,#60d,clock_end;!!!!!!!!!!!!!!!!!!!!!!
                mov sec,#00h
clock_end:
		ret
;************************************
led_ch_clock: 
		call led_blk
;**********************************************
led_year:       
		ret

;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
da_out:
		mov r1,#y1
		mov a,da_no
		mov b,#03
		mul ab
		add a,r1
		mov r1,a
	;************************			
		mov r0,#fd2_temp
		call fmov
		mov r1,#fs1
		mov a,da_no
		mov b,#03
		mul ab
		add a,r1
		mov r1,a
	;***************************	
		call fdiv         ;fd2_temp= da%
		mov fd1_temp,#04h
		mov fd1_temp+1,#40h
		mov fd1_temp+2,#da_l ;*******2001.10.16
		mov r0,#fd1_temp
		call btof
		mov r1,#fd2_temp
		call fmul  ;fd1_temp= data
		call fint
		call ftod								
		clr cs_da
		mov r7,#08
		clr a
		jnb f0,da_12
		mov a,fd1_temp;(h)<=
	da_12:	
		call da_bit1
		mov r7,#08
		mov a,fd1_temp;(l)<=
		jnb f0,da_13
		mov a,fd1_temp+1;(l)<=
	da_13:
		call da_bit1
		setb cs_da
		setb ck_da
		ret
	da_bit1:
		setb ck_da
		rlc a
		mov si_da,c
		clr ck_da
		djnz r7,da_bit1
		ret	

led_asc:
		db 11111100B;0
		db 01100000B;1
		db 11011010B;2
		db 11110010B;3
		db 01100110B;4
		db 10110110B;5
		db 10111110B;6
		db 11100000B;7
		db 11111110B;8
		db 11110110B;9
		DB   11101110B;a=>A
		DB   00111110B;B=>B      
		DB   10011100B;C=>C      
		DB   01111010B;D=>D      
		DB   10011110B;E=>E      
		DB   10001110B;F=>F      
		DB   01101110B;H=>10H      
		DB   00011100B;L=>11H      
		DB   11101100B;N=>12H      
		db   00101010b;n=>13h
		db   11111100b;O=>14h
		dB   00111010B;o=>15H
		DB   11001110B;P=>16H
		DB   11100110B;Q=>17H
		DB   00001010B;r=>18H
		DB   10110110B;S=>19H      
		DB   01111100B;U=>1AH      
		DB   00111000B;u=>1BH      
		DB   00000000B;BLACK=>1CH
		DB   11111111B;8.=>1DH
		db   00000010b;-=>1Eh
		db   00011110b;t=>1Fh
		db 11111101B;0.=>20h
		db 01100001B;1.
		db 11011011B;2.
		db 11110011B;3.
		db 01100111B;4.
		db 10110111B;5.
		db 10111111B;6.
		db 11100001B;7.
		db 11111111B;8.
		db 11110111B;9.=>29h
		db 00011010b;cc=>2ah
		db 00000001b;cc=>2bh
		db 01110110b;y0=>2ch
		db 'li jie 2001 9 20'  
asc_1:
		;abcd efgh=>abch fged
		;mov b,#0
		mov c,acc.7;a
		mov b.7,c
		mov c,acc.6;b
		mov b.6,c
		mov c,acc.5;c
		mov b.5,c
		mov c,acc.4;d
		mov b.0,c
		
		mov c,acc.3;e
		mov b.1,c
		mov c,acc.2;f
		mov b.3,c
		mov c,acc.1;g
		mov b.2,c
		mov c,acc.0;h
		mov b.4,c
		mov a,b
		ret		
		

;*******************************************
		;led=>  /   abcdefgh
		;abcdefgh=>
		;degfhcba;****fu hao out

		proc led
LED:            
		call fh_to_led9
		;mov led9,#00001100b
		;mov led10,#00100000b
;********************************2002.1.19
		mov r0,#lcd_buf
		mov r1,#led1
		mov R7,#12
		mov dptr,#led_asc
	led_next:
		mov a,@r1
		cjne r1,#led9,lku12
	lku13:
		sjmp lku14	
	lku12:
		jnc lku13	
		movc a,@a+dptr
;******************************** p4,p8 to led
		mov b,a
		cjne r1,#led4,lku45
		             ;trxd to p4
		mov c,rs_led
		cpl c
		mov acc.0,c
		sjmp lku14
	lku451:
		mov a,b
		clr acc.0
		sjmp lku14
	lku45:
		cjne r1,#led8,lku14
		mov c,ee_f
		;cpl c
		mov acc.0,c
		sjmp lku14
	lku453:
		mov a,b
		clr acc.0
	lku14:
		call asc_1
	lki12:
		mov @r0,a
		inc r0
		inc r1
		djnz R7 ,led_next               

led_np:
		call seg_bin
		call bin_lcd
led_end1:
		
		ret
		end
seg_bin:
		setb llc_f
		mov r0,#lcd_buf
		mov r1,#p0_buf
		mov r6,#12
	stodpg1:
		mov b,r1
		mov r7,#8
		mov a,@r0
		mov r2,a
	stodpg2:
		mov a,r2
		rrc a
		mov r2,a
		push psw
		mov a,@r1
		rrc a
		mov @r1,a
		inc r1
		pop psw
		cpl c
		mov a,@r1
		rrc a 
		mov @r1,a
		inc r1
		cjne r7,#5,stodpg3
		mov r1,b
	stodpg3:
		djnz r7,stodpg2
		inc r0
		mov r1,b
		cjne r6,#9,stodpg4
		mov r1,#p2_buf  ;!!!!!!!!!
	stodpg4:
		cjne r6,#5,stodpg5
		mov r1,#p3_buf  ;!!!!!!!!!
	stodpg5:
		djnz r6,stodpg1
		clr llc_f
		ret
lcd_ee24:
;*************** change led9,led10 (low)
;		mov a,led10     ;led10=abcdefgh=>0,0,0,ppm,kn,%rh,t,0
		mov a,led9      ;led9=C,m,MPa,^,v,v,^,%
		anl a,#0fh
		rl a
		mov led10,a    ;fh2 to led10 
		;******************************
		mov b,led9	
		mov a,h_l_out;*1_ch to led
		mov c,acc.0;1l
		mov b.2,c
		mov c,acc.1;1h
		mov b.1,c
		;**************************2ch to led9
		mov a,h_l_out;*********
		mov c,acc.2;2l
		mov b.3,c
		mov c,acc.3;2h
		mov b.4,c
		;************ % to led9.0
		mov a,led9
		mov c,acc.4
		mov b.0,c
;**************************** b= led9 +2^,2v,1^,1v
		mov a,fh1_bak  ;jb fh=1,0
		dec a
		jnz jk_12 
		clr b.2    ;1l
		clr b.1	   ;1h
		mov led1,#black
		mov led2,#black
		mov led3,#black
		mov led4,#black
	jk_12:
		mov a,fh2_bak
		dec a
		jnz jk_13 
		clr b.3    ;2l
		clr b.4	   ;2h
		mov led5,#black
		mov led6,#black
		mov led7,#black
		mov led8,#black
	jk_13:		
		mov led9,b
		ret
;***********************************
p0_lcd_out:
		push dph
		push dpl
		push 00h
		push 07h
		push 06h
		push 05h
		push 04h
		push 03h
		push 02h
		push 01h

	       mov p0,#0aah
		;mov p0,#01010101b

		mov a,m_count
		add a,#p0_buf_bak ;m_wei
		mov r0,a
		mov a,@r0
		mov r6,a

		mov a,m_count
		add a,#p2_buf_bak;r_wei
		mov r0,a
		mov a,@r0
		mov r5,a
;**************************************
		mov a,m_count    ;f_wei
		add a,#p3_buf_bak
		mov r0,a
		mov a,@r0
;**************************************
		mov c,beep_out
		mov acc.5,c     ;beep out at 595.5
		mov c, lamp_out	
		cpl c
		mov acc.6,c    ;lamp out at 595.6 
		mov c,ee_f
		cpl c
		mov acc.4,c    ;ee out at 595.4 
		mov r4,a
		call lcd_595
;************************************
		clr rck_m
		clr rck_r
		clr rck_f
		setb rck_m
		setb rck_r
		setb rck_f
		;**************** com_out

		mov a,m_count
		mov dptr,#lcd_tab
		movc a,@a+dptr
		mov p0,a
;*******************************
xc2:
		mov w_adj_1,#xu-10
		inc m_count
		mov a,m_count
		cjne a,#8,t0_int
		mov m_count,#0
		;call bin_lcd
		;call led
	t0_int:
		;call bin_lcd
		pop 01h
		pop 02h
		pop 03h
		pop 04h
		pop 05h
		pop 06h
		pop 07h
		pop 00h
		pop dpl
		pop dph
		ret
lcd_tab:
	db 10101000b
	db 10101011b
	db 10100010b
	db 10101110b
	db 10001010b
	db 10111010b
	db 00010101b
	db 11101010b
;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
lcd_595:
		mov r0,#04h
		mov r3,#03
	lcd_n1:			
		mov r7,#8d
		mov a,@r0
	lcd01:
		rlc a
		mov si_lcd,c
		clr sck_lcd
		nop
		setb sck_lcd
		djnz r7,lcd01
		inc r0
		djnz r3,lcd_n1
		ret
bin_lcd:
		jb llc_f,bin_lcd_end
		mov r0,#p0_buf
		mov r1,#p0_buf_bak
		mov r7,#24d
	bin_lcd1:
		mov a,@r0
		mov @r1,a
		inc r0
		inc r1
		djnz r7,bin_lcd1
		;mov w_adj_1,#xu+138
		ret
bin_lcd_end:
		;mov w_adj_1,#xu
		ret
;*******************************
		proc set_fh12	
set_fh12:
;***********************************
		clr menu1_over
		mov set_data,#0
		call led_blk
		call led_fh12		
	pass1:
		call led_fh12		
		call key_bord1
		call key_del
		call key_jmp12
		call clock
		call y1_count
		jnb menu1_over,pass1
		mov set_data,#0
		call clr_kd
		mov fh1_bak,fh1
		mov fh2_bak,fh2
		ret
		end
;*************************************
key_jmp12:
		mov a,key_data
		jnz kp12	
		ret	
	kp12:
		cjne a,#02,kp22;kb
		mov kc_data,#0
		inc set_data
		mov a,set_data
		cjne a,#02,kp22_1
		mov set_data,#0	
	kp22_1:
		ret						
	kp22:
		cjne a,#01,kp32;ka
		ret			
	kp32:
		cjne a,#03,kp422;kc
		mov r0,#fh1
		mov a,set_data
		add a,r0
		mov r0,a
		inc @r0
		mov a,@r0
		cjne a,#6,kp32_1  ;midf 2002.3.17
		mov @r0,#0	
	kp32_1:
		ret
	kp422:
		cjne a,#04,kp5221;kd
		mov dptr,#fh1_ee
		mov r2,#2
		mov r0,#fh1		
		call clr_wk
		setb menu1_over
	kp5221:
		ret		


led_fh12:
		;call led_blk
		mov led1,#05h
		mov led2,#n_led
		mov led3,fh1
		mov led4,fh2
		jb fl_250ms,led_fh12_end
		mov r0,#led3
		mov a,set_data
		add a,r0
		mov r0,a
		mov @r0,#black
led_fh12_end:
		call led
		ret
		
fh_to_led9:
		;0,p4,1,2,3 led9_h
		;0=no ,p4=led4+20h
		;0,p8,1,2,3 led9_l
		;0=no ,p8=led8+20h
		;abcdef_6     led10
;***************************************
		mov a,fh1
		jnz fhto1
	fhto1_1:
		mov a,led9
		anl a,#0fh
		mov led9,a
		sjmp fhto2
	fhto1:
		cjne a,#01,fhto13

		sjmp fhto1_1
	fhto13:
		mov dptr,#fh_asc
		dec a
		dec a
		movc a,@a+dptr
		mov b,a		
		mov a,led9
		anl a,#0fh
		orl a,b
		mov led9,a
;***********************************
	fhto2:	
		mov a,fh2
		jnz fhto122
	fhto2_1:
		mov a,led9
		anl a,#0f0h
		mov led9,a
		sjmp fhto222
	fhto122:
		cjne a,#01,fhto132
		sjmp fhto2_1
	fhto132:
		mov dptr,#fh_asc
		dec a
		dec a
		movc a,@a+dptr
		swap a ;;;;;;h=>l
		mov b,a		
		mov a,led9
		anl a,#0f0h
		orl a,b
		mov led9,a
	fhto222:
;****************** auto led ee_f trs h,l********
		jmp lcd_ee24		
fh_asc:
	db 10000000b
	db 01000000b
	db 00100000b
	db 00010000b
