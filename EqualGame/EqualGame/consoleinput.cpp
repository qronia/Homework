#include "consoleinput.h"
#include <windows.h>

void gotoxy(int x, int y)
{
	COORD coord{ x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetConsoleCursor(ConsoleCursor cc)
{
	CONSOLE_CURSOR_INFO cci{};

	switch (cc)
	{
	case ConsoleCursor::NONE:
		cci.bVisible = false;
		break;
	default:
	case ConsoleCursor::NORMAL:
		cci.bVisible = true;
		cci.dwSize = 20;
		break;
	case ConsoleCursor::SELECT:
		cci.bVisible = true;
		cci.dwSize = 100;
		break;
	}

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}
