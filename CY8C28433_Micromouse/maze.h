#ifndef MAZE_H
#define MAZE_H

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "PSoCGPIOINT.h"
#include "MicromouseModules.h"

#define MAZE_HEIGHT 16
#define MAZE_WIDTH  16
#define MAZE_CELL_COUNT (MAZE_HEIGHT * MAZE_WIDTH)

#define MAZE_QUEUE_SIZE 128  // Power of two
#define MAZE_QUEUE_MASK 0x7F

#define CELL_START  0x00   // Start cell
#define CELL_CENTER 0x77   // Center of a 16x16 maze

#define WEST  0x08
#define SOUTH 0x04
#define EAST  0x02
#define NORTH 0x01
#define CELL_IN_QUEUE 0x10

#define cellWallExists(c, d)   (mazeFlags[c] &  d)
#define cellSetFlags(c, f)     (mazeFlags[c] |= f)

#define cellIsInQueue(c)       (mazeFlags[c] & CELL_IN_QUEUE)

#define cellGetColumn(c)       (c & 0x0F)
#define cellGetRow(c)          (c >> 4)

typedef char Cell;
typedef char Direction;

void Maze_Init(void);

void Maze_AddWall(Cell c, Direction d);

void Maze_Enqueue(Cell c);
Cell Maze_Dequeue(void);

#endif
