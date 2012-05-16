#include "maze.h"

#pragma data:page0
char mazeFloodHeadPointer;
char mazeFloodTailPointer;
char mazeFloodCount;
char mazeFloodQueue[MAZE_QUEUE_SIZE];

#pragma data:page1  // Gets RAM page 1 all to itself
char mazeFlags[MAZE_CELL_COUNT];
// [3] fWest
// [2] fSouth
// [1] fEast
// [0] fNorth

#pragma data:page2  // Gets RAM page 2 all to itself
char mazeRouting[MAZE_CELL_COUNT];
#pragma data:data

// Stores the cell to use as the goal when flooding
Cell mazeGoalCell;

void Maze_Init(void)
{
	// Reset the flooding queue
	mazeFloodHeadPointer = 0;
	mazeFloodTailPointer = 0;
	mazeFloodCount = 0;
}

void Maze_AddWall(Cell c, Direction d)
{
	char x = cellGetColumn(c);
	char y = cellGetRow(c);
	
	// Set wall flags for the current cell
	cellSetFlags(c, d);
	
	if (d == NORTH)
	{
		if (y != (MAZE_HEIGHT - 1))  // Check if a cell exists above
		{
			c += MAZE_WIDTH;         // Address the row above
			cellSetFlags(c, SOUTH);  // Set it's south wall
		}
	}
	else if (d == SOUTH)
	{
		if (y != 0)  // Check if a cell exists below
		{
			c -= MAZE_WIDTH;         // Address the row above
			cellSetFlags(c, NORTH);  // Set it's north wall
		}
	}
	else if (d == EAST)
	{
		if (x != (MAZE_WIDTH - 1))   // Check if a cell exists to the right
		{
			c += 1;                  // Address the cell to the right
			cellSetFlags(c, WEST);   // Set it's west wall
		}
	}
	else if (d == WEST)
	{
		if (x != 0)                   // Check if a cell exists to the left
		{
			c -= 1;                  // Address the cell to the left
			cellSetFlags(c, EAST);   // Set it's EAST wall
		}
	}
	
}

void Maze_Enqueue(Cell c)
{
	if (mazeFloodCount != MAZE_QUEUE_SIZE)  // Check that queue is not already full
	{
		if (!cellIsInQueue(c))              // Check that the cell is not already in the queue
		{
			mazeFloodCount ++;               // Increment size counter
			mazeFloodQueue[mazeFloodHeadPointer] = c;  // Put the cell index in the queue
			
			cellSetFlags(c, CELL_IN_QUEUE); // Set the cell's "in queue" flag
			
			mazeFloodHeadPointer ++;                             // advance head pointer
			mazeFloodHeadPointer &= MAZE_QUEUE_MASK;             // mask off overflow
		}
	}
}

Cell Maze_Dequeue(void)
{
	if (mazeFloodCount)
	{
		Cell result;
		
		mazeFloodCount --;  // decrement size counter
		
		result = mazeFloodQueue[mazeFloodTailPointer];       // Retrieve the cell index at the tail pointer
		mazeFlags[result] &= (~CELL_IN_QUEUE);               // Clear the cell's "in queue" flag
		
		mazeFloodTailPointer ++;                             // advance tail pointer
		mazeFloodTailPointer &= MAZE_QUEUE_MASK;             // mask off overflow
		
		return result;
	}
	else
	{
		// The queue is empty
		return 0;
	}
}
