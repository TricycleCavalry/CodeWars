#ifndef _OCT_TREE_H_
#define _OCT_TREE_H_


#include "StaticArray.h"
#include "Vector3.h"

#include "TreeDwellerFlags.h"

class TreeNode;
class TreeDweller;







class OctTree
{
public:
	OctTree(void);
	~OctTree(void);

	void BuildTreeRecursive(const Vector3<float>& aCenterPosition,const float& aHalfWidth,const int& aDepth,const float& aLooseness);
	void InsertTreeDweller(TreeDweller* aTreeDweller);

	void UpdateTreeDweller(TreeDweller* aTreeDweller);

private:
	TreeNode* BuildTreeRecursive(TreeNode* aParentNode, const Vector3<float>& aCenterPosition,const float& aHalfWidth,const int& aDepth,const float& aLooseness);
	void InsertTreeDweller(TreeNode* aTreeNode,TreeDweller* aTreeDweller);

private:
	TreeNode* myRootNode;
	int myDepth;
};

#endif