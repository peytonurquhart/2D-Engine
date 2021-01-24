#include "List.h"

ChunkStrip::ChunkStrip(int yLevel)
{
	pHead = nullptr;

	lLast = nullptr;

	rLast = nullptr;

	numInScene = 0;

	this->yLevel = yLevel;
}

void ChunkStrip::Init(int yLevel)
{
	pHead = nullptr;

	lLast = nullptr;

	rLast = nullptr;

	numInScene = 0;

	this->yLevel = yLevel;
}

void ChunkStrip::printXMidpoints()
{
	cout << endl;

	Node *nTemp = nullptr;
	Node *pL = nullptr, *pR = nullptr;
	Chunk * cTemp = nullptr;
	float o[2];
	float *p = nullptr;

	nTemp = pHead;
	cTemp = nTemp->getChunkPointer();
	cTemp->calcMidPoint(o);
	p = cTemp->getPendingTranslate();

	cout << "h: " << o[0] << " - pending: " << p[0] << endl;

	pL = pHead;
	pR = pHead;

	for (int i = 1; pL->getLeft() != nullptr && pR->getRight() != nullptr; i++)
	{
		pL = pL->getLeft();
		pR = pR->getRight();

		cTemp = pR->getChunkPointer();
		cTemp->calcMidPoint(o);
		p = cTemp->getPendingTranslate();

		cout << i << " : " << o[0] << " - pending: " << p[0] << endl;



		cTemp = pL->getChunkPointer();
		cTemp->calcMidPoint(o);
		p = cTemp->getPendingTranslate();

		cout << "n" << i << " : " << o[0] << " - pending: " << p[0] << endl;
	}

	cout << endl;

}

void ChunkStrip::printXOrigins()
{
	Node *nTemp = nullptr;
	Node *pL = nullptr, *pR = nullptr;
	Chunk * cTemp = nullptr;
	float o[2];
	float *p = nullptr;

	nTemp = pHead;
	cTemp = nTemp->getChunkPointer();
	cTemp->getOrigin(o);
	p = cTemp->getPendingTranslate();

	cout << "h: " << o[0] << " - pending: " << p[0] << endl;

	pL = pHead;
	pR = pHead;

	for (int i = 1; pL->getLeft() != nullptr && pR->getRight() != nullptr; i++)
	{
		pL = pL->getLeft();
		pR = pR->getRight();

		cTemp = pR->getChunkPointer();
		cTemp->getOrigin(o);
		p = cTemp->getPendingTranslate();

		cout << i << " : " << o[0] << " - pending: " << p[0] << endl;



		cTemp = pL->getChunkPointer();
		cTemp->getOrigin(o);
		p = cTemp->getPendingTranslate();

		cout << i << " : " << o[0] << " - pending: " << p[0] << endl;
	}

}

void ChunkStrip::insertAtEnd(int pm, int chunkSize, const blockType type, Texture *texPointers, float blockSize, int numTexturesPerBlock)
{
	if (!isEmpty())
	{
		int id = 0;

		Chunk *newChunk = nullptr;
		newChunk = new Chunk(chunkSize, type, texPointers, blockSize, numTexturesPerBlock);

		Node *newNode = nullptr;
		newNode = new Node();
		newNode->setChunkPointer(newChunk);


		switch (pm)
		{
		case 1:
			/*the id for the new node will be the node before it plus 1*/
			id = rLast->getNodeID() + 1;

			/*the previous last nodes right node is the one we are inserting*/
			rLast->setRight(newNode);

			/*newnode is pointing right to null*/
			newNode->setRight(nullptr);

			/*setting the new nodes id*/
			newNode->setNodeID(id);

			/*translating the new node to is origin*/
			newChunk->TranslateChunkSize(id, yLevel);

			/*translating the node based on the position of the camera*/
			newChunk->Translate(currentTranslate[0], currentTranslate[1]);

			/*the new node is the new last node*/
			rLast = newNode;
			break;
		case -1:
			id = lLast->getNodeID() - 1;

			lLast->setLeft(newNode);

			newNode->setLeft(nullptr);

			newNode->setNodeID(id);

			newChunk->TranslateChunkSize(id, yLevel);

			newChunk->Translate(currentTranslate[0], currentTranslate[1]);

			lLast = newNode;
			break;
		}

	}
	else
	{
		cout << "ERROR: insertAtEnd() can only take pm values of -1 or 1: insert failed" << endl;
		return;
	}
}

