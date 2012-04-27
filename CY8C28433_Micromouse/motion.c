#include "motion.h"



extern SEncCount motorSetpoint;



void Motion_Init(void)
{
}

void Motion_Update(void)
{
	if (motorSetpoint.right < (MOTION_COUNT_ROT90*2))
	{
		motorSetpoint.left -= 4;
		motorSetpoint.right += 4;
	}
}