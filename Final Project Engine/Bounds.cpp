#include "Init.h"

Bounds::Bounds(float zonePM, bool shouldVerify, float bounceAmt)
{
	for (int i = 0; i < 4; i++)
	{
		bounds[i].Init(zonePM * 2 * 12);
	}

	bounds[0].Translate(0, -1 * zonePM * 6.99);
	bounds[1].Translate(zonePM * 6.995, 0);
	bounds[2].Translate(0, zonePM * 6.99);
	bounds[3].Translate(-1 * zonePM * 6.995, 0);

	this->verify = shouldVerify;
	this->bounceAmt = bounceAmt;

}

void Bounds::Init(float zonePM, bool shouldVerify, float bounceAmt)
{
	for (int i = 0; i < 4; i++)
	{
		bounds[i].Init(zonePM * 2 * 12);
	}

	bounds[0].Translate(0, -1 * zonePM * 6.99);
	bounds[1].Translate(zonePM * 6.995, 0);
	bounds[2].Translate(0, zonePM * 6.99);
	bounds[3].Translate(-1 * zonePM * 6.995, 0);

	this->verify = shouldVerify;
	this->bounceAmt = bounceAmt;
}


Boundlimit Bounds::isInBounds(Hitbox &h)
{
	float mids[2] = { 0.0f };

	for (int i = 0; i < 4; i++)
	{
		if (bounds[i].isOverlap(h, true))
		{
			h.CalcMidPoint(mids);

			switch (i)
			{
			case 0: //lower

				if (verify)
				{

					if (mids[0] < mids[1])
					{
						return Left;
					}
					else if (mids[0] * -1 < mids[1])
					{
						return Right;
					}

				}

				return Lower;

				break;
			case 1: //right

				if (verify)
				{
					if (mids[1] > mids[0])
					{
						return Upper;
					}
					else if (mids[1] * -1 > mids[0])
					{
						return Lower;
					}

				}

				return Right;

				break;
			case 2: //upper

				if (verify)
				{
					if (mids[0] > mids[1])
					{
						return Right;
					}
					else if (mids[1] * -1 > mids[0])
					{
						return Left;
					}

				}

				return Upper;

				break;
			case 3: //left

				if (verify)
				{
					if (mids[1] < mids[0])
					{
						return Lower;
					}
					else if (mids[1] * -1 < mids[0])
					{
						return Upper;
					}

				}

				return Left;

				break;
			}
		}

	}

	return Unbound;
}



Boundlimit Bounds::isInBounds(HitArray16 &hA)
{
	Hitbox *temp;
	Boundlimit lTemp = Unbound;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			/**/
			if (hA.indexMap(i, j) == true)
			{
				temp = hA.indexMatrix(i, j);

				lTemp = isInBounds(*temp);
				
				if (lTemp != Unbound)
				{
					return lTemp;
				}
			}

			/**/
		}
	}

	return Unbound;

}


int Bounds::getQuadrant(float * x, float  * y)
{
	float X = *x, Y = *y;

	if (X >= 0) //1 or 1
	{
		if (X == 0)
		{
			*x += 0.000001;
		}

		if (Y >= 0) //1
		{
			if (Y == 0)
			{
				*y += 0.000001;
			}

			return 1;


		}
		else if (Y < 0)
		{
			return 4;
		}

	}
	else if (X < 0)
	{

		if (Y >= 0)
		{
			if (Y == 0)
			{
				*y += 0.000001;
			}

			return 2;


		}
		else if (Y < 0)
		{
			return 3;
		}
	}

}


void Bounds::Bounce(Boundlimit lim, Hitbox &h, bool isAttached, Shape *s)
{
	switch (lim)
	{
	case Lower:
		h.Translate(0, bounceAmt);

		if (isAttached)
		s->Translate(0, bounceAmt);

		break;
	case Right:
			h.Translate(-1 * bounceAmt, 0);

		if (isAttached)
			s->Translate(-1 * bounceAmt, 0);
		break;
	case Upper:
		h.Translate(0, -1 * bounceAmt);

		if (isAttached)
		s->Translate(0, -1 *bounceAmt);
		break;
	case Left:
		h.Translate(bounceAmt, 0);

		if (isAttached)
			s->Translate(bounceAmt, 0);
		break;
	}
}

void Bounds::Bounce(Boundlimit lim, HitArray16 &h, bool isAttached, Shape *s)
{
	switch (lim)
	{
	case Lower:
		h.Translate(0, bounceAmt);

		if (isAttached)
			s->Translate(0, bounceAmt);

		break;
	case Right:
		h.Translate(-1 * bounceAmt, 0);

		if (isAttached)
			s->Translate(-1 * bounceAmt, 0);
		break;
	case Upper:
		h.Translate(0, -1 * bounceAmt);

		if (isAttached)
			s->Translate(0, -1 * bounceAmt);
		break;
	case Left:
		h.Translate(bounceAmt, 0);

		if (isAttached)
			s->Translate(bounceAmt, 0);
		break;
	}

	return;
}