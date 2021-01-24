#include "Chunk.h"

Chunk::Chunk(int chunkSize, const blockType type, Texture *texPointers, float blockSize, int numTexturesPerBlock)
{
	this->chunkSize = chunkSize;
	this->blockSize = blockSize;

	chunk = new Block[chunkSize * chunkSize];

	origin[0] = 0.0f;
	origin[1] = 0.0f;

	bool reset = false;

	for (int i = 0; i < (chunkSize * chunkSize); i++)
	{
		if (i == 0)
			reset = true;
		else
			reset = false;

		chunk[i].Init(type, texPointers, blockSize, numTexturesPerBlock, chunkSize, reset);
		chunk[i].Translate(chunk[i].getMatX() * blockSize * SQ_ASPECT_RATIO, chunk[i].getMatY() * blockSize);
		chunk[i].Attach();
	}
}

Chunk::Chunk(const string &string, int chunkSize, float blockSize, int numTexturesPerBlock)
{
	if (string == "nullchunk")
	{

		this->chunkSize = chunkSize;
		this->blockSize = blockSize;

		chunk = new Block[chunkSize * chunkSize];

		origin[0] = 0.0f;
		origin[1] = 0.0f;

		bool reset = false;

		for (int i = 0; i < (chunkSize * chunkSize); i++)
		{
			if (i == 0)
				reset = true;
			else
				reset = false;

			chunk[i].Init("nullblock",reset, blockSize, chunkSize);
			chunk[i].Translate(chunk[i].getMatX() * blockSize * SQ_ASPECT_RATIO, chunk[i].getMatY() * blockSize);
			chunk[i].Attach();
		}

	}
	else
	{
		cout << "Invalid special chunk name: " << string << " ; Chunk could not be created" << endl;
	}
}

void Chunk::Init(const string &string, int chunkSize, float blockSize, int numTexturesPerBlock)
{
	if (string == "nullchunk")
	{

		this->chunkSize = chunkSize;
		this->blockSize = blockSize;

		chunk = new Block[chunkSize * chunkSize];

		origin[0] = 0.0f;
		origin[1] = 0.0f;

		bool reset = false;

		for (int i = 0; i < (chunkSize * chunkSize); i++)
		{
			if (i == 0)
				reset = true;
			else
				reset = false;

			chunk[i].Init("nullblock", reset, blockSize, chunkSize);
			chunk[i].Translate(chunk[i].getMatX() * blockSize * SQ_ASPECT_RATIO, chunk[i].getMatY() * blockSize);
			chunk[i].Attach();
		}

	}
	else
	{
		cout << "Invalid special chunk name: " << string << " ; Chunk could not be created" << endl;
	}
}


void Chunk::Init(int chunkSize, const blockType type, Texture *texPointers, float blockSize, int numTexturesPerBlock)
{
	this->chunkSize = chunkSize;
	this->blockSize = blockSize;

	chunk = new Block[chunkSize * chunkSize];

	origin[0] = 0.0f;
	origin[1] = 0.0f;


	bool reset = false;

	for (int i = 0; i < (chunkSize * chunkSize); i++)
	{
		if (i == 0)
			reset = true;
		else
			reset = false;

		chunk[i].Init(type, texPointers, blockSize, numTexturesPerBlock, chunkSize, reset);
		chunk[i].Translate(chunk[i].getMatX() * blockSize * SQ_ASPECT_RATIO, chunk[i].getMatY() * blockSize);
		chunk[i].Attach();
	}
}


void Chunk::Draw()
{
	if (!isEmpty())
	{
		for (int i = 0; i < (chunkSize * chunkSize); i++)
		{
			//if its not a null block draw it (null blocks have no matrix memory)
			if(chunk[i].getIsNullBlock() == false)
			chunk[i].Draw();
		}
	}
}

Block Chunk::grabBlock(int matX, int matY)
{
	int mX = 0, mY = 0;

	if (!isEmpty() && (matX < chunkSize && matY < chunkSize && matX >= 0 && matY >= 0))
	{
		for (int i = 0; i < (chunkSize * chunkSize); i++)
		{
			if (mX == matX && mY == matY)
			{
				if (chunk[i].getIsNullBlock() == false)
				{
					return chunk[i];
				}
			}

			mX++;

			if (mX == chunkSize)
			{
				mY++;
				mX = 0;
			}

		}
	}
	else
	{
		cout << "Invalid block grabbed, chunk was empty or the block was outside of range" << endl;
	}

	Block nb("nullblock", 0, 0);
	return nb;

}

