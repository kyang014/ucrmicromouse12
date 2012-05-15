#include "maze.h"

#pragma data:page0
unsigned char mazeFloodQueue[128];
#pragma data:page1  // Gets RAM page 1 all to itself
unsigned char mazeFlags[256];
#pragma data:page2  // Gets RAM page 2 all to itself
unsigned char mazeRouting[256];
#pragma data:data
