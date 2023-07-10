#pragma once
#define SDL_MAIN_HANDLED
#include "guiHandler.h"
#include "Draw.h"
#include "menuClass.h"



class FPS
{
public:
	int fps_poczatek;
	int fps_koniec;
	int roznica;
	float delay;

	int fps = 30;

	void poczatek();
	void koniec();


};

class Game
{
	static Game instance;
	Draw dr1;
	FPS fps;
	Renderer* r1;
	std::vector<Level> levels;
	std::vector<Level> levelsBackup;

	menuClass main;
	OptionsMenuClass options;
	HUDClass HUD;

	Game();
	Game(const Game&) = delete;
	~Game();
	int levelIndex;
	static int randomNumber;
	Player* plr1; //wskaznik do gracza obecnego poziomu ustawiany w setlevel() do gracza mozna sie tez dostac poprzez funkcje getplayer() w obiekcie level

	int gameState;
	int renderWindowH, renderWindowW;
	bool isRunning, shot;
	static std::mutex mut;

	void generateRandomNumber();

public:
	
	static Game& getInstance();
	
	
	void setLevel(); // ustawia obecny poziom i koordynaty gracza
	void loadLevels(); //laduje poziomy do pamieci
	void init();
	void loop();
	void inputHandling();
	void enemyLogic();
	void enemyMovement();
	void checkWinCondition();

	void softReset();

};




