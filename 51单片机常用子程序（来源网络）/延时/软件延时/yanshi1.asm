;æß’Ò11.0592      hz,—” ±1s


         MOV 70H,200
   LOOP2:MOV 71H,#100
   LOOP3:MOV 72H,#21
   LOOP4:DJNZ 72H,LOOP4
         DJNZ 71H,LOOP3
         NOP
         NOP
         NOP
         NOP
         DJNZ 70H,LOOP2
               
