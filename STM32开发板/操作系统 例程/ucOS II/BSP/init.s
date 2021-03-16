;******************************************************************************
;
;                               STARTUP CODE
;                                
;                             KEIL's uVision3 
;                   (RealView Microprocessor Developer Kit)
;
; Filename      : init.s
;******************************************************************************

                PRESERVE8
                AREA   INIT, CODE, READONLY                     ; Name this block of code                                   ;
                THUMB

;******************************************************************************
;                                  IMPORTS
;******************************************************************************
                                
                IMPORT  __main

;******************************************************************************
;                                  EXPORTS
;******************************************************************************

                EXPORT  ResetHndlr

;//bhs ----------------------------------------------------------------------------------------
				EXPORT __BASEPRICONFIG		   ;//bhs
				EXPORT __GetBASEPRI
				EXPORT __RESETFAULTMASK
				EXPORT __RESETPRIMASK
				EXPORT __SETFAULTMASK
				EXPORT __SETPRIMASK
				EXPORT __WFI
                EXPORT __WFE



;******************************************************************************
;                                DEFINITIONS
;******************************************************************************


;******************************************************************************
;                             PERFORM ROM/RAM REMAPPING
;******************************************************************************                

                ENTRY
;*******************************************************************************
; Function Name  : __BASEPRICONFIG
; Description    : Assembler function to set the Base Priority.
; Input          : - r0 : Base Priority new value  
; Return         : None
;*******************************************************************************
__BASEPRICONFIG

  MSR BASEPRI, r0
  BX r14

;*******************************************************************************
; Function Name  : __GetBASEPRI
; Description    : Assembler function to get the Base Priority value.
; Input          : None 
; Return         : - r0 : Base Priority value 
;*******************************************************************************
__GetBASEPRI

  MRS r0, BASEPRI_MAX
  BX r14

;*******************************************************************************
; Function Name  : __RESETFAULTMASK
; Description    : Assembler function to reset the FAULTMASK.
; Input          : None 
; Return         : None
;*******************************************************************************
__RESETFAULTMASK

  CPSIE f
  BX r14


;*******************************************************************************
; Function Name  : __RESETPRIMASK
; Description    : Assembler function to reset the PRIMASK.
; Input          : None 
; Return         : None
;*******************************************************************************
__RESETPRIMASK

  CPSIE i
  BX r14

;*******************************************************************************
; Function Name  : __SETFAULTMASK
; Description    : Assembler function to set the FAULTMASK.
; Input          : None 
; Return         : None
;*******************************************************************************
__SETFAULTMASK

  CPSID f
  BX r14

;*******************************************************************************
; Function Name  : __SETPRIMASK
; Description    : Assembler function to set the PRIMASK.
; Input          : None 
; Return         : None
;*******************************************************************************
__SETPRIMASK

  CPSID i
  BX r14

;*******************************************************************************
; Function Name  : __WFI
; Description    : Assembler function for the WFI instruction.
; Input          : None
; Return         : None
;*******************************************************************************
__WFI 
 
    WFI
    BX r14

;*******************************************************************************
; Function Name  : __WFE
; Description    : Assembler function for the WFE instruction.
; Input          : None
; Return         : None
;*******************************************************************************
__WFE

    WFE
    BX r14

;//bhs ----------------------------------------------------------------------------------------

ResetHndlr      

;******************************************************************************
;                              SETUP STACK POINTERS
;******************************************************************************
                

;******************************************************************************
;                                   MOVE TO MAIN
;******************************************************************************
                ldr     r0, =__main
                bx      r0                             	    ; Save this in register for possible long jump              ;

                ALIGN
                END 
        
