#include "Game.h"

int Game::randomNumber = 0;
std::mutex Game::mut;

void FPS::poczatek()
{
	fps_poczatek = clock();
}

void FPS::koniec()
{
	fps_koniec = clock();
	roznica = fps_koniec - fps_poczatek;
	
	
	delay = 1000.0 / fps - roznica;
	if (delay > 0)
	{
		SDL_Delay(delay);
	}
	
}

Game Game::instance;

Game::Game()
{
	
	
}
Game::~Game()
{

}

Game& Game::getInstance()
{
	return instance;
}


void Game::setLevel()
{
	plr1 = &levels[levelIndex].getPlayer();
	plr1->setCoordinates(32, 32);
	plr1->setRotation(3.14);

}

void Game::loadLevels()
{
	using namespace std::filesystem;

	for (const directory_entry& opl : directory_iterator(current_path())) {
		if (opl.path().extension().string() == ".txt") {
			std::string name = opl.path().filename().string();
			std::regex reg("Level\\d\\.[A-Za-z]+");
			std::smatch match;
			if (std::regex_match(name,match,reg))
			{
				levels.push_back(Level());
				
				levels[levels.size() - 1].loadMap(opl.path(), randomNumber); // -1 bo indeksowanie wektora jest od 0;
			
			}
		}
	}
	levelsBackup = levels;
}

void Game::init()
{
	r1 = &Renderer::getInstance();
	r1->init();
	dr1.init(gameState);
	options.init(dr1.getResolution(), gameState, dr1.getFOV());
	main.init(gameState);
	gameState = 0;
	levelIndex = 0;
	
	
}

void Game::loop()
{
	isRunning = true;
	shot = false;

	main.setGuiHandler();
	options.setGuiHandler();
	HUD.setGuiHandler();

	main.guiInit();
	
	loadLevels();
	setLevel();
	
	std::thread t1 = std::thread([&]() {this->generateRandomNumber(); });
	// w osobnym w¹tku dodasz rzeczy takie jak myœlenie mobow i zmienianie levela ( myœlenie dla ka¿dego moba z tablicy przy pomocy ranges)
	// myœlenie mobow np iterujesz w pêtli co losowy czas przez kazdego moba, ogarniasz myslenie(ustawienie rotacji itd) i nastepnie jezeli liczba jest np 
	// podzielna przez 2 to wl¹czasz ruszanie
	std::thread t2 = std::thread([&]() {this->enemyLogic(); });
	std::thread t3 = std::thread([&]() {dr1.weaponAnimation(isRunning, shot); });
	int renderWindowH, renderWindowW, temp;

	SDL_GetRendererOutputSize(r1->getMainRenderer(), &renderWindowW, &renderWindowH);
	
	while (isRunning)
	{
		fps.poczatek();
		temp = gameState;
		switch (gameState)
		{
		case 0://menu
			SDL_GetRendererOutputSize(r1->getMainRenderer(), &renderWindowW, &renderWindowH);
			main.newFrame();
			
			main.drawMenu();
			dr1.drawSprite(renderWindowW/2, renderWindowH/3, 4);
			main.draw();
			break;
		case 1://gra
			
			dr1.drawMap(levels[levelIndex]);
			dr1.draw2DRays(levels[levelIndex]);
			dr1.drawWeaponSprite();
			HUD.newFrame();
			HUD.drawHUD();
			HUD.draw();
			//dr1.display();  potrzebne gdy nie ma funkcji klasy menu o nazwie draw (któr¹ powinienem zmieniæ na display wsm)
			break;
		case 2://mapa
			
			dr1.drawMap(levels[levelIndex]);
			dr1.draw2DRays(levels[levelIndex]);
			
			dr1.drawPlayer(levels[levelIndex]);
			dr1.drawEntities(levels[levelIndex]);
			dr1.drawEnemies(levels[levelIndex]);
			options.newFrame();
			//options.drawMenu();
			options.drawPlayerCoordinates(plr1->x, plr1->y, plr1->rotationAngle);
		
			options.draw();
			break;
		case 3://menu opcji pauzy
			//levels[levelIndex].updateEnemies();
			
			dr1.drawMap(levels[levelIndex]);
			dr1.draw2DRays(levels[levelIndex]);
			
			
			options.newFrame();
			options.drawPauseOptionsMenu();
			options.drawPlayerCoordinates(plr1->x, plr1->y, plr1->rotationAngle);
			options.draw();
			break;
		case 4://opcje
			SDL_GetRendererOutputSize(r1->getMainRenderer(), &renderWindowW, &renderWindowH);
			options.newFrame();

			options.drawMenu();
			dr1.drawSprite(renderWindowW / 2, renderWindowH / 3, 4);
			options.draw();
			break;
		case 5://menu pauze
			
			//levels[levelIndex].updateEnemies();

			dr1.drawMap(levels[levelIndex]);
			dr1.draw2DRays(levels[levelIndex]);


			options.newFrame();
			options.drawPauseMenu();
			//options.drawPlayerCoordinates(plr1->x, plr1->y, plr1->rotationAngle);
			main.draw();
			break;
		case 6://ekran Help
			SDL_GetRendererOutputSize(r1->getMainRenderer(), &renderWindowW, &renderWindowH);
			main.flushRendererColor();//zostawiam tylko w main bo w dr1 bylo by napisane doslownie to samo
			main.newFrame();
			dr1.drawSprite(renderWindowW / 2, renderWindowH / 2, 11);
			main.draw();
			break;
		case 7:// ekran wygranej
			SDL_GetRendererOutputSize(r1->getMainRenderer(), &renderWindowW, &renderWindowH);
			main.flushRendererColor();
			main.newFrame();
			dr1.drawSprite(renderWindowW / 2, renderWindowH / 2, 10);
			main.draw();
			break;
		case 8:
			isRunning = false;
		break;
		}
		
		
		//////////////
		enemyMovement();
		levels[levelIndex].checkPickup();
		inputHandling();
		
		

		if (temp == 0 && gameState == 1)
		{
			softReset();
		}
		//////////////
		if (plr1->health <= 0)
		{
			main.flushRendererColor();
			gameState = 0;
		}

		checkWinCondition();
		//std::cout << randomNumber << std::endl;

		

		fps.koniec();
	}

	main.shutdown();
	t1.join();
	t2.join();
	t3.join();
	SDL_Quit();
}

