#include "stdafx.h"
#include "InputThreadHandler.h"
#include "InputReader.h"
#include "CommonMacros.h"

DWORD WINAPI InputThread(void* threadData)
{
	InputThreadData* inputThreadData = reinterpret_cast<InputThreadData*>(threadData);
	for(;;)
	{
		if(inputThreadData->myQuitFlag == true)
		{
			inputThreadData->myQuitFlag = false;
			return 0;
		}
		if(inputThreadData->myIsAllowedToStartFlag == true)
		{
			inputThreadData->myIsAllowedToStartFlag = false;
			GrowingArray<InputData>& currentArrayToUpdate = (*inputThreadData->myInputUpdates)[static_cast<int>(inputThreadData->myCurrentArrayToSpam)];

			inputThreadData->myInput->Update();
			currentArrayToUpdate.Add(inputThreadData->myInput->GetData());

			inputThreadData->myIsDoneFlag = true;
		}
		else
		{
			Sleep(0);
		}
	}
}

InputThreadHandler::InputThreadHandler(void)
{
}

InputThreadHandler::~InputThreadHandler(void)
{
	myInputThreadData.myQuitFlag = true;
	while(myInputThreadData.myQuitFlag == true);
	SAFE_DELETE(myInputThreadData.myInput);
}

void InputThreadHandler::StartThread(HINSTANCE aHInstance, HWND aHWnd, int screenWidth, int screenHeight, bool aCaptureMouseFlag)
{
	myInputUpdates[0].Init(8);
	myInputUpdates[1].Init(8);

	myCurrentArrayToUpdate = 1;

	myInputThreadData.myCurrentArrayToSpam = 0;
	myInputThreadData.myIsAllowedToStartFlag = false;
	myInputThreadData.myIsDoneFlag = true;
	myInputThreadData.myInputUpdates = &myInputUpdates;
	myInputThreadData.myInput = new InputReader();
	myInputThreadData.myInput->Init(aHInstance,aHWnd,screenWidth,screenHeight, aCaptureMouseFlag);
	myInputThreadData.myQuitFlag = false;

	CreateThread(NULL,2000,&InputThread,reinterpret_cast<void*>(&myInputThreadData),0,NULL);
}

void InputThreadHandler::Update()
{
	for(;;)
	{
		if(myInputThreadData.myIsDoneFlag == true)
		{
			myInputThreadData.myIsAllowedToStartFlag = false;
			if(myInputThreadData.myCurrentArrayToSpam == 1)
			{
				myCurrentArrayToUpdate = 1;
				myInputThreadData.myCurrentArrayToSpam = 0;
			}
			else
			{
				myCurrentArrayToUpdate = 0;
				myInputThreadData.myCurrentArrayToSpam = 1;
			}

			myInputThreadData.myIsDoneFlag = false;
			myInputThreadData.myIsAllowedToStartFlag = true;
			break;
		}
		else
		{
			Sleep(0);
		}
	}
}

void InputThreadHandler::ChangeScreenSize(const int& aScreenWidth, const int& aScreenHeight)
{
	myInputThreadData.myInput->ChangeScreenSize(aScreenWidth,aScreenHeight);
}

void InputThreadHandler::ReCaptureMouse(HWND aHWND)
{
	myInputThreadData.myInput->ReCaptureMouse(aHWND);
}

void InputThreadHandler::ReCaptureKeyBoard(HWND aHWND)
{
	myInputThreadData.myInput->ReCaptureKeyBoard(aHWND);
}

void InputThreadHandler::SetExclusiveFlag(const bool& anExclusiveFlag)
{
	myInputThreadData.myInput->SetExclusiveFlag(anExclusiveFlag);
}

GrowingArray<InputData>& InputThreadHandler::GetInputDataArray()
{
	return myInputUpdates[myCurrentArrayToUpdate];
}