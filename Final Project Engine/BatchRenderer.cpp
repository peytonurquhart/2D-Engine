#include "BatchRenderer.h"


RendererObject::RendererObject()
{
	float mesh[MAX_FLOATS];
	unsigned int indeces[MAX_INDECES];

	for (int i = 0; i < MAX_FLOATS; i++)
	{
		mesh[i] = 0.0f;

		if (i < MAX_INDECES)
		{
			indeces[i] = 0.0f;
		}
	}

	batch.ReInit(8000, 2, sizeof(float), MAX_FLOATS, mesh, true, MAX_INDECES, indeces, 8, GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, 2);

	batch.Bind();

	glVertexAttribPointer(batch.getVaPointerIndex(), 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	glEnableVertexAttribArray(batch.getVaPointerIndex());
}

void RendererObject::Flush()
{
	float *mTemp = batch.getMatrix();
	unsigned int *iTemp = batch.getIndeces();

	for (int i = 0; i < MAX_FLOATS; i++)
	{
		mTemp[i] = 0.0f;

		if (i < MAX_INDECES)
		{
			iTemp[i] = 0.0f;
		}
	}
}

void RendererObject::Push(Chunk **scene, int numChunksInScene, blockType target, Texture *texPointer)
{
	float *mTemp = batch.getMatrix();
	unsigned int *iTemp = batch.getIndeces();

	int nChunks = 0;
	Chunk *cTemp = nullptr;

	Block *blx = nullptr;
	float *mtx = nullptr;
	unsigned int *ind = nullptr;

	int k = 0;
	int g = 0;
	int m = 0;

	fstream log;
	log.open("C:/Users/Peyton/Documents/Visual Studio 2015/Projects/openGl/2D Engine/Final Project Engine/Logs/matrixlog.txt", std::ios_base::in);
	stringstream stm;
	string str;

	/* blocks are not being limited by blockType yet! */

	for (nChunks = 0, blx = nullptr, mtx = nullptr, ind = nullptr; nChunks < numChunksInScene; nChunks++)
	{
		cTemp = scene[nChunks];

		blx = cTemp->getBlocks();

		int cSize = cTemp->getChunkSize() * cTemp->getChunkSize();



		// i indexes the current block
		for (int i = 0; i < cSize; i++)
		{
			/*if the blocktype is a match*/
			if (blx[i].getBlockType() == target)
			{

				mtx = blx[i].getMatrix();
				ind = blx[i].getIndeces();

				stm << mtx << " - " << ind << "\n";
				str = stm.str();

				log.write(str.c_str(), 100);


				int numFloats = blx[i].getNumFloats();
				int numIndeces = blx[i].getNumIndeces();


				// j indexes the float in each block
				// k is fills the mesh and is not updates for each float that is pushed, but never reset
				for (int x = 0; x < numFloats; x++, k++)
				{
					mTemp[k] = mtx[x];
				}

				// j indexes the index in each block
				// g fills the indeces and is never reset
				// m tracks each block looped through each chunk and is never reset
				for (int j = 0; j < numIndeces; j++, g++)
				{
					iTemp[g] = ind[j] + (m * 4);
				}

				m++;

			}

		}

	}

	currentTexPointer = texPointer;

}

void RendererObject::Draw()
{
	currentTexPointer->Use();

	batch.Bind();

	batch.BufferVertex();

	batch.BufferIndeces();

	batch.Draw();
}


Renderer::Renderer(int numBatches, blockType *targets, Texture **texPointers)
{
	this->numBatches = numBatches;
	this->targets = targets;
	this->texPointers = texPointers;

	renderList = new RendererObject[numBatches];
}

void Renderer::PushAll(Chunk **scene, int numChunksInScene)
{
	for (int i = 0; i < numBatches; i++)
	{
		renderList[i].Push(scene, numChunksInScene, targets[i], texPointers[i]);
	}
}

void Renderer::DrawAll()
{
	for (int i = 0; i < numBatches; i++)
	{
		renderList[i].Draw();
	}
}

void Renderer::FlushAll()
{
	for (int i = 0; i < numBatches; i++)
	{
		renderList[i].Flush();
	}
}