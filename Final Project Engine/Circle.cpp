#include "Init.h"

Circle::Circle(float r, float xPos, float yPos)
{
	this->radius = r;
	this->midpoint[0] = xPos;
	this->midpoint[1] = yPos;
}

void Circle::Init(float r, float xPos, float yPos)
{
	this->radius = r;
	this->midpoint[0] = xPos;
	this->midpoint[1] = yPos;
}

void Circle::getMidpoint(float mid[2])
{
	mid[0] = this->midpoint[0];
	mid[1] = this->midpoint[1];
}

float Circle::getX()
{
	return this->midpoint[0];
}

float Circle::getY()
{
	return this->midpoint[1];
}

float Circle::getRadius()
{
	return this->radius;
}

void Circle::Draw()
{
	glBegin(GL_POLYGON);

	for (int deg = 0; deg < CIRCLE_SIDES; deg++)
	{
		float radians = deg * PI / 180;
		glVertex2f((cos(radians)*this->radius + midpoint[0]) * SQ_ASPECT_RATIO, sin(radians)*this->radius + midpoint[1]);

	}
	glEnd();
}

/*
tx = xcos * 0.5 + 0.5;
ty = ysin * 0.5 + 0.5;
*/

void Circle::Translate(float xAmount, float yAmount)
{
	/* why do we have to use the reciprocal when we translate? is it build in to the gl functions*/

	midpoint[0] += xAmount / SQ_ASPECT_RATIO; //Modifies x pos
	midpoint[1] += yAmount; //Modifies y pos
}

void Circle::TranslateToOrigin()
{
	float mids[2];
	getMidpoint(mids);

	float xTranslation = mids[0] * -1;
	float yTranslation = mids[1] * -1;

	Translate(xTranslation, yTranslation);
}

void Circle::Swing(float theta)
{
	float tempX, tempY;
	tempX = midpoint[0] / SQ_ASPECT_RATIO; //Scale x axis down
	tempY = midpoint[1] / SQ_ASPECT_RATIO; //Scale y axis down

	midpoint[0] = tempX * cos(theta) - tempY * sin(theta);
	midpoint[1] = tempY * cos(theta) + tempX * sin(theta);
	midpoint[0] *= SQ_ASPECT_RATIO; //Scale x axis up
	midpoint[1] *= SQ_ASPECT_RATIO; //Scale y axis up
}