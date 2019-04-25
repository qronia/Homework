// ConsoleApplication3.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>

#include "NameCard.h"

int main()
{
	NameCard c("이름", 
		{ "010-0000-0000", "010-1111-1111", "010-1221-1311" }, 
		{"화성시", "안산시"},
		NameCard::Position::Employee
	);

	c.Print();
	getchar();
}