#ifndef _VTUNE_H_
#define _VTUNE_H_

#ifdef VTUNE_TASK_LOG
#include "ittnotify.h"
#pragma comment(lib, "libittnotify.lib.")

static __itt_domain* gDomain = new __itt_domain;

#define VTUNE_CREATE_TASK(aTaskName)__itt_string_handle* aTaskName = __itt_string_handle_create(#aTaskName)
#define VTUNE_BEGIN_TASK(aTask)	__itt_task_begin(gDomain,__itt_null,__itt_null,aTask)
#define VTUNE_END_TASK() __itt_task_end(gDomain);
#define VTUNE_PAUSE() __itt_pause()
#define VTUNE_RESUME() __itt_resume()

#else
#define VTUNE_CREATE_TASK(aTaskName);
#define VTUNE_BEGIN_TASK(aTask)
#define VTUNE_END_TASK()
#define VTUNE_PAUSE() __itt_pause();
#define VTUNE_RESUME() __itt_resume();
#endif

#endif