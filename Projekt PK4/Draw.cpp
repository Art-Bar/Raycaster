#include "Draw.h"

void Draw::init(int& gameStateIn)
{
	r1 = &Renderer::getInstance();
	Resolution = 4;
	FOV = 80;
	gameState = &gameStateIn;
	loadTextures();
	createTextureObjects();
}

void Draw::drawMap(Level& levelIn)
{
	SDL_Rect bg, fg;
	float blockSize, beginx, beginy;

	SDL_GetWindowSize(r1->getMainWindow(), &renderWindowW, &renderWindowH);
	if (*gameState == 2)
	{


		if (renderWindowH > renderWindowW)
		{
			beginx = 0;
			beginy = (renderWindowH / 2) - (renderWindowW / 2);
			bg.x = 0;
			bg.y = (renderWindowH / 2) - (renderWindowW / 2);
			bg.w = renderWindowW;
			bg.h = renderWindowW;
			blockSize = static_cast<float> (renderWindowW) / levelIn.grid;
		}
		if (renderWindowH < renderWindowW)
		{
			beginx = (renderWindowW / 2) - (renderWindowH / 2);
			beginy = 0;
			bg.x = (renderWindowW / 2) - (renderWindowH / 2);
			bg.y = 0;
			bg.w = renderWindowH;
			bg.h = renderWindowH;
			blockSize = static_cast<float>(renderWindowH) / levelIn.grid;
		}

		fg.w = blockSize;
		fg.h = blockSize;

		SDL_SetRenderDrawColor(r1->getMainRenderer(), 255, 0, 0, 255);

		// Kolorujemy ekran na podany kolor
		SDL_RenderClear(r1->getMainRenderer());
		//pokazujemy rect bg
		SDL_SetRenderDrawColor(r1->getMainRenderer(), 0, 0, 0, 255);
		SDL_RenderFillRect(r1->getMainRenderer(), &bg);
		SDL_SetRenderDrawColor(r1->getMainRenderer(), 0, 255, 0, 255);

		for (int i = 0; i < levelIn.grid; i++)
		{
			fg.y = beginy + (i * blockSize);

			for (int j = 0; j < levelIn.grid; j++)
			{
				fg.x = beginx + (j * blockSize);
				if (levelIn.map[(i * levelIn.grid) + j])
				{
					SDL_RenderFillRect(r1->getMainRenderer(), &fg);
				}
			}
		}
		//kod do rysowania poziomu, ale mo¿e siê przydaæ przy kolizjach w klasie level
	}
}

