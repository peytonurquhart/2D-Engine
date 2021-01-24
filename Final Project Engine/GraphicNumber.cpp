#include "Init.h"

graphicNumber::graphicNumber()
{
	this->number = 0;
	this->numDigits = 0;
	this->width = 0;
	this->bitWidth = 0;
	this->isEmpty = true;
}

Hitbox * graphicNumber::getSquareAtIndex(int i, int j)
{
	return &squares[i][j];
}


void graphicNumber::init(float size)
{
	this->number = 0;
	this->numDigits = 0;
	this->width = size;
	this->bitWidth = (size / 8);
	this->isEmpty = true;


	int i = 0, j = 0;

	for (j = 0; j < 8; j++)
	{
		for (i = 0; i < 8; i++)
		{
			squares[j][i].Init(bitWidth);
		}
	}

	for (j = 0; j < 8; j++)
	{
		for (i = 0; i < 8; i++)
		{
			squares[j][i].Translate(i * bitWidth * SQ_ASPECT_RATIO, j * bitWidth * -1);
			map[j][i] = false;
		}
	}

}

void graphicNumber::clearMap()
{
	int i = 0, j = 0;

	for (j = 0; j < 8; j++)
	{
		for (i = 0; i < 8; i++)
		{
			map[j][i] = false;
		}
	}

	this->isEmpty = true;
}


void graphicNumber::Draw()
{
	int i = 0, j = 0;

	if (this->isEmptyNum() != true)
	{
		for (j = 0; j < 8; j++)
		{
			for (i = 0; i < 8; i++)
			{
				if (map[j][i] == true)
				{

					squares[j][i].Bind();
					squares[j][i].BufferVertex();
					squares[j][i].Draw();
					squares[j][i].Unbind();

				}
			}
		}

	}
}

bool graphicNumber::isEmptyNum()
{
	return this->isEmpty;
}


void graphicNumber::transLate(float x, float y)
{
	int i = 0, j = 0;

	for (j = 0; j < 8; j++)
	{
		for (i = 0; i < 8; i++)
		{
			squares[j][i].Translate(x, y); //this updates the frame for some reason to do with glbuffersubdata
		}
	}
}


void graphicNumber::midNum(float mids[2])
{
	squares[4][4].CalcMidPoint(mids);
}


