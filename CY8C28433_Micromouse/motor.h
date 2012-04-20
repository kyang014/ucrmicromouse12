#ifndef MOTOR_H
#define MOTOR_H

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "PSoCGPIOINT.h"
#include "ui.h"

#define motor_left_disable()  (MotorEnable_L_Data_ADDR &= ~MotorEnable_L_MASK)
#define motor_left_enable()   (MotorEnable_L_Data_ADDR |=  MotorEnable_L_MASK)
#define motor_right_disable() (MotorEnable_R_Data_ADDR &= ~MotorEnable_R_MASK)
#define motor_right_enable()  (MotorEnable_R_Data_ADDR |=  MotorEnable_R_MASK)

// "quadrature" refers to raw gray code readings
// "encoder" refers to readings converted to counts

#define QUADRATURE_STATE_LEFT_1  (0x00)
#define QUADRATURE_STATE_LEFT_2  (Encoder_LeftA_MASK)
#define QUADRATURE_STATE_LEFT_3  (Encoder_LeftA_MASK | Encoder_LeftB_MASK)
#define QUADRATURE_STATE_LEFT_4  (Encoder_LeftB_MASK)
#define QUADRATURE_STATE_RIGHT_1 (0x00)
#define QUADRATURE_STATE_RIGHT_2 (Encoder_RightA_MASK)
#define QUADRATURE_STATE_RIGHT_3 (Encoder_RightA_MASK | Encoder_RightB_MASK)
#define QUADRATURE_STATE_RIGHT_4 (Encoder_RightB_MASK)

// Reads the state of the encoders. Assumes both inputs of an encoder
// are on the same port.
#define _quadrature_left()  (Encoder_LeftA_Data_ADDR  & (Encoder_LeftA_MASK  | Encoder_LeftB_MASK))
#define _quadrature_right() (Encoder_RightA_Data_ADDR & (Encoder_RightA_MASK | Encoder_RightB_MASK))

#define Encoder_ResumeCount() M8C_EnableIntMask(INT_MSK0, INT_MSK0_GPIO)   // Enable GPIO interrupts
#define Encoder_PauseCount()  M8C_DisableIntMask(INT_MSK0, INT_MSK0_GPIO)  // Disable GPIO interrupts

typedef struct Encoder_Count_T
{
   int left;
   int right;
} EncoderCounts;

extern EncoderCounts encoderCount;
//extern int encoderCountLeft;
//extern int encoderCountRight;

void Encoder_Init(void);

#pragma interrupt_handler GPIO_ISR
void GPIO_ISR(void);

void Motor_Init(void);
void Motor_Drive_Left(int power);
void Motor_Drive_Right(int power);

#endif