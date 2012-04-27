//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "motor.h"
#include "ui.h"
#include "adc.h"
#include "sched.h"

#pragma data:page0
unsigned char mazeFloodQueue[128];
#pragma data:page1  // Gets RAM page 1 all to itself
unsigned char mazeFlags[256];
#pragma data:page2  // Gets RAM page 2 all to itself
unsigned char mazeRouting[256];
#pragma data:data


void main(void)
{
	// -------------------- Setup --------------------
	
	M8C_EnableGInt; // Enable Global Interrupts
	Encoder_Init(); // encoder.h
	Motor_Init();   // motor.h
	LED_Init();     // ui.h
	I2C_Init();     // ui.h
	ADC_Init();     // adc.h
	Sched_Init();   // sched.h
	Motion_Init();  // motion.h
	
	SleepTimer_Start();
	SleepTimer_EnableInt();

	// ------------------ End Setup ------------------

	SleepTimer_SyncWait(8, SleepTimer_WAIT_RELOAD);
	
	Motion_SetNextCommand(MOTION_COMMAND_FWD);
	
	while(1)
	{
		Sched_RunQueue();
	}
}

