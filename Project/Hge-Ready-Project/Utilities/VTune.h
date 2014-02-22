#ifndef _VTUNE_H_
#define _VTUNE_H_

#ifdef VTUNE_TASK_LOG
#include "ittnotify.h"
#pragma comment(lib, "libittnotify.lib.")

static __itt_domain* gDomain = new __itt_domain;

static GrowingArray<__itt_string_handle*> gTasks(4);

#define VTUNE_CREATE_TASK(aTaskName)__itt_string_handle_create(L#aTaskName)
#define VTUNE_CREATE_AND_BEGIN_TASK(aTaskName) \
	gTasks.Add(__itt_string_handle_create(L#aTaskName));\
	__itt_task_begin(gDomain,__itt_null,__itt_null,gTasks.GetLast())
#define VTUNE_BEGIN_TASK(aTask)	__itt_task_begin(gDomain,__itt_null,__itt_null,aTask)
#define VTUNE_END_TASK() __itt_task_end(gDomain); gTasks.RemoveCyclicAtIndex(gTasks.Count()-1)
#define VTUNE_PAUSE() __itt_pause()
#define VTUNE_RESUME() __itt_resume()

#else
#define VTUNE_CREATE_TASK(aTaskName);
#define VTUNE_CREATE_AND_BEGIN_TASK(aTaskName);
#define VTUNE_BEGIN_TASK(aTask)
#define VTUNE_END_TASK() 
#define VTUNE_PAUSE() __itt_pause();
#define VTUNE_RESUME() __itt_resume();
#endif





#endif