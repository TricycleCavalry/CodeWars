#ifndef _LUA_BIND_HEADER_
#define _LUA_BIND_HEADER_

#include "Debug.h"
#include <lua.hpp>

//Macro for setting the class' exposed Functions
#define CLASS_FUNCTION_LUA(aClass, aFunctionNameInLua, aFunction) {aFunctionNameInLua, &aClass::aFunction}

//Macro for setting the class' exposed Variables
//It's Get and Set Functions need to be "Set"+VariableName
#define CLASS_VARIABLE_LUA( aClass, aVariableNameInLua, aGetFunction, aSetFunction) {aVariableNameInLua , &aClass::aGetFunction , &aClass::aSetFunction }

template<class Type> class LuaBind
{
private:
	LuaBind();
public:
	static void RegisterClassToLua(lua_State* aLuaState)
	{
		//Set the Constructor for the class
		lua_pushcfunction(aLuaState, &LuaBind<Type>::Constructor);
		lua_setglobal(aLuaState, Type::myClassName);

		//Set the destructor for the class
		luaL_newmetatable(aLuaState,Type::myClassName);
		lua_pushstring(aLuaState, "__gc");
		lua_pushcfunction(aLuaState, &LuaBind<Type>::Destructor);
		lua_settable(aLuaState, -3);
	}

	//Use This Function When there is only 1 instance of the class
	static void LinkClassToLua(lua_State* aLuaState, Type* aPointerToClass)
	{
		lua_settop(aLuaState,0);

		lua_newtable(aLuaState);

		lua_pushnumber(aLuaState,0);

		Type** pointerToObjectAdress = static_cast<Type**>(lua_newuserdata(aLuaState, sizeof(Type*)));
		*pointerToObjectAdress = aPointerToClass;

		luaL_newmetatable(aLuaState, Type::myClassName);

		lua_setmetatable(aLuaState, -2);

		lua_settable(aLuaState, -3);

		RegisterFunctions(aLuaState);
		RegisterVariables(aLuaState);

		lua_setglobal(aLuaState,Type::myClassName);
	}

	//This function creates the table and sets upp all the fields  of it
	//It also allocates the object that is to be called
	static int Constructor(lua_State* aLuaState)
	{
		Type* objectPointer = new Type(aLuaState);

		//Clear the stack
		lua_settop(aLuaState,0);

		//The table containing the class
		lua_newtable(aLuaState);

		//Which index the objectPointer shall be placed
		lua_pushnumber(aLuaState, 0);

		//Create the pointer to the ObjectPointer which the luaScript will refer to
		Type** pointerToObjectAdress = static_cast<Type**>(lua_newuserdata(aLuaState, sizeof(Type*)));
		//Set the pointer to point to the objectPointer
		*pointerToObjectAdress = objectPointer;

		//Push the class's metatable onto the top of the stack
		luaL_getmetatable(aLuaState,Type::myClassName);

		//Set the metatable of the table (assigning the destructor of the class)
		lua_setmetatable(aLuaState, -2);

		//Set the tables first index to contain the objectPointer
		//table[0] = objectPointer
		lua_settable(aLuaState, -3);

		//Register the Functions
		RegisterFunctions(aLuaState);

		//Register the Variables
		RegisterVariables(aLuaState);

		//Since the table is the only thing left on the stack we return the top, hence the "1"
		return 1;
	}

	static void RegisterFunctions(lua_State* aLuaState)
	{
		for(int i=0; Type::myExposedFunctions[i].myFunctionName ; i++)
		{
			lua_pushstring(aLuaState, Type::myExposedFunctions[i].myFunctionName);
			lua_pushnumber(aLuaState, i);
			lua_pushcclosure(aLuaState, &LuaBind<Type>::CallFunction, 1);
			lua_settable(aLuaState, -3);
		}
	}

	static void RegisterVariables(lua_State* aLuaState)
	{
		for(int i=0; Type::myExposedVariables[i].myVariableName ; i++)
		{
			lua_pushstring(aLuaState, Type::myExposedVariables[i].myVariableName);
			lua_pushnumber(aLuaState, i);
			lua_pushcclosure(aLuaState,  &LuaBind<Type>::CallVariable, 1);
			lua_settable(aLuaState, -3);
		}
	}

	static int CallFunction(lua_State* aLuaState)
	{
		//Get the Object
		int index = static_cast<int>(lua_tonumber(aLuaState, lua_upvalueindex(1)));
		lua_pushnumber(aLuaState,0);
		lua_gettable(aLuaState,1);

		Type* objectPointer = *static_cast<Type**>(luaL_checkudata(aLuaState,-1,Type::myClassName));
		lua_pop(aLuaState,1);

		//Call on the corresponding Function using the functionPointers in the array
		return (objectPointer->*(Type::myExposedFunctions[index].myFunction))(aLuaState);
	}

	static int CallVariable(lua_State* aLuaState)
	{
		int index = static_cast<int>(lua_tonumber(aLuaState, lua_upvalueindex(1)));
		lua_pushnumber(aLuaState,0);
		lua_gettable(aLuaState,1);

		Type* objectPointer = *static_cast<Type**>(luaL_checkudata(aLuaState,-1,Type::myClassName));
		lua_pop(aLuaState,1);

		int nrOfArguments = lua_gettop(aLuaState)-1;

		if(nrOfArguments == 0)
		{
			(objectPointer->*(Type::myExposedVariables[index].myGetFunction))(aLuaState);
			return 1;
		}
		else if(nrOfArguments == 1)
		{
			(objectPointer->*(Type::myExposedVariables[index].mySetFunction))(aLuaState);
			return 0;
		}
		else
		{
			DL_ASSERT("Too many arguments for assignment of variable!");
			return -1;
		}
	}

	static int Destructor(lua_State* aLuaState)
	{
		Type* objectPointer = *static_cast<Type**>(luaL_checkudata(aLuaState,-1,Type::myClassName));
		delete(objectPointer);
		objectPointer = NULL;
		return 0;
	}

	struct FunctionInfo
	{
		const char* myFunctionName;
		int(Type::*myFunction)(lua_State*);
	};

	struct VariableInfo
	{
		const char* myVariableName;
		int(Type::*myGetFunction)(lua_State*);
		int(Type::*mySetFunction)(lua_State*);
	};
};

#endif