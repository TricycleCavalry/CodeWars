#ifndef _TREE_NODE_H_
#define _TREE_NODE_H_
 
#include "Vector3.h"
#include "StaticArray.h"
#include "GrowingArray.h"
#include "OctTree.h"



class TreeDweller;

class TreeNode
{
	friend class OctTree;
	friend TreeDweller;
public:
	TreeNode(void);
	~TreeNode(void);

	void Update();


	GrowingArray<TreeDweller*>& GetMyTreeDwellers() { return myTreeDwellers; }

	//Borde skickas in en oputArray!!!!
	GrowingArray<TreeDweller*> GetTreeDwellers();		//Rename!! It returns all treedwellers under its depth
	void GetTreeDwellers(GrowingArray<TreeDweller*>& anOutArray,int someTreeDwellerFlags = TDF_DEFAULT);

	void GetTreeDwellersUnder(GrowingArray<TreeDweller*>& anOutArray,int someTreeDwellerFlags);

	//Borde skickas in en oputArray!!!!
	GrowingArray<TreeDweller*> GetTreeDwellersAboveAndUnder(int someTreeDwellerFlags = TDF_DEFAULT);	//Rename it returns all tredwellers under its depth and all treeparents dwellers
	void GetTreeDwellersAboveAndUnder(GrowingArray<TreeDweller*>& anOutArray, int someTreeDwellerFlags = TDF_DEFAULT);

	int Find(TreeDweller* aDweller);

	void RemoveFromNode(TreeDweller* aDweller);

private:
	Vector3<float> myCenterPosition;
	float myHalfWidth;
	int myDepth;
	float myLooseness;
	TreeNode* myParentNode;

	StaticArray<TreeNode*,8> myChildNodes;
	GrowingArray<TreeDweller*> myTreeDwellers;
};




#endif