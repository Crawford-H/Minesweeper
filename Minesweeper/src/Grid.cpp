#include "..\headers\Grid.h"


MineS::Grid::Grid(int numRows, int numColumns, int numBombs) 
	: numRows(numRows), numColumns(numColumns), numBombs(numBombs)
{
	// initialize grid
	initGrid();
	// randomize location of tiles in grid (bombs take the first tiles if not randomized)
	randomizeGrid();
	// calculate numNearBombs for each tile in the grid (the number of displayed on a tile)
	calcNumBombs();
}


void MineS::Grid::initGrid()
{
	// make space for columns and rows
	grid.reserve(numRows);
	for (auto& row : grid)
	{
		row.reserve(numColumns);
	}

	// create rows
	int bombCount = 0;
	for (int i = 0; i < numRows; i++) 
	{
		// create a row
		grid.emplace_back();
		// add each column to the row
		insertColumns(bombCount, grid[i]);
	}
}


void MineS::Grid::dig(int row, int column)
{
	// so a flagged tiled cannot be dug
	if (!grid[row][column].isFlagged)
	{
		// dig then open up surrounding tiles if near bombs is 0
		grid[row][column].isDug = true;
		numDug++;
		if (grid[row][column].numNearBombs == 0)
		{
			updateZeroes(row, column);
		}
	}
}


void MineS::Grid::toggleFlag(int row, int column)
{
	if (!grid[row][column].isFlagged)
	{
		grid[row][column].isFlagged = true;
		return;
	}
	grid[row][column].isFlagged = false;
}


bool MineS::Grid::isWon()
{
	if (numDug == numRows * numColumns - numBombs)
	{
		return true;
	}
	return false;
}


bool MineS::Grid::isLost()
{
	return bombDug;
}


void MineS::Grid::insertColumns(int& bombCount, std::vector<Tile>& row)
{
	for (int j = 0; j < numColumns; j++)
	{
		if (bombCount < numBombs)
		{
			row.emplace_back(true);
			bombCount++;
		}
		else 
		{
			row.emplace_back(false);
		}
	}
}


void MineS::Grid::calcNumBombs()
{
	for (int row = 0; row < numRows; row++)
	{
		for (int column = 0; column < numColumns; column++)
		{
			if (grid[row][column].isBomb)
			{
				updateSurrounding(row, column, [&](int m, int n) { grid[m][n].numNearBombs++; });
			}
		}
	}
}


void MineS::Grid::randomizeGrid()
{
	srand(time(0));
	// swap tiles randomly a large amount of times
	for (int i = 0; i < numRows * numColumns * 100; i++)
	{
		std::swap(grid[rand() % numRows][rand() % numColumns], grid[rand() % numRows][rand() % numColumns]);
	}
}


void MineS::Grid::updateZeroes(int row, int column)
{
	// function to be passed to updateSurrounding
	auto func = [&](int row, int column) {
		// digs then calls function again if num of bombs is equal to 0
		if (grid[row][column].numNearBombs == 0 && !grid[row][column].isDug)
		{
			grid[row][column].isDug = true;
			numDug++;
			updateZeroes(row, column);
		}
		grid[row][column].isDug = true;
		numDug++;
	};
	// call updateSurrounding to dig all tiles around a tile with 0 near bombs
	updateSurrounding(row, column, func);
}


void MineS::Grid::updateSurrounding(int row, int column, const std::function<void(int, int)>& func)
{
	// left column
	if (column - 1 >= 0) {
		func(row, column - 1);
		//top right, bottom right
		if (row - 1 >= 0)	   { func(row - 1, column - 1); }
		if (row + 1 < numRows) { func(row + 1, column - 1); }
	}
	// right column
	if (column + 1 < numColumns) {
		func(row, column + 1);
		//top left, bottom left
		if (row - 1 >= 0)	   { func(row - 1, column + 1); }
		if (row + 1 < numRows) { func(row + 1, column + 1); }
	}
	// top, bottom
	if (row - 1 >= 0)	   { func(row - 1, column); }
	if (row + 1 < numRows) { func(row + 1, column); }
}