#pragma once
#pragma warning(disable : 4018)

#include "Pixel.h"
#include "SpritesModel.h"
#include "../Row/Player/Player.h"
#include "../Row/EnemyRow/EnemyRow.h"

#include <string>

class Scene
{
private:
	int width_, height_;
	Pixel** thePrevScene_, ** theScene_;

	SpritesModel model_;

	// Not const char*
	void cusStrcpy(int coordX, int coordY, char* model, int size)
	{
		// Check if in map
		// Only copy in the map
		for (int i = 0; i < size; ++i)
			if ((coordX + i > MapLeftCol && coordX + i < MapRightCol) && (coordY > MapTopRow && coordY < MapBottomRow))
				theScene_[coordY][coordX + i].setContent(model[i]);
	}
	void cusStrcpyNInMap(int coordX, int coordY, char* model, int size)
	{
		for (int i = 0; i < size; ++i)
			if ((coordX + i >= 0 && coordX + i < width_) && (coordY >= 0 && coordY < height_))
				theScene_[coordY][coordX + i].setContent(model[i]);
	}
	// Const char*
	void cusStrcpy(int coordX, int coordY, const char* model, int size)
	{
		// Check if in map
		// Only copy in the map
		for (int i = 0; i < size; ++i)
			if ((coordX + i > MapLeftCol && coordX + i < MapRightCol) && (coordY > MapTopRow && coordY < MapBottomRow))
				theScene_[coordY][coordX + i].setContent(model[i]);
	}
	void cusStrcpyNInMap(int coordX, int coordY, const char* model, int size)
	{
		for (int i = 0; i < size; ++i)
			if ((coordX + i >= 0 && coordX + i < width_) && (coordY >= 0 && coordY < height_))
				theScene_[coordY][coordX + i].setContent(model[i]);
	}

public:
	// Init two buffer and whitespace to it
	Scene()
	{
		GetWindowBufferSize(height_, width_);
		theScene_ = new Pixel * [height_];
		for (int i = 0; i < height_; ++i)
			theScene_[i] = new Pixel[width_];

		thePrevScene_ = new Pixel * [height_];
		for (int i = 0; i < height_; ++i)
			thePrevScene_[i] = new Pixel[width_];
	}
	~Scene()
	{
		for (int i = 0; i < height_; ++i)
		{
			delete[] thePrevScene_[i];
			delete[] theScene_[i];
		}

		delete[] thePrevScene_;
		delete[] theScene_;
	}
	// Reset all pixel to space char and clear the color
	void drawAllWhite()
	{
		for (int i = 0; i < height_; ++i)
			for (int j = 0; j < width_; ++j)
			{
				if (j == width_ - 1)
					theScene_[i][j].setContent('\n');
				else
					theScene_[i][j].setContent(' ');

				theScene_[i][j].setForeGround(FOREGROUND_WHITE);
				theScene_[i][j].setBackground(FOREGROUND_BLACK);
			}
	}
	// Reset all pixel to space char
	void drawContentWhite()
	{
		for (int i = 0; i < height_; ++i)
			for (int j = 0; j < width_; ++j)
			{
				if (j == width_ - 1)
					theScene_[i][j].content_ = '\n';
				else
					theScene_[i][j].content_ = ' ';
			}
	}
	// Draw \n to the right edge of theScene_
	void drawNewLineAtEnd()
	{
		for (int i = 0; i < height_; ++i)
			theScene_[i][width_ - 1].setContent('\n');
	}

