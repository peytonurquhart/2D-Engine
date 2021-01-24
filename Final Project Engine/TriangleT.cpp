#include "Init.h"


TriangleT::TriangleT(float a, float b, float c)
{
	this->a = a;
	this->b = b;
	this->c = c;

	float theta = 0.0f;

	this->currentRotation = 0.0f;

	newMatrix = new float[24];

	newMatrix[0] = (a / 2) * -1;
	newMatrix[1] = 0.0f;
	newMatrix[2] = 0.0f;

	newMatrix[8] = (a / 2);
	newMatrix[9] = 0.0f;
	newMatrix[10] = 0.0f;

	theta = acos((pow(b, 2) - pow(a, 2) - pow(c, 2)) / (-2 * a*c));
	newMatrix[16] = c * cos(theta) + newMatrix[0];
	newMatrix[17] = c * sin(theta);
	newMatrix[18] = 0.0f;



	newMatrix[3] = 0.0f;
	newMatrix[4] = 0.0f;
	newMatrix[5] = 0.0f;

	newMatrix[6] = 0.0f / SQ_ASPECT_RATIO;
	newMatrix[7] = 0.0f;


	newMatrix[11] = 0.0f;
	newMatrix[12] = 0.0f;
	newMatrix[13] = 0.0f;

	newMatrix[14] = 1.0f / SQ_ASPECT_RATIO;
	newMatrix[15] = 0.0f;


	newMatrix[19] = 0.0f;
	newMatrix[20] = 0.0f;
	newMatrix[21] = 0.0f;

	newMatrix[22] = 0.5f / SQ_ASPECT_RATIO;
	newMatrix[23] = 1.0f;



	Shape::Init(3, 3, sizeof(float), 24, newMatrix, false, 0, nullptr, 8, GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER, 0, 2, GL_TRIANGLES);

	Shape::Unbind();


	delete[] newMatrix;
	return;
}


void TriangleT::Init(float a, float b, float c)
{
	this->a = a;
	this->b = b;
	this->c = c;

	float theta = 0.0f;

	this->currentRotation = 0.0f;

	newMatrix = new float[24];

	newMatrix[0] = (a / 2) * -1;
	newMatrix[1] = 0.0f;
	newMatrix[2] = 0.0f;

	newMatrix[8] = (a / 2);
	newMatrix[9] = 0.0f;
	newMatrix[10] = 0.0f;

	theta = acos((pow(b, 2) - pow(a, 2) - pow(c, 2)) / (-2 * a*c));
	newMatrix[16] = c * cos(theta) + newMatrix[0];
	newMatrix[17] = c * sin(theta);
	newMatrix[18] = 0.0f;



	newMatrix[3] = 0.0f;
	newMatrix[4] = 0.0f;
	newMatrix[5] = 0.0f;

	newMatrix[6] = 0.0f / SQ_ASPECT_RATIO;
	newMatrix[7] = 0.0f;


	newMatrix[11] = 0.0f;
	newMatrix[12] = 0.0f;
	newMatrix[13] = 0.0f;

	newMatrix[14] = 1.0f / SQ_ASPECT_RATIO;
	newMatrix[15] = 0.0f;


	newMatrix[19] = 0.0f;
	newMatrix[20] = 0.0f;
	newMatrix[21] = 0.0f;

	newMatrix[22] = 0.5f / SQ_ASPECT_RATIO;
	newMatrix[23] = 1.0f;



	Shape::Init(3, 3, sizeof(float), 24, newMatrix, false, 0, nullptr, 8, GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER, 0, 2, GL_TRIANGLES);

	Shape::Unbind();


	delete[] newMatrix;
	return;
}



float TriangleT::getAngleA()
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


float TriangleT::getAngleB()
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


float TriangleT::getAngleC()
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


float TriangleT::getAngleA_D()
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


float TriangleT::getAngleB_D()
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


float TriangleT::getAngleC_D()
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



void TriangleT::CalcMidPoint(float mids[2])
{
	if (Shape::getIsAlloced())
	{
		float *matrix;
		matrix = Shape::getMatrix();

		mids[0] = ((matrix[0] + matrix[8] + matrix[16]) / 3);
		mids[1] = ((matrix[1] + matrix[9] + matrix[17]) / 3);
	}
	else
	{
		cout << "Cannot calculate a midpoint of an unallocated shape" << endl;
	}

}


void TriangleT::EditVertex(unsigned int vertex, float xOffset, float yOffset)
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
			vNew[0] = matrix[8];
			vNew[1] = matrix[9];

			matrix[8] += xOffset;
			matrix[9] += yOffset;
			break;
		case 2: //4,5
			vNew[0] = matrix[16];
			vNew[1] = matrix[17];

			matrix[16] += xOffset;
			matrix[17] += yOffset;
			break;
		}

		vNew[0] += xOffset;
		vNew[1] += yOffset;

		glBufferSubData(getBufferType(), vertex * getVertexStride() * getSizeOfDataBytes(), 2 * getSizeOfDataBytes(), vNew);

	}

	return;
}


