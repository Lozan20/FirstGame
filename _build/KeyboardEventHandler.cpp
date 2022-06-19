#include "KeyboardEventHandler.h"
#include <raylib.h>
#include "WindowVars.h"

void KeyboardEventHandler::handleChange(Moveable2D *obj,int speed)
{
	if (IsKeyDown(KEY_D))
	{
		if (obj->getXPos() <= WindowVars::width - obj->getSpec())
		{
			obj->addXPos(speed);
		}
	}
	if (IsKeyDown(KEY_A))
	{
		if (obj->getXPos() >= obj->getSpec())
		{
			obj->subXPos(speed);
		}
	}
	if (IsKeyDown(KEY_S))
	{
		if (obj->getYPos() <= WindowVars::height - obj->getSpec())
		{

			obj->addYPos(speed);
		}
	}
	if (IsKeyDown(KEY_W))
	{
		if (obj->getYPos() >= obj->getSpec())
		{
			obj->subYPos(speed);
		}
	}
}