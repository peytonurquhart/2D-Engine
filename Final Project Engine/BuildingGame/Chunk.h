#pragma once

#include "Init.h"
#include "Block.h"

#define MAXBLOCKTEXTURES 64

class Chunk
{
public:
	Chunk & operator=(Chunk &old);

	Chunk(const Chunk &oldChunk);

	~Chunk() { if (isAlloaced) { delete[] chunk; } }

	Chunk(int chunkSize, const blockType type, Texture *texPointers, float blockSize = 0.1, int numTexturesPerBlock = 1);

	Chunk() { chunk = nullptr; chunkSize = 0; return; }

	Chunk(const string &string, int chunkSize, float blockSize, int numTexturesPerBlock);

	void Init(const string &string, int chunkSize, float blockSize, int numTexturesPerBlock);

	void Init(int chunkSize, const blockType type, Texture *texPointers, float blockSize = 0.1, int numTexturesPerBlock = 1);

	void InitFromFile(const string &directory, int chunkSize, float blockSize, Texture *texPointers[MAXBLOCKTEXTURES], int numTextures, int stripID, int nodeID, float *listCurrentTranslate);

	//displays the chunk on the screen including all of its blocks unique locations
	void Draw();

	//returns true if the chunk is not yet initialized
	bool isEmpty() { if (chunk == nullptr || !isAlloaced) { return true; } return false; }

	//returns a deep copy of a block at the chuck x and y
	Block grabBlock(int matX, int matY);

	//returns the address to a block at the chunk x and y
	Block * grabBlockLocation(int matX, int matY);

	//POINT MUST BE IN CHUNK OR RETURNS NULL - safetyRatio 1 is most safe, 0 is least safe
	Block * grabBlockLocation(float validPoint[2], bool isBuffer = false, float safetyRatio = 0.0f);

	//returns the total number of blocks in the individual chunk
	int getNumBlocks() { return chunkSize * chunkSize; }

	//returns the chunksize ( sqrt(numblocks) )
	int getChunkSize() { return this->chunkSize; }

	//translates the entire chunk an amount x and y
	void Translate(float amountx, float amounty);

	//will translate an amount of positive or negative chunksizes x and y ----> this is a free translation
	void TranslateChunkSize(int x, int y);

	//removes a block from a chunk and returns a pointer to the free block (a new block in memory), replaces it with a nullblock
	//this new block in memory should be attached to a new chunk and freed from the players personal block memory once it is placed and forgotten
	Block * UnAttachBlock(int i, int j);

	//converts a double index to a single chunk index
	int convertToSingleChunkIndex(int i, int j);

	//converts a single chunk index to its matrix type index
	void convertToDoubleChunkIndex(int ij[2], int index);

	//attaches a block to a position in the 2d chunk matrix
	bool AttachBlock(Block *block, int i, int j);

	//attaches a block at a chunk array index
	bool AttachBlock(Block *block, int singleIndex);

	//attaches a block at a point 
	//precondition: POINT MUST BE IN THE CHUNK
	bool AttachBlock(Block *block, float validPoint[2]);

	//returns false if the block at the chunks index is null
	bool isBlockAtIndex(int i, int j);

	//returns true if there is a block other than the null block at a chunks single index, false otherwise
	bool isBlockAtIndex(int singleIndex);

	//indirectly returns a vector to block 0,0s bottom left corner (the chunks origin)
	void getOrigin(float origin[2]) { origin[0] = this->origin[0]; origin[1] = this->origin[1]; }

	//returns true if the given point is inside the chunk, false otherwise
	bool isPointInChunk(float point[]);

	//indirectly returns the best index in a chunk given a valid point with the distance formula
	//WARNING: not reccomended and not very accurate for some reason
	void getBestIndexForPoint(float validPoint[], int *j);

	
	//returns true if one of the boxes is touching the chunk only including blocks that are not null (LINEAR WITHOUT NULLBLOCK CHECK, O(n^2) to chunksize WITHOUT)
	bool isTouchingChunk(Hitbox *boxes, int numBoxes, bool nullBlockCheck = false);

	//1 = right, 2 = up, 3 = left, 4 = down  /* returns true if the proposed translation will be touching the chunk
	bool willBeTouchingChunk(Hitbox *boxes, int numBoxes, float speed, int direction, int numMovesInDirection, bool nullBlockCheck = true);

	void calcMidPoint(float m[2]);

	/*calculates the midpoint as if the chunk has completed all queued translations*/
	void calcMidPointIncludingQueuedTranslations(float m[2]);

	/*would the chunk be within this bound if the translations were updated*/
	bool WouldBeInXBound(float pm);

	/* translation queue */
	void pushTranslation(float x, float y) { PendingTranslate[0] += x; PendingTranslate[1] += y; }
	void popTranslationQueue(float t[2]) { t[0] = PendingTranslate[0]; t[1] = PendingTranslate[1]; PendingTranslate[0] = 0; PendingTranslate[1] = 0; }
	void clearTranslationQueue() { PendingTranslate[0] = 0.0f; PendingTranslate[1] = 0.0f; }
	void translateFromQueue() { float t[2]; popTranslationQueue(t); Translate(t[0], t[1]); }

	/*returns a pointer to the chunks pending x/y translation*/
	float *getPendingTranslate() { return PendingTranslate; }

	/* write chunk to a file and then clear its RAM memory if shouldUnallocate*/
	bool saveToFile(const string &directory, int stripID, int NodeID, bool shouldUnallocate = false);

	bool getIsAlloced() { return isAlloaced; }

	float getBlockSize() { return this->blockSize; }

	Block *getBlocks() { return chunk; }

private:
	
	/*does the chunk contain memory to be rendered or does it exist in a file only*/
	bool isAlloaced;

	int chunkSize;

	float blockSize;

	Block *chunk;

	float origin[2];

	float PendingTranslate[2];

	fstream chunkFile;
};