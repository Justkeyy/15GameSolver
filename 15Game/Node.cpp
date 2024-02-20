#include "Node.h"


Node::Node()
{
	pPrev = nullptr;
	pNext = nullptr;
}

Node::Node(Node* node, const board* brd) :m_data(*brd)
{
	pPrev = node;
	pNext = node->pNext;
	node->pNext = this;
	this->pNext->pPrev = this;
}

Node::~Node()
{
	if (pNext)
	{
			pNext->pPrev = this->pPrev;
	}

	if (pPrev)
	{
			pPrev->pNext = this->pNext;
	}
}


