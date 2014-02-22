#ifndef _LUA_STATE_HEADER_
#define _LUA_STATE_HEADER_

#include <string>
#include "LuaBind.h"
#include "lstate.h"

#include "GrowingArray.h"
#include "ScriptStruct.h"

#define GetLinkedInstanceClassPointer(aClassName, aLuaState) reinterpret_cast<aClassName*>(LuaState::GetLuaState(aLuaState)->GetPointerToInstanceOfLinkedClassObject(#aClassName))

class LuaState
{
public:
	static const char myClassName[];
	static LuaBind<LuaState>::FunctionInfo myExposedFunctions[];
	static LuaBind<LuaState>::VariableInfo myExposedVariables[];

	int PrintDebugMessageLua(lua_State* aLuaState);
	int AssertLua(lua_State* aLuaState);
	int RunFileLua(lua_State* aLuaState);

public:
	static void Create();
	static LuaState* GetInstance();

	void Destroy();

public:
	void LoadScript(const std::string& aFilePath, const std::string& aScriptName);
	void ReloadScripts();

	void RunScript(const std::string& aScriptName, int aNrOfArguments = 0, int aNrOfResults = LUA_MULTRET, int aMessageHandler = 0);
	void RunFile(const std::string& aFilePath, int aNrOfArguments = 0, int aNrOfResults = LUA_MULTRET, int aMessageHandler = 0);
	void RunString(const std::string& aStringToRun, const bool& aConsoleFlag = false);

	void RegisterFunctionToLua(const std::string& aFunctionName, void (*aFunctionPtr));
	template<class Type>
	void RegisterClassToLua() { LuaBind<Type>::RegisterClassToLua(myLuaState); }

	template<class Type>
	void LinkClassToLua(Type* aPointerToClass) { LuaBind<Type>::LinkClassToLua(myLuaState,aPointerToClass); }
	void LinkObjectToLua(void* aPointerToInstanceOfClass, const std::string& aNameOfInstance);

	void* GetPointerToInstanceOfLinkedClassObject(const std::string& aClassName);

	inline static LuaState* GetLuaState(lua_State* aLuaState) { return reinterpret_cast<LuaState*>(aLuaState->myLuaStatePointer); }
	inline operator lua_State*() { return myLuaState; }

	int NrOfArguments();

private:
	void OpenLibraries();

	FILETIME GetLastModifiedTime(const std::string& aFilePath);
	void PushScriptFromTable(const std::string& aScriptName);
	void CreateScriptsTable();

	std::string GetScriptName(const std::string& aFilePath);
	int FindScript(const std::string& aScriptName);

	void Run(int aNrOfArguments, int aNrOfResults, int aMessageHandler);
	void ErrorReport(int aStatus, bool aCrashFlag = true);
	void LoadFile(const std::string& aFilePath);
	


	GrowingArray<ScriptStruct> myScripts;
	lua_State* myLuaState;

private:
	LuaState(void);
	~LuaState(void);

	static LuaState* myInstance;
};

#endif