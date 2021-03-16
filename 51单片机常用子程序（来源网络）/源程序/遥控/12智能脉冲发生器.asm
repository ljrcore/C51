;智能脉冲发生器源程序-2001年31期12版
   out bit p1.6
   increase bit p3.2
   decrease bit p3.3
   hi_fre data 50h
   lo_fre_hi data 51h
   lo_fre_lo data 52h
   lo_state data 53h
   hi_fre_temp data 54h
   lo_fre_temp data 55h

   org 0000h
   ajmp init

   org 001bh
   mov th1,#0feh        ;setup timer
   mov tl1,#0feh        ;setup timer
   push psw
   ajmp main
   
   org 0003h
   ajmp inc_adjust
   
   org 0013h
   ajmp dec_adjust

   org 0040h
init: mov hi_fre,#01h  ;set high frequence delay
   mov lo_fre_hi,#14h ;set low frequence high output
   mov lo_fre_lo,#20h ;set low frequence low output
   mov lo_state,#00h
   mov hi_fre_temp,#01h
   mov lo_fre_temp,#30h
   clr out 
;int0 and int1 setup
   setb it0
   setb it1
   setb ex0
   setb ex1
;timer setup   
   mov tmod,#11h
   mov th1,#0feh        ;setup timer
   mov tl1,#0feh        ;setup timer
   setb et1
   setb ea
   setb tr1
   sjmp $
;output singal with higher and lower frequence    
main: mov a,lo_state
     cjne a,#01h,out_lo
     djnz hi_fre_temp,exit
     mov a,hi_fre
     mov hi_fre_temp,a
     cpl out
     djnz lo_fre_temp,exit
     mov a,lo_fre_lo
     mov lo_fre_temp,a
     mov a,#00h
     mov lo_state,a      
     ajmp exit
out_lo: clr out
     djnz hi_fre_temp,exit
     mov a,hi_fre
     mov hi_fre_temp,a
     djnz lo_fre_temp,exit
     mov a,lo_fre_hi
     mov lo_fre_temp,a  
     mov a,#01h
mov lo_state,a      
exit: pop psw
    reti

;low level delay time increase adjust   
inc_adjust: mov a,lo_fre_lo
   cjne a,#30h,i1     ;setup maxium lower delay time
   mov a,#01h
   ajmp exit_i 
i1: inc a            ;setup increase interval
exit_i: mov lo_fre_lo,a
   reti
   
;low level delay time decrease adjust   
dec_adjust: mov a,lo_fre_lo
   cjne a,#01h,d1
   mov a,#30h    ;setup maxium lower delay time
   ajmp exit_d
d1:dec a          ;setup decrease interval
exit_d: mov lo_fre_lo,a
   reti
