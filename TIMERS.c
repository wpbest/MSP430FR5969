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
/* Contains functions for timers.
 *                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include <msp430.h>

#include "TIMERS.h"
#include "LED.h"
#include "USER.h"
#include "SYSTEM.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/******************************************************************************/
/*  Functions                                                           */
/******************************************************************************/

/******************************************************************************/
/* Functions                                                                  */
/******************************************************************************/

/******************************************************************************/
/* Init_Timers
 *
 * The function initializes the timers.
 *                                                                            */
/******************************************************************************/
void Init_Timers(void)
{
	Init_TimerA0();
	Init_TimerA1();
}

/******************************************************************************/
/* Init_TimerA0
 *
 * The function initializes timer A0 which is used for the timing between
 *  button 2 presses.
 *                                                                            */
/******************************************************************************/
void Init_TimerA0(void)
{
	TA0CTL |= TASSEL0; 		// Timer_A clock source select: 01b = ACLK
	TA0CTL &= ~(ID1 | ID0);  // Input divider: 00b = /1
	TA0EX0 |= TAIDEX2 | TAIDEX1 | TAIDEX0; // Input divider expansion: 111b = Divide by 8
	TMR_ModeTimerA0(OFF);
	TMR_SetTimerA0(0x0400);
	TMR_ResetTimerA0();
	TA0CCTL0 |= CCIE; // Capture/compare interrupt enable: 1b = Interrupt enabled
	TA0CCTL0 &= ~CCIFG; // clear flag
	TMR_InterruptTimerA0(ON);
}

/******************************************************************************/
/* Init_TimerA1
 *
 * The function initializes timer A1 which is used for the timing between
 *  button 1 presses.
 *                                                                            */
/******************************************************************************/
void Init_TimerA1(void)
{
	TA1CTL |= TASSEL0; 		// Timer_A clock source select: 01b = ACLK
	TA1CTL &= ~(ID1 | ID0);  // Input divider: 00b = /1
	TA1EX0 |= TAIDEX2 | TAIDEX1 | TAIDEX0; // Input divider expansion: 111b = Divide by 8
	TMR_ModeTimerA1(OFF);
	TMR_SetTimerA1(0x0400);
	TMR_ResetTimerA1();
	TA1CCTL0 |= CCIE; // Capture/compare interrupt enable: 1b = Interrupt enabled
	TA1CCTL0 &= ~CCIFG; // clear flag
	TMR_InterruptTimerA1(ON);
}

/******************************************************************************/
/* TMR_ModeTimerA0
 *
 * Controls the TimerA0 mode.
 *
 * Input: mode (OFF, UP, CONTINUOUS, or UP_DOWN)
 * Output: the previous mode
 * Action: controls the timer mode (MC bits)
 *                                                                            */
/******************************************************************************/
unsigned char TMR_ModeTimerA0(unsigned char state)
{
	unsigned char mode;
	unsigned short PreviousState;

	mode = (TA0CTL & (MC1 | MC0)) >> 4;
	if(mode == 0b00)
	{
		PreviousState = OFF;
	}
	else if(mode == 0b01)
	{
		PreviousState = UP;
	}
	else if(mode == 0b01)
	{
		PreviousState = CONTINUOUS;
	}
	else
	{
		PreviousState = UP_DOWN;
	}

	TA0CTL &= ~(MC1 | MC0);
	if(state == UP)
	{
		TA0CTL |= MC0; // 01b = Up mode: Timer counts up to TAxCCR0
	}
	else if(state == CONTINUOUS)
	{
		TA0CTL |= MC1; // 10b = Continuous mode: Timer counts up to 0FFFFh
	}
	else if(state == UP_DOWN)
	{
		TA0CTL |= (MC1 | MC0); // 11b = Up/down mode: Timer counts up to TAxCCR0 then down to 0000h
	}

	return PreviousState;
}

/******************************************************************************/
/* TMR_ModeTimerA1
 *
 * Controls the TimerA1 mode.
 *
 * Input: mode (OFF, UP, CONTINUOUS, or UP_DOWN)
 * Output: the previous mode
 * Action: controls the timer mode (MC bits)
 *                                                                            */