void Draw::drawPlayer(Level& levelIn)
{
	SDL_Rect fg;



	if (renderWindowH > renderWindowW)
	{
		fg.h = (static_cast<float>(renderWindowW) / levelIn.grid);
		fg.w = (static_cast<float>(renderWindowW) / levelIn.grid);
		fg.x = (static_cast<float>(renderWindowW) / levelIn.grid) * levelIn.getPlayer().x;
		fg.y = (renderWindowH / 2) - (renderWindowW / 2) + (static_cast<float>(renderWindowW) / levelIn.grid) * levelIn.getPlayer().y;
		SDL_RenderDrawLine(r1->getMainRenderer(),
			fg.x,
			fg.y,
			fg.x + levelIn.getPlayer().deltax * 11.2,
			fg.y + levelIn.getPlayer().deltay * 11.2);

	}
	if (renderWindowH < renderWindowW)
	{
		fg.h = (static_cast<float>(renderWindowH) / levelIn.grid);
		fg.w = (static_cast<float>(renderWindowH) / levelIn.grid);
		fg.x = (renderWindowW / 2) - (renderWindowH / 2) + (static_cast<float>(renderWindowH) / levelIn.grid) * levelIn.getPlayer().x;
		fg.y = (static_cast<float>(renderWindowH) / levelIn.grid) * levelIn.getPlayer().y;
		SDL_RenderDrawLine(r1->getMainRenderer(),
			fg.x,
			fg.y,
			fg.x + levelIn.getPlayer().deltax * 11.2,
			fg.y + levelIn.getPlayer().deltay * 11.2);
	}
	SDL_SetRenderDrawColor(r1->getMainRenderer(), 0, 0, 255, 255);
	SDL_RenderFillRect(r1->getMainRenderer(), &fg);


}
void Draw::drawEntities(Level& levelIn)
{
	SDL_Rect fg;


	for (int i =0; i < levelIn.getEntities().size(); i++)
	{
		if (renderWindowH > renderWindowW)
		{
			fg.h = (static_cast<float>(renderWindowW) / (2 *levelIn.grid));
			fg.w = (static_cast<float>(renderWindowW) / (2 *levelIn.grid));
			fg.x = (static_cast<float>(renderWindowW) / levelIn.grid) * levelIn.getEntities()[i].x;
			fg.y = (renderWindowH / 2) - (renderWindowW / 2) + (static_cast<float>(renderWindowW) / levelIn.grid) * levelIn.getEntities()[i].y;
		

		}
		if (renderWindowH < renderWindowW)
		{
			fg.h = (static_cast<float>(renderWindowH) / (2* levelIn.grid));
			fg.w = (static_cast<float>(renderWindowH) / (2* levelIn.grid));
			fg.x = (renderWindowW / 2) - (renderWindowH / 2) + (static_cast<float>(renderWindowH) / levelIn.grid) * levelIn.getEntities()[i].x;
			fg.y = (static_cast<float>(renderWindowH) / levelIn.grid) * levelIn.getEntities()[i].y;
			
		}
		SDL_SetRenderDrawColor(r1->getMainRenderer(), 255, 255, 0, 255);
		SDL_RenderFillRect(r1->getMainRenderer(), &fg);
	}

}

void Draw::drawEnemies(Level& levelIn)
{
	SDL_Rect fg;


	for (int i = 0; i < levelIn.getEnemies().size(); i++)
	{
		if (renderWindowH > renderWindowW)
		{
			fg.h = (static_cast<float>(renderWindowW) / (2 * levelIn.grid));
			fg.w = (static_cast<float>(renderWindowW) / (2 * levelIn.grid));
			fg.x = (static_cast<float>(renderWindowW) / levelIn.grid) * levelIn.getEnemies()[i].x;
			fg.y = (renderWindowH / 2) - (renderWindowW / 2) + (static_cast<float>(renderWindowW) / levelIn.grid) * levelIn.getEnemies()[i].y;


		}
		if (renderWindowH < renderWindowW)
		{
			fg.h = (static_cast<float>(renderWindowH) / (2 * levelIn.grid));
			fg.w = (static_cast<float>(renderWindowH) / (2 * levelIn.grid));
			fg.x = (renderWindowW / 2) - (renderWindowH / 2) + (static_cast<float>(renderWindowH) / levelIn.grid) * levelIn.getEnemies()[i].x;
			fg.y = (static_cast<float>(renderWindowH) / levelIn.grid) * levelIn.getEnemies()[i].y;

		}
		SDL_SetRenderDrawColor(r1->getMainRenderer(), 255, 255, 0, 255);
		SDL_RenderFillRect(r1->getMainRenderer(), &fg);
	}

}

