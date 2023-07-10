#pragma once
#include <filesystem>
#include <vector>
#include "Entity.h"
#include <fstream>
class Level
{
	std::vector<Entity> entities;
	std::vector<Enemy> enemies;
	
	Player player;
	
public:
	int grid;
	int map[4096];

	static int numberOfLevels;
	Level();
	~Level();

	Player &getPlayer();
	void loadMap(std::filesystem::path a, int &randIn);//przekazywanie wskaznika do zmiennej sterujacej przeciwnikami do funkcji ladowania mapy to troche hack
	
	void playerShoot();
	void enemyShoot(Enemy& n);
	void checkPickup();

	std::vector<Entity> &getEntities();
	std::vector<Enemy> &getEnemies();
};

