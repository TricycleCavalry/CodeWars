#ifndef _XML_UTIL_HEADER_
#define _XML_UTIL_HEADER_

#include "tinyxml2.h"
#include "Vector.h"
#include <string>

namespace XMLUTIL
{
	tinyxml2::XMLElement* LoadFile(const std::string& aFilePath);

	std::string GetString(tinyxml2::XMLElement* anElement, const std::string& anAttributeName);
	Vector2<float> GetVector2(tinyxml2::XMLElement* anElement, const std::string& anAttributeName);
	Vector3<float> GetVector3(tinyxml2::XMLElement* anElement, const std::string& anAttributeName);
	Vector4<float> GetVector4(tinyxml2::XMLElement* anElement, const std::string& anAttributeName);
	float GetFloat(tinyxml2::XMLElement* anElement, const std::string& anAttributeName);
	double GetDouble(tinyxml2::XMLElement* anElement, const std::string& anAttributeName);
	bool GetBool(tinyxml2::XMLElement* anElement, const std::string& anAttributeName);

	float	GetFloat(const char* aFloat, const float& aDefaultValue = 0.f);
	int		GetInt(const char* anInt, const int& aDefaultValue = 0);
	bool	GetBool(const char* aBool, const bool& aDefaultValue = false);

	Vector2<float> GetVector2(const char* aVector,const Vector2<float>& aDefaultValue = Vector2<float>(0.f,0.f));
	Vector3<float> GetVector3(const char* aVector,const Vector3<float>& aDefaultValue = Vector3<float>(0.f,0.f,0.f));
	Vector4<float> GetVector4(const char* aVector,const Vector4<float>& aDefaultValue = Vector4<float>(0.f,0.f,0.f,0.f));
};

#endif