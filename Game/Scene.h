#ifndef _SCENE
#define _SCENE

#include <iostream>
#include <vector>
#include <string>
#include "Row.h"
#include "Sprite.h"
#include "Pixel.h"
#include "Win32Helper.h"

enum class LightMode
{
	RED, GREEN
};

class Scene
{
private:
	int _row = 30, _playCol = 110, _totalCol = 150;

	char _prevContentBuffer[30][150];
	char _contentBuffer[30][150];

	char _prevForegroundBuffer[30][150];
	char _foregroundBuffer[30][150];

	LightMode _prevLight[4];
	LightMode _light[4];

	Sprite _logo;
public:
	Scene()
	{
		memset(_contentBuffer, (int)' ', 150 * 30);
		memset(_prevContentBuffer, (int)' ', 150 * 30);

		memset(_prevForegroundBuffer, FOREGROUND_WHITE, 150 * 30);
		memset(_foregroundBuffer, FOREGROUND_WHITE, 150 * 30);

		memset(_prevLight, int(LightMode::RED), sizeof(LightMode::RED) * 4);
		memset(_light, int(LightMode::RED), sizeof(LightMode::RED) * 4);

		_logo.openFile("Sprites\\MainScreen.txt");
	}

	~Scene() = default;

	// Getter
	int getCol() const
	{
		return _row;
	}
	int getRow() const
	{
		return _playCol;
	}

	void setStrToBuffer(int col, int row, std::string nd)
	{
		for (int i = 0; i < nd.size(); i++)
			_contentBuffer[row][col + i] = nd[i];
	}