void Draw::draw2DRays(Level& levelIn)
{
	float rotationAngle = levelIn.getPlayer().rotationAngle;
	float x = levelIn.getPlayer().x;
	float y = levelIn.getPlayer().y;
	float xStep, yStep, xOffset, yOffset, rayAngle = levelIn.getPlayer().rotationAngle - DR * (FOV/2);//TODO ZROB PROMIENIE W ILOSCI renderWindowW Z POLEM WIDZENIA 60 STOPNI
	if (rayAngle < 0) { rayAngle += 2 * PI; }
	if (rayAngle > 2 * PI) { rayAngle -= 2 * PI; }
	int dof, mapPos;
	bool vertical;

	float fgx = 0;
	float fgy = 0;

	float xSHorizontal, ySHorizontal, xSVertical, ySVertical, finalDistance;

	


	if (*gameState == 1 || *gameState == 3|| *gameState == 5)
	{
		mut.lock();
		SDL_SetRenderDrawColor(r1->getMainRenderer(), 0, 0, 0, 255);
		SDL_RenderClear(r1->getMainRenderer());
		mut.unlock();
	}


	for (int r = 0; r < renderWindowW / Resolution +1; r++)
	{
		//sprawdza poziome œciany
		dof = 0;
		float aTan = -1 / tan(rayAngle);
		if (rayAngle > PI) { yStep = (int)y; xStep = (y - yStep) * aTan + x; yOffset = -1.0; xOffset = -yOffset * aTan; } //gora
		if (rayAngle < PI) { yStep = (int)y + 1.0; xStep = (y - yStep) * aTan + x; yOffset = 1.0; xOffset = -yOffset * aTan; } //dol
		if (rayAngle == 0 || rayAngle == PI) { xStep = x; yStep = y; dof = 64; } //lewo prawo
		while (dof < levelIn.grid)
		{
			if (rayAngle > PI) { mapPos = (int)(yStep - 1.0) * levelIn.grid + (int)xStep; }//osobny map pos bo koordynaty kostki zaczynaja sie w lewym gornym rogu
			else { mapPos = (int)yStep * levelIn.grid + (int)xStep; }
			if (xStep < levelIn.grid && yStep < levelIn.grid && mapPos < (levelIn.grid * levelIn.grid) && mapPos >0 && levelIn.map[mapPos] == 1) { dof = levelIn.grid; }//sprawdzam czy promien nie wychodzi poza granice mapy oraz czy styka sie ze sciana
			else { xStep += xOffset; yStep += yOffset; dof++; }

		}
		xSHorizontal = xStep; ySHorizontal = yStep;

		//sprawdza pionowe œciany 
		dof = 0;
		float nTan = -tan(rayAngle);
		if (rayAngle > P2 && rayAngle < P3) { xStep = (int)x; yStep = (x - xStep) * nTan + y; xOffset = -1.0; yOffset = -xOffset * nTan; } //lewo
		if (rayAngle < P2 || rayAngle >P3) { xStep = (int)x + 1.0; yStep = (x - xStep) * nTan + y; xOffset = 1.0; yOffset = -xOffset * nTan; } //prawo
		if (rayAngle == 0 || rayAngle == PI) { xStep = x; yStep = y; dof = 64; }//gora dol
		while (dof < levelIn.grid)
		{
			if (rayAngle > P2 && rayAngle < P3) { mapPos = (int)(yStep)*levelIn.grid + (int)(xStep - 1.0); }//osobny map pos bo koordynaty kostki zaczynaja sie w lewym gornym rogu
			else { mapPos = (int)yStep * levelIn.grid + (int)xStep; }

			if (xStep < levelIn.grid && yStep < levelIn.grid && mapPos < (levelIn.grid * levelIn.grid) && mapPos > 0 && levelIn.map[mapPos] == 1) //sprawdzam czy promien nie wychodzi poza granice mapy oraz czy styka sie ze sciana
			{
				dof = levelIn.grid;
			}
			else
			{
				xStep += xOffset; yStep += yOffset; dof++;
			}

		}

		xSVertical = xStep; ySVertical = yStep;

		//porównanie d³ugoœci promieni sprawdzajacych sciany pionowe i poziome i wyswietlenie krótszego.
		if (Distance(xSHorizontal, x, ySHorizontal, y) > Distance(xSVertical, x, ySVertical, y)) {
			xStep = xSVertical; yStep = ySVertical; finalDistance = Distance(xSVertical, x, ySVertical, y);
			mut.lock(); SDL_SetRenderDrawColor(r1->getMainRenderer(), 0, 0, 255, 255); mut.unlock(); vertical = true;
		}
		if (Distance(xSHorizontal, x, ySHorizontal, y) < Distance(xSVertical, x, ySVertical, y)) {
			xStep = xSHorizontal; yStep = ySHorizontal; finalDistance = Distance(xSHorizontal, x, ySHorizontal, y);
			mut.lock(); SDL_SetRenderDrawColor(r1->getMainRenderer(), 0, 0, 200, 255); mut.unlock(); vertical = false;
		}
		float angleDelta = rotationAngle - rayAngle;
		if (angleDelta < 0) { angleDelta += 2 * PI; }
		if (angleDelta > 2 * PI) { angleDelta -= 2 * PI; }

		distances.push_back(finalDistance);
		finalDistance = finalDistance * cos(angleDelta);
		

		//rysowanie promienia
		if (*gameState == 2)
		{
			if (renderWindowH < renderWindowW)
			{
				fgx = (renderWindowW / 2) - (renderWindowH / 2) + (static_cast<float>(renderWindowH) / levelIn.grid) * x;
				fgy = (static_cast<float>(renderWindowH) / levelIn.grid) * y;
				mut.lock();
				SDL_SetRenderDrawColor(r1->getMainRenderer(), 0, 0, 255, 255);
				SDL_RenderDrawLine(r1->getMainRenderer(),
					fgx,
					fgy,
					(renderWindowW / 2) - (renderWindowH / 2) + (static_cast<float>(renderWindowH) / levelIn.grid) * xStep,
					(static_cast<float>(renderWindowH) / levelIn.grid) * yStep);
				mut.unlock();
			}
			if (renderWindowH > renderWindowW)
			{
				fgx = (static_cast<float>(renderWindowW) / levelIn.grid) * x;
				fgy = (renderWindowH / 2) - (renderWindowW / 2) + (static_cast<float>(renderWindowW) / levelIn.grid) * y;
				mut.lock();
				SDL_SetRenderDrawColor(r1->getMainRenderer(), 0, 0, 255, 255);
				SDL_RenderDrawLine(r1->getMainRenderer(),
					fgx,
					fgy,
					(static_cast<float>(renderWindowW) / levelIn.grid) * xStep,
					(renderWindowH / 2) - (renderWindowW / 2) + (static_cast<float>(renderWindowW) / levelIn.grid) * yStep);
				mut.unlock();
			}
		}
		//rysuje widok 3D
 		if (*gameState == 1 || *gameState == 3 || *gameState == 5)
		{

			//draw3DView(finalDistance, Resolution, r);


			
			drawFloorsPhotoTextured(rayAngle, finalDistance, rotationAngle, x, y, Resolution, r);
			draw3DViewPhotoTextured(finalDistance, Resolution, r, vertical, rayAngle, xStep, yStep);
			
			
		}
			

		//ustawiam nastêpny promien w kolejce
		rayAngle += ((DR * FOV) / (renderWindowW / Resolution));
		if (rayAngle < 0) { rayAngle += 2 * PI; }
		if (rayAngle > 2 * PI) { rayAngle -= 2 * PI; }

	}
	if (*gameState == 1)
	{
		drawEntitiesin3DSpace(levelIn);
		drawEnemiesin3DSpace(levelIn);
	}
			distances.clear();

}

