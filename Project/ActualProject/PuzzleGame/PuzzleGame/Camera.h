#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Vector2.h"

class Camera
{
public:
	Camera(void);
	~Camera(void);

	void Update(const float anElapsedTime);

	void SetPosition(const Vector2<float> &aNewPosition);
	const Vector2<float>& GetPosition() const;

	void MoveToPosition(const Vector2<float> &aPositionToMoveTo, const float aTimeToMove);

private:
	Vector2<float> myPosition;
	Vector2<float> myStartPosition;
	Vector2<float> myTargetPosition;

	bool myIsLerping;
	float myLerpTime;
	float myCurrentTime;
};

#endif