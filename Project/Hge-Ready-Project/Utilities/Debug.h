#ifndef _DEBUG_
#define _DEBUG_

#include <string>
#include <bitset>
#include "File.h"

enum ErrorLevels
{
	DEBUG_MESSAGE,
	ERROR_MESSAGE,
	SEVERE_ERROR,
	CRITICAL_ERROR,

	D_DEBUG = 1,
	D_ERROR = 2,
	D_SEVERE = 4,
	D_CRITICAL = 8
};

#define DL_ASSERT(message) Debug::GetInstance()->AssertMessage(_CRT_WIDE(__FILE__),__LINE__,_CRT_WIDE(__FUNCTION__),_CRT_WIDE(message));
#define DL_PRINT(message)  Debug::GetInstance()->PrintMessage(message);
#define DL_CALLSTACK(message) Debug::GetInstance()->CallStackMessage(message);
#define DL_DEBUG(...)  Debug::GetInstance()->DebugMessage(__LINE__,__FUNCTION__,__VA_ARGS__);
#define DL_ERROR(...)	Debug::GetInstance()->ErrorMessage(__LINE__,__FUNCTION__,__VA_ARGS__);
#define DL_SEVERE(...)	Debug::GetInstance()->SevereErrorMessage(__LINE__,__FUNCTION__,__VA_ARGS__);
#define DL_CRITICAL(...)	Debug::GetInstance()->CriticalErrorMessage(__LINE__,__FUNCTION__,__VA_ARGS__);

class Debug
{
public:
	static bool Create(std::string aFile = "DebugLogger.txt", std::bitset<8> someAssertFlags = D_SEVERE | D_CRITICAL);
	static bool Destroy();

	static Debug* GetInstance();
	
	void AssertMessage(wchar_t* aFilePath, int aLineNumber, wchar_t* aFunctionName, wchar_t* aString);
	void PrintMessage(std::string aString);
	void CallStackMessage(std::string aString);
	void DebugMessage(int aLineNumber, char* aFunctionName, ...);
	void ErrorMessage(int aLineNumber, char* aFunctionName, ...);
	void SevereErrorMessage(int aLineNumber, char* aFunctionName, ...);
	void CriticalErrorMessage(int aLineNumber, char* aFunctionName, ...);

private:
	Debug(void);
	~Debug(void);
	static bool Init(std::string aFile, std::bitset<8> someAssertFlags);
	static Debug* ourInstance;
	static File myDebugFile;
	static std::bitset<8> myDebugLevelFlags;
};

#endif