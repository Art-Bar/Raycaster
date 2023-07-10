#include "menuClass.h"

menuClass::menuClass()
{

}

void menuClass::guiInit()
{
	gui1->init();
}

void menuClass::setGuiHandler()
{
	gui1 = &guiHandler::getInstance();
}

void menuClass::newFrame()
{
	gui1->newFrame();
}

void menuClass::shutdown()
{
	gui1->shutdown();
}

void menuClass::draw()
{
	gui1->draw();
}

void menuClass::end()
{
	gui1->end();
}

void menuClass::init(int& gameStateIn)
{
	gameState = &gameStateIn;
}

void menuClass::flushRendererColor()
{
	gui1->FlushRendererColor();
}

void menuClass::drawMenu()
{
	
	ImGui::Begin("Main Menu");
	
	if (ImGui::Button("Start Game", ImVec2(ImGui::GetWindowSize().x , 0.0f)))
	{
		*gameState = 1;
	}
	if (ImGui::Button("Options", ImVec2(ImGui::GetWindowSize().x, 0.0f)))
	{
		*gameState = 4;
	}
	if (ImGui::Button("Help", ImVec2(ImGui::GetWindowSize().x, 0.0f)))
	{
		*gameState = 6;
	}
	if (ImGui::Button("Exit", ImVec2(ImGui::GetWindowSize().x, 0.0f)))
	{
		*gameState = 8;
	}
	ImGui::End();
	gui1->draw();
	
}

void menuClass::drawPauseMenu()
{
	ImGui::Begin("Pause Menu");

	if (ImGui::Button("Resume Game", ImVec2(ImGui::GetWindowSize().x, 0.0f)))
	{
		*gameState = 1;
	}
	if (ImGui::Button("Options", ImVec2(ImGui::GetWindowSize().x, 0.0f)))
	{
		gui1->FlushRendererColor();
		*gameState = 3;
	}
	if (ImGui::Button("Exit to Menu", ImVec2(ImGui::GetWindowSize().x, 0.0f)))
	{
		gui1->FlushRendererColor();
		*gameState = 0;
	}
	ImGui::End();
	

}

void OptionsMenuClass::SetWindowSize(int w, int h)
{
	Renderer* temp = &Renderer::getInstance();
	temp->SetWindowSize(w, h);
}

void OptionsMenuClass::drawMenu()
{
	ImGui::Begin("Options Menu");
	ImGui::SliderInt("Window Width", &renderWindowW, 800, 1920);
	ImGui::SliderInt("Window Height", &renderWindowH, 600, 1080);
	ImGui::SliderInt("Detail", &*Resolution, 1, 64); //FMA Resolution
	ImGui::SliderInt("FOV", &*FOV, 60, 120);
	ImGui::SliderInt("Volume", &volume, 0, 100);
	if (ImGui::Button("Set window Size"))
	{
		SetWindowSize(renderWindowW, renderWindowH);
	}
	ImGui::SameLine();
	if (ImGui::Button("Back"))
	{
		gui1->FlushRendererColor();
		*gameState = 0;
	}
	ImGui::End();
	
}
void OptionsMenuClass::drawPauseOptionsMenu()
{
	ImGui::Begin("Options Menu");
	ImGui::SliderInt("Window Width", &renderWindowW, 800, 1920);
	ImGui::SliderInt("Window Height", &renderWindowH, 600, 1080);
	ImGui::SliderInt("Detail", &*Resolution, 1, 64); //FMA Resolution
	ImGui::SliderInt("FOV", &*FOV, 60, 120);
	ImGui::SliderInt("Volume", &volume, 0, 100);
	if (ImGui::Button("Set window Size"))
	{
		SetWindowSize(renderWindowW, renderWindowH);
	}
	ImGui::SameLine();
	if (ImGui::Button("Back"))
	{
		gui1->FlushRendererColor();
		*gameState = 5;
	}
	ImGui::End();

}
void OptionsMenuClass::drawPlayerCoordinates(float x, float y, float rot)
{
	ImGui::Begin("coordinates");
	ImGui::SliderFloat("X", &x, 0.0, 64.0);
	ImGui::SliderFloat("Y", &y, 0.0, 64.0);
	ImGui::SliderFloat("Rotation", &rot, 0.0, 7.0);
	ImGui::End();
	
}

void OptionsMenuClass::init(int &ResIn, int& gameStateIn, int& FOVIN)
{
	Resolution = &ResIn;
	gameState = &gameStateIn;
	FOV = &FOVIN;
}

void HUDClass::init(int& healthIn, int& ammoIn)
{
	health = &healthIn;
	ammo = &ammoIn;
}



void HUDClass::drawHUD()
{
	gui1->getWindowSize(x, y);
	ImGui::SetNextWindowSize(ImVec2(300.0f, 100.0f));
	ImGui::SetNextWindowPos(ImVec2((float)(x*(1.0f/15.0f)), (float)(y * (9.0f / 10.0f))));
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoBackground;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;
	ImGui::Begin("Window",NULL, window_flags );
	ImGui::SliderInt("Health", &*health, 0.0, 100.0);
	ImGui::SliderInt("Ammo", &*ammo, 0.0,20.0);
	ImGui::End();

}
