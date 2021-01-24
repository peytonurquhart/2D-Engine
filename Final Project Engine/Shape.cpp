#include "Init.h"

Shape::Shape()
{
	this->vertexBuffer = 0;
	this->indexBuffer = 0;

	this->numVerteces = 0;
	this->sizeofDataTypeInBytes = 0;
	this->numFloats = 0;
	this->matrix = nullptr;
	this->isIndexed = false;
	this->numIndeces = 0;
	this->indeces = nullptr;
	this->vertexStride = 0;
	this->drawType = GL_DYNAMIC_DRAW;
	this->bufferType = GL_ARRAY_BUFFER;
	this->indexBufferType = GL_ELEMENT_ARRAY_BUFFER;
	this->componentsPerVertex = 0;
	this->isAlloced = false;
	this->VaPointerIndex = 0;
	this->vertexArrayObject = 0;
}

Shape::Shape(const Shape &oldShape)
{
	this->vertexBuffer = oldShape.vertexBuffer;
	this->indexBuffer = oldShape.indexBuffer;

	this->numVerteces = oldShape.numVerteces;
	this->sizeofDataTypeInBytes = oldShape.sizeofDataTypeInBytes;
	this->numFloats = oldShape.numFloats;


	this->matrix = new float[oldShape.numFloats];
	float *oTemp = oldShape.matrix;
	for (short int i = 0; i < oldShape.numFloats; i++)
	{
		this->matrix[i] = oTemp[i];
	}

	this->isIndexed = oldShape.isIndexed;
	this->numIndeces = oldShape.numIndeces;


	this->indeces = new unsigned int[oldShape.numIndeces];
	unsigned int *iTemp = oldShape.indeces;
	for (short int i = 0; i < oldShape.numIndeces; i++)
	{
		this->indeces[i] = iTemp[i];
	}


	this->vertexStride = oldShape.vertexStride;
	this->drawType = oldShape.drawType;
	this->bufferType = oldShape.bufferType;
	this->indexBufferType = oldShape.indexBufferType;
	this->componentsPerVertex = oldShape.componentsPerVertex;
	this->isAlloced = oldShape.isAlloced;
	this->VaPointerIndex = oldShape.VaPointerIndex;
	this->vertexArrayObject = oldShape.vertexArrayObject;
	this->polygonDrawType = oldShape.polygonDrawType;


}

Shape::~Shape()
{

	if (isBuffered)
	{

		glDeleteVertexArrays(1, &vertexArrayObject);
		glDeleteBuffers(1, &vertexBuffer);
		glDeleteBuffers(1, &indexBuffer);
	//	isBuffered = false;

	}

	if (isAlloced)
	{

		delete[]matrix;

		delete[]indeces;

		isAlloced = false;

	}
}

void Shape::deleteGLBuffers()
{
	if (isBuffered)
	{
		glDeleteVertexArrays(1, &vertexArrayObject);
		glDeleteBuffers(1, &vertexBuffer);
		glDeleteBuffers(1, &indexBuffer);
		isBuffered = false;
	}
}

