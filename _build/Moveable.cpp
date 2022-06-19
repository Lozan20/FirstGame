#include "Moveable.h"


Moveable2D::Moveable2D()
{
}

int Moveable2D::getXPos()
{
    return this->xPos;
}

void Moveable2D::setXPos(int newPos)
{
    this->xPos = newPos;
}

int Moveable2D::getYPos()
{
    return this->yPos;
}

void Moveable2D::setYPos(int newPos)
{
    this->yPos = newPos;
}

void Moveable2D::addXPos(int addVar)
{
    setXPos(this->xPos + addVar);
}

void Moveable2D::subXPos(int subVar)
{
    setXPos(this->xPos - subVar);
}

void Moveable2D::addYPos(int addVar)
{
    setYPos(this->yPos + addVar);
}

void Moveable2D::subYPos(int subVar)
{
    setYPos(this->yPos - subVar);
}

int Moveable2D::getSpec()
{
    return 0;
}
