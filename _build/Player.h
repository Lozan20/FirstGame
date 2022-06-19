#pragma once
#include "Moveable.h"
class Player : public Moveable2D
{
public:
	Player(int xPos_, int yPos_, int radius_);
	Player();
private:
	int xPos;
	int yPos;
	int radius;
	int speed;
public:
	int getRadius();
	void setRadius(int);
	int getSpec();
	int getSpeed();
	void setSpeed(int );
};

