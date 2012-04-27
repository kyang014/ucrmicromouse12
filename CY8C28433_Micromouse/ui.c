#include "ui.h"

struct T_I2C_Regs
{
    int val0;
    int val1;
    int val2;
	int val3;
	char bar0;
	char bar1;
	char bar2;
} I2C_Regs;

void LED_Init(void)
{
	LED_All_Off();
}
                
void I2C_Init(void)
{
	EzI2Cs_SetRamBuffer(sizeof(I2C_Regs), 0, (char*)(&I2C_Regs));
	EzI2Cs_SetAddr(I2C_SLAVE_ADDRESS);
	EzI2Cs_Start();  // Turn on I2C
}

void I2C_Update(void)
{
	M8C_DisableGInt;
	
	I2C_Regs.val0 = encoderCurrentCount.left;
	I2C_Regs.val1 = encoderCurrentCount.right;
	I2C_Regs.val2 = adcIRFront;
	I2C_Regs.val3 = adcIRRight;
	
	I2C_Regs.bar0 = (char)(adcIRLeft / 32);
	I2C_Regs.bar1 = (char)(adcIRFront / 32);
	I2C_Regs.bar2 = (char)(adcIRRight / 32);
	
	M8C_EnableGInt;
}