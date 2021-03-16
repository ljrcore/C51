;通用宽行打印机检测及打印程序PPRNT（如SENTRONICS标准并行接口的EPSON LQ-570型，FX-800型）
;入口条件：设定外部中断（INT1)服务引导和开中断EA=1；欲打印数据放在片外
;RAM中，首地址放在片内RAM双字节71H，72H中；
；；每行打印数据以CR和LF命令分割；以03为打印结束标志。
；；出口条件：EX1=0时，打印结束


PPRNT:SETB INT1
      JB INT1,ERR9
      MOV A,,#0DH
      MOV DPTR,#PRTP   ；指向锁存器74LS377
      MOVX @DPTR,A
      CLR T1
      NOP
      SETB T1
      MOV RR3,#40
PPRT1:SETB INT1       
      JB INT1,PPRT2
      DJNZ R3,PPRT1
 ERR9:MOV A,#9
      ACALL DSERX   ；显示第9号ERROR
ERR91:LCALL DSPA
      JZ ERR91
      LJMP DIPA1
PPRT2:MOV 71H,#99H
      MOV 72H,#0
      SETB EX1
      RET
INT1SV:PUSH DPH
       PUSH DPL
       PUSH ACC
       PUSH PSW
       MOV DPH 71H
       MOV DPL 72H
       MOVX A,@DPTR
       INC DPTR
       MOV 71H,DPH
       MOV 72H,DPL
       CJNE A,#3,INT1SD
       CLR EX1
       SJMP INT1ED
INT1SD:MOV DPTR,#PRTP   ;;??
       MOVX @DPTR,A
       CLR T1
       NOP
       SETB T1
INT1ED:POP ACC
       POP PSW
       POP DPL
       POP DPH
       RETI                               