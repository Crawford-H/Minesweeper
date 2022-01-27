#include "../headers/Minesweeper.h"

// constructor
Minesweeper::Minesweeper()
{
	sAppName = "Minesweeper";
}

// called once when the application is created
bool Minesweeper::OnUserCreate()
{
	// calculate how many rows or columns to draw then init grid
	grid = std::make_unique<MineS::Grid>(ROWS, COLUMNS, NUMBOMBS);
	screenUpdated = false;
	
	// load images
	bombImage = std::make_unique<olc::Sprite>("./resources/bomb.png");
	flagImage = std::make_unique<olc::Sprite>("./resources/flag.png");
	tileImage = std::make_unique<olc::Sprite>("./resources/tile.png");

	return true;
}

// called repeatedly
bool Minesweeper::OnUserUpdate(float fElapsedTime)
{
	keyInput();

	if (!screenUpdated)
	{
		Clear(olc::WHITE);
		drawGrid();
	}
	return true;
}


void Minesweeper::drawGrid()
{
	// draw every tile in the grid
	drawTiles();
	// draw grid outlines
	drawGridLines();
	// change status of screen
	screenUpdated = true;
}


void Minesweeper::drawTiles()
{
	// loop through each tile in the grid
	for (int i = 0; i < grid->getNumRows(); i++) 
	{
		for (int j = 0; j < grid->getNumColumns(); j++) 
		{
			// calculate x and y for grid
			int x = (j * TILEW) + TILEW;
			int y = (i * TILEW) + (2 * TILEW);

			drawTile(grid->getGrid()[i][j], x, y);
		}
	}
}


void Minesweeper::drawTile(const MineS::Tile& tile, int x, int y)
{
	// when tiles haven't been pressed
	if (!tile.isDug)
	{
		if (tile.isFlagged)
		{
			DrawSprite(x, y, flagImage.get());
		}
		else 
		{
			DrawSprite(x, y, tileImage.get());
		}
		return;
	}

	// when a tile has been pressed
	if (tile.isBomb)
	{
		DrawSprite(x, y, bombImage.get());
	}
	// draw number if not 0
	else if (tile.numNearBombs > 0)
	{
		DrawString(x + 8, y + 8, std::to_string(tile.numNearBombs), getColour(tile), 2);
	}
}


void Minesweeper::drawGridLines()
{
	// draw vertical lines
	for (int i = 1; i < ScreenWidth() / TILEW; i++)
	{
		DrawLine(i * TILEW, 2 * TILEW, i * TILEW, ScreenHeight() - TILEW, olc::BLACK);
	}
	//horizontal lines
	for (int i = 2; i < ScreenHeight() / TILEW; i++)
	{
		DrawLine(TILEW, i * TILEW, ScreenWidth() - TILEW, i * TILEW, olc::BLACK);
	}
}


olc::Pixel Minesweeper::getColour(MineS::Tile tile)
{
	// return the colour associated with the number of bombs of a tile
	switch (tile.numNearBombs)
	{
		case 1:  return olc::BLUE;	        break;
		case 2:  return olc::GREEN;         break;
		case 3:  return olc::RED;		    break;
		case 4:  return olc::DARK_MAGENTA;  break;
		case 5:  return olc::VERY_DARK_RED; break;
		case 6:  return olc::CYAN;		    break;
		case 7:  return olc::MAGENTA;	    break;
		default: return olc::GREY;
	}
}

void Minesweeper::keyInput()
{
	bool lClick = GetMouse(0).bPressed;
	bool rClick = GetMouse(1).bPressed;
	bool esc = GetKey(olc::Key::ESCAPE).bPressed;

	// dig or flag when a mouse button has been clicked and in the grid
	if ((rClick || lClick) && 
		GetMouseY() < ScreenHeight() - TILEW &&
		GetMouseY() > 2 * TILEW - TILEW &&
		GetMouseX() < ScreenWidth() - TILEW &&
		GetMouseX() > TILEW)
	{
		// calculate the row and column of where mouse button was pressed
		int row = ((GetMouseY() - 2 * TILEW) / TILEW);
		int column = ((GetMouseX() - TILEW) / TILEW);

		// dig or flag tile
		if (lClick)
		{
			grid->dig(row, column);
		}
		if (rClick)
		{
			grid->toggleFlag(row, column);
		}

		// change state of sceen
		screenUpdated = false;
	}
	if (esc) 
	{
		OnUserCreate();
	}
}


int main()
{
	Minesweeper app;
	if (app.Construct(960, 800, 1, 1))
	{
		app.Start();
	}
	return 0;
}