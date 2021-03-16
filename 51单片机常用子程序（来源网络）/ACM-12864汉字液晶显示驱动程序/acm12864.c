//ACM-12864汉字液晶显示驱动程序


sbit p_csa=P2^6;
sbit p_csb=P2^7;
sbit p_gnda=P2^5;
sbit p_gndb=P2^4;
sbit p_di=P2^3;
sbit p_rw=P2^2;
sbit p_e=P2^1;


/*忙判别*/
void lcd_busy(void) {
	p_di=0;p_rw=1;P0=0xff;
	while (1) {
		p_e=1;
		if (P0<0x80) break;
		p_e=0;
	} 
	p_e=0;
}
/*设置xy*/
void set_xy(unsigned char x,unsigned char y) {
	if (x>=64) {p_csa=0;p_csb=1;} else {p_csb=0;p_csa=1;}
	lcd_busy();
	p_di=p_rw=0;P0=0x40|x;p_e=1;p_e=0;
	lcd_busy();
	p_di=p_rw=0;P0=0xb8|y;p_e=1;p_e=0;
	P0=0xff;
}
void lw(unsigned char x,unsigned char y,unsigned char dd) {
	set_xy(x,y);
	lcd_busy();p_di=1;p_rw=0;P0=dd;p_e=1;p_e=0;
	P0=0xff;
}
/*显示初始化*/
#pragma disable
void lcd_init(void) {
	unsigned char x,y;
	p_gnda=p_gndb=0;
	/*开显示*/
	p_e=p_di=p_rw=0;
	p_csa=p_csb=0;
	p_csa=1;P0=0x3f;p_e=1;p_e=0;p_csa=0;
	p_csb=1;P0=0x3f;p_e=1;p_e=0;p_csb=0;
	/*0行开始显示*/
	p_csa=1;lcd_busy();p_di=p_rw=0;P0=0xc0;p_e=1;p_e=0;p_csa=0;
	p_csb=1;lcd_busy();p_di=p_rw=0;P0=0xc0;p_e=1;p_e=0;p_csb=0;
	for (y=0;y<8;y++) {
		for (x=0;x<128;x++) lw(x,y,0);
	}
}


