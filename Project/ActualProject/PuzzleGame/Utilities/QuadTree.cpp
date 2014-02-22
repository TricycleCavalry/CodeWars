#include "QuadTree.h"

#include "QuadTreeNode.h"
#include "QuadTreeDweller.h"
#include "Intersections.h"

QuadTree::QuadTree(void)
{
}


QuadTree::~QuadTree(void)
{
}

void QuadTree::BuildTreeRecursive(const Vector2<float>& aCenterPosition,const float& aHalfWidth,const int& aDepth,const float& aLooseness)
{
	myDepth = aDepth;
	myRootNode = BuildTreeRecursive(NULL,aCenterPosition,aHalfWidth,0,aLooseness);
}
void QuadTree::InsertTreeDweller(QuadTreeDweller* aTreeDweller)
{
	InsertTreeDweller(myRootNode,aTreeDweller);
}

void QuadTree::UpdateTreeDweller(QuadTreeDweller* aTreeDweller)
{
	QuadTreeNode* currentNode = aTreeDweller->myOccupiedNode;
	currentNode->RemoveFromNode(aTreeDweller);
	
	Vector2<float> objectPos = aTreeDweller->myPosition;
	float objectRad = aTreeDweller->myRadius;

	

	while(true)
	{
		float nodeHalfWidth = currentNode->myHalfWidth;
		Vector2<float> nodeCenter = currentNode->myCenterPosition;
		Vector2<float> nodeTopLeftCorner = Vector2<float>(nodeCenter - Vector2<float>(nodeHalfWidth,nodeHalfWidth));
		float nodeWidthMinusRad = nodeHalfWidth - objectRad;

		if( (Intersections::RectVsCircle(nodeTopLeftCorner,Vector2<float>(nodeHalfWidth,nodeHalfWidth)*2,objectPos,objectRad) == true 
			&& Intersections::RectVsPoint(nodeTopLeftCorner,Vector2<float>(nodeHalfWidth,nodeHalfWidth)*2,objectPos) == true)
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


QuadTreeNode* QuadTree::BuildTreeRecursive(QuadTreeNode* aParentNode, const Vector2<float>& aCenterPosition,const float& aHalfWidth,const int& aDepth,const float& aLooseness)
{
	if(aDepth >= myDepth)
	{
		return NULL;
	}

	QuadTreeNode* newNode = new QuadTreeNode();
	newNode->myCenterPosition = aCenterPosition;
	newNode->myHalfWidth = aHalfWidth;
	newNode->myDepth = aDepth;
	newNode->myParentNode = aParentNode;
	newNode->myLooseness = aLooseness;
	newNode->myTreeDwellers.Init(32);


	float step = aHalfWidth * .5f;
	Vector2<float> newCenterPosition(0,0);

	for(int i = 0; i < 8; ++i)
	{
		newCenterPosition.x = aCenterPosition.x + ((i & 1) ? step : -step);
		newCenterPosition.y = aCenterPosition.y + ((i & 2) ? step : -step);
		newNode->myChildNodes[i] = BuildTreeRecursive(newNode,newCenterPosition,step,aDepth+1,aLooseness);
	}
	return newNode;
}
void QuadTree::InsertTreeDweller(QuadTreeNode* aTreeNode,QuadTreeDweller* aTreeDweller)
{
	int childIndex = 0;
	bool straddle = false;

	float deltaX;
	float deltaY;

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
			childIndex += 4;
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