void TriangleT::Translate(float xAmount, float yAmount)
{
	EditVertex(0, xAmount, yAmount);
	EditVertex(1, xAmount, yAmount);
	EditVertex(2, xAmount, yAmount);
}


void TriangleT::Resize(float factor)
{

	if (Shape::getIsAlloced())
	{
		float *matrix;
		matrix = Shape::getMatrix();

		for (int i = 0; i < 6; i++)
		{
			if(i % 8 == 0 || i % 8 == 1)
			matrix[i] = (matrix[i] * factor);
		}

		a = a * factor;
		b = b * factor;
		c = c * factor;

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, matrix, GL_DYNAMIC_DRAW);
	}
}


void TriangleT::getVertex(int vertex, float vert[2])
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
			vert[0] = matrix[8];
			vert[1] = matrix[9];
			break;
		case 2: //4,5
			vert[0] = matrix[16];
			vert[1] = matrix[17];
			break;
		}
	}
}

void TriangleT::Rotate(float theta)
{
	float mids[2];
	CalcMidPoint(mids);

	float xTranslation = mids[0] * -1;
	float yTranslation = mids[1] * -1;

	Translate(xTranslation, yTranslation);

	Swing(theta);

	Translate(xTranslation * -1, yTranslation * -1);
}


void TriangleT::FreeRotate(float theta)
{
	float mids[2];
	CalcMidPoint(mids);

	float xTranslation = mids[0] * -1;
	float yTranslation = mids[1] * -1;

	Translate(xTranslation, yTranslation);

	FreeSwing(theta);

	Translate(xTranslation * -1, yTranslation * -1);
}


void TriangleT::FreeSwing(float theta)
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

		xB = matrix[8] * SQ_RATIO_RECIP;
		yB = matrix[9];

		xC = matrix[16] * SQ_RATIO_RECIP;
		yC = matrix[17];

		matrix[0] = ((xA * cos(theta)) - (yA * sin(theta)));
		matrix[1] = ((yA * cos(theta)) + (xA * sin(theta)));

		matrix[8] = ((xB * cos(theta)) - (yB * sin(theta)));
		matrix[9] = ((yB * cos(theta)) + (xB * sin(theta)));

		matrix[16] = ((xC * cos(theta)) - (yC * sin(theta)));
		matrix[17] = ((yC * cos(theta)) + (xC * sin(theta)));

		matrix[0] = matrix[0] * SQ_ASPECT_RATIO;
		matrix[8] = matrix[8] * SQ_ASPECT_RATIO;
		matrix[16] = matrix[16] * SQ_ASPECT_RATIO;

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, matrix, GL_DYNAMIC_DRAW);

	}
}



void TriangleT::TranslateToOrigin()
{
	float mids[2];
	CalcMidPoint(mids);

	float xTranslation = mids[0] * -1;
	float yTranslation = mids[1] * -1;

	Translate(xTranslation, yTranslation);
}

void TriangleT::Swing(float theta)
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

		xB = matrix[8] * SQ_RATIO_RECIP;
		yB = matrix[9];

		xC = matrix[16] * SQ_RATIO_RECIP;
		yC = matrix[17];

		matrix[0] = ((xA * cos(theta)) - (yA * sin(theta)));
		matrix[1] = ((yA * cos(theta)) + (xA * sin(theta)));

		matrix[8] = ((xB * cos(theta)) - (yB * sin(theta)));
		matrix[9] = ((yB * cos(theta)) + (xB * sin(theta)));

		matrix[16] = ((xC * cos(theta)) - (yC * sin(theta)));
		matrix[17] = ((yC * cos(theta)) + (xC * sin(theta)));

		matrix[0] = matrix[0] * SQ_ASPECT_RATIO;
		matrix[8] = matrix[8] * SQ_ASPECT_RATIO;
		matrix[16] = matrix[16] * SQ_ASPECT_RATIO;

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, matrix, GL_DYNAMIC_DRAW);


		//if the shape has rotated more than 360 degrees
		currentRotation += theta;

	}
}

void TriangleT::RotateVertex(int vertex, float theta)
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
			x = matrix[8];
			y = matrix[9];

			matrix[8] = ((x * cos(theta)) - (y * sin(theta)));
			matrix[9] = ((y * cos(theta)) + (x * sin(theta)));

			break;
		case 2: //4,5
			x = matrix[16];
			y = matrix[17];

			matrix[16] = ((x * cos(theta)) - (y * sin(theta)));
			matrix[17] = ((y * cos(theta)) + (x * sin(theta)));

			break;
		}

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, matrix, GL_DYNAMIC_DRAW);
	}
}


void TriangleT::Bind()
{
	Shape::Bind();

	glVertexAttribPointer(Shape::getVaPointerIndex(), 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(Shape::getVaPointerIndex());
}
