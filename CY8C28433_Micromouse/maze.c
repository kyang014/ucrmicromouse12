#include "maze.h"

#pragma data:page0
unsigned char mazeFloodHeadPointer;
unsigned char mazeFloodTailPointer;
unsigned char mazeFloodCount;
unsigned char mazeFloodQueue[MAZE_QUEUE_SIZE];

#pragma data:page1  // Gets RAM page 1 all to itself
unsigned char mazeFlags[MAZE_CELL_COUNT];

#pragma data:page2  // Gets RAM page 2 all to itself
unsigned char mazeRouting[MAZE_CELL_COUNT];
#pragma data:data

// Stores the cell to use as the goal when flooding
CellIndex mazeGoalCell;

void Maze_Init(void)
{
	// Reset the flooding queue
	mazeFloodHeadPointer = 0;
	mazeFloodTailPointer = 0;
	mazeFloodCount = 0;

	Maze_AddBorders();
}


void Maze_AddWall(CellIndex c, Direction d)
{
	CellIndex adj;     // Adjacent cell
	unsigned char x = cellGetColumn(c);
	unsigned char y = cellGetRow(c);
		
	// Set wall flags for the current cell
	cellSetFlags(c, d);
	
	// Set wall flags for the current cell
	cellSetFlags(c, d);
	
	if (d & WALL_NORTH)
	{
		if (y != (MAZE_HEIGHT - 1))  // Check if a cell exists above
		{
			adj = c;
			adj += MAZE_WIDTH;              // Address the row above
			cellSetFlags(adj, WALL_SOUTH);  // Set it's south wall
		}
	}
	if (d & WALL_SOUTH)
	{
		if (y != 0)  // Check if a cell exists below
		{
			adj = c;
			adj -= MAZE_WIDTH;              // Address the row below
			cellSetFlags(adj, WALL_NORTH);  // Set it's north wall
		}
	}
	if (d & WALL_EAST)
	{
		if (x != (MAZE_WIDTH - 1))   // Check if a cell exists to the right
		{
			adj = c;
			adj += 1;                       // Address the cell to the right
			cellSetFlags(adj, WALL_WEST);   // Set it's west wall
		}
	}
	if (d & WALL_WEST)
	{
		if (x != 0)                   // Check if a cell exists to the left
		{
			adj = c;
			adj -= 1;                       // Address the cell to the left
			cellSetFlags(adj, WALL_EAST);   // Set it's EAST wall
		}
	}
	
}

// Adds walls along the maze edge
void Maze_AddBorders(void)
{
	CellIndex cell;
	CellIndex oppositeCell;

	for (cell = MAZE_LOWER_LEFT; cell < MAZE_WIDTH; cell++)
	{
		// Cells on lower edge
		cellSetFlags(cell, WALL_SOUTH);

		// Cells on upper edge
		oppositeCell = cell + (MAZE_CELL_COUNT - MAZE_WIDTH);  // Calculate index of cell on opposite side
		cellSetFlags(oppositeCell , WALL_NORTH);

		// Cells on leftmost edge
		oppositeCell = cell * MAZE_HEIGHT;
		cellSetFlags(oppositeCell , WALL_WEST);

		// Cells on rightmost edge
		oppositeCell += (MAZE_WIDTH - 1);
		cellSetFlags(oppositeCell , WALL_EAST);
	}

}

void Maze_Enqueue(CellIndex c)
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

CellIndex Maze_Dequeue(void)
{
	if (mazeFloodCount)
	{
		CellIndex result;
		
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