Block * Chunk::grabBlockLocation(int matX, int matY)
{
	int mX = 0, mY = 0;

	if (!isEmpty() && (matX < chunkSize && matY < chunkSize && matX >= 0 && matY >= 0))
	{
		for (int i = 0; i < (chunkSize * chunkSize); i++)
		{
			if (mX == matX && mY == matY)
			{
				if (chunk[i].getIsNullBlock() == false)
				{
					return &chunk[i];
				}
				else
				{
					return nullptr;
				}
			}

			mX++;

			if (mX == chunkSize)
			{
				mY++;
				mX = 0;
			}

		}
	}
	else
	{
		cout << "Invalid block grabbed, chunk was empty or the block was outside of range" << endl;

		return nullptr;
	}
}


bool Chunk::isBlockAtIndex(int i, int j)
{
	int index = convertToSingleChunkIndex(i, j);

	if (chunk[index].getIsNullBlock() == false)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool Chunk::isBlockAtIndex(int singleIndex)
{

	if (chunk[singleIndex].getIsNullBlock() == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}


int Chunk::convertToSingleChunkIndex(int i, int j)
{
	int mX = 0, mY = 0;

	if (!isEmpty() && (i < chunkSize && j < chunkSize && i >= 0 && j >= 0))
	{
		for (int k = 0; k < (chunkSize * chunkSize); k++)
		{
			if (mX == i && mY == j)
			{
				return k;
			}

			mX++;

			if (mX == chunkSize)
			{
				mY++;
				mX = 0;
			}

		}
	}
	else
	{
		cout << "Invalid index converted, out of range" << endl;
		return -1;
	}
}

void Chunk::convertToDoubleChunkIndex(int ij[2], int index)
{
	int c = 0;

	for (int i = 0; i < chunkSize; i++)
	{
		for (int j = 0; j < chunkSize; j++)
		{
			if (c == index)
			{
				ij[0] = j;
				ij[1] = i;

 				return;
			}

			c++;
		}
	}
}

void Chunk::Translate(float amountx, float amounty)
{
	origin[0] += amountx * SQ_ASPECT_RATIO;
	origin[1] += amounty;

	if (!isEmpty())
	{
		for (int i = 0; i < getChunkSize() * getChunkSize(); i++)
		{
			chunk[i].Translate(amountx * SQ_ASPECT_RATIO, amounty);
		}

	}
}

void Chunk::TranslateChunkSize(int x, int y)
{
	origin[0] += (x * chunkSize * blockSize * SQ_ASPECT_RATIO);
	origin[1] += (y * chunkSize * blockSize);

	if (!isEmpty())
	{
		for (int i = 0; i < (getChunkSize() * getChunkSize()); i++)
		{
			chunk[i].Translate(x * chunkSize * blockSize * SQ_ASPECT_RATIO, y * chunkSize * blockSize);
		}

	}
}

Block * Chunk::UnAttachBlock(int i, int j)
{
	if (!isEmpty())
	{
		Block *temp = new Block;

		float o[2];
			
			*temp = grabBlock(i, j);

			//sets the blocks personal status to unattached, can be set to attached when it is part of another chunks memory so it can be identified
			temp->unAttach();

			getOrigin(o);

			//setting this blocks place in the chunk to a nullblock
			Block nb("nullblock", blockSize, chunkSize);
			chunk[convertToSingleChunkIndex(i, j)] = nb;

			chunk[convertToSingleChunkIndex(i, j)].MoveToOrigin();
			chunk[convertToSingleChunkIndex(i, j)].Translate(i * blockSize * SQ_ASPECT_RATIO + o[0], j * blockSize + o[1]);
		

		//returns a pointer to the free block
		return temp;
	}

	return nullptr;
}

bool Chunk::AttachBlock(Block *block, int i, int j)
{
	//if the requested chunk position already has a block in it
	if (isBlockAtIndex(i, j) == true)
	{
		cout << "block at index" << endl;
		return false;
	}
	else
	{

		if (block->isAlloced())
		{

			float o[2];

			int index = convertToSingleChunkIndex(i, j);
			chunk[index] = *block;

			getOrigin(o);

			chunk[index].MoveToOrigin();
			chunk[index].Translate(i * blockSize * SQ_ASPECT_RATIO + o[0], j * blockSize + o[1]);

			chunk[index].Attach();

			return true;

			//	delete block;
		}

	}

	return false;
}

bool Chunk::AttachBlock(Block *block, int singleIndex)
{
	if (isBlockAtIndex(singleIndex) == true)
	{
		cout << "block at index" << endl;
		return false;
	}
	else
	{
		if (block->isAlloced())
		{

			float o[2];
			int ij[2];
			convertToDoubleChunkIndex(ij, singleIndex);

			chunk[singleIndex] = *block;

			getOrigin(o);

			chunk[singleIndex].MoveToOrigin();
			chunk[singleIndex].Translate(ij[0] * blockSize * SQ_ASPECT_RATIO + o[0], ij[1] * blockSize + o[1]);

			chunk[singleIndex].Attach();

			//	delete block;

			return true;

		}
	}

	return false;
}

void Chunk::getBestIndexForPoint(float validPoint[], int *j)
{
	float minDist = blockSize * (chunkSize + 1);
	int minIndex = -1;

	if (isPointInChunk(validPoint))
	{

		for (int i = 0; i < (chunkSize * chunkSize); i++)
		{

			if (chunk[i].isPointInBlock(validPoint) == true)
			{
				*j = i;
				return;
			}
		}

	}
}

bool Chunk::AttachBlock(Block *block, float validPoint[2])
{

	if (isPointInChunk(validPoint))
	{
		int bestIndex = -1;
		getBestIndexForPoint(validPoint, &bestIndex);

		if ((chunk[bestIndex].getIsNullBlock()) == true)
		{
			if (AttachBlock(block, bestIndex))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

}

bool Chunk::isPointInChunk(float point[])
{
	float distancepmy = blockSize * chunkSize;
	distancepmy = (distancepmy - (distancepmy / chunkSize));

	float distancepmx = blockSize * chunkSize * SQ_ASPECT_RATIO;
	distancepmx = (distancepmx - (distancepmx / chunkSize));

	float o[2];
		
	getOrigin(o);

	if ((point[0] >= (o[0] - (blockSize * SQ_ASPECT_RATIO))) && (point[0] < o[0] + distancepmx))
	{
		if ((point[1] >= (o[1] - blockSize)) && point[1] < o[1] + distancepmy)
		{
			return true;
		}
	}

		return false;
}

Block * Chunk::grabBlockLocation(float validPoint[2], bool isBuffer, float safetyRatio)
{
	int bestIndex = 0, i = 0;

	float minDist = blockSize * (chunkSize + 1);


	if (isPointInChunk(validPoint) == true)
	{


		//check if a point is inside a block
		for (i = 0; i < (chunkSize * chunkSize); i++)
		{
			if (chunk[i].isPointInBlock(validPoint))
			{
				return &chunk[i];
			}
		}

		if (isBuffer)
		{

			//find the best block in the chunk if not
			for (i = 0; i < (chunkSize * chunkSize); i++)
			{
				if (chunk[i].getDistanceFromPoint(validPoint) < minDist)
				{
					minDist = chunk[i].getDistanceFromPoint(validPoint);
					bestIndex = i;
				}
			}

			//decide what amount of accuracy is requested and return the best block or return nullptr
			if (minDist < blockSize * safetyRatio)
			{
				return &chunk[bestIndex];
			}
			else
			{
				cout << "ERROR: invalid block grabbed / outside safety ratio, no block to return" << endl;
				cout << "mindistance: " << minDist << endl;
				cout << "buffer (block * sr): " << blockSize * safetyRatio << endl << endl;
				return nullptr;
			}

		}

	}
	else
	{
		return nullptr;
	}

}

bool Chunk::isTouchingChunk(Hitbox *boxes, int numBoxes)
{
	Hitbox * temp;

	for (int j = 0; j < numBoxes; j++)
	{
		for (int i = 0; i < (chunkSize * chunkSize); i++)
		{
			temp = chunk[i].getHitBoxPointer();

			if (chunk[i].getIsNullBlock() == false)
			{
				if (boxes[j].isOverlap(*temp))
				{
					return true;
				}
			}
		}
	}

	return false;
}

bool Chunk::willBeTouchingChunk(Hitbox *boxes, int numBoxes, float speed, const string &direction, int numMovesInDirection)
{
	bool var = false;

	for (int i = 0; i < numBoxes; i++)
	{
		if (direction == "up")
		{
			boxes[i].Translate(0, speed * numMovesInDirection);
		}
		if (direction == "down")
		{
			boxes[i].Translate(0, -1 * speed * numMovesInDirection);
		}
		if (direction == "left")
		{
			boxes[i].Translate(-1 * speed * numMovesInDirection, 0);
		}
		if (direction == "right")
		{
			boxes[i].Translate(speed * numMovesInDirection, 0);
		}
	}

	var = isTouchingChunk(boxes, numBoxes);

	for (int i = 0; i < numBoxes; i++)
	{
		if (direction == "down")
		{
			boxes[i].Translate(0, speed * numMovesInDirection);
		}
		if (direction == "up")
		{
			boxes[i].Translate(0, -1 * speed * numMovesInDirection);
		}
		if (direction == "right")
		{
			boxes[i].Translate(-1 * speed * numMovesInDirection, 0);
		}
		if (direction == "left")
		{
			boxes[i].Translate(speed * numMovesInDirection, 0);
		}
	}

	return var;
}