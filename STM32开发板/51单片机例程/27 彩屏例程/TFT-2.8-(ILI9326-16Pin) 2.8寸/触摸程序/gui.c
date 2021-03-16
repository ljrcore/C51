#include"gui.h"
#include"charcode.h"
//---���Ҫ��ʾͼƬ��������ͷ�ļ�---//
#ifdef PICTURE_SHOW

#include"picture.h"

#endif

/****************************************************************************
*��������GUI_Dot
*��  �룺x,y, color
*��  ����
*��  �ܣ�����������Ϳ����ɫ��
****************************************************************************/	  

void GUI_Dot(uchar x, uint y, uint color)
{  
	uchar i;

	TFT_SetWindow(x-1, y-1, x+2, y+2);  //��������

	for(i=0; i<16; i++)
	{
		TFT_WriteData(color);
	}
}

///****************************************************************************
//*��������GUI_Box
//*��  �룺 sx, sy, ex, ey, color
//*��  ����
//*��  �ܣ���һ������Ϳ����ɫ��
//****************************************************************************/	  
//void GUI_Box(uchar sx, uint sy, uchar ex, uint ey, uint color)
//{ 
//	uint temp;   
//	TFT_SetWindow(sx, sy, ex, ey); 
//  sx = ex - sx + 1;
//	sy = ey - sy + 1;
//	while (sx--)
//	{
//	 	temp = sy;
//		while (temp--)
//	 	{	
//			TFT_WriteData(color);
//		}
//	}
//}

/****************************************************************************
*��������GUI_Line 
*��  �룺xStart,yStart,xEnd,yEnd,color
*��  ����
*��  �ܣ���һ��ֱ��
****************************************************************************/	  

void GUI_Line(uchar xStart, uint yStart, uchar xEnd, uint yEnd, uint color)
{
	uint t;  
	int xerr = 0, yerr = 0, delta_x, delta_y, distance;  
	int incx, incy;  
	uint row, col;  
	delta_x = xEnd - xStart;//������������  
	delta_y = yEnd - yStart;  
	col = xStart;  
	row = yStart;  
	if (delta_x > 0)
	{
		incx=1;//���õ�������
	} 	  
	else    
	{  
	    if (delta_x == 0)
		{
			incx = 0;//��ֱ�� 
		} 		 
	    else 
			{
				incx = -1;
				delta_x = -delta_x;
			}  
	}  
	if (delta_y > 0)
	{
		incy = 1;
	}	  
	else  
	{  
	    if (delta_y == 0)
		{
			incy = 0;//ˮƽ��  
		} 
	    else 
		{
			incy = -1;
			delta_y = -delta_y;
		}  
	}  
	if (delta_x > delta_y)
	{ 
		distance = delta_x;//ѡȡ��������������  
	}
	else
	{
		distance = delta_y; 
	} 	
	for (t=0; t<=distance+1; t++)  
	{                                     //�������  
	    GUI_Dot(col, row, color);
	    xerr += delta_x;  
	    yerr += delta_y;  
	  	if(xerr > distance)  
	    {  
	        xerr -= distance;  
	        col += incx;  
	    }  
	    if(yerr > distance)  
	    {  
	        yerr -= distance;  
	        row += incy;  
	    }  
	}  
}

/****************************************************************************
*��������GUI_WriteCnChar 
*��  �룺x,y,cn,wordColor,backColor
*��  ����
*��  �ܣ�д���ſ��庺��
****************************************************************************/	  

#ifdef CHAR32_SHOW

void GUI_Write32CnChar(uint x, uint y, uchar *cn, uint wordColor, uint backColor)	 
{  
	uchar i, j, wordNum;
	uint color;
	while (*cn != '\0')
	{
		TFT_SetWindow(x, y, x+31, y+28);
		for (wordNum=0; wordNum<20; wordNum++)
		{	//wordNumɨ���ֿ������
			if ((CnChar32x29[wordNum].Index[0]==*cn)
			     &&(CnChar32x29[wordNum].Index[1]==*(cn+1)))
			{
				for(i=0; i<116; i++) 
				{	//MSK��λ��
					color=CnChar32x29[wordNum].Msk[i];
					for(j=0;j<8;j++) 
					{
						if((color&0x80)==0x80)
						{
							TFT_WriteData(wordColor);
						} 						
						else
						{
							TFT_WriteData(backColor);
						} 
						color<<=1;
					}//for(j=0;j<8;j++)����
				}    
			}
		} //for (wordNum=0; wordNum<20; wordNum++)���� 	
		cn += 2;
		x += 32;
	}
}
#endif

/****************************************************************************
*��������GUI_WriteEnChar 
*��  �룺x,y,en,wordColor,backColor
*��  ����
*��  �ܣ�д�ĺ�����ĸ
****************************************************************************/	  
#ifdef CHAR14_SHOW

void GUI_Write14CnChar(uint x,uint y,uchar *cn,uint wordColor,uint backColor)	 
{  
	uchar i, j, wordNum;
	uint color;
	while (*cn != '\0')
	{
		TFT_SetWindow(x, y, x+23, y+18);
		for (wordNum=0; wordNum<20; wordNum++)
		{	//wordNumɨ���ֿ������
			if ((CnChar19x24[wordNum].Index[0]==*cn)
			     &&(CnChar19x24[wordNum].Index[1]==*(cn+1)))
			{
				for(i=0; i<57; i++) 
				{	//MSK��λ��
					color=CnChar19x24[wordNum].Msk[i];
					for(j=0;j<8;j++) 
					{
						if((color&0x80)==0x80)
						{
							TFT_WriteData(wordColor);
						} 						
						else
						{
							TFT_WriteData(backColor);
						} 
						color<<=1;
					}//for(j=0;j<8;j++)����
				}    
			}
		} //for (wordNum=0; wordNum<20; wordNum++)���� 	
		cn += 2;
		x += 24;
	}
}

#endif 
/****************************************************************************
*��������GUI_WriteASCII 
*��  �룺x,y,en,wordColor,backColor, *p
*��  ����
*��  �ܣ�д16X24��ASCII�ַ�
****************************************************************************/	  

#ifdef USE_ASCII

void GUI_WriteASCII(uchar x, uchar y, uchar *p, uint wordColor, uint backColor)
{
	uchar j, wordByte,wordNum;
	uint color;
	while(*p != '\0')
	{
		wordNum = *p - 32;
		TFT_SetWindow(x,y,x+15, y+23);
		for (wordByte=0; wordByte<48; wordByte++)
		{
			color = ASCII16x24[wordNum][wordByte];
			for (j=0; j<8; j++) 
			{
				if ((color&0x80) == 0x80)
				{
					TFT_WriteData(wordColor);
				} 						
				else
				{
					TFT_WriteData(backColor);
				} 	
				color <<= 1;
			}
		}
		p++;
		x +=16;
	}
}
#endif

/****************************************************************************
*��������GUI_ShowPicture 
*��  �룺x,y,cn,wordColor,backColor
*��  ����
*��  �ܣ���һ��ֱ��
****************************************************************************/	  
#ifdef PICTURE_SHOW

void GUI_ShowPicture(uchar x, uint y, uchar wide, uint high)
{
	uint temp = 0, tmp = 0, num = 0;
	TFT_SetWindow(x, y, x+wide-1, y+high-1);
	num = wide * high * 2;
	do
	{  
		temp = pic[tmp + 1];
		temp = temp << 8;
		temp = temp | pic[tmp];
		TFT_WriteData(temp);//�����ʾ
		tmp += 2;
	}
	while(tmp < num);	
}

#endif















