#include "LuaState.h"
#include "Debug.h"
#include <lua.hpp>

LuaState* LuaState::myInstance = NULL;

///--------------Lua Stuff------------///

const char LuaState::myClassName[] = "LuaManager";

LuaBind<LuaState>::FunctionInfo LuaState::myExposedFunctions[] =
{
	CLASS_FUNCTION_LUA(LuaState, "PrintDebug", PrintDebugMessageLua),
	CLASS_FUNCTION_LUA(LuaState, "Assert", AssertLua),
	CLASS_FUNCTION_LUA(LuaState, "RunFile", RunFileLua),
	{0,0}
};

LuaBind<LuaState>::VariableInfo LuaState::myExposedVariables[] =
{
	{0,0}
};

int LuaState::PrintDebugMessageLua(lua_State* aLuaState)
{
	int numberOfArguments = NrOfArguments();
	std::string completeMessage = "Lua DebugMessage: ";
	for(int i=numberOfArguments;i>0;i--)
	{
		std::string message = lua_tostring(aLuaState,-i);
		completeMessage += message;
	}
	DL_PRINT(completeMessage.c_str());
	return 0;
}

int LuaState::AssertLua(lua_State* aLuaState)
{
	int numberOfArguments = NrOfArguments();
	std::string completeMessage = "Lua Assert: ";
	for(int i=numberOfArguments;i>0;i--)
	{
		std::string message = lua_tostring(aLuaState,-i);
		completeMessage += message;
	}
	DL_CRITICAL(completeMessage.c_str());
	DL_ASSERT("Crash in LUA");
	return 0;
}

int LuaState::RunFileLua(lua_State* aLuaState)
{
	int numberOfArguments = NrOfArguments();
	if(numberOfArguments > 1)
	{
		DL_CRITICAL("Too many arguments while trying to run a script from lua");
		DL_ASSERT("Too many arguments on RunFile-Call");
	}
	std::string filePath = lua_tostring(aLuaState,-1);
	RunFile(filePath);
	return 0;
}

///--------------Static Singleton Functions------------///

void LuaState::Create()
{
	if(myInstance != NULL)
	{
		DL_ASSERT("Instance of Object already exists!");
	}

	myInstance = new LuaState();
}

LuaState* LuaState::GetInstance()
{
	return myInstance;
}

void LuaState::Destroy()
{
	myInstance->~LuaState();
}

///--------------Public Functions------------///

void LuaState::LoadScript(const std::string& aFilePath, const std::string& aScriptName)
{
	lua_getglobal(myLuaState,"HostScripts");
	lua_pushstring(myLuaState,aScriptName.c_str());
	lua_newtable(myLuaState);
	lua_settable(myLuaState,-3);
	lua_getfield(myLuaState,-1,aScriptName.c_str());

	lua_newtable(myLuaState);
	lua_pushstring(myLuaState,"__call");
	
	LoadFile(aFilePath);
	
	lua_settable(myLuaState,-3);
	lua_setmetatable(myLuaState,-2);
	lua_pop(myLuaState,1);

	myScripts.Add(ScriptStruct(aScriptName,aFilePath,GetLastModifiedTime(aFilePath)));
}

void LuaState::ReloadScripts()
{
	FILETIME lastWrittenTime;
	for(int i=0,count=myScripts.Count();i<count;i++)
	{
		lastWrittenTime = GetLastModifiedTime(myScripts[i].myFilePath);

		if(myScripts[i].myLastModifiedDate.dwHighDateTime != lastWrittenTime.dwHighDateTime || myScripts[i].myLastModifiedDate.dwLowDateTime != lastWrittenTime.dwLowDateTime)
		{
			PushScriptFromTable(myScripts[i].myScriptName.c_str());
			lua_getmetatable(myLuaState,-1);
			
			LoadFile(myScripts[i].myFilePath);

			myScripts[i].myLastModifiedDate = lastWrittenTime;

			lua_setfield(myLuaState,-2,"__call");
			lua_pop(myLuaState,1);
		}
	}
}

void LuaState::RunScript(const std::string& aScriptName, int aNrOfArguments, int aNrOfResults, int aMessageHandler)
{
	for(int i=0, count=myScripts.Count();i<count;i++)
	{
		if(myScripts[i].myScriptName == aScriptName)
		{
			PushScriptFromTable(myScripts[i].myScriptName);
			Run(aNrOfArguments,aNrOfResults,aMessageHandler);
			return;
		}
	}

	DL_CRITICAL("lua-Script %s was not found, please contact programmer!",aScriptName.c_str());
	DL_ASSERT("Crash");	
}

