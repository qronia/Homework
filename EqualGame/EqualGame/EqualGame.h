#pragma once

class EqualGame final
{
private:
	struct Card
	{
		Card():isDeleted(false) {}

		char shape;
		bool isDeleted;
	};

	void DeleteBoard();
	bool MakeBoard(int sizeX, int sizeY, int typeCount=4);

public:

	EqualGame() = default;
	~EqualGame();
	void PrintBoard(int x, int y, bool reveal=false);
	void GameStart();


private:
	Card **board;

	unsigned int sizeX;
	unsigned int sizeY;
};