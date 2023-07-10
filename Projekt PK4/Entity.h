#pragma once
#include <math.h>
#include <iostream>
#define PI 3.141592
#define P2 PI/2
#define P3 3*PI/2
#define DR 0.0174533
class Entity
{
public:
	Entity() = default;
	float x, y;// max wartoœæ x i y to grid
	char type;
	
	void setCoordinates(float xIn,float yIn);
	void setType(char cIn);
	//dodatkowo kazdy obiekt musi miec swoja grafike
};


class movingEntity : public Entity
{
public:
	bool moveConditional;
	float deltax, deltay;
	float rotationAngle;
	void setRotation(float rotIn);
	void move(int* map, int grid);
	
};


class Player: public movingEntity
{
	
public:
	Player() :movingEntity()
	{
		mvForward = false;
		mvBack = false;
		trnLeft = false;
		trnRight = false;
		deltax = 0;
		deltay = 1;
		health = 100;
		ammo = 20;
	};
	int health;
	int ammo;
	bool mvForward, mvBack, trnLeft, trnRight, collision;
	void move(int *map, int grid);
	float get_deltax();
	float get_deltay();
	
	
};


class Enemy : public movingEntity
{
	int* randomNumber;

public:
	Enemy(int &i) :movingEntity()
	{
		randomNumber = &i;
	}
	
	bool visible;
	bool attack;
	void think();
};