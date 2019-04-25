#include "EqualGame.h"

#include <iostream>
#include <cstdlib>
#include <ctime>


EqualGame::~EqualGame() { DeleteBoard(); }
void EqualGame::DeleteBoard()
{
	// �̹� ���ŵǾ��ִٸ� ó�� ����
	if (board == nullptr) return;

	// �Ϲ����� ���� ����.
	for (int i = 0; i < sizeY; ++i)  delete board[i];
	delete[] board;

	board = nullptr;
}

bool EqualGame::MakeBoard(int sizeX, int sizeY, int typeCount)
{
	if ( sizeX < 1 || sizeY < 1 || typeCount < 2 // �μ����� �ּҷ��� ������ �˻�
		|| ((sizeX*sizeY) & 1) )  // ī���� ������ Ȧ���� �Ǹ� ¦�� �ȸ±� ������ �ź��ؾ���
		return false;

	this->sizeX = sizeX;
	this->sizeY = sizeY;

	int i,j=sizeX*sizeY/2,k;
	int *cards = new int[typeCount] {0, };

	// ���� �����⸦ �ʱ�ȭ�ϰ�, ī���� ������ �������� ����ϴ�.
	// ī��� ¦�� �¾ƾ��ϱ� ������ 2���� �ֽ��ϴ�.
	srand(time(NULL));
	while (j--)	cards[ rand()%typeCount] += 2;

	// ���带 �����ϸ鼭 ������ ä��� �ʱ�ȭ�մϴ�.
	board = new Card*[sizeY];
	for (i = 0; i < sizeY; ++i)
	{
		board[i] = new Card[sizeX];
		for (j = 0; j < sizeX; ++j)
		{
			// ������ ä�ﶧ���� �����ϰ� �������� �õ��ϵ�, 
			// ������� ������ ī�尡 ���̻� �������� ������ ��õ��մϴ�.
			// �� ������ ó���� ����� �� ������ �����Ͻʽÿ�.
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