void ChunkStrip::insertAtEnd(int pm, const string &command, int chunksize, float blocksize, int numTexturesPerBlock)
{
	if (!isEmpty())
	{
		if (command == "nullchunk")
		{
			int id = 0;

			Chunk *newChunk = nullptr;
			newChunk = new Chunk("nullchunk", chunksize, blocksize, numTexturesPerBlock);

			Node *newNode = nullptr;
			newNode = new Node();
			newNode->setChunkPointer(newChunk);

			switch (pm)
			{
			case 1:
				/*the id for the new node will be the node before it plus 1*/
				id = rLast->getNodeID() + 1;

				/*the previous last nodes right node is the one we are inserting*/
				rLast->setRight(newNode);

				/*newnode is pointing right to null*/
				newNode->setRight(nullptr);

				/*setting the new nodes id*/
				newNode->setNodeID(id);

				/*translating the new node to is origin*/
				newChunk->TranslateChunkSize(id, yLevel);

				/*translating the node based on the position of the camera*/
				newChunk->Translate(currentTranslate[0], currentTranslate[1]);

				/*the new node is the new last node*/
				rLast = newNode;
				break;
			case -1:
				id = lLast->getNodeID() - 1;

				lLast->setLeft(newNode);

				newNode->setLeft(nullptr);

				newNode->setNodeID(id);

				newChunk->TranslateChunkSize(id, yLevel);

				newChunk->Translate(currentTranslate[0], currentTranslate[1]);

				lLast = newNode;
				break;
			}


		}
		else
		{
			cout << "ERROR: invalid command in chunklist::insertAtEnd(): " << command << endl;
		}
	}

}

void ChunkStrip::Push(int pm, int chunkSize, const blockType type, Texture *texPointers, float blockSize, int numTexturesPerBlock)
{
	Chunk *newChunk = nullptr;
	newChunk = new Chunk(chunkSize, type, texPointers, blockSize, numTexturesPerBlock);

	Node *newNode = nullptr;
	newNode = new Node();
	newNode->setChunkPointer(newChunk);

	if (newChunk == nullptr)
	{
		cout << "ERROR: Chunk allocation failed: newChunk was nullptr" << endl;
	}
	else
	{
		switch (pm)
		{
		case 0:
			if (pHead == nullptr)
			{
				pHead = newNode;
				pHead->setNodeID(0);
				newChunk->TranslateChunkSize(0, yLevel);

				/**/
				this->lLast = pHead;
				this->rLast = pHead;

			}
			else
			{
				cout << "ERROR: invalid request to create head node: list was not empty" << endl;
			}
			break;
		case 1:
			if (pHead != nullptr)
			{
				Node *pTemp = nullptr;

				pTemp = pHead;

				int i = 1;
				for (i = 1; (pTemp->getRight() != nullptr); i++)
				{
					pTemp = pTemp->getRight();
				}

				pTemp->setRight(newNode);

				newNode->setRight(nullptr);

				newNode->setNodeID(i);

				newChunk->TranslateChunkSize(i, yLevel);

				newChunk->Translate(currentTranslate[0], currentTranslate[1]);

				/**/
				this->rLast = newNode;


			}
			else
			{
				cout << "ERROR: invalid request to create right node: list was empty" << endl;
			}

			break;
		case -1:
			if (pHead != nullptr)
			{
				Node *pTemp = nullptr;

				pTemp = pHead;

				int i = 1;
				for (i = 1; (pTemp->getLeft() != nullptr); i++)
				{
					pTemp = pTemp->getLeft();
				}

				pTemp->setLeft(newNode);

				newNode->setLeft(nullptr);

				newNode->setNodeID(i * -1);

				newChunk->TranslateChunkSize(i * -1, yLevel);

				newChunk->Translate(currentTranslate[0], currentTranslate[1]);

				/**/
				this->lLast = newNode;

			}
			else
			{
				cout << "ERROR: invalid request to create left node: list was empty" << endl;
			}

			break;
		default:
			cout << "ERROR: Invalid request during chunk list creation" << endl;
			return;
		}
	}
}

