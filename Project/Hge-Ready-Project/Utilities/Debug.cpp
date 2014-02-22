#include "Debug.h"
#include <stdarg.h>
#include <stdio.h>
#include "DL_Assert.h"
#include "StackWalker\StackWalker.h"

#pragma warning(disable:4996)

#define SAFE_DELETE(pointer) if (pointer != NULL) delete(pointer); pointer = NULL

Debug* Debug::ourInstance(NULL);
File Debug::myDebugFile;
std::bitset<8> Debug::myDebugLevelFlags;

Debug::Debug(void)
{
}

Debug::~Debug(void)
{
}

bool Debug::Create(std::string aFile, std::bitset<8> someAssertFlags)
{
	ourInstance = new Debug();
	if(!ourInstance || !ourInstance->Init(aFile, someAssertFlags))
	{
		SAFE_DELETE(ourInstance);
		return false;
	}
	return true;
}

bool Debug::Destroy()
{
	if(ourInstance->myDebugFile.Close() == false)
	{
		return false;
	}
	SAFE_DELETE(ourInstance);
	if(ourInstance == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Debug::Init(std::string aFile, std::bitset<8> someAssertFlags)
{
	myDebugLevelFlags = someAssertFlags;
	return myDebugFile.Open(aFile, F_WRITE);
}

Debug* Debug::GetInstance()
{
	return ourInstance;
}

void Debug::AssertMessage(wchar_t* aFilePath, int aLineNumber, wchar_t* aFunctionName, wchar_t* aString)
{
	myDebugFile.WriteString("ASSERT: ");

	char pathBuffer[256];
	wcstombs(pathBuffer,aFilePath,256);
	std::string stringBuffer(pathBuffer);
	myDebugFile.WriteString("FILEPATH: ");
	myDebugFile.WriteString(stringBuffer);
	myDebugFile.WriteString(" ");
	myDebugFile.WriteString("LINE: ");
	myDebugFile.WriteInt(aLineNumber);

	char functionBuffer[256];
	wcstombs(functionBuffer,aFunctionName,256);
	stringBuffer = functionBuffer;
	myDebugFile.WriteString("FUNCTION: ");
	myDebugFile.WriteString(stringBuffer);
	myDebugFile.WriteString(" ");

	char messageBuffer[256];
	wcstombs(messageBuffer,aString,256);
	stringBuffer = messageBuffer;
	myDebugFile.WriteString("MESSAGE: ");
	myDebugFile.WriteString(stringBuffer);
	myDebugFile.WriteString("\n");

	BaseStackWalker sw;
	sw.ShowCallstack();
	_wassert(aString,aFilePath,static_cast<unsigned int>(aLineNumber));
}

void Debug::PrintMessage(std::string aString)
{
	myDebugFile.WriteString("MESSAGE: ");
	myDebugFile.WriteString(aString);
	myDebugFile.WriteString("\n");

	myDebugFile.FlushToDisk();
}

void Debug::CallStackMessage(std::string aString)
{
	myDebugFile.WriteString("CALLSTACK: ");
	myDebugFile.WriteString(aString);
	
	myDebugFile.FlushToDisk();
}

void Debug::DebugMessage(int aLineNumber, char* aFunctionName, ...)
{
	myDebugFile.WriteString("DEBUG: ");
	myDebugFile.WriteString("LINE ");
	myDebugFile.WriteInt(aLineNumber);
	myDebugFile.WriteString("- ");
	myDebugFile.WriteString("FUNCTION: ");
	std::string tempString(aFunctionName);
	tempString += " MESSAGE: ";
	myDebugFile.WriteString(tempString);
	va_list args;
	va_start (args, aFunctionName);
	char* currentChar = va_arg(args, char*);
	char buffer[256];
	vsnprintf(buffer,256,currentChar,args);
	va_end(args);
	tempString = buffer; 
	tempString += ("\n");
	myDebugFile.WriteString(tempString);

	
	myDebugFile.FlushToDisk();

	if(myDebugLevelFlags.test(DEBUG_MESSAGE) == true)
	{
		DL_ASSERT("DEBUG")
	}
}

void Debug::ErrorMessage(int aLineNumber, char* aFunctionName, ...)
{
	myDebugFile.WriteString("ERROR: ");
	myDebugFile.WriteString("LINE ");
	myDebugFile.WriteInt(aLineNumber);
	myDebugFile.WriteString("- ");
	myDebugFile.WriteString("FUNCTION: ");
	std::string tempString(aFunctionName);
	tempString += " MESSAGE: ";
	myDebugFile.WriteString(tempString);
	va_list args;
	va_start (args, aFunctionName);
	char* currentChar = va_arg(args, char*);
	char buffer[256];
	vsnprintf(buffer,256,currentChar,args);
	va_end(args);
	tempString = buffer; 
	tempString += ("\n");
	myDebugFile.WriteString(tempString);

	
	myDebugFile.FlushToDisk();

	if(myDebugLevelFlags.test(ERROR_MESSAGE) == true)
	{
		DL_ASSERT("ERROR")
	}
}

void Debug::SevereErrorMessage(int aLineNumber, char* aFunctionName, ...)
{
	myDebugFile.WriteString("SEVERE: ");
	myDebugFile.WriteString("LINE ");
	myDebugFile.WriteInt(aLineNumber);
	myDebugFile.WriteString("- ");
	myDebugFile.WriteString("FUNCTION: ");
	std::string tempString(aFunctionName);
	tempString += " MESSAGE: ";
	myDebugFile.WriteString(tempString);
	va_list args;
	va_start (args, aFunctionName);
	char* currentChar = va_arg(args, char*);
	char buffer[256];
	vsnprintf(buffer,256,currentChar,args);
	va_end(args);
	tempString = buffer; 
	tempString += ("\n");
	myDebugFile.WriteString(tempString);
	
	myDebugFile.FlushToDisk();

	if(myDebugLevelFlags.test(SEVERE_ERROR) == true)
	{
		DL_ASSERT("SEVERE")
	}
}

void Debug::CriticalErrorMessage(int aLineNumber, char* aFunctionName, ...)
{
	myDebugFile.WriteString("CRITICAL: ");
	myDebugFile.WriteString("LINE ");
	myDebugFile.WriteInt(aLineNumber);
	myDebugFile.WriteString("- ");
	myDebugFile.WriteString("FUNCTION: ");
	std::string tempString(aFunctionName);
	tempString += " MESSAGE: ";
	myDebugFile.WriteString(tempString);
	va_list args;
	va_start (args, aFunctionName);
	char* currentChar = va_arg(args, char*);
	char buffer[256];
	vsnprintf(buffer,256,currentChar,args);
	va_end(args);
	tempString = buffer; 
	tempString += ("\n");
	myDebugFile.WriteString(tempString);
	
	myDebugFile.FlushToDisk();

	if(myDebugLevelFlags.test(CRITICAL_ERROR) == true)
	{
		DL_ASSERT("CRITICAL")
	}
}