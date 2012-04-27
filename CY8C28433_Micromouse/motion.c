#include "motion.h"



extern SEncCount motorSetpoint;



void Motion_Init(void)
{
}

void Motion_Update(void)
{
	if (motorSetpoint.left < MOTION_COUNT_CELL)
	{
		motorSetpoint.left += 4;
		motorSetpoint.right += 4;
	}
}