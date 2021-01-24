#pragma once

#include "Init.h"
#include "Node.h"

#define MAXUPDATEAREA 64


/*
			Horizontal list of chunks

			/* Chunks are the last dynamically destructable objects, chunkstrips should be in the world once and to stay

			/* Considerizing optimizing chunk searching by adding saved bookmark addresses to the list

*/

class ChunkStrip
{
public:
	/* Initializes a chunk strip at a specific ylevel */
	ChunkStrip() { return; }

	ChunkStrip(int yLevel);

	void Init(int yLevel);
	
	/* return true if there are no chunks in the strip*/
	bool isEmpty() { if (pHead == nullptr) { return true; } return false; }

	/* pushes one chunk to the strip */
	/* pm (if the new chunk should be inserted to the right or left) -1 = left, 0 = phead, 1 = right*/
	void Push(int pm, int chunkSize, const blockType type, Texture *texPointers, float blockSize = 0.1, int numTexturesPerBlock = 1);
	void Push(int pm, const string &command, int chunksize, float blocksize, int numTexturesPerBlock);

	/*initializes a whole strip of chunks with given size and takes a special key argument (such as nullchunk)*/
	void Init(int sizePlusMinus, const string &command, int chunksize, float blocksize, int numtexturesperblock);

	/*initializes a whole strip of chunks with given size and blocktype + texture pointer*/
	void Init(int sizePlusMinus, int chunkSize, const blockType type, Texture *texPointers[MAXBLOCKTEXTURES], float blockSize = 0.1, int numTexturesPerBlock = 1);


	/*adds translations to the queue for all chunks*/
	void QueueTranslations(float x, float y);
	/*translates all chunks from the translationQueue*/
	void Translate(float bound = 1.5);
	/*adds translations to queue for all chunks, translates chunks within the bound*/
	void QueueTranslations_Translate(float x, float y, const string & directory, float bound, Texture *texArray[MAXBLOCKTEXTURES], int numTextures);
	/*centers the entire strip with respect to the midpoint */
	void XCenterAll();

	/* draws all the chunks in the strip (not sure if opengl optimizes draw calls outside the buffer or not)*/
	void DrawAll();

	/* O(1) dependent on O(n) generateArray() but can be called if no movement has occured */
	void DrawArray();

	/* returns the amount of chunks which touched the play area, updates the updatearray*/  /* O(n) */
	int generateUpdateArray(float pm);

	/*returns an array to the chunks that are in the specified play area when generateUpdateArray() is called*/
	Chunk **getUpdateArray() { return updateArray; }

	/*translates the strip chunksize x and y*/    /* O(n) */
	void TranslateChunkSize(int x, int y);

	/* precondition: list must be initialized and created before inserting at an end*/    /* O(1) */
	void insertAtEnd(int pm, int chunkSize, const blockType type, Texture *texPointers, float blockSize = 0.1, int numTexturesPerBlock = 1);
	void insertAtEnd(int pm, const string &command, int chunksize, float blocksize, int numTexturesPerBlock);

	/*returns how far x and y the scene is from the origin*/
	float getCurrentXTranslate() { return currentTranslate[0]; }
	float getCurrentYTranslate() { return currentTranslate[1]; }

	float *getCurrentTranslate() { return currentTranslate; }

	/* saves the entire list to a file, chunk by chunk under its yLevel Directory*/
	void saveAllToFile(const string &directory);

	int getYLevel() { return yLevel; }

	/*helper*/

	void printXOrigins();

	void printXMidpoints();

	void printCurrentNumTranslationsMade() { cout << "translations made: " << currentNumTranslationsMade << endl; }

	void deleteAll();
	void deleteAll(Node *pSub);

private:
	Node *pHead;

	Node *lLast;

	Node *rLast;
	
	/*must be generated*/
	Chunk *updateArray[MAXUPDATEAREA];

	int numInScene;

	int yLevel;

	float currentTranslate[2];

	/* log */

	int currentNumTranslationsMade;
};