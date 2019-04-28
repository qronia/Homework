#include "EqualGame.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

#include <Windows.h>
#include "consoleinput.h"

#define getch() _getch()

#pragma warning(disable:4018)
#pragma warning(disable:4244)

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


//���带 ����ϴ�.
bool EqualGame::MakeBoard(int sizeX, int sizeY, int typeCount)
{
	if (sizeX < 1 || sizeY < 1 || typeCount < 2 // �μ����� �ּҷ��� ������ �˻�
		|| ((sizeX*sizeY) & 1))  // ī���� ������ Ȧ���� �Ǹ� ¦�� �ȸ±� ������ �ź��ؾ���
		return false;

	this->sizeX = sizeX;
	this->sizeY = sizeY;

	int i, j = sizeX * sizeY / 2, k;
	int *cards = new int[typeCount] {0, };

	// ���� �����⸦ �ʱ�ȭ�ϰ�, ī���� ������ �������� ����ϴ�.
	// ī��� ¦�� �¾ƾ��ϱ� ������ 2���� �ֽ��ϴ�.
	srand(time(NULL));
	while (j--)	cards[rand() % typeCount] += 2;

	// ���� ���带 �����ϱ� ��, ���� ���� ������ �����ؾ��մϴ�.
	// NULLPTR üũ�� DeleteBoard()���� �ϹǷ� ���⼭ �ѹ��� �� �ʿ�� �����ϴ�.
	DeleteBoard();
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
					--cards[k];
					break;
				}
			}

			board[i][j].shape = 'A' + k;
			board[i][j].isDeleted = false;
		}
	}

	return true;
}


// ���带 �׸��ϴ�. reveal ���ο� ���� �����ݴϴ�.
void EqualGame::PrintBoard(int x, int y, bool reveal)
{
	if (board == nullptr) return;

	int i, j;
	for (i = 0; i < sizeY; ++i)
	{
		gotoxy(x, y+i);
		if (!reveal) {
			for (j = 0; j < sizeX; ++j)
				std::cout << (board[i][j].isDeleted ? ' ' : '#');
		}
		else {
			for (j = 0; j < sizeX; ++j)
				std::cout << board[i][j].shape;
		}
	}

	std::cout.flush();
}


// �����ϴ� ī�常�� �׷����ϴ�. x�� y�� ���尡 �׷����� ���� ��ġ�� �����ؾ��մϴ�.
void EqualGame::RevealSingleCard(int x, int y, int selectedX, int selectedY)
{
	// ������ �ùٸ��� �����մϴ�.
	if (board == nullptr || selectedX<0 || selectedY<0 || x < 0 || y<0 ) return;

	gotoxy(x + selectedX, y + selectedY);
	std::cout << board[selectedY][selectedX].shape;
}


// �ֿܼ��� Ű�� �Է¹޾� ��ȯ�մϴ�.
EqualGame::Input EqualGame::InputKey()
{
	switch (getch())
	{
	case InputKeyCode::SPECIAL_TRIGGER:
		switch (getch())
		{
		case InputKeyCode::UP: return Input::UP;
		case InputKeyCode::DOWN: return Input::DOWN;
		case InputKeyCode::LEFT: return Input::LEFT;
		case InputKeyCode::RIGHT: return Input::RIGHT;

		default: return Input::NONE;
		}
		break;

	case InputKeyCode::CONFIRM:
	case InputKeyCode::ENTER:
		return Input::CONFIRM;

	default: return Input::NONE;
	}
}



