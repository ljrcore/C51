;;;RAM表的程序设计
;；；；读出表
;；；；设表格的数据均为三字节数据，表格存放于外部RAM中。
;；；；查表时按寄存器R2，R3的内容找出对应的数据送到R6，R2，R3中。
;；；；表格存放于64KB的任意位置。




FRAM_READ:MOV R6,#00H       ;；计算表头地址
          MOV R7,#01H
          LCALL NSUB_SUB    ;；将（R2，R3）减一后送到R4，R5中
          MOV A,R5
          MOV R7,A
          CLR C
          RLC A
          XCH A,R4
          MOV R6,A
          RLC A
          XCH A,R4
          ADD A,DPL
          MOV DPL,A
          MOV R3,A
          MOV A,DPH
          ADDC A,R4
          MOV DPH, A          ;；计算：（R2R3）*2+（DPTR）
          MOV R3,A
          LCALL NADD_SUB
          MOV A,R4
          MOV DPH, A
          MOV A,R5
          MOV DPL,A 
          MOVX A,@DPTR    ;；查表取第一个字节并送R6中
          MOV R6,A
          INC DPTR
          MOVX A,@DPTR    ;；查表取第2个字节并送R2中
          MOV R2,A
          INC DPTR
          MOVX A,@DPTR   ;;; ;；查表取第3个字节并送R3中
          MOV R3,A
          RET
 NSUB_SUB:MOV A,R3
          CLR C
          SUBB A,R7
          MOV R5,A
          MOV A,R2
          SUBB A,R5
          MOV R4,A
          RET
 NADD_SUB:MOV A,R3
          ADD A,R7
          MOV R6,A
          MOV A,R3
          ADDC A,R6
          MOV R4,A
          RET
                   