void Shape::Init(int numVerteces, int componentsPerVertex, int sizeofDataTypeBytes,

	int numFloats, float newMatix[],

	bool isIndexed, int numIndeces, unsigned int newIndeces[],

	int vertexStride, GLenum drawType, GLenum bufferType, GLenum indexBufferType, int vaPointerIndex, GLenum polygonDrawType, bool isBuffered)
{
	float aspectRatio = 1.0f;

	aspectRatio = SQ_ASPECT_RATIO;


	static int a = 0;

	this->a = a;

	this->vertexBuffer = 0;
	this->indexBuffer = 0;

	this->numVerteces = numVerteces;
	this->sizeofDataTypeInBytes = sizeofDataTypeBytes;
	this->numFloats = numFloats;
	this->matrix = nullptr;
	this->isIndexed = isIndexed;
	this->numIndeces = numIndeces;

	if (!isIndexed)
		this->indeces = nullptr;

	this->vertexStride = vertexStride;
	this->drawType = drawType;
	this->bufferType = bufferType;
	this->indexBufferType = indexBufferType;
	this->componentsPerVertex = componentsPerVertex;
	this->polygonDrawType = polygonDrawType;
	this->VaPointerIndex = vaPointerIndex;

	matrix = new float[numFloats];

	float temp;

	for (int i = 2, j = 0; i < numFloats + 2; i++, j++)
	{
		temp = newMatix[j];

		if (i % 2 == 0)
		{
			temp = temp * SQ_ASPECT_RATIO;
		}

		matrix[j] = temp;
	}

	if (isIndexed == true)
	{
		indeces = new unsigned int[numIndeces];
		for (int i = 0; i < numIndeces; i++)
		{
			indeces[i] = newIndeces[i];
		}
	}
	//+0.52 KB



		this->isAlloced = true;

		if (isBuffered = true)
		{

			glGenVertexArrays(1, &vertexArrayObject); //creating a vertex array (required when using core mode or publishing) and binding, nothing is actually done with it
			glBindVertexArray(vertexArrayObject);

			glGenBuffers(1, &vertexBuffer);
			glBindBuffer(bufferType, vertexBuffer);

			glBufferData(bufferType, sizeofDataTypeBytes * numFloats, matrix, drawType);
			glVertexAttribPointer(0, componentsPerVertex, GL_FLOAT, GL_FALSE, sizeofDataTypeBytes * vertexStride, 0); //this is the line of code which links the buffer (at index 0 (function paramater 1)) to the vertex array object
			glEnableVertexAttribArray(0);

			if (isIndexed == true)
			{
				glGenBuffers(1, &indexBuffer);
				glBindBuffer(indexBufferType, indexBuffer); //GL_ELEMENT_ARRAY_BUFFER for an index buffer
				glBufferData(indexBufferType, sizeof(unsigned int) * numIndeces, indeces, drawType);
			}

		}
	
	a++;

}


void Shape::ReInit(int numVerteces, int componentsPerVertex, int sizeofDataTypeBytes,

	int numFloats, float newMatix[],

	bool isIndexed, int numIndeces, unsigned int newIndeces[],

	int vertexStride, GLenum drawType, GLenum bufferType, GLenum indexBufferType, int vaPointerIndex, GLenum polygonDrawType, bool isBuffered)
{
	float aspectRatio = 1.0f;

	aspectRatio = SQ_ASPECT_RATIO;


	static int a = 0;

	this->a = a;

	this->vertexBuffer = 0;
	this->indexBuffer = 0;

	this->numVerteces = numVerteces;
	this->sizeofDataTypeInBytes = sizeofDataTypeBytes;
	this->numFloats = numFloats;
	this->matrix = nullptr;
	this->isIndexed = isIndexed;
	this->numIndeces = numIndeces;

	if (!isIndexed)
		this->indeces = nullptr;

	this->vertexStride = vertexStride;
	this->drawType = drawType;
	this->bufferType = bufferType;
	this->indexBufferType = indexBufferType;
	this->componentsPerVertex = componentsPerVertex;
	this->polygonDrawType = polygonDrawType;
	this->VaPointerIndex = vaPointerIndex;

	matrix = new float[numFloats];

	float temp;

	for (int i = 2, j = 0; i < numFloats + 2; i++, j++)
	{
		temp = newMatix[j];

		matrix[j] = temp;
	}

	if (isIndexed == true)
	{
		indeces = new unsigned int[numIndeces];
		for (int i = 0; i < numIndeces; i++)
		{
			indeces[i] = newIndeces[i];
		}
	}
	//+0.52 KB



		this->isAlloced = true;

		if (isBuffered = true)
		{

			glGenVertexArrays(1, &vertexArrayObject); //creating a vertex array (required when using core mode or publishing) and binding, nothing is actually done with it
			glBindVertexArray(vertexArrayObject);

			glGenBuffers(1, &vertexBuffer);
			glBindBuffer(bufferType, vertexBuffer);

			glBufferData(bufferType, sizeofDataTypeBytes * numFloats, matrix, drawType);
			glVertexAttribPointer(0, componentsPerVertex, GL_FLOAT, GL_FALSE, sizeofDataTypeBytes * vertexStride, 0); //this is the line of code which links the buffer (at index 0 (function paramater 1)) to the vertex array object
			glEnableVertexAttribArray(0);

			if (isIndexed == true)
			{
				glGenBuffers(1, &indexBuffer);
				glBindBuffer(indexBufferType, indexBuffer); //GL_ELEMENT_ARRAY_BUFFER for an index buffer
				glBufferData(indexBufferType, sizeof(unsigned int) * numIndeces, indeces, drawType);
			}

		}

	a++;

}


