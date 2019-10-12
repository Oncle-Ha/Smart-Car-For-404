/*****************************************************************************
* (c) Copyright Freescale Semiconductor, Inc 2012-2013, All Rights Reserved  *
******************************************************************************

******************************************************************************
*                                                                            *
*             EEPROM Emulation Driver For FTFx                               *
*                                                                            *
* FILE NAME     :  ee_demo.h                                                 *
* DATE          :  Dec 25,2013                                               *
*                                                                            *
* AUTHOR        :  FPT Team                                                  *
* E-mail        :  r56611@freescale.com                                      *
*                                                                            *
******************************************************************************/

/************************** CHANGES ******************************************
0.1.0       12.25.2013      FPT Team      Initial Version                     
******************************************************************************/
#ifndef _EE_DEMO_H_
#define _EE_DEMO_H_

#define DEMO_PASS               0x0U
#define DEMO_FAIL               0xFFU

/* Start address of Eeprom emulation in byte */
#if defined(EVB_MT128) 
    #define EE_START_ADDRESS        0x2c00U
#elif defined(TRK_KEA8)
    #define EE_START_ADDRESS        0x1400U
#endif

#define SWAPPING_NUMBER         0x3U

#define CALLBACK_SIZE           0x40U    

#endif /* _EE_DEMO_H_ */
