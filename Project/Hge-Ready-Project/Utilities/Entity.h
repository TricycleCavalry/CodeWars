#ifndef _ENTITY_HEADER_
#define _ENTITY_HEADER_

#include "GrowingArray.h"
#include "Vector3.h"
#pragma warning (disable : 4005)
#include "Vector2.h"

class Component;
enum ComponentTypes;

class Entity
{
public:
	Entity(const Vector3<float>& aPosition);
	Entity(const Vector2<float>& aPosition);
	~Entity(void);

	void Update(const float& anElapsedTime);

	void Render();

	void AddComponent(Component* aComponent);

	void SetPosition(const Vector3<float>& aPosition);
	void SetPosition(const Vector2<float>& aPosition);
	Vector3<float> GetPosition() const;
	Vector2<float> GetPositionVector2() const;

	void Move(const Vector3<float>& aPosition);
	void Move(const Vector2<float>& aPosition);

	Component* GetComponent(const ComponentTypes& aComponentType);

private:

	Vector3<float> myPosition;
	GrowingArray<Component*> myComponents;
};

#endif