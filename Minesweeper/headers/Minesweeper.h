#pragma once

// std includes
#include <iostream>

// PixelGameEngine includes
#define OLC_PGE_APPLICATION
#include "../resources/olcPixelGameEngine.h"

// Minesweeper includes
#include "../headers/Grid.h"


class Minesweeper : public olc::PixelGameEngine
{
public:
	// constructor
	Minesweeper();
	// called once when created
	bool OnUserCreate() override;
	// called repeatedly
	bool OnUserUpdate(float fElapsedTime) override;


private:
	// draws the grid to the window
	void drawGrid();
	// draw each tile in the grid
	void drawTiles();
	// finds which sprite to use for a tile then draws it
	void drawTile(const MineS::Tile& tile, int x, int y);
	// draws the grid lines
	void drawGridLines();
	// returns the colour to draw a number
	olc::Pixel getColour(MineS::Tile tile);
	// gets key input from user
	void keyInput();

private:
	// the grid which contains the info about the board
	std::unique_ptr<MineS::Grid> grid;
	// keeps track if the screen is up to date
	bool screenUpdated;

	// width of each tile
	const int TILEW = 32;

	// number rows and column in the grid
	const int ROWS = 800 / TILEW - 3;
	const int COLUMNS = 960 / TILEW - 2;
	const int NUMBOMBS = ROWS * COLUMNS / 6;

	// sprites
	std::unique_ptr<olc::Sprite> tileImage;
	std::unique_ptr<olc::Sprite> flagImage;
	std::unique_ptr<olc::Sprite> bombImage;
};