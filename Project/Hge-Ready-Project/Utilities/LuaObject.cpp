#include "luaobject.h"
#include "LuaState.h"

// Define the Lua ClassName

const char LuaGameObject::myClassName[] = "LuaGameObject";

// Define the methods we will expose to Lua
// Check luaobject.h for the definitions...

LuaBind<LuaGameObject>::FunctionInfo LuaGameObject::myExposedFunctions[] = 
{
	CLASS_FUNCTION_LUA(LuaGameObject, "setAttr", setAttr),
	CLASS_FUNCTION_LUA(LuaGameObject, "getAttr", getAttr),
	CLASS_FUNCTION_LUA(LuaGameObject, "getMessage", getMessage),
	CLASS_FUNCTION_LUA(LuaGameObject, "setMessage", setMessage),
	{0,0}
};

LuaBind<LuaGameObject>::VariableInfo LuaGameObject::myExposedVariables[] =
{
	CLASS_VARIABLE_LUA(LuaGameObject, "atr" , getAttr, setAttr),
	CLASS_VARIABLE_LUA(LuaGameObject, "msg" , getMessage, setMessage),
	{0,0}
};

LuaGameObject::LuaGameObject(lua_State *L){
	real_object = GetLinkedInstanceClassPointer(GameObject,L);
}

void LuaGameObject::setObject(lua_State *L){
  real_object = GetLinkedInstanceClassPointer(GameObject,L);
}

int LuaGameObject::setAttr(lua_State *L)
{
	int arguments = lua_gettop(L);
	int argument = lua_tointeger(L,-1);
	real_object->setAttr(argument);
	return 0;
}
int LuaGameObject::getAttr(lua_State *L){
  lua_pushnumber(L, real_object->getAttr());
  return 1;
}

int LuaGameObject::setMessage(lua_State *L){
  real_object->setMessage(lua_tostring(L, -1));
  return 0;
}
int LuaGameObject::getMessage(lua_State *L){
  lua_pushstring(L, real_object->getMessage());
  return 1;
}

LuaGameObject::~LuaGameObject(){
  printf("deleted Lua Object (%p)\n", this);
}