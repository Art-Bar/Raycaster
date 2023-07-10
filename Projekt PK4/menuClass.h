#pragma once
#include "guiHandler.h"
class menuClass
{
protected:
	guiHandler* gui1;
	int* gameState;
	
public:
	menuClass();
	
	void guiInit();
	void setGuiHandler();
	void newFrame();
	void shutdown();
	void draw();
	void end();
	void init(int& gameStateIn);
	void flushRendererColor();

//do rysowania

	virtual void drawMenu();
	void drawPauseMenu();
	
};

class OptionsMenuClass : public menuClass
{
	//te zmienne do "options menu"
	int renderWindowW, renderWindowH;
	int *Resolution;
	int* FOV;
	int volume;
	void SetWindowSize(int w, int h);

public:
	
	void drawMenu();
	void drawPauseOptionsMenu();
	void drawPlayerCoordinates(float x,float y, float rot);
	void init(int& ResIn, int& gameStateIn, int& FOVIN);
};
class HUDClass : public menuClass
{
	int *health, *ammo;
	
	int x, y;
public:
	int src_texture_x;
	int src_texture_y;
	
	void drawHUD();
	void init(int& healthIn, int& ammoIn);
};
