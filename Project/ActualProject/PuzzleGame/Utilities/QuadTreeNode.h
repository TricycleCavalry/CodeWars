#ifndef _QUAD_TREE_NODE_H_
#define _QUAD_TREE_NODE_H_

#include "Vector2.h"
#include "StaticArray.h"
#include "GrowingArray.h"
#include "QuadTree.h"
#include "TreeDwellerFlags.h"

class QuadTreeNode
{
	friend class QuadTree;
	friend class QuadTreeDweller;
public:
	QuadTreeNode(void);
	~QuadTreeNode(void);

	void Update();

	GrowingArray<QuadTreeDweller*>& GetMyTreeDwellers() { return myTreeDwellers; }

	GrowingArray<QuadTreeDweller*> GetTreeDwellers();		//Rename!! It returns all treedwellers under its depth
	void GetTreeDwellers(GrowingArray<QuadTreeDweller*>& anOutArray,int someTreeDwellerFlags = TDF_DEFAULT);

	void GetTreeDwellersUnder(GrowingArray<QuadTreeDweller*>& anOutArray,int someTreeDwellerFlags);

	GrowingArray<QuadTreeDweller*> GetTreeDwellersAboveAndUnder(int someTreeDwellerFlags = TDF_DEFAULT);	//Rename it returns all tredwellers under its depth and all treeparents dwellers
	void GetTreeDwellersAboveAndUnder(GrowingArray<QuadTreeDweller*>& anOutArray, int someTreeDwellerFlags = TDF_DEFAULT);

	int Find(QuadTreeDweller* aDweller);

	void RemoveFromNode(QuadTreeDweller* aDweller);


	
private:
	Vector2<float> myCenterPosition;
	float myHalfWidth;
	int myDepth;
	float myLooseness;
	QuadTreeNode* myParentNode;

	StaticArray<QuadTreeNode*,8> myChildNodes;
	GrowingArray<QuadTreeDweller*> myTreeDwellers;

};

#endif