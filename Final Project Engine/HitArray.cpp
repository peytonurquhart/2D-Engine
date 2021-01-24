#include "Init.h"

/* 16 */

HitArray16::HitArray16(float boxSize, bool newMap[4][4]) 
{
	float bitWidth = boxSize / 4;

	isGenereated = false;

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			map[j][i] = newMap[j][i];

			if (newMap[j][i])
			{
				matrix[j][i].Init(boxSize / 4);
			}
		}
	}

	/* this index is allocated no matter what because it needs to be used to calculate the midpoint */
	if(!matrix[2][3].getIsAlloced())
		matrix[2][3].Init(boxSize / 4);


	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if(newMap[j][i])
			matrix[j][i].Translate(i * bitWidth * SQ_ASPECT_RATIO, j * bitWidth * -1);


			/* The ends of the array must get allocated no matter what because they are used to calculate midpoint*/
			if(j == 2 && i == 3 && !newMap[2][3])
			matrix[j][i].Translate(i * bitWidth * SQ_ASPECT_RATIO, j * bitWidth * -1);
			
		}
	}




	isGenereated = true;

}

void HitArray16::Init(float boxSize, bool newMap[4][4])
{
	float bitWidth = boxSize / 4;

	isGenereated = false;

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			map[j][i] = newMap[j][i];

			if (newMap[j][i])
			{
				matrix[j][i].Init(boxSize / 4);
			}
		}
	}

	/* this index is allocated no matter what because it needs to be used to calculate the midpoint */
	if (!matrix[2][3].getIsAlloced())
		matrix[2][3].Init(boxSize / 4);


	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (newMap[j][i])
				matrix[j][i].Translate(i * bitWidth * SQ_ASPECT_RATIO, j * bitWidth * -1);


			/* The ends of the array must get allocated no matter what because they are used to calculate midpoint*/
			if (j == 2 && i == 3 && !newMap[2][3])
				matrix[j][i].Translate(i * bitWidth * SQ_ASPECT_RATIO, j * bitWidth * -1);

		}
	}




	isGenereated = true;
}


void HitArray16::DrawMap()
{
	if (isGenereated)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				if (map[j][i])
				{
					matrix[j][i].Bind();
					matrix[j][i].BufferVertex();
					matrix[j][i].Draw();
					matrix[j][i].Unbind();
				}
			}
		}
	}
	else
	{
		cout << "Cant print out hitboxes which are not generated yet" << endl;
	}
}

bool HitArray16::isOverlap(HitArray16 &checkArray)
{
	Hitbox *temp;

	if (isGenereated && checkArray.getIsGenerated())
	{
		for (int k = 0; k < 4; k++)
		{

			for (int u = 0; u < 4; u++)
			{
				if (checkArray.indexMap(k, u) == true)
				{


			/*inner*/
			for (int j = 0; j < 4; j++)
			{
				for (int i = 0; i < 4; i++)
				{
					if (map[j][i] == true)
					{
						temp = checkArray.indexMatrix(k, u);
						if (matrix[j][i].isOverlap(*temp, true))
						{
							return true;
						}
				   	}
				}
			}
				/* */


				}
			}
		}
	}
	else
	{
		cout << "Cannot test for hits on an unallocated HitArray16 object" << endl;
	}

	return false;
}



bool HitArray16::isOverlap(Hitbox &checkBox)
{
	if (isGenereated)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				if (map[j][i] == true)
				{
					if (matrix[j][i].isOverlap(checkBox, true))
					{
						return true;
					}
				}
			}
		}
	}
	else
	{
		cout << "Cannot test for hits on an unallocated HitArray16 object" << endl;
	}

	return false;
}



void HitArray16::Translate(float xAmount, float yAmount)
{
	if (isGenereated)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				if (map[j][i] == true)
				{
					matrix[j][i].Translate(xAmount, yAmount);
				}
			}
		}

		/*if the calculating box was not translated it needs to be*/
		if(map[2][3] == false)
		matrix[2][3].Translate(xAmount, yAmount);

	}
}

void HitArray16::Swing(float theta)
{
	if (isGenereated)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				if (map[j][i] == true)
				{
					matrix[j][i].Swing(theta);
				}
			}
		}

		/*if the calculating box was not swung it needs to be*/
		if (map[2][3] == false)
			matrix[2][3].Swing(theta);

	}
}

void HitArray16::Rotate(float theta)
{
	if (isGenereated)
	{
		float mids[2];
		CalcHitArrayMidpoint(mids);

		float xTranslation = mids[0] * -1;
		float yTranslation = mids[1] * -1;

		Translate(xTranslation, yTranslation);

		Swing(theta);

		Translate(xTranslation * -1, yTranslation * -1);
	}
}

void HitArray16::FreeSwing(float theta)
{
	if (isGenereated)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				if (map[j][i] == true)
				{
					matrix[j][i].FreeSwing(theta);
				}
			}
		}

		/*if the calculating box was not swung it needs to be*/
		if (map[2][3] == false)
			matrix[2][3].FreeSwing(theta);

	}
}

void HitArray16::FreeRotate(float theta)
{
	if (isGenereated)
	{
		float mids[2];
		CalcHitArrayMidpoint(mids);

		float xTranslation = mids[0] * -1;
		float yTranslation = mids[1] * -1;

		Translate(xTranslation, yTranslation);

		FreeSwing(theta);

		Translate(xTranslation * -1, yTranslation * -1);
	}
}



void HitArray16::CalcHitArrayMidpoint(float mids[2])
{
	if (isGenereated)
	{
		float *mTemp = nullptr;

		mTemp = matrix[2][3].getMatrix();

		mids[0] = mTemp[0];
		mids[1] = mTemp[1];

	}
}

void HitArray16::TranslateToOrigin()
{
	if (isGenereated)
	{
		float mids[2];
		CalcHitArrayMidpoint(mids);

		float xTranslation = mids[0] * -1;
		float yTranslation = mids[1] * -1;

		Translate(xTranslation, yTranslation);
	}
}

void HitArray16::Attach(Shape &s)
{
	s.TranslateToOrigin();
	this->TranslateToOrigin();
}
