#include "Entity.h"
#include "Component.h"
#include "CommonMacros.h"

Entity::Entity(const Vector3<float>& aPosition)
:	myPosition(aPosition)
,	myComponents(4)
{
}

Entity::Entity(const Vector2<float>& aPosition)
:	myPosition(Vector3<float>(aPosition.x,aPosition.y,0))
,	myComponents(4)
{
}

Entity::~Entity(void)
{
	myComponents.DeleteAll();
}

void Entity::Update(const float& anElapsedTime)
{
	for(int i=0,count=myComponents.Count();i<count;i++)
	{
		myComponents[i]->Update(anElapsedTime);
	}
}

void Entity::Render()
{
	for(int i=0,count=myComponents.Count();i<count;i++)
	{
		myComponents[i]->Render();
	}
}

void Entity::AddComponent(Component* aComponent)
{
	aComponent->SetOwner(this);
	myComponents.Add(aComponent);
}

void Entity::SetPosition(const Vector3<float>& aPosition)
{
	myPosition = aPosition;
}

void Entity::SetPosition(const Vector2<float>& aPosition)
{
	myPosition.x = aPosition.x;
	myPosition.y = aPosition.y;
}

Vector3<float> Entity::GetPosition() const
{
	return myPosition;
}

Vector2<float> Entity::GetPositionVector2() const
{
	return Vector2<float>(myPosition.x,myPosition.y);
}

void Entity::Move(const Vector3<float>& aPosition)
{
	myPosition += aPosition;
}

void Entity::Move(const Vector2<float>& aPosition)
{
	myPosition.x += aPosition.x;
	myPosition.y += aPosition.y;
}

Component* Entity::GetComponent(const ComponentTypes& aComponentType)
{
	for(int i=0;i<myComponents.Count();i++)
	{
		if(myComponents[i]->GetType() == aComponentType)
		{
			return myComponents[i];
		}
	}
	return NULL;
}