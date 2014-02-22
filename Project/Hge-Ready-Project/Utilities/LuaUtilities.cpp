#include "LuaUtilities.h"
#include <lua.hpp>

#include "MathLib.c"

using namespace LuaUtilities;

Vector2<float> LuaUtilities::LuaToVector2(lua_State* aLuaState, const int& anIndexOnTheStack)
{
	Vector2<float> returnVector;

	lua_getfield(aLuaState,-anIndexOnTheStack,"x");
	returnVector.x = static_cast<float>(lua_tonumber(aLuaState,-1));

	lua_getfield(aLuaState,-(anIndexOnTheStack+1),"y");
	returnVector.y = static_cast<float>(lua_tonumber(aLuaState,-1));

	lua_pop(aLuaState,2);

	return returnVector;
}

void LuaUtilities::Vector2ToLua(lua_State* aLuaState, const Vector2<float>& aVector)
{
	lua_pushnumber(aLuaState,aVector.x);
	lua_pushnumber(aLuaState,aVector.y);
	Vector2_New(aLuaState);
}