/******************************************************************************/
unsigned char TMR_ModeTimerA1(unsigned char state)
{
	unsigned char mode;
	unsigned short PreviousState;

	mode = (TA1CTL & (MC1 | MC0)) >> 4;
	if(mode == 0b00)
	{
		PreviousState = OFF;
	}
	else if(mode == 0b01)
	{
		PreviousState = UP;
	}
	else if(mode == 0b01)
	{
		PreviousState = CONTINUOUS;
	}
	else
	{
		PreviousState = UP_DOWN;
	}

	TA1CTL &= ~(MC1 | MC0);
	if(state == UP)
	{
		TA1CTL |= MC0; // 01b = Up mode: Timer counts up to TAxCCR0
	}
	else if(state == CONTINUOUS)
	{
		TA1CTL |= MC1; // 10b = Continuous mode: Timer counts up to 0FFFFh
	}
	else if(state == UP_DOWN)
	{
		TA1CTL |= (MC1 | MC0); // 11b = Up/down mode: Timer counts up to TAxCCR0 then down to 0000h
	}

	return PreviousState;
}

/******************************************************************************/
/* TMR_InterruptTimerA0
 *
 * Controls the TimerA0 interrupt.
 *
 * Input: state (ON or OFF)
 * Output: the previous state of the Timer interrupt
 * Action: controls the timer interrupt (TAIE bits)
 *                                                                            */
/******************************************************************************/
unsigned char TMR_InterruptTimerA0(unsigned char state)
{
	unsigned char status = FALSE;

	if(TA0CTL & TAIE)
	{
		status = TRUE;
	}

	if(state)
	{
		TA0CTL |= TAIE;
	}
	else
	{
		TA0CTL &= ~TAIE;
	}
	return status;
}

/******************************************************************************/
/* TMR_InterruptTimerA1
 *
 * Controls the TimerA1 interrupt.
 *
 * Input: state (ON or OFF)
 * Output: the previous state of the Timer interrupt
 * Action: controls the timer interrupt (TAIE bits)
 *                                                                            */
/******************************************************************************/
unsigned char TMR_InterruptTimerA1(unsigned char state)
{
	unsigned char status = FALSE;

	if(TA1CTL & TAIE)
	{
		status = TRUE;
	}

	if(state)
	{
		TA1CTL |= TAIE;
	}
	else
	{
		TA1CTL &= ~TAIE;
	}
	return status;
}

/******************************************************************************/
/* TMR_ResetTimerA0
 *
 * Restarts TimerA0.
 *
 * Input: N/A
 * Output: N/A
 * Action: clears TAR, the clock divider logic (the divider setting remains
 *  unchanged), and the count direction. The TACLR bit is automatically reset
 *  and is always read as zero.
 *                                                                            */
/******************************************************************************/
void TMR_ResetTimerA0(void)
{
    TA0CTL |= TACLR; // Timer_A clear
}

/******************************************************************************/
/* TMR_ResetTimerA1
 *
 * Restarts TimerA1.
 *
 * Input: N/A
 * Output: N/A
 * Action: clears TAR, the clock divider logic (the divider setting remains
 *  unchanged), and the count direction. The TACLR bit is automatically reset
 *  and is always read as zero.
 *                                                                            */
/******************************************************************************/
void TMR_ResetTimerA1(void)
{
    TA1CTL |= TACLR; // Timer_A clear
}

/******************************************************************************/
/* TMR_SetTimerA0
 *
 * Sets the TA0CCR0 register for TAR to compare.
 *
 * Input: N/A
 * Output: N/A
 * Action:
 * 	Compare mode: TAxCCRn holds the data for the comparison to the
 *   timer value in the Timer_A Register, TAR.
 *  Capture mode: The Timer_A Register, TAR, is copied into the TAxCCRn
 *   register when a capture is performed.
 *                                                                            */
/******************************************************************************/
void TMR_SetTimerA0(unsigned short time)
{
    TA0CCR0 = time;
}

/******************************************************************************/
/* TMR_SetTimerA1
 *
 * Sets the TA1CCR0 register for TAR to compare.
 *
 * Input: N/A
 * Output: N/A
 * Action:
 * 	Compare mode: TAxCCRn holds the data for the comparison to the
 *   timer value in the Timer_A Register, TAR.
 *  Capture mode: The Timer_A Register, TAR, is copied into the TAxCCRn
 *   register when a capture is performed.
 *                                                                            */
/******************************************************************************/
void TMR_SetTimerA1(unsigned short time)
{
    TA1CCR0 = time;
}

/******************************************************************************/
/* TMR_GetTimerA0
 *
 * Gets the TA0R register.
 *
 * Input: N/A
 * Output: Count of TimerA0
 * Action: Reads the TimerA0 count and returns.
 *                                                                            */
/******************************************************************************/
unsigned short TMR_GetTimerA0(void)
{
    return TA0R;
}

/******************************************************************************/
/* TMR_GetTimerA1
 *
 * Gets the TA1R register.
 *
 * Input: N/A
 * Output: Count of TimerA1
 * Action: Reads the TimerA1 count and returns.
 *                                                                            */
/******************************************************************************/
unsigned short TMR_GetTimerA1(void)
{
    return TA1R;
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
