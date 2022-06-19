#include "Enemy.h"
#include "WindowVars.h"
Enemy::Enemy() : Moveable2D(WindowVars::width/2-50,WindowVars::height/2-50)
{
	this->height = 100;
	this->direction = false;
	this->color = BLUE;
}
Enemy::Enemy(int posX, int posY, int height) : Moveable2D(posX, posY)
{
	this->height = height;
	this->color = BLUE;
}

void Enemy::updatePos(int speed)
{
	if (!this->direction)
	{
		this->addYPos(speed);
		if (this->getYPos() >= WindowVars::height- this->getSpec()/2-10)
		{
			this->direction = true;
		}
	}
	else
	{
		this->subYPos(speed);
		if (this->getYPos() <= 10)
		{
			this->direction = false;
		}
	}

}

int Enemy::getSpec()
{
	return this->height;
}

void Enemy::setColor(Color newColor)
{
	this->color = newColor;
}

Color Enemy::getColor()
{
	return this->color;
}
