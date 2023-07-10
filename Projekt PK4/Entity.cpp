#include "Entity.h"

void Entity::setCoordinates(float xIn, float yIn)
{
	x = xIn;
	y = yIn;
}

void Entity::setType(char cIn)
{
	type = cIn;
}

void movingEntity::setRotation(float rotIn)
{
	rotationAngle = rotIn;
}



void Player::move(int *map, int grid)
{
	//kolizja
	float xCol = 0.6, yCol = 0.6;
	
	if (map[(int)((int)y * grid + x - 1)] == 1 && rotationAngle >P2 && rotationAngle <P3) { xCol = 0; }
	if (map[(int)((int)y * grid + x + 1)] == 1 && (rotationAngle < P2 || rotationAngle > P3)) { xCol = 0; }
	if (map[(int)((int)(y - 1) * grid + x)] == 1 && (rotationAngle > PI)) { yCol = 0; }
	if (map[(int)((int)(y + 1) * grid + x)] == 1 && (rotationAngle < PI)) { yCol = 0; }
	//sterowanie graczem tutaj
	if (mvForward) {  x += deltax * xCol; y += deltay * yCol; }
	if (mvBack) { x -= deltax; y -= deltay; }
	if (trnLeft) { rotationAngle -= 0.1; if (rotationAngle < 0) { rotationAngle += 2 * PI; } deltax = cos(rotationAngle); deltay = sin(rotationAngle) ; }
	if (trnRight) { rotationAngle += 0.1; if (rotationAngle > 2*PI) { rotationAngle -= 2 * PI; } deltax = cos(rotationAngle); deltay = sin(rotationAngle) ; }


}

float Player::get_deltax()
{
	return deltax;
}

float Player::get_deltay()
{
	return deltay;
}




void Enemy::think()
{
	if (*randomNumber % 2 == 0)
	{
		moveConditional = true;
	}
	if (*randomNumber % 3 == 0)
	{

		if (*randomNumber % 10 > 5) deltax = ((float)*randomNumber / 100000);
		if (*randomNumber % 10 < 5) deltax = -((float)*randomNumber / 100000);
		
	}
	if (*randomNumber % 4 == 0)
	{
		if (*randomNumber % 10 > 5) deltay = ((float)*randomNumber / 100000);
		if (*randomNumber % 10 < 5) deltay = -((float)*randomNumber / 100000);
	}
	if (*randomNumber % 2 != 0)
	{
		moveConditional = false;
	}
	if (*randomNumber % 7 == 0)
	{
		attack = true;
	}
	if (*randomNumber % 7 != 0)
	{
		attack = false;
	}
}

void movingEntity::move(int* map, int grid)
{
	if (moveConditional) {
		float xCol = 1.0, yCol = 1.0;

		if (map[(int)((int)y * grid + x - 1)] == 1 && rotationAngle > P2 && rotationAngle < P3) { xCol = 0; }
		if (map[(int)((int)y * grid + x + 1)] == 1 && (rotationAngle < P2 || rotationAngle > P3)) { xCol = 0; }
		if (map[(int)((int)(y - 1) * grid + x)] == 1 && (rotationAngle > PI)) { yCol = 0; }
		if (map[(int)((int)(y + 1) * grid + x)] == 1 && (rotationAngle < PI)) { yCol = 0; }

		x += deltax * xCol; y += deltay * yCol;
	}
}
