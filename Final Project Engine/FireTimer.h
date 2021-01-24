#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <math.h>


/* Returns true if the firerate specified should allow for a timer using a MS counter*/
class FireTimer
{

public:
	FireTimer(int rateMs) { this->rate = rateMs; this->last = 0; }

	bool IsGoodFire(int counter)
	{
		if ((counter - last) > rate) 
		{
			last = counter;
			return true;
		}
		else
		{
			return false;
		}
	}

private:
	int rate;
	int last;

};