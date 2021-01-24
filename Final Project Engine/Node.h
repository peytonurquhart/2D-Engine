#pragma once
#include "Init.h"
#include "BuildingGame\Chunk.h"

class Node
{
public:
	Node();

	Node(Chunk &newChunk);

	Chunk *getChunkPointer() {  return this->chunk;  }

	void setChunkPointer(Chunk * newChunk) { this->chunk = newChunk;  }

	void setNodeID(int newID) {this->NodeID = newID; }
	int getNodeID() { return NodeID; }

	Node *getRight() { return this->pRight; }

	Node *getLeft() { return this->pLeft; }

	void setRight(Node *newPtr) { this->pRight = newPtr; }

	void setLeft(Node *newPtr) { this->pLeft = newPtr; }

	bool isRightNull() { if (pRight == nullptr) {return true; } return false; }

	bool isLeftNull() { if (pLeft == nullptr) { return true; } return false; }

	int ID() { return NodeID; }

private:

	Chunk *chunk;

	Node *pLeft;
	Node *pRight;

	int NodeID;

};