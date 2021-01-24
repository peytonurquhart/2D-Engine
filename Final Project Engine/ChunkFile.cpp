#include "BuildingGame\Chunk.h"
#include <fstream>
#include <sstream>

/*

Chunk File Notes:

- REMEMBER: nullblocks dont have texpointers/numtextures and their blockID is -1

- Tex pointer saving is only for dynamically saving and loading blocks, it will not work to load a saved game since the value of the textures pointer changes!


*/


int absVal(int n)
{
	if (n < 0)
	{
		n = n * -1;
	}

	return n;
}


bool Chunk::saveToFile(const string &directory, int stripID, int nodeID, bool shouldUnallocate)
{
	stringstream filename;
	string convert;
	int i = 0;

	if (stripID < 0)
	{
		filename << directory << '/' << 'n' << absVal(stripID) << "/" << nodeID << ".csv";
	}
	else
	{
		filename << directory << '/' << absVal(stripID) << "/" << nodeID << ".csv";
	}

	convert = filename.str();


	chunkFile.open(convert.c_str(), std::fstream::out);

	if (chunkFile.is_open() == true)
	{
		/*write data here*/
		for (i = 0; i < (chunkSize * chunkSize) - 1; i++)
		{
			chunkFile << (int)chunk[i].getBlockType() << endl;
		}
		chunkFile << (int)chunk[i].getBlockType();


		if (shouldUnallocate == true)
		{

			delete[] chunk;

			isAlloaced = false;
		}

		chunkFile.close();
		return true;
	}
	else
	{
		chunkFile.close();
		return false;
	}
}


/* made for one line chunk descriptions for the time being */
void Chunk::InitFromFile(const string &directory, int chunkSize, float blockSize, Texture *texPointers[MAXBLOCKTEXTURES], int numTextures, int stripID, int nodeID, float *listCurrentTranslate)
{
	/* 1.) assign default values to the new chunk*/

	this->chunkSize = chunkSize;
	this->blockSize = blockSize;

	chunk = new Block[chunkSize * chunkSize];

	if (chunk == nullptr)
	{
		cout << "memory allocation fail: InitFromFile():" << endl;
		system("pause");
	}


	origin[0] = 0.0f;
	origin[1] = 0.0f;

	PendingTranslate[0] = 0.0f;
	PendingTranslate[1] = 0.0f;


	bool reset = false;

	/* 2.) find the file directory for this chunk */

	stringstream filename;
	string convert;
	int i = 0;

	if (stripID < 0)
	{
		filename << directory << '/' << 'n' << absVal(stripID) << "/" << nodeID << ".csv";
	}
	else
	{
		filename << directory << '/' << absVal(stripID) << "/" << nodeID << ".csv";
	}

	convert = filename.str();

	chunkFile.open(convert.c_str(), std::fstream::in);

	int type;
	char str[4];
	int numTexturesPerBlock = 1; //NUMTEXPERBLOCK SET TO 1 STATIC since it is unused rn


	for (int i = 0; i < chunkSize * chunkSize; i++)
	{

		if (i == 0)
			reset = true;
		else
			reset = false;

		chunkFile.getline(str, 4);
		type = atoi(str);


		if (type < -1 || type > numTextures)
		{
			cout << "ERROR: Blocktype referenced from chunkfile was outside the bound of acceptable block types" << endl;
			system("pause");
		}
		else
		{
				chunk[i].Init((blockType)type, texPointers[type], blockSize, numTexturesPerBlock, chunkSize, reset);
				chunk[i].Translate(chunk[i].getMatX() * blockSize * SQ_ASPECT_RATIO, chunk[i].getMatY() * blockSize);
				chunk[i].Attach();
		}

		for (int i = 0; i < 4; i++)
		{
			str[i] = '\0';
		}
	}

	this->isAlloaced = true;

	this->TranslateChunkSize(nodeID, stripID);

	this->Translate(listCurrentTranslate[0], listCurrentTranslate[1]);

	chunkFile.close();
}