void Game::inputHandling()
{
	SDL_Event Event;
	int index;
	while (SDL_PollEvent(&Event)) {
		
		switch (Event.type) {

		case SDL_QUIT:
			SDL_Quit();
			break;

		case SDL_KEYDOWN:
			switch (Event.key.keysym.sym)
			{
			case SDLK_RETURN: if (gameState == 0) { gameState = 1;  } 
							  else if (gameState == 7) { gameState = 0; }
							  else if (gameState == 6) { gameState = 0; } break;
			case SDLK_LEFT: plr1->trnLeft = true; break;
			case SDLK_RIGHT: plr1->trnRight = true; break;
			case SDLK_UP: plr1->mvForward = true;   break;
			case SDLK_DOWN: plr1->mvBack = true; break;
			case SDLK_z:  if (gameState != 3) { gameState = 3; } else if (gameState == 3) { gameState = 1; } /*main.end();*/	break;
			case SDLK_x:
						 index = (int)(plr1->y + plr1->get_deltay()) * levels[levelIndex].grid + (plr1->x + plr1->get_deltax());
						 levels[levelIndex].map[index] = 1; break;
			case SDLK_a:	 break;
			case SDLK_q: if (gameState != 2) { gameState = 2; } /*main.end();*/	break;
			case SDLK_c: index = (int)(plr1->y + plr1->get_deltay()) * levels[levelIndex].grid + (plr1->x + plr1->get_deltax());
						 levels[levelIndex].map[index] = 0; break;
			case SDLK_ESCAPE: if (gameState == 0) {}
							else if (gameState == 4) { gameState = 0; }
							else if (gameState == 1) { gameState = 5; }
							else if (gameState == 5) { gameState = 1; } 
							else if (gameState == 7) { gameState = 0; }
							else if (gameState == 6) { gameState = 0; } break;
			case SDLK_LCTRL: if (plr1->ammo > 0 && shot == false){
								shot = true;
								plr1->ammo--;
								levels[levelIndex].playerShoot();
							}break;
			
			}
			break;
		case SDL_KEYUP:
			switch (Event.key.keysym.sym)
			{
			case SDLK_LEFT: plr1->trnLeft = false; break;
			case SDLK_RIGHT: plr1->trnRight = false; break;
			case SDLK_UP: plr1->mvForward = false;   break;
			case SDLK_DOWN: plr1->mvBack = false; break;
			case SDLK_z:     break;
			case SDLK_x:	 break;
			case SDLK_a:	 break;
			case SDLK_q: gameState = 1;	options.end(); break;
			}
			break;
		
		default:
			break;
		}
		ImGui_ImplSDL2_ProcessEvent(&Event);
	}
	plr1->move(levels[levelIndex].map, levels[levelIndex].grid);
}

void Game::enemyMovement()
{
	for (auto& n : levels[levelIndex].getEnemies())
	{


		mut.lock();
		n.move(levels[levelIndex].map, levels[levelIndex].grid);
		mut.unlock();
	
	}
	
}

void Game::checkWinCondition()
{
	if (gameState == 1)
	{


		if (levels[levelIndex].getEnemies().size() == 0 && levelIndex == levels.size() - 1)
		{
			gameState = 7;
		}
		else if (levels[levelIndex].getEnemies().size() == 0) levelIndex++;
	}
}

void Game::softReset()
{
	mut.lock();
	levels = levelsBackup;
	setLevel();
	mut.unlock();

	levels[levelIndex].getPlayer().health = 100;
	levels[levelIndex].getPlayer().ammo = 20;
	HUD.init(
		levels[levelIndex].getPlayer().health,
		levels[levelIndex].getPlayer().ammo);

}

void Game::enemyLogic()
{
	while (isRunning)
	{
		for(auto &n : levels[levelIndex].getEnemies())
		{
			
			if (gameState == 1)
			{
				mut.lock();
				n.think();
				if (n.attack == true)
				{
					levels[levelIndex].enemyShoot(n);
				}
				mut.unlock();
				Sleep(100);
			}
		}
	}
	
}

void Game::generateRandomNumber()
{
	std::random_device rnd;
	std::mt19937 mt{ rnd() };
	std::uniform_int_distribution<int> dist{ 1, 10000 };
	while (isRunning)
	{
		mut.lock();
		randomNumber = dist(mt);
		mut.unlock();
		Sleep(10);
	}
}





