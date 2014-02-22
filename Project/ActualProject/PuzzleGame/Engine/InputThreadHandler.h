#ifndef _INPUT_THREAD_HEADER_
#define _INPUT_THREAD_HEADER_

#include "InputData.h"
#include "GrowingArray.h"
#include "StaticArray.h"

class InputReader;

struct InputThreadData
{
	InputReader* myInput;
	volatile bool myIsDoneFlag;
	volatile bool myIsAllowedToStartFlag;
	volatile bool myQuitFlag;
	volatile int myCurrentArrayToSpam;
	StaticArray<GrowingArray<InputData>,2>* myInputUpdates;
};

class InputThreadHandler
{
public:
	InputThreadHandler(void);
	~InputThreadHandler(void);

	void StartThread(HINSTANCE aHInstance, HWND aHWnd, int screenWidth, int screenHeight, bool aCaptureMouseFlag = true);

	void Update();

	void ChangeScreenSize(const int& aScreenWidth, const int& aScreenHeight);

	void ReCaptureMouse(HWND aHWND);
	void ReCaptureKeyBoard(HWND aHWND);

	void SetExclusiveFlag(const bool& anExclusiveFlag);

	GrowingArray<InputData>& GetInputDataArray();
private:
	StaticArray<GrowingArray<InputData>,2> myInputUpdates;
	InputThreadData myInputThreadData;
	int myCurrentArrayToUpdate;
};

#endif