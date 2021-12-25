#pragma once
#pragma warning(disable : 4018)

#include "Pixel.h"
#include "SpritesModel.h"
#include "../Row/Player/Player.h"
#include "../Row/EnemyRow/EnemyRow.h"

#include <string>
#include <chrono>

class Scene
{
private:
	int _width, _height;
	Pixel** _prevScene, ** _currScene;

	SpritesModel model_;

	std::chrono::high_resolution_clock::time_point _startOfSecond;
	unsigned int _fps;
	unsigned int _fpsCount;

private:
	// Not const char*
	void cusStrcpy(int coordX, int coordY, char* model, int size)
	{
		// Check if in map
		// Only copy in the map
		for (int i = 0; i < size; ++i)
			if ((coordX + i > MapLeftCol && coordX + i < MapRightCol) && (coordY > MapTopRow && coordY < MapBottomRow))
				_currScene[coordY][coordX + i]._content = model[i];
	}
	void cusStrcpyNInMap(int coordX, int coordY, char* model, int size)
	{
		for (int i = 0; i < size; ++i)
			if ((coordX + i >= 0 && coordX + i < _width) && (coordY >= 0 && coordY < _height))
				_currScene[coordY][coordX + i]._content = model[i];
	}
	// Const char*
	void cusStrcpy(int coordX, int coordY, const char* model, int size)
	{
		// Check if in map
		// Only copy in the map
		for (int i = 0; i < size; ++i)
			if ((coordX + i > MapLeftCol && coordX + i < MapRightCol) && (coordY > MapTopRow && coordY < MapBottomRow))
				_currScene[coordY][coordX + i]._content = model[i];
	}
	void cusStrcpyNInMap(int coordX, int coordY, const char* model, int size)
	{
		for (int i = 0; i < size; ++i)
			if ((coordX + i >= 0 && coordX + i < _width) && (coordY >= 0 && coordY < _height))
				_currScene[coordY][coordX + i]._content = model[i];
	}

public:
	// Init two buffer and whitespace to it
	Scene()
	{
		std::ios_base::sync_with_stdio(false);

		GetWindowBufferSize(_height, _width);
		_currScene = new Pixel * [_height];
		for (int i = 0; i < _height; ++i)
			_currScene[i] = new Pixel[_width];

		_prevScene = new Pixel * [_height];
		for (int i = 0; i < _height; ++i)
			_prevScene[i] = new Pixel[_width];

		_startOfSecond = std::chrono::high_resolution_clock::now();
		_fps = 0;
		_fpsCount = 0;
	}
	~Scene()
	{
		for (int i = 0; i < _height; ++i)
		{
			delete[] _prevScene[i];
			delete[] _currScene[i];
		}

		delete[] _prevScene;
		delete[] _currScene;
	}
	//// Reset all pixel to space char and clear the color
	//void drawAllWhite()
	//{
	//	for (int i = 0; i < _height; ++i)
	//		for (int j = 0; j < _width; ++j)
	//		{
	//			if (j == _width - 1)
	//				_currScene[i][j]._content = '\n';
	//			else
	//			{
	//				// #TODO This 
	//				_currScene[i][j]._content = ' ';
	//			}

	//			// #TODO this
	//			_currScene[i][j]._bafoGround |= FG_WHITE;
	//			_currScene[i][j]._bafoGround |= FG_BLACK;
	//		}
	//}
	//// Reset all pixel to space char
	//void drawContentWhite()
	//{
	//	for (int i = 0; i < _height; ++i)
	//		for (int j = 0; j < _width; ++j)
	//		{
	//			if (j == _width - 1)
	//				_currScene[i][j]._content = '\n';
	//			else
	//				_currScene[i][j]._content = ' ';
	//		}
	//}
	void ClearScene()
	{
		// 0x20 is (Space character) and 0x07 is (BLACK_BACKGROUND | WHITE_FOREGROUND)
		// Because little endian so must to swap to 0x0720
		for (int row = 0; row < _height; ++row)
		{
			unsigned short* p = reinterpret_cast<unsigned short*>(_currScene[row]);

			for (int col = 0; col < _width; ++col)
				*(p + col) = 0x0720;
		}
	}

