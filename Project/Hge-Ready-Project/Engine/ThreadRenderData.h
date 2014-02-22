#ifndef _THREAD_RENDER_DATA_H_
#define _THREAD_RENDER_DATA_H_
#include "Renderer.h"

#include "StaticArray.h"
#include "GrowingArray.h"
#include "RenderData.h"

struct ThreadRenderData
{
	volatile bool myIsDoneFlag;
	volatile bool myIsAllowedToStartFlag;	
	volatile int myCurrentArrayToRender;
	Renderer* myRenderer;
};

#endif