#include<reg51.h>
#define uchar unsigned char
#define slave 0x02
#define BN 16
uchar idata rbuf[16];
uchar idata tbuf[16]={"master transmit"};
void err(void)
{SBUF=0xff;
 while(TI==0);TI=0;
 }

uchar master(uchar addr,uchar command)
 {uchar aa,i,pf;
 while(TI==0);TI=0;
 while(RI==0);RI=0;
 if(SBUF!=addr)err();
 else{TB8=0;
 SBUF=command;
 while(TI==0);TI=0;
 while(RI==0);RI=0;
 aa=SBUF;  
 if((aa&0x08)==0x08){TB8=1;err();}
 else{
      if(command==0x01)
         {if((aa&0x01)==0x01)
		    { do {
			      pf=0;
		          for(i=0;i<BN;i++)
			        {SBUF=tbuf[i];
			         pf+=tbuf[i];
			         while( TI==0);TI=0;
			         }
			      SBUF=pf;
			      while(TI==0);TI=0;
			      while(RI==0);RI=0;
		         }while(SBUF!=0);
		      TB8=1;
		      return(0);
		    }
	     } 
	 else {
	      if((aa&0x02)==0x02)
		    {while(1)
			    {pf=0;
				 for(i=0;i,BN;i++)
				   {while(RI==0);RI=0;
				    rbuf[i]=SBUF;
					pf+=rbuf[i];
					}
				 while(RI==0);RI=0;
				 if(SBUF==pf)
				   {SBUF=0x00;
				    while(TI==0);TI=0;
				    break;
				    }
				 else{SBUF=0xff;
				     while(TI==0);TI=0;
					 }
			   	 }
			 TB8=1;
			 return(0);
			}
		 }
	 }
 }

main()
{ TMOD=0x20;
  TL1=0xfd;
  TH1=0xfd;
  PCON=0x00;
  TR1=1;
  SCON=0xf0;
  master(slave,0x01);
  master(slave,0x02);
}
