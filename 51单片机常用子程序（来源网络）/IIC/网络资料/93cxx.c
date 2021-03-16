//------------------------------------------
/*通用93c06-93c86系列		普通封装*/
//93c01=93c46
//93c56=93c66
//93c76=93c86
//dipx 可以自行定义
#define di_93 dip3 
#define sk_93 dip2
#define cs_93 dip1
#define do_93 dip4
#define gnd_93 dip5
#define org_93	dip6

void high46(void){
	di_93=1;
	sk_93=1;nop;sk_93=0;
	nop;
}
void low46(void){
	di_93=0;
	sk_93=1;nop;sk_93=0;
	nop;
}
void wd46(unsigned char dd){
	unsigned char i;
	for (i=0;i<8;i++) {
		if (dd>=0x80) high46(); else low46();
		dd=dd<<1;
	}
}
unsigned char rd46(void){
	unsigned char i,dd;
	do_93=1;
	for (i=0;i<8;i++) {
		dd<<=1;
		sk_93=1;nop;sk_93=0;
		nop;
		if (do_93) dd|=1;
	}
	return(dd);
}

void ewen46(void){
	nop;
	cs_93=1;
	high46();
	wd46(0x30);
	cs_93=0;
}


//特殊封装
#define di_93a dip5
#define sk_93a dip4
#define cs_93a dip3
#define do_93a dip6
#define gnd_93a dip7
#define vcc_93a out_vcc(2)

void high46a(void){
	di_93a=1;
	sk_93a=1;nop;sk_93a=0;
	nop;
}
void low46a(void){
	di_93a=0;
	sk_93a=1;nop;sk_93a=0;
	nop;
}
void wd46a(unsigned char dd){
	unsigned char i;
	for (i=0;i<8;i++) {
		if (dd>=0x80) high46a(); else low46a();
		dd=dd<<1;
	}
}
unsigned char rd46a(void){
	unsigned char i,dd;
	do_93a=1;
	for (i=0;i<8;i++) {
		dd<<=1;
		sk_93a=1;nop;sk_93a=0;nop;
		if (do_93a) dd|=1;
	}
	return(dd);
}


unsigned int read93c46_word(unsigned char address) {
	unsigned int dat;
	unsigned char dat0,dat1;
	gnd_93a=0;
	gnd_93=0;
	cs_93=sk_93=0;org_93=1;cs_93=1;
	nop;
	address=address>>1;
	address=address|0x80;
	high46();
	wd46(address);dat1=rd46();dat0=rd46();
	cs_93=0;dat=dat1*256+dat0;
	return(dat);
}


bit write93c46_word(unsigned char address,unsigned int dat){
	unsigned char e,temp=address;
	e=0;
	while (e<3) {
		gnd_93a=0;
		gnd_93=0;
		cs_93=sk_93=0;org_93=1;cs_93=1;
		ewen46();
		nop;
		cs_93=1;
		nop;
		high46();
		address|=0x80;
		address>>=1;
		wd46(address);wd46(dat/256);wd46(dat%256);
		cs_93=0;nop;cs_93=1;
		time=0;do_93=1;
		while (1) {
			if (do_93==1) break;
			if (time>20) break;
		}
		cs_93=0;
		if (read93c46_word(temp)==dat) {
			return(0);
		}
		e++;
	}
	return(1);
}




//=============================================================
	//93c57
void ewen57(void){
	nop;
	cs_93=1;
	dip7=0;
	high46();
	low46();
	wd46(0x60);
	cs_93=0;
}

unsigned int read93c57_word(unsigned int address) {
	unsigned int dat;
	unsigned char dat0,dat1;
	gnd_93=0;
	cs_93=sk_93=0;org_93=1;cs_93=1;
	address=address>>1;
	high46();
	high46();
	wd46(address);dat1=rd46();dat0=rd46();
	cs_93=0;dat=dat1*256+dat0;
	return(dat);
}

bit write93c57_word(unsigned int address,unsigned int dat){
	unsigned char e;
	unsigned int temp=address;
	e=0;
	while (e<3) {
		gnd_93=0;
		cs_93=sk_93=0;org_93=1;cs_93=1;
		ewen57();
		cs_93=1;
		nop;
		high46();
		low46();
		address>>=1;
		address|=0x80;
		wd46(address);wd46(dat/256);wd46(dat%256);
		cs_93=0;nop;cs_93=1;
		time=0;do_93=1;
		while (1) {
			if (do_93==1) break;
			if (time>20) break;
		}
		cs_93=0;
		if (read93c57_word(temp)==dat) {
			return(0);
		}
		e++;
	}
	return(1);
}





//=================================================


void ewen56(void){
	nop;
	cs_93=1;
	high46();
	low46();
	low46();
	wd46(0xc0);
	cs_93=0;
}
unsigned int read93c56_word(unsigned int address) {
	unsigned int dat;
	unsigned char dat0,dat1;
	gnd_93=0;
	cs_93=sk_93=0;org_93=1;cs_93=1;
	address=address>>1;
	high46();
	high46();
	low46();
	wd46(address);dat1=rd46();dat0=rd46();
	cs_93=0;dat=dat1*256+dat0;
	return(dat);
}
bit write93c56_word(unsigned int address,unsigned int dat){
	unsigned char e;
	unsigned int temp=address;
	e=0;
	while (e<3) {
		gnd_93=0;
		cs_93=sk_93=0;org_93=1;cs_93=1;
		ewen56();
		nop;
		cs_93=1;
		nop;
		high46();
		low46();
		high46();
		address>>=1;
		wd46(address);wd46(dat/256);wd46(dat%256);
		cs_93=0;nop;cs_93=1;
		TH0=0;
		time=0;do_93=1;
		while (1) {
			if (do_93==1) break;
			if (time) break;
		}
		cs_93=0;
		if (read93c56_word(temp)==dat) {
			return(0);
		}
		e++;
	}
	return(1);
}

//========================================================
	//93c76	93c86

//=======================================================
void ewen76(void){
	nop;
	cs_93=1;
	dip7=1;
	high46();
	low46();
	low46();
	high46();
	high46();
	wd46(0xff);
	cs_93=0;
}

unsigned int read93c76_word(unsigned int address) {
	unsigned char dat0,dat1;
	gnd_93=0;
	cs_93=sk_93=0;org_93=1;cs_93=1;
	address>>=1;
	high46();
	high46();
	low46();
	if((address&0x200)==0x200) high46(); else low46();
	if ((address&0x100)==0x100) high46(); else low46();
	wd46(address);dat1=rd46();dat0=rd46();
	cs_93=0;
	return(dat1*256|dat0);
}

bit write93c76_word(unsigned int address,unsigned int dat){
	unsigned char e;
	unsigned int temp=address;
	e=0;
	address>>=1;
	while (e<3) {
		gnd_93=0;
		cs_93=sk_93=0;org_93=1;cs_93=1;
		ewen76();
		nop;
		cs_93=1;
		high46();
		low46();
		high46();
		if((address&0x200)==0x200) high46(); else low46();
		if ((address&0x100)==0x100) high46(); else low46();
		wd46(address);wd46(dat/256);wd46(dat%256);
		cs_93=0;nop;cs_93=1;
		time=0;do_93=1;
		while (1) {
			if (do_93==1) break;
			if (time>10) break;
		}
		cs_93=0;
		if (read93c76_word(temp)==dat) {
			return(0);
		}
		e++;
	}
	return(1);
}