// ������ �����մϴ�. �ܺο� �˷����ϴ�.
void EqualGame::GameStart()
{
	// ����ؾ��� ��ġ���Դϴ�. Point�� �ܼ��� x�� y������ �����ϴ�.
	Point boardPos;				// ���尡 �׷����� ���� ��ġ�Դϴ�.
	Point cursorPos{ 0,0 };		// Ŀ���� ���� ��ġ�Դϴ�.
	Point selectedPos{ -1,-1 }; // ������ ����� ��ġ�Դϴ�. ��͵� ���õ��� �ʾҴٸ� -1 ���� �����ϴ�.

	int remainPair;				// ���� �����ִ� ī���� ���Դϴ�. �̰��� 0�϶� ������ ����˴ϴ�.

	// ���带 �����ϰ�, ī���� ������ ���ϴ�.
	// ���� ���� ���н�, ������ �����Ű�� �ʽ��ϴ�.
	//if(!MakeBoard(5, 4, 8)) return;

	std::cout << "������ ���̸� �Է��ϼ���:";
	std::cin >> sizeX;
	std::cout << "������ ���̸� �Է��ϼ���:";
	std::cin >> sizeY;

	if (!MakeBoard(sizeX, sizeY, 8))return;
	

	remainPair = (sizeX * sizeY) / 2;

	// ������ ��ġ �ϵ��ڵ�.
	boardPos.x = 5;
	boardPos.y = 5;

	// Ŀ���� ���������� ����ϴ�. Windows Console API�̹Ƿ�,
	// �� �˾ƺ��� �ʹٸ� ������ �����Ͻʽÿ�.
	SetConsoleCursor(ConsoleCursor::SELECT);

	// ī����� 0���� �ɶ����� �����մϴ�.
	while (remainPair)
	{ // ����ϸ� ���带 �׸���, ����, �´��� Ȯ���մϴ�.


		// ���带 �׸��ϴ�.
		// RevealSingleCard�� ������ �ùٸ��� �Դ��� �˻��ϰ� �ƴϸ� ó���� �ź��ϱ� ������
		// ���ٸ� ���ǹ��� �߰��� �ʿ䰡 �����ϴ�.
		PrintBoard(boardPos.x, boardPos.y);
		RevealSingleCard(boardPos.x, boardPos.y, selectedPos.x, selectedPos.y);

		// ��� �׸� ��, Ŀ���� �־���� ��ġ�� ��ġ��ŵ�ϴ�.
		gotoxy(boardPos.x + cursorPos.x, boardPos.y + cursorPos.y);

		switch (InputKey())
		{
		// Ŀ���� �̵�
		case Input::UP:		 if (cursorPos.y > 0)	    --cursorPos.y;	break;
		case Input::DOWN:	 if (cursorPos.y < sizeY-1) ++cursorPos.y;	break;
		case Input::LEFT:	 if (cursorPos.x > 0)	    --cursorPos.x;	break;
		case Input::RIGHT:	 if (cursorPos.x < sizeX-1) ++cursorPos.x;	break;

		// ���ý��� �ൿ
		case Input::CONFIRM: 			
			// ���� ���� �����Ϸ� �ϰų� ���� ���� �����Ϸ��� �Ѵٸ� �ź��մϴ�.
			if (  board[cursorPos.y][cursorPos.x].isDeleted || 
				((selectedPos.x == cursorPos.x) && (selectedPos.y == cursorPos.y)) ) 
				break;


			// ���� �ƹ��͵� ������ ���°� �ƴϾ��ٸ�
			if (selectedPos.x == -1) {
				// ������ ����� ��ġ�� �����մϴ�.
				selectedPos.x = cursorPos.x;
				selectedPos.y = cursorPos.y;
				break;
			}


			// ������ ���� �� �÷��̾ Ȯ���� �� �ֵ��� �����ְ� ��� ��ٸ��ϴ�.
			RevealSingleCard(boardPos.x, boardPos.y, cursorPos.x, cursorPos.y);
			Sleep(1500);




			// ���� ������ Ȯ���ϰ� ������ ����ó�� �մϴ�.
			if (board[cursorPos.y][cursorPos.x].shape == board[selectedPos.y][selectedPos.x].shape)
			{
				board[cursorPos.y][cursorPos.x].isDeleted = true;
				board[selectedPos.y][selectedPos.x].isDeleted = true;

				--remainPair;
			}


			selectedPos.x = selectedPos.y = -1; // �ٽ� �������� �ʾ����� �˸��� ���� �����մϴ�.
			break;


		// �Է� ����.
		default: case Input::NONE: break;
		}

	}

	// ������ ������ � �������� �Ǿ��־����� �����ְ� Ŀ���� ������� �ǵ����ϴ�.
	PrintBoard(boardPos.x, boardPos.y, true);
	SetConsoleCursor(ConsoleCursor::NORMAL);
}
