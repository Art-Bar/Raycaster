#pragma once
#include "Renderer.h"

class guiHandler
{
	static guiHandler instance;
	Renderer* r1;
public:
	
	void init();
	void newFrame();
	void draw();
	void shutdown();
	void end();
	void FlushRendererColor();
	void getWindowSize(int& x,int& y);
	static guiHandler& getInstance();
};