unsigned char code asc[]={
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x38,0xfc,0xfc,0x38,0x0,0x0,0x0,0x0,0x0,0xd,0xd,0x0,0x0,0x0,
0x0,0xe,0x1e,0x0,0x0,0x1e,0xe,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x20,0xf8,0xf8,0x20,0xf8,0xf8,0x20,0x0,0x2,0xf,0xf,0x2,0xf,0xf,0x2,0x0,
0x38,0x7c,0x44,0x47,0x47,0xcc,0x98,0x0,0x6,0xc,0x8,0x38,0x38,0xf,0x7,0x0,
0x30,0x30,0x0,0x80,0xc0,0x60,0x30,0x0,0xc,0x6,0x3,0x1,0x0,0xc,0xc,0x0,
0x80,0xd8,0x7c,0xe4,0xbc,0xd8,0x40,0x0,0x7,0xf,0x8,0x8,0x7,0xf,0x8,0x0,
0x0,0x10,0x1e,0xe,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0xf0,0xf8,0xc,0x4,0x0,0x0,0x0,0x0,0x3,0x7,0xc,0x8,0x0,0x0,
0x0,0x0,0x4,0xc,0xf8,0xf0,0x0,0x0,0x0,0x0,0x8,0xc,0x7,0x3,0x0,0x0,
0x80,0xa0,0xe0,0xc0,0xc0,0xe0,0xa0,0x80,0x0,0x2,0x3,0x1,0x1,0x3,0x2,0x0,
0x0,0x80,0x80,0xe0,0xe0,0x80,0x80,0x0,0x0,0x0,0x0,0x3,0x3,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x10,0x1e,0xe,0x0,0x0,0x0,
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xc,0xc,0x0,0x0,0x0,
0x0,0x0,0x0,0x80,0xc0,0x60,0x30,0x0,0xc,0x6,0x3,0x1,0x0,0x0,0x0,0x0,
0xf0,0xf8,0xc,0xc4,0xc,0xf8,0xf0,0x0,0x3,0x7,0xc,0x8,0xc,0x7,0x3,0x0,
0x0,0x10,0x18,0xfc,0xfc,0x0,0x0,0x0,0x0,0x8,0x8,0xf,0xf,0x8,0x8,0x0,
0x8,0xc,0x84,0xc4,0x64,0x3c,0x18,0x0,0xe,0xf,0x9,0x8,0x8,0xc,0xc,0x0,
0x8,0xc,0x44,0x44,0x44,0xfc,0xb8,0x0,0x4,0xc,0x8,0x8,0x8,0xf,0x7,0x0,
0xc0,0xe0,0xb0,0x98,0xfc,0xfc,0x80,0x0,0x0,0x0,0x0,0x8,0xf,0xf,0x8,0x0,
0x7c,0x7c,0x44,0x44,0x44,0xc4,0x84,0x0,0x4,0xc,0x8,0x8,0x8,0xf,0x7,0x0,
0xf0,0xf8,0x4c,0x44,0x44,0xc0,0x80,0x0,0x7,0xf,0x8,0x8,0x8,0xf,0x7,0x0,
0xc,0xc,0x4,0x84,0xc4,0x7c,0x3c,0x0,0x0,0x0,0xf,0xf,0x0,0x0,0x0,0x0,
0xb8,0xfc,0x44,0x44,0x44,0xfc,0xb8,0x0,0x7,0xf,0x8,0x8,0x8,0xf,0x7,0x0,
0x38,0x7c,0x44,0x44,0x44,0xfc,0xf8,0x0,0x0,0x8,0x8,0x8,0xc,0x7,0x3,0x0,
0x0,0x0,0x0,0x30,0x30,0x0,0x0,0x0,0x0,0x0,0x0,0x6,0x6,0x0,0x0,0x0,
0x0,0x0,0x0,0x30,0x30,0x0,0x0,0x0,0x0,0x0,0x8,0xe,0x6,0x0,0x0,0x0,
0x0,0x80,0xc0,0x60,0x30,0x18,0x8,0x0,0x0,0x0,0x1,0x3,0x6,0xc,0x8,0x0,
0x0,0x20,0x20,0x20,0x20,0x20,0x20,0x0,0x0,0x1,0x1,0x1,0x1,0x1,0x1,0x0,
0x0,0x8,0x18,0x30,0x60,0xc0,0x80,0x0,0x0,0x8,0xc,0x6,0x3,0x1,0x0,0x0,
0x18,0x1c,0x4,0xc4,0xe4,0x3c,0x18,0x0,0x0,0x0,0x0,0xd,0xd,0x0,0x0,0x0,
0xf0,0xf8,0x8,0xc8,0xc8,0xf8,0xf0,0x0,0x7,0xf,0x8,0xb,0xb,0xb,0x1,0x0,
0xe0,0xf0,0x98,0x8c,0x98,0xf0,0xe0,0x0,0xf,0xf,0x0,0x0,0x0,0xf,0xf,0x0,
0x4,0xfc,0xfc,0x44,0x44,0xfc,0xb8,0x0,0x8,0xf,0xf,0x8,0x8,0xf,0x7,0x0,
0xf0,0xf8,0xc,0x4,0x4,0xc,0x18,0x0,0x3,0x7,0xc,0x8,0x8,0xc,0x6,0x0,
0x4,0xfc,0xfc,0x4,0xc,0xf8,0xf0,0x0,0x8,0xf,0xf,0x8,0xc,0x7,0x3,0x0,
0x4,0xfc,0xfc,0x44,0xe4,0xc,0x1c,0x0,0x8,0xf,0xf,0x8,0x8,0xc,0xe,0x0,
0x4,0xfc,0xfc,0x44,0xe4,0xc,0x1c,0x0,0x8,0xf,0xf,0x8,0x0,0x0,0x0,0x0,
0xf0,0xf8,0xc,0x84,0x84,0x8c,0x98,0x0,0x3,0x7,0xc,0x8,0x8,0x7,0xf,0x0,
0xfc,0xfc,0x40,0x40,0x40,0xfc,0xfc,0x0,0xf,0xf,0x0,0x0,0x0,0xf,0xf,0x0,
0x0,0x0,0x4,0xfc,0xfc,0x4,0x0,0x0,0x0,0x0,0x8,0xf,0xf,0x8,0x0,0x0,
0x0,0x0,0x0,0x4,0xfc,0xfc,0x4,0x0,0x7,0xf,0x8,0x8,0xf,0x7,0x0,0x0,
0x4,0xfc,0xfc,0xc0,0xe0,0x3c,0x1c,0x0,0x8,0xf,0xf,0x0,0x1,0xf,0xe,0x0,
0x4,0xfc,0xfc,0x4,0x0,0x0,0x0,0x0,0x8,0xf,0xf,0x8,0x8,0xc,0xe,0x0,
0xfc,0xfc,0x38,0x70,0x38,0xfc,0xfc,0x0,0xf,0xf,0x0,0x0,0x0,0xf,0xf,0x0,
0xfc,0xfc,0x38,0x70,0xe0,0xfc,0xfc,0x0,0xf,0xf,0x0,0x0,0x0,0xf,0xf,0x0,
0xf8,0xfc,0x4,0x4,0x4,0xfc,0xf8,0x0,0x7,0xf,0x8,0x8,0x8,0xf,0x7,0x0,
0x4,0xfc,0xfc,0x44,0x44,0x7c,0x38,0x0,0x8,0xf,0xf,0x8,0x0,0x0,0x0,0x0,
0xf8,0xfc,0x4,0x4,0x4,0xfc,0xf8,0x0,0x7,0xf,0x8,0xe,0x3c,0x3f,0x27,0x0,
0x4,0xfc,0xfc,0x44,0xc4,0xfc,0x38,0x0,0x8,0xf,0xf,0x0,0x0,0xf,0xf,0x0,
0x18,0x3c,0x64,0x44,0xc4,0x9c,0x18,0x0,0x6,0xe,0x8,0x8,0x8,0xf,0x7,0x0,
0x0,0x1c,0xc,0xfc,0xfc,0xc,0x1c,0x0,0x0,0x0,0x8,0xf,0xf,0x8,0x0,0x0,
0xfc,0xfc,0x0,0x0,0x0,0xfc,0xfc,0x0,0x7,0xf,0x8,0x8,0x8,0xf,0x7,0x0,
0xfc,0xfc,0x0,0x0,0x0,0xfc,0xfc,0x0,0x1,0x3,0x6,0xc,0x6,0x3,0x1,0x0,
0xfc,0xfc,0x0,0xc0,0x0,0xfc,0xfc,0x0,0x7,0xf,0xe,0x3,0xe,0xf,0x7,0x0,
0xc,0x3c,0xf0,0xe0,0xf0,0x3c,0xc,0x0,0xc,0xf,0x3,0x1,0x3,0xf,0xc,0x0,
0x0,0x3c,0x7c,0xc0,0xc0,0x7c,0x3c,0x0,0x0,0x0,0x8,0xf,0xf,0x8,0x0,0x0,
0x1c,0xc,0x84,0xc4,0x64,0x3c,0x1c,0x0,0xe,0xf,0x9,0x8,0x8,0xc,0xe,0x0,
0x0,0x0,0xfc,0xfc,0x4,0x4,0x0,0x0,0x0,0x0,0xf,0xf,0x8,0x8,0x0,0x0,
0x38,0x70,0xe0,0xc0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x3,0x7,0xe,0x0,
0x0,0x0,0x4,0x4,0xfc,0xfc,0x0,0x0,0x0,0x0,0x8,0x8,0xf,0xf,0x0,0x0,
0x8,0xc,0x6,0x3,0x6,0xc,0x8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x0,0x0,0x3,0x7,0x4,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0xa0,0xa0,0xa0,0xe0,0xc0,0x0,0x0,0x7,0xf,0x8,0x8,0x7,0xf,0x8,0x0,
0x4,0xfc,0xfc,0x20,0x60,0xc0,0x80,0x0,0x0,0xf,0xf,0x8,0x8,0xf,0x7,0x0,
0xc0,0xe0,0x20,0x20,0x20,0x60,0x40,0x0,0x7,0xf,0x8,0x8,0x8,0xc,0x4,0x0,
0x80,0xc0,0x60,0x24,0xfc,0xfc,0x0,0x0,0x7,0xf,0x8,0x8,0x7,0xf,0x8,0x0,
0xc0,0xe0,0xa0,0xa0,0xa0,0xe0,0xc0,0x0,0x7,0xf,0x8,0x8,0x8,0xc,0x4,0x0,
0x40,0xf8,0xfc,0x44,0xc,0x18,0x0,0x0,0x8,0xf,0xf,0x8,0x0,0x0,0x0,0x0,
0xc0,0xe0,0x20,0x20,0xc0,0xe0,0x20,0x0,0x27,0x6f,0x48,0x48,0x7f,0x3f,0x0,0x0,
0x4,0xfc,0xfc,0x40,0x20,0xe0,0xc0,0x0,0x8,0xf,0xf,0x0,0x0,0xf,0xf,0x0,
0x0,0x0,0x20,0xec,0xec,0x0,0x0,0x0,0x0,0x0,0x8,0xf,0xf,0x8,0x0,0x0,
0x0,0x0,0x0,0x0,0x20,0xec,0xec,0x0,0x0,0x30,0x70,0x40,0x40,0x7f,0x3f,0x0,
0x4,0xfc,0xfc,0x80,0xc0,0x60,0x20,0x0,0x8,0xf,0xf,0x1,0x3,0xe,0xc,0x0,
0x0,0x0,0x4,0xfc,0xfc,0x0,0x0,0x0,0x0,0x0,0x8,0xf,0xf,0x8,0x0,0x0,
0xe0,0xe0,0x60,0xc0,0x60,0xe0,0xc0,0x0,0xf,0xf,0x0,0x7,0x0,0xf,0xf,0x0,
0x20,0xe0,0xc0,0x20,0x20,0xe0,0xc0,0x0,0x0,0xf,0xf,0x0,0x0,0xf,0xf,0x0,
0xc0,0xe0,0x20,0x20,0x20,0xe0,0xc0,0x0,0x7,0xf,0x8,0x8,0x8,0xf,0x7,0x0,
0x20,0xe0,0xc0,0x20,0x20,0xe0,0xc0,0x0,0x40,0x7f,0x7f,0x48,0x8,0xf,0x7,0x0,
0xc0,0xe0,0x20,0x20,0xc0,0xe0,0x20,0x0,0x7,0xf,0x8,0x48,0x7f,0x7f,0x40,0x0,
0x20,0xe0,0xc0,0x60,0x20,0xe0,0xc0,0x0,0x8,0xf,0xf,0x8,0x0,0x0,0x0,0x0,
0x40,0xe0,0xa0,0x20,0x20,0x60,0x40,0x0,0x4,0xc,0x9,0x9,0xb,0xe,0x4,0x0,
0x20,0x20,0xf8,0xfc,0x20,0x20,0x0,0x0,0x0,0x0,0x7,0xf,0x8,0xc,0x4,0x0,
0xe0,0xe0,0x0,0x0,0xe0,0xe0,0x0,0x0,0x7,0xf,0x8,0x8,0x7,0xf,0x8,0x0,
0x0,0xe0,0xe0,0x0,0x0,0xe0,0xe0,0x0,0x0,0x3,0x7,0xc,0xc,0x7,0x3,0x0,
0xe0,0xe0,0x0,0x80,0x0,0xe0,0xe0,0x0,0x7,0xf,0xc,0x7,0xc,0xf,0x7,0x0,
0x20,0x60,0xc0,0x80,0xc0,0x60,0x20,0x0,0x8,0xc,0x7,0x3,0x7,0xc,0x8,0x0,
0xe0,0xe0,0x0,0x0,0x0,0xe0,0xe0,0x0,0x47,0x4f,0x48,0x48,0x68,0x3f,0x1f,0x0,
0x60,0x60,0x20,0xa0,0xe0,0x60,0x20,0x0,0xc,0xe,0xb,0x9,0x8,0xc,0xc,0x0,
0x0,0x40,0x40,0xf8,0xbc,0x4,0x4,0x0,0x0,0x0,0x0,0x7,0xf,0x8,0x8,0x0,
0x0,0x0,0x0,0xbc,0xbc,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0xf,0x0,0x0,0x0,
0x0,0x4,0x4,0xbc,0xf8,0x40,0x40,0x0,0x0,0x8,0x8,0xf,0x7,0x0,0x0,0x0,
0x8,0xc,0x4,0xc,0x8,0xc,0x4,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x80,0xc0,0x60,0x30,0x60,0xc0,0x80,0x0,0x7,0x7,0x4,0x4,0x4,0x7,0x7,0x0
};


