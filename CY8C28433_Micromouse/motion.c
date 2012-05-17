#include "motion.h"

extern SEncCount motorSetpoint;

char motionCommandNext;
char motionCommandCurrent;

int _distanceTraveled;

void Motion_Init(void)
{
	motionCommandNext = MOTION_COMMAND_NONE;
	motionCommandCurrent = MOTION_COMMAND_NONE;
}

void Motion_Update(void)
{
	if (motionCommandCurrent == MOTION_COMMAND_NONE)
	{
		// If not currently running a command, load next command.
		// There is no next command, nothing happens and mouse maintains position
		motionCommandCurrent = motionCommandNext;
		motionCommandNext = MOTION_COMMAND_NONE;
		
		Motor_Center();
		
		// These should only run once when the command is first loaded
		if (motionCommandCurrent == MOTION_COMMAND_NONE)
		{
			// Center setpoint and just stay in one place
		}
		else if (motionCommandCurrent == MOTION_COMMAND_FWD)
		{
			// setup for Forward
			
		}
		else if (motionCommandCurrent == MOTION_COMMAND_LEFT90)
		{
			// setup for Left90
		}
		else if (motionCommandCurrent == MOTION_COMMAND_RIGHT90)
		{
			// setup for Right90
		}
	}
	
	// Run movement commands if they are active
	if (motionCommandCurrent == MOTION_COMMAND_FWD)   //------------------------------------
	{
		_Motion_CommandForward();
	}
	else if (motionCommandCurrent == MOTION_COMMAND_LEFT90)  //------------------------------------
	{
		_Motion_CommandLeft90();
	}
	else if (motionCommandCurrent == MOTION_COMMAND_RIGHT90)  //------------------------------------
	{
		_Motion_CommandRight90();
	}

}

void _Motion_CommandForward(void)
{
	if (motorSetpoint.right < MOTION_COUNT_CELL)
		{
			motorSetpoint.right += MOTION_BASE_VELOCITY - 1;
			motorSetpoint.left += MOTION_BASE_VELOCITY;
			
			motorSetpoint.left = abs(motorSetpoint.left);
			
			
			
		}
		else
		{
			// Setpoint reached
			motionCommandCurrent = MOTION_COMMAND_NONE;
		}

}

void _Motion_CommandRight90(void)
{
	if (motorSetpoint.left < MOTION_COUNT_ROT90)
	{
		motorSetpoint.left += MOTION_BASE_VELOCITY;
		if (motorSetpoint.left > MOTION_COUNT_ROT90) motorSetpoint.left = MOTION_COUNT_ROT90;
		
		motorSetpoint.right -= MOTION_BASE_VELOCITY;
		if (motorSetpoint.right < -MOTION_COUNT_ROT90) motorSetpoint.right = -MOTION_COUNT_ROT90;
	}
	else
	{
		// Setpoint reached
		motionCommandCurrent = MOTION_COMMAND_NONE;
	}
}

void _Motion_CommandLeft90(void)
{
	if (motorSetpoint.right < MOTION_COUNT_ROT90)
	{
		motorSetpoint.right += MOTION_BASE_VELOCITY;
		if (motorSetpoint.right > MOTION_COUNT_ROT90) motorSetpoint.right = MOTION_COUNT_ROT90;
		
		motorSetpoint.left -= MOTION_BASE_VELOCITY;
		if (motorSetpoint.left < -MOTION_COUNT_ROT90) motorSetpoint.left = -MOTION_COUNT_ROT90;
	}
	else
	{
		// Setpoint reached
		motionCommandCurrent = MOTION_COMMAND_NONE;
	}
}