	//// Draw \n to the right edge of theScene_
	//void DrawNewLineAtEnd()
	//{
	//	for (int i = 0; i < _height; ++i)
	//		_currScene[i][_width - 1]._content = '\n';
	//}

	void DrawBorder()
	{
		for (int i = 0; i < _height; ++i)
		{
			for (int j = 0; j < _width; ++j)
			{
				if ((i == MapTopRow || i == MapBottomRow - 1) && (j >= MapLeftCol && j <= MapRightCol))
					_currScene[i][j]._content = '#';
				else if (j == MapLeftCol || j == MapRightCol)
					_currScene[i][j]._content = '#';
			}
		}
	}
	void DrawLevelAndInfo(int level)
	{
		char fpsStr[12];
		for (auto& chr : fpsStr)
			chr = ' ';
		snprintf(fpsStr, 12, "- FPS: %d", _fps);
		cusStrcpyNInMap(115, 5, fpsStr, 11);

		char levelInfo[17];
		for (char& chr : levelInfo)
			chr = ' ';
		snprintf(levelInfo, 17, "- LEVEL: %i", level);
		cusStrcpyNInMap(115, 7, levelInfo, 17);

		const char* moving[] = { "- MOVING", "[ A ] Left", "[ W ] Up", "[ D ] Right", "[ S ] Down" };
		cusStrcpyNInMap(115, 9, moving[0], 8);
		cusStrcpyNInMap(115, 10, moving[1], 10);
		cusStrcpyNInMap(115, 11, moving[2], 8);
		cusStrcpyNInMap(115, 12, moving[3], 11);
		cusStrcpyNInMap(115, 13, moving[4], 10);

		const char* function[] = { "- FUNCTION", "[ P ] Pause", "[ R ] Resume", "[ T ] Save Game", "[ L ] Load Game", "[ Q ] Return to Menu" };
		cusStrcpyNInMap(115, 15, function[0], 10);
		cusStrcpyNInMap(115, 16, function[1], 11);
		cusStrcpyNInMap(115, 17, function[2], 12);
		cusStrcpyNInMap(115, 18, function[3], 15);
		cusStrcpyNInMap(115, 19, function[4], 15);
		cusStrcpyNInMap(115, 20, function[5], 20);
	}
	void DrawIsPause(bool isPause)
	{
		const char* isPauseStr[] = { "[X] Pause", "[ ] Not Pause" };
		if (isPause)
		{
			cusStrcpyNInMap(115, 22, isPauseStr[0], 9);
			for (int i = 0; i < 9; ++i)
				_currScene[22][115 + i]._bafoGround |= BG_RED;
		} else
		{
			cusStrcpyNInMap(115, 22, isPauseStr[1], 13);
			for (int i = 0; i < 13; ++i)
				_currScene[22][115 + i]._bafoGround |= BG_GREEN;
		}
	}

