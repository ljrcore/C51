;;模数转换器AD7701的应用
；；；GETAD1是以外时钟方法查询接收AD7701数据的子程序

  GATAD1:SETB P1.4
         JNB P1.4,$-2
         SETB  P1.4
         JB P1.4,$-2
         CLR  P1.2
         MOV R2,#8
   GETL0:SETB P1.0
         MOV C,P1.0
         RLC A
         SETB P1.1
         CLR P1.1
         DJNZ R2,GETL0
         MOV R5,A
         MOV 2DH,A
         MOV R2,#8
   GETL1:SETB P1.0
         MOV C,P1.0
         RLC A
         SETB P1.1
         CLR P1.1
         DJNZ R2,GETL1
         SETB P1.2
         MOV R6,A
         MOV 2CH,A
  GADCOM:MOV R7,#0
         MOV R4,#80H
     GAD:MOV A,R5
         JB ACC.7,GETL2
         LCALL SHIF
         DJNZ R4,GAD
         RET
   GETL2:CLR  ACC.7
         MOV R5,A
         LCALL G10
         DEC R4
         DEC R4
         LCALL FPMU
         MOV A,R4
         RET


      ；；GETAD2是以单片机串行口接收AD7701数据的子程序
  GETAD2:MOV SCON ,#10
         MOV IE,#10H
         CLR RI
         MOV R0,#60H
         JB P1.4,$
         CLR P1.2
  INTLOP:JNB RI,$
         CLR RI
         MOV R7,#8
         MOV A,SBUF
  INTSL1:RLC A
         XCH A,@R0
         RRC A
         XCH A,@R0
         DJNZ R7,INTSL1
         INC R0
         CJNE R0,#62H,INTLOP
         SETB P1.2
         MOV R5,60H
         MOV R6,61H
         SJMP GADCOM        
         
         
         
                                                  