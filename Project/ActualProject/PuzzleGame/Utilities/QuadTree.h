#ifndef _QUAD_TREE_H_
#define _QUAD_TREE_H_

#include "Vector2.h"

class QuadTreeNode;
class QuadTreeDweller;


class QuadTree
{
public:
	QuadTree(void);
	~QuadTree(void);

	void BuildTreeRecursive(const Vector2<float>& aCenterPosition,const float& aHalfWidth,const int& aDepth,const float& aLooseness);
	void InsertTreeDweller(QuadTreeDweller* aTreeDweller);

	void UpdateTreeDweller(QuadTreeDweller* aTreeDweller);

private:
	QuadTreeNode* BuildTreeRecursive(QuadTreeNode* aParentNode, const Vector2<float>& aCenterPosition,const float& aHalfWidth,const int& aDepth,const float& aLooseness);
	void InsertTreeDweller(QuadTreeNode* aTreeNode,QuadTreeDweller* aTreeDweller);

private:
	QuadTreeNode* myRootNode;
	int myDepth;

};

#endif