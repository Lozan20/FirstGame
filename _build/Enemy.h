#pragma once
#include "Moveable.h"
#include <raylib.h>
class Enemy : public Moveable2D
{
public:
	Enemy();
	Enemy(int, int, int);
private:
	int height;
	bool direction;
	Color color;

public:
	void updatePos(int);
	int getSpec();
	void setColor(Color);
	Color getColor();
};

