;中值滤波，采样值分别放在R2，r3，r4中，
结果从小到大排序放在R2，R3，R4中
 ；R3为中值 
 FILT2:MOV A,R2
       CLR C
       SUBB A,R3
       JC FILT21
       MOV A,R2
       XCH A,R3
       MOV R2,A
FILT21:MOV A,R3
       CLR C
       SUBB A,R4
       JC FILT22
       MOV A,R4
       XCH A,R3
       XCH R4,A
       CLR C
       SUBB A,R2
       JNC FILT22
       MOV A,R2
       MOV R3,A
FILT22:RET             
      
