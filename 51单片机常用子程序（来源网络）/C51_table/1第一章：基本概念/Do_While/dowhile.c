#include<at89x51.h>
void Delay50us(Byte count);
void Dowhiledemo(void)
{Byte i=0,j,k;
 Byte Soundlong,Soundtone;
 Byte music_soundlong1[10];
 Byte music_soundtone1[10];
 Word m;
 do
 	{Soundlong=music_soundlong1[i];
 	 Soundtone=music_soundtone1[i];
 	 for(j=0;j<Soundlong;j++)		 //Soundlong������
     	{for(k=0;k<12;k++)
			{for(m=0;m<Soundtone;m++)//Soundtone������
				P1_0=0;
		 	 for(m=0;m<Soundtone;m++)	 
				P1_0=1;
			 }
    	  Delay50us(6);
		 }
	}while(music_soundtone1[i]!=0x00);//û���������
}
