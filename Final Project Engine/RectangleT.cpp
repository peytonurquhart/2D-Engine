#include "Init.h"


RectangleT::RectangleT(float height, float width, float z, bool isBuffered)
{
	newMatrix = new float[32];
	newInd = new unsigned int[6];


	this->height = height;
	this->width = width;
	this->currentRotation = 0.0f;

	float x = width / 2;
	float y = height / 2;


	//0

	//xyz
	newMatrix[0] = x;
	newMatrix[1] = y;
	newMatrix[2] = z;
	//c
	newMatrix[3] = 0.0f;
	newMatrix[4] = 0.0f;
	newMatrix[5] = 0.0f;
	//t
	newMatrix[6] = 1.0f / SQ_ASPECT_RATIO;
	newMatrix[7] = 1.0f;


	//1

	//xyz
	newMatrix[8] = x;
	newMatrix[9] = y * -1;
	newMatrix[10] = z;
	//c
	newMatrix[11] = 0.0f;
	newMatrix[12] = 0.0f;
	newMatrix[13] = 0.0f;
	//t
	newMatrix[14] = 1.0f / SQ_ASPECT_RATIO;
	newMatrix[15] = 0.0f;


	//2

	//xyz
	newMatrix[16] = x * -1;
	newMatrix[17] = y * -1;
	newMatrix[18] = z;
	//c
	newMatrix[19] = 0.0f;
	newMatrix[20] = 0.0f;
	newMatrix[21] = 0.0f;
	//t
	newMatrix[22] = 0.0f / SQ_ASPECT_RATIO;
	newMatrix[23] = 0.0f;


	//3

	//xyz
	newMatrix[24] = -1 * x;
	newMatrix[25] = y;
	newMatrix[26] = z;
	//c
	newMatrix[27] = 0.0f;
	newMatrix[28] = 0.0f;
	newMatrix[29] = 0.0f;
	//t
	newMatrix[30] = 0.0f / SQ_ASPECT_RATIO;
	newMatrix[31] = 1.0f;




	// Draw pattern
	newInd[0] = 0;
	newInd[1] = 1;
	newInd[2] = 2;

	newInd[3] = 2;
	newInd[4] = 0;
	newInd[5] = 3;


	Shape::Init(4, 3, sizeof(float), 32, newMatrix, true, 6, newInd, 8, GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, 2, 4U, isBuffered);



	delete[]newMatrix;
	delete[]newInd;

	Shape::Unbind();
}



void RectangleT::Init(float height, float width, float z, bool isBuffered)
{
	newMatrix = new float[32];
	newInd = new unsigned int[6];


	this->height = height;
	this->width = width;
	this->currentRotation = 0.0f;

	float x = width / 2;
	float y = height / 2;


	//0

	//xyz
	newMatrix[0] = x;
	newMatrix[1] = y;
	newMatrix[2] = z;
	//c
	newMatrix[3] = 0.0f;
	newMatrix[4] = 0.0f;
	newMatrix[5] = 0.0f;
	//t
	newMatrix[6] = 1.0f / SQ_ASPECT_RATIO;
	newMatrix[7] = 1.0f;


	//1

	//xyz
	newMatrix[8] = x;
	newMatrix[9] = y * -1;
	newMatrix[10] = z;
	//c
	newMatrix[11] = 0.0f;
	newMatrix[12] = 0.0f;
	newMatrix[13] = 0.0f;
	//t
	newMatrix[14] = 1.0f / SQ_ASPECT_RATIO;
	newMatrix[15] = 0.0f;


	//2

	//xyz
	newMatrix[16] = x * -1;
	newMatrix[17] = y * -1;
	newMatrix[18] = z;
	//c
	newMatrix[19] = 0.0f;
	newMatrix[20] = 0.0f;
	newMatrix[21] = 0.0f;
	//t
	newMatrix[22] = 0.0f / SQ_ASPECT_RATIO;
	newMatrix[23] = 0.0f;


	//3

	//xyz
	newMatrix[24] = -1 * x;
	newMatrix[25] = y;
	newMatrix[26] = z;
	//c
	newMatrix[27] = 0.0f;
	newMatrix[28] = 0.0f;
	newMatrix[29] = 0.0f;
	//t
	newMatrix[30] = 0.0f / SQ_ASPECT_RATIO;
	newMatrix[31] = 1.0f;




	// Draw pattern
	newInd[0] = 0;
	newInd[1] = 1;
	newInd[2] = 2;

	newInd[3] = 2;
	newInd[4] = 0;
	newInd[5] = 3;


	Shape::Init(4, 3, sizeof(float), 32, newMatrix, true, 6, newInd, 8, GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, 2, 4U, isBuffered);

	delete[]newMatrix;
	delete[]newInd;

	Shape::Unbind();
}

void RectangleT::CalcMidPoint(float mids[2])
{
	if (Shape::getIsAlloced())
	{
		float *matrix;
		matrix = Shape::getMatrix();

		mids[0] = ((matrix[0] + matrix[16]) / 2);
		mids[1] = ((matrix[1] + matrix[17]) / 2);
	}
	else
	{
		cout << "Cannot calculate a midpoint of an unallocated shape" << endl;
	}
}


