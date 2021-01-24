#include "GameWorld.h"

GameWorld::GameWorld(int sizePm, float blockSize, int chunkSize, Texture **texPointers, int numTextures, blockType *blockTypes, const string &type, int size, float cameraBound, float insertBound, Human *character, const string &chunkdirectory, float updateSize)
{
	this->size = size;
	this->cameraBound = cameraBound;
	this->insertBound = insertBound;
	this->type = type;
	this->character = character;
	this->blockSize = blockSize;
	this->chunkSize = chunkSize;
	this->texPointers = texPointers;
	this->blockTypes = blockTypes;
	this->updateSize = updateSize;
	this->numTextures = numTextures;
	this->chunkdirectory = chunkdirectory;

	if (type == "flatworld")
	{
		FlatWorld(sizePm);
	}
	else
	{
		cout << "World Type Not Recognized: " << type << endl;
		system("pause");
	}
}

void GameWorld::FlatWorld(int sizePm)
{
	strips = new ChunkStrip[size];
	int yLev = size / 2 * -1;

	for (int i = 0; i < size; i++, yLev++)
	{
		strips[i].Init(yLev);

		/*below ground*/
		if (yLev < 0)
		{
			strips[i].Init(sizePm, chunkSize, stoneBlock, texPointers, blockSize, 1);
		}
		else /*above ground*/
		{
			strips[i].Init(sizePm, "nullchunk", chunkSize, blockSize, 1);
		}

		strips[i].XCenterAll();
	}
}


Chunk ** GameWorld::getScene()
{
	this->numInScene = 0;

	int numS = 0, k = 0;
	Chunk **sceneTemp = nullptr;

	for (int i = 0; i < size; i++)
	{
		numS = strips[i].generateUpdateArray(this->updateSize);
		sceneTemp = strips[i].getUpdateArray();

		numInScene += numS;

		for (int j = 0; j < numS; j++)
		{
			scene[k] = sceneTemp[j];
			k++;
		}
	}

	return scene;
}


void GameWorld::QueueTranslations()
{
	if (character->getX() < -1 * cameraBound)
	{
		character->FreeTranslate(character->getSpeed() * 1, 0);

		for (int i = 0; i < size; i++)
		{
			strips[i].QueueTranslations_Translate(character->getSpeed() * 1, 0, chunkdirectory, updateSize + 0.5f, texPointers, numTextures);
		}


	}
	else if (character->getX() > cameraBound)
	{
		character->FreeTranslate(character->getSpeed() * -1, 0);

		for (int i = 0; i < size; i++)
		{
			strips[i].QueueTranslations_Translate(character->getSpeed() * -1, 0, chunkdirectory, updateSize + 0.5f, texPointers, numTextures);
		}

	}
}


void GameWorld::generateNewChunks()
{
	if (character->pollForFurthestDistance(insertBound) == true)
	{
		for (int i = 0; i < size; i++)
		{
			if (strips[i].getYLevel() < 0)
			{
				strips[i].insertAtEnd(1, chunkSize, stoneBlock, texPointers[1], 0.08, 1);
				strips[i].insertAtEnd(-1, chunkSize, stoneBlock, texPointers[1], 0.08, 1);
			}
			else
			{
				strips[i].insertAtEnd(1, "nullchunk", chunkSize, 0.08, 1);
				strips[i].insertAtEnd(-1, "nullchunk", chunkSize, 0.08, 1);
			}
		}

	}
}