void Draw::draw3DView(float Distance, int Res, int currentRay)
{
	SDL_Rect line;
	float lineHeight = (2 * renderWindowH) / Distance;
	float lineWidth = Res;
	if (lineHeight > renderWindowH) { lineHeight = renderWindowH; }
	line.h = lineHeight;
	line.w = lineWidth;
	line.x = lineWidth * currentRay;
	line.y = (renderWindowH / 2) - (lineHeight / 2);
	SDL_RenderFillRect(r1->getMainRenderer(), &line);
}

void Draw::draw3DViewPhotoTextured(float Distance, int Res, int currentRay, bool vertical, float rayAngle, float xStep, float yStep)
{



	SDL_Rect FPVrect;
	SDL_Rect SRCrect;
	mut.lock();
	//SDL_Texture* texture = SDL_CreateTextureFromSurface(r1->getMainRenderer(), Images[0]);
	mut.unlock();
	int textureW = Images[0]->w;
	int textureH = Images[0]->h;

	int Shade = 1020 / Distance;
	if (Shade > 255) { Shade = 255; }
	if (Shade < 0) { Shade = 0; }
	mut.lock();
	SDL_SetTextureColorMod(Textures[0], Shade, Shade, Shade);
	mut.unlock();
	SRCrect.w = textureW / 32;
	SRCrect.h = textureH;
	SRCrect.x = 0;
	SRCrect.y = 0;
	float lineHeight = (2 * renderWindowH) / Distance;
	float lineWidth = Res;
	//if (lineHeight > renderWindowH) { lineHeight = renderWindowH; }
	float textureY_step = 32 / (float)lineHeight;
	float textureY_offset = 0;

	float textureY = 0;
	int textureX;
	if (vertical) {
		textureX = (int)(yStep * 16) % 32; if (rayAngle > PI) { textureX = 31 - textureX; }
	}
	else {
		textureX = (int)(xStep * 16) % 32; if (rayAngle > P2 && rayAngle < P3) { textureX = 31 - textureX; }
	}
	FPVrect.w = Res;
	FPVrect.h = lineHeight;
	FPVrect.x = lineWidth * currentRay;
	FPVrect.y = (renderWindowH / 2) - (lineHeight / 2);
	SRCrect.x = (int)(textureX * (textureW / 32.0));
	mut.lock();
	SDL_RenderCopy(r1->getMainRenderer(), Textures[0], &SRCrect, &FPVrect);
	
	mut.unlock();


}

