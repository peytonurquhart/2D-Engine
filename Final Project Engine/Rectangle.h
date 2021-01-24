#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <math.h>


class Rectangle : public Shape
{
public:
	Rectangle() { return; }
	
	Rectangle(Rectangle &oldR) : Shape(oldR)
	{
		this->height = oldR.height;
		this->width = oldR.width;
		this->currentRotation = oldR.currentRotation;
		this->newMatrix = nullptr;
		this-> newInd = nullptr;
	}


	Rectangle(float height, float width);

	void Init(float height, float width);

	float getWidth() { return this->width; }
	float getHeight() { return this->height; }
	float getCurrentRotation() { return this->currentRotation; }

	void CalcMidPoint(float mids[2]);

	void EditVertex(unsigned int vertex, float xOffset, float yOffset);

	void Resize(float factor);

	void TranslateToOrigin();

	void Translate(float xAmount, float yAmount);

	void Swing(float theta);

	void Rotate(float theta);

	void FreeSwing(float theta);

	void FreeRotate(float theta);

	void setCurRotation(float theta) { this->currentRotation = theta; }

	void MoveToOrigin();

private:

	float *newMatrix;
	unsigned int *newInd;

	float height;
	float width;

	float currentRotation;
	
};

/* Rectangle Which Suppors a Texture Shader (but does not require one) uses 4x more memory + texture storage slot*/

class RectangleT : public Shape
{
public:
	RectangleT() { return; }

	~RectangleT() { return; }

	RectangleT(const RectangleT &oldRec) : Shape(oldRec)
	{
		this->height = oldRec.height;
		this->width = oldRec.width;
		this->currentRotation = oldRec.currentRotation;
		this->newMatrix = nullptr;
		this->newInd = nullptr;
	}

	RectangleT(float height, float width, float z, bool isBuffered = true);

	void Init(float height, float width, float z, bool isBuffered = true);

	float getWidth() { return this->width; }
	float getHeight() { return this->height; }
	float getCurrentRotation() { return this->currentRotation; }

	void CalcMidPoint(float mids[2]);

	void EditVertex(unsigned int vertex, float xOffset, float yOffset);

	void Resize(float factor);

	void TranslateToOrigin();

	void Translate(float xAmount, float yAmount);

	void Swing(float theta);

	void Rotate(float theta);

	void FreeSwing(float theta);

	void FreeRotate(float theta);

	void setCurRotation(float theta) { this->currentRotation = theta; }

	void Bind();

	void MoveToOrigin();

private:

	float *newMatrix;
	unsigned int *newInd;

	float height;
	float width;

	float currentRotation;
};