#ifndef _COLLISION_HEADER_
#define _COLLISION_HEADER_

#include "Vector2.h"
#include "CollisionFeedback.h"
#include "GrowingArray.h"

class CollisionSystem;
class CollisionCircle;
class CollisionBox;
class CollisionPoint;
struct CollisionData;

enum CollisionOwnerType
{
	COT_PLAYER,
	COT_ENEMY,
	COT_NEUTRAL,
};


class Collision
{
public:
	Collision(CollisionSystem* aCollisionSystem, const Vector2<float>& aPosition, const CollisionOwnerType& anOwnerType);
	virtual ~Collision(void);

	virtual bool IsColliding(Collision* aCollision)=0;
	virtual bool IsColliding(CollisionCircle* aCollision)=0;
	virtual bool IsColliding(CollisionBox* aCollision)=0;
	virtual bool IsColliding(CollisionPoint* aCollision)=0;

	void AddFeedback(const CollisionFeedback& someFeedback);
	void ClearFeedback();
	bool HasCollided() const;
	bool HasLethallyCollided() const;

	void Update(const Vector2<float>& aPosition);

	Vector2<float> GetPosition() const;
	CollisionOwnerType GetOwnerType() const;
protected:
	Vector2<float> myPosition;
private:
	void SubmitCollisionData(const CollisionData& someCollisionData);
	CollisionSystem* myCollisionSystem;
	GrowingArray<CollisionFeedback> myFeedback;
	CollisionOwnerType myOwnerType;
};

#endif