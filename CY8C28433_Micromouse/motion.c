#include "motion.h"

int _motion_lastEncoderCountLeft;

void Motion_Init(void)
{
}

void Motion_Update(void)
{ 
	int _leftSpeed = 255;
	int _rightSpeed = 200;
	
	_leftSpeed -= (adcIRRight*2);
	_rightSpeed -= (adcIRLeft*2);
	
	if (adcIRRight > adcIRLeft)
	{
		_leftSpeed -= (adcIRFront*2);
	}
	else
	{
		_rightSpeed -= (adcIRFront*2);
	}
	
	Motor_Drive_Left(_leftSpeed);
	Motor_Drive_Right(_rightSpeed);
}