;;;RAM��ĳ������
;������������
;��������������ݾ�Ϊ���ֽ����ݣ���������ⲿRAM�С�
;���������ʱ���Ĵ���R2��R3�������ҳ���Ӧ�������͵�R6��R2��R3�С�
;�������������64KB������λ�á�




FRAM_READ:MOV R6,#00H       ;�������ͷ��ַ
          MOV R7,#01H
          LCALL NSUB_SUB    ;������R2��R3����һ���͵�R4��R5��
          MOV A,R5
          MOV R7,A
          CLR C
          RLC A
          XCH A,R4
          MOV R6,A
          RLC A
          XCH A,R4
          ADD A,DPL
          MOV DPL,A
          MOV R3,A
          MOV A,DPH
          ADDC A,R4
          MOV DPH, A          ;�����㣺��R2R3��*2+��DPTR��
          MOV R3,A
          LCALL NADD_SUB
          MOV A,R4
          MOV DPH, A
          MOV A,R5
          MOV DPL,A 
          MOVX A,@DPTR    ;�����ȡ��һ���ֽڲ���R6��
          MOV R6,A
          INC DPTR
          MOVX A,@DPTR    ;�����ȡ��2���ֽڲ���R2��
          MOV R2,A
          INC DPTR
          MOVX A,@DPTR   ;;; ;�����ȡ��3���ֽڲ���R3��
          MOV R3,A
          RET
 NSUB_SUB:MOV A,R3
          CLR C
          SUBB A,R7
          MOV R5,A
          MOV A,R2
          SUBB A,R5
          MOV R4,A
          RET
 NADD_SUB:MOV A,R3
          ADD A,R7
          MOV R6,A
          MOV A,R3
          ADDC A,R6
          MOV R4,A
          RET
                   