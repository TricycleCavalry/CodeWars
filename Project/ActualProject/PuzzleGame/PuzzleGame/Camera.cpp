
#include "Camera.h"

Camera::Camera(void)
:myIsLerping(false)
,myLerpTime(0)
,myCurrentTime(0)
{
}

Camera::~Camera(void)
{
}
void Camera::Update(const float anElapsedTime)
{
	if(myIsLerping == true)
	{
		if(myCurrentTime >= myLerpTime)
		{
			myCurrentTime = 0;
			myLerpTime = 0;
			myIsLerping = false;
		}
		else
		{
			myCurrentTime += anElapsedTime;
			myPosition = Vector2<float>::Lerp(myStartPosition, myTargetPosition, myCurrentTime / myLerpTime);
		}
	}
}
void Camera::SetPosition(const Vector2<float> &aNewPosition)
{
	myPosition = aNewPosition;
}
const Vector2<float>& Camera::GetPosition() const
{
	return myPosition;
}
void Camera::MoveToPosition(const Vector2<float> &aPositionToMoveTo, const float aTimeToMove)
{
	if(aPositionToMoveTo == myPosition)
	{
		return;
	}
	myStartPosition = myPosition;
	myTargetPosition = aPositionToMoveTo - Vector2<float>(400,300) + Vector2<float>(16,16);
	myIsLerping = true;
	myLerpTime = aTimeToMove;
	myCurrentTime = 0;
}