void ChunkStrip::Push(int pm, const string &command, int chunksize, float blocksize, int numTexturesPerBlock)
{

	if (command == "nullchunk")
	{

		Chunk *newChunk = nullptr;
		newChunk = new Chunk("nullchunk", chunksize, blocksize, numTexturesPerBlock);

		Node *newNode = nullptr;
		newNode = new Node();
		newNode->setChunkPointer(newChunk);

		if (newChunk == nullptr)
		{
			cout << "ERROR: Chunk allocation failed: newChunk was nullptr" << endl;
		}
		else
		{
			switch (pm)
			{
			case 0:
				if (pHead == nullptr)
				{
					pHead = newNode;
					pHead->setNodeID(0);
					newChunk->TranslateChunkSize(0, yLevel);

					/**/
					this->lLast = pHead;
					this->rLast = pHead;
				}
				else
				{
					cout << "ERROR: invalid request to create head node: list was not empty" << endl;
				}
				break;
			case 1:
				if (pHead != nullptr)
				{
					Node *pTemp = nullptr;

					pTemp = pHead;

					int i = 1;
					for (i = 1; (pTemp->getRight() != nullptr); i++)
					{
						pTemp = pTemp->getRight();
					}

					pTemp->setRight(newNode);

					newNode->setRight(nullptr);

					newNode->setNodeID(i);

					newChunk->TranslateChunkSize(i, yLevel);

					newChunk->Translate(currentTranslate[0], currentTranslate[1]);

					/**/
					this->rLast = newNode;

				}
				else
				{
					cout << "ERROR: invalid request to create right node: list was empty" << endl;
				}

				break;
			case -1:
				if (pHead != nullptr)
				{
					Node *pTemp = nullptr;

					pTemp = pHead;

					int i = 1;
					for (i = 1; (pTemp->getLeft() != nullptr); i++)
					{
						pTemp = pTemp->getLeft();
					}

					pTemp->setLeft(newNode);

					newNode->setLeft(nullptr);

					newNode->setNodeID(i * -1);

					newChunk->TranslateChunkSize(i * -1, yLevel);

					newChunk->Translate(currentTranslate[0], currentTranslate[1]);

					/**/
					this->lLast = newNode;

				}
				else
				{
					cout << "ERROR: invalid request to create left node: list was empty" << endl;
				}

				break;
			default:
				cout << "ERROR: Invalid request during chunk list creation" << endl;
				return;
			}
		}
	}
	else
	{
		cout << "ERROR: invalid command in chunklist::push(): " << command << endl;
	}
}


void ChunkStrip::Init(int sizePlusMinus, const string &command, int chunksize, float blocksize, int numtexturesperblock)
{
	if (command == "nullchunk")
	{
		Push(0, "nullchunk", chunksize, blocksize, numtexturesperblock);
		for (int i = 0; i < sizePlusMinus; i++)
		{
			Push(1, "nullchunk", chunksize, blocksize, numtexturesperblock);
			Push(-1, "nullchunk", chunksize, blocksize, numtexturesperblock);
		}
	}
	else
	{
		cout << "ERROR: invalid command in chunklist::init(): " << command << endl;
	}
}

void ChunkStrip::ChunkStrip::Init(int sizePlusMinus, int chunkSize, const blockType type, Texture *texPointers[MAXBLOCKTEXTURES], float blockSize, int numTexturesPerBlock)
{
	Push(0, chunkSize, type, texPointers[0], blockSize, numTexturesPerBlock);
	for (int i = 0; i < sizePlusMinus; i++)
	{
		Push(1, chunkSize, type, texPointers[0], blockSize, numTexturesPerBlock);
		Push(-1, chunkSize, type, texPointers[0], blockSize, numTexturesPerBlock);
	}
}

