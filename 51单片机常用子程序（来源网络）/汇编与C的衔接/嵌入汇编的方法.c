//keil c6.20c 直接嵌入汇编的方法!（C51BBS网友cuiwei）
//<asm.h>
#ifdef ASM
         unsigned long shiftR1(register unsigned long);
#else    
         extern unsigned long shiftR1(register unsigned long);
#endif
//end of asm.h

//<asm.c>
#define ASM
#include <asm.h>
#include <reg52.h>
#pragma OT(4,speed)
unsigned long    shiftR1(register unsigned long    x)
{
    #pragma asm
    clr c
    mov a,r4
    rrc a
    mov r4,a

    mov a,r5
    rrc a
    mov r5,a

    mov a,r6
    rrc a
    mov r6,a

    mov a,r7
    rrc a
    mov r7,a
    
    #pragma endasm
    return(x);
}
//end of asm.c
/*将此源文件加入要编译的工程文件，
//将光标指向此文件，选择右键菜单“option for file 'asm.c'”,
//将属性单“properties”中的“Generate Assembler SRC File”“Assemble SRC File”
//两项设置成黑体的“√”将“Link Public Only”的“√”去掉，再编译即可。
//用此方法可以在c源代码的任意位置用#pragma asm和#pragma endasm嵌入汇编语句。
//但要注意的是在直接使用形参时要小心，在不同的优化级别下产生的汇编代码有所不同，
//可以察看对应的.lst文件看一看，得到正确的优化级别后，#pragma OT(x,speed)锁定
//优化级别（这里的值是0-9）。


 
