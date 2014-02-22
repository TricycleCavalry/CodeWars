#include "Camera.h"
#include "commonMacros.h"
#include <cstdlib>

#define NULL 0

Camera::Camera(Matrix33<float>* aPlayerOrientation,Vector2<int> someScreenDimensions)
:	myPlayerOrientation(aPlayerOrientation)
,	myWindowWidth(static_cast<float>(someScreenDimensions.x))
,	myWindowHeight(static_cast<float>(someScreenDimensions.y))
,	myVelocity(1000)
,	myPanningPoints(2)
,	myPanningTimers(2)
,	myIsShaking(false)
,	myShakeAmplitude(0)
,	myShakeFrequency(0)
,	myShakingTime(0)
,	myShakeDirection(0,0)
,	myZ(0.f)
,	myCenterPosition(0,0)
,	myPanningSpeedIsSetFlag(false)
{

}

Camera::~Camera(void)
{
	//SAFE_DELETE(myPlayerOrientation);
}



void Camera::Update(const float& someElapsedTime)
{
	float elapsedTime = someElapsedTime;

	if(myPanningPoints.Count() > 0 )
	{
		FollowPanningPoints(someElapsedTime);
	}
	else
	{
		FollowPlayer(someElapsedTime);
	}

	if(myIsShaking == true)
	{
		myShakingTime-=someElapsedTime;
		myShakeAmplitude += ((0 - myShakeAmplitude) * someElapsedTime);

		myPosition += myShakeDirection * myShakeAmplitude * sin(myShakeFrequency * myShakingTime);
		
		if(myShakingTime <= 0)
		{
			myIsShaking = false;
		}
	}
	myCenterPosition = myPosition + Vector2<float>(myWindowWidth * myZ, myWindowHeight * myZ);

}
void Camera::FollowPlayer(const float& someElapsedTime)
{
	
	myPosition = Vector2<float>::Lerp(myPosition,myPlayerOrientation->GetPosition()- Vector2<float>(myWindowWidth/2,myWindowHeight/2),someElapsedTime*8);

	Vector2<float> playerPosition = myPlayerOrientation->GetPosition();


	if(myPosition.myX > myMinPos.myX)
	{
				
	}
	else

	{
		myPosition.myX = myMinPos.myX;
	}

	if(myPosition.myX + myWindowWidth < myMaxPos.myX)
	{
		
	}
	
	else
	{
		myPosition.myX = myMaxPos.myX - myWindowWidth;
	}

	if(myPosition.myY > myMinPos.myY)
	{
		
	}
	else
	{
		myPosition.myY = myMinPos.myY;
	}

	if(myPosition.myY + myWindowHeight < myMaxPos.myY)
	{
		
	}
	else
	{
		myPosition.myY = myMaxPos.myY - myWindowHeight;
	}

}

void Camera::FollowPanningPoints(const float& someElapsedTime)
{
	if(myPanningTimers.GetLast() > 0)
	{
		if(myPanningSpeedIsSetFlag == false)
		{
			float lenght = (myPosition - myPanningPoints.GetLast()).Length();
			myCurrentPanningSpeed = lenght / myPanningTimers.GetLast();
			myPanningSpeedIsSetFlag = true;
		}
		myPosition += (myPanningPoints.GetLast() - myPosition).GetNormalize() * someElapsedTime * myCurrentPanningSpeed;
	}
	else
	{
		myPosition = Vector2<float>::Lerp(myPosition,myPanningPoints.GetLast(),someElapsedTime);
	}

	if( (myPosition -  myPanningPoints.GetLast()).Length() < 4.f)
	{

		myPanningPoints.RemoveCyclicAtIndex(myPanningPoints.Count()-1);
		myPanningTimers.RemoveCyclicAtIndex(myPanningTimers.Count()-1);
		myPanningSpeedIsSetFlag = false;		
	
	}
}
Vector2<float>& Camera::GetPosition()
{
	return myPosition;
}
Vector2<float> Camera::GetOffset()
{
	return myPosition;
}

Vector2<float*> Camera::GetWindowDimensions()
{
	return Vector2<float*>(&myWindowWidth,&myWindowHeight);
}
Vector2<float> Camera::GetCenterPosition()
{
	Vector2<float> centerPos = myPosition;
	centerPos += Vector2<float>(myWindowWidth * myZ, myWindowHeight * myZ);
	return centerPos;	
}
Vector2<float>* Camera::GetCenterPositionPtr()
{
	return &myCenterPosition;
}
void Camera::SetPosition(const Vector2<float>& aPosition)
{
	myPosition = aPosition;
}
void Camera::SetZ(const float& aZ)
{
	myZ = aZ;
}
void Camera::RemoveAllPanningPoints()
{
	myPanningPoints.RemoveAll();
	myPanningTimers.RemoveAll();
}
void Camera::AddPanningPoint(const Vector2<float>& aPoint,const float& aTime)
{
	if(myPanningPoints.Count() > 0)
	{
		myPanningPoints.Insert(0,aPoint - Vector2<float>(myWindowWidth/2,myWindowHeight/2));
		myPanningTimers.Insert(0,aTime);
	}
	else
	{
		myPanningPoints.Add(aPoint - Vector2<float>(myWindowWidth/2,myWindowHeight/2));
		myPanningTimers.Add(aTime);
	}

	
	
}
void Camera::AddPanningPoints(const GrowingArray<Vector2<float>>& somePoints,const GrowingArray<float>& someTimes)
{
	if(myPanningPoints.Count() > 0)
	{
		for(int i = 0; i < somePoints.Count(); ++i)
		{
			myPanningPoints.Insert(0,somePoints[i] - Vector2<float>(myWindowWidth/2,myWindowHeight/2));
			myPanningTimers.Insert(0,someTimes[i]);
		}
	}
	else
	{
		for(int i = somePoints.Count()-1; i >= 0; --i)
		{
			myPanningPoints.Add(somePoints[i] - Vector2<float>(myWindowWidth/2,myWindowHeight/2));
			myPanningTimers.Add(someTimes[i]);
		}
	}
}

void Camera::SetLevelDimensions(const Vector2<float>& aLevelPosition, const float& aLevelWidth,const float& aLevelHeight)
{
	myMaxPos = aLevelPosition + Vector2<float>(aLevelWidth,aLevelHeight);
	myMinPos = (aLevelPosition * -1);
}
void Camera::Shake(const float& aAmplitude,const float& aFrequency,const float& aTime)
{
	myIsShaking = true;
	myShakeAmplitude = aAmplitude;
	myShakeFrequency = aFrequency;
	myShakingTime += aTime;
	myShakeDirection = Vector2<float>(static_cast<float>(rand()),static_cast<float>(rand()));
	myShakeDirection.Normalize();
}