void ChunkStrip::QueueTranslations_Translate(float x, float y, const string & directory, float bound, Texture *texArray[MAXBLOCKTEXTURES], int numTextures)
{
	Node *pR = nullptr, *pL = nullptr;
	Chunk *temp = nullptr;
	int t = 0;

	currentTranslate[0] += x;
	currentTranslate[1] += y;

	if (!isEmpty())
	{
		pR = pHead->getRight();
		pL = pHead->getLeft();

		temp = pHead->getChunkPointer();
		temp->pushTranslation(x, y);

		if (temp->WouldBeInXBound(bound))
		{
			if (temp->getIsAlloced() == false)
			{
				temp->InitFromFile(directory, temp->getChunkSize(), temp->getBlockSize(), texArray, numTextures, yLevel, pHead->ID(), getCurrentTranslate());
			}
	
				temp->translateFromQueue();
				t++;
			
		}
		else
		{
			if (temp->getIsAlloced() == true)
			{
				temp->saveToFile(directory, yLevel, pHead->ID(), true);
			}
		}




		while (pR != nullptr && pL != nullptr)
		{
			temp = pR->getChunkPointer();
			temp->pushTranslation(x, y);

			if (temp->WouldBeInXBound(bound))
			{
				if (temp->getIsAlloced() == false)
				{
					temp->InitFromFile(directory, temp->getChunkSize(), temp->getBlockSize(), texArray, numTextures, yLevel, pR->ID(), getCurrentTranslate());
				}

					temp->translateFromQueue();
					t++;
				
			}
			else
			{
				if (temp->getIsAlloced() == true)
				{
					temp->saveToFile(directory, yLevel, pR->ID(), true);
				}
			}

			temp = pL->getChunkPointer();
			temp->pushTranslation(x, y);
			if (temp->WouldBeInXBound(bound))
			{
				if (temp->getIsAlloced() == false)
				{
					temp->InitFromFile(directory, temp->getChunkSize(), temp->getBlockSize(), texArray, numTextures, yLevel, pL->ID(), getCurrentTranslate());
				}

					temp->translateFromQueue();
					t++;
				
			}
			else
			{
				if (temp->getIsAlloced() == true)
				{
					temp->saveToFile(directory, yLevel, pL->ID(), true);
				}
			}


			pR = pR->getRight();
			pL = pL->getLeft();

		}

	}

	currentNumTranslationsMade = t;
}

void ChunkStrip::XCenterAll()
{
	Chunk *temp = pHead->getChunkPointer();
	float m[2];
	temp->calcMidPoint(m);

	Node *pR = nullptr, *pL = nullptr;

	temp->Translate(-1 * m[0] / SQ_ASPECT_RATIO, 0);

	pR = pHead->getRight();
	pL = pHead->getLeft();

	while (pR != nullptr && pL != nullptr)
	{
		temp = pR->getChunkPointer();
		temp->Translate(-1 * m[0] / SQ_ASPECT_RATIO, 0);

		temp = pL->getChunkPointer();
		temp->Translate(-1 * m[0] / SQ_ASPECT_RATIO, 0);

		pR = pR->getRight();
		pL = pL->getLeft();
	}

	/*DID THIS BY GUESS AND CHECK.. SORT OF UNSURE ABOUT IT*/
	currentTranslate[0] += m[0] / SQ_ASPECT_RATIO * -1;
}


void ChunkStrip::QueueTranslations(float x, float y)
{
	Node *pR = nullptr, *pL = nullptr;
	Chunk *temp = nullptr;


	if (!isEmpty())
	{
		pR = pHead->getRight();
		pL = pHead->getLeft();

		temp = pHead->getChunkPointer();
		temp->pushTranslation(x, y);



		while (pR != nullptr && pL != nullptr)
		{
			temp = pR->getChunkPointer();
			temp->pushTranslation(x, y);

			temp = pL->getChunkPointer();
			temp->pushTranslation(x, y);

			pR = pR->getRight();
			pL = pL->getLeft();
		}
	}
	else
	{
		cout << "cannot translate 0 chunks" << endl;
	}

	currentTranslate[0] += x;
	currentTranslate[1] += y;


}

void ChunkStrip::Translate(float bound)
{
	Node *pR = nullptr, *pL = nullptr;
	Chunk *temp = nullptr;

	int t = 0;

	if (!isEmpty())
	{
		pR = pHead->getRight();
		pL = pHead->getLeft();

		temp = pHead->getChunkPointer();
		if (temp->WouldBeInXBound(bound))
		{
			temp->translateFromQueue();
			t++;
		}

		while (pR != nullptr && pL != nullptr)
		{
			temp = pR->getChunkPointer();
			if (temp->WouldBeInXBound(bound))
			{
				temp->translateFromQueue();
				t++;
			}

			temp = pL->getChunkPointer();
			if (temp->WouldBeInXBound(bound))
			{
				temp->translateFromQueue();
				t++;
			}

			pR = pR->getRight();
			pL = pL->getLeft();
		}

		currentNumTranslationsMade = t;
	}
	else
	{
		cout << "cannot translate 0 chunks" << endl;
		currentNumTranslationsMade = 0;
	}

}


