#include "Init.h"

ScoreBoard::ScoreBoard(int numDigits, float sizeNums, float tX, float tY, float numberSpacing)
{
	board = new graphicNumber[numDigits];

	for (int i = 0; i < numDigits; i++)
	{
		board[i].init(sizeNums);
		board[i].insert(0, 0);
	}

	for (int i = 0; i < numDigits; i++)
	{
		board[i].transLate(tX, tY);
		tX -= numberSpacing;
	}

	this->numDigits = numDigits;
	this->base = 0;


}

void ScoreBoard::incr()
{
	realNum += 1;

	for (int i = 0; i < numDigits; i++)
	{
		if (!board[i].incr())
		{
			if (i + 1 > base)
				this->base = i + 1;

			break;
		}
	}

}

void ScoreBoard::Draw()
{
	for (int i = 0; i < numDigits && i < base; i++)
	{
		board[i].Draw();
	}
}