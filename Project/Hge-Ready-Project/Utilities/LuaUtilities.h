#ifndef _LUA_UTILITIES_HEADER_
#define _LUA_UTILITIES_HEADER_

#include "Vector2.h"

struct lua_State;

namespace LuaUtilities
{
	Vector2<float> LuaToVector2(lua_State* aLuaState, const int& anIndexOnTheStack);
	void Vector2ToLua(lua_State* aLuaState, const Vector2<float>& aVector);
};

#endif