#ifndef _EXCEPTION_HANDLER_HEADER_
#define _EXCEPTION_HANDLER_HEADER_

#include <Windows.h>
#include <DbgHelp.h>


#include <string>

enum ExceptionHandlerDumpType
{
	EHDT_NODUMP,
	EHDT_TINY,
	EHDT_MINI,
	EHDT_MIDI,
	EHDT_MAXI,
};

class ExceptionHandler
{
	ExceptionHandler(void);
	~ExceptionHandler(void);
public:
	static LONG WINAPI CreateDump(EXCEPTION_POINTERS* someExceptionPointers);

	static void SetExceptionFilter(int argc, LPSTR argv);

	static std::string myDumpType;
private:
	static MINIDUMP_TYPE GetType(const ExceptionHandlerDumpType& aType);
	static ExceptionHandlerDumpType GetType(std::string& aDumpType);	
};

#endif