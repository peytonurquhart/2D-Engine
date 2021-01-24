#pragma once

#include "Init.h"
#include "BuildingGame\Chunk.h"

#define MAX_FLOATS 64000
#define MAX_INDECES 12000

/*
 Batch Rendrer Object

- Quicker rendering of many Shapes with single GPU call.
- One batch has at most 1 Texture

*/

class RendererObject
{
public:

	RendererObject();

	/*pushes new indeces and verticies*/
	void Push(Chunk **scene, int numChunksInScene, blockType target, Texture *texPointer);

	/*binds and draws the shape*/
	void Draw();

	/*flushes all indeces and verticies*/
	void Flush();

	void displayAllAttributes() { batch.DispAllAttributes(); }



private:

	Shape batch;

	/* texture that belongs to the current batch */
	Texture *currentTexPointer;

};



class Renderer
{
public:
	~Renderer() { delete renderList; }

	Renderer(int numBatches, blockType *targets, Texture **texPointers);

	void PushAll(Chunk **scene, int numChunksInScene);

	void DrawAll();

	void FlushAll();



private:

	RendererObject *renderList;

	Texture **texPointers;

	blockType *targets;

	int numBatches;
};
