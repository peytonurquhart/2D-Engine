#pragma once

#include "Init.h"

class Tests
{
public:
	Tests() { return; }

	void BatchTest();

	void TranslateCursorPos(float pos[2], float height, float width)
	{
		float xpix = width - (width * 0.5f);
		float ypix = height - (height * 0.5f);

		pos[0] = (pos[0] - xpix) / xpix;
		pos[1] = (pos[1] - ypix) / ypix * -1;

	}

};