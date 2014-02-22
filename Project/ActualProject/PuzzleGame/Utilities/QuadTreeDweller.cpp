#include "QuadTreeDweller.h"

#include "QuadTreeNode.h"

QuadTreeDweller::QuadTreeDweller(void)
:	myDataAdress(NULL)
,	myFlags(1)
,	myOccupiedNode(NULL)
{
}

QuadTreeDweller::QuadTreeDweller(void* aDataAdress, int someFlags)
:	myDataAdress(aDataAdress)
,	myFlags(someFlags)
,	myOccupiedNode(NULL)
{
}

QuadTreeDweller::~QuadTreeDweller(void)
{
}

void QuadTreeDweller::Init(void* aDataAdress, int someFlags)
{
	myDataAdress = aDataAdress;
	myFlags = someFlags;
	myOccupiedNode = NULL;
}

void QuadTreeDweller::RemoveFromQuadTree()
{
	if(myOccupiedNode != NULL)
	{
		myOccupiedNode->RemoveFromNode(this);
		myOccupiedNode = NULL;
	}
}

void QuadTreeDweller::GetNearbyTreeDwellers(int someTreeDwellerFlags,GrowingArray<QuadTreeDweller*>& someDwellers)
{
	if(myOccupiedNode != NULL)
	{
		someDwellers.RemoveAll();
		myOccupiedNode->GetTreeDwellersAboveAndUnder(someDwellers,someTreeDwellerFlags);
	}
}

void QuadTreeDweller::Clear()
{
	myDataAdress = NULL;
	myFlags = 1;
	myOccupiedNode = NULL;
}