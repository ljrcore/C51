;             ¼ÒÓÃ·ÀµÁ±¨¾¯Æ÷Ô´³ÌÐòÇåµ¥
;’„
        ORG  0000H         
        AJMP MAIN           
        ORG  001BH     
        LJMP WT0
        ORG  30H

MAIN:   MOV  SP,#50H 
        MOV 20H,#0
        MOV 24H,#0
        MOV  P3,#0
        MOV  P1,#0
        MOV  TH0,#6        
        MOV  TL0,#6
        MOV  TMOD,#02H
        SETB EA
        SETB ET0
        SETB TR0
M:      MOV P1,#00H
        MOV A,P3
        ANL A,#7FH
        CJNE A,#7FH,W37
        AJMP M  
                           
WT0:    PUSH ACC
        PUSH PSW
        INC 22H                 
        MOV A,22H
        CJNE A,#200,TORETI 
        MOV 22H,#0
        INC 23H                 
        MOV A,23H
        CJNE A,#10,TORETI       ;1s   
        MOV 23H,#0              
        JNB 00H,WBJ
TORETI: POP PSW
        POP ACC
        RETI
WBJ:    CPL P3.7
        AJMP TORETI             
W37:    INC 24H
	MOV A,24H
        CJNE A,#10,M
        SETB 00H
        AJMP M
        END
 
                                              - Íõ°®Á® - 

                                                          99-10-7
ÔÊ¾µ÷ÊÔ´°¿ÚÒÔºó,°´<F3>¼ü,µ÷Èë¡°L06.ASM¡±Š,°´<F9>¼ü½øÐÐ»ã±à¡£3.°´<ALT>+<F>¼ü½«¡°L06.ASM¡±×ª»»³É±à³ÌÆ÷ÐèÒªµÄ¸ñÊ½µÄŠÎÄ¼þ¡£Ñ¡Ôñ¡°Save OBJ as....¡±Ïî,°´»Ø³µ¼ü´ý³öÏÖÑ¡Ôñ´°¿Úºó,°´<Esc>¼üÈ·¶¨ÎÄŠ¼þÃûºÍÎÄ¼þ¸ñÊ½¡£ÎÄ¼þ¸ñÊ½Ñ¡¡°(.)ROM¡±,È»ºó´æÅÌ¡£4.°´<Esc>¼üÇ°ÍËÒ»²½¡£5.°´Š<Alt>+<X>¼ü·µ»ØDOSÏµÍ³¡£
    ÓÃÒÔÇ°½éÉÜµÄ·½·¨½«¡°L06.ROM¡±¸ñÊ½µÄÎÄ¼þ¹Ì»¯ÔÚAT89C2051ÖÐ¡£
    Ó²¼þµ÷ÊÔ:1.¼ì²éÏßÂ·Ó¦º¸½ÓÎÞÎó¡£2.ÏÈ²»²åÈëAT89C2051,ÓÃ¶ÌÂ·Ïß°ÑD1²å×ùŠµÄ(12)½Å½ÓµØ£¬µ÷ÕûL1ºÍV1µÄ°²×°Î»ÖÃºÍ½Ç¶È£¬²âÁ¿D1²å×ùµÄ(2)½ÅµçÑ¹£¬L1ºÍV1ŠÖ®¼äÎÞÕÚµ²Ê±(2)½ÅµçÑ¹Ô¼Îª0V£¬ÓÐÕÚµ²Ê±(2)½ÅµçÑ¹´óÓÚ4V¡£ÓÃÏàÍ¬·½·¨·´¸´µ÷ÕûŠÆäËû¼¸¶ÔºìÍâÊÕ·¢¹ÜµÄÎ»ÖÃºÍ½Ç¶È£¬Ê¹D1²å×ùµÄ(3)(6)(7)(8)(9)¸÷½ÅµÄµçÑ¹·ûºÏŠÒªÇó¡£ ½«Ð´Èë³ÌÐòµÄAT89C2051²åÈëµçÂ·ÖÐµÄIC²å×ùÉÏ£¬½ÓÍ¨µçÔ´¼´¿É¹¤×÷¡£


 
                                              - Íõ°®Á® - 

                                                          99-10-7
¼þµ÷ÊÔ:1.¼ì²éÏßÂ·Ó¦º¸½ÓÎÞÎó¡£2.ÏÈ²»²åÈëAT89C2051,ÓÃ¶ÌÂ·Ïß°ÑD1²å×ùµÄŠ(12)½Å½ÓµØ£¬µ÷ÕûL1ºÍV1µÄ°²×°Î»ÖÃºÍ½Ç¶È£¬²âÁ¿D1²å×ùµÄ(2)½ÅµçÑ¹£¬L1ºÍV1Ö®¼äŠÎÞÕÚµ²Ê±(2)½ÅµçÑ¹Ô¼Îª0V£¬ÓÐÕÚµ²Ê±(2)½ÅµçÑ¹´óÓÚ4V¡£ÓÃÏàÍ¬·½·¨·´¸´µ÷ÕûÆäËû¼¸Š¶ÔºìÍâÊÕ·¢¹ÜµÄÎ»ÖÃºÍ½Ç¶È£¬Ê¹D1²å×ùµÄ(3)(6)(7)(8)(9)¸÷½ÅµÄµçÑ¹·ûºÏÒªÇó¡£ ½«ŠÐ´Èë³ÌÐòµÄAT89C2051²åÈëµçÂ·ÖÐµÄIC²å×ùÉÏ£¬½ÓÍ¨µçÔ´¼´¿É¹¤×÷¡£


 
                                              - Ï¦Ñô - 

                                                          99-10-7
