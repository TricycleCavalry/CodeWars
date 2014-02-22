#include "stdafx.h"
#include "ExceptionHandler.h"

#include <direct.h>

std::string ExceptionHandler::myDumpType = "NoDump";

ExceptionHandler::ExceptionHandler(void)
{
}


ExceptionHandler::~ExceptionHandler(void)
{
}

LONG WINAPI ExceptionHandler::CreateDump(EXCEPTION_POINTERS* someExceptionPointers)
{
	std::string fileName = myDumpType;
	ExceptionHandlerDumpType dumpType = GetType(fileName);
	if(dumpType != EHDT_NODUMP && MessageBox(0,"The game has crashed for some unexpected reason, do you wish to create a dumpFile so the programmers can debug it?\n \
											   Don't forget: Work, work!","Oh noes!",MB_YESNO) == IDYES)
	{
		_chdir("../");
		fileName += "Dump.dmp";
		HANDLE fileHandle = CreateFile( fileName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

		if((fileHandle != NULL)  && (fileHandle != INVALID_HANDLE_VALUE))
		{
			MINIDUMP_EXCEPTION_INFORMATION mdei;

			mdei.ThreadId			= GetCurrentThreadId();
			mdei.ExceptionPointers	= someExceptionPointers;
			mdei.ClientPointers		= FALSE;

			BOOL rv = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), fileHandle, GetType(dumpType)
										, (someExceptionPointers != 0) ? &mdei : 0, 0, 0);
			if(!rv)
			{
				printf("DumpWrite failed. Error: %u \n", GetLastError());
			}
			else
			{
				printf("Minidump created.\n");
			}

			// Close the file 

			CloseHandle(fileHandle);
		}
		else
		{
			printf("Create File failed. Error: %u \n", GetLastError());
		}
	}
	return EXCEPTION_EXECUTE_HANDLER;
}

void ExceptionHandler::SetExceptionFilter(int argc, LPSTR argv)
{
	SetUnhandledExceptionFilter(ExceptionHandler::CreateDump);
	if(argc > 1)
	{
		std::string type = argv;
		int firstDash = type.find_first_of('-')+1;
		type.erase(type.begin(),type.begin()+firstDash);
		int endOfWord = type.find_first_of(' ');
		if(endOfWord != -1)
		{
			type.erase(type.begin()+endOfWord,type.end());
		}

		if(GetType(type) != EHDT_NODUMP)
		{
			myDumpType = type;
		}
	}
}

MINIDUMP_TYPE ExceptionHandler::GetType(const ExceptionHandlerDumpType& aType)
{
	MINIDUMP_TYPE mdt;
	switch(aType)
	{
	case EHDT_TINY:
		mdt = MiniDumpNormal;
		break;
	case EHDT_MINI:
		mdt = (MINIDUMP_TYPE) (MiniDumpWithIndirectlyReferencedMemory | MiniDumpScanMemory);
		break;
	case EHDT_MIDI:
		mdt = (MINIDUMP_TYPE)	(MiniDumpWithPrivateReadWriteMemory | MiniDumpWithDataSegs | 
								MiniDumpWithHandleData | MiniDumpWithFullMemoryInfo | 
								MiniDumpWithThreadInfo | MiniDumpWithUnloadedModules ); 
		break;
	case EHDT_MAXI:
		mdt = (MINIDUMP_TYPE)	(MiniDumpWithFullMemory | MiniDumpWithFullMemoryInfo |
								MiniDumpWithHandleData | MiniDumpWithThreadInfo | 
								MiniDumpWithUnloadedModules ); 
		break;
	}
	return mdt;
}

ExceptionHandlerDumpType ExceptionHandler::GetType(std::string& aDumpType)
{
	ExceptionHandlerDumpType returnType = EHDT_NODUMP;
	if(aDumpType == "Tiny")
	{
		returnType = EHDT_TINY;
	}
	else if(aDumpType == "Mini")
	{
		returnType = EHDT_MINI;
	}
	else if(aDumpType == "Midi")
	{
		returnType = EHDT_MIDI;
	}
	else if(aDumpType == "Maxi")
	{
		returnType = EHDT_MAXI;
	}
	else
	{
		aDumpType = "NoDump";
	}
	return returnType;
}