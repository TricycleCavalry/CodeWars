#ifndef _TREE_DWELLER_H_
#define _TREE_DWELLER_H_

#include "Vector3.h"
#include "TreeNode.h"
#include "OctTree.h"
//class TreeNode;




class TreeDweller
{
	friend class TreeNode;
	friend OctTree;
public:
	TreeDweller(void);
	TreeDweller(void* aDataAddress, int someFlags = 1);
	~TreeDweller(void);

	void Init(void* aDataAdress, int someFlags = 1);

	void RemoveFromOctTree();
	
	TreeNode* GetOccupiedNode() { return myOccupiedNode;};
	void SetRadius(const float& aRadius) {myRadius = aRadius;};
	void SetPosition(const Vector3<float>& aPosition) {myPosition = aPosition;};

	template<typename TYPE> 
	void GetAffectedTreeDwellersData(int someTreeDwellerFlags,GrowingArray<TYPE*>& someAffectDataArray, GrowingArray<TreeDweller*>& someDwellers);

private:

	Vector3<float> myPosition;
	float myRadius;		//Change if we want to have more "intersections"
	TreeNode* myOccupiedNode;
	//QuadTreeNode* myOccupiedQuadNode;	//TODO: arv eller gör, QuadTreeDweller ->OctTreeNode, men de gör väldigt mycket lika dana saker så Arv!?
	void* myDataAdress;

	int myFlags;	//Used for tree iteration "collision"
};

template<typename TYPE> 
void TreeDweller::GetAffectedTreeDwellersData(int someTreeDwellerFlags,GrowingArray<TYPE*>& someAffectDataArray, GrowingArray<TreeDweller*>& someDwellers)
{
	if(myOccupiedNode != NULL)
	{
		someDwellers.RemoveAll();
		myOccupiedNode->GetTreeDwellersAboveAndUnder(someDwellers,someTreeDwellerFlags);

		for(int i = 0; i < someDwellers.Count(); ++i)
		{
			someAffectDataArray.Add(reinterpret_cast<TYPE*>(someDwellers[i]->myDataAdress));
		}
	}
}


	
#endif

