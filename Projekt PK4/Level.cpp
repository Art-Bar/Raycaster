#include "Level.h"
int Level::numberOfLevels = 0;
Level::Level()
{
	numberOfLevels++;
}

Level::~Level()
{
	//numberOfLevels--; narazie nie? liczba poziomow pozostaje 0 gdy to jest odkomentowane.
}

Player &Level::getPlayer()
{
	return player;
}



void Level::loadMap(std::filesystem::path a, int &randIn)
{
	grid = 64; //64x64
	std::fstream plik(a);
	int index = 0;
	char buffer;
	float x, y;
	while (!plik.eof())
	{
		plik >> buffer;
		if (buffer == 'i' || buffer == 'a')
		{
			map[index] = 0;
			entities.push_back(Entity());
			y = index / grid;
			x = index % grid;
			entities[entities.size() - 1].setCoordinates(x, y);
			entities[entities.size() - 1].setType(buffer);
		}
		else if (buffer == 'E')
		{
			map[index] = 0;
			enemies.push_back(Enemy(randIn));
			y = index / grid;
			x = index % grid;
			enemies[enemies.size() - 1].setCoordinates(x, y);
			//enemies[enemies.size() - 1].setType(buffer);
		}
		else
		{
			map[index] = buffer - '0';
		}
		index++;
	}
	//tu umieœcisz kod który wczytuje do tablicy map zawartoœæ pliku .txt wskazanego przez path a //ZROBIONE
}

void Level::playerShoot()
{
	float deltaX, deltaY;
	float direction;
	int index = 0;
	bool erased = false;
	for (auto& n : enemies)
	{
		deltaX = n.x - player.x;
		deltaY = n.y - player.y;

		direction = atan2(deltaY, deltaX);
		if (direction < 0) direction += 6.28;
		if (direction >= player.rotationAngle - 0.1 && direction <= player.rotationAngle + 0.1 && n.visible == true)
		{
			enemies.erase(enemies.begin() + index);
			break;
		}
		index++;
	}
}

void Level::enemyShoot(Enemy& n)
{
	if (n.visible == true)
	{
		player.health -= 10;
	}
}



void Level::checkPickup()
{
	int index = 0;
	for (auto& n : entities)
	{
		if ((int)player.x == (int)n.x && (int)player.y == (int)n.y)
		{
			switch (n.type)
			{
			case 'i': if (player.health < 100) { player.health += 10; entities.erase(entities.begin() + index); break; }
			case 'a': if (player.ammo < 20) { player.ammo += 5; entities.erase(entities.begin() + index); break; }
			}
		}
		index++;
	}
	if (player.health > 100) player.health = 100;
	if (player.ammo > 20) player.ammo = 20;
}



std::vector<Entity> &Level::getEntities()
{
	return entities;
}

std::vector<Enemy> &Level::getEnemies()
{
	return enemies;
}


