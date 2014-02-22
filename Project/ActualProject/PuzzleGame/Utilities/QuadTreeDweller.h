#ifndef _QUAD_TREE_DWELLER_HEADER_
#define _QUAD_TREE_DWELLER_HEADER_

#include "GrowingArray.h"
#include "Vector2.h"
#include "TreeDwellerFlags.h"
#include "QuadTreeNode.h"
#include "Intersections.h"

class QuadTreeDweller
{
	friend class QuadTree;
	friend class QuadTreeNode;
public:
	QuadTreeDweller(void);
	QuadTreeDweller(void* aDataAdress, int someFlags = 1);
	~QuadTreeDweller(void);

	void Init(void* aDataAdress, int someFlags = 1);

	void RemoveFromQuadTree();

	QuadTreeNode* GetOccupiedNode() { return myOccupiedNode; }
	void SetRadius(const float& aRadius) { myRadius = aRadius; }
	float GetRadius() { return myRadius; }
	void SetPosition(const Vector2f& aPosition) { myPosition = aPosition; }
	Vector2f GetPosition() { return myPosition; };

	void GetNearbyTreeDwellers(int someTreeDwellerFlags,GrowingArray<QuadTreeDweller*>& someDwellers);

	template<typename TYPE>
	void GetAffectedTreeDwellersData(int someTreeDwellerFlags, GrowingArray<TYPE*>& someAffectedDataArray, GrowingArray<QuadTreeDweller*>& someDwellers);
	template<typename TYPE>
	void GetNearbyTreeDwellersData(int someTreeDwellerFlags,GrowingArray<TYPE*>& someAffectDataArray, GrowingArray<QuadTreeDweller*>& someDwellers);

	template<typename TYPE>
	void GetAffectedTreeDwellersDataOfSortFromArray(int someTreeDwellerFlags,GrowingArray<TYPE*>& someAffectDataArray,GrowingArray<QuadTreeDweller*>& someAffectDataDwellers, GrowingArray<QuadTreeDweller*>& someDwellers);

	void* GetDataAdress() const { return myDataAdress; }

	void Clear();

private:
	Vector2f myPosition;
	float myRadius;
	QuadTreeNode* myOccupiedNode;
	void* myDataAdress;	
	int myFlags;
};

template<typename TYPE> 
void QuadTreeDweller::GetAffectedTreeDwellersData(int someTreeDwellerFlags,GrowingArray<TYPE*>& someAffectDataArray, GrowingArray<QuadTreeDweller*>& someDwellers)
{
	someDwellers.RemoveAll();
	if(myOccupiedNode != NULL)
	{		
		myOccupiedNode->GetTreeDwellersAboveAndUnder(someDwellers,someTreeDwellerFlags);

		for(int i = 0; i < someDwellers.Count(); ++i)
		{
			someAffectDataArray.Add(reinterpret_cast<TYPE*>(someDwellers[i]->myDataAdress));
		}
	}
}

template<typename TYPE> 
void QuadTreeDweller::GetNearbyTreeDwellersData(int someTreeDwellerFlags,GrowingArray<TYPE*>& someAffectDataArray, GrowingArray<QuadTreeDweller*>& someDwellers)
{
	if(myOccupiedNode != NULL)
	{
		someDwellers.RemoveAll();
		myOccupiedNode->GetTreeDwellersAboveAndUnder(someDwellers,someTreeDwellerFlags);

		someAffectDataArray.RemoveAll();
		QuadTreeDweller* currentDweller;
		for(int i = 0; i < someDwellers.Count(); ++i)
		{
			currentDweller = someDwellers[i];
			if(Intersections::CircleVsCircle(myPosition,myRadius,currentDweller->myPosition,currentDweller->myRadius) == true)
			{
				someAffectDataArray.Add(reinterpret_cast<TYPE*>(someDwellers[i]->myDataAdress));
			}
		}
	}
}

template<typename TYPE> 
void QuadTreeDweller::GetAffectedTreeDwellersDataOfSortFromArray(int someTreeDwellerFlags,GrowingArray<TYPE*>& someAffectDataArray,GrowingArray<QuadTreeDweller*>& someAffectDataDwellers, GrowingArray<QuadTreeDweller*>& someDwellers)
{
	someAffectDataDwellers.RemoveAll();
	someAffectDataArray.RemoveAll();
	QuadTreeDweller* currentDweller;
	for(int i = someDwellers.Count()-1; i >= 0 ; --i)
	{
		currentDweller = someDwellers[i];
		if(currentDweller->myFlags & someTreeDwellerFlags)
		{
			if(Intersections::CircleVsCircle(myPosition,myRadius,currentDweller->myPosition,currentDweller->myRadius) == true)
			{
				someAffectDataArray.Add(reinterpret_cast<TYPE*>(currentDweller->myDataAdress));
				someAffectDataDwellers.Add(currentDweller);
			}
			someDwellers.RemoveCyclicAtIndex(i);
		}
	}
}

#endif