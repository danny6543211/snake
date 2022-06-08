#include<iostream>
#include<conio.h>
#include<windows.h>
#include "snake.h"
#include "global.h"
using namespace std;

// 設置光標位置
void gotoxy(int x, int y) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}

// 隱藏光標
void hide_cursor() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(handle, &CursorInfo);
}