unsigned char code hz[]={
/*解:	0*/
0x20,0x10,0xec,0x27,0xf4,0x2c,0xe4,0x40,
0x22,0x9e,0x2,0xd2,0x22,0x1f,0x2,0x0,
0x80,0x40,0x3f,0x9,0x3f,0x89,0xff,0x8,
0xa,0x9,0x9,0xff,0x9,0x9,0x8,0x0
};


//显示汉字，fb==1:反白显示
void dh(unsigned char x,unsigned char y,unsigned char n,unsigned char fb) {
	unsigned char i,dd;
	for (i=0;i<16;i++) {
		dd=hz[i+n*32];
		if (fb) if (n!=kongbai) dd=255-dd;
		lw(x*8+i,y,dd);
		dd=hz[i+n*32+16];
		if (fb) if (n!=kongbai) dd=255-dd;
		lw(x*8+i,y+1,dd);
	}
}

//显示字符，fb==1:反白显示
void da(unsigned char x,unsigned char y,unsigned char n,unsigned char fb) {
	unsigned char i,dd;
	n-=32;
	if (n>128) n=0;
	if (fb) dd=255; else dd=0; 
	lw(x*8,y,dd);
	lw(x*8,y+1,dd);
	for (i=0;i<7;i++) {
		dd=asc[i+n*16];
		if (fb) dd=255-dd; 
		lw(x*8+i+1,y,dd);
		dd=asc[i+n*16+8];
		if (fb) dd=255-dd; 
		lw(x*8+i+1,y+1,dd);
	}
}








