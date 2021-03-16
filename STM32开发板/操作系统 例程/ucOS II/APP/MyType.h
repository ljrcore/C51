#if !defined( _MYTYPE_H )
#define _MYTYPE_H


//���ñ������Ͷ���
typedef unsigned char   tByte;
typedef unsigned int    tWord;



typedef unsigned char   uchar;
typedef unsigned int    uint;//int�е�CPU��32λ
typedef unsigned long   ulong;

#ifndef   BOOL
 //typedef unsigned char 	BOOL;
#endif

#define	int8            signed char
#define	int16           signed short
#define	int32           signed long
#define	uint8           unsigned char
#define	uint16          unsigned short
#define	uint32          unsigned long


typedef unsigned char BOOLEAN;
typedef unsigned char INT8U;      /* Unsigned  8 bit quantity         */
typedef signed   char INT8S;      /* Signed    8 bit quantity         */
typedef unsigned short INT16U;    /* Unsigned 16 bit quantity         */
typedef signed   short INT16S;    /* Signed   16 bit quantity         */
//typedef unsigned long INT32U;       /* Unsigned 32 bit quantity       */
//typedef signed   long INT32S;       /* Signed   32 bit quantity       */
typedef float FP32;       /* Single precision floating point    */
typedef double FP64;      /* Double precision floating point      */

#define BYTE       INT8S         /* Define data types for backward compatibility ...   */
#define UBYTE      INT8U       /* ... to uC/OS V1.xx.  Not actually needed for ...   */
#define WORD       INT16S      /* ... uC/OS-II.            */
#define UWORD      INT16U
#define LONG       INT32S
#define ULONG      INT32U

typedef void (*pFUN)(void);
typedef void (*pFUNpar)(uint8);
typedef void (*pFUNparU8)(uint8);
typedef void (*pFUNparU16)(uint16);

typedef uint8 (*pU8FUN)(void);

//typedef unsigned char OS_STK;       /* Each stack entry is 8-bit wide      */
//typedef INT16U             OS_FLAGS;   /* Date type for event flag bits (8, 16 or 32 bits)             */



#define SetBit(Value,Bit)  ( Value |= (0x01<<Bit) )     //Bit(0~7)//һ��Ҫ��()
#define ClrBit(Value,Bit)  ( Value &= (~(0x01<<Bit)) )

#define SetBit32(Value,Bit)  ( Value |= (1UL<<Bit) )     //Bit(0~31)//һ��Ҫ��()
#define ClrBit32(Value,Bit)  ( Value &= (~(1UL<<Bit)) )


#define BIT(n)             ( (uint8)((uint8)1<<n) )    //n(0~7)
#define BIT8(n)            ( (uint8)((uint8)1<<n) )    //n(0~7)
#define BIT16(n)           (  (uint16)((uint16)1<<n) )   //n(0~31)
#define BIT32(n)           (  (uint32)((uint32)1UL<<n) )   //n(0~31) 


//����ĳλ�Ƿ�Ϊ1��Ϊ1����1��Ϊ0����Ϊ0
#define	isBit(dat, n)    ((dat&BIT8(n)) ? 1: 0)//0~7
#define isBit8(dat, n)   ((dat&BIT8(n)) ? 1: 0)//0~7

//����ĳλ�Ƿ�Ϊ1��Ϊ1����1��Ϊ0����Ϊ0
#define	isBit16(dat, n)  ((dat&BIT16(n)) ? 1: 0)//0~15

#define	isBit32(dat, n)  ((dat&BIT32(n)) ? 1: 0)//0~31

//��16λ���ݿ�����8λ���ݣ����ֽ���ǰ
#define cpyU8fU16(U8dat, U16dat)     \
{                                    \
   *((uint8 *)(U8dat+0))=U16dat>>8;  \
   *((uint8 *)(U8dat+1))=U16dat;     \
}

//��32λ���ݿ�����8λ���ݣ����ֽ���ǰ
#define cpyU8fU32(U8dat, U32dat)     \
{                                    \
   *((uint8 *)U8dat)=(uint8)(U32dat>>24);     \
   *((uint8 *)(U8dat+1))=(uint8)(U32dat>>16); \
   *((uint8 *)(U8dat+2))=(uint8)(U32dat>>8);  \
   *((uint8 *)(U8dat+3))=(uint8)U32dat;     \
}

