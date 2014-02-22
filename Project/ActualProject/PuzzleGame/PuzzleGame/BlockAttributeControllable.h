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
	void Move(const MovementDirectionType& aMovementDirection);

	void Clear();

protected:
	BlockAttribute* SubCopy();

private:
	bool myIsMoving;
	MovementDirectionType myMovementDirectionType;


};
#endif