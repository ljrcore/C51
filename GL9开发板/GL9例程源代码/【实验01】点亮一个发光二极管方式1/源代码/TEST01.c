////////////////////////////////////////////////////////////////////////////
//                给力者单片机开发学习系统，开发学习都给力！              //
////////////////////////////////////////////////////////////////////////////
//                     学习51单片机，其实可以很简单                       //
////////////////////////////////////////////////////////////////////////////
//                宁波芯动电子有限公司  www.MovingChip.com                //
////////////////////////////////////////////////////////////////////////////

#include<AT89X52.h>       //调用51单片机的头文件

//---------------------------------------
//名称: 主函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120913
//---------------------------------------
void main(void)            //主函数,单片机开机后就是从这个函数开始运行
{

    P0_0=1;                //按位方式写PO.0=1
    P0_1=0;                //按位方式写PO.1=0
    P0_2=0;                //按位方式写PO.2=0
    P0_3=0;                //按位方式写PO.3=0
    P0_4=0;                //按位方式写PO.4=0
    P0_5=0;                //按位方式写PO.5=0
    P0_6=0;                //按位方式写PO.6=0
    P0_7=0;                //按位方式写PO.7=0
    while(1)               //死循环,单片机初始化后,将一直运行这个死循环
    {

    }
}