void Draw::drawFloorsPhotoTextured(float rayAngle, float Distance, float rotationAngle, float x, float y, int Res, int currentRay)
{
	/*float nearPlane = 0.01f;
	float farPlane = 5.0f;
	float FOVHalf = 30.0f;

	float fFarX1 = x + cosf(rotationAngle - FOVHalf) * farPlane;
	float fFarY1 = y + sinf(rotationAngle - FOVHalf) * farPlane;

	float fFarX2 = x + cosf(rotationAngle + FOVHalf) * farPlane;
	float fFarY2 = y + sinf(rotationAngle + FOVHalf) * farPlane;

	float fNearX1 = x + cosf(rotationAngle - FOVHalf) * nearPlane;
	float fNearY1 = y + sinf(rotationAngle - FOVHalf) * nearPlane;

	float fNearX2 = x + cosf(rotationAngle + FOVHalf) * nearPlane;
	float fNearY2 = y + sinf(rotationAngle + FOVHalf) * nearPlane;

	SDL_Rect FPVrect;
	SDL_Rect SRCrect;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(r1->getMainRenderer(), Images[0]);
	int textureW = Images[0]->w;
	int textureH = Images[0]->h;
	SRCrect.w = textureW / 32;
	SRCrect.h = textureH / 32;
	SRCrect.x = 0;
	SRCrect.y = 0;
	FPVrect.w = 16;
	FPVrect.h = 16;
	//i = y      j = x
	for (int i = 0; i < renderWindowH / 2; i+=16)
	{
		float fSampleDepth = (float)i / ((float)renderWindowH / 2.0f);

		float fStartX = (fFarX1 - fNearX1) / (fSampleDepth)+fNearX1;
		float fStartY = (fFarY1 - fNearY1) / (fSampleDepth)+fNearY1;
		float fEndX = (fFarX2 - fNearX2) / (fSampleDepth)+fNearX2;
		float fEndY = (fFarY2 - fNearY2) / (fSampleDepth)+fNearY2;
		for (int j = 0; j < renderWindowW; j+=16)
		{
			float fSampleWidth = (float)j / (float)renderWindowW;
			float fSampleX = (fEndX - fStartX) * fSampleWidth + fStartX;
			float fSampleY = (fEndY - fStartY) * fSampleWidth + fStartY;

			fSampleX = fmod(fSampleX, 1.0f);
			fSampleX = fmod(fSampleY, 1.0f);
			SRCrect.x = fSampleY;
			SRCrect.y = fSampleX;
			FPVrect.x = j;
			FPVrect.y = i + renderWindowH / 2;
			SDL_RenderCopy(r1->getMainRenderer(), texture, &SRCrect, &FPVrect);

		}
	}
	SDL_DestroyTexture(texture);*/

	//std::cout << "abcd";

	float lineHeight = (2 * renderWindowH) / Distance;
	float beta = rotationAngle - rayAngle;
	if (beta > 2 * PI) { beta -= 2 * PI; } if (beta < 0) { beta += 2 * PI; }

	SDL_Rect FPVrect;
	SDL_Rect SRCrect;
	mut.lock();
	//SDL_Texture* texture = SDL_CreateTextureFromSurface(r1->getMainRenderer(), Images[1]);
	mut.unlock();
	int textureW = Images[0]->w;
	int textureH = Images[0]->h;
	SRCrect.w = textureW / 32;
	SRCrect.h = textureH / 32;

	float diff = renderWindowH / 2;
	float Shade;

	FPVrect.w = Res;
	FPVrect.h = Res;
	


	for (int i = renderWindowH / 2 + lineHeight / 2; i < renderWindowH; i += Res)
	{

		float dy = i - (renderWindowH / 2.0), raFix = cos(beta);
		float textureX = x * 16 + cos(rayAngle) * 158 * 64 / dy / raFix + 64 ;
		float textureY = y * 16 + sin(rayAngle) * 158 * 64 / dy / raFix + 64 ;
		float texmodx = fmod(textureX, 32.0f);
		float texmody = fmod(textureY, 32.0f);
		//std::cout << textureX << "x" << textureY << std::endl;
		Shade = i - diff + 15;
		if (Shade > 255) { Shade = 255; }
		if (Shade < 0) { Shade = 0; }
		mut.lock();
		SDL_SetTextureColorMod(Textures[1], Shade, Shade, Shade);
		mut.unlock();


		SRCrect.x = texmodx;
		SRCrect.y = texmody;
		FPVrect.x = currentRay * Res;
		FPVrect.y = i;
		mut.lock();
		SDL_RenderCopy(r1->getMainRenderer(), Textures[1], &SRCrect, &FPVrect);
		mut.unlock();
		/* Rysowanie sufitu (spowalnia gre 2 razy xdddd)
		FPVrect.y = renderWindowH - i;
		mut.lock();
		SDL_RenderCopy(r1->getMainRenderer(), texture, &SRCrect, &FPVrect);
		mut.unlock();*/

	}
	
}