void ChunkStrip::DrawAll()
{
	Node *pR = nullptr, *pL = nullptr;
	Chunk *temp = nullptr;
	if (!isEmpty())
	{
		pR = pHead->getRight();
		pL = pHead->getLeft();

		temp = pHead->getChunkPointer();
		temp->Draw();

		while (pR != nullptr && pL != nullptr)
		{
			temp = pR->getChunkPointer();
			temp->Draw();
			temp = pL->getChunkPointer();
			temp->Draw();

			pR = pR->getRight();
			pL = pL->getLeft();
		}
	}
	else
	{
		cout << "cannot draw 0 chunks" << endl;
	}
}

void ChunkStrip::DrawArray()
{
	for (int i = 0; i < numInScene; i++)
	{
		updateArray[i]->Draw();
	}
}


int ChunkStrip::generateUpdateArray(float pm)
{
	Node *pR = nullptr, *pL = nullptr;
	Chunk *temp = nullptr;

	float o[2];
	int i = 0;


	if (!isEmpty())
	{
		temp = pHead->getChunkPointer();
		temp->calcMidPointIncludingQueuedTranslations(o);

		if (o[0] > (pm * -1) && o[0] < pm)
		{
			if (o[1] > (pm * -1) && o[1] < pm)
			{
				updateArray[0] = temp;
				i++;
			}
		}

		pR = pHead;
		pL = pHead;

		while (pR->getRight() != nullptr && pL->getLeft() != nullptr)
		{
			pR = pR->getRight();
			pL = pL->getLeft();


			temp = pR->getChunkPointer();
			temp->calcMidPointIncludingQueuedTranslations(o);

			if (o[0] > (pm * -1) && o[0] < pm)
			{
				if (o[1] > (pm * -1) && o[1] < pm)
				{
					updateArray[i] = temp;
					i++;

				}
			}


			temp = pL->getChunkPointer();
			temp->calcMidPointIncludingQueuedTranslations(o);

			if (o[0] > (pm * -1) && o[0] < pm)
			{
				if (o[1] > (pm * -1) && o[1] < pm)
				{
					updateArray[i] = temp;
					i++;
				}
			}
		}
	}
	else
	{
		return 0;
	}

	/**/
	this->numInScene = i;
	return i;
}


void ChunkStrip::TranslateChunkSize(int x, int y)
{
	Node *pR = nullptr, *pL = nullptr;
	Chunk *temp = nullptr;

	if (!isEmpty())
	{
		temp = pHead->getChunkPointer();
		temp->TranslateChunkSize(x, y);

		pR = pHead;
		pL = pHead;

		while (pR->getRight() != nullptr && pL->getLeft() != nullptr)
		{
			pR = pR->getRight();
			pL = pL->getLeft();

			temp = pR->getChunkPointer();
			temp->TranslateChunkSize(x, y);

			temp = pL->getChunkPointer();
			temp->TranslateChunkSize(x, y);
		}
	}
}


void ChunkStrip::saveAllToFile(const string &directory)
{
	Node *pR = nullptr, *pL = nullptr;
	Chunk *temp = nullptr;

	if (!isEmpty())
	{
		temp = pHead->getChunkPointer();

		temp->saveToFile(directory, yLevel, pHead->ID());

		pR = pHead;
		pL = pHead;

		while (pR->getRight() != nullptr && pL->getLeft() != nullptr)
		{
			pR = pR->getRight();
			pL = pL->getLeft();

			temp = pR->getChunkPointer();
			temp->saveToFile(directory, yLevel, pR->ID());

			temp = pL->getChunkPointer();
			temp->saveToFile(directory, yLevel, pL->ID());
		}
	}
}


void ChunkStrip::deleteAll()
{
	deleteAll(pHead);
}

void ChunkStrip::deleteAll(Node *pSub)
{
	if (pSub == nullptr)
	{
		return;
	}
	else
	{
		Chunk * temp = nullptr;
		temp = pSub->getChunkPointer();

		delete temp;

		deleteAll(pSub->getRight());
		deleteAll(pSub->getLeft());
	}
}