	void DrawMenu(int choose, unsigned char color)
	{
		/*drawAllWhite();
		DrawNewLineAtEnd();*/

		cusStrcpyNInMap(20, 6, R"(_________                         _____                    ________             _________)", 90);
		cusStrcpyNInMap(20, 7, R"(__  ____/____________________________(_)_____________ _    ___  __ \\___________ ______ /)", 90);
		cusStrcpyNInMap(20, 8, R"(_  /    __  ___/  __ \  __ \_  ___/_  /__  __ \_  __ `/    __  /_/ /  __ \  __ `/  __  / )", 90);
		cusStrcpyNInMap(20, 9, R"(/ /___  _  /   / /_/ / /_/ /(__  )_  / _  / / /  /_/ /     _  _, _// /_/ / /_/ // /_/ /  )", 90);
		cusStrcpyNInMap(20, 10, R"(\____/  /_/    \____/\____//____/ /_/  /_/ /_/_\__, /      /_/ |_| \____/\__,_/ \__,_/   )", 90);
		cusStrcpyNInMap(20, 11, R"(                                              /____/                                     )", 90);

		for (int row = 6; row <= 11; ++row)
		{
			for (int col = 0; col < 90; ++col)
			{
				_currScene[row][20 + col]._bafoGround = BG_DEFAULT | color;
			}
		}

		cusStrcpyNInMap(36, 15, "1. New Game", 11);
		cusStrcpyNInMap(36, 16, "2. Load Game", 12);
		cusStrcpyNInMap(36, 17, "3. Setting", 10);
		cusStrcpyNInMap(36, 18, "4. Credit", 9);
		cusStrcpyNInMap(36, 19, "5. Quit", 7);

		switch (choose)
		{
		case 0:
			for (int i = 0; i < 11; ++i)
				_currScene[15][36 + i]._bafoGround = BG_DEFAULT | FG_BLUE;
			break;
		case 1:
			for (int i = 0; i < 12; ++i)
				_currScene[16][36 + i]._bafoGround = BG_DEFAULT | FG_BLUE;
			break;
		case 2:
			for (int i = 0; i < 10; ++i)
				_currScene[17][36 + i]._bafoGround = BG_DEFAULT | FG_BLUE;
			break;
		case 3:
			for (int i = 0; i < 9; ++i)
				_currScene[18][36 + i]._bafoGround = BG_DEFAULT | FG_BLUE;
			break;
		default:
			for (int i = 0; i < 7; ++i)
				_currScene[19][36 + i]._bafoGround = BG_DEFAULT | FG_BLUE;
			break;
		}
	}
	void DrawPlayer(Player player)
	{
		Point2D coord = player.getCoord();

		/* [4][5]
		 _0_
		/| |\
		 \_/
		 / \
		*/

		for (int rowOfModel = 0; rowOfModel < 4; ++rowOfModel)
			cusStrcpy(coord.getX(), coord.getY() + rowOfModel, model_.PlayerMiddle_[rowOfModel], 5);
	}
	void DrawOneRow(EnemyRow& enemyRow, int index)
	{
		OneRow* theRow = enemyRow.getListRow()[index];
		// Right
		if (theRow->getDirection())
		{
			// Draw Light
			if (theRow->getIsRedLight())
				_currScene[2 + 5 * (theRow->getCurrentRow() - 1)][MapRightCol + 1]._bafoGround |= BG_LIGHT_RED;
			else
				_currScene[2 + 5 * (theRow->getCurrentRow() - 1)][MapRightCol + 1]._bafoGround |= BG_LIGHT_GREEN;
			for (auto& mem : theRow->getEnemyList())
			{
				Point2D coord = mem->getCoord();
				switch (theRow->getType())
				{
				// Car
				case 0:
					for (int rowOfModel = 0; rowOfModel < 4; ++rowOfModel)
						cusStrcpy(coord.getX(), coord.getY() + rowOfModel, model_.CarRight_[rowOfModel], 12);
					break;
				// Truck
				case 1:
					for (int rowOfModel = 0; rowOfModel < 4; ++rowOfModel)
						cusStrcpy(coord.getX(), coord.getY() + rowOfModel, model_.TruckRight_[rowOfModel], 12);
					break;
				// Bird
				case 2:
					for (int rowOfModel = 0; rowOfModel < 4; ++rowOfModel)
						cusStrcpy(coord.getX(), coord.getY() + rowOfModel, model_.BirdRight_[rowOfModel], 5);
					break;
				// Dinosaur
				case 3:
					for (int rowOfModel = 0; rowOfModel < 4; ++rowOfModel)
						cusStrcpy(coord.getX(), coord.getY() + rowOfModel, model_.DinosaurRight_[rowOfModel], 12);
					break;
				default:
					break;
				}
			}
			// Left
		} else
		{
			// Draw Light
			if (theRow->getIsRedLight())
				_currScene[2 + 5 * (theRow->getCurrentRow() - 1)][MapLeftCol - 1]._bafoGround |= BG_LIGHT_RED;
			else
				_currScene[2 + 5 * (theRow->getCurrentRow() - 1)][MapLeftCol - 1]._bafoGround |= BG_LIGHT_GREEN;

			for (auto& mem : theRow->getEnemyList())
			{
				Point2D coord = mem->getCoord();
				switch (theRow->getType())
				{
				// Car
				case 0:
					for (int rowOfModel = 0; rowOfModel < 4; ++rowOfModel)
						cusStrcpy(coord.getX(), coord.getY() + rowOfModel, model_.CarLeft_[rowOfModel], 12);
					break;
				// Truck
				case 1:
					for (int rowOfModel = 0; rowOfModel < 4; ++rowOfModel)
						cusStrcpy(coord.getX(), coord.getY() + rowOfModel, model_.TruckLeft_[rowOfModel], 12);
					break;
				// Bird
				case 2:
					for (int rowOfModel = 0; rowOfModel < 4; ++rowOfModel)
						cusStrcpy(coord.getX(), coord.getY() + rowOfModel, model_.BirdLeft_[rowOfModel], 5);
					break;
				// Dinosaur
				case 3:
					for (int rowOfModel = 0; rowOfModel < 4; ++rowOfModel)
						cusStrcpy(coord.getX(), coord.getY() + rowOfModel, model_.DinosaurLeft_[rowOfModel], 12);
					break;
				default:
					break;
				}
			}
		}
	}

