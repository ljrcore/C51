//  ��΢����ģ��I2C���ߵ�����У��ò��пڵ�D0��PIN2��ģ��SCL�źţ���D1��PIN3��ģ��SDA�źš�����IIC���ߵĵ�ƽ�淶���������£� 
    #include <dos.h> 
    #include <stdio.h> 
    #include <conio.h> 
    #include <bios.h> 

    #define DELAY_TIME 10 
    #define FALSE 0 
    #define TRUE 1 
    const unsigned char SCL_PIN=0x01; 
    const unsigned char SDA_OIN=0x02; 

    static void SET_SCL(void) 
    { 
        asm{ 
            mov dx,0x378 
            in  ax,dx 
            or  ax,SCL_PIN            //��SCL��1 
            out dx,ax 
        } 
    } 

    static void CLR_SCL(void) 
    { 
        asm{ 
            mov dx,0x378 
            in  ax,dx 
            or  ax,0xff-SCL_PIN       //��SCL��0 
            out dx,ax 
        } 
    } 

    static void SET_SDA(void) 
    { 
        asm{ 
            mov dx,0x378 
            in  ax,dx 
            or  ax,SDA_PIN            //��SDA��1 
            out dx,ax 
        } 
    } 

    static void CLR_SDA(void) 
    { 
        asm{ 
            mov dx,0x378 
            in  ax,dx 
            or  ax,0xff-SDA_PIN       //��SDA��0 
            out dx,ax 
        } 
    } 

    void DELAY(int t=DELAY_TIME)      //��ʱ�ӳ��� 
    { 
        for(int i=0;i<t;i++); 
    } 

    void IIC_Start(void)              //����I2C���� 
    { 
        //��SCLΪ�ߵ�ƽʱ��ʹSDA����һ�������� 
        SET_SDA(); 
        SET_SCL(); 
        DELAY(); 
        CLR_SDA(); 
        DELAY(); 
        CLR_SCL(); 
        DELAY(); 
    } 

    void IIC_Stop(void)               //��ֹI2C���� 
    { 
        //��SCLΪ�ߵ�ƽʱ��ʹSDA����һ�������� 
        CLR_SDA(); 
        SET_SCL(); 
        DELAY(); 
        SET_SDA(); 
        DELAY(); 
        CLR_SCL(); 
        DELAY(); 
    } 

    void SEND_0(void)                //����BIT0 
    { 
        //��SCLΪ�ߵ�ƽʱ��ʹSDA���ֵ͵�ƽ 
        CLR_SDA(); 
        SET_SCL(); 
        DELAY(); 
        CLR_SCL(); 
        DELAY(); 
    } 

    void SEND_1(void)                //����BIT1 
    { 
        //��SCLΪ�ߵ�ƽʱ��ʹSDA���ָߵ�ƽ 
        SET_SDA(); 
        SET_SCL(); 
        DELAY(); 
        CLR_SCL(); 
        DELAY(); 
    } 

    int Check_Acknowledge(void) 
    { 
        //������ÿ���ֽڼ��SLAVE��Ӧ���ź� 
        SET_SDA();                   //�������ͷ�SDA�� 
        SET_SCL(); 
        DELAY(DELAY_TIME/2); 
        unsigned char b=inportb(0x378);    //�����ź��� 
        DELAY(DELAY_TIME/2); 
        CLR_SCL(); 
        DELAY(); 
        if(b&0xSDA_PIN)            //SALVE����1 
            return FLASE; 
        return TRUE; 
    } 

ʹ���������룬�������PC���ò��п�ģ��I2C������ʵ�顢��غ͵��ԡ� 