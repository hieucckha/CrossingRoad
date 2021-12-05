#pragma once
#include <Windows.h>
#include <iostream>

#define Color_Black				0x0
#define Color_Blue				0x1
#define Color_Green				0x2
#define Color_Aqua				0x3
#define Color_Red				0x4
#define Color_Purple			0x5 
#define Color_Yellow			0x6
#define Color_White				0x7
#define Color_Gray				0x8
#define Color_Light_Blue		0x9 
#define Color_Light_Green		0xA
#define Color_Light_Aqua		0xB
#define Color_Light_Red			0xC
#define Color_Light_Purple		0xD
#define Color_Light_Yellow		0xE
#define Color_Bright_White		0xF

// 0xAB A is background, B is Color of text
#define _COLOR(MyBackGround, MyText) ((MyBackGround << 4) | MyText)

void FixConsoleWindow();

void GotoXY(SHORT x, SHORT y);

void SetTextColor(SHORT color);

// https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns
//
void GetWindowBufferSize(SHORT& row, SHORT& col);

// https://stackoverflow.com/questions/18028808/remove-blinking-underscore-on-console-cmd-prompt
//
void ShowConsoleCursor(bool showFlag);

// https://stackoverflow.com/questions/34842526/update-console-without-flickering-c
//
void ClearConsoleScreen();

void ResizeWindow();

void setConsoleFontSize();

