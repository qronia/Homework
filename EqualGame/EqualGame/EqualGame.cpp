#include "EqualGame.h"

#include <iostream>
#include <cstdlib>
#include <ctime>


EqualGame::~EqualGame() { DeleteBoard(); }
void EqualGame::DeleteBoard()
{
	// 이미 제거되어있다면 처리 종료
	if (board == nullptr) return;

	// 일반적인 삭제 로직.
	for (int i = 0; i < sizeY; ++i)  delete board[i];
	delete[] board;

	board = nullptr;
}

bool EqualGame::MakeBoard(int sizeX, int sizeY, int typeCount)
{
	if ( sizeX < 1 || sizeY < 1 || typeCount < 2 // 인수들이 최소량을 갖는지 검사
		|| ((sizeX*sizeY) & 1) )  // 카드의 개수가 홀수가 되면 짝이 안맞기 때문에 거부해야함
		return false;

	this->sizeX = sizeX;
	this->sizeY = sizeY;

	int i,j=sizeX*sizeY/2,k;
	int *cards = new int[typeCount] {0, };

	// 랜덤 생성기를 초기화하고, 카드의 개수를 랜덤으로 만듭니다.
	// 카드는 짝이 맞아야하기 때문에 2개씩 넣습니다.
	srand(time(NULL));
	while (j--)	cards[ rand()%typeCount] += 2;

	// 보드를 생성하면서 내용을 채우고 초기화합니다.
	board = new Card*[sizeY];
	for (i = 0; i < sizeY; ++i)
	{
		board[i] = new Card[sizeX];
		for (j = 0; j < sizeX; ++j)
		{
			// 내용을 채울때에는 랜덤하게 넣으려고 시도하되, 
			// 대상으로 선정된 카드가 더이상 존재하지 않으면 재시도합니다.
			// 이 때문에 처리가 길어질 수 있으니 주의하십시오.
			while (true) {
				k = rand() % typeCount;
				if (cards[k] != 0)
				{
					--k;
					break;
				}
			}

			board[i][j].shape = 'a' + k;
			board[i][j].isDeleted = false;
		}
	}
}

void EqualGame::PrintBoard(int x, int y, bool reveal)
{
	if (board == nullptr) return;

	int i, j;
	for (i = 0; i < sizeY; ++i)
	{
		for (j = 0; j < sizeX; ++j)
			std::cout << (board[i][j].isDeleted ? ' ' : board[i][j].shape) << " ";

		std::cout << "\n";
	}

	std::cout.flush();
}