void Draw::drawEntitiesin3DSpace(Level& levelIn)
{
	float deltaX, deltaY;
	float entity_dir, entity_dist;
	float entity_xpos;
	float correction;
	float height, width;
	SDL_Rect FPVRect;
	SDL_Rect SRCRect;

	int texNumber;
	

	for (int i = 0; i < levelIn.getEntities().size(); i++)
	{
		entity_dist = Distance(levelIn.getPlayer().x, levelIn.getEntities()[i].x, levelIn.getPlayer().y, levelIn.getEntities()[i].y);
				//////////////////////////////////////zale¿ne od rodzaju przedmiotu
				if (levelIn.getEntities()[i].type == 'i')
				{


					texNumber = 5;
				}
				else if (levelIn.getEntities()[i].type == 'a')
				{
					texNumber = 6;
				}
				/////////////////////////////////////////
				width = renderWindowW / entity_dist;
				height = renderWindowH / entity_dist;

				SRCRect.h = Images[texNumber]->h;
				SRCRect.w = Resolution*entity_dist;
				SRCRect.y = 0;
				SRCRect.x = 0;
				FPVRect.w = Resolution;
				FPVRect.h = height;
				
				deltaX = levelIn.getEntities()[i].x - levelIn.getPlayer().x;
				deltaY = levelIn.getEntities()[i].y - levelIn.getPlayer().y;

				entity_dir = atan2(deltaY, deltaX);

				if (entity_dir - levelIn.getPlayer().rotationAngle > PI) entity_dir -= 2 * PI;
				else if (entity_dir - levelIn.getPlayer().rotationAngle < -PI) entity_dir += 2 * PI;

				entity_dir = (entity_dir - levelIn.getPlayer().rotationAngle) * 180 / PI;
				for (int j = 0; j < width; j += Resolution)
				{

					///////////////////
			
					
					
					
					//////////////////
				
					FPVRect.x = renderWindowW / 2 + entity_dir * (renderWindowW / FOV) + j;
					FPVRect.y = renderWindowH / 2 + (renderWindowH / entity_dist) + entity_dir * atan(entity_dir/(entity_dist*0.1*FOV)) - height;
					int temp = FPVRect.x / Resolution;

					if ((temp) > 0 && (temp) < renderWindowW / Resolution && entity_dist < distances[temp])
					{
						//SDL_SetRenderDrawColor(r1->getMainRenderer(), 0, 0, 255, 255);
						//SDL_RenderFillRect(r1->getMainRenderer(), &FPVRect);
						SDL_RenderCopy(r1->getMainRenderer(), Textures[texNumber], &SRCRect, &FPVRect);
					}
					SRCRect.x += SRCRect.w;
				}
				//std::cout << entity_dist << std::endl;
	}
}

