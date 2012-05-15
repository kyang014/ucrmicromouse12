#ifndef ADC_H
#define ADC_H

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "PSoCGPIOINT.h"
#include "ui.h"

#define IR_Emitter_On()    (IR_Emitter_Data_ADDR  |=  IR_Emitter_MASK)
#define IR_Emitter_Off()   (IR_Emitter_Data_ADDR  &= ~IR_Emitter_MASK)
#define IR_Emitter_Powered (IR_Emitter_Data_ADDR  &   IR_Emitter_MASK)

#define ADC_CHAN_IR_FRONT SAR10_CHS_P00
#define ADC_CHAN_IR_LEFT  SAR10_CHS_P01
#define ADC_CHAN_IR_RIGHT SAR10_CHS_P02
#define ADC_CHAN_USER     SAR10_CHS_P06

// Ambient light offsets
#define ADC_OFFSET_IR_FRONT 48
#define ADC_OFFSET_IR_LEFT  65
#define ADC_OFFSET_IR_RIGHT 195

extern unsigned int adcIRFrontDark;
extern unsigned int adcIRLeftDark;
extern unsigned int adcIRRightDark;

extern unsigned int adcIRFront;
extern unsigned int adcIRLeft;
extern unsigned int adcIRRight;

extern unsigned int adcUser;

//extern unsigned int adcSideCenterDistance;
//extern unsigned int adcFrontCenterDistance;

void ADC_Init(void);
void ADC_Update(void);

#define ADC_WALL_THRESHOLD   100

#define ADC_FrontWallExists  (adcIRFront > ADC_WALL_THRESHOLD)
#define ADC_LeftWallExists   (adcIRLeft  > ADC_WALL_THRESHOLD)
#define ADC_RightWallExists  (adcIRRight > ADC_WALL_THRESHOLD)

#endif