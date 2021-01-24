#include "Init.h"


Triangle::Triangle(float a, float b, float c)
{
	this->a = a;
	this->b = b;
	this->c = c;

	currentRotation = 0.0f;

	newMatrix = new float[6];

	newMatrix[0] = (a / 2) * -1;
	newMatrix[1] = 0.0f;

	newMatrix[2] = (a / 2);
	newMatrix[3] = 0.0f;

	float theta = 0.0f;
	theta = acos((pow(b, 2) - pow(a, 2) - pow(c, 2)) / (-2 * a*c));
	newMatrix[4] = c * cos(theta) + newMatrix[0];
	newMatrix[5] = c * sin(theta);

	for (int i = 0; i < 6; i++)
	{
		Round(ROUND_TO_ZERO, &newMatrix[i]);
	}

	Shape::Init(3, 2, sizeof(float), 6, newMatrix, false, 0, nullptr, 2, GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER, GL_ARRAY_BUFFER);

	Shape::Unbind();

	delete[] newMatrix;
	return;
}


void Triangle::Init(float a, float b, float c)
{
	this->a = a;
	this->b = b;
	this->c = c;

	currentRotation = 0.0f;

	newMatrix = new float[6];

	newMatrix[0] = (a / 2) * -1;
	newMatrix[1] = 0.0f;

	newMatrix[2] = (a / 2);
	newMatrix[3] = 0.0f;

	float theta = 0.0f;
	theta = acos((pow(b, 2) - pow(a, 2) - pow(c, 2)) / (-2 * a*c));
	newMatrix[4] = c * cos(theta) + newMatrix[0];
	newMatrix[5] = c * sin(theta);

	for (int i = 0; i < 6; i++)
	{
		Round(ROUND_TO_ZERO, &newMatrix[i]);
	}

	Shape::Init(3, 2, sizeof(float), 6, newMatrix, false, 0, nullptr, 2, GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER, GL_ARRAY_BUFFER);

	Shape::Unbind();

	delete[] newMatrix;
	return;
}



float Triangle::getAngleA()
{
	if (getIsAlloced())
	{
		return acos((pow(b, 2) + pow(c, 2) - pow(a, 2)) / (2 * b * c));
	}
	else
	{
		return 0.0f;
	}
}


float Triangle::getAngleB()
{
	if (getIsAlloced())
	{
		return acos((pow(a, 2) + pow(c, 2) - pow(b, 2)) / (2 * a * c));
	}
	else
	{
		return 0.0f;
	}
}


float Triangle::getAngleC()
{
	if (getIsAlloced())
	{
		return acos((pow(b, 2) + pow(a, 2) - pow(c, 2)) / (2 * b * a));
	}
	else
	{
		return 0.0f;
	}
}


float Triangle::getAngleA_D()
{
	if (getIsAlloced())
	{
		return (acos((pow(b, 2) + pow(c, 2) - pow(a, 2)) / (2 * b * c)))  * (180 / PI);
	}
	else
	{
		return 0.0f;
	}
}


float Triangle::getAngleB_D()
{
	if (getIsAlloced())
	{
		return (acos((pow(a, 2) + pow(c, 2) - pow(b, 2)) / (2 * a * c)))  * (180 / PI);
	}
	else
	{
		return 0.0f;
	}
}


float Triangle::getAngleC_D()
{
	if (getIsAlloced())
	{
		return (acos((pow(b, 2) + pow(a, 2) - pow(c, 2)) / (2 * b * a)))  * (180 / PI);
	}
	else
	{
		return 0.0f;
	}
}


void Triangle::CalcMidPoint(float mids[2])
{
	if (Shape::getIsAlloced())
	{
		float *matrix;
		matrix = Shape::getMatrix();

		mids[0] = ((matrix[0] + matrix[2] + matrix[4]) / 3);
		mids[1] = ((matrix[1] + matrix[3] + matrix[5]) / 3);
	}
	else
	{
		cout << "Cannot calculate a midpoint of an unallocated shape" << endl;
	}

}


void Triangle::EditVertex(unsigned int vertex, float xOffset, float yOffset)
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
		}

		vNew[0] += xOffset;
		vNew[1] += yOffset;

		glBufferSubData(getBufferType(), vertex * getVertexStride() * getSizeOfDataBytes(), 2 * getSizeOfDataBytes(), vNew);

	}

	return;
}


void Triangle::Translate(float xAmount, float yAmount)
{
	EditVertex(0, xAmount, yAmount);
	EditVertex(1, xAmount, yAmount);
	EditVertex(2, xAmount, yAmount);
}


void Triangle::Resize(float factor)
{

	if (Shape::getIsAlloced())
	{
		float *matrix;
		matrix = Shape::getMatrix();

		for (int i = 0; i < 6; i++)
		{
			matrix[i] = (matrix[i] * factor);
		}

		a = a * factor;
		b = b * factor;
		c = c * factor;

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, matrix, GL_DYNAMIC_DRAW);
	}
}


