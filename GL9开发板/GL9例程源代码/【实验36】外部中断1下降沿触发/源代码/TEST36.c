////////////////////////////////////////////////////////////////////////////
//                给力者单片机开发学习系统，开发学习都给力！              //
////////////////////////////////////////////////////////////////////////////
//                     学习51单片机，其实可以很简单                       //
////////////////////////////////////////////////////////////////////////////
//                宁波芯动电子有限公司  www.MovingChip.com                //
////////////////////////////////////////////////////////////////////////////

#include <AT89X52.h>       //调用51单片机的头文件

unsigned char k;
//---------------------------------------
//定义一个数据表格
unsigned char code TAB[10]=
{                          //定义表格一定要使用code，这样会做到程序存储区中
    0x3F,                  //表格第1步数据0b00111111
    0x06,                  //表格第2步数据0b00000110
    0x5B,                  //表格第3步数据0b01011011
    0x4F,                  //表格第4步数据0b01001111
    0x66,                  //表格第5步数据0b01100110
    0x6D,                  //表格第6步数据0b01101101
    0x7D,                  //表格第7步数据0b01111101
    0x07,                  //表格第8步数据0b00000111
    0x7F,                  //表格第9步数据0b01111111
    0x6F,                  //表格第10步数据0b01101111
};

//---------------------------------------
//名称：外部INT1中断服务程序
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120914
//---------------------------------------
void INIT1(void) interrupt 2 
{

    //***此处用户自行添加外部INT1中断处理程序***
	k++;
	P2=TAB[k%10];          //数码管监控显示K最后一位数字
    //******************************************

}
//---------------------------------------
//名称: 主函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120914
//---------------------------------------
void main(void)            //主函数,单片机开机后就是从这个函数开始运行
{

    //***外部中断INT1初始化***
    IT1=1;                 //下降沿触发方式
    EX1=1;                 //外部INT1中断允许
    //**********************

    //***开全局中断设置****
    //外部中断INT1设置了中断允许,此处要开全局中断
    EA=1;                  //开全局中断
    //*********************
	 P2=TAB[0];         //开机后数码管显示0
    while(1)               //死循环,单片机初始化后,将一直运行这个死循环
    {
        

    }
}



