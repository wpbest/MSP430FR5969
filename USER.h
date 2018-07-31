/******************************************************************************/
/* Change log                                                                 *
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 10/04/15     3.0_DW0a    Initial project make.
 *                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#ifndef USER_H
#define	USER_H

#include <msp430.h>

#include "SYSTEM.h"

/******************************************************************************/
/* Firmware Version                                                           */
/******************************************************************************/
#define CPU_VERSION    "3"
#define CPU_REVISION   "0"
#define CPU_ALPHA      ""
#define CPU_BRANCH     "DW0b"

/******************************************************************************/
/* PCB board
 *
 * This code is used with boards:
 * 1. MSP430FR5969_LAUNCHPAD      (Debug/Release MSP430FR5969 Launchpad)      */
/******************************************************************************/
#define MSP430FR5969_LAUNCHPAD

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/
#define ON 1
#define OFF 0
#define TRUE 1
#define FALSE 0
#define OUTPUT 1
#define INPUT 0
#define PASS 1
#define FAIL 0
#define YES 1
#define NO 0

/******************************************************************************/
/* Pin Defines                                                                */
/******************************************************************************/

/************* 32768 crystal *************/
/* Connected to the LFXIN */
#define Port_LF_Crystal1	P4DIR // PJ.4
#define Pin_LF_Crystal1	0x10  // PJ.4

/* Connected to the LFXOUT */
#define Port_LF_Crystal2	P4DIR // PJ.5
#define Pin_LF_Crystal2	0x20  // PJ.5

/************* Green LED *************/
/* Connected to the green LED indicator */
#define Port_GreenLED	P1DIR // P1.0
#define Pin_GreenLED	0x01  // P1.0

/************* Red LED *************/
/* Connected to the Red LED indicator */
#define Port_RedLED	P4DIR // P4.6
#define Pin_RedLED	0x40  // P4.6

/************* Button 1 (SW 1) *************/
/* Connected to pushbutton switch S1 */
#define Port_Button1	P4DIR // P4.5
#define Pin_Button1		0x20  // P4.5

/************* Button 2 (SW 2) *************/
/* Connected to pushbutton switch S2 */
#define Port_Button2	P1DIR // P1.1
#define Pin_Button2		0x02  // P1.1

/******************************************************************************/
/* Version variables                                                          */
/******************************************************************************/
extern const unsigned char Version[];
extern const unsigned char Revision[];
extern const unsigned char Alpha[];
extern const unsigned char Branch_Version[];

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void Init_App(void);
void Init_System (void);

#endif	/* USER_H */
