#ifndef _SCRIPT_STRUCT_HEADER_
#define _SCRIPT_STRUCT_HEADER_

#include <string>
#include "windows.h"

struct ScriptStruct
{
	std::string myScriptName;
	std::string myFilePath;
	FILETIME myLastModifiedDate;

	ScriptStruct()
	:	myScriptName("")
	,	myFilePath("")
	{
	}

	ScriptStruct(const std::string& aScriptName, const std::string& aFilePath, const FILETIME& aLastModifiedDate)
	:	myScriptName(aScriptName)
	,	myFilePath(aFilePath)
	,	myLastModifiedDate(aLastModifiedDate)
	{
	}
};

#endif