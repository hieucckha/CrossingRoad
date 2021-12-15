//#include "Game.h"
//
//Game::Game()
//{
//	level_ = 0;
//	vol = 100;
//}
//
//Game::~Game()
//{
//}
//
//std::vector<Row*>& Game::getRow()
//{
//	return row;
//}
//
//int Game::getLevel() const
//{
//	return level_;
//}
//
///// <summary>
///// Display generated Buffer to the monitor
///// Causion when use outside of SubThread
///// </summary>
//void Game::PrintBuffer()
//{
//	gameScene.PrintBuffer();
//}
//
///// <summary>
///// Display main menu
///// </summary>
//void Game::mainMenu()
//{
//	gameScene.drawMainMenu();
//	gameScene.PrintBuffer();
//}
//
///// <summary>
///// Play music of game
///// </summary>
//void Game::playMusic()
//{
//	DWORD dwVol = ON;
//	waveOutSetVolume(NULL, dwVol);
//
//	PlaySound(TEXT("Music\\music.wav"), NULL, SND_ASYNC | SND_LOOP);
//}
//
//void Game::stopMusic()
//{
//	PlaySound(NULL, NULL, SND_ASYNC);
//}
//
///// <summary>
///// Generate and display ALL elements of the game
///// </summary>
//void Game::drawNormalGame()
//{
//	gameScene.drawScene(level_);
//
//	for (auto x : row)
//		gameScene.drawOneRow(*x);
//
//	gameScene.drawEntity(player_);
//	gameScene.drawManual();
//	gameScene.PrintBuffer();
//}
//
////Remember to pause the game
//void Game::playerDead()
//{
//	gameScene.drawDeadMenu();
//	gameScene.PrintBuffer();
//}
//
//void Game::setPlayerDead()
//{
//	player_.setState(false);
//}
//
//const Player& Game::getPlayer() const
//{
//	return player_;
//}
//
//void Game::levelUp()
//{
//	level_++;
//}
//
//void Game::resetLevel()
//{
//	level_ = 0;
//}
//
//void Game::resetGame()
//{
//	row.clear();
//	updatePosPeople(' ');
//	updateRows();
//	drawNormalGame();
//}
//
//void Game::exitGame(std::thread& thd)
//{
//	ClearConsoleScreen();
//	thd.join();
//}
//
//void Game::startGame()
//{
//	g_isRunning = true;
//	player_.setState(true);
//
//	player_.move(55, 27);
//}
//
//void Game::loadGame()
//{
//	std::deque<std::string> listName;
//	std::deque<int> listLevel;
//
//	//Get data
//	std::fstream input("SaveGame.txt", std::ios::in);
//	std::string name;
//	int lvl;
//	while (input.eof() == false)
//	{
//		input >> lvl;
//		input.ignore(80, ' ');
//		getline(input, name);
//		listName.push_back(name);
//		listLevel.push_back(lvl);
//	}
//	listName.pop_back();
//	listLevel.pop_back();
//	input.close();
//
//	//Update the number of data in the file
//	int n = listName.size();
//	if (n > 10)
//	{
//		for (int i = 0; i < n - 10; i++)
//		{
//			listName.erase(listName.begin());
//			listLevel.erase(listLevel.begin());
//		}
//		n = listName.size();
//		std::fstream output("SaveGame.txt", std::ios::out);
//		for (int i = 0; i < n; i++)
//			output << listLevel[i] << " " << listName[i] << std::endl;
//		output.close();
//	}
//
//	gameScene.drawLoadMenu();
//	for (int i = 0; i < n; i++)
//	{
//		gameScene.setStrToBuffer(38, 11 + i, listName[i]);
//		gameScene.setStrToBuffer(52, 11 + i, "level: " + std::to_string(listLevel[i]));
//	}
//	gameScene.PrintBuffer();
//
//	GotoXY(55, 22); getline(std::cin, name);
//	gameScene.clearPrevBuffer();
//	gameScene.PrintBuffer();
//
//	for (int i = 0; i < n; i++)
//		if (name == listName[i])
//		{
//			level_ = listLevel[i];
//			resetGame();
//			startGame();
//		}
//}
//
//void Game::saveGame()
//{
//	gameScene.drawSaveMenu();
//	gameScene.PrintBuffer();
//
//	std::string name;
//	GotoXY(52, 16); getline(std::cin, name);
//	gameScene.clearPrevBuffer();
//	gameScene.PrintBuffer();
//
//	std::fstream out("SaveGame.txt", std::ios::app);
//	out << level_ << " " << name << std::endl;
//	out.close();
//}
//
//void Game::pauseGame()
//{
//	gameScene.drawPauseMenu();
//	gameScene.PrintBuffer();
//}
//
//void Game::pauseSystem(HANDLE hd)
//{
//	SuspendThread(hd);
//}
//
//void Game::resumeSystem(HANDLE hd)
//{
//	ResumeThread(hd);
//}
//
//void Game::atMainMenu(char input, HANDLE hd)
//{
//	if (input == 'N')
//	{
//		g_isMainMenu = false;
//	}
//	else if (input == 'T')
//	{
//		pauseSystem(hd);
//		loadGame();
//		g_isMainMenu = false;
//		resumeSystem(hd);
//	}
//	else if (input == 'S')
//	{
//		int newVol = 0;
//		pauseSystem(hd);
//		gameScene.drawSettingMenu();
//		gameScene.PrintBuffer();
//
//		GotoXY(81, 21);
//		char settingInput = toupper(_getch());
//		if (settingInput == 'T')
//		{
//			g_isMusic = !g_isMusic;
//			if (g_isMusic)
//				playMusic();
//			else
//				stopMusic();
//		}
//		gameScene.clearPrevBuffer();
//		gameScene.PrintBuffer();
//		resumeSystem(hd);
//	}
//	else if (input == 27)
//	{
//		g_isRunning = false;
//	}
//	gameScene.clearPrevBuffer();
//}
//
//void Game::deadScene(unsigned int deadBy)
//{
//	g_isAnimate = true;
//	if (deadBy == 2)
//	{
//		PlaySound(TEXT("Music\\Bird.wav"), NULL, SND_ASYNC);
//		gameScene.deadByBird();
//	}
//	else if (deadBy == 3)
//	{
//		PlaySound(TEXT("Music\\Dino.wav"), NULL, SND_ASYNC);
//		gameScene.deadByDino();
//	}
//	else
//	{
//		PlaySound(TEXT("Music\\Car.wav"), NULL, SND_ASYNC);
//		gameScene.deadByVehicle();
//	}
//	g_isAnimate = false;
//}
//
//void Game::updatePosPeople(char moveKey)
//{
//	if (moveKey == 'W')
//		player_.Up();
//	else if (moveKey == 'A')
//		player_.Left();
//	else if (moveKey == 'S')
//		player_.Down();
//	else if (moveKey == 'D')
//		player_.Right();
//}
//
//void Game::updateRows()
//{
//	// Initialize
//	if (row.empty())
//	{
//		row.push_back(new Row(7));
//		row.push_back(new Row(12));
//		row.push_back(new Row(17));
//		row.push_back(new Row(22));
//	}
//
//	for (auto& x : row)
//	{
//		x->AtLevel(level_);
//		x->append();
//		x->move();
//	}
//}