	void clearPrevBuffer()
	{
		memset(_prevContentBuffer, (int)'&', 150 * 30);

		memset(_prevLight, int(LightMode::RED), sizeof(LightMode::RED) * 4);
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
				if (_contentBuffer[r][c] == _prevContentBuffer[r][c] && _foregroundBuffer[r][c] == _prevForegroundBuffer[r][c])
					continue;
				else if (_contentBuffer[r][c] != _prevContentBuffer[r][c] && _foregroundBuffer[r][c] == _prevForegroundBuffer[r][c])
				{
					GotoXY(c, r);
					std::cout << _contentBuffer[r][c];
				} else
				{
					GotoXY(c, r);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _foregroundBuffer[r][c]);
					std::cout << _contentBuffer[r][c];
				}
			}
		}

		for (int i = 0; i < 4; ++i)
		{
			if (_light[i] != _prevLight[i])
			{
				GotoXY(_playCol + 2, (i + 1) * 5 + 2);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (_light[i] == LightMode::GREEN) ? 10 : 12);
				std::cout << _contentBuffer[(i + 1) * 5 + 2][_playCol + 2];
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

		std::cout.flush();

		std::memcpy((char*)_prevContentBuffer, (char const*)_contentBuffer, 150 * 30);
		std::memcpy((char*)_prevForegroundBuffer, (char const*)_foregroundBuffer, 150 * 30);
		std::memcpy((char*)_prevLight, (char const*)_light, sizeof(LightMode::GREEN) * 4);

		memset(_foregroundBuffer, FOREGROUND_WHITE, 150 * 30);
	}

	/// <summary>
	/// Generate and display ALL elements of the game
	/// </summary>
	void drawScene(int level_)
	{
		//ClearConsoleScreen();

		for (int i = 0; i < _row; ++i)
			_contentBuffer[i][_totalCol - 1] = '\n';

		for (int r = 0; r < _row; ++r)
		{
			for (int c = 0; c < _totalCol - 40; ++c)
			{
				if (r == 0 || r == _row - 1)
					_contentBuffer[r][c] = '#';
				else if (r % 5 == 0)
				{
					if (c == 0 || c == _totalCol - 41)
						_contentBuffer[r][c] = '#';
					else
						_contentBuffer[r][c] = '_';
				} else
				{
					if (c == 0 || c == _totalCol - 41)
						_contentBuffer[r][c] = '#';
					else
						_contentBuffer[r][c] = ' ';
				}
			}
		}

		snprintf((*(_contentBuffer + _row / 2) + _playCol + 2), 14, "Level: %d", level_);

		snprintf((*(_contentBuffer + 7) + _playCol + 2), 2, "%c", 254);
		snprintf((*(_contentBuffer + 12) + _playCol + 2), 2, "%c", 254);
		snprintf((*(_contentBuffer + 17) + _playCol + 2), 2, "%c", 254);
		snprintf((*(_contentBuffer + 22) + _playCol + 2), 2, "%c", 254);
	}

	void deadByBird()
	{
		int x = 5, y = 20;

		std::fstream file("Scene\\BirdDeath.txt");
		int r, c, total;
		file >> r;
		file >> c;
		file >> total;
		file.ignore();

		for (int i = 0; i < total; ++i)
		{
			for (int j = 0; j < r; ++j)
			{
				std::string temp;
				getline(file, temp);
				setStrToBuffer(y, x + j, temp);
			}
			file.ignore();
			PrintBuffer();
			Sleep(225);
		}

		file.close();
	}

	void deadByDino()
	{
		int x = 5, y = 19;

		std::fstream file("Scene\\DinoDeath.txt");
		int r, c, total;
		file >> r;
		file >> c;
		file >> total;
		file.ignore();

		for (int i = 0; i < total; ++i)
		{
			for (int j = 0; j < r; ++j)
			{
				std::string temp;
				getline(file, temp);
				setStrToBuffer(y, x + j, temp);
			}
			file.ignore();
			PrintBuffer();
			Sleep(300);
		}

		Sleep(150);
		file.close();
	}

	void deadByVehicle()
	{
		int x = 8, y = 20;

		std::fstream file("Scene\\CarDeath.txt");
		int r, c, total;
		file >> r;
		file >> c;
		file >> total;
		file.ignore();

		for (int i = 0; i < total; ++i)
		{
			for (int j = 0; j < r; ++j)
			{
				std::string temp;
				getline(file, temp);
				setStrToBuffer(y, x + j, temp);
			}
			file.ignore();
			PrintBuffer();
			Sleep(250);
		}

		file.close();
	}

	void drawEntity(const Entity& obj, bool isRight = false)
	{
		for (int y = 0; y < obj.getSpriteHeight(); ++y)
			for (int x = 0; x < obj.getSpriteWidth(); ++x)
			{
				if ((y + obj.getY() - obj.getBound(0) > 0 && y + obj.getY() - obj.getBound(0) < _row - 1) && (x + obj.getX() - obj.getBound(3) > 0 && x + obj.getX() - obj.getBound(3) < _playCol - 1))
					_contentBuffer[y + obj.getY() - obj.getBound(0)][x + obj.getX() - obj.getBound(3)] = obj.getSprite(isRight)[y][x];
			}
	}

	void drawOneRow(const Row& obj) // Draw rows here
	{
		//Draw traffic light
		if (obj.GetRedLight())
			_light[(obj.GetY() - 2) / 5 - 1] = LightMode::RED;
		else
			_light[(obj.GetY() - 2) / 5 - 1] = LightMode::GREEN;

		for (auto& enemy : obj.GetList())
			drawEntity(*enemy, !obj.getIsFromRight());
	}

	void drawMainMenu()
	{
		for (int i = 0; i < _logo.getHeight(); ++i)
		{
			for (int j = 0; j < _logo.getWidth(); ++j)
			{
				_contentBuffer[i + 3][j + 42] = _logo[i][j];
				_foregroundBuffer[i + 3][j + 42] = FOREGROUND_LIGHT_GREEN;
			}
		}

		for (int i = 0; i < 7; ++i)
			memcpy((char*)(_contentBuffer[i + 19] + 61), (char*)(MainMenu[i]), strlen(MainMenu[0]));
	}

	void drawSettingMenu()
	{
		for (int i = 0; i < 7; ++i)
			memcpy((char*)(_contentBuffer[i + 19] + 61), (char*)(Setting[i]), strlen(Setting[0]));
	}

	void drawDeadMenu()
	{
		for (int i = 0; i < 7; ++i)
		{
			memcpy((char*)(_contentBuffer[i + 12] + 39), (char*)(DeadMenu[i]), strlen(DeadMenu[0]));
			memset(_foregroundBuffer[i + 12] + 39, FOREGROUND_RED, sizeof(char) * strlen(DeadMenu[0]));
		}
	}

	void drawLoadMenu()
	{
		for (int i = 0; i < 16; ++i)
			memcpy((char*)(_contentBuffer[i + 8] + 35), (char*)(LoadMenu[i]), strlen(LoadMenu[0]));
	}

	void drawSaveMenu()
	{
		for (int i = 0; i < 5; ++i)
			memcpy((char*)(_contentBuffer[i + 13] + 35), (char*)(SaveMenu[i]), strlen(SaveMenu[0]));
	}

	void drawPauseMenu()
	{
		for (int i = 0; i < 5; ++i)
			memcpy((char*)(_contentBuffer[i + 13] + 35), (char*)(PauseMenu[i]), strlen(PauseMenu[0]));
	}

	const static char DeadMenu[7][33];
	const static char LoadMenu[16][41];
	const static char SaveMenu[5][41];
	const static char PauseMenu[5][41];
	const static char MainMenu[7][27];
	const static char Setting[7][27];
};

#endif //!_SCENE