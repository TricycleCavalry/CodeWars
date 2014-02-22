#include "OctTree.h"

#include "TreeNode.h"
#include "TreeDweller.h"


#include "Intersections.h"
#include "DL_Debug.h"


OctTree::OctTree(void)
{
}


OctTree::~OctTree(void)
{
}

void OctTree::BuildTreeRecursive(const Vector3<float>& aCenterPosition,const float& aHalfWidth,const int& aDepth,const float& aLooseness)
{
	myDepth = aDepth;
	myRootNode = BuildTreeRecursive(NULL,aCenterPosition,aHalfWidth,0,aLooseness);
}


TreeNode* OctTree::BuildTreeRecursive(TreeNode* aParentNode,const Vector3<float>& aCenterPosition,const float& aHalfWidth,const int& aDepth,const float& aLooseness)
{
	if(aDepth >= myDepth)
	{
		return NULL;
	}

	TreeNode* newNode = new TreeNode();
	newNode->myCenterPosition = aCenterPosition;
	newNode->myHalfWidth = aHalfWidth;
	newNode->myDepth = aDepth;
	newNode->myParentNode = aParentNode;
	newNode->myLooseness = aLooseness;
	newNode->myTreeDwellers.Init(512);


	float step = aHalfWidth * .5f;
	Vector3<float> newCenterPosition(0,0,0);

	for(int i = 0; i < 8; ++i)
	{
		newCenterPosition.x = aCenterPosition.x + ((i & 1) ? step : -step);
		newCenterPosition.y = aCenterPosition.y + ((i & 2) ? step : -step);
		newCenterPosition.z = aCenterPosition.z + ((i & 4) ? step : -step);
		newNode->myChildNodes[i] = BuildTreeRecursive(newNode,newCenterPosition,step,aDepth+1,aLooseness);
	}
	return newNode;
}
void OctTree::InsertTreeDweller(TreeDweller* aTreeDweller)
{
	InsertTreeDweller(myRootNode,aTreeDweller);
}
void OctTree::UpdateTreeDweller(TreeDweller* aTreeDweller)
{	
	TreeNode* currentNode = aTreeDweller->myOccupiedNode;
	currentNode->RemoveFromNode(aTreeDweller);
	
	Vector3<float> objectPos = aTreeDweller->myPosition;
	float objectRad = aTreeDweller->myRadius;

	while(true)
	{
		float nodeHalfWidth = currentNode->myHalfWidth;
		Vector3<float> nodeCenter = currentNode->myCenterPosition;
		float nodeWidthMinusRad = nodeHalfWidth - objectRad;
		if( (Intersections::SphereVsAABB(objectPos,objectRad,nodeCenter,nodeHalfWidth,nodeHalfWidth,nodeHalfWidth) == true 
			&& Intersections::PointVsAABB(objectPos,nodeCenter,nodeWidthMinusRad,nodeWidthMinusRad,nodeWidthMinusRad) == true)
			|| currentNode->myParentNode == NULL)
		{			
			InsertTreeDweller(currentNode, aTreeDweller);
			break;
		}
		else
		{			
			currentNode = currentNode->myParentNode;
		}
	}
}
void OctTree::InsertTreeDweller(TreeNode* aTreeNode,TreeDweller* aTreeDweller)
{
	int childIndex = 0;
	bool straddle = false;

	float deltaX;
	float deltaY;
	float deltaZ;

	float looseness = (aTreeNode->myHalfWidth * (aTreeNode->myLooseness - 1));

	deltaX = aTreeDweller->myPosition.x - aTreeNode->myCenterPosition.x;
	straddle = abs(deltaX) + looseness <= aTreeDweller->myRadius;

	if(deltaX > 0.f)
	{
		childIndex = 1;
	}
	if(straddle == false)
	{
		deltaY = aTreeDweller->myPosition.y - aTreeNode->myCenterPosition.y;
		straddle = abs(deltaY) + looseness <= aTreeDweller->myRadius;
		if(deltaY > 0.f)
		{
			childIndex += 2;
		}

		if(straddle == false)
		{
			deltaZ = aTreeDweller->myPosition.z - aTreeNode->myCenterPosition.z;
			straddle = abs(deltaZ) + looseness <= aTreeDweller->myRadius;
			if(deltaZ > 0.f)
			{
				childIndex += 4;
			}
		}
	}

	if(straddle == false && aTreeNode->myChildNodes[childIndex] != NULL)
	{
		InsertTreeDweller(aTreeNode->myChildNodes[childIndex],aTreeDweller);
	}
	else
	{
		if(aTreeNode->myTreeDwellers.Find(aTreeDweller) == -1)
		{
			aTreeNode->myTreeDwellers.Add(aTreeDweller);

			if(aTreeDweller->myFlags == TDF_LIGHT)
			{				
				//DL_DEBUG("Poiner 0x%x Added to node 0x%x",aTreeDweller,aTreeNode);
			}			
		}
		else
		{
			bool omglol = false;
		}
		aTreeDweller->myOccupiedNode = aTreeNode;
		
	}
}