	void DrawSaveFile(std::string fileName)
	{
		cusStrcpyNInMap(40, 14, "- This is Save File", 19);

		// To long will bug
		std::string strName = "- Name: " + fileName;
		cusStrcpyNInMap(40, 16, strName.c_str(), strName.length());

		cusStrcpyNInMap(40, 18, "- Press <Enter> to save", 23);
		cusStrcpyNInMap(40, 19, "- Press <ESC> to go back", 24);
	}
	void DrawLoadFile(std::vector<std::string> listFile, int choose)
	{
		cusStrcpyNInMap(40, 14, "- This is Save File", 19);

		if (listFile.empty())
		{
			cusStrcpyNInMap(40, 16, "- No file saved", 15);
			cusStrcpyNInMap(40, 17, "- Press <ESC> to go back", 24);
		} else
		{
			std::string fileName;
			for (int i = 0; i < listFile.size(); ++i)
			{
				fileName = listFile[i];
				cusStrcpyNInMap(40, 16 + i, fileName.c_str(), fileName.length());

				if (i == choose)
				{
					for (int j = 0; j < fileName.length(); ++j)
						_currScene[16 + i][40 + j]._bafoGround = BG_DEFAULT | FG_LIGHT_YELLOW;
				}
			}

			cusStrcpyNInMap(40, 16 + listFile.size() + 2, "- Press <Enter> to save", 23);
			cusStrcpyNInMap(40, 16 + listFile.size() + 3, "- Press <ESC> to go back", 24);
		}
	}

