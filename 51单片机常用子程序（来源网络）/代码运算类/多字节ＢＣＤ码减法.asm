;Èë¿ÚÌõ¼þ£º×Ö½ÚÊýÔÚR7ÖÐ£¬±»¼õÊýÔÚ[R0]ÖÐ£¬¼õÊýÔÚ[R1]ÖÐ¡£
;³ö¿ÚÐÅÏ¢£º²îÔÚ[R0]ÖÐ£¬×î¸ßÎ»½èÎ»ÔÚCYÖÐ¡£
;Ó°Ïì×ÊÔ´£ºPSW¡¢A¡¢R2¡¢R3    ¶ÑÕ»ÐèÇó£º  £¶×Ö½Ú

BCDB:	LCALL	NEG1	;¼õÊý[R1]Ê®½øÖÆÈ¡²¹
	LCALL	BCDA	;°´¶à×Ö½Ú£Â£Ã£ÄÂë¼Ó·¨´¦Àí
	CPL	C	;½«²¹Âë¼Ó·¨µÄ½øÎ»±êÖ¾×ª»»³É½èÎ»±êÖ¾
	MOV	F0,C	;±;¤½èÎ»±êÖ¾
	LCALL	NEG1	;»Ö¸´¼õÊý[R1]µÄÔ­Ê¼Öµ
	MOV	C,F0    ;»Ö¸´½èÎ»±êÖ¾
	RET
NEG1:	MOV	A,R0	;[R1]Ê®½øÖÆÈ¡²¹×Ó³ÌÐòÈë¿Ú
	XCH	A,R1	;½»»»Ö¸Õë
	XCH	A,R0
	LCALL	NEG	;Í¨¹ý[R0]ÊµÏÖ[R1]È¡²¹
	MOV	A,R0
	XCH	A,R1	;»»»ØÖ¸Õë
	XCH	A,R0
	RET
;¶à×Ö½Ú£Â£Ã£ÄÂëÈ¡²¹
NEG:	MOV	A,R7	;È¡£¨×Ö½ÚÊý¼õÒ»£©ÖÁR2ÖÐ
	DEC	A
	MOV	R2,A
	MOV	A,R0	;±;¤Ö¸Õë
	MOV	R3,A
NEG0:	CLR	C	
	MOV	A,#99H
	SUBB	A,@R0	;°´×Ö½ÚÊ®½øÖÆÈ¡²¹
	MOV	@R0,A	;´æ»Ø[R0]ÖÐ
	INC	R0	;µ÷ÕûÊý¾ÝÖ¸Õë
	DJNZ	R2,NEG0	;´¦ÀíÍê£¨R2£©×Ö½Ú
	MOV	A,#9AH	;×îµÍ×Ö½Úµ¥¶ÀÈ¡²¹
	SUBB	A,@R0
	MOV	@R0,A
	MOV	A,R3	;»Ö¸´Ö¸Õë
	MOV	R0,A
	RET
;¶à×Ö½ÚBCDÂë¼Ó·¨
	BCDA:	MOV	A,R7	;È¡×Ö½ÚÊýÖÁR2ÖÐ
	MOV	R2,A
	ADD	A,R0	;³õÊ¼»¯Êý¾ÝÖ¸Õë
	MOV	R0,A
	MOV	A,R2
	ADD	A,R1
	MOV	R1,A
	CLR	C
BCD1:	DEC	R0	;µ÷ÕûÊý¾ÝÖ¸Õë
	DEC	R1
	MOV	A,@R0
	ADDC	A,@R1	;°´×Ö½ÚÏà¼Ó
	DA	A	;Ê®½øÖÆµ÷Õû
	MOV	@R0,A	;ºÍ´æ»Ø[R0]ÖÐ
	DJNZ	R2,BCD1	;´¦ÀíÍêËùÓÐ×Ö½Ú
	RET