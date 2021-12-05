#ifndef _SCENE
#define _SCENE

#include <iostream>
#include <vector>
#include "Row.h"
#include "Pixel.h"
#include "Win32Helper.h"

enum class LightMode { RED, GREEN };

class Scene
{
private:
	int row = 30, playCol = 110, totalCol = 150;
	char PrevBuffer[30][150];
	char Buffer[30][150];
	LightMode PrevLight[4];
	LightMode Light[4];

public:
	Scene()
	{
		memset(Buffer, (int)' ', 150 * 30);
		memset(PrevBuffer, (int)' ', 150 * 30);

		memset(PrevLight, int(LightMode::GREEN), sizeof(LightMode::GREEN) * 4);
		memset(Light, int(LightMode::GREEN), sizeof(LightMode::GREEN) * 4);
	}

	~Scene()
	{
	}

	int getCol() const
	{
		return row;
	}

	int getRow() const
	{
		return playCol;
	}

	void setBuffer(int col, int row, std::string nd)
	{
		for (int i = 0; i < nd.size(); i++)
			Buffer[row][col + i] = nd[i];
	}

	/// <summary>
	/// Display generated Buffer to the monitor
	/// </summary>
	void PrintBuffer()
	{
		for (SHORT r = 0; r < 30; ++r)
		{
			for (SHORT c = 0; c < 150; ++c)
			{
				if (Buffer[r][c] == PrevBuffer[r][c])
					continue;

				GotoXY(c, r);
				std::cout << Buffer[r][c];
			}
		}

		for (int i = 0; i < 4; ++i) {
			if (Light[i] != PrevLight[i])
			{
				GotoXY(playCol + 2, (i + 1) * 5 + 2);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (Light[i] == LightMode::GREEN) ? 10 : 12);
				std::cout << Buffer[(i + 1) * 5 + 2][playCol + 2];
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

		std::cout.flush();
		std::memcpy((char*)PrevBuffer, (char const*)Buffer, 150 * 30);
		std::memcpy((char*)PrevLight, (char const*)Light, sizeof(LightMode::GREEN) * 4);
	}

	/// <summary>
	/// Generate and display ALL elements of the game
	/// </summary>
	void drawScene(int level_)
	{
		//ClearConsoleScreen();

		for (int i = 0; i < row; ++i)
			Buffer[i][totalCol - 1] = '\n';

		for (int r = 0; r < row; ++r)
		{
			for (int c = 0; c < totalCol - 40; ++c)
			{
				if (r == 0 || r == row - 1)
					Buffer[r][c] = '#';
				else if (r % 5 == 0)
				{
					if (c == 0 || c == totalCol - 41)
						Buffer[r][c] = '#';
					else
						Buffer[r][c] = '_';
				}
				else
				{
					if (c == 0 || c == totalCol - 41)
						Buffer[r][c] = '#';
					else
						Buffer[r][c] = ' ';
				}
			}
		}

		snprintf((*(Buffer + row / 2) + playCol + 2), 14, "Level: %d", level_);

		snprintf((*(Buffer + 7) + playCol + 2), 2, "%c", 254);
		snprintf((*(Buffer + 12) + playCol + 2), 2, "%c", 254);
		snprintf((*(Buffer + 17) + playCol + 2), 2, "%c", 254);
		snprintf((*(Buffer + 22) + playCol + 2), 2, "%c", 254);
	}

	void drawEntity(const Entity& obj, bool isRight = 0)
	{
		for (int y = 0; y < obj.getSpriteHeight(); ++y)
			for (int x = 0; x < obj.getSpriteWidth(); ++x) {
				if ((y + obj.getY() - obj.getBound(0) > 0 && y + obj.getY() - obj.getBound(0) < row - 1) && (x + obj.getX() - obj.getBound(3) > 0 && x + obj.getX() - obj.getBound(3) < playCol - 1))
					Buffer[y + obj.getY() - obj.getBound(0)][x + obj.getX() - obj.getBound(3)] = obj.getSprite(isRight)[y][x];
			}
	}

	void drawOneRow(const Row& obj) // Draw rows here
	{
		//Draw traffic light
		if (obj.GetRedLight())
			Light[(obj.GetY() - 2) / 5 - 1] = LightMode::RED;
		else
			Light[(obj.GetY() - 2) / 5 - 1] = LightMode::GREEN;

		for (auto& enemy : obj.GetList())
			drawEntity(*enemy, !obj.getIsFromRight());
	}

	void drawDeadMenu()
	{
		for (int i = 0; i < 7; ++i)
			memcpy((char*)(Buffer[i + 12] + 24), (char*)(DeadMenu[i]), strlen(DeadMenu[0]));
	}

	void drawLoadMenu()
	{
		for (int i = 0; i < 10; ++i)
			memcpy((char*)(Buffer[i + 12] + 20), (char*)(LoadMenu[i]), strlen(LoadMenu[0]));
	}

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
	const static char LoadMenu[10][41];
	const static char SaveMenu[5][41];
	const static char PauseMenu[5][41];
};

#endif _SCENE