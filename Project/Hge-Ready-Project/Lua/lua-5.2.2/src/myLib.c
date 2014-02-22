#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define myLib_c
#define LUA_LIB

#include "lua.h"

#include "lauxlib.h"
#include "lualib.h"

static int myLib_ListFilesInDirectory(lua_State* aLuaState)
{
	luaL_dostring(aLuaState,"Print(\"This feature has not yet been implemented\")");
	return 0;
}

static const luaL_Reg myLibFuncs[] =
{
	{"ListFilesInDirectory", myLib_ListFilesInDirectory},
	{NULL,NULL}
};

LUAMOD_API int luaopen_myLib(lua_State *aLuaState)
{
	luaL_newlib(aLuaState, myLibFuncs);
	return 1;
}