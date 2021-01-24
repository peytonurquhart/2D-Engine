#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <math.h>

class ScoreBoard
{
public:
	/*initializes a scoreboard of numbers with a maxnumdigits, sizeofnums, spawnpoint and spacing on the screen*/
	ScoreBoard(int numDigits, float sizeNums, float tX, float tY, float numberSpacing);

	/*incriments the board as a whole*/
	void incr();

	/*draws the entire scoreboard in its current state*/
	void Draw();

	/*returns an interger to what the scoreboard saya*/
	long int getRealNum() { return this->realNum; }

private:
	graphicNumber * board;
	long int realNum;
	int numDigits;

	int base;
};
