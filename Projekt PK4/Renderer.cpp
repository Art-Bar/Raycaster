#include "Renderer.h"

Renderer Renderer::instance;

Renderer::Renderer()
{
	
}
Renderer::~Renderer()
{

}

void Renderer::init()
{

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		mainWindow = SDL_CreateWindow("Okno", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, NULL);
		mainRenderer = SDL_CreateRenderer(mainWindow, -1, NULL);
	}
	else
	{
		std::cout << SDL_GetError();
	}

}

void Renderer::SetWindowSize(int w, int h)
{
	SDL_SetWindowSize(mainWindow,w,h);
}

SDL_Window* Renderer::getMainWindow()
{
	return mainWindow;
}

SDL_Renderer* Renderer::getMainRenderer()
{
	return mainRenderer;
}
Renderer& Renderer::getInstance()
{
	return instance;
}