bool graphicNumber::incr()
{
	if (number > 9)
	{
		number = 0; //guard code
	}

	if (number == 9)
	{
		number = 0;
	}
	else
	{
		number += 1;
	}

	insert(number, 1);

	if (number == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void graphicNumber::insert(int n, int digits) //ROWS , COLS
{
	if (n > -1 && n < 10)
	{
		if (isEmptyNum() == false)
		{
			clearMap();
		}

		number = n;

		this->isEmpty = false;

		switch (n)
		{
		case 0:

			map[1][0] = true;
			map[2][0] = true;
			map[3][0] = true;
			map[4][0] = true;
			map[5][0] = true;
			map[6][0] = true;


			map[0][1] = true;
			map[0][2] = true;
			map[0][3] = true;
			map[0][4] = true;
			map[0][5] = true;
			map[0][6] = true;


			map[1][7] = true;
			map[2][7] = true;
			map[3][7] = true;
			map[4][7] = true;
			map[5][7] = true;
			map[6][7] = true;

			map[7][6] = true;
			map[7][5] = true;
			map[7][4] = true;
			map[7][3] = true;
			map[7][2] = true;
			map[7][1] = true;


			return;
		case 1:
			map[0][5] = true;
			map[1][5] = true;
			map[2][5] = true;
			map[3][5] = true;
			map[4][5] = true;
			map[5][5] = true;
			map[6][5] = true;
			map[7][5] = true;

			map[0][4] = true;
			return;
		case 2:

			map[1][0] = true;

			map[0][1] = true;
			map[0][2] = true;
			map[0][3] = true;
			map[0][4] = true;
			map[0][5] = true;
			map[0][6] = true;

			map[1][7] = true;
			map[2][7] = true;
			map[3][7] = true;

			map[4][1] = true;
			map[4][2] = true;
			map[4][3] = true;
			map[4][4] = true;
			map[4][5] = true;
			map[4][6] = true;

			map[5][0] = true;
			map[6][0] = true;


			map[7][1] = true;
			map[7][2] = true;
			map[7][3] = true;
			map[7][4] = true;
			map[7][5] = true;
			map[7][6] = true;
			map[7][7] = true;

			return;
		case 3:

			map[1][0] = true;
			map[0][1] = true;
			map[0][2] = true;
			map[0][3] = true;
			map[0][4] = true;
			map[0][5] = true;
			map[0][6] = true;

			map[1][7] = true;
			map[2][7] = true;

			map[3][3] = true;
			map[3][4] = true;
			map[3][5] = true;
			map[3][6] = true;

			map[4][7] = true;
			map[5][7] = true;
			map[6][7] = true;

			map[6][0] = true;
			map[7][1] = true;
			map[7][2] = true;
			map[7][3] = true;
			map[7][4] = true;
			map[7][5] = true;
			map[7][6] = true;

			return;
		case 4:
			map[0][0] = true;
			map[1][0] = true;
			map[2][0] = true;
			map[3][0] = true;

			map[0][7] = true;
			map[1][7] = true;
			map[2][7] = true;
			map[3][7] = true;

			map[3][1] = true;
			map[3][2] = true;
			map[3][3] = true;
			map[3][4] = true;
			map[3][5] = true;
			map[3][6] = true;

			map[4][7] = true;
			map[5][7] = true;
			map[6][7] = true;
			map[7][7] = true;

			return;
		case 5:

			map[0][1] = true;
			map[0][2] = true;
			map[0][3] = true;
			map[0][4] = true;
			map[0][5] = true;
			map[0][6] = true;
			map[0][7] = true;

			map[1][0] = true;
			map[2][0] = true;

			map[3][1] = true;
			map[3][2] = true;
			map[3][3] = true;
			map[3][4] = true;
			map[3][5] = true;
			map[3][6] = true;

			map[4][7] = true;
			map[5][7] = true;
			map[6][7] = true;

			map[7][6] = true;
			map[7][5] = true;
			map[7][4] = true;
			map[7][3] = true;
			map[7][2] = true;
			map[7][1] = true;
			map[7][0] = true;

			return;
		case 6:
			map[0][1] = true;
			map[0][2] = true;
			map[0][3] = true;
			map[0][4] = true;
			map[0][5] = true;
			map[0][6] = true;

			map[1][7] = true;

			map[1][0] = true;
			map[2][0] = true;
			map[3][0] = true;
			map[4][0] = true;
			map[5][0] = true;
			map[6][0] = true;


			map[4][1] = true;
			map[4][2] = true;
			map[4][3] = true;
			map[4][4] = true;
			map[4][5] = true;
			map[4][6] = true;

			map[5][7] = true;
			map[6][7] = true;

			map[7][6] = true;
			map[7][5] = true;
			map[7][4] = true;
			map[7][3] = true;
			map[7][2] = true;
			map[7][1] = true;

			return;
		case 7:
			map[0][1] = true;
			map[0][2] = true;
			map[0][3] = true;
			map[0][4] = true;
			map[0][5] = true;
			map[0][6] = true;

			map[1][0] = true;

			map[1][7] = true;
			map[2][6] = true;
			map[3][5] = true;
			map[4][4] = true;
			map[5][3] = true;
			map[6][2] = true;
			map[7][1] = true;
			return;
		case 8:
			map[0][1] = true;
			map[0][2] = true;
			map[0][3] = true;
			map[0][4] = true;
			map[0][5] = true;
			map[0][6] = true;

			map[1][0] = true;
			map[2][0] = true;

			map[1][7] = true;
			map[2][7] = true;

			map[3][1] = true;
			map[3][2] = true;
			map[3][3] = true;
			map[3][4] = true;
			map[3][5] = true;
			map[3][6] = true;

			map[4][0] = true;
			map[5][0] = true;
			map[6][0] = true;

			map[4][7] = true;
			map[5][7] = true;
			map[6][7] = true;

			map[7][1] = true;
			map[7][2] = true;
			map[7][3] = true;
			map[7][4] = true;
			map[7][5] = true;
			map[7][6] = true;

			return;
		case 9:
			map[0][1] = true;
			map[0][2] = true;
			map[0][3] = true;
			map[0][4] = true;
			map[0][5] = true;
			map[0][6] = true;

			map[1][0] = true;
			map[2][0] = true;

			map[1][7] = true;
			map[2][7] = true;

			map[3][1] = true;
			map[3][2] = true;
			map[3][3] = true;
			map[3][4] = true;
			map[3][5] = true;
			map[3][6] = true;
			map[3][7] = true;

			map[6][0] = true;

			map[4][7] = true;
			map[5][7] = true;
			map[6][7] = true;

			map[7][1] = true;
			map[7][2] = true;
			map[7][3] = true;
			map[7][4] = true;
			map[7][5] = true;
			map[7][6] = true;
			return;
		}

	}

	return;
}