void Triangle::getVertex(int vertex, float vert[2])
{
	if (Shape::getIsAlloced())
	{
		float *matrix;
		matrix = Shape::getMatrix();

		switch (vertex)
		{
		case 0: //0,1
			vert[0] = matrix[0];
			vert[1] = matrix[1];
			break;
		case 1: //2,3
			vert[0] = matrix[2];
			vert[1] = matrix[3];
			break;
		case 2: //4,5
			vert[0] = matrix[4];
			vert[1] = matrix[5];
			break;
		}
	}
}

void Triangle::Rotate(float theta)
{
	float mids[2];
	CalcMidPoint(mids);

	float xTranslation = mids[0] * -1;
	float yTranslation = mids[1] * -1;

	Translate(xTranslation, yTranslation);

	Swing(theta);

	Translate(xTranslation * -1, yTranslation * -1);
}


void Triangle::FreeRotate(float theta)
{
	float mids[2];
	CalcMidPoint(mids);

	float xTranslation = mids[0] * -1;
	float yTranslation = mids[1] * -1;

	Translate(xTranslation, yTranslation);

	FreeSwing(theta);

	Translate(xTranslation * -1, yTranslation * -1);
}


void Triangle::FreeSwing(float theta)
{
	float xA = 0.0f;
	float yA = 0.0f;
	float xB = 0.0f;
	float yB = 0.0f;
	float xC = 0.0f;
	float yC = 0.0f;

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

		matrix[0] = ((xA * cos(theta)) - (yA * sin(theta)));
		matrix[1] = ((yA * cos(theta)) + (xA * sin(theta)));

		matrix[2] = ((xB * cos(theta)) - (yB * sin(theta)));
		matrix[3] = ((yB * cos(theta)) + (xB * sin(theta)));

		matrix[4] = ((xC * cos(theta)) - (yC * sin(theta)));
		matrix[5] = ((yC * cos(theta)) + (xC * sin(theta)));

		matrix[0] = matrix[0] * SQ_ASPECT_RATIO;
		matrix[2] = matrix[2] * SQ_ASPECT_RATIO;
		matrix[4] = matrix[4] * SQ_ASPECT_RATIO;

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, matrix, GL_DYNAMIC_DRAW);

	}
}



void Triangle::TranslateToOrigin()
{
	float mids[2];
	CalcMidPoint(mids);

	float xTranslation = mids[0] * -1;
	float yTranslation = mids[1] * -1;

	Translate(xTranslation, yTranslation);
}

void Triangle::Swing(float theta)
{
	float xA = 0.0f;
	float yA = 0.0f;
	float xB = 0.0f;
	float yB = 0.0f;
	float xC = 0.0f;
	float yC = 0.0f;

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

			matrix[0] = ((xA * cos(theta)) - (yA * sin(theta)));
			matrix[1] = ((yA * cos(theta)) + (xA * sin(theta)));

			matrix[2] = ((xB * cos(theta)) - (yB * sin(theta)));
			matrix[3] = ((yB * cos(theta)) + (xB * sin(theta)));

			matrix[4] = ((xC * cos(theta)) - (yC * sin(theta)));
			matrix[5] = ((yC * cos(theta)) + (xC * sin(theta)));

			matrix[0] = matrix[0] * SQ_ASPECT_RATIO;
			matrix[2] = matrix[2] * SQ_ASPECT_RATIO;
			matrix[4] = matrix[4] * SQ_ASPECT_RATIO;

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, matrix, GL_DYNAMIC_DRAW);


		//if the shape has rotated more than 360 degrees
		currentRotation += theta;

		//if (currentRotation >= (2.0f * PI))
		//{
		//	currentRotation = ((2.0f * PI) - currentRotation);
		//}

		//if (currentRotation <= (-2.0f * PI))
		//{
		//	currentRotation = ((2.0f * PI) + currentRotation);
		//}

	}
}

void Triangle::RotateVertex(int vertex, float theta)
{
	float x = 0.0f;
	float y = 0.0f;

	if (Shape::getIsAlloced())
	{
		float *matrix;
		matrix = Shape::getMatrix();

		switch (vertex)
		{
		case 0: //0,1
			x = matrix[0];
			y = matrix[1];

			matrix[0] = ((x * cos(theta)) - (y * sin(theta)));
			matrix[1] = ((y * cos(theta)) + (x * sin(theta)));

			break;
		case 1: //2,3
			x = matrix[2];
			y = matrix[3];

			matrix[2] = ((x * cos(theta)) - (y * sin(theta)));
			matrix[3] = ((y * cos(theta)) + (x * sin(theta)));

			break;
		case 2: //4,5
			x = matrix[4];
			y = matrix[5];

			matrix[4] = ((x * cos(theta)) - (y * sin(theta)));
			matrix[5] = ((y * cos(theta)) + (x * sin(theta)));

			break;
		}

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, matrix, GL_DYNAMIC_DRAW);
	}
}


/* Helper Functions*/

void Triangle::printSidesAngles()
{
	if (getIsAlloced())
	{
		cout << getSidea() << " " << getSideb() << " " << getSidec() << endl;
		cout << getAngleA_D() << " " << getAngleB_D() << " " << getAngleC_D() << endl;
	}
	else
	{
		return;
	}
}
