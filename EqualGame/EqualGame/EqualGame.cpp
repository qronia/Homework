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
	// 이미 제거되어있다면 처리 종료
	if (board == nullptr) return;

	// 일반적인 삭제 로직.
	for (int i = 0; i < sizeY; ++i)  delete board[i];
	delete[] board;

	board = nullptr;
}


//보드를 만듭니다.
bool EqualGame::MakeBoard(int sizeX, int sizeY, int typeCount)
{
	if (sizeX < 1 || sizeY < 1 || typeCount < 2 // 인수들이 최소량을 갖는지 검사
		|| ((sizeX*sizeY) & 1))  // 카드의 개수가 홀수가 되면 짝이 안맞기 때문에 거부해야함
		return false;

	this->sizeX = sizeX;
	this->sizeY = sizeY;

	int i, j = sizeX * sizeY / 2, k;
	int *cards = new int[typeCount] {0, };

	// 랜덤 생성기를 초기화하고, 카드의 개수를 랜덤으로 만듭니다.
	// 카드는 짝이 맞아야하기 때문에 2개씩 넣습니다.
	srand(time(NULL));
	while (j--)	cards[rand() % typeCount] += 2;

	// 먼저 보드를 생성하기 전, 이전 보드 내용을 삭제해야합니다.
	// NULLPTR 체크는 DeleteBoard()에서 하므로 여기서 한번더 할 필요는 없습니다.
	DeleteBoard();
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


// 보드를 그립니다. reveal 여부에 따라 가려줍니다.
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


// 지정하는 카드만을 그려냅니다. x와 y는 보드가 그려지는 시작 위치를 지정해야합니다.
void EqualGame::RevealSingleCard(int x, int y, int selectedX, int selectedY)
{
	// 변수가 올바른지 점검합니다.
	if (board == nullptr || selectedX<0 || selectedY<0 || x < 0 || y<0 ) return;

	gotoxy(x + selectedX, y + selectedY);
	std::cout << board[selectedY][selectedX].shape;
}


// 콘솔에서 키를 입력받아 반환합니다.
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



// 게임을 시작합니다. 외부에 알려집니다.
void EqualGame::GameStart()
{
	// 기록해야할 위치들입니다. Point는 단순한 x와 y값만을 가집니다.
	Point boardPos;				// 보드가 그려지는 시작 위치입니다.
	Point cursorPos{ 0,0 };		// 커서의 현재 위치입니다.
	Point selectedPos{ -1,-1 }; // 선택한 대상의 위치입니다. 어떤것도 선택되지 않았다면 -1 값을 가집니다.

	int remainPair;				// 현재 남아있는 카드의 쌍입니다. 이것이 0일때 게임이 종료됩니다.

	// 보드를 생성하고, 카드의 갯수를 셉니다.
	// 보드 생성 실패시, 게임을 실행시키지 않습니다.
	//if(!MakeBoard(5, 4, 8)) return;

	std::cout << "가로의 길이를 입력하세요:";
	std::cin >> sizeX;
	std::cout << "세로의 길이를 입력하세요:";
	std::cin >> sizeY;

	if (!MakeBoard(sizeX, sizeY, 8))return;
	

	remainPair = (sizeX * sizeY) / 2;

	// 보드의 위치 하드코딩.
	boardPos.x = 5;
	boardPos.y = 5;

	// 커서를 선택형으로 만듭니다. Windows Console API이므로,
	// 더 알아보고 싶다면 이쪽을 참고하십시오.
	SetConsoleCursor(ConsoleCursor::SELECT);

	// 카드쌍이 0개가 될때까지 동작합니다.
	while (remainPair)
	{ // 요약하면 보드를 그리고, 고르고, 맞는지 확인합니다.


		// 보드를 그립니다.
		// RevealSingleCard는 변수가 올바르게 왔는지 검사하고 아니면 처리를 거부하기 때문에
		// 별다른 조건문을 추가할 필요가 없습니다.
		PrintBoard(boardPos.x, boardPos.y);
		RevealSingleCard(boardPos.x, boardPos.y, selectedPos.x, selectedPos.y);

		// 모두 그린 후, 커서가 있어야할 위치로 위치시킵니다.
		gotoxy(boardPos.x + cursorPos.x, boardPos.y + cursorPos.y);

		switch (InputKey())
		{
		// 커서의 이동
		case Input::UP:		 if (cursorPos.y > 0)	    --cursorPos.y;	break;
		case Input::DOWN:	 if (cursorPos.y < sizeY-1) ++cursorPos.y;	break;
		case Input::LEFT:	 if (cursorPos.x > 0)	    --cursorPos.x;	break;
		case Input::RIGHT:	 if (cursorPos.x < sizeX-1) ++cursorPos.x;	break;

		// 선택시의 행동
		case Input::CONFIRM: 			
			// 같은 것을 선택하려 하거나 없는 것을 선택하려고 한다면 거부합니다.
			if (  board[cursorPos.y][cursorPos.x].isDeleted || 
				((selectedPos.x == cursorPos.x) && (selectedPos.y == cursorPos.y)) ) 
				break;


			// 만일 아무것도 선택한 상태가 아니었다면
			if (selectedPos.x == -1) {
				// 선택한 대상의 위치를 저장합니다.
				selectedPos.x = cursorPos.x;
				selectedPos.y = cursorPos.y;
				break;
			}


			// 선택후 비교할 때 플레이어도 확인할 수 있도록 보여주고 잠시 기다립니다.
			RevealSingleCard(boardPos.x, boardPos.y, cursorPos.x, cursorPos.y);
			Sleep(1500);




			// 같은 것인지 확인하고 같으면 삭제처리 합니다.
			if (board[cursorPos.y][cursorPos.x].shape == board[selectedPos.y][selectedPos.x].shape)
			{
				board[cursorPos.y][cursorPos.x].isDeleted = true;
				board[selectedPos.y][selectedPos.x].isDeleted = true;

				--remainPair;
			}


			selectedPos.x = selectedPos.y = -1; // 다시 선택하지 않았음을 알리기 위해 설정합니다.
			break;


		// 입력 에러.
		default: case Input::NONE: break;
		}

	}

	// 게임이 끝나면 어떤 설정으로 되어있었는지 보여주고 커서를 원래대로 되돌립니다.
	PrintBoard(boardPos.x, boardPos.y, true);
	SetConsoleCursor(ConsoleCursor::NORMAL);
}
