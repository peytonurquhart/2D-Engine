#pragma once

#include "Init.h"

#define MAX_TEXTURES_PER_BLOCK

enum blockType 
{
	grassBlock, 
	stoneBlock, 
	woodBlock, 
	leafBlock
};


/*
		Block

		- Each block which is spawned is given a static block id (x and y) coordinate by which it may be identified

		- With each individual chunk the static block ids may be reset and the blocks may be sorted by chunk as opposed to individually

		- NULLBLOCKS are ALWAYS null blocks, they are just place holders, is you need to alter this think about the blocks attach status

*/


class Block
{
public:

	~Block() { if (block->getIsAlloced() && hb->getIsAlloced()) { delete block; delete hb; } }

	//deep copies a new block from its matrix roots
	Block(Block &oldBlock);

	Block(blockType blockID, Texture * texPointer, float blockSize = 0.1, unsigned int numTextures = 1, int chunkSize = 16, bool staticReset = false);

	Block(const string nb, bool staticReset, float blockSize = 0, float chunkSize = 0);

	void Init(const string nb, bool staticReset, float blockSize = 0, float chunkSize = 0);

	Block() { return; }

	void Init(blockType blockID, Texture * texPointer, float blockSize = 0.1, unsigned int numTextures = 1, int chunkSize = 16, bool staticReset = false);

	void Draw();

	//translates block and hitbox x and y
	void Translate(float x, float y) { block->Translate(x, y); hb->Translate(x, y); }

	//swings (normal swing for free swing)
	void Swing(float theta, bool free = false) { if (!free) { block->Swing(theta); hb->Swing(theta); } else { block->FreeSwing(theta); hb->FreeSwing(theta); } } 

	//rotates (normal rotate or free rotate)
	void Rotate(float theta, bool free = false) { if (!free) { block->Rotate(theta); /*hb.Rotate(theta);*/ } else { block->FreeRotate(theta); hb->FreeRotate(theta); } }

	//returns the blocks current rotation not including the free rotations
	float getCurrentRotation() { return block->getCurrentRotation(); }

	//gets the blocks x a position in its current chunk
	int getMatX() { return this->matX; }

	//gets the blocks y position in its current chunk
	int getMatY() { return this->matY; }

	void getOrigin(float o[2]) { hb->getOrigin(o); }

	void getOrigin(float o[2], int v) { block->getOrigin(o, v); }

	void printInfo() { cout << "chunk loc: " << matX << "," << matY << endl; }

	void setTexturePointer(Texture *newTex) { this->textures = newTex; }
	void setBlockType(blockType newType) { this->blockID = newType; }
	void setBlockType(blockType newType, Texture *newTex) { setBlockType(newType), setTexturePointer(newTex); return; }

	void unAttach() { isAttached = false; }
	void Attach() { isAttached = true; }

	bool getIsAttached() { return isAttached; }
	bool getIsNullBlock() { return isNullBlock;}

	RectangleT getRectangle() { return *(this->block); }
	Hitbox getHitBox() { return *(this->hb); }

	void displayShapeAttributes() { block->DispAllAttributes(); }

	void MoveToOrigin();

	bool isPointInBlock(float point[2]);

	float getDistanceFromPoint(float point[2]);

	bool isAlloced() { return block->getIsAlloced(); }

	Hitbox * getHitBoxPointer() { return hb; }

	blockType getBlockType() { return blockID; }

	Texture *getTex() { return textures; }

	unsigned int getNumTex() { return numTextures; }

	float *getMatrix() { return block->getMatrix(); }
	unsigned int *getIndeces() { return block->getIndeces(); }
	int getNumFloats() { return block->getNumFloats(); }
	int getNumIndeces() { return block->getNumIndeces(); }


private:

	/* Size of the origional chunk this block belonged to (matters to how it is identified as a unique block in that chunk)*/
	int chunkSize;

	/* Unique X/Y Coordinates Relative to which chunk blocks are in to make sorting of unique blocks logrithmic*/
	int matX;
	int matY;

	/* Current Block Type of this block*/
	blockType blockID;

	/* Rectangle Which Represents The Block*/
	RectangleT  * block;

	/* HitBox Which follows the Block*/
	Hitbox  * hb;

	/* The Number of Textures Given by The Texture Pointer*/
	unsigned int numTextures;

	/* Current texture of the block for the frame (should be 0 unless broken, on fire, stepped on, etc)*/
	unsigned int currentTextureIndex;

	/* Size of the block (should generally be uniform for all blocks) */
	float blockSize;

	//is the block currently attached to a chunk
	bool isAttached;

	//a bloack which is nothing and represents nothing but can be used to hold a place in a chunks memory
	bool isNullBlock;

	/*Pointer to an array of textures for the block
	
	textures[0] = main texture
	textures[1 - 4] = breaking textures
	textures[5 + n] = misc textures
	*/
	Texture *textures;

};

