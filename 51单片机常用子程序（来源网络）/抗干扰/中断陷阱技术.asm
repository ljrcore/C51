       ORG 0000H
       LJMP MAIN
       ORG 0003H
       LJMP PGINT0
       NOP
       NOP
       LJMP ERR
       ORG 000BH
       LJMP PGT0
       NOP
       NOP
       LJMP ERR
       ORG 0013H
       LJMP ERR              ;δʹ��
       NOP
       NOP
       LJMP ERR
       ORG OO1BH
       LJMP ERR            ;δʹ��
       NOP 
       NOP
       LJMP ERR
       ORG 0023H
       LJMP ERR        ;δʹ��
       NOP
       NOP
       LJMP ERR
  MAIM:
  ERR:LJMP MAIN     
       