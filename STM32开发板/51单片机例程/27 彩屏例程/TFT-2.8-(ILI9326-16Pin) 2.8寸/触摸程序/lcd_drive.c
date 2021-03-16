#include "lcd_drive.h"

/****************************************************************************
*��������TFT_WriteCmd
*��  �룺cmd������
*��  ����
*��  �ܣ�д���
****************************************************************************/	  

void TFT_WriteCmd(uint cmd)
{
	uchar cmdH, cmdL;
	cmdH = cmd >> 8;
	cmdL = cmd & 0x00FF;
	
	
	TFT_WR = 1;	 		  //��ʼ��WR
	TFT_CS = 0;			  //��Ƭѡ
	
	TFT_RD = 1;           //ѡ��д
	TFT_RS = 0;			  //ѡ������
	
	TFT_DATAPORTH = cmdH; //������������
    TFT_DATAPORTL = cmdL; 
	
	TFT_WR = 0;			  //д��ʱ��
	TFT_WR = 1;

	TFT_CS = 1;			  //�ر�Ƭѡ	
}

/****************************************************************************
*��������TFT_WriteData
*��  �룺 dat������
*��  ����
*��  ��: д���ݡ�
****************************************************************************/	  

void TFT_WriteData(uint dat)
{
	uchar datH, datL;
	datH = dat >> 8;
	datL = dat & 0x00FF;
	
	TFT_WR = 1;	 		  //��ʼ��WR
	TFT_CS = 0;			  //��Ƭѡ
	
	TFT_RD = 1;           //ѡ��д
	TFT_RS = 1;			  //ѡ��������
	
	TFT_DATAPORTH = datH;  //������������
    TFT_DATAPORTL = datL;	

	TFT_WR = 0;			  //д��ʱ��
	TFT_WR = 1;
	
	TFT_CS = 1;			  //�ر�Ƭѡ
}

/****************************************************************************
*��������TFT_WriteColorData
*��  �룺 dat���������ɫ
*��  ����
*��  ��: д���ݡ�
****************************************************************************/	  

void TFT_WriteColorData(uint dat)
{
	uchar datH, datL, db8H, db8L;
    
    //-- ������ɫת�� --//
    datL = dat & 0x00FF;
    db8L = (dat >> 4) & 0x01;

    datH = dat >> 11;
    datH <<= 1;
    datH |= dat >> 15;
    datH <<= 2;
    datH |= (dat >> 9) & 0x03;
    db8H = (dat >> 8) & 0x01;


	
	TFT_WR = 1;	 		  //��ʼ��WR
	TFT_CS = 0;			  //��Ƭѡ
	
	TFT_RD = 1;           //ѡ��д
	TFT_RS = 1;			  //ѡ��������
	
	TFT_DATAPORTH = datH;  //������������
    TFT_DATAPORTL = datL;	


	TFT_WR = 0;			  //д��ʱ��
	TFT_WR = 1;
	
	TFT_CS = 1;			  //�ر�Ƭѡ
}

/****************************************************************************
*��������TFT_WriteCmdData
*��  �룺cmd������
*      ��dat������
*��  ����
*��  �ܣ�д��� д���ݡ�
****************************************************************************/	  

void TFT_WriteCmdData(uint cmd, uint dat)
{
	TFT_WriteCmd(cmd);
	TFT_WriteData(dat);
}
/****************************************************************************
*��������TFT_Init
*��  �룺
*��  ����
*��  �ܣ���ʼ��TFT��
****************************************************************************/	  