void LuaState::RunFile(const std::string& aFilePath, int aNrOfArguments, int aNrOfResults, int aMessageHandler)
{
	LoadFile(aFilePath);
	Run(aNrOfArguments,aNrOfResults,aMessageHandler);
}

void LuaState::RunString(const std::string& aStringToRun, const bool& aConsoleFlag)
{
	int status = luaL_dostring(myLuaState,aStringToRun.c_str());
	if(status != 0)
	{
		ErrorReport(status, aConsoleFlag == false);
	}
}

void LuaState::RegisterFunctionToLua(const std::string& aFunctionName, void (*aFunctionPtr))
{
	lua_register(myLuaState,aFunctionName.c_str(),reinterpret_cast<lua_CFunction>(aFunctionPtr));
}

void LuaState::LinkObjectToLua(void* aPointerToInstanceOfClass, const std::string& aNameOfVariable)
{
	//Push the pointer to the object onto the Lua Stack
	lua_pushlightuserdata(myLuaState,aPointerToInstanceOfClass);
	//Set the recently pushed pointer to react on this variable name in LUA
	lua_setglobal(myLuaState,aNameOfVariable.c_str());
}

void* LuaState::GetPointerToInstanceOfLinkedClassObject(const std::string& aClassName)
{
	void* pointerToClassObject = lua_touserdata(myLuaState, 1);
	if(pointerToClassObject != NULL)
	{
		return pointerToClassObject;
	}
	
	DL_CRITICAL("No Linked Object of the class: \"%s\" and name exists, check name of the linked instance and class\n \
				Crash While Getting Pointer To Linked Instance Of Object (it's constructor)", aClassName.c_str());
	DL_ASSERT("Crash");
	return NULL;
}

int LuaState::NrOfArguments()
{
	return lua_gettop(myLuaState)-1;
}


///--------------Private Functions------------///

void LuaState::OpenLibraries()
{
	luaL_openlibs(myLuaState);
}

FILETIME LuaState::GetLastModifiedTime(const std::string& aFilePath)
{
	HANDLE fileHandle = CreateFile(aFilePath.c_str(), GENERIC_READ,FILE_SHARE_DELETE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	FILETIME lastModifiedTime;
	GetFileTime(fileHandle,NULL,NULL,&lastModifiedTime);
	CloseHandle(fileHandle);
	return lastModifiedTime;
}

void LuaState::PushScriptFromTable(const std::string& aScriptName)
{
	lua_getglobal(myLuaState,"HostScripts");
	lua_getfield(myLuaState,-1,aScriptName.c_str());
	lua_insert(myLuaState,-2);
	lua_pop(myLuaState,1);
}

void LuaState::CreateScriptsTable()
{
	lua_newtable(myLuaState);
	lua_setglobal(myLuaState,"HostScripts");
}

std::string LuaState::GetScriptName(const std::string& aFilePath)
{
	for(int i=0,count=myScripts.Count();i<count;i++)
	{
		if(myScripts[i].myFilePath == aFilePath)
		{
			return myScripts[i].myScriptName;
		}
	}
	return "NULL";
}

int LuaState::FindScript(const std::string& aScriptName)
{
	for(int i=0,count=myScripts.Count();i<count;i++)
	{
		if(myScripts[i].myScriptName == aScriptName)
		{
			return i;
		}
	}
	return -1;
}

void LuaState::Run(int aNrOfArguments, int aNrOfResults, int aMessageHandler)
{
	int status = lua_pcall(myLuaState,aNrOfArguments,aNrOfResults,aMessageHandler);
	ErrorReport(status);
}

void LuaState::ErrorReport(int aStatus, bool aCrashFlag)
{
	if(aStatus != 0)
	{
		std::string errorString = lua_tostring(myLuaState, -1);
		if(aCrashFlag == true)
		{
			DL_CRITICAL("Lua Error: %s \n", errorString.c_str());
			DL_ASSERT("Lua Error!");
		}
		else
		{
			DL_DEBUG("Lua Error: %s \n", errorString.c_str());
			lua_pop(myLuaState, 1);
		}
	}
}

void LuaState::LoadFile(const std::string& aFilePath)
{
	int status = luaL_loadfile(myLuaState, aFilePath.c_str());
	if(status != 0)
	{
		DL_DEBUG("Lua LoadFile Error: \n");
		ErrorReport(status);
	}
}



///--------------Constructor & Destructor------------///

LuaState::LuaState()
:	myLuaState(luaL_newstate())
,	myScripts(4)
{
	OpenLibraries();
	CreateScriptsTable();
	myLuaState->myLuaStatePointer = reinterpret_cast<void*>(this);
	LuaBind<LuaState>::LinkClassToLua(myLuaState,this);
}

LuaState::~LuaState()
{
	myScripts.RemoveAll();
	lua_close(myLuaState);
}