#pragma once
#include "Moveable.h"
#include "Player.h"
class CollisionDetect
{
public:
	template<typename T,typename K>
	inline static bool checkCollision(Moveable2D* a, Moveable2D* b)
	{
		a = static_cast<T*>(a);
		b = static_cast<K*>(b);
		float testEdgeX = a->getXPos();
		float testEdgeY = a->getYPos();
		if (a->getXPos() < b->getXPos() ) // left
		{
			testEdgeX = b->getXPos()  ;
		}
		else if (a->getXPos()  > b->getXPos() + b->getSpec() ) //right
		{
			testEdgeX = b->getXPos() + b->getSpec()  ;
		}
		if (a->getYPos() < b->getYPos() ) // top
		{
			testEdgeY = b->getYPos()  ;
		}
		else if (a->getYPos() > b->getYPos() + b->getSpec() ) // down
		{
			testEdgeY = b->getYPos() + b->getSpec() ;
		}
		float distX = a->getXPos() - testEdgeX;
		float distY = a->getYPos() - testEdgeY;
		float distance = sqrt((distX * distX) + (distY * distY));
		if (a->getSpec() >= distance)
			return true;
		return false;
	}
	static double checkDistance(int, int, int, int);
};

