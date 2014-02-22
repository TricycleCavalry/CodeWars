#include "QuadTreeNode.h"
#include "TreeDweller.h"

#include "QuadTreeDweller.h"

QuadTreeNode::QuadTreeNode(void)
{
}


QuadTreeNode::~QuadTreeNode(void)
{
}
void QuadTreeNode::Update()
{
}	

GrowingArray<QuadTreeDweller*> QuadTreeNode::GetTreeDwellers()
{
	return myTreeDwellers;
}
void QuadTreeNode::GetTreeDwellers(GrowingArray<QuadTreeDweller*>& anOutArray,int someTreeDwellerFlags)
{
	for(int i = 0; i  < myTreeDwellers.Count(); ++i)
	{
		if(myTreeDwellers[i]->myFlags & someTreeDwellerFlags)
		{
			anOutArray.Add(myTreeDwellers[i]);
		}
	}
}

void QuadTreeNode::GetTreeDwellersUnder(GrowingArray<QuadTreeDweller*>& anOutArray,int someTreeDwellerFlags)
{
	if(myChildNodes[0] != NULL)
	{
		for(int i = 0; i < 8; ++i)
		{
			myChildNodes[i]->GetTreeDwellers(anOutArray,someTreeDwellerFlags);
			myChildNodes[i]->GetTreeDwellersUnder(anOutArray,someTreeDwellerFlags);
		}
	}
}

GrowingArray<QuadTreeDweller*> QuadTreeNode::GetTreeDwellersAboveAndUnder(int someTreeDwellerFlags)
{
	GrowingArray<QuadTreeDweller*> returnArray(8192);
	GetTreeDwellersAboveAndUnder(returnArray,someTreeDwellerFlags);
	return returnArray;
}
void QuadTreeNode::GetTreeDwellersAboveAndUnder(GrowingArray<QuadTreeDweller*>& anOutArray, int someTreeDwellerFlags)
{
	GetTreeDwellers(anOutArray,someTreeDwellerFlags);
	GetTreeDwellersUnder(anOutArray,someTreeDwellerFlags);


	QuadTreeNode* treeNodeIterator = myParentNode;
	while(treeNodeIterator != NULL)
	{
		treeNodeIterator->GetTreeDwellers(anOutArray,someTreeDwellerFlags);
		treeNodeIterator = treeNodeIterator->myParentNode;
	}
}

int QuadTreeNode::Find(QuadTreeDweller* aDweller)
{
	for(int i=0,count=myTreeDwellers.Count();i<count;i++)
	{
		if(myTreeDwellers[i]->myDataAdress == aDweller->myDataAdress)
		{
			return i;
		}
	}
	return -1;
}

void QuadTreeNode::RemoveFromNode(QuadTreeDweller* aDweller)
{
	int index = Find(aDweller);
	if(index != -1)
	{
		myTreeDwellers.RemoveCyclicAtIndex(index);
	}
	else
	{
		DL_DEBUG("TreeDweller RemoveFromNode did not find the associated node to remove (QuadTree)");
	}
}