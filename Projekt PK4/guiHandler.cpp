#include "guiHandler.h"

guiHandler guiHandler::instance;

void guiHandler::init()
{
	r1 = &Renderer::getInstance();
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForSDLRenderer(r1->getMainWindow(), r1->getMainRenderer());
	ImGui_ImplSDLRenderer_Init(r1->getMainRenderer());

}

void guiHandler::newFrame()
{
	ImGui_ImplSDLRenderer_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
}

void guiHandler::draw()
{
	

	ImGui::Render();
	ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(r1->getMainRenderer());
	SDL_RenderClear(r1->getMainRenderer());
	ImGui::EndFrame();
}
void guiHandler::end()
{
	//ImGui::End();
}

void guiHandler::FlushRendererColor()
{
	SDL_SetRenderDrawColor(r1->getMainRenderer(), 0, 0, 0, 0);
}

void guiHandler::getWindowSize(int& x, int& y)
{
	SDL_GetRendererOutputSize(r1->getMainRenderer(), &x, &y);
}


void guiHandler::shutdown()
{
	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

guiHandler& guiHandler::getInstance()
{
	return instance;
}
