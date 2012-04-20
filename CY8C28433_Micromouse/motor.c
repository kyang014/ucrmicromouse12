#include "motor.h"

EncoderCounts encoderCount;

char _quadratureState;
char _previousQuadratureStateLeft;
char _previousQuadratureStateRight;

void GPIO_ISR(void)
{
	LED_Right_On();
	_quadratureState = _quadrature_left();
	if (_quadratureState != _previousQuadratureStateLeft)
	{
		if (_quadratureState == QUADRATURE_STATE_LEFT_1)
		{
			if (_previousQuadratureStateLeft == QUADRATURE_STATE_LEFT_4)
				encoderCount.left++;
			else
				encoderCount.left--;
		}
		else if (_quadratureState == QUADRATURE_STATE_LEFT_2)
		{
			if (_previousQuadratureStateLeft == QUADRATURE_STATE_LEFT_1)
				encoderCount.left++;
			else
				encoderCount.left--;
		}
		else if (_quadratureState == QUADRATURE_STATE_LEFT_3)
		{
			if (_previousQuadratureStateLeft == QUADRATURE_STATE_LEFT_2)
				encoderCount.left++;
			else
				encoderCount.left--;
		}
		else
		{
			if (_previousQuadratureStateLeft == QUADRATURE_STATE_LEFT_3)
				encoderCount.left++;
			else
				encoderCount.left--;
		}
		_previousQuadratureStateLeft = _quadratureState;
	}
	
	_quadratureState = _quadrature_right();
	if (_quadratureState != _previousQuadratureStateRight)
	{
		if (_quadratureState == QUADRATURE_STATE_RIGHT_1)
		{
			if (_previousQuadratureStateRight == QUADRATURE_STATE_RIGHT_4)
				encoderCount.right++;
			else
				encoderCount.right--;
		}
		else if (_quadratureState == QUADRATURE_STATE_RIGHT_2)
		{
			if (_previousQuadratureStateRight == QUADRATURE_STATE_RIGHT_1)
				encoderCount.right++;
			else
				encoderCount.right--;
		}
		else if (_quadratureState == QUADRATURE_STATE_RIGHT_3)
		{
			if (_previousQuadratureStateRight == QUADRATURE_STATE_RIGHT_2)
				encoderCount.right++;
			else
				encoderCount.right--;
		}
		else
		{
			if (_previousQuadratureStateRight == QUADRATURE_STATE_RIGHT_3)
				encoderCount.right++;
			else
				encoderCount.right--;
		}
		_previousQuadratureStateRight = _quadratureState;
	}
	LED_Right_Off();
}

void Encoder_Init(void)
{
	encoderCount.left  = 0;
	encoderCount.right = 0;
	
	_previousQuadratureStateLeft = _quadrature_left();   // Initialize left encoder state machine
	_previousQuadratureStateRight = _quadrature_right(); // Initialize right encoder state machine

	M8C_EnableIntMask(INT_MSK0, INT_MSK0_GPIO);         // Enable GPIO interrupts
}

void Motor_Init(void)
{
	// Start motor PWMs
	PWM8_LeftFwd_Start();
	PWM8_LeftRev_Start();
	PWM8_RightFwd_Start();
	PWM8_RightRev_Start();

	motor_left_enable();
	motor_right_enable();
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
