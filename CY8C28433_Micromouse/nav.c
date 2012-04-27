#include "nav.h"

#pragma data:page0
unsigned char mazeFloodQueue[128];
#pragma data:page1  // Gets RAM page 1 all to itself
unsigned char mazeFlags[256];
#pragma data:page2  // Gets RAM page 2 all to itself
unsigned char mazeRouting[256];
#pragma data:data

      char _navCommandIndex = 0;
const char _navCommandListSize = 8;
const char _navCommandList[] = {MOTION_COMMAND_FWD,
                                MOTION_COMMAND_FWD,
							    MOTION_COMMAND_LEFT90,
								MOTION_COMMAND_LEFT90,
								MOTION_COMMAND_FWD,
								MOTION_COMMAND_FWD,
								MOTION_COMMAND_RIGHT90,
								MOTION_COMMAND_RIGHT90};
							  
void Nav_Init(void)
{
}

void Nav_Update(void)
{
	if (Motion_Ready())
	{
		Motion_SetNextCommand(_navCommandList[_navCommandIndex]);
		_navCommandIndex++;
		if (_navCommandIndex == _navCommandListSize) _navCommandIndex = 0;
	}
}
