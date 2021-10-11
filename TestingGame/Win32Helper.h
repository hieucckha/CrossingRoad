#pragma once
#include <Windows.h>
#include <iostream>

void FixConsoleWindow();

void GotoXY(int x, int y);

void GetWindowSize(int& row, int& col);

void ShowConsoleCursor(bool showFlag);

void ClearConsoleScreen();