Shape::Shape(int numVerteces, int componentsPerVertex, int sizeofDataTypeBytes, int numFloats, float newMatix[], bool isIndexed,
	int numIndeces, unsigned int newIndeces[], int vertexStride, GLenum drawType, GLenum bufferType, GLenum indexBufferType, int vaPointerIndex, GLenum polygonDrawType, bool isBuffered)
{
	float aspectRatio = 1.0f;

	aspectRatio = SQ_ASPECT_RATIO;

	this->vertexBuffer = 0;
	this->indexBuffer = 0;

	this->numVerteces = numVerteces;
	this->sizeofDataTypeInBytes = sizeofDataTypeBytes;
	this->numFloats = numFloats;
	this->matrix = nullptr;
	this->isIndexed = isIndexed;
	this->numIndeces = numIndeces;

	if (!isIndexed)
		this->indeces = nullptr;

	this->vertexStride = vertexStride;
	this->drawType = drawType;
	this->bufferType = bufferType;
	this->indexBufferType = indexBufferType;
	this->componentsPerVertex = componentsPerVertex;
	this->polygonDrawType = polygonDrawType;
	this->VaPointerIndex = vaPointerIndex;

	matrix = new float[numFloats];

	for (int i = 2, j = 0; i < numFloats + 2; i++, j++)
	{
		if (i % 2 == 0) //if x
			matrix[j] = (newMatix[j] * aspectRatio);
		else
			matrix[j] = newMatix[j];
	}

	if (isIndexed == true)
	{
		indeces = new unsigned int[numIndeces];

		for (int i = 0; i < numIndeces; i++)
		{
			indeces[i] = newIndeces[i];
		}
	}



		this->isAlloced = true;

		if (isBuffered = true)
		{

			glGenVertexArrays(1, &vertexArrayObject); //creating a vertex array (required when using core mode or publishing) and binding, nothing is actually done with it
			glBindVertexArray(vertexArrayObject);

			glGenBuffers(1, &vertexBuffer);
			glBindBuffer(bufferType, vertexBuffer);

			glBufferData(bufferType, sizeofDataTypeBytes * numFloats, matrix, drawType);
			glVertexAttribPointer(0, componentsPerVertex, GL_FLOAT, GL_FALSE, sizeofDataTypeBytes * vertexStride, 0); //this is the line of code which links the buffer (at index 0 (function paramater 1)) to the vertex array object
			glEnableVertexAttribArray(0);

			if (isIndexed == true)
			{
				glGenBuffers(1, &indexBuffer);
				glBindBuffer(indexBufferType, indexBuffer); //GL_ELEMENT_ARRAY_BUFFER for an index buffer
				glBufferData(indexBufferType, sizeof(unsigned int) * numIndeces, indeces, drawType);
			}

		}

}


void Shape::Draw()
{
	if (isAlloced)
	{
		if (isIndexed)
		{
			glDrawElements(polygonDrawType, getNumIndeces(), GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(polygonDrawType, 0, getNumVerteces());
		}
	}
	else
	{
		cout << "isAlloced was false: Attempted to draw a shape which hasnt been buffered yet!" << endl;
	}
}



void Shape::Unbind()
{
	/*unbinding not needed exept for debug*/

	//	glBindVertexArray(0);
	//	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void Shape::BufferVertex()
{
	if (isAlloced)
	{
		glBufferSubData(bufferType, 0, sizeofDataTypeInBytes * numFloats, matrix);
	}
}

/* PERFORMANCE */
/*consider changing to glBufferSubData */
void Shape::BufferIndeces()
{
	if (isAlloced && isIndexed)
	{
		glBufferData(indexBufferType, sizeof(unsigned int) * numIndeces, indeces, drawType);
	}
}


void Shape::Bind()
{
	if (isAlloced)
	{
		glBindBuffer(bufferType, vertexBuffer);

		glBindVertexArray(vertexArrayObject);

		if (isIndexed)
		{
			glBindBuffer(indexBufferType, indexBuffer);
		}
	}
	else
	{
		cout << "isAlloced was false: Attempted to bind a shape which hasnt been allocated yet" << endl;
	}
}
