;;;11路12位串行输出A/D转换器TLC2543
；；；



        ORG 1000H
        AD_CS  BIT P1.0   ；定义I/O口
        AD_CLK  BIT P1.1
        AD_EOC  BIT P1.4
        AD_OUT  BIT P1.3
        AD_IN  BIT P1.2
        AD_L    EQU   40H   ；；定义A/D转换的低字节
        AD_H    EQU   41H    ；；定义A/D转换的高字节
        AD_AB    EQU   42H    ；；定义A/D转换器的输入地址
 ADCONB:CLR    AD_CS 
        MOV   AD_L,#00H
        MOV     AD_H,#00H
        CLR    AD_CLK        ；；设置AD-CLK 为低电平
        MOV    R5,#08H
        LCALL  A_DELAY4
C_AD_CN1:LCALL  A_DELAY1              
         MOV  C,  AD_OUT
         MOV A,  AD_H
         RLC A
         MOV   AD_H,A
         MOV   A,  AD_AB
         RLC  A
         MOV    AD_IN,C
         MOV      AD_AB,A
         SETB   AD_CLK
         LCALL  A_DELAY1
         CLR      AD_CLK
         DJNZ  C_AD_CN1
         MOV   R5,#04H
         CLR    AD_IN
C_AD_CN2:LCALL A_DELAY1
         MOV C ,  AD_OUT
         MOV A,  AD_L
         RLC   A
         MOV   AD_L,A
         SETB  AD_CLK
         LCALL A_DELAY1
         CLR    AD_CLK
         DJNZ R5,C_AD_CN2
         SETB AD_CS
         MOV R5,#04H
         CLR C
         ANL   AD_L,#0FH
         MOV B,  AD_L
C_AD_CN3:MOV A,  AD_H
         RRC A
         MOV   AD_H,A
         MOV A,  AD_L
         DJNZ R5,C_AD_CN3
         ANL AD_L,#0F0H
         MOV A,B
         ORL  AD_H,#0FH                  
         RET
 ADCON_0:JNB AD_EOC,ADCON_0
         MOV AD_AB,#00H
         LCALL ADCONB
         LCALL A_DELAY1
         RET
A_DELAY1:MOV R7,#10H
 C_DELAY:DJNZ R7, C_DELAY                        
         RET
         
         
         
         
         
         
         
         
         
         
         
         