/**
 * This is the wrapper around the C++ object found in object.cc
 * Everything this object has done to it is passed on FROM Lua to the real C++
 * object through the pointer 'real_object'
 * Notice that I kept the function names the same for simplicity.
 */
#ifndef _luaobject_h_
#define _luaobject_h_

// Need to include lua headers this way
extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

// I am using luna
#include "LuaBind.h"
// The header file for the real C++ object
#include "object.h"

class LuaGameObject{
public:
  // Constants
  static const char myClassName[];
  static LuaBind<LuaGameObject>::FunctionInfo myExposedFunctions[];
  static LuaBind<LuaGameObject>::VariableInfo myExposedVariables[];

  // Initialize the pointer
  LuaGameObject(lua_State *L);
  ~LuaGameObject();
  void setObject(lua_State *L);

  // Methods we will need to use
  int getAttr(lua_State *L);
  int setAttr(lua_State *L);
  int getMessage(lua_State *L);
  int setMessage(lua_State *L);
private:
  // The pointer to the 'real object' defined in object.cc
  GameObject* real_object;
};
#endif