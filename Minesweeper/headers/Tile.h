#pragma once

namespace MineS 
{
	struct Tile
	{
		// number of bombs next to tile
		int numNearBombs = 0;

		// if the tile has been dug
		bool isDug = false;

		// if the tile has been flagged
		bool isFlagged = false;

		//if the tile is a bomb
		bool isBomb;

		Tile(bool isBomb) : 
			isBomb(isBomb) {};
	};
}