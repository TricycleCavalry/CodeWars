#ifndef _ENGINE_HEADER_
#define _ENGINE_HEADER_

#include "TimeManager.h"
#include "InputThreadHandler.h"
#include "InputHandler.h"
#include "ThreadRenderData.h"

class Renderer;
class InputHandler;
class HGE;

class Engine
{
public:
	Engine(void);
	~Engine(void);

	void Init();
	void Start();

	void Update();

	

	Renderer& GetRenderer();
	InputHandler& GetInputHandler();
	TimeManager& GetTimeManager();

	float GetElapsedTime();

	HGE& GetHGE();

	void CleanRenderQueue();

private:

	HWND myHwnd;

	void StartRenderThread();
	HGE* InitiateHGE();
	void ShutDownHGE();
	void CheckFocus();

	void UpdateInput(GrowingArray<InputData>& someInputData);
	TimeManager myTimeManager;

	InputThreadHandler myInputThread;
	InputHandler* myInputHandler;

	Renderer* myRenderer;
	ThreadRenderData myThreadRenderData;

	HGE* myHGE;
};

#endif