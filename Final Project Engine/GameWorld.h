#pragma once

#include "Init.h"
#include "List.h"
#include "Human.h"
#include "BuildingGame\Chunk.h"

/*

	GameWorld

	- Worlds should be generated and updated based on world type ()
			
			- This effects which type of chunks will be pushed to InsertAtEnd()




	- Array of ChunkLists which are arranged vertically

	- 0 is the bottom chunkList and it moves up from there

	- Needs to return ** scene of chunks and the number of chunks in the scene

	- Needs to QueueTranslations_Translate its chunks

	- Needs to insertAtEnd() chunks when nescessary

	- Will accept a pointer to the main character

*/


class GameWorld
{
public:
	
	/* CameraBound is when the camera will be moved in either direction, insertBound is when new chunks should be created on the ends of each strip */
	GameWorld(int sizePm, float blockSize, int chunkSize, Texture **texPointers, int numTextures, blockType *blockTypes, 
		
	const string &type, int size, float cameraBound, float insertBound, Human *character, const string &chunkdirectory, float updateSize = 1.5f);



	void FlatWorld(int sizePm);

	Chunk **getScene();

	int getNumS() { return numInScene; }

	void QueueTranslations();

	void generateNewChunks();


private:

	string type;

	ChunkStrip *strips;

	Chunk *scene[MAXUPDATEAREA];
	int numInScene;


	Texture **texPointers;
	blockType *blockTypes;
	int numTextures;

	Human *character;

	string chunkdirectory;

	float blockSize;
	int chunkSize;
	int size;

	float cameraBound;
	float insertBound;
	float updateSize;

};