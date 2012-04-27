#ifndef SCHED_H
#define SCHED_H

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "PSoCGPIOINT.h"
#include "MicromouseModules.h"

// milliseconds
#define SCHED_PERIOD_ADC    4  // Can reduce to 1 ms if needed. Sensors can settle fast enough
#define SCHED_PERIOD_MOTOR  5
#define SCHED_PERIOD_I2C    32
#define SCHED_PERIOD_MOTION 10

#define SCHED_RUN_ADC    0x01
#define SCHED_RUN_MOTOR  0x02
#define SCHED_RUN_I2C    0x04
#define SCHED_RUN_MOTION 0x08

void Sched_Init(void);

void Sched_RunQueue(void);

#pragma interrupt_handler TICK_ISR
void TICK_ISR(void);

#endif