	void DrawDeadScene(int i)
	{
		std::string deadStr = "[*] This is the dead scene " + std::to_string(i);
		cusStrcpyNInMap(50, 15, deadStr.c_str(), deadStr.length());
	}
	void DrawContinueGame(int choose)
	{
		const char* CapAndOption[] = { "Do you want to continue: ", "[*] Yes", "[*] No" };
		cusStrcpyNInMap(50, 15, CapAndOption[0], 25);
		cusStrcpyNInMap(50, 17, CapAndOption[1], 7);
		cusStrcpyNInMap(50, 18, CapAndOption[2], 6);

		if (choose == 0)
		{
			for (int i = 0; i < 8; ++i)
				_currScene[17][50 + i]._bafoGround |= BG_LIGHT_PURPLE;
		} else
		{
			for (int i = 0; i < 7; ++i)
				_currScene[18][50 + i]._bafoGround |= BG_LIGHT_PURPLE;
		}
	}
	void DrawSetting()
	{
		cusStrcpyNInMap(50, 15, "- This is setting", 17);

		if (g_isHard)
		{
			cusStrcpyNInMap(50, 17, "- Hard mode: [X]", 16);
			for (int i = 0; i < 16; ++i)
				_currScene[17][50 + i]._bafoGround |= BG_YELLOW;
		} else
		{
			cusStrcpyNInMap(50, 17, "- Hard mode: [ ]", 16);
			for (int i = 0; i < 16; ++i)
				_currScene[17][50 + i]._bafoGround |= BG_BLUE;
		}

		cusStrcpyNInMap(50, 19, "- Press <Enter> to toggle", 25);
		cusStrcpyNInMap(50, 20, "- Press <ESC> to go back", 24);
	}
	void DrawCredit()
	{
		cusStrcpyNInMap(20, 6, R"(a'!   _,,_ a'!   _,,_     a'!   _,,_     )", 41);
		cusStrcpyNInMap(20, 7, R"(  \\_/    \  \\_/    \      \\_/    \.-, )", 41);
		cusStrcpyNInMap(20, 8, R"(   \, /-( /'-,\, /-( /'-,    \, /-( /    )", 41);
		cusStrcpyNInMap(20, 9, R"(   //\ //\\   //\ //\\       //\ //\\jrei)", 41);

		for (int row = 0; row < 4; ++row)
			for (int col = 0; col < 41; ++col)
				_currScene[6 + row][20 + col]._bafoGround = BG_DEFAULT | rand() % 16;

		cusStrcpyNInMap(25, 10, R"(Credit image from here: https://ascii.co.uk/art/camel)", 53);

		for (int col = 0; col < 53; ++col)
			_currScene[10][25 + col]._bafoGround = BG_DEFAULT | rand() % 16;

		cusStrcpyNInMap(31, 15, R"(This game made by LacDaLacDa(hieucckha))", 39);
		cusStrcpyNInMap(37, 16, R"(Have fun in coding :3)", 21);


		cusStrcpyNInMap(34, 19, "Press any key to change color", 29);

		for (int col = 0; col < 29; ++col)
			_currScene[19][34 + col]._bafoGround = BG_DEFAULT | rand() % 16;

		cusStrcpyNInMap(37, 20, "Press <ESC> to go back", 24);

		for (int col = 0; col < 24; ++col)
			_currScene[20][37 + col]._bafoGround = BG_DEFAULT | rand() % 16;
	}

	void DrawExitGame()
	{
		cusStrcpyNInMap(20, 6, R"(a'!   _,,_ a'!   _,,_     a'!   _,,_     )", 41);
		cusStrcpyNInMap(20, 7, R"(  \\_/    \  \\_/    \      \\_/    \.-, )", 41);
		cusStrcpyNInMap(20, 8, R"(   \, /-( /'-,\, /-( /'-,    \, /-( /    )", 41);
		cusStrcpyNInMap(20, 9, R"(   //\ //\\   //\ //\\       //\ //\\jrei)", 41);

		for (int row = 0; row < 4; ++row)
			for (int col = 0; col < 41; ++col)
				_currScene[6 + row][20 + col]._bafoGround = BG_DEFAULT | rand() % 16;

		cusStrcpyNInMap(25, 10, R"(Credit image from here: https://ascii.co.uk/art/camel)", 53);

		for (int col = 0; col < 53; ++col)
			_currScene[10][25 + col]._bafoGround = BG_DEFAULT | rand() % 16;

		cusStrcpyNInMap(31, 15, R"(This game made by LacDaLacDa(hieucckha))", 39);
		cusStrcpyNInMap(37, 16, R"(Have fun in coding :3)", 21);
	}

	void SwapScene()
	{
		// int tmp = a;
		// a = b;
		// b = tmp;
		Pixel** tmp = _prevScene;
		_prevScene = _currScene;
		_currScene = tmp;
	}

	void DoneFrame()
	{
		_fpsCount++;

		std::chrono::duration<float> duration = std::chrono::high_resolution_clock::now() - _startOfSecond;
		if (duration.count() > 1)
		{
			_startOfSecond = std::chrono::high_resolution_clock::now();
			_fps = _fpsCount;
			_fpsCount = 0;
		}
	}

	void showScene()
	{
		for (int i = 0; i < _height; ++i)
		{
			for (int j = 0; j < _width; ++j)
			{
				if (_currScene[i][j]._content == _prevScene[i][j]._content && _currScene[i][j]._bafoGround == _prevScene[i][j]._bafoGround)
					continue;

				GotoXY(j, i);
				setConsoleColor(_currScene[i][j]._bafoGround);
				std::cout << _currScene[i][j]._content;
			}
		}
		// Force all char in buffer must write to console
		std::cout.flush();

		SwapScene();
		ClearScene();

		DoneFrame();
	}
};
