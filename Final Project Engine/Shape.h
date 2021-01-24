#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

using std::endl;
using std::cout;


/* Notes For Derriving*/

/*
	- Derrived classes must have a calcMidpoint() function

	- Coordinate type is assumed as float, but still can be passed in to account for differences in sizeof() operators

	- Index type is assumed as unsigned int
*/


class Shape
{
public:

	virtual ~Shape();

	Shape();

	Shape(const Shape &oldShape);

	Shape(int numVerteces, int componentsPerVertex, int sizeofDataTypeBytes,

		int numFloats, float newMatix[],

		bool isIndexed, int numIndeces, unsigned int newIndeces[],

		int vertexStride, GLenum drawType, GLenum bufferType, GLenum indexBufferType, int vaPointerIndex = 0, GLenum polygonDrawType = GL_TRIANGLES, bool isBuffered = true);


	void Init(int numVerteces, int componentsPerVertex, int sizeofDataTypeBytes,

		int numFloats, float newMatix[],

		bool isIndexed, int numIndeces, unsigned int newIndeces[],

		int vertexStride, GLenum drawType, GLenum bufferType, GLenum indexBufferType, int vaPointerIndex = 0, GLenum polygonDrawType = GL_TRIANGLES, bool isBuffered = true);


	/* Same as init but does not normalize the vertives to fit a 16:9 aspect ratio, useful when creating meshes */
	void ReInit(int numVerteces, int componentsPerVertex, int sizeofDataTypeBytes,

		int numFloats, float newMatix[],

		bool isIndexed, int numIndeces, unsigned int newIndeces[],

		int vertexStride, GLenum drawType, GLenum bufferType, GLenum indexBufferType, int vaPointerIndex = 0, GLenum polygonDrawType = GL_TRIANGLES, bool isBuffered = true);


	/*Getters*/

	int getComponentsPerVertex() { return this->componentsPerVertex; }
	unsigned int getVertexBuff() { return this->vertexBuffer; }
	unsigned int getIndexBuff() { return this->indexBuffer; }

	int getNumVerteces() { return this->numVerteces; }
	int getSizeOfDataBytes() { return this->sizeofDataTypeInBytes; }

	int getNumFloats() { return this->numFloats; }
	float * getMatrix() { return matrix; }

	int getVertexStride() { return this->vertexStride; }

	bool getIsIndexed() { return this->isIndexed; }
	int getNumIndeces() { return this->numIndeces; }
	unsigned int * getIndeces() { return indeces; }

	GLenum getDrawType() { return this->drawType; }
	GLenum getBufferType() { return this->bufferType; }
	GLenum getIndexBufferType() { return this->indexBufferType; }

	int getVaPointerIndex() { return this->VaPointerIndex; }

	bool getIsAlloced() { return isAlloced; }

	void isAllocedBypass() { isAlloced = true; std::cout << "IsAlloced was bypassed, VBO ID: " << vertexBuffer << std::endl; }

	/*Operations*/

	void Unbind();

	virtual void Bind();

	void BufferVertex();

	void BufferIndeces();

	/*Virtual Operations*/

	virtual void Draw();

	virtual void TranslateToOrigin() { return; }

	virtual void Translate(float, float) { return; }

	virtual void Rotate(float) { return; }

	virtual void Swing(float) { return; }

	virtual void CalcMidpoint(float[2]) { return; }

	void deleteGLBuffers();

	/* gets the shapes origin (vertex 0) */
	void getOrigin(float origin[2]) { origin[0] = matrix[0]; origin[1] = matrix[1]; }

	/* gets any of the shapes verticies */
	void getOrigin(float origin[2], int vertex) 
	{ 
		int index;
		index = 0 + vertex * vertexStride;
		origin[0] = matrix[index]; 
		index = 1 + vertex * vertexStride;
		origin[1] = matrix[index]; 
	}




	/* Display / Helper */

	void DispAllAttributes()
	{

		cout << "-----------------------------------------------";
		cout <<
			endl <<
			"vertexbuffer: " << vertexBuffer << endl <<
			"indexbuffer: " << indexBuffer << endl <<
			"component / vertex: " << componentsPerVertex << endl <<
			"num vertices: " << numVerteces << endl <<
			"sizeofdatatype: " << sizeofDataTypeInBytes << endl <<
			"numfloats: " << numFloats << endl << endl;

		cout << "matrix 0 - " << numFloats - 1 << ": " << endl;
		for (int i = 0; i < numFloats; i++)
		{
			cout << i << ": " << matrix[i] << endl;
		}

		cout <<
			endl <<
			"vertexstride: " << vertexStride << endl <<
			"isindexed?: " << isIndexed << endl <<
			"numindeces: " << numIndeces << endl << endl;

		cout << "indeces 0 - " << numIndeces - 1 << ": " << endl;
		for (int i = 0; i < numIndeces; i++)
		{
			cout << i << ": " << indeces[i] << endl;
		}

		cout <<
			endl <<
			"drawtype: " << drawType << endl <<
			"buffertype: " << bufferType << endl <<
			"indexbuffertype: " << indexBufferType << endl <<
			"polygondrawtype: " << polygonDrawType << endl <<

			"vapointerindex: " << VaPointerIndex << endl <<
			"vertexarrayobject: " << vertexArrayObject << endl <<
			"isalloced?: " << isAlloced << endl;
		cout << "-----------------------------------------------" << endl;
 
	}





private:

	/*Buffers*/

	unsigned int vertexBuffer;
	unsigned int indexBuffer;

	unsigned int vertexArrayObject;

	/*Members*/

	int componentsPerVertex;
	int numVerteces;
	int sizeofDataTypeInBytes;

	int numFloats;
	float *matrix;

	int vertexStride;

	bool isIndexed;
	int numIndeces;
	unsigned int *indeces;

	GLenum drawType;
	GLenum bufferType;
	GLenum indexBufferType;
	GLenum polygonDrawType;

	int VaPointerIndex;

	bool isAlloced;
	bool isBuffered;

	/*test*/
	int a;
};