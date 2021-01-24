#include "Init.h"

Rectangle::Rectangle(float height, float width)
{
	newMatrix = new float[8];
	newInd = new unsigned int[6];
	

	this->height = height;
	this->width = width;
	this->currentRotation = 0.0f;

	float x = width / 2;
	float y = height / 2;

	// Q 3
	newMatrix[0] = x * -1;
	newMatrix[1] = y * -1;

	// Q 4
	newMatrix[2] = x;
	newMatrix[3] = y * -1;

	// Q 1
	newMatrix[4] = x;
	newMatrix[5] = y;

	// Q 2
	newMatrix[6] = x * -1;
	newMatrix[7] = y;

	// Draw pattern
	newInd[0] = 0;
	newInd[1] = 1;
	newInd[2] = 2;

	newInd[3] = 2;
	newInd[4] = 0;
	newInd[5] = 3;


	Shape::Init(4, 2, sizeof(float), 8, newMatrix, true, 6, newInd, 2, GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER);

	delete[]newMatrix;
	delete[]newInd;
	
	Shape::Unbind();
}

void Rectangle::Init(float height, float width)
{
	newMatrix = new float[8];
	newInd = new unsigned int[6];


	this->height = height;
	this->width = width;
	this->currentRotation = 0.0f;

	float x = width / 2;
	float y = height / 2;

	// Q 3
	newMatrix[0] = x * -1;
	newMatrix[1] = y * -1;

	// Q 4
	newMatrix[2] = x;
	newMatrix[3] = y * -1;

	// Q 1
	newMatrix[4] = x;
	newMatrix[5] = y;

	// Q 2
	newMatrix[6] = x * -1;
	newMatrix[7] = y;

	// Draw pattern
	newInd[0] = 0;
	newInd[1] = 1;
	newInd[2] = 2;

	newInd[3] = 2;
	newInd[4] = 0;
	newInd[5] = 3;

		Shape::Init(4, 2, sizeof(float), 8, newMatrix, true, 6, newInd, 2, GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER);
		Shape::Unbind();

	delete[]newMatrix;
	delete[]newInd;

}

void Rectangle::CalcMidPoint(float mids[2])
{
	if (Shape::getIsAlloced())
	{
		float *matrix;
		matrix = Shape::getMatrix();

		mids[0] = ((matrix[0] + matrix[4]) / 2);
		mids[1] = ((matrix[1] + matrix[5]) / 2);
	}
	else
	{
		cout << "Cannot calculate a midpoint of an unallocated shape" << endl;
	}
}

void Rectangle::EditVertex(unsigned int vertex, float xOffset, float yOffset)
{

	if (Shape::getIsAlloced())
	{
		float vNew[2] = { 0.0f };
		float *matrix;
		matrix = Shape::getMatrix();

		switch (vertex)
		{
		case 0: //0,1
			vNew[0] = matrix[0];
			vNew[1] = matrix[1];

			matrix[0] += xOffset;
			matrix[1] += yOffset;
			break;
		case 1: //2,3
			vNew[0] = matrix[2];
			vNew[1] = matrix[3];

			matrix[2] += xOffset;
			matrix[3] += yOffset;
			break;
		case 2: //4,5
			vNew[0] = matrix[4];
			vNew[1] = matrix[5];

			matrix[4] += xOffset;
			matrix[5] += yOffset;
			break;
		case 3: //6,7
			vNew[0] = matrix[6];
			vNew[1] = matrix[7];

			matrix[6] += xOffset;
			matrix[7] += yOffset;
			break;

		}

		vNew[0] += xOffset;
		vNew[1] += yOffset;


	}

	return;
}


void Rectangle::Translate(float xAmount, float yAmount)
{
	EditVertex(0, xAmount, yAmount);
	EditVertex(1, xAmount, yAmount);
	EditVertex(2, xAmount, yAmount);
	EditVertex(3, xAmount, yAmount);
}


void Rectangle::Resize(float factor)
{

	if (Shape::getIsAlloced())
	{
		float *matrix;
		matrix = Shape::getMatrix();

		for (int i = 0; i < 8; i++)
		{
			matrix[i] = (matrix[i] * factor);
		}

		height = height * factor;
		width = width * factor;

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Shape::getNumFloats(), matrix, GL_DYNAMIC_DRAW);
	}
}


void Rectangle::Rotate(float theta)
{
	float mids[2];
	CalcMidPoint(mids);

	float xTranslation = mids[0] * -1;
	float yTranslation = mids[1] * -1;

	Translate(xTranslation, yTranslation);

	Swing(theta);

	Translate(xTranslation * -1, yTranslation * -1);
}



