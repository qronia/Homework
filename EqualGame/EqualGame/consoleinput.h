#pragma once

#include <conio.h>

enum class ConsoleCursor {
	NONE,
	NORMAL,
	SELECT,
};

struct Point {
	int x;
	int y;
};

void gotoxy(int x, int y);
void SetConsoleCursor(ConsoleCursor cc);