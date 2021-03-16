;步进电机控制
;;；；；p1.4-p1.7控制a,b,c,d四个相位开关


          ORG 0000H
 MOT_DRVB:AJMP BEGIN_STR
          ORG 000BH
          LJMP TO_T0SEV
BEGIN_STR:MOV SP,#0D0H
          MOV 6CH,#N
          MOV 6DH,#90H
          ACALL STP_DRV
SOMP_PRG:
          SJMP SOMP_PRG
 STP_DRV:MOV A,6CH
         JZ FDRT_END
         RL A
         RL A
         INC A
         MOV 6CH,A
         MOV P1,#0F0H
         MOV TMOD ,#21H
         MOV TH0,#0EEH
         MOV TL0,#00H
         SETB EA
         SETB ET0
         SETB TR0
FDRT_END:RET
TO_T0SEV:PUSH ACC
         PUSH PSW
         JB 37H,TO_SV2
         MOV TH0,#0F8H
         MOV TL0,#0CDH
         MOV A,6DH
         MOV P1,A
         MOV C,ACC.4
         RRC A
         CLR ACC.3
         MOV 6DH,A
         DJNZ 6CH,TO_RET
  TO_SV2:MOV P1,#0F8H
         CLR ET0
         CLR TR0
         CLR 37H
 TO_RET:POP PSW
        POP ACC
        RETI        
               
                                            