void Rectangle::TranslateToOrigin()
{
	float mids[2];
	CalcMidPoint(mids);

	float xTranslation = mids[0] * -1;
	float yTranslation = mids[1] * -1;

	Translate(xTranslation, yTranslation);
}

void Rectangle::Swing(float theta)
{
	float xA = 0.0f;
	float yA = 0.0f;
	float xB = 0.0f;
	float yB = 0.0f;
	float xC = 0.0f;
	float yC = 0.0f;
	float xD = 0.0f;
	float yD = 0.0f;

	if (Shape::getIsAlloced())
	{

		float *matrix;
		matrix = Shape::getMatrix();


		xA = matrix[0] * SQ_RATIO_RECIP;
		yA = matrix[1];

		xB = matrix[2] * SQ_RATIO_RECIP;
		yB = matrix[3];

		xC = matrix[4] * SQ_RATIO_RECIP;
		yC = matrix[5];

		xD = matrix[6] * SQ_RATIO_RECIP;
		yD = matrix[7];

		matrix[0] = ((xA * cos(theta)) - (yA * sin(theta)));
		matrix[1] = ((yA * cos(theta)) + (xA * sin(theta)));

		matrix[2] = ((xB * cos(theta)) - (yB * sin(theta)));
		matrix[3] = ((yB * cos(theta)) + (xB * sin(theta)));

		matrix[4] = ((xC * cos(theta)) - (yC * sin(theta)));
		matrix[5] = ((yC * cos(theta)) + (xC * sin(theta)));

		matrix[6] = ((xD * cos(theta)) - (yD * sin(theta)));
		matrix[7] = ((yD * cos(theta)) + (xD * sin(theta)));

		matrix[0] = matrix[0] * SQ_ASPECT_RATIO;
		matrix[2] = matrix[2] * SQ_ASPECT_RATIO;
		matrix[4] = matrix[4] * SQ_ASPECT_RATIO;
		matrix[6] = matrix[6] * SQ_ASPECT_RATIO;

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, matrix, GL_DYNAMIC_DRAW);

		currentRotation += theta;
	}
}


void Rectangle::FreeSwing(float theta)
{
	float xA = 0.0f;
	float yA = 0.0f;
	float xB = 0.0f;
	float yB = 0.0f;
	float xC = 0.0f;
	float yC = 0.0f;
	float xD = 0.0f;
	float yD = 0.0f;

	if (Shape::getIsAlloced())
	{

		float *matrix;
		matrix = Shape::getMatrix();


		xA = matrix[0] * SQ_RATIO_RECIP;
		yA = matrix[1];

		xB = matrix[2] * SQ_RATIO_RECIP;
		yB = matrix[3];

		xC = matrix[4] * SQ_RATIO_RECIP;
		yC = matrix[5];

		xD = matrix[6] * SQ_RATIO_RECIP;
		yD = matrix[7];

		matrix[0] = ((xA * cos(theta)) - (yA * sin(theta)));
		matrix[1] = ((yA * cos(theta)) + (xA * sin(theta)));

		matrix[2] = ((xB * cos(theta)) - (yB * sin(theta)));
		matrix[3] = ((yB * cos(theta)) + (xB * sin(theta)));

		matrix[4] = ((xC * cos(theta)) - (yC * sin(theta)));
		matrix[5] = ((yC * cos(theta)) + (xC * sin(theta)));

		matrix[6] = ((xD * cos(theta)) - (yD * sin(theta)));
		matrix[7] = ((yD * cos(theta)) + (xD * sin(theta)));

		matrix[0] = matrix[0] * SQ_ASPECT_RATIO;
		matrix[2] = matrix[2] * SQ_ASPECT_RATIO;
		matrix[4] = matrix[4] * SQ_ASPECT_RATIO;
		matrix[6] = matrix[6] * SQ_ASPECT_RATIO;

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, matrix, GL_DYNAMIC_DRAW);

	}
}

void Rectangle::FreeRotate(float theta)
{
	float mids[2];
	CalcMidPoint(mids);

	float xTranslation = mids[0] * -1;
	float yTranslation = mids[1] * -1;

	Translate(xTranslation, yTranslation);

	FreeSwing(theta);

	Translate(xTranslation * -1, yTranslation * -1);
}

void Rectangle::MoveToOrigin()
{
	float o[2];

	getOrigin(o);

	o[0] = o[0] * -1;
	o[1] = o[1] * -1;

	Translate(o[0], o[1]);
}