void Draw::drawEnemiesin3DSpace(Level& levelIn)
{
	float deltaX, deltaY;
	float enemy_dir, enemy_dist;
	float enemy_xpos;
	float correction;
	float height, width;
	SDL_Rect FPVRect;
	SDL_Rect SRCRect;

	int texNumber;


	for (int i = 0; i < levelIn.getEnemies().size(); i++)
	{
		enemy_dist = Distance(levelIn.getPlayer().x, levelIn.getEnemies()[i].x, levelIn.getPlayer().y, levelIn.getEnemies()[i].y);
		//////////////////////////////////////zale¿ne od rodzaju przedmiotu
		if (levelIn.getEnemies()[i].type = 'E')
		{

			texNumber = 7;
		}
		if (levelIn.getEnemies()[i].attack == true)
		{
			texNumber++;
		}
		/////////////////////////////////////////
		width =  renderWindowW / enemy_dist;
		height = renderWindowH*1.5 / enemy_dist;

		SRCRect.h = Images[texNumber]->h;
		SRCRect.w = Resolution * enemy_dist;
		SRCRect.y = 0;
		SRCRect.x = 0;
		FPVRect.w = Resolution;
		FPVRect.h = height;

		deltaX = levelIn.getEnemies()[i].x - levelIn.getPlayer().x;
		deltaY = levelIn.getEnemies()[i].y - levelIn.getPlayer().y;

		enemy_dir = atan2(deltaY, deltaX);

		if (enemy_dir - levelIn.getPlayer().rotationAngle > PI) enemy_dir -= 2 * PI;
		else if (enemy_dir - levelIn.getPlayer().rotationAngle < -PI) enemy_dir += 2 * PI;

		enemy_dir = (enemy_dir - levelIn.getPlayer().rotationAngle) * 180 / PI;
		levelIn.getEnemies()[i].visible = false;
		for (int j = 0; j < width; j += Resolution)
		{

			FPVRect.x = renderWindowW / 2 + enemy_dir * (renderWindowW / FOV) + j;
			FPVRect.y = renderWindowH / 2 + (renderWindowH / enemy_dist) + enemy_dir * atan(enemy_dir / (enemy_dist * 0.1 * FOV)) - height;
			int temp = FPVRect.x / Resolution;

			if ((temp) > 0 && (temp) < renderWindowW / Resolution && enemy_dist < distances[temp])
			{
				//SDL_SetRenderDrawColor(r1->getMainRenderer(), 0, 0, 255, 255);
				//SDL_RenderFillRect(r1->getMainRenderer(), &FPVRect);
				SDL_RenderCopy(r1->getMainRenderer(), Textures[texNumber], &SRCRect, &FPVRect);
				levelIn.getEnemies()[i].visible = true;
			}
			SRCRect.x += SRCRect.w;

			
		}
		//std::cout << entity_dist << std::endl;
	}
}


