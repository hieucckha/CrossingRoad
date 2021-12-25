#pragma once
#pragma warning( disable : 4005  )

#include <Windows.h>
#include <iostream>

#define FG_DEFAULT			0x7
#define FG_BLACK			0x0
#define FG_BLUE				0x1		
#define FG_GREEN			0x2
#define FG_AQUA				0x3
#define FG_RED				0x4
#define FG_PURPLE			0x5 
#define FG_YELLOW			0x6
#define FG_WHITE			0x7
#define FG_GRAY				0x8
#define FG_LIGHT_BLUE		0x9 
#define FG_LIGHT_GREEN		0xA
#define FG_LIGHT_AQUA		0xB
#define FG_LIGHT_RED		0xC
#define FG_LIGHT_PURPLE		0xD
#define FG_LIGHT_YELLOW		0xE
#define FG_BRIGHT_WHITE		0xF

#define BG_DEFAULT			0x00
#define BG_BLACK			0x00
#define BG_BLUE				0x10
#define BG_GREEN			0x20
#define BG_AQUA				0x30
#define BG_RED				0x40
#define BG_PURPLE			0x50
#define BG_YELLOW			0x60
#define BG_WHITE			0x70
#define BG_GRAY				0x80
#define BG_LIGHT_BLUE		0x90
#define BG_LIGHT_GREEN		0xA0
#define BG_LIGHT_AQUA		0xB0
#define BG_LIGHT_RED		0xC0
#define BG_LIGHT_PURPLE		0xD0
#define BG_LIGHT_YELLOW		0xE0
#define BG_BRIGHT_WHITE		0xF0

void FixConsoleWindow();
void GotoXY(SHORT x, SHORT y);
void setConsoleColor(unsigned char color);
void GetWindowBufferSize(int& row, int& col);
void ShowConsoleCursor(bool showFlag);
void ClearConsoleScreen();
bool dir_exists(std::string const& dir_path);

