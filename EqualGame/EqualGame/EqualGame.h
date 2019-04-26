#pragma once

class EqualGame final
{
private:
	enum Setting {
		BoardX = 10,
		BoardY = 10,
	};

	enum InputKeyCode : unsigned char {
		SPECIAL_TRIGGER = 224,
		UP = 72,
		DOWN = 80,
		LEFT = 75,
		RIGHT = 77,

		ENTER = 13,
		CONFIRM = 'z',

		NONE = 0,
	};

	enum class Input : unsigned char {
		UP,
		DOWN,
		LEFT,
		RIGHT,

		CONFIRM,

		NONE,
	};

private:
	struct Card
	{
		Card():isDeleted(false) {}

		char shape;
		bool isDeleted;
	};

	void DeleteBoard();
	bool MakeBoard(int sizeX, int sizeY, int typeCount=4);
	
	EqualGame::Input InputKey();

public:

	EqualGame() = default;
	~EqualGame();
	void PrintBoard(int x, int y, bool reveal=false);
	void RevealSingleCard(int x, int y, int selectedX, int selectedY);
	void GameStart();


private:
	Card **board;

	unsigned int sizeX;
	unsigned int sizeY;
};