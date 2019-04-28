#include <iostream>
#include "EqualGame.h"

#include "consoleinput.h"

using namespace std;

int main()
{
	EqualGame a;
	a.GameStart();

	
	for (int i = 1; i < 10; ++i)
	{
		gotoxy(i-1, i-1);
		cout << i;
	}

	getchar();
	return 0;
}