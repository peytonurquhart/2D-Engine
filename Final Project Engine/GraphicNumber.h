#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <math.h>


class graphicNumber
{
public:
	graphicNumber();

	/*Initializes a number of size*/
	void init(float size);

	/*Inserts int n to the number to be ready for display*/
	void insert(int n, int digits);

	/*returns true if number is empty (no number has been pushed)*/
	bool isEmptyNum();

	/*draws the number by drawing every square in its map*/
	void Draw();

	/*clears the bool map*/
	void clearMap();

	/*translates the number x y*/
	void transLate(float x, float y);

	/*incriment the number by 1, if > 9 n = 0*/
	bool incr();

	/* returns a pointer to the square at a given index*/
	Hitbox * getSquareAtIndex(int i, int j);

	/*returns the midpoint of the number map*/
	void midNum(float mids[2]);

protected:

	bool isEmpty;

	int number;
	int numDigits;
	float width;
	float bitWidth;

	int numBits;
	Hitbox squares[8][8];

	bool map[8][8];
};
