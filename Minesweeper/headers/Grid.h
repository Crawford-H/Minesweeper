#pragma once

#include <vector>
#include <random>
#include <time.h>
#include <functional>

#include "Tile.h"

namespace MineS 
{
	class Grid
	{
	// public methods
	public:
		// constructor
		Grid(int rows, int columns, int numBombs);
		// digs a certain tile
		void dig(int row, int column);
		// toggles flag on a tile
		void toggleFlag(int row, int column);
		// if the player has won 
		bool isWon();
		// if a bomb has been pressed
		bool isLost();


	// getters and setters
	public: 
		std::vector<std::vector<MineS::Tile>>& getGrid() { return grid; }
		const int& getNumRows()    { return numRows;    }
		const int& getNumColumns() { return numColumns; }
		const int& getNumBombs()   { return numBombs;   }


	// private methods
	private:
		// initalizes the tiles in the grid
		void initGrid();
		// calculate the number for each tile
		void calcNumBombs();
		// puts tiles into each column of each row in the grid
		void insertColumns(int& bombCount, std::vector<Tile>& row);
		// randomizes location of tiles in the grid
		void randomizeGrid();
		// digs the zeroes surrounding a dug tile
		void updateZeroes(int row, int column);
		// applies a given function to each tile surrounding a given tile
		void updateSurrounding(int row, int column, const std::function<void(int, int)>& func);
		

	// private variables
	private:
		// vector of vector of tiles
		std::vector<std::vector<MineS::Tile>> grid;
		// amount of rows
		int numRows;
		// amount of bomba in the grid
		int numBombs;
		// amount of columns
		int numColumns;
		// amount of tiles that are dug
		int numDug = 0;
		// if a bomb has been dug
		bool bombDug = false;
	};
}


