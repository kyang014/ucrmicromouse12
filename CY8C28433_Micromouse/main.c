//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "motor.h"
#include "ui.h"
#include "adc.h"
#include "sched.h"

#pragma data:page1  // Gets RAM page 1 all to itself
unsigned char mazeA[256];
#pragma data:page2  // Gets RAM page 2 all to itself
unsigned char mazeB[256];
#pragma data:page0
//unsigned char mystack[256];
#pragma data:data 


void main(void)
{
	// -------------------- Setup --------------------
	
	M8C_EnableGInt; // Enable Global Interrupts
	
	// motor.h
	Encoder_Init();
	Motor_Init();
	
	// ui.h
	LED_Init();
	I2C_Init();
	
	// adc.h
	ADC_Init();

	// sched.h
	Sched_Init();

	SleepTimer_Start();
	SleepTimer_EnableInt();

	// ------------------ End Setup ------------------

	//while(1)
	//{
//		Encoder_PauseCount();
//		if (encoderCountLeft > encoderCountRight)
//		{
//			PWM8_LeftFwd_WritePulseWidth(0);
//			PWM8_LeftRev_WritePulseWidth(255);
//		}
//		else if (encoderCountLeft < encoderCountRight)
//		{
//			PWM8_LeftFwd_WritePulseWidth(255);
//			PWM8_LeftRev_WritePulseWidth(0);
//		}
//		else
//		{
//			PWM8_LeftFwd_WritePulseWidth(0);
//			PWM8_LeftRev_WritePulseWidth(0);
//		}
//		Encoder_ResumeCount();
	//}
	
	SleepTimer_SyncWait(8, SleepTimer_WAIT_RELOAD);
	
	while(1)
	{
		Sched_RunQueue();
	}
}

