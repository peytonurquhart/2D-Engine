#include "Node.h"

Node::Node()
{
	this->chunk = nullptr;
	this->pLeft = nullptr;
	this->pRight = nullptr;
	this->NodeID = 0;

}

Node::Node(Chunk &newChunk)
{
	this->chunk = &newChunk;
	this->NodeID = 0;
}
