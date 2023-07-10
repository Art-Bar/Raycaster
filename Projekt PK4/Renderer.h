#pragma once
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer.h"
#include "SDL.h"
#include <iostream>
#include <vector>
#include <windows.h>
#include <future>
#include <random>
#include <algorithm>
#include <regex>

class Renderer
{
	static Renderer instance;
	

	Renderer();
	Renderer(const Renderer&) = delete;
	~Renderer();
	

	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;

public:
	
	static Renderer& getInstance();
	void init();
	void SetWindowSize(int w,int h);
	
	SDL_Window* getMainWindow();
	SDL_Renderer* getMainRenderer();
};

