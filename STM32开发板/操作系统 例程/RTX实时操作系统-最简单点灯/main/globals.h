#if !defined( _GLOBALS_H )
#define _GLOBALS_H



#ifdef   SYS_GLOBALS
  #define  GLOBALS
#else
  #define  GLOBALS  extern
#endif

GLOBALS uint32 volatile gTimer_1ms;

GLOBALS OS_TID rd_task;
GLOBALS OS_TID wg_task;
GLOBALS OS_TID TID_ICCardTask;
GLOBALS OS_TID TID_AudioTask;

#define  IntervalTimems(time)          \
{                                        \
   if( (gTimer_1ms-counter)>=(time) )    \
     counter=gTimer_1ms;                 \
   else                                  \
    return;                              \
}

#endif

