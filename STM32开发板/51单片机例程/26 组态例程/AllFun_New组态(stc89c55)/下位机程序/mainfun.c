/******************************************************************************************************************
����:  �ۺϳ���																	                                  *
* 	   �˳�������˰��д󲿷ֵĹ��ܣ������λ��һ��ʹ��  ����ǰ��˫��Keillib.exe																										  *
*																												  *
*******************************************************************************************************************/
      
#include <system.h>

#define  NOP() _nop_()  /* �����ָ�� */
#define  TRUE  0xff
#define  FALSE 0


//6T/12T����ģʽ
#define  Model_6T  0


unsigned char bdata X0,X1,Y0,Key;
unsigned int  Tick_10ms=0;    //ʱ��Ƭ������

sbit K0=Key^0;
sbit K1=Key^1;
sbit K2=Key^2;
sbit K3=Key^3;
sbit K4=Key^4;
sbit K5=Key^5;
sbit K6=Key^6;
sbit K7=Key^7;

bit K0J,K1J,K2J,K3J,K4J,K5J;


#define  M_Sum 32
#define  D_Sum 185
unsigned char  idata M[M_Sum];
unsigned short xdata D[D_Sum];
     
unsigned int TestDelay1, TestDelay2, TestDelay3;
unsigned int T[6];


//*********************************************************************
#define UCHAR unsigned char
void delay(unsigned int i)
{
    UCHAR j;
    for(i; i > 0; i--)
        for(j = 200; j > 0; j--);
}

 /*************************************************************************
* ��������: ConversionStr(void)
* ��������: �ַ���ת������
* ��    ��: *Register, *str
***************************************************************************/
void ConversionStr(unsigned short *Register,unsigned char code *str)
{ 
  unsigned char sL,sH;
  while(1)
   { 
     if(*str == '\0') break;
     sL=(*str++);
     sH=(*str++);          
     *Register++=sH<<8|sL;	 
   }
}



/*************************************************************       
* (T0) 10 ms ʱ�ӳ��     
;************************************************************/
void T0zd(void) interrupt 1 
{
    //TH0=0xC4; //18.432M
    //TL0=0x00;

    #if Model_6T
        TH0=0xB8; //22.1184M
        TL0=0x00;
	#else
        TH0=0xDC; //11.0592M
        TL0=0x00;
	#endif
  
    Tick_10ms++;
}


/***********************************************************
purpose: ϵͳ��ʼ��
/**********************************************************/
void system_Ini()
{
    TMOD|= 0x11;
	//TH0=0xC4; //18.432M
    //TL0=0x00;

	#if Model_6T
        TH0=0xB8; //22.1184M
        TL0=0x00;
	#else
        TH0=0xDC; //11.0592M
        TL0=0x00;
	#endif
	IE    = 0x8A;	
    TR0  = 1;

	//PWM  
    //TH1 = 0xfe; //11.0592
    //TL1 = 0x33;
    //TR1  = 1; 
}



