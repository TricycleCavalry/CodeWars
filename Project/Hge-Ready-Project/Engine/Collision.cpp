#include "Collision.h"
#include "CollisionSystem.h"
#include "CollisionData.h"

Collision::Collision(CollisionSystem* aCollisionSystem, const Vector2<float>& aPosition, const CollisionOwnerType& anOwnerType)
:	myCollisionSystem(aCollisionSystem)
,	myPosition(aPosition)
,	myFeedback(4)
,	myOwnerType(anOwnerType)
{
}

Collision::~Collision(void)
{
}

void Collision::AddFeedback(const CollisionFeedback& someFeedback)
{
	myFeedback.Add(someFeedback);
}

void Collision::ClearFeedback()
{
	myFeedback.RemoveAll();
}

bool Collision::HasCollided() const
{
	return myFeedback.Count() > 0;
}

bool Collision::HasLethallyCollided() const
{
	for(int i=0, count=myFeedback.Count();i<count;i++)
	{
		if(myFeedback[i].myTypeCollidedWith != myOwnerType)
		{
			return true;
		}
	}
	return false;
}

void Collision::Update(const Vector2<float>& aPosition)
{
	ClearFeedback();

	myPosition = aPosition;
	CollisionData dataToBeSent;
	dataToBeSent.myCollision = this;
	dataToBeSent.myOwnerType = myOwnerType;
	SubmitCollisionData(dataToBeSent);
}

Vector2<float> Collision::GetPosition() const
{
	return myPosition;
}

CollisionOwnerType Collision::GetOwnerType() const
{
	return myOwnerType;
}

void Collision::SubmitCollisionData(const CollisionData& someCollisionData)
{
	myCollisionSystem->AddDynamicCollision(someCollisionData);
}