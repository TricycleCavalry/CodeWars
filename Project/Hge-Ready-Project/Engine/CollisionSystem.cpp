#include "CollisionSystem.h"

#include "Collision.h"

CollisionSystem::CollisionSystem(void)
:	myStaticCollisions(32)
,	myDynamicCollisions(64)
{
}


CollisionSystem::~CollisionSystem(void)
{
}

void CollisionSystem::AddStaticCollision(const CollisionData& someCollisionData)
{
	myStaticCollisions.Add(someCollisionData);
}

void CollisionSystem::AddDynamicCollision(const CollisionData& someCollisionData)
{
	myDynamicCollisions.Add(someCollisionData);
}

void CollisionSystem::CheckCollisions()
{
	for(int i=myStaticCollisions.Count()-1;i>=0;i--)
	{
		myStaticCollisions[i].myCollision->ClearFeedback();
	}

	for(int i=myDynamicCollisions.Count()-1;i>=0;i--)
	{
		CollisionData& currentCollision = myDynamicCollisions[i];
		for(int o=myStaticCollisions.Count()-1;o>=0;o--)
		{
			if(currentCollision.myCollision->IsColliding(myStaticCollisions[o].myCollision) == true)
			{
				currentCollision.myCollision->AddFeedback(CollisionFeedback(myStaticCollisions[o].myOwnerType));
				myStaticCollisions[o].myCollision->AddFeedback(CollisionFeedback(currentCollision.myOwnerType));
			}
		}
	}

	for(int i=myDynamicCollisions.Count()-1;i>=0;i--)
	{
		CollisionData& currentCollision = myDynamicCollisions[i];
		for(int o=i-1;o>=0;o--)
		{
			if(currentCollision.myCollision->IsColliding(myDynamicCollisions[o].myCollision) == true)
			{
				currentCollision.myCollision->AddFeedback(CollisionFeedback(myDynamicCollisions[o].myOwnerType));
				myDynamicCollisions[o].myCollision->AddFeedback(CollisionFeedback(currentCollision.myOwnerType));
			}
		}
	}

	myDynamicCollisions.RemoveAll();
}