void RectangleT::EditVertex(unsigned int vertex, float xOffset, float yOffset)
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
		case 3: //6,7
			vNew[0] = matrix[24];
			vNew[1] = matrix[25];

			matrix[24] += xOffset;
			matrix[25] += yOffset;
			break;

		}

		vNew[0] += xOffset;
		vNew[1] += yOffset;

	}

	return;
}


void RectangleT::Translate(float xAmount, float yAmount)
{
	EditVertex(0, xAmount, yAmount);
	EditVertex(1, xAmount, yAmount);
	EditVertex(2, xAmount, yAmount);	
	EditVertex(3, xAmount, yAmount);
}


void RectangleT::Resize(float factor)
{

	if (Shape::getIsAlloced())
	{
		float *matrix;
		matrix = Shape::getMatrix();

		for (int i = 0; i < 32; i++)
		{
			if(i % 8 == 0 || i % 8 == 1)
			matrix[i] = (matrix[i] * factor);
		}

		height = height * factor;
		width = width * factor;

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Shape::getNumFloats(), matrix, GL_DYNAMIC_DRAW);
	}
}


void RectangleT::Rotate(float theta)
{
	float mids[2];
	CalcMidPoint(mids);

	float xTranslation = mids[0] * -1;
	float yTranslation = mids[1] * -1;

	Translate(xTranslation, yTranslation);

	Swing(theta);

	Translate(xTranslation * -1, yTranslation * -1);
}



void RectangleT::TranslateToOrigin()
{
	float mids[2];
	CalcMidPoint(mids);

	float xTranslation = mids[0] * -1;
	float yTranslation = mids[1] * -1;

	Translate(xTranslation, yTranslation);
}

void RectangleT::Swing(float theta)
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

		xB = matrix[8] * SQ_RATIO_RECIP;
		yB = matrix[9];

		xC = matrix[16] * SQ_RATIO_RECIP;
		yC = matrix[17];

		xD = matrix[24] * SQ_RATIO_RECIP;
		yD = matrix[25];

		matrix[0] = ((xA * cos(theta)) - (yA * sin(theta)));
		matrix[1] = ((yA * cos(theta)) + (xA * sin(theta)));

		matrix[8] = ((xB * cos(theta)) - (yB * sin(theta)));
		matrix[9] = ((yB * cos(theta)) + (xB * sin(theta)));

		matrix[16] = ((xC * cos(theta)) - (yC * sin(theta)));
		matrix[17] = ((yC * cos(theta)) + (xC * sin(theta)));

		matrix[24] = ((xD * cos(theta)) - (yD * sin(theta)));
		matrix[25] = ((yD * cos(theta)) + (xD * sin(theta)));

		matrix[0] = matrix[0] * SQ_ASPECT_RATIO;
		matrix[8] = matrix[8] * SQ_ASPECT_RATIO;
		matrix[16] = matrix[16] * SQ_ASPECT_RATIO;
		matrix[24] = matrix[24] * SQ_ASPECT_RATIO;

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Shape::getNumFloats(), matrix, GL_DYNAMIC_DRAW);

		currentRotation += theta;
	}
}


void RectangleT::FreeSwing(float theta)
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

		xB = matrix[8] * SQ_RATIO_RECIP;
		yB = matrix[9];

		xC = matrix[16] * SQ_RATIO_RECIP;
		yC = matrix[17];

		xD = matrix[24] * SQ_RATIO_RECIP;
		yD = matrix[25];

		matrix[0] = ((xA * cos(theta)) - (yA * sin(theta)));
		matrix[1] = ((yA * cos(theta)) + (xA * sin(theta)));

		matrix[8] = ((xB * cos(theta)) - (yB * sin(theta)));
		matrix[9] = ((yB * cos(theta)) + (xB * sin(theta)));

		matrix[16] = ((xC * cos(theta)) - (yC * sin(theta)));
		matrix[17] = ((yC * cos(theta)) + (xC * sin(theta)));

		matrix[24] = ((xD * cos(theta)) - (yD * sin(theta)));
		matrix[25] = ((yD * cos(theta)) + (xD * sin(theta)));

		matrix[0] = matrix[0] * SQ_ASPECT_RATIO;
		matrix[8] = matrix[8] * SQ_ASPECT_RATIO;
		matrix[16] = matrix[16] * SQ_ASPECT_RATIO;
		matrix[24] = matrix[24] * SQ_ASPECT_RATIO;

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Shape::getNumFloats(), matrix, GL_DYNAMIC_DRAW);
	}
}

void RectangleT::FreeRotate(float theta)
{
	float mids[2];
	CalcMidPoint(mids);

	float xTranslation = mids[0] * -1;
	float yTranslation = mids[1] * -1;

	Translate(xTranslation, yTranslation);

	FreeSwing(theta);

	Translate(xTranslation * -1, yTranslation * -1);
}


void RectangleT::Bind()
{
	// only allows for 2 components per generic vertex attribute

	Shape::Bind();
	glVertexAttribPointer(Shape::getVaPointerIndex(), 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(Shape::getVaPointerIndex());
}

void RectangleT::MoveToOrigin()
{
	float o[2];

	getOrigin(o);

	o[0] = o[0] * -1;
	o[1] = o[1] * -1;

	Translate(o[0], o[1]);
}
