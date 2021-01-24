#include "Block.h"


float absVal(float val)
{
	if (val > 0)
	{
		return val;
	}
	else if (val < 0)
	{
		return val * -1;
	}
}


Block::Block(blockType blockID, Texture * texPointer, float blockSize, unsigned int numTextures, int chunkSize, bool staticReset)
{
	static int cX = 0, cY = 0;

	if (staticReset)
	{
		cX = 0;
		cY = 0;
	}

	matX = cX;
	cX++;

	matY = cY;

	if (cX == chunkSize)
	{
		cY++;
		cX = 0;
	}


	this->chunkSize = chunkSize;
	this->blockID = blockID;
	this->textures = texPointer;
	this->numTextures = numTextures;
	this->blockSize = blockSize;
	this->currentTextureIndex = 0;
	this->isNullBlock = false;

	block.Init(blockSize, blockSize, 0.0f);
	hb.Init(blockSize);

	block.MoveToOrigin();
	hb.MoveToOrigin();
}

void Block::Init(blockType blockID, Texture * texPointer, float blockSize, unsigned int numTextures, int chunkSize, bool staticReset)
{
	static int cX = 0, cY = 0;

	if (staticReset)
	{
		cX = 0;
		cY = 0;
	}

	matX = cX;
	cX++;

	matY = cY;

	if (cX == chunkSize)
	{
		cY++;
		cX = 0;
	}


	this->chunkSize = chunkSize;
	this->blockID = blockID;
	this->textures = texPointer;
	this->numTextures = numTextures;
	this->blockSize = blockSize;
	this->currentTextureIndex = 0;
	this->isNullBlock = false;

	block.Init(blockSize, blockSize, 0.0f);
	hb.Init(blockSize);

	block.MoveToOrigin();
	hb.MoveToOrigin();
}


Block::Block(Block &oldBlock)
{
	this->chunkSize = oldBlock.chunkSize;

	this->matX = oldBlock.matX;
	this->matY = oldBlock.matY;


	this->blockID = oldBlock.blockID;

	this->block = oldBlock.getRectangle();


	this->hb = oldBlock.getHitBox();


	this->numTextures = oldBlock.numTextures;


	this->currentTextureIndex = oldBlock.currentTextureIndex;


	this->blockSize = oldBlock.blockSize;


	this->isAttached = oldBlock.isAttached;


	this->isNullBlock = oldBlock.isNullBlock;

	this->textures = oldBlock.textures;
}

Block::Block(const string nb, bool staticReset, float blockSize, float chunkSize)
{
	static int cX = 0, cY = 0;

	if (staticReset)
	{
		cX = 0;
		cY = 0;
	}

	matX = cX;
	cX++;

	matY = cY;

	if (cX == chunkSize)
	{
		cY++;
		cX = 0;
	}


	if (nb == "nullblock")
	{
		this->isNullBlock = true;

		this->chunkSize = chunkSize;
		this->blockID = (blockType)-1;
		this->textures = nullptr;
		this->numTextures = 0;
		this->blockSize = blockSize;
		this->currentTextureIndex = 0;
		this->isAttached = false;

		block.Init(blockSize, blockSize, 0.0f);
		hb.Init(blockSize);

		block.MoveToOrigin();
		hb.MoveToOrigin();
	}
	else
	{
		cout << "invalid special block initialization: " << nb << endl;
 	}
}


void Block::Init(const string nb, bool staticReset, float blockSize, float chunkSize)
{

	static int cX = 0, cY = 0;

	if (staticReset)
	{
		cX = 0;
		cY = 0;
	}

	matX = cX;
	cX++;

	matY = cY;

	if (cX == chunkSize)
	{
		cY++;
		cX = 0;
	}

	if (nb == "nullblock")
	{
		this->isNullBlock = true;

		this->chunkSize = chunkSize;
		this->blockID = (blockType)-1;
		this->textures = nullptr;
		this->numTextures = 0;
		this->blockSize = blockSize;
		this->currentTextureIndex = 0;
		this->isAttached = false;

		block.Init(blockSize, blockSize, 0.0f);
		hb.Init(blockSize);

		block.MoveToOrigin();
		hb.MoveToOrigin();
	}
	else
	{
		cout << "invalid special block initialization: " << nb << endl;
	}
}


void Block::Draw()
{

	textures[currentTextureIndex].Use();

	block.Bind();
	block.BufferVertex();
	block.Draw();
	block.Unbind();

	textures[currentTextureIndex].unBind();

}

void Block::MoveToOrigin()
{
	float o[2];

	block.getOrigin(o);

	o[0] = o[0] * -1;
	o[1] = o[1] * -1;

	block.Translate(o[0], o[1]);
	hb.Translate(o[0], o[1]);
}

bool Block::isPointInBlock(float point[2])
{
	float o[2];
	hb.getOrigin(o);

	float distancepmy = blockSize * 1;
	distancepmy = (distancepmy - (distancepmy / 1));

	float distancepmx = blockSize * 1 * SQ_ASPECT_RATIO;
	distancepmx = (distancepmx - (distancepmx / 1));

	if ((point[0] >= (o[0] - (blockSize * SQ_ASPECT_RATIO))) && (point[0] < o[0] + distancepmx))
	{
		if ((point[1] >= (o[1] - blockSize)) && point[1] < o[1] + distancepmy)
		{
			return true;
		}
	}

	return false;
}

float Block::getDistanceFromPoint(float point[2])
{
	float mids[2];

	hb.CalcMidPoint(mids);

	return sqrt(pow((point[0] - mids[0]), 2) + pow((point[1] - mids[1]), 2));
}
