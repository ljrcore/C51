#include<reg51.h>
void Ledon();
void Ledoff();
void IfDemo2(void)
{Byte Ledcount;
 if(Ledcount<26)//�����û����26�μ�����
	{Ledon();
	 Ledcount++;
	 }
 else			//�������
	Ledoff();
}
