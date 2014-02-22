#ifndef _FILE_WRAPPER_
#define _FILE_WRAPPER_

#include <string>
#include <bitset>

enum FileFlags
{
	READ,
	WRITE,
	APPEND,
	BINARY,

	F_READ = 1,
	F_WRITE = 2,
	F_APPEND = 4,
	F_BINARY = 8
};

class File
{
public:
	File(void);
	~File(void);

	bool Open(std::string aFileName, std::bitset<8> aSetOfFlags=0xF);
	bool Close();

	bool GoToNewLine();

	bool ReadInt(int &aInteger);
	bool ReadFloat(float &aFloat);
	bool ReadDouble(double &aDoubble);
	bool ReadWord(std::string &aString);
	bool ReadString(std::string &aString);

	bool WriteString(std::string aString);
	bool WriteInt(int &aInteger);
	bool WriteFloat(float &aFloat);
	bool WriteDouble(double &aDouble);

	bool WriteData(void *someData,int aSizeToWrite);
	bool ReadData(void *someData,int aSizeToRead);
	bool FlushToDisk();

private:

	FILE *myFile;
	std::bitset<8> myFlags;
};

#endif