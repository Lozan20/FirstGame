#pragma once
#include "Moveable.h"
#include <raylib.h>
class PowerUp : public Moveable2D
{
	int height;
	int powerUpType; 
	Texture2D texture;
	public:
	static float timer;
	static bool isSlowDownActivated;
	static bool isMoveFasterActivated;
public:
	PowerUp();
	int getSpec();
	int selectRandomPowerUp();
	Texture2D loadTexture(int);
	Texture2D getTexture();
	int getHeight();
	void setHeight();
	int getPowerUpType();
	static void setPowerUpType();
	static void startTimer();
	static float getTimer();
	static void resetTimer();

};