//��8λ���ݿ�����16λ���ݣ����ֽ���ǰ
#define cpyU16fU8(U16dat, U8dat)     \
{                                    \
   U16dat = *((uint8 *)U8dat);       \
   U16dat <<= 8;                     \
   U16dat += *((uint8 *)(U8dat+1));  \
}

//��8λ���ݿ�����32λ���ݣ����ֽ���ǰ
#define cpyU32fU8(U32dat, U8dat)     \
{                                    \
   U32dat = *((uint8 *)U8dat);       \
   U32dat <<= 8;                     \
   U32dat += *((uint8 *)(U8dat+1));  \
   U32dat <<= 8;                     \
   U32dat += *((uint8 *)(U8dat+2));  \
   U32dat <<= 8;                     \
   U32dat += *((uint8 *)(U8dat+3));  \
}


//  Intel && AMD
#define  LITTLE_ENDIAN 1

 // �ֽ���
#if defined(BIG_ENDIAN) && !defined(LITTLE_ENDIAN)

   #define htons(A)   (A)
   #define htonl(A)   (A)
   #define ntohs(A)   (A)
   #define ntohl(A)   (A)

#elif defined(LITTLE_ENDIAN) && !defined(BIG_ENDIAN)

   #define htons(A)    ((((uint16)(A) & 0xff00) >> 8) | \
                        (((uint16)(A) & 0x00ff) << 8))
   #define htonl(A)    ((((uint32)(A) & 0xff000000) >> 24) | \
                        (((uint32)(A) & 0x00ff0000) >> 8) | \
                        (((uint32)(A) & 0x0000ff00) << 8) | \
                        (((uint32)(A) & 0x000000ff) << 24))
   #define ntohs htons
   #define ntohl htonl

#else

   #error "Either BIG_ENDIAN or LITTLE_ENDIAN must be #defined, but not both."
   
   int checkCPUendian()  //��鴦������big-endian����little-endian
   {
      union 
      {
      	unsigned int a;
       unsigned char b;            
      }c;
      c.a = 1;
      return (c.b == 1);       
   }  /*return 1 : little-endian, return 0:big-endian*/
#endif


//����һЩ����ʱ���ղ�����

//#define NOP()               __asm { nop }
//
//#define DelayNop1()         {NOP();}
//#define DelayNop2()         {DelayNop1(); NOP();}
//#define DelayNop3()         {DelayNop2(); NOP();}
//#define DelayNop4()         {DelayNop3(); NOP();}
//#define DelayNop5()         {DelayNop4(); NOP();}
//#define DelayNop6()         {DelayNop5(); NOP();}
//#define DelayNop7()         {DelayNop6(); NOP();}
//#define DelayNop8()         {DelayNop7(); NOP();}
//#define DelayNop9()         {DelayNop8(); NOP();}
//
//#define DelayNop(N)         DelayNop##N()


#define __NOP1__  __asm { nop }
#define __NOP2__ __NOP1__ __NOP1__
#define __NOP4__ __NOP2__ __NOP2__
#define __NOP8__ __NOP4__ __NOP4__
#define __NOP16__ __NOP8__ __NOP8__
#define __NOP32__ __NOP16__ __NOP16__
#define __NOP64__ __NOP32__ __NOP32__
#define __NOP128__ __NOP64__ __NOP64__


#define DelayNop(a)             \
    if ((a)&(0x01))    {__NOP1__}                    \
    if ((a)&(0x02))    {__NOP2__}                    \
    if ((a)&(0x04))    {__NOP4__}                    \
    if ((a)&(0x08))    {__NOP8__}                    \
    if ((a)&(0x10))    {__NOP16__}                    \
    if ((a)&(0x20))    {__NOP32__}                    \
    if ((a)&(0x40))    {__NOP64__}                    \
    if ((a)&(0x80))    {__NOP128__}                    




#include "BinType.h"




#endif
