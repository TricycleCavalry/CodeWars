#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include "Vector2.h"
#include "Matrix33.h"
#include "GrowingArray.h"

class Camera
{
public:
	Camera(Matrix33<float>* aPlayerOrientation,Vector2<int> someScreenDimensions);
	~Camera(void);

	void Update(const float& someElapsedTime);
	void FollowPlayer(const float& someElapsedTime);
	void FollowPanningPoints(const float& someElapsedTime);

	Vector2<float>& GetPosition();
	Vector2<float> GetOffset();
	Vector2<float*> GetWindowDimensions();
	Vector2<float> GetCenterPosition();
	Vector2<float>* GetCenterPositionPtr();

	void SetPosition(const Vector2<float>& aPosition);

	void SetZ(const float& aZ);


	void RemoveAllPanningPoints();


	void AddPanningPoint(const Vector2<float>& aPoint,const float& aTime = 0.f);
	void AddPanningPoints(const GrowingArray<Vector2<float>>& somePoints,const GrowingArray<float>& someTimes);

	void SetLevelDimensions(const Vector2<float>& aLevelPosition, const float& aLevelWidth,const float& aLevelHeight);

	void Shake(const float& aAmplitude,const float& aFrequency,const float& aTime);

private:

	GrowingArray<Vector2<float>> myPanningPoints;
	GrowingArray<float> myPanningTimers;
	float myCurrentPanningSpeed;
	bool	myPanningSpeedIsSetFlag;

	Matrix33<float>* myPlayerOrientation;

	float myVelocity;
	Vector2<float> myPosition;
	Vector2<float> myCenterPosition;
	float myZ;
	float myWindowWidth;
	float myWindowHeight;

	Vector2<float> myMinPos;
	Vector2<float> myMaxPos;

	bool myIsShaking;
	float myShakeAmplitude;
	float myShakeFrequency;
	float myShakingTime;
	Vector2<float> myShakeDirection;

	
};

#endif