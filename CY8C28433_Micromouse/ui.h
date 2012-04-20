#ifndef UI_H
#define UI_H

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "PSoCGPIOINT.h"
#include "motor.h"
#include "adc.h"

#define LED_Left_On()  (LED_Left_Data_ADDR  &= ~LED_Left_MASK)
#define LED_Left_Off()   (LED_Left_Data_ADDR  |=  LED_Left_MASK)

#define LED_Right_On() (LED_Right_Data_ADDR &= ~LED_Right_MASK)
#define LED_Right_Off()  (LED_Right_Data_ADDR |=  LED_Right_MASK)

#define LED_Front_On() (LED_Front_Data_ADDR &= ~LED_Front_MASK)
#define LED_Front_Off()  (LED_Front_Data_ADDR |=  LED_Front_MASK)

#define LED_All_On()    LED_Left_On();  \
                        LED_Right_On(); \
						LED_Front_On()					
#define LED_All_Off()   LED_Left_Off();  \
                        LED_Right_Off(); \
						LED_Front_Off()

void LED_Init(void);	

#define I2C_SLAVE_ADDRESS 4

void I2C_Init(void);
void I2C_Update(void);

#endif