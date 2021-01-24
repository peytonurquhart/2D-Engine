#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <math.h>

#define CIRCLE_SIDES 360

#define PI 3.1415926

class Texture;

class Circle
{
public:
	Circle() { return; }

	Circle(float r, float xPos = 0, float yPos = 0);

	void Init(float r, float xPos = 0, float yPos = 0);

	void getMidpoint(float mid[2]);

	float getX();

	float getY();

	float getRadius();

	void Draw();

	void Translate(float xAmount = 0, float yAmount = 0);

	void TranslateToOrigin();

	void Swing(float theta);

private:
	float radius;

	float midpoint[2]; //[0] is x, [1] is y
};