#ifndef _APP_H_
#define _APP_H_

#include "Editor.h"

class HGE;

class App
{
public:
	App( HGE &aHGE );
	~App(void);

	void Initialize();

	bool Update();

	void Render();

private:
	HGE &myHGE;
	Editor myEditor;
};

#endif