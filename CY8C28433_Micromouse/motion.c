#include "motion.h"

int _motion_lastEncoderCountLeft;

void Motion_Init(void)
{
}

void Motion_Update(void)
{ 
	int _drivePower = 255 - (adcIRFront / 2);
	Motor_Drive_Left(_drivePower);
	Motor_Drive_Right(_drivePower);
}