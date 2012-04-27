PROJNAME=CY8C28433_Micromouse
DEVICE=CY8C28433
BASEDEVICE=CY8C28033
PROJPATH=C:/Users/Kevin/Dropbox/PSOCDE~1/CY8C28~3/CY8C28~1
PSOCDIR=C:/PROGRA~2/Cypress/PSOCDE~1/5.2/Common/CY110F~1
INCLUDE_PATH=C:/PROGRA~2/Cypress/PSOCDE~1/5.2/Common/CY110F~1/tools/include/CY8C28~1
CSRCS= adc.c encoder.c main.c motion.c motor.c nav.c sched.c ui.c
LIBCSRCS=
STDCSRCS=
ASMSRCS=
LIBASMSRCS= counter16_tick.asm counter16_tickint.asm ezi2cs.asm ezi2csint.asm psocconfig.asm psocconfigtbl.asm psocgpioint.asm pwm8_leftfwd.asm pwm8_leftfwdint.asm pwm8_leftrev.asm pwm8_leftrevint.asm pwm8_pump.asm pwm8_pumpint.asm pwm8_rightfwd.asm pwm8_rightfwdint.asm pwm8_rightrev.asm pwm8_rightrevint.asm sar10.asm sar10int.asm sleeptimer.asm sleeptimerint.asm
STDASMSRCS=
OBJECT_SOURCES= adc.c encoder.c main.c motion.c motor.c nav.c sched.c ui.c
FILLVALUE=0x30
LASTROM=0x3fff
LASTRAM=0x3ff
LAST_DATARAM=0x35f
CODECOMPRESSOR=
MORE_CFLAGS=-Wf-LMM4 -D_LMM
RELSTART=0x190
CDEFINES=
LIBS=
UMLIBS=
LIB_PATH=
ENABLE_ALIGN_SHIFT=0
LMM=1
SYS_INC_CONTENTS:=SYSTEM_STACK_PAGE:_equ_3 SYSTEM_STACK_BASE_ADDR:_equ_60h SYSTEM_LARGE_MEMORY_MODEL:_equ_1 SYSTEM_SMALL_MEMORY_MODEL:_equ_0 IMAGECRAFT:_equ_1 HITECH:_equ_2 TOOLCHAIN:_equ_IMAGECRAFT 
SYSTEM_TOOLS=1
CSFLOW=
CONFIG_NAMES=cy8c28433_micromouse 
