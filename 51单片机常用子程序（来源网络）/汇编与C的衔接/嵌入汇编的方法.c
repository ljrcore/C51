//keil c6.20c ֱ��Ƕ����ķ���!��C51BBS����cuiwei��
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
/*����Դ�ļ�����Ҫ����Ĺ����ļ���
//�����ָ����ļ���ѡ���Ҽ��˵���option for file 'asm.c'��,
//�����Ե���properties���еġ�Generate Assembler SRC File����Assemble SRC File��
//�������óɺ���ġ��̡�����Link Public Only���ġ��̡�ȥ�����ٱ��뼴�ɡ�
//�ô˷���������cԴ���������λ����#pragma asm��#pragma endasmǶ������䡣
//��Ҫע�������ֱ��ʹ���β�ʱҪС�ģ��ڲ�ͬ���Ż������²����Ļ�����������ͬ��
//���Բ쿴��Ӧ��.lst�ļ���һ�����õ���ȷ���Ż������#pragma OT(x,speed)����
//�Ż����������ֵ��0-9����


 
