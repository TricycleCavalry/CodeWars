#include "TreeDweller.h"
#include "TreeNode.h"

#include "DL_Debug.h"


TreeDweller::TreeDweller(void)
		:	myDataAdress(NULL)
		,	myFlags(1)
		,	myOccupiedNode(NULL)
{
}

TreeDweller::TreeDweller(void* aDataAddress, int someFlags)
	:	myDataAdress(aDataAddress)
	,	myFlags(someFlags)
	,	myOccupiedNode(NULL)
{
}

TreeDweller::~TreeDweller(void)
{
//	RemoveFromOctTree();
}

void TreeDweller::Init(void* aDataAdress, int someFlags)
{
	myDataAdress = aDataAdress;
	myFlags = someFlags;
	myOccupiedNode = NULL;
}

void TreeDweller::RemoveFromOctTree()
{
	if(myOccupiedNode != NULL)
	{
		myOccupiedNode->RemoveFromNode(this);
		myOccupiedNode = NULL;
	}
}