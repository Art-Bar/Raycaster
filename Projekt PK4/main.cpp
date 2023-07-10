#include <iostream>
#include "Game.h"


int main()
{
	
	Game &renderer = Game::getInstance();
	
	renderer.init();
	renderer.loop();
	

	return 0;
}