//***********************************************************
main()
{  unsigned char Input;
   unsigned char i,j;
   unsigned char code str1[] = "PLC�����汾 V1.05   ";
   unsigned char code str2[] = "51�����汾 V3.28  ";

	system_Ini();
	InitMotor();

	Input=ReHC74165();
    X0=Input;

	#if Model_6T   // ���� ������ վ��
        Modbus_Init(221184, 57600, 1, &M[0], &D[0]);
	#else
	    //Modbus_Init(110592, 19200, 1, &M[0], &D[0]);
		Modbus_Init(120000, 19200, 1, &M[0], &D[0]);
	#endif
	//Modbus_Init(184320, 57600, X1, &M[0], &D[0]);

	for(i=0; i<M_Sum; i++) M[i]=0;	
	for(i=0; i<D_Sum; i++) D[i]=i;	
	Y0=0;
	D[12]=1;
	D[24]=0;
	D[28]=100;
	D[30]=50;
	D[100]=0; //PLC-K0~K3���ƻ����л�OFF
	D[180]=0; //AD��������
	D[181]=0; //���ߺ�ɫ����
	ConversionStr(&D[50],str1);

    ////////////////////////////////////////////////////////////////////////
	while(1)
	{  
       Input=ReHC74165();
       X0=Input;
	   Key=X0;

       if(K0&K0J) //����ͼƬ�л� D27
	   {
	     M[0]=~M[0]; 
		 if(++D[27]>5) D[27]=0;
		 if(D[100]) D[24]=10; //���ƴ�����(��ʾ�����=10)
	   }
	   K0J=~K0;
	     
	   //��K1~K5΢�ֿ���, �����л�M1~M5 
	   if(K1&K1J)
	   {
	      M[1]=~M[1]; 
		  if(D[100]) D[24]=17; //���ƴ�����(��ʾ�����=17)
	   }
	   K1J=~K1;
	      
	   if(K2&K2J)
	   {
	      M[2]=~M[2]; 
		  if(D[100])D[24]=29; //���ƴ�����(��ʾ�����=29)
	   }
	   K2J=~K2; 
		  
	   if(K3&K3J)
	   {
	      M[3]=~M[3];
		  if(D[100])D[24]=30; //���ƴ�����(��ʾ�����=30)
	   }
	   K3J=~K3; 

	   if(K4&K4J)M[4]=~M[4]; K4J=~K4;   
	   if(K5&K5J)M[5]=~M[5]; K5J=~K5; 


	   if(M[1])	 //�Զ�ͼƬ�л� D[27] ���10ms*D[28] �Ӽ�һ��
	   {
	   	  if(TickOut(&T[0],D[28])) if(++D[27]>5) D[27]=0;  //10ms*D[28]   
	   }

	   //��ʾ��λ������汾
	   if(K0) ConversionStr(&D[50],str1);
	   if(K1) ConversionStr(&D[50],str2);


	   //��̬�ı��������ݲ���
	   if(TickOut(&T[1],D[30])) //D[30]λ�˻��趨�Ķ����ٶ�
	   {
	      //������Ϣ
	      if((K0)&&(D[21]<58)) ++D[21];
	      if((K1)&&(D[21]>0))  --D[21]; 

		  //������Ϣ
		  if((K2)&&(D[22]<9))  ++D[22];
	      if((K3)&&(D[22]>0))  --D[22];
 
		  //�¶�״̬��ɫ��ʾ
		  D[90]++;

		  //����ʱ��
		  D[93]++;
	   
		  //����S5(��ON/˫OFF),���Ʊ����Զ��仯
		  if(M[4])
		  {		  
		    if(++D[21]>57) D[21]=0;
		  }

		  //����S6(��ON/˫OFF),���ƶ����Զ��仯
		  if(M[5])
		  {		  
		    if(!M[6]) //����++
		    {
			  if(++D[22]>8) 
			  {
			    D[22]=8;
			    M[6]=TRUE;
			  }
			}
			else //����--
			{
			  if(--D[22]==0) M[6]=FALSE;
			}
		  }
	   }

	   //���뿪�ؿ���[����״̬��ʾ]
	   D[99]=0;
	   if(X1&0x10) D[99]=1; //���뿪��1
	   if(X1&0x20) D[99]=2; //���뿪��2
	   if(X1&0x40) D[99]=3; //���뿪��3
	   if(X1&0x80) D[99]=4; //���뿪��4

	 
	   //�������ʾֵ++
	   if(TickOut(&TestDelay1,1))  LedNumVal++;  //10ms*10

	   //�������λ
	   if(TickOut(&TestDelay2,50))               //10ms*100
	   {  
	     LedUnit<<=1;
		 if(LedUnit==0)LedUnit=1;  
	   }
	 
	   //���δִ��,ʵʱ�����������ƶ�
	   if(D[180]==0) 
	   {
	     if(TickOut(&T[2],200)) //��֤PLC�յ��ĺ�������
	     {     
           D[150]=0;
		   for(i=0; i<14; i++)
		   {	 
		     D[150]+=D[115+i*2];
		   }   
	     }
	   }


	   //ʵʱ�����������ƶ�, 30��*2 [D110-169]
	   if(D[180]>0)
	   {
         if(TickOut(&T[3],100))
	     {
		   D[139]=D[0];
	       for(i=0; i<29; i++) D[110+i]=D[111+i];
           
		   D[169]=D[1];
		   for(i=0; i<29; i++) D[140+i]=D[141+i];        
	     }
	   }

       //AD,DA,LCD����
	   if(TickOut(&TestDelay3,10)) //10ms*10
	    {
		    if((K4)&&(D[12]<100)) ++D[12];
	        if((K5)&&(D[12]>0))   --D[12]; 
			if((K6)&&(D[4]<1000)) ++D[4];
	        if((K7)&&(D[4]>0))    --D[4];		
			ad_da();         //D[AD=0..3, DA=4]
		}

	   
	   Y0=LedUnit;
	   if(D[25]==1) //���Y=B
	   {
	     Y0=0;
	     for(i=0;i<8;i++) Y0+=(M[i]&(1<<i));
	   }
	   else
	   {
	     if(D[25]==2) Y0=D[29]; //���Y=��ĸ���D29
	   }


       //������������ S1~S8 ��Ӧ0~7
	   for(i=0;i<8;i++) 
	   {
	     if(Key&(1<<i)) 
		 {
		   D[19]=i;
		   break;
		 }
	   }


	   //=============================================================================
	   SetMotor(); //D[12]
	   Modbus_Handle(Tick_10ms);
	   //========================IIC ��ȡ
	   if(D[13]==66)
	   { unsigned char i;
	     unsigned char pDat[8];

	     D[13]=0;
		 IRcvStr(AT24C02, 0 , &pDat[0], 8); 
		 for (i=0; i<4; i++)
	     {
		   D[14+i]=pDat[i*2+0]+pDat[i*2+1]*0x100;
		 }	     
	   }

	   //========================IIC ����
	   if(D[13]==88)
	   { unsigned char i;
	     unsigned char pDat[8];

	     D[13]=0;
		 for (i=0; i<4; i++)
	     {
		   pDat[i*2+0]=D[14+i];
		   pDat[i*2+1]=D[14+i]>>8;
		 }
	     ISendStr(AT24C02, 0 , &pDat[0], 8); 
	   }


       D[18]=X0;
 	   D[31]=X1;
	   D[23]=LedNumVal;
	   D[26]=Key;

	   if(Key) BEEP=0;
	   else    BEEP=1;	  
	  
	   /*
	   if(X1&0x10) //���뿪��1
	   {
	     Y0=X0;
	     LedNumVal=D[0];
	   }

	   if(X1&0x20) //���뿪��2
	   {
	     Y0=Key;
	     LedNumVal=D[1];
	   }

	   if(X1&0x40) //���뿪��3
	   {
	     Y0=Key;
  	     LedNumVal=D[2];
	   }

	   if(X1&0x80) //���뿪��4
	   {
	     LedUnit=0;
	     if(M[0])LedUnit|=1;
	     if(M[1])LedUnit|=2;
	     if(M[2])LedUnit|=4;
	     if(M[3])LedUnit|=8;

		 Y0=LedUnit;
		 LedNumVal=D[12];
	   }
	   */
	  
	   //д���
       LedOut[0]=Disp_Tab[LedNumVal%10000/1000];
       LedOut[1]=Disp_Tab[LedNumVal%1000/100]&0x7f;
       LedOut[2]=Disp_Tab[LedNumVal%100/10];
       LedOut[3]=Disp_Tab[LedNumVal%10]; 

	   LedOut[4]=Disp_Tab[LedNumVal%10000/1000];
       LedOut[5]=Disp_Tab[LedNumVal%1000/100]&0x7f;
       LedOut[6]=Disp_Tab[LedNumVal%100/10];
       LedOut[7]=Disp_Tab[LedNumVal%10]; 
     	 
	    
	 for( i=0; i<9; i++) 
	 {	 
	  P1 = LedOut[i];			
	  switch(i)					  
	     {	    
			case 0:LS138A=0; LS138B=0; LS138C=0; LED8_1=1; break;         
	        case 1:LS138A=1; LS138B=0; LS138C=0; LED8_1=1; break;             	
	        case 2:LS138A=0; LS138B=1; LS138C=0; LED8_1=1; break; 
	        case 3:LS138A=1; LS138B=1; LS138C=0; LED8_1=1; break; 
			case 4:LS138A=0; LS138B=0; LS138C=1; LED8_1=1; break;
			case 5:LS138A=1; LS138B=0; LS138C=1; LED8_1=1; break;
			case 6:LS138A=0; LS138B=1; LS138C=1; LED8_1=1; break;
			case 7:LS138A=1; LS138B=1; LS138C=1; LED8_1=1; break;
		    case 8:LS138B=1; LS138B=1; LS138C=1; LED8_1=0; break;	
	     }
		  
		delay(3);
	  }
	    //P1 = 0;

	  //��75165 ����ֵ�� 74595 �������������ʾ���֡� 0-8 ��
	  j=0;
	  for( i=0; i<8; i++) 
	  {
	    if(X0&(1<<i)) 
		{
		  j=i+1; 
		  break;
		}
	  }
	  HC595SendData(LED7Code[j]);	  
	}
}