void TFT_Init(void)
{
	uint i;

	TFT_RST = 1;
	for(i=500; i>0; i--);
	TFT_RST = 0;
	for(i=500; i>0; i--);
	TFT_RST = 1;
	for(i=5000; i>0; i--);
	
	TFT_CS = 0;
	
//************* Start Initial Sequence **********//
	TFT_WriteCmdData(0x0702, 0x3008);   // Set internal timing 
	TFT_WriteCmdData(0x0705, 0x0012);   // Set internal timing 
	TFT_WriteCmdData(0x070b, 0x1213);   // Set internal timing
    TFT_WriteCmdData(0x0001, 0x0100);   // set SS and SM bit 
    TFT_WriteCmdData(0x0002, 0x0100);   // set 1 line inversion 
    TFT_WriteCmdData(0x0003, 0x1030);   // set GRAM write direction and BGR=1.  
    TFT_WriteCmdData(0x0008, 0x0808);   // set the back porch and front porch
    TFT_WriteCmdData(0x0009, 0x0000);   // set non-display area refresh cycle ISC[3:0]  
    TFT_WriteCmdData(0x000c, 0x0000);   // RGB interface setting
    TFT_WriteCmdData(0x000f, 0x0000);   // RGB interface polarity

  //*************Power On seence ****************// 
    TFT_WriteCmdData(0x0100, 0x0000);      // SAP, BT[3:0], AP, DSTB, SLP, STB 
    TFT_WriteCmdData(0x0102, 0x0000);      // DC1[2:0], DC0[2:0], VC[2:0] 
    TFT_WriteCmdData(0x0103, 0x0000);      // VREG1OUT voltage 
    TFT_WriteCmdData(0x0100, 0x1190);      // VDV[4:0] for VCOM amplitude 
	for(i=5000; i>0; i--);                 // Dis-charge capacitor power voltage 
    TFT_WriteCmdData(0x0101, 0x0137);      // SAP, BT[3:0], AP, DSTB, SLP, STB 
    TFT_WriteCmdData(0x0102, 0x01bc);      // DC1[2:0], DC0[2:0], VC[2:0] 
	for(i=5000; i>0; i--);                 // Delay 50ms   
    TFT_WriteCmdData(0x0103, 0x3400);      // Internal reference voltage= Vci; 
	for(i=5000; i>0; i--);                 // Delay 50ms 
    TFT_WriteCmdData(0x0281, 0x0015);      // Set VDV[4:0] for VCOM amplitude 
    TFT_WriteCmdData(0x0200, 0x0000);      // Set VCM[5:0] for VCOMH 
    TFT_WriteCmdData(0x0201, 0x0000);      // Set Frame Rate  
	for(i=5000; i>0; i--);                 // Delay 50ms 

    // ----------- Adjust thGamma    Curve ----------// 
    TFT_WriteCmdData(0x0300, 0x0000); 
    TFT_WriteCmdData(0x0301, 0x0204); 
    TFT_WriteCmdData(0x0302, 0x0202); 
    TFT_WriteCmdData(0x0305, 0x0105); 
    TFT_WriteCmdData(0x0306, 0x0808); 
    TFT_WriteCmdData(0x0307, 0x0505); 
    TFT_WriteCmdData(0x0308, 0x0305); 
    TFT_WriteCmdData(0x0309, 0x0707); 
    TFT_WriteCmdData(0x030c, 0x0501); 
    TFT_WriteCmdData(0x030D, 0x0808);
	 
    //------------------ SetRAM area ---------------// 
    TFT_WriteCmdData(0x0210, 0x0000);     // Horizontal GRAM Start Address 
    TFT_WriteCmdData(0x0211, 0x00EF);     // Horizontal GRAM End Address 
    TFT_WriteCmdData(0x0212, 0x0000);     // Vertical GRAM Start Address 
    TFT_WriteCmdData(0x0213, 0x01af);     // Vertical GRAM Start Address 
    TFT_WriteCmdData(0x0400, 0x3500);     // Gate Scan Line 	
    TFT_WriteCmdData(0x0401, 0x0001);     // NDL,VLE, REV (????)IPS(0000),TN(0001)
    TFT_WriteCmdData(0x0404, 0x0000);     // set scrolling line 

    //-------------- Partialisplay Control ---------// 
    TFT_WriteCmdData(0x0500, 0x0000); 
    TFT_WriteCmdData(0x0501, 0x0000); 
    TFT_WriteCmdData(0x0502, 0x0000); 
    TFT_WriteCmdData(0x0503, 0x0000); 
    TFT_WriteCmdData(0x0504, 0x0000); 
    TFT_WriteCmdData(0x0505, 0x0000);
	 
    //-------------- Panel Ctrol -------------------// 
    TFT_WriteCmdData(0x0010, 0x0010); 	   // DIVI[1:0];RTNI[4:0]	 16clock
    TFT_WriteCmdData(0x0011, 0x0600);	   // NOWI[2:0];SDTI[2:0]	  6clock
	TFT_WriteCmdData(0x0020, 0x0002); 	   // DIVE[1:0];RTNE[5:0]
    TFT_WriteCmdData(0x0007, 0x0173);      // 262K color and display ON
}

/****************************************************************************
*��������TFT_SetWindow
*��  �룺xStart����ʼX����
*      ��yStart����ʼY���� 
*      ��xEnd������X����
*      ��yEnd������Y����
*��  ����
*��  �ܣ�����Ҫ�����Ĵ��ڡ�
****************************************************************************/	  

void TFT_SetWindow(uint xStart, uint yStart, uint xEnd, uint yEnd)
{

	TFT_WriteCmdData(0x0210, xStart);	 //ˮƽ����ʼ
	TFT_WriteCmdData(0x0212, yStart);	 //��ֱ����ʼ
	TFT_WriteCmdData(0x0211, xEnd);	     //ˮƽ�߽���
	TFT_WriteCmdData(0x0213, yEnd);	     //��ֱ�߽���

	TFT_WriteCmdData(0x0200, xEnd);
	TFT_WriteCmdData(0x0201, yEnd);
	TFT_WriteCmd(0x0202);
}


/****************************************************************************
*��������GUI_Clearcreen
*��  �룺backColor��������ɫ
*��  ����
*��  �ܣ�������Ϳ����ɫ��
****************************************************************************/
	  
void TFT_ClearScreen(uint color)
{
  	uint i, j;

	TFT_SetWindow(0, 0, TFT_XMAX, TFT_YMAX);	 //��������
  	for(i=0; i<= TFT_XMAX; i++)
	{
		for (j=0; j<= TFT_YMAX; j++)
		{
			TFT_WriteData(color);
		}
	}
}


