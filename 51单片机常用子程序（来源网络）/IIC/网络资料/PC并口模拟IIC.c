//  在微机上模拟I2C总线的设计中，用并行口的D0（PIN2）模拟SCL信号，用D1（PIN3）模拟SDA信号。根据IIC总线的电平规范，程序如下： 
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
            or  ax,SCL_PIN            //将SCL置1 
            out dx,ax 
        } 
    } 

    static void CLR_SCL(void) 
    { 
        asm{ 
            mov dx,0x378 
            in  ax,dx 
            or  ax,0xff-SCL_PIN       //将SCL置0 
            out dx,ax 
        } 
    } 

    static void SET_SDA(void) 
    { 
        asm{ 
            mov dx,0x378 
            in  ax,dx 
            or  ax,SDA_PIN            //将SDA置1 
            out dx,ax 
        } 
    } 

    static void CLR_SDA(void) 
    { 
        asm{ 
            mov dx,0x378 
            in  ax,dx 
            or  ax,0xff-SDA_PIN       //将SDA置0 
            out dx,ax 
        } 
    } 

    void DELAY(int t=DELAY_TIME)      //延时子程序 
    { 
        for(int i=0;i<t;i++); 
    } 

    void IIC_Start(void)              //启动I2C总线 
    { 
        //在SCL为高电平时，使SDA出现一个负跳变 
        SET_SDA(); 
        SET_SCL(); 
        DELAY(); 
        CLR_SDA(); 
        DELAY(); 
        CLR_SCL(); 
        DELAY(); 
    } 

    void IIC_Stop(void)               //终止I2C总线 
    { 
        //在SCL为高电平时，使SDA出现一个正跳变 
        CLR_SDA(); 
        SET_SCL(); 
        DELAY(); 
        SET_SDA(); 
        DELAY(); 
        CLR_SCL(); 
        DELAY(); 
    } 

    void SEND_0(void)                //发送BIT0 
    { 
        //在SCL为高电平时，使SDA保持低电平 
        CLR_SDA(); 
        SET_SCL(); 
        DELAY(); 
        CLR_SCL(); 
        DELAY(); 
    } 

    void SEND_1(void)                //发送BIT1 
    { 
        //在SCL为高电平时，使SDA保持高电平 
        SET_SDA(); 
        SET_SCL(); 
        DELAY(); 
        CLR_SCL(); 
        DELAY(); 
    } 

    int Check_Acknowledge(void) 
    { 
        //发送完每个字节检查SLAVE的应答信号 
        SET_SDA();                   //主器件释放SDA线 
        SET_SCL(); 
        DELAY(DELAY_TIME/2); 
        unsigned char b=inportb(0x378);    //采样信号线 
        DELAY(DELAY_TIME/2); 
        CLR_SCL(); 
        DELAY(); 
        if(b&0xSDA_PIN)            //SALVE返回1 
            return FLASE; 
        return TRUE; 
    } 

使用上述代码，你可以在PC上用并行口模拟I2C，进行实验、监控和调试。 