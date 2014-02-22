#include "CommonUtilities.h"
#include "stdarg.h"

#pragma warning (disable:4996)

std::string CommonUtilities::GetString(const char* someText,...)
{
	std::string returnString;
	char buffer[1024];
	va_list args;
	va_start(args,someText);
	vsnprintf(buffer,256,someText,args);
	returnString = buffer;
	va_end(args);
	return returnString;
}