/**************************************************************************************
*  ����:  �������������															  *
* 																					  *
*    ͨ���������˽ⲽ�����ʹ�ü����������д										  *
*     ˫���Ĺ�����ʽ��                                                           	  *
*    AB-BC-CD-DA (��һ������,ת 7.5 ��)    											  *
*                     	                                                        	  *
*  ��ѧԱһ��Ҫ�����������̣�                                           	    	  *
                    	                          									  *
**************************************************************************************/    
 

#include "reg52.h"
 //Motor
sbit F1 = P1^0;
sbit F2 = P1^1;
sbit F3 = P1^2;
sbit F4 = P1^3;



 ///////////////////////////////////////
//�����������
unsigned char MotorStep=0;
unsigned int MotorTimer = 0;
unsigned int TIM,CT;

void InitMotor()
{
  F1 = 1;
  F2 = 1;
  F3 = 1;
  F4 = 1;
}


 
void SetMotor()
{
  //  if(Speed == 0) return;

   
    switch(MotorStep)
    {
       case 0:
          if(TIM)
          {
            F1 = 0;
            F2 = 0;
			F3 = 1;
			F4 = 1;
            MotorStep = 1;
			 TIM=0;
          }
       break;

       case 1:
         if(TIM)
          {	
            F1 = 1;
            F2 = 0;
            F3 = 0;
            F4 = 1;
            MotorStep = 2;
			TIM=0;
          }
       break;

       case 2:
         if(TIM)
          {
           
          
            F1 = 1;
            F2 = 1;
            F3 = 0;
            F4 = 0;
            MotorStep = 3;
			TIM=0;
          }
       break;


       case 3:
         if(TIM)
          {	
            F1 = 0;
            F2 = 1;
            F3 = 1;
            F4 = 0;
            MotorStep = 0;
			TIM=0;
          }
       break;
    }

}


void system_Ini()
{
    TMOD|= 0x11;
    TH0=0xDC; //11.0592M
    TL0=0x00;	
	IE = 0x8A;	
    TR0  = 1;


}

main() 
 { system_Ini();
   InitMotor();
    while(1)
	{
	 SetMotor();

	 }



  }
  
 /*************************************
 [ t1 (0.5ms)�ж�] �ж����� PWM ���
  ------------1000/(0.02ms*250)=200Hz
*************************************/
  void Tzd(void) interrupt 1
{
   TH0 = 0xfe;    //11.0592
	 TL0 = 0x33;

	if( CT++==35) 
	  {TIM=1;
	   CT=0;
	  }
 }
