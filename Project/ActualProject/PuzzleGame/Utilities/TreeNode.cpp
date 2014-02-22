#include "stdafx.h"
#include "TreeNode.h"
#include "OctTree.h"

#include "Intersections.h"
#include "TreeDweller.h"



TreeNode::TreeNode(void)
{
}
TreeNode::~TreeNode(void)
{
}

GrowingArray<TreeDweller*> TreeNode::GetTreeDwellers()
{
	return myTreeDwellers;
}
void TreeNode::GetTreeDwellers(GrowingArray<TreeDweller*>& anOutArray,int someTreeDwellerFlags)
{
	for(int i = 0; i  < myTreeDwellers.Count(); ++i)
	{
		if(myTreeDwellers[i]->myFlags & someTreeDwellerFlags)
		{
			anOutArray.Add(myTreeDwellers[i]);
		}
	}
	
}
void TreeNode::GetTreeDwellersUnder(GrowingArray<TreeDweller*>& anOutArray,int someTreeDwellerFlags)
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
void TreeNode::Update()
{
	//Hello TODO:
}
GrowingArray<TreeDweller*> TreeNode::GetTreeDwellersAboveAndUnder(int someTreeDwellerFlags)
{
	GrowingArray<TreeDweller*> returnArray(8192);
	GetTreeDwellersAboveAndUnder(returnArray,someTreeDwellerFlags);
	return returnArray;
}
void TreeNode::GetTreeDwellersAboveAndUnder(GrowingArray<TreeDweller*>& anOutArray,int someTreeDwellerFlags)
{

	GetTreeDwellers(anOutArray,someTreeDwellerFlags);
	GetTreeDwellersUnder(anOutArray,someTreeDwellerFlags);
	
	
	TreeNode* treeNodeIterator = myParentNode;
	while(treeNodeIterator != NULL)
	{
		treeNodeIterator->GetTreeDwellers(anOutArray,someTreeDwellerFlags);
		treeNodeIterator = treeNodeIterator->myParentNode;
	}

}

int TreeNode::Find(TreeDweller* aDweller)
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

void TreeNode::RemoveFromNode(TreeDweller* aDweller)
{
	int index = Find(aDweller);
	if(index != -1)
	{
		myTreeDwellers.RemoveCyclicAtIndex(index);
	}
	else
	{
		DL_DEBUG("TreeDweller RemoveFromNode did not find the associated node to remove");
	}
}