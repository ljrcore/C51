
；；；ADC0809模数转换， 将读数存放在A中



ADC0809:SETB IT1
        SETB EA
        SETB EX1
        MOV DPTR,#7FF8H     ；DAC0809首址
        MOVX @DPTR,A        ；启动AD转换
    HERE:SJMP HERE
    INT1:MOVX A,@DPTR
                      
         RETI
                   