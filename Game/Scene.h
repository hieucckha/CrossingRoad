#ifndef _SCENE
#define _SCENE

#include <iostream>
#include <vector>
#include "Row.h"
#include "Win32Helper.h"

class Scene
{
private:
	char PrevBuffer[30][120];
	char Buffer[30][120];
public:
	Scene()
	{
		memset(Buffer, (int)' ', 120 * 30);
		memset(PrevBuffer, (int)' ', 120 * 30);
	}

	~Scene()
	{
	}

	/// <summary>
	/// Display generated Buffer to the monitor
	/// </summary>
	void PrintBuffer()
	{
		for (SHORT row = 0; row < 30; ++row)
		{
			for (SHORT col = 0; col < 120; ++col)
			{
				if (Buffer[row][col] == PrevBuffer[row][col])
					continue;

				GotoXY(col, row);
				std::cout << Buffer[row][col];
			}
		}

		std::cout.flush();
		std::memcpy((char*)PrevBuffer, (char const*)Buffer, 120 * 30);
	}

	/// <summary>
	/// Generate and display ALL elements of the game
	/// </summary>
	void drawScene(int level_)
	{
		//ClearConsoleScreen();
		int row = 30, col = 120;

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
				Buffer[y + obj.getY() - obj.getBound(0)][x + obj.getX() - obj.getBound(3)] = obj.getSprite()[y][x];
			}
	}

	void drawDeadMenu()
	{
		for (int i = 0; i < 5; ++i)
			memcpy((char*)(Buffer[i] + 24), (char*)(DeadMenu), sizeof(DeadMenu[0]));
	}

	void drawLoadMenu()
	{

	}

	void drawSaveMenu()
	{

	}

	void drawPauseMenu()
	{

	}

	const static char DeadMenu[7][33];
	const static char LoadMenu[8][41];
	const static char SaveMenu[5][41];
	const static char PauseMenu[5][41];
};

#endif _SCENE