#include "sched.h"

char _schedTimerAdc;
char _schedTimerMotor;
char _schedTimerI2C;
char _schedTimerMotion;

char _schedQueue;
char _schedCycleQueue;

void Sched_Init(void)
{
	_schedTimerAdc    = 0;
	_schedTimerMotor  = 0;
	_schedTimerI2C    = 0;
	_schedTimerMotion = 0;
	
	_schedQueue = 0;
	
	Counter16_Tick_EnableInt_M;
	Counter16_Tick_Start_M;
}

void Sched_RunQueue(void)
{

	Counter16_Tick_DisableInt_M;
	_schedCycleQueue = _schedQueue;  // Make a copy of the queue for this cycle
	_schedQueue = 0;                 // Empty the scheduler queue
	Counter16_Tick_EnableInt_M;
	
	if (_schedCycleQueue == 0)
	{
		// Run short unscheduled background tasks here
		// e.g. maze filling
	}
	else
	{
		LED_Front_On();		
		
		// There is a scheduled task in the queue
		if (_schedCycleQueue & SCHED_RUN_ADC)
		{
			// ADC module is scheduled to run this cycle
			ADC_Update();
		}
		if (_schedCycleQueue & SCHED_RUN_MOTOR)
		{
			// Motor module is scheduled to run this cycle
			Motor_Update();
		}
		if (_schedCycleQueue & SCHED_RUN_I2C)
		{
			// I2C module is scheduled to run this cycle
			I2C_Update();
		}
		if (_schedCycleQueue & SCHED_RUN_MOTION)
		{
			// Motion control module is scheduled to run this cycle
			Motion_Update();
		}
		LED_Front_Off();
	}
}

void TICK_ISR(void)
{
	if (_schedTimerAdc == 0)
	{
		_schedQueue |= SCHED_RUN_ADC;
		_schedTimerAdc = (SCHED_PERIOD_ADC);
	}
	
	if (_schedTimerMotor == 0)
	{
		_schedQueue |= SCHED_RUN_MOTOR;
		_schedTimerMotor = (SCHED_PERIOD_MOTOR);
	}
	
	if (_schedTimerI2C == 0)
	{
		_schedQueue |= SCHED_RUN_I2C;
		_schedTimerI2C = (SCHED_PERIOD_I2C);
	}
	
	if (_schedTimerMotion == 0)
	{
		_schedQueue |= SCHED_RUN_MOTION;
		_schedTimerMotion = (SCHED_PERIOD_MOTION);
	}
	
	_schedTimerAdc --;
	_schedTimerMotor --;
	_schedTimerI2C --;
	_schedTimerMotion --;
}