#include "Player.h"

Player::Player(int xPos_, int yPos_, int radius_) : Moveable2D(xPos_,yPos_)
{
	this->setRadius(radius_);
    this->speed = 10;
}

Player::Player()
{

}

int Player::getRadius()
{
    return this->radius;
}

void Player::setRadius(int newRadius)
{
    this->radius = newRadius;
}

int Player::getSpec()
{
    return this->radius;
}

int Player::getSpeed()
{
    return this->speed;
}

void Player::setSpeed(int speed_)
{
    this->speed = speed_;
}