	void drawBorder()
	{
		for (int i = 0; i < height_; ++i)
		{
			for (int j = 0; j < width_; ++j)
			{
				if ((i == MapTopRow || i == MapBottomRow - 1) && (j >= MapLeftCol && j <= MapRightCol))
					theScene_[i][j].setContent('#');
				else if (j == MapLeftCol || j == MapRightCol)
					theScene_[i][j].setContent('#');
			}
		}
	}
	void drawLevelAndInfo(int level)
	{
		char levelInfo[17];
		for (char& i : levelInfo)
			i = ' ';
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
	void drawIsPause(bool isPause)
	{
		const char* isPauseStr[] = { "[X] Pause", "[ ] Not Pause" };
		if (isPause)
		{
			cusStrcpyNInMap(115, 22, isPauseStr[0], 9);
			for (int i = 0; i < 9; ++i)
				theScene_[22][115 + i].background_ = BACKGROUND_RED;
		} else
		{
			cusStrcpyNInMap(115, 22, isPauseStr[1], 13);
			for (int i = 0; i < 13; ++i)
				theScene_[22][115 + i].background_ = BACKGROUND_GREEN;
		}
	}

	void drawMenu(int choose, int color)
	{
		drawAllWhite();
		drawNewLineAtEnd();

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
				theScene_[row][20 + col].setForeGround(color);
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
				theScene_[15][36 + i].setForeGround(FOREGROUND_BLUE);
			break;
		case 1:
			for (int i = 0; i < 12; ++i)
				theScene_[16][36 + i].setForeGround(FOREGROUND_BLUE);
			break;
		case 2:
			for (int i = 0; i < 10; ++i)
				theScene_[17][36 + i].setForeGround(FOREGROUND_BLUE);
			break;
		case 3:
			for (int i = 0; i < 9; ++i)
				theScene_[18][36 + i].setForeGround(FOREGROUND_BLUE);
			break;
		default:
			for (int i = 0; i < 7; ++i)
				theScene_[19][36 + i].setForeGround(FOREGROUND_BLUE);
			break;
		}
	}
	void drawPlayer(Player player)
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
	void drawOneRow(EnemyRow& enemyRow, int index)
	{
		OneRow* theRow = enemyRow.getListRow()[index];
		// Right
		if (theRow->getDirection())
		{
			// Draw Light
			if (theRow->getIsRedLight())
				theScene_[2 + 5 * (theRow->getCurrentRow() - 1)][MapRightCol + 1].background_ = BACKGROUND_LIGHT_RED;
			else
				theScene_[2 + 5 * (theRow->getCurrentRow() - 1)][MapRightCol + 1].background_ = BACKGROUND_LIGHT_GREEN;
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
				theScene_[2 + 5 * (theRow->getCurrentRow() - 1)][MapLeftCol - 1].background_ = BACKGROUND_LIGHT_RED;
			else
				theScene_[2 + 5 * (theRow->getCurrentRow() - 1)][MapLeftCol - 1].background_ = BACKGROUND_LIGHT_GREEN;

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

	void drawSaveFile(std::string fileName)
	{
		cusStrcpyNInMap(40, 14, "- This is Save File", 19);

		// To long will bug
		std::string strName = "- Name: " + fileName;
		cusStrcpyNInMap(40, 16, strName.c_str(), strName.length());

		cusStrcpyNInMap(40, 18, "- Press <Enter> to save", 23);
		cusStrcpyNInMap(40, 19, "- Press <ESC> to go back", 24);
	}
	void drawLoadFile(std::vector<std::string> listFile, int choose)
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
						theScene_[16 + i][40 + j].foreground_ = FOREGROUND_LIGHT_YELLOW;
				}
			}

			cusStrcpyNInMap(40, 16 + listFile.size() + 2, "- Press <Enter> to save", 23);
			cusStrcpyNInMap(40, 16 + listFile.size() + 3, "- Press <ESC> to go back", 24);
		}
	}

	void drawDeadScene(int i)
	{
		std::string deadStr = "[*] This is the dead scene " + std::to_string(i);
		cusStrcpyNInMap(50, 15, deadStr.c_str(), deadStr.length());
	}
	void drawContinueGame(int choose)
	{
		const char* CapAndOption[] = { "Do you want to continue: ", "[*] Yes", "[*] No" };
		cusStrcpyNInMap(50, 15, CapAndOption[0], 25);
		cusStrcpyNInMap(50, 17, CapAndOption[1], 7);
		cusStrcpyNInMap(50, 18, CapAndOption[2], 6);

		if (choose == 0)
		{
			for (int i = 0; i < 8; ++i)
				theScene_[17][50 + i].background_ = BACKGROUND_LIGHT_PURPLE;
		} else
		{
			for (int i = 0; i < 7; ++i)
				theScene_[18][50 + i].background_ = BACKGROUND_LIGHT_PURPLE;
		}
	}
	void drawSetting()
	{
		cusStrcpyNInMap(50, 15, "- This is setting", 17);

		if (g_isHard)
		{
			cusStrcpyNInMap(50, 17, "- Hard mode: [X]", 16);
			for (int i = 0; i < 16; ++i)
				theScene_[17][50 + i].background_ = BACKGROUND_YELLOW;
		} else
		{
			cusStrcpyNInMap(50, 17, "- Hard mode: [ ]", 16);
			for (int i = 0; i < 16; ++i)
				theScene_[17][50 + i].background_ = BACKGROUND_BLUE;
		}

		cusStrcpyNInMap(50, 19, "- Press <Enter> to toggle", 25);
		cusStrcpyNInMap(50, 20, "- Press <ESC> to go back", 24);
	}
	void drawCredit()
	{
		cusStrcpyNInMap(20, 6, R"(a'!   _,,_ a'!   _,,_     a'!   _,,_     )", 41);
		cusStrcpyNInMap(20, 7, R"(  \\_/    \  \\_/    \      \\_/    \.-, )", 41);
		cusStrcpyNInMap(20, 8, R"(   \, /-( /'-,\, /-( /'-,    \, /-( /    )", 41);
		cusStrcpyNInMap(20, 9, R"(   //\ //\\   //\ //\\       //\ //\\jrei)", 41);

		for (int row = 0; row < 4; ++row)
			for (int col = 0; col < 41; ++col)
				theScene_[6 + row][20 + col].setForeGround(rand() % 16);

		cusStrcpyNInMap(25, 10, R"(Credit image from here: https://ascii.co.uk/art/camel)", 53);

		for (int col = 0; col < 53; ++col)
			theScene_[10][25 + col].setForeGround(rand() % 16);

		cusStrcpyNInMap(31, 15, R"(This game made by LacDaLacDa(hieucckha))", 39);
		cusStrcpyNInMap(37, 16, R"(Have fun in coding :3)", 21);


		cusStrcpyNInMap(34, 19, "Press any key to change color", 29);

		for (int col = 0; col < 29; ++col)
			theScene_[19][34 + col].setForeGround(rand() % 16);

		cusStrcpyNInMap(37, 20, "Press <ESC> to go back", 24);

		for (int col = 0; col < 24; ++col)
			theScene_[20][37 + col].setForeGround(rand() % 16);
	}

	void drawExitGame()
	{
		cusStrcpyNInMap(20, 6, R"(a'!   _,,_ a'!   _,,_     a'!   _,,_     )", 41);
		cusStrcpyNInMap(20, 7, R"(  \\_/    \  \\_/    \      \\_/    \.-, )", 41);
		cusStrcpyNInMap(20, 8, R"(   \, /-( /'-,\, /-( /'-,    \, /-( /    )", 41);
		cusStrcpyNInMap(20, 9, R"(   //\ //\\   //\ //\\       //\ //\\jrei)", 41);

		for (int row = 0; row < 4; ++row)
			for (int col = 0; col < 41; ++col)
				theScene_[6 + row][20 + col].setForeGround(rand() % 16);

		cusStrcpyNInMap(25, 10, R"(Credit image from here: https://ascii.co.uk/art/camel)", 53);

		for (int col = 0; col < 53; ++col)
			theScene_[10][25 + col].setForeGround(rand() % 16);

		cusStrcpyNInMap(31, 15, R"(This game made by LacDaLacDa(hieucckha))", 39);
		cusStrcpyNInMap(37, 16, R"(Have fun in coding :3)", 21);
	}

	void showScene()
	{
		for (int i = 0; i < height_; ++i)
		{
			for (int j = 0; j < width_; ++j)
			{
				/*if (theScene_[i][j].content_ == thePrevScene_[i][j].content_ &&
					theScene_[i][j].foreground_ == thePrevScene_[i][j].foreground_)
				{
					continue;
				} else if (theScene_[i][j].content_ != thePrevScene_[i][j].content_ &&
					theScene_[i][j].foreground_ == thePrevScene_[i][j].foreground_)
				{
					GotoXY(j, i);
					setConsoleColor(theScene_[i][j].getForeground());
					std::cout << theScene_[i][j].content_;
				} else if (theScene_[i][j].content_ == thePrevScene_[i][j].content_ &&
					theScene_[i][j].foreground_ != thePrevScene_[i][j].foreground_)
				{
					GotoXY(j, i);
					setConsoleColor(theScene_[i][j].getForeground());
					std::cout << theScene_[i][j].content_;
				} else
				{
					GotoXY(j, i);
					setConsoleColor(theScene_[i][j].getForeground());
					std::cout << theScene_[i][j].content_;
				}*/

				if (theScene_[i][j].content_ == thePrevScene_[i][j].content_ &&
					theScene_[i][j].foreground_ == thePrevScene_[i][j].foreground_ &&
					theScene_[i][j].background_ == thePrevScene_[i][j].background_)
					continue;

				GotoXY(j, i);
				setConsoleColor(theScene_[i][j].getBackground() | theScene_[i][j].getForeground());
				std::cout << theScene_[i][j].content_;
			}
		}
		std::cout.flush();

		for (int i = 0; i < height_; ++i)
			memcpy(thePrevScene_[i], theScene_[i], sizeof(Pixel) * width_);

		drawContentWhite();
		drawAllWhite();
	}
};
