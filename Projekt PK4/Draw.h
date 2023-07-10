#pragma once
#include "Level.h"
#include "Renderer.h"
class Draw
{
	int renderWindowW, renderWindowH;
	int Resolution, FOV;
	int* gameState;
	int weaponAnimationFrame;
	Renderer* r1;
	std::vector<SDL_Surface*> Images;
	std::vector<SDL_Texture*> Textures;
	std::vector<float> distances;


	std::mutex mut;
	
	


public:
	void init(int &gameStateIn);
	void loadTextures();
	void createTextureObjects();

	void drawMap(Level& levelIn);
	void drawPlayer(Level& levelIn);
	void drawEntities(Level& levelIn);
	void drawEnemies(Level& levelIn);
	void draw2DRays(Level& levelIn);

	void draw3DView(float Distance, int Res, int currentRay);
	void draw3DViewPhotoTextured(float Distance, int Res, int currentRay,bool vertical, float rayAngle, float xStep, float yStep);
	void drawFloorsPhotoTextured(float rayAngle, float Distance, float rotationAngle, float x, float y, int Res, int currentRay);

	void drawEntitiesin3DSpace(Level& levelIn);
	void drawEnemiesin3DSpace(Level& levelIn);

	void display();
	void drawSprite(int x,int y,int index);
	void drawWeaponSprite();
	void weaponAnimation(bool& isRunning, bool& shot);
	float Distance(float x1,float x2, float y1, float y2);
	
	int &getResolution();
	int& getFOV();


};