void Draw::display()
{
	SDL_RenderPresent(r1->getMainRenderer());
}

void Draw::drawSprite(int x, int y, int index)
{
	SDL_Rect OutRect;
	OutRect.x = x - (Images[index]->w/2);
	OutRect.y = y - (Images[index]->h / 2);
	OutRect.h = Images[index]->h;
	OutRect.w = Images[index]->w;
	SDL_RenderCopy(r1->getMainRenderer(), Textures[index], NULL, &OutRect);
	
}

void Draw::drawWeaponSprite()
{
	
	SDL_Rect OutRect;
	SDL_Rect InRect;
	InRect.x = weaponAnimationFrame * (Images[9]->w / 5);
	InRect.y = 0;
	InRect.h = Images[9]->h;
	InRect.w = Images[9]->w / 5;
	OutRect.h = renderWindowH / 2;
	OutRect.w = renderWindowW / 5;
	OutRect.x = renderWindowW / 2 - OutRect.w/2 ;
	OutRect.y = renderWindowH - OutRect.h * 4/5;
	
	SDL_RenderCopy(r1->getMainRenderer(), Textures[9], &InRect, &OutRect);
}

void Draw::weaponAnimation(bool& isRunning, bool& shot)
{
	weaponAnimationFrame = 0;
	SDL_Event Event;
	while (isRunning)
	{

		if (shot)
		{

			weaponAnimationFrame = 1;
			Sleep(100);
			weaponAnimationFrame = 2;
			Sleep(100);
			weaponAnimationFrame = 3;
			Sleep(100);
			weaponAnimationFrame = 4;
			Sleep(100);
			weaponAnimationFrame = 5;
			Sleep(100);
			weaponAnimationFrame = 0;
			shot = false;
		}
	}
}

float Draw::Distance(float x1, float x2, float y1, float y2)
{

	return sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));
}

int& Draw::getResolution()
{
	return Resolution;
}

int& Draw::getFOV()
{
	return FOV;
}

void Draw::loadTextures()
{
	using namespace std::filesystem;

	for (const directory_entry& opl : recursive_directory_iterator(current_path())) {
		if (opl.path().extension().string() == ".bmp") {
			std::string name = opl.path().filename().string();
			std::regex reg("^\\d+[A-Za-z]+\\.[A-Za-z]+");
			std::smatch match;

			if (std::regex_match(name, match, reg))
			{
				SDL_Surface* Image = SDL_LoadBMP(opl.path().string().c_str());
				Images.push_back(Image);
			}
			}
			

			
	}

	//dodaj filesystem
	
	
}

void Draw::createTextureObjects()
{
	for (int i = 0; i < Images.size(); i++)
	{
		
		//std::cout << SDL_GetError();
		Textures.push_back(SDL_CreateTextureFromSurface(r1->getMainRenderer(), Images[i]));
		
	}
}
