#ifndef MOTION_H
#define MOTION_H

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "PSoCGPIOINT.h"
#include "MicromouseModules.h"

#define MOTION_COUNT_BACKLASH 15   // encoder ticks of drivetrain backlash
#define MOTION_COUNT_CELL     547  // encoder ticks per wall length
#define MOTION_COUNT_ROT90    258  // encoder ticks per wheel to rotate in place 90 degrees

void Motion_Init(void);

void Motion_Update(void);

#endif