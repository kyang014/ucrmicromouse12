#include "encoder.h"

SEncCount encoderCurrentCount;

char _quadratureState;
char _previousQuadratureStateLeft;
char _previousQuadratureStateRight;

void Encoder_Init(void)
{
	encoderCurrentCount.left  = 0;
	encoderCurrentCount.right = 0;
	
	_previousQuadratureStateLeft = _quadrature_left();   // Initialize left encoder state machine
	_previousQuadratureStateRight = _quadrature_right(); // Initialize right encoder state machine

	M8C_EnableIntMask(INT_MSK0, INT_MSK0_GPIO);         // Enable GPIO interrupts
}

void GPIO_ISR(void)
{
	LED_Right_On();
	_quadratureState = _quadrature_left();
	if (_quadratureState != _previousQuadratureStateLeft)
	{
		if (_quadratureState == QUADRATURE_STATE_LEFT_1)
		{
			if (_previousQuadratureStateLeft == QUADRATURE_STATE_LEFT_4)
				encoderCurrentCount.left++;
			else
				encoderCurrentCount.left--;
		}
		else if (_quadratureState == QUADRATURE_STATE_LEFT_2)
		{
			if (_previousQuadratureStateLeft == QUADRATURE_STATE_LEFT_1)
				encoderCurrentCount.left++;
			else
				encoderCurrentCount.left--;
		}
		else if (_quadratureState == QUADRATURE_STATE_LEFT_3)
		{
			if (_previousQuadratureStateLeft == QUADRATURE_STATE_LEFT_2)
				encoderCurrentCount.left++;
			else
				encoderCurrentCount.left--;
		}
		else
		{
			if (_previousQuadratureStateLeft == QUADRATURE_STATE_LEFT_3)
				encoderCurrentCount.left++;
			else
				encoderCurrentCount.left--;
		}
		_previousQuadratureStateLeft = _quadratureState;
	}
	
	_quadratureState = _quadrature_right();
	if (_quadratureState != _previousQuadratureStateRight)
	{
		if (_quadratureState == QUADRATURE_STATE_RIGHT_1)
		{
			if (_previousQuadratureStateRight == QUADRATURE_STATE_RIGHT_4)
				encoderCurrentCount.right++;
			else
				encoderCurrentCount.right--;
		}
		else if (_quadratureState == QUADRATURE_STATE_RIGHT_2)
		{
			if (_previousQuadratureStateRight == QUADRATURE_STATE_RIGHT_1)
				encoderCurrentCount.right++;
			else
				encoderCurrentCount.right--;
		}
		else if (_quadratureState == QUADRATURE_STATE_RIGHT_3)
		{
			if (_previousQuadratureStateRight == QUADRATURE_STATE_RIGHT_2)
				encoderCurrentCount.right++;
			else
				encoderCurrentCount.right--;
		}
		else
		{
			if (_previousQuadratureStateRight == QUADRATURE_STATE_RIGHT_3)
				encoderCurrentCount.right++;
			else
				encoderCurrentCount.right--;
		}
		_previousQuadratureStateRight = _quadratureState;
	}
	LED_Right_Off();
}