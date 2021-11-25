#ifndef _SCENE
#define _SCENE

#include <iostream>
#include <vector>
#include "Row.h"
#include "Pixel.h"
#include "Win32Helper.h"

class Scene
{
private:
	int playCol = 30, playRow = 110;
	char PrevBuffer[30][150];
	char Buffer[30][150];

public:
	Scene()
	{
		memset(Buffer, (int)' ', 150 * 30);
		memset(PrevBuffer, (int)' ', 150 * 30);
	}

	~Scene()
	{
	}

	int getCol() const
	{
		return playCol;
	}

	int getRow() const
	{
		return playRow;
	}

	/// <summary>
	/// Display generated Buffer to the monitor
	/// </summary>
	void PrintBuffer()
	{
		for (SHORT row = 0; row < 30; ++row)
		{
			for (SHORT col = 0; col < 150; ++col)
			{
				if (Buffer[row][col] == PrevBuffer[row][col])
					continue;

				GotoXY(col, row);
				std::cout << Buffer[row][col];
			}
		}

		std::cout.flush();
		std::memcpy((char*)PrevBuffer, (char const*)Buffer, 150 * 30);
	}

	/// <summary>
	/// Generate and display ALL elements of the game
	/// </summary>
	void drawScene(int level_)
	{
		//ClearConsoleScreen();
		int row = 30, col = 150;

		for (int i = 0; i < row; ++i)
			Buffer[i][col - 1] = '\n';

		for (int r = 0; r < row; ++r)
		{
			for (int c = 0; c < col - 40; ++c)
			{
				if (r == 0 || r == row - 1)
					Buffer[r][c] = '#';
				else if (r % 5 == 0)
				{
					if (c == 0 || c == col - 41)
						Buffer[r][c] = '#';
					else
						Buffer[r][c] = '_';
				}
				else
				{
					if (c == 0 || c == col - 41)
						Buffer[r][c] = '#';
					else
						Buffer[r][c] = ' ';
				}
			}
		}

		snprintf((*(Buffer + 15) + 90), 14, "Level: %d", level_);
	}

	void drawEntity(const Entity& obj)
	{
		for(int y = 0; y < obj.getSpriteHeight(); ++y)
			for (int x = 0; x < obj.getSpriteWidth(); ++x) {
				if((y + obj.getY() - obj.getBound(0) > 0 && y + obj.getY() - obj.getBound(0) < playCol - 1) && (x + obj.getX() - obj.getBound(3) > 0 && x + obj.getX() - obj.getBound(3) < playRow - 1))
					Buffer[y + obj.getY() - obj.getBound(0)][x + obj.getX() - obj.getBound(3)] = obj.getSprite()[y][x];
			}
	}

	void drawOneRow(const Row& obj) // Draw rows here
	{
		// Task to do: draw traffic light (thank you Hao <3)

		for (auto& enemy : obj.GetList())
			drawEntity(*enemy);
	}

	void drawDeadMenu()
	{
		for (int i = 0; i < 7; ++i)
			memcpy((char*)(Buffer[i + 12] + 24), (char*)(DeadMenu[i]), strlen(DeadMenu[0]));
	}

	//!!!NOT FINISH!!!
	//Waiting for loading
	void drawLoadMenu()
	{
		for (int i = 0; i < 5; ++i)
			memcpy((char*)(Buffer[i + 12] + 20), (char*)(LoadMenu[i]), strlen(LoadMenu[0]));
	}

	//!!!NOT FINISH!!!
	//Waiting for saving
	void drawSaveMenu()
	{
		for (int i = 0; i < 5; ++i)
			memcpy((char*)(Buffer[i + 13] + 20), (char*)(SaveMenu[i]), strlen(SaveMenu[0]));
	}

	void drawPauseMenu()
	{
		for (int i = 0; i < 5; ++i)
			memcpy((char*)(Buffer[i + 13] + 20), (char*)(PauseMenu[i]), strlen(PauseMenu[0]));
	}

	const static char DeadMenu[7][33];
	const static char LoadMenu[8][41];
	const static char SaveMenu[5][41];
	const static char PauseMenu[5][41];
};

#endif _SCENE