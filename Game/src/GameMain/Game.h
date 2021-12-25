#pragma once
#pragma warning( disable : 4018 )

#include "../Row/EnemyRow/EnemyRow.h"
#include "../Row/Player/Player.h"
#include "../SceneAndPoint2D/Scene.h"
#include "../ConstantAndDefine/Define.h"
#include "../WindowsConsole/Win32Helper.h"

#include <conio.h>
#include <fstream>

class Game
{
private:
	int level_;
	int playerRow_;

	Player player_;
	// Control all row which had enemy 
	EnemyRow enemyRow_;

	// Will draw and show to console
	Scene theScene_;

private:
	int inputKey()
	{
		if (_kbhit())
		{
			int key = _getch();

			return key;
		} else
		{
			return -1;
		}
	}
	void SaveFile(std::string fileName, unsigned int tick)
	{
		// If folder data not exist
		if (!dir_exists("./data/"))
			CreateDirectoryA("./data/", nullptr);

		std::string path = "./data/" + fileName + ".bin";
		std::ofstream os(path, std::ios::out | std::ios::binary);

		// level_ : int 
		// playerRow_ : int 
		// player_ : Player -> coord()
		// enemyRow_ : EnemyRow 

		// Tick
		os.write(reinterpret_cast<char*>(&tick), sizeof(tick));
		// Level
		int tmp = level_;
		os.write(reinterpret_cast<char*>(&tmp), sizeof(tmp));
		// Current Row of Player
		tmp = playerRow_;
		os.write(reinterpret_cast<char*>(&tmp), sizeof(tmp));
		// Coord X of Player
		tmp = player_.getCoord().getX();
		os.write(reinterpret_cast<char*>(&tmp), sizeof(tmp));
		// Coord Y of Player
		tmp = player_.getCoord().getY();
		os.write(reinterpret_cast<char*>(&tmp), sizeof(tmp));

		for (auto& mem : enemyRow_.getListRow())
		{
			int tmpInt = 0;
			bool tmpBool = false;
			size_t numEnemy = mem->getEnemyList().size();
			os.write(reinterpret_cast<char*>(&numEnemy), sizeof(numEnemy));

			// Coord of each enemy in row
			for (auto& enemy : mem->getEnemyList())
			{
				tmpInt = enemy->getCoord().getX();
				os.write(reinterpret_cast<char*>(&tmpInt), sizeof(tmpInt));
				tmpInt = enemy->getCoord().getY();
				os.write(reinterpret_cast<char*>(&tmpInt), sizeof(tmpInt));
			}

			// Type
			tmpInt = mem->getType();
			os.write(reinterpret_cast<char*>(&tmpInt), sizeof(tmpInt));

			// LinearRandom
			tmpBool = mem->getLinearRandom();
			os.write(reinterpret_cast<char*>(&tmpBool), sizeof(tmpBool));

			// Direction
			tmpBool = mem->getDirection();
			os.write(reinterpret_cast<char*>(&tmpBool), sizeof(tmpBool));

			// Red Light Or Not
			tmp = mem->getIsRedLight();
			os.write(reinterpret_cast<char*>(&tmpBool), sizeof(tmpBool));

			// Red Light Time
			tmpInt = mem->getRedLightTime();
			os.write(reinterpret_cast<char*>(&tmpInt), sizeof(tmpInt));

			// Speed
			tmpInt = mem->getSpeed();
			os.write(reinterpret_cast<char*>(&tmpInt), sizeof(tmpInt));

			// Current Row
			tmpInt = mem->getCurrentRow();
			os.write(reinterpret_cast<char*>(&tmpInt), sizeof(tmpInt));
		}
	}
	// Return name
	std::vector<std::string> getAllFilename(const std::string& name)
	{
		std::vector<std::string> listFileName;
		std::string pattern(name);
		pattern.append("\\*");

		WIN32_FIND_DATAA data;
		HANDLE hFind;

		if ((hFind = FindFirstFileA(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE)
		{
			do
			{
				std::string str(data.cFileName);
				if (str[0] == '.')
					continue;

				listFileName.push_back(str);
			} while (FindNextFileA(hFind, &data) != 0);

			FindClose(hFind);
		}

		return listFileName;
	}
	// Return current tick
	unsigned int LoadFile(const std::string folder, std::string fileName)
	{
		std::string filePath = "./" + folder + "/" + fileName;
		std::ifstream is(filePath, std::ios::in | std::ios::binary);
		if (is.fail())
		{
			return -1;
		}

		unsigned int tick = 0;

		int tmpInt = 0;
		int tmpInt2 = 0;
		bool tmpBool = false;

		// Tick
		is.read(reinterpret_cast<char*>(&tick), sizeof(tick));
		// Level
		is.read(reinterpret_cast<char*>(&tmpInt), sizeof(tmpInt));
		level_ = tmpInt;
		// Player Row
		is.read(reinterpret_cast<char*>(&tmpInt), sizeof(tmpInt));
		playerRow_ = tmpInt;
		// Player Coord X and Y
		is.read(reinterpret_cast<char*>(&tmpInt), sizeof(tmpInt));
		is.read(reinterpret_cast<char*>(&tmpInt2), sizeof(tmpInt2));
		player_.setCoord(tmpInt, tmpInt2);

		enemyRow_.cleanRow();
		for (int i = 0; i < 6; ++i)
		{
			std::vector<Enemy*> listEnemy;

			int nEnemy = 0;
			is.read(reinterpret_cast<char*>(&nEnemy), sizeof(nEnemy));
			for (int i = 0; i < nEnemy; ++i)
			{
				int coordX = 0, coordY = 0;
				is.read(reinterpret_cast<char*>(&coordX), sizeof(coordX));
				is.read(reinterpret_cast<char*>(&coordY), sizeof(coordY));
				Enemy* enemy = new Enemy(coordX, coordY);
				listEnemy.push_back(enemy);
			}

			int type = 0;
			is.read(reinterpret_cast<char*>(&type), sizeof(type));

			bool linearRandom = false;
			is.read(reinterpret_cast<char*>(&linearRandom), sizeof(linearRandom));

			bool direction = false;
			is.read(reinterpret_cast<char*>(&direction), sizeof(direction));

			bool isRedLight = false;
			is.read(reinterpret_cast<char*>(&isRedLight), sizeof(isRedLight));

			int redLightTime = 0;
			is.read(reinterpret_cast<char*>(&redLightTime), sizeof(redLightTime));

			int speed = 0;
			is.read(reinterpret_cast<char*>(&speed), sizeof(speed));

			int currRow = 0;
			is.read(reinterpret_cast<char*>(&currRow), sizeof(currRow));

			OneRow* oneRow = new OneRow(listEnemy, type, linearRandom, direction, isRedLight, redLightTime, speed, currRow);
			enemyRow_.getListRow().push_back(oneRow);
		}

		return tick;
	}

public:
	Game()
	{
		level_ = 0;
		playerRow_ = 7;
	}
	~Game()
	{
		theScene_.DrawExitGame();
		theScene_.showScene();

		setConsoleColor(BG_BLACK | FG_WHITE);
	}

	void Menu()
	{
		unsigned int tick = 0;

		int choose = 0;

		int color = rand() % 16;
		while (true)
		{
			//theScene_.drawAllWhite();
			theScene_.DrawMenu(choose, color);
			theScene_.showScene();

			switch (inputKey())
			{
			case 'w':
				if (choose > 0)
				{
					color = rand() % 16;
					choose--;
				}
				theScene_.DrawMenu(choose, color);
				theScene_.showScene();
				break;
			case 's':
				if (choose < 4)
				{
					color = rand() % 16;
					choose++;
				}
				theScene_.DrawMenu(choose, color);
				theScene_.showScene();
				break;
			case 13:
				switch (choose)
				{
				// New Game
				case 0:
					runGame(tick);
					break;
				// Load Game
				case 1:
					// Return tick
					g_isPause = true;
					tick = runLoadGame("data");
					if (tick != -1)
						runGame(tick);
					break;
				// Setting
				case 2:
					runSetting();
					break;
				case 3:
					runCredit();
					break;
				// Quit
				default:
					ClearConsoleScreen();
					return;
				}
				break;
			default:
				break;
			}
		}
	}
	void runGame(int tick)
	{
		// 1 While loop done -> 1 tick
		unsigned int tick_ = tick;

		theScene_.DrawBorder();
		theScene_.DrawLevelAndInfo(level_);
		theScene_.DrawPlayer(this->player_);
		theScene_.showScene();

		while (true)
		{
			if (_kbhit())
			{
				int key = _getch();

				// Pause
				if (key == 'p')
				{
					g_isPause = true;
				}
				// Resume
				else if (key == 'r')
				{
					g_isPause = false;
				}
				// Load Game
				else if (key == 'l')
				{
					tick_ = runLoadGame("data");
				}
				// Save Game
				else if (key == 't')
				{
					runSaveGame(tick);
				}
				// Moving Left
				else if (key == 'a' && !g_isPause)
				{
					player_.move(DIRECTION_PLAYER::LEFT_DIRECTION);
				}
				// Moving Up
				else if (key == 'w' && !g_isPause)
				{
					player_.move(DIRECTION_PLAYER::TOP_DIRECTION);
					if (playerRow_ <= 7 && playerRow_ > 0)
						playerRow_--;
				}
				// Moving Right
				else if (key == 'd' && !g_isPause)
				{
					player_.move(DIRECTION_PLAYER::RIGHT_DIRECTION);
				}
				// Moving Down
				else if (key == 's' && !g_isPause)
				{
					player_.move(DIRECTION_PLAYER::BOTTOM_DIRECTION);
					if (playerRow_ >= 0 && playerRow_ < 7)
						playerRow_++;
				}
				// Return to menu
				else if (key == 'q')
				{
					level_ = 0;
					player_.reset();
					playerRow_ = 7;
					enemyRow_.setLevel(level_);
					player_.setStateTrue();
					return;
				}
			}

			// Draw 
			if (!g_isPause)
			{
				theScene_.DrawBorder();
				theScene_.DrawLevelAndInfo(level_);
				theScene_.DrawIsPause(g_isPause);

				theScene_.DrawPlayer(this->player_);
				if (player_.checkCollistion(this->enemyRow_, playerRow_))
					player_.setStateFalse();
				for (int i = 0; i < MAXIMUN_ENEMY_ROW; ++i)
				{
					enemyRow_.update(tick_, this->playerRow_, i, level_);
					theScene_.DrawOneRow(this->enemyRow_, i);
					if (player_.checkCollistion(this->enemyRow_, playerRow_))
						player_.setStateFalse();
				}

				theScene_.showScene();
			} else
			{
				theScene_.DrawBorder();
				theScene_.DrawLevelAndInfo(level_);
				theScene_.DrawIsPause(g_isPause);

				theScene_.DrawPlayer(this->player_);
				for (int i = 0; i < MAXIMUN_ENEMY_ROW; ++i)
					theScene_.DrawOneRow(this->enemyRow_, i);

				theScene_.showScene();
			}

			// Dead
			if (!player_.getState())
			{
				for (int i = 0; i < 10; ++i)
				{
					theScene_.DrawDeadScene(i);
					theScene_.showScene();
					Sleep(300);
				}

				int choose = 0;

				// Choose to continue play
				theScene_.DrawContinueGame(choose);
				theScene_.showScene();

				while (true)
				{

					int tmp = _getch();
					if (tmp == 'w')
					{
						if (choose > 0)
							choose--;
					} else if (tmp == 's')
					{
						if (choose < 1)
							choose++;
					}
					// Enter
					else if (tmp == 13)
					{
						// Yes
						if (choose == 0)
						{
							break;
						}
						// No
						else
						{
							level_ = 0;
							player_.reset();
							playerRow_ = 7;
							enemyRow_.setLevel(level_);
							player_.setStateTrue();
							return;
						}
					}

					theScene_.DrawContinueGame(choose);
					theScene_.showScene();
				}

				level_ = 0;

				player_.reset();
				playerRow_ = 7;

				enemyRow_.setLevel(level_);

				theScene_.DrawBorder();
				theScene_.DrawLevelAndInfo(level_);
				theScene_.DrawPlayer(this->player_);
				theScene_.showScene();
				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
				player_.setStateTrue();
			}

			// Finish
			if (playerRow_ == 0)
			{
				Sleep(1000);
				level_++;

				player_.reset();
				playerRow_ = 7;

				enemyRow_.setLevel(level_);

				theScene_.DrawBorder();
				theScene_.DrawLevelAndInfo(level_);
				theScene_.DrawPlayer(this->player_);
				theScene_.showScene();
				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			}

			if (!g_isPause)
				tick_++;
		}
	}
	// Return current tick
	unsigned int runLoadGame(const std::string folder)
	{
		g_isPause = true;

		std::vector<std::string> listFile = getAllFilename(folder);
		size_t nListFile = listFile.size();
		int choose = 0;

		theScene_.DrawLoadFile(listFile, choose);
		theScene_.showScene();

		while (true)
		{
			if (_kbhit())
			{
				int tmp = _getch();

				if (tmp == 'w' && nListFile != 0)
				{
					if (choose > 0)
						choose--;
				} else if (tmp == 's' && nListFile != 0)
				{
					// 1 for index and 1 for check
					if (choose < nListFile - 1)
						choose++;
				}
				// ENTER
				else if (tmp == 13 && nListFile != 0)
				{
					unsigned int tick = LoadFile(folder, listFile[choose]);
					return tick;
				}
				// ESC
				else if (tmp == 27)
				{
					g_isPause = false;
					return -1;
				}

				theScene_.DrawLoadFile(listFile, choose);
				theScene_.showScene();
			}
		}
	}
	void runSetting()
	{
		int choose = 0;

		theScene_.DrawSetting();
		theScene_.showScene();

		while (true)
		{
			int tmp = _getch();
			// Enter
			if (tmp == 'w')
			{
				if (choose > 0)
					choose--;
			} else if (tmp == 's')
			{
				if (choose < 0)
					choose++;
			} else if (tmp == 13)
			{
				if (choose == 0)
				{
					g_isHard = !g_isHard;
				}
			}
			// ESC
			else if (tmp == 27)
			{
				return;
			}

			theScene_.DrawSetting();
			theScene_.showScene();
		}
	}
	void runCredit()
	{
		theScene_.DrawCredit();
		theScene_.showScene();

		while (true)
		{
			int tmp = _getch();

			// ESC
			if (tmp == 27)
			{
				return;
			}

			theScene_.DrawCredit();
			theScene_.showScene();
		}
	}
	void runSaveGame(unsigned int tick)
	{
		g_isPause = true;
		std::string fileName;

		theScene_.DrawSaveFile(fileName);
		theScene_.showScene();

		while (true)
		{
			if (_kbhit())
			{
				int tmp = _getch();

				// Backspace
				if (tmp == '\b')
				{
					if (fileName.size() > 0)
						fileName.pop_back();
				}
				// ESC -> return to game
				else if (tmp == 27)
				{
					return;
				}
				// Enter -> Save file
				else if (tmp == 13)
				{
					SaveFile(fileName, tick);
					return;
				} else
				{
					if (fileName.length() <= 20)
						fileName.push_back(tmp);
				}

				theScene_.DrawSaveFile(fileName);
				theScene_.showScene();
			}
		}
	}
};