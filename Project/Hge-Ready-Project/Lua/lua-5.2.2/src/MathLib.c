#define MathLib_c
#define LUA_LIB

#include "lua.h"

#include "lauxlib.h"
#include "lualib.h"

#include <math.h>

static const luaL_Reg MathLibFuncs[] =
{
	{NULL,NULL}
};

LUAMOD_API int luaopen_MathLib(lua_State* aLuaState)
{
	luaL_newlib(aLuaState, MathLibFuncs);
	return 1;
}

///Vector2 for Lua

static int Vector2_New(lua_State* aLuaState)
{
	float x = 0.f;
	float y = 0.f;
	int nrOfArguments = lua_gettop(aLuaState)-1;
	if(nrOfArguments == 0 || nrOfArguments == 2)
	{
		if(nrOfArguments == 2)
		{
			x = (float)(lua_tonumber(aLuaState,-2));
			y = (float)(lua_tonumber(aLuaState,-1));
		}
	}
	else
	{
		LUA_ASSERT(aLuaState,"Too many or too few arguments in Vector declaration");
	}
	lua_pop(aLuaState,3);
	lua_newtable(aLuaState);
	lua_pushstring(aLuaState,"x");
	lua_pushnumber(aLuaState,x);
	lua_settable(aLuaState,-3);
	lua_pushstring(aLuaState,"y");
	lua_pushnumber(aLuaState,y);
	lua_settable(aLuaState,-3);
	luaL_getmetatable(aLuaState,"Vector2");
	lua_setmetatable(aLuaState,-2);
	return 1;
}

static int Vector2_Length2(lua_State* aLuaState)
{
	float x;
	float y;
	float pythagorasSquared;
	int nrOfArguments = lua_gettop(aLuaState);
	if(nrOfArguments == 0 || nrOfArguments > 1)
	{
		LUA_ASSERT(aLuaState,"Length Function of Vector2 Class needs only the instance calling the function as an argument");
	}

	lua_getfield(aLuaState,-1,"x");
	x = (float)lua_tonumber(aLuaState,-1);

	lua_getfield(aLuaState,-2,"y");
	y = (float)lua_tonumber(aLuaState,-1);
	lua_pop(aLuaState,2);

	pythagorasSquared = x*x+y*y;

	lua_pushnumber(aLuaState,pythagorasSquared);
	return 1;
}

static int Vector2_Length(lua_State* aLuaState)
{
	float pythagoras;
	Vector2_Length2(aLuaState);

	pythagoras = (float)sqrt(lua_tonumber(aLuaState,-1));
	lua_pop(aLuaState,1);

	lua_pushnumber(aLuaState,pythagoras);
	return 1;
}

static int Vector2_Mul(lua_State* aLuaState)
{
	int nrOfArguments = lua_gettop(aLuaState);
	float x;
	float y;
	float multiplicator = (float)lua_tonumber(aLuaState,-1);
	lua_getfield(aLuaState,-2,"x");
	x = (float)lua_tonumber(aLuaState,-1);

	lua_getfield(aLuaState,-3,"y");
	y = (float)lua_tonumber(aLuaState,-1);

	lua_pop(aLuaState,3);

	x *= multiplicator;
	y *= multiplicator;

	lua_pushnumber(aLuaState,x);
	lua_pushnumber(aLuaState,y);
	Vector2_New(aLuaState);

	return 1;
}

static int Vector2_Normalize(lua_State* aLuaState)
{
	int nrOfArguments = lua_gettop(aLuaState)-1;
	float length;
	float x;
	float y;
	if(nrOfArguments > 0)
	{
		LUA_ASSERT(aLuaState,"Vector2.Normalize should not take any arguments");
	}

	Vector2_Length(aLuaState);
	length = (float)lua_tonumber(aLuaState,-1);

	lua_getfield(aLuaState,-2,"x");
	x = (float)lua_tonumber(aLuaState,-1);
	lua_getfield(aLuaState,-3,"y");
	y = (float)lua_tonumber(aLuaState,-1);

	lua_pop(aLuaState,3);

	lua_pushstring(aLuaState,"x");
	lua_pushnumber(aLuaState,x/length);
	lua_settable(aLuaState,-3);

	lua_pushstring(aLuaState,"y");
	lua_pushnumber(aLuaState,y/length);
	lua_settable(aLuaState,-3);

	return 0;
}

static int Vector2_GetNormalize(lua_State* aLuaState)
{
	int nrOfArguments = lua_gettop(aLuaState)-1;
	if(nrOfArguments > 0)
	{
		LUA_ASSERT(aLuaState,"Vector2.GetNormalize should not take any arguments");
	}

	lua_getfield(aLuaState,-1,"x");
	lua_getfield(aLuaState,-2,"y");

	Vector2_New(aLuaState);
	Vector2_Normalize(aLuaState);

	return 1;
}

static const luaL_Reg Vector2Functions[] =
{
	{"Length2", Vector2_Length2},
	{"Length", Vector2_Length},
	{"__mul", Vector2_Mul},
	{"Normalize", Vector2_Normalize},
	{"GetNormalize", Vector2_GetNormalize},
	{NULL,NULL}
};

LUAMOD_API int luaopen_Vector2Class(lua_State* aLuaState)
{
	luaL_newmetatable(aLuaState, "Vector2");
	lua_pushvalue(aLuaState, -1);
	lua_setfield(aLuaState, -2, "__index");

	luaL_setfuncs(aLuaState, Vector2Functions, 0);

	lua_newtable(aLuaState);
	lua_pushstring(aLuaState, "__call");
	lua_pushcfunction(aLuaState,Vector2_New);
	lua_settable(aLuaState,-3);
	lua_setmetatable(aLuaState,-2);
	return 1;
}