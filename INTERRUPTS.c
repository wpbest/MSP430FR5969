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
/* Interrupt Vector Options
 *
 * VECTOR NAMES:
 *
 * AES256_VECTOR
 * RTC_VECTOR
 * PORT4_VECTOR
 * PORT3_VECTOR
 * TIMER3_A1_VECTOR
 * TIMER3_A0_VECTOR
 * PORT2_VECTOR
 * TIMER2_A1_VECTOR
 * TIMER2_A0_VECTOR
 * PORT1_VECTOR
 * TIMER1_A1_VECTOR
 * TIMER1_A0_VECTOR
 * DMA_VECTOR
 * USCI_A1_VECTOR
 * TIMER0_A1_VECTOR
 * TIMER0_A0_VECTOR
 * ADC12_VECTOR
 * USCI_B0_VECTOR
 * USCI_A0_VECTOR
 * WDT_VECTOR
 * TIMER0_B1_VECTOR
 * TIMER0_B0_VECTOR
 * COMP_E_VECTOR
 * UNMI_VECTOR
 * SYSNMI_VECTOR
 * RESET_VECTOR
 *
 * Vector information found here:
 * C:\ti\ccsv6\ccs_base\msp430\include
 *                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include <msp430.h>

#include "BUTTON.h"
#include "TIMERS.h"
#include "LED.h"
#include "USER.h"
#include "SYSTEM.h"

/******************************************************************************/
/* Global Variables                                                           */
/******************************************************************************/

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/******************************************************************************/
/* Port 1 interrupt (used for button 2)
 *                                                                            */
/******************************************************************************/
#pragma vector=PORT1_VECTOR
__interrupt void Port1_ISR(void)
{
	if(P1IFG & Pin_Button2)
	{
		/* Button 2 was pressed */
		LED_GreenToggle();
		TMR_ResetTimerA0();
		TMR_ModeTimerA0(UP);
		BUT_Button2Interrupt(OFF);
		P1IFG &= ~Pin_Button2;
	}
}

/******************************************************************************/
/* Port 4 interrupt (used for button 1)
 *                                                                            */
/******************************************************************************/
#pragma vector=PORT4_VECTOR
__interrupt void Port4_ISR(void)
{
	WAKE();
	if(P4IFG & Pin_Button1)
	{
		/* Button 1 was pressed */
		LED_RedToggle();
		TMR_ResetTimerA1();
		TMR_ModeTimerA1(UP);
		BUT_Button1Interrupt(OFF);
		P4IFG &= ~Pin_Button1;
	}
}

/******************************************************************************/
/* Timer A0 interrupt (used for button 2)
 *                                                                            */
/******************************************************************************/
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TimerA0_ISR(void)
{
	WAKE();
	TMR_ModeTimerA0(OFF);
	P1IFG &= ~Pin_Button2;
	BUT_Button2Interrupt(ON);
	TA0CCTL0 &= ~CCIFG;
}

/******************************************************************************/
/* Timer A1 interrupt (used for button 1)
 *                                                                            */
/******************************************************************************/
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TimerA1_ISR(void)
{
	WAKE();
	TMR_ModeTimerA1(OFF);
	P4IFG &= ~Pin_Button1;
	BUT_Button1Interrupt(ON);
	TA1CCTL0 &= ~CCIFG;
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
