////////////////////////////////////////////////////////////////////////////
//                给力者单片机开发学习系统，开发学习都给力！              //
////////////////////////////////////////////////////////////////////////////
//                     学习51单片机，其实可以很简单                       //
////////////////////////////////////////////////////////////////////////////
//                宁波芯动电子有限公司  www.MovingChip.com                //
////////////////////////////////////////////////////////////////////////////

#include <AT89X52.h>       //调用51单片机的头文件

//---------------------------------------
//名称: 主函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120914
//---------------------------------------
void main(void)            //主函数,单片机开机后就是从这个函数开始运行
{

    P2=0x06;               //按字节方式写P2口I/O状态
    while(1)               //死循环,单片机初始化后,将一直运行这个死循环
    {

    }
}


