#include "nav.h"

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
//	if (Motion_Ready())
//	{
//		Motion_SetNextCommand(_navCommandList[_navCommandIndex]);
//		_navCommandIndex++;
//		if (_navCommandIndex == _navCommandListSize) _navCommandIndex = 0;
//	}
}
