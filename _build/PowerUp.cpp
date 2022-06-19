#include "PowerUp.h"

float PowerUp::timer = 0.0f;
bool PowerUp::isMoveFasterActivated = false;
bool PowerUp::isSlowDownActivated = false;
PowerUp::PowerUp() : Moveable2D(GetRandomValue(150, 1200), GetRandomValue(0, 100))
{
	this->height = 50;
	this->powerUpType = selectRandomPowerUp();
	this->texture = loadTexture(this->powerUpType);
}

int PowerUp::getSpec()
{
	return this->height;
}

int PowerUp::selectRandomPowerUp()
{
	return GetRandomValue(1, 4);
}

Texture2D PowerUp::loadTexture(int type)
{
	Texture2D* temp = new Texture2D();
	Image powerup;
	switch (type)
	{
	case 1:
		powerup = LoadImage("resources/divideenemies.png");
		break;
	case 2:
		powerup = LoadImage("resources/minustwo.png");
		break;
	case 3:
		powerup = LoadImage("resources/slowdown.png");
		break;
	case 4:
		powerup = LoadImage("resources/movefaster.png");
		break;
	}
	*temp = LoadTextureFromImage(powerup);
	UnloadImage(powerup);
	texture = *temp;
	return *temp;
}

Texture2D PowerUp::getTexture()
{
	return this->texture;
}

int PowerUp::getHeight()
{
	return 0;
}

void PowerUp::setHeight()
{
}

int PowerUp::getPowerUpType()
{
	return this->powerUpType;
}

void PowerUp::setPowerUpType()
{
}

void PowerUp::startTimer()
{
	timer = GetTime();
}

float PowerUp::getTimer()
{
	return timer;
}

void PowerUp::resetTimer()
{
	timer = 0;
}

