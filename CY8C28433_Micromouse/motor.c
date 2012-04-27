#include "motor.h"

SEncCount _iState;
SEncCount motorSetpoint;

void Motor_Init(void)
{
	// Start motor PWMs
	PWM8_LeftFwd_Start();
	PWM8_LeftRev_Start();
	PWM8_RightFwd_Start();
	PWM8_RightRev_Start();

	motor_left_enable();
	motor_right_enable();
	
	_iState.left  = 0;
	_iState.right = 0;
	motorSetpoint.left  = 0;
	motorSetpoint.right = 0;
}

void Motor_Update(void)
{
	SEncCount _error;
	SEncCount _pTerm;
	
#ifdef MOTOR_ENABLE_INTEGRAL
	SEncCount _iTerm;
#endif

	
	// Calculate error from setpoint
	Encoder_PauseCount();  // Temporaily disable encoder interrupts
	_error.left  = motorSetpoint.left - encoderCurrentCount.left;
	_error.right = motorSetpoint.right - encoderCurrentCount.right;
	Encoder_ResumeCount();
	
	// Calculate proportional corrections
	_pTerm.left  = _error.left  * MOTOR_PGAIN;
	_pTerm.right = _error.right * MOTOR_PGAIN;

#ifdef MOTOR_ENABLE_INTEGRAL
	// Calculate the integral state with limiting
	_iState.left  += _error.left;
	     if (_iState.left > MOTOR_IMAX) _iState.left = MOTOR_IMAX;  // limit upper bound
	else if (_iState.left < MOTOR_IMIN) _iState.left = MOTOR_IMIN;  // limit lower bound

	_iState.right += _error.right;
	     if (_iState.right > MOTOR_IMAX) _iState.right = MOTOR_IMAX;  // limit upper bound
	else if (_iState.right < MOTOR_IMIN) _iState.right = MOTOR_IMIN;  // limit lower bound
	
	// Calculate integral corrections
	_iTerm.left  = _iState.left  / MOTOR_IDIV;
	_iTerm.right = _iState.right / MOTOR_IDIV;
	
	
	// Sum correction terms
	_pTerm.left  += _iTerm.left;
	_pTerm.right += _iTerm.right;
#endif

	// Perform corrections
	Motor_Drive_Left (_pTerm.left );
	Motor_Drive_Right(_pTerm.right);
}
void Motor_Center(void)
{
}

void Motor_Drive_Left(int power)
{
	if (power > 0)
	{
		if (power > 255) power = 255;
		PWM8_LeftFwd_COMPARE_REG = power;
		PWM8_LeftRev_COMPARE_REG = 0;
	}
	else
	{
		if (power < -255) power = -255;
		PWM8_LeftFwd_COMPARE_REG = 0;
		PWM8_LeftRev_COMPARE_REG = -power;
	}
}

void Motor_Drive_Right(int power)
{
	if (power > 0)
	{
		if (power > 255) power = 255;
		PWM8_RightFwd_COMPARE_REG = power;
		PWM8_RightRev_COMPARE_REG = 0;
	}
	else
	{
		if (power < -255) power = -255;
		PWM8_RightFwd_COMPARE_REG = 0;
		PWM8_RightRev_COMPARE_REG = -power;
	}
}

