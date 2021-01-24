#include "Init.h"

Hitbox::Hitbox(float size) 
{
	this->size = size;
	this->half = size / 2;

	Rectangle::Init(size, size);
}

void Hitbox::Init(float size)
{
	this->size = size;
	this->half = size / 2;

	Rectangle::Init(size, size);
}

bool Hitbox::isOverlap(Hitbox &checkBox, bool checkOpposite)
{
	float *m1;
	m1 = this->getMatrix();

	float tpoint[2];
	tpoint[0] = m1[0];
	tpoint[1] = m1[1];
	if (checkBox.isPointInHitbox(tpoint))
	{
		return true;
	}
	tpoint[0] = m1[2];
	tpoint[1] = m1[3];
	if (checkBox.isPointInHitbox(tpoint))
	{
		return true;
	}
	tpoint[0] = m1[4];
	tpoint[1] = m1[5];
	if (checkBox.isPointInHitbox(tpoint))
	{
		return true;
	}
	tpoint[0] = m1[6];
	tpoint[1] = m1[7];
	if (checkBox.isPointInHitbox(tpoint))
	{
		return true;
	}

	if (checkOpposite)
	{
		if (checkBox.isOverlap(*this, false))
		{
			return true;
		}
	}

	return false;
}

bool Hitbox::isPointInHitbox(float point[2])
{
	float o[2];
	getOrigin(o);

	float distancepmy = size * 1;
	distancepmy = (distancepmy - (distancepmy / 1));

	float distancepmx = size * 1 * SQ_ASPECT_RATIO;
	distancepmx = (distancepmx - (distancepmx / 1));

	if ((point[0] >= (o[0] - (size * SQ_ASPECT_RATIO))) && (point[0] < o[0] + distancepmx))
	{
		if ((point[1] >= (o[1] - size)) && point[1] < o[1] + distancepmy)
		{
			return true;
		}
	}

	return false;
}

//bool Hitbox::isPointInHitbox(float point[2])
//{
//	bool xM = false, yM = false;
//
//	float one[2], two[2], three[2];
//	getOrigin(one, 0);
//	getOrigin(two, 1);
//	getOrigin(three, 2);
//
//	if (!(point[0] > one[0] && point[0] < two[0]))
//	{
//		return false;
//	}
//
//	if (point[1] > one[1] && point[1] < three[1])
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//
//}

//float m1[2] = { 0.0f };
//float m2[2] = { 0.0f };
//float zonePM = 0.0f;
//bool xMatch = false, yMatch = false;
//
//zonePM = (getHalf() + checkBox.getHalf()) / 2;
//
//checkPoint(m1);
//checkBox.checkPoint(m2);
//
//float x1 = m1[0];
//float x2 = m2[0];
//
//float y1 = m1[1];
//float y2 = m2[1];
//
//if (x1 > x2)
//{
//	if (x1 - zonePM <= x2)
//	{
//		xMatch = true;
//	}
//}
//else if (x2 > x1)
//{
//	if (x2 - zonePM <= x1)
//	{
//		xMatch = true;
//	}
//}
//else if (x1 == x2)
//{
//	xMatch = true;
//}
//
//if (y1 > y2)
//{
//	if (y1 - zonePM <= y2)
//	{
//		yMatch = true;
//	}
//}
//else if (y2 > y1)
//{
//	if (y2 - zonePM <= y1)
//	{
//		yMatch = true;
//	}
//}
//else if (y1 == y2)
//{
//	yMatch = true;
//}
//
//
//if (xMatch == true && yMatch == true)
//{
//	return true;
//}
//else
//{
//	return false;
//}