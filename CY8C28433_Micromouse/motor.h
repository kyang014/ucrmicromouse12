#ifndef MOTOR_H
#define MOTOR_H

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "PSoCGPIOINT.h"
#include "MicromouseModules.h"

#define motor_left_disable()  (MotorEnable_L_Data_ADDR &= ~MotorEnable_L_MASK)
#define motor_left_enable()   (MotorEnable_L_Data_ADDR |=  MotorEnable_L_MASK)
#define motor_right_disable() (MotorEnable_R_Data_ADDR &= ~MotorEnable_R_MASK)
#define motor_right_enable()  (MotorEnable_R_Data_ADDR |=  MotorEnable_R_MASK)

#define MOTOR_PGAIN    8    // Proportional gain
#define MOTOR_IDIV     16   // Integral gain (as a divisor)
#define MOTOR_IMIN    -256  // Minimum allowable integrator state
#define MOTOR_IMAX     256  // Maximum allowable integrator state

//#define MOTOR_ENABLE_INTEGRAL

void Motor_Init(void);
void Motor_Update(void);
void Motor_Center(void);
void Motor_Drive_Left(int power);
void Motor_Drive_Right(int power);

#endif