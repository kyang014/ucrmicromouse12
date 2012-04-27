#include "motion.h"



extern SEncCount motorSetpoint;

char state = 0;

void Motion_Init(void)
{
}

void Motion_Update(void)
{
	if (state)
	{
		if (motorSetpoint.right < (MOTION_COUNT_ROT90*2))
		{
			motorSetpoint.left -= 4;
			motorSetpoint.right += 4;
		}
		else
		{
			state = 0;
			Motor_Center();
		}
	}
	else
	{
		if (motorSetpoint.left < (MOTION_COUNT_ROT90*2))
		{
			motorSetpoint.left += 4;
			motorSetpoint.right -= 4;
		}
		else
		{
			state = 1;
			Motor_Center();
		}
	}
}