#ifndef _BLOCK_ATTRIBUTE__CONTROLLABLE_H_
#define _BLOCK_ATTRIBUTE__CONTROLLABLE_H_
#include "BlockAttribute.h"

#include "MovementDirectionType.h"

class BlockAttributeControllable :	public BlockAttribute
{
public:
	BlockAttributeControllable(void);
	~BlockAttributeControllable(void);

	void Init();
	void Update(const float anElapsedTime);
	void Move(const MovementDirectionType& aMovementDirection,const Vector2<float>& aEndPosition);

	bool IsMoving();
	void Clear();

protected:
	BlockAttribute* SubCopy();

private:
	bool* myIsMoving;
	MovementDirectionType myMovementDirectionType;
	Vector2<float> myEndPosition;


};
#endif