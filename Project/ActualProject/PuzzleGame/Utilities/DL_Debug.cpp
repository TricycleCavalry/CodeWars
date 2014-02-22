#include "DL_Debug.h"
#include "DL_Assert.h"
#include "CommonMacros.h"
#include <ctime>
#include "GrowingArray.h"

#pragma warning(disable: 4996)
DL_Debug* DL_Debug::ourInstance(NULL);
File DL_Debug::myDebugFile;
bitset<4> DL_Debug::myAssertFlags;


DL_Debug::DL_Debug(void)
:	myLogs(new GrowingArray<DebugLogStruct>(8))
{	
}

DL_Debug::~DL_Debug(void)
{
}

bool DL_Debug::Create(std::string aFile, std::bitset<4> someAssertFlags)
{
	ourInstance = new DL_Debug();
	if(ourInstance == NULL || ourInstance->Init(aFile,someAssertFlags) == false)
	{
		SAFE_DELETE(ourInstance);
		return false;
	}
	else
	{
		ourInstance->Init(aFile,someAssertFlags);
	}
	return true;
	
}
bool DL_Debug::Destroy()
{
	if(ourInstance->myDebugFile.Close()==false)
	{
		return false;
	}
	if(ourInstance!=NULL)
	{
		SAFE_DELETE(ourInstance);
		return true;
	}
	DL_ASSERT("Instance doesn't exist!");
	return false;
}

DL_Debug* DL_Debug::GetInstance()
{
	return ourInstance;
}
bool DL_Debug::Init(std::string aFile,std::bitset<4> someAssertFlags)
{
	myAssertFlags = someAssertFlags;
	return myDebugFile.Open(aFile,2);
}

void DL_Debug::AssertMessage(wchar_t* aFilePath,int aLine,wchar_t* aFunction, char* aMessage)
{
	const size_t cSize = strlen(aMessage)+1;
	std::wstring wc(cSize,L'#');
	mbstowcs(&wc[0],aMessage,cSize);
	AssertMessage(aFilePath,aLine,aFunction,(wchar_t*)wc.c_str());
}

void DL_Debug::AssertMessage(wchar_t* aFilePath,int aLine,wchar_t* aFunction, wchar_t* aMassasge)
{
	myDebugFile.WriteString("ASSERT_MESSAGE:");	
	char filePathBuffer[256];
	wcstombs(filePathBuffer,aFilePath,256);
	string filePath(filePathBuffer);
	myDebugFile.WriteString("\n\tFile Path:\t");
	myDebugFile.WriteString(filePath);
	myDebugFile.WriteString("\n\tLine:\t\t");
	myDebugFile.WriteInt(aLine);

	char functionBuffer[256];
	wcstombs(functionBuffer,aFunction,256);
	string functionName(functionBuffer);
	myDebugFile.WriteString("\n\tFunction:\t");
	myDebugFile.WriteString(functionName);

	char messageBuffer[256];
	wcstombs(messageBuffer,aMassasge,256);
	string messsage(messageBuffer);
	myDebugFile.WriteString("\n\tMessage:\t");
	myDebugFile.WriteString(messsage);

	myDebugFile.WriteString("\n\nCALL_STACK:\n");
	
	BaseStackWalker stackWalker;
	stackWalker.ShowCallstack();
	_wassert(aMassasge,aFilePath,aLine);


}

void DL_Debug::PrintMessage(string aString)
{
	myDebugFile.WriteString("MESSAGE:");

	myDebugFile.WriteString("\n\t");
	myDebugFile.WriteString(aString);
	myDebugFile.WriteString("\n\n");
	myDebugFile.FlushToDisk();
}
void DL_Debug::CallStack(string aString)
{
	myDebugFile.WriteString("\t");
	myDebugFile.WriteString(aString);
	myDebugFile.WriteString("\n");
	myDebugFile.FlushToDisk();
}
void DL_Debug::DebugMessage(int aLine,char* aFunction , ...)
{
	myDebugFile.WriteString("DEBUG_MESSAGE:\n");
	va_list args;
	va_start(args,aFunction);
	WriteMessage(aLine,aFunction,args);
	va_end(args);
	assert(!myAssertFlags.test(ASSERT_DEBUG)  && "DEBUG");
	
}
void DL_Debug::ErrorMessage(int aLine,char* aFunction, ...)
{
	myDebugFile.WriteString("ERROR_MESSAGE:\n");
	va_list args;
	va_start(args,aFunction);
	WriteMessage(aLine,aFunction,args);
	va_end(args);
	assert(!myAssertFlags.test(ASSERT_ERROR) && "ERROR");
}
void DL_Debug::SevereErrorMessage(int aLine,char* aFunction, ...)
{
	myDebugFile.WriteString("SEVER_ERROR_MESSAGE:\n");
	va_list args;
	va_start(args,aFunction);
	WriteMessage(aLine,aFunction,args);
	va_end(args);
	assert(!myAssertFlags.test(ASSERT_SEVERE) && "SEVER_ERROR");
}
void DL_Debug::CriticalErrorMessage(int aLine,char* aFunction, ...)
{
	myDebugFile.WriteString("CRITICAL_ERROR_MESSAGE:\n");
	va_list args;
	va_start(args,aFunction);
	WriteMessage(aLine,aFunction,args);
	va_end(args);
	assert(!myAssertFlags.test(ASSERT_CRITICAL) && "CRITICAL_ERROR");
}
void DL_Debug::WriteLog(const char* aLogName,...)
{
	int logIndex = FindLog(aLogName);
	if(logIndex != -1 && (*myLogs)[logIndex].myIsActivated == true)
	{
		SYSTEMTIME systemTime;
		GetLocalTime(&systemTime);

		string arguments ="";
		va_list args;
		va_start(args,aLogName);
		char* currentChar = NULL;
		currentChar = va_arg(args,char*);
		if(currentChar != NULL)
		{		
			char buffer[256];		
			vsnprintf(buffer,256,currentChar,args);
			arguments = buffer;
		};
		va_end(args);

		char buff[256];
		sprintf(buff, "[%i:%i:%i:%i][%s] %s\n", systemTime.wHour,systemTime.wMinute,systemTime.wSecond,systemTime.wMilliseconds,aLogName,arguments.c_str());
		std::string time = buff;

		myDebugFile.WriteString(time);
		myDebugFile.FlushToDisk();
	}	
}
void DL_Debug::ToggleLog(const char* aLogName, bool anActivationFlag)
{
	int logIndex = FindLog(aLogName);
	if(logIndex != -1)
	{
		(*myLogs)[logIndex].myIsActivated = anActivationFlag;
	}
	else if(anActivationFlag == true)
	{
		(*myLogs).Add(DebugLogStruct(aLogName,anActivationFlag));
	}
}
void DL_Debug::WriteMessage(int aLine,char* aFunction ,va_list args)
{
	myDebugFile.WriteString("\tLine:\t\t");
	myDebugFile.WriteInt(aLine);
	myDebugFile.WriteString("\n\tFunction:\t");
	string functionName(aFunction);
	myDebugFile.WriteString(functionName);

	char* currentChar = NULL;
	currentChar = va_arg(args,char*);
	if(currentChar != NULL)
	{		
		char buffer[256];		
		vsnprintf(buffer,256,currentChar,args);
		string arguments(buffer);
		myDebugFile.WriteString("\n\tArguments:\t");
		myDebugFile.WriteString(arguments);
	};		
	myDebugFile.WriteString("\n\n");
	myDebugFile.FlushToDisk();
}

int DL_Debug::FindLog(const char* aLogName)
{
	for(int i=0,count=(*myLogs).Count();i<count;i++)
	{
		if((*myLogs)[i].myLogName == aLogName)
		{
			return i;
		}
	}
	return -1;
}