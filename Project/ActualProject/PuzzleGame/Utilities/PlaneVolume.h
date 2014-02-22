#ifndef _PLANE_VOLUME_HEADER_
#define _PLANE_VOLUME_HEADER_

#include "GrowingArray.h"
#include "Plane.h"

template<typename Type>
class PlaneVolume
{
public:
	PlaneVolume();
	PlaneVolume(GrowingArray<Plane<Type>> aPlaneList);
	~PlaneVolume();

	inline Plane<Type>& operator[](const int& aIndex);
	inline const Plane<Type>& operator[](const int& aIndex) const;

	void AddPlane(Plane<Type> aPlane);
	void RemovePlane(Plane<Type> aPlane);

	bool Inside(Vector3<Type> aPosition);
	bool SphereInside( Vector3<Type> &aPosition, const float &aRadius );

private:
	GrowingArray<Plane<Type>> myPlaneList;
};

template<typename Type>
PlaneVolume<Type>::PlaneVolume()
:myPlaneList(6)
{
}

template<typename Type>
PlaneVolume<Type>::PlaneVolume(GrowingArray<Plane<Type> > aPlaneList)
:myPlaneList(aPlaneList)
{
}

template<typename Type>
PlaneVolume<Type>::~PlaneVolume()
{
}
template<typename Type>
Plane<Type>& PlaneVolume<Type>::operator[](const int& aIndex)
{
	return myPlaneList[aIndex];
}
template<typename Type>	
const Plane<Type>& PlaneVolume<Type>::operator[](const int& aIndex) const
{
	return myPlaneList[aIndex];
}
template<typename Type>
void PlaneVolume<Type>::AddPlane(Plane<Type> aPlane)
{
	myPlaneList.Add(aPlane);
}

template<typename Type>
void PlaneVolume<Type>::RemovePlane(Plane<Type> aPlane)
{
	myPlaneList.RemoveCyclic(aPlane);
}

template<typename Type>
bool PlaneVolume<Type>::Inside(Vector3<Type> aPosition)
{
	for(int i=0;i<myPlaneList.Count();i++)
	{
		if(myPlaneList[i].Inside(aPosition)==false)
		{
			return false;
		}
	}
	return true;
}

template<typename Type>
bool PlaneVolume<Type>::SphereInside( Vector3<Type> &aPosition, const float &aRadius )
{
	for( int planeIndex = 0; planeIndex < myPlanes.Count(); ++planeIndex )
	{
		if( myPlaneList[planeIndex].SphereInside( aPosition, aRadius ) == false )
		{
			return false;
		}
	}
	return true;
}

#endif