;;;将片内RAM50H-59H中的数据按从大到小的顺序排序



QUE:CLR 00H
    MOV R3,#9H     ;;;；10个数据循环次数
    MOV R0,#50H
    MOV A,@R0
 L2:INC R0
    MOV R2,A
    SUBB A,@R0
    MOV A,R2
    JNC L1
    SETB 00H
    XCH A,@R0
    DEC R0
    XCH A,@R0
    INC R0
 L1:MOV A,@R0
    DJNZ R3,L2
    JB 00H,QUE
    RET      