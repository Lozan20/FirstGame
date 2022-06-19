#pragma once
class Moveable2D
{
public:
	Moveable2D(int xPos_, int yPos_)
	{
		this->setXPos(xPos_);
		this->setYPos(yPos_);
	}
	Moveable2D();
private:
	int xPos;
	int yPos;
public:
	int getXPos();
	void setXPos(int);
	int getYPos();
	void  setYPos(int);
	void addXPos(int);
	void subXPos(int);
	void addYPos(int);
	void subYPos(int);
	virtual int getSpec();
};

