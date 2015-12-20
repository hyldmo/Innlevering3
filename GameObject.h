#ifndef _GAMEOBJECT_h
#define _GAMEOBJECT_h

#include "Renderer.h"

class GameObject
{
public:
	GameObject();
	GameObject(uint8_t _x, uint8_t _y);
	virtual ~GameObject();

	virtual void Update(unsigned long deltaTime) = 0; //deltaTime is in milliseconds
	virtual void Draw() = 0;
	uint8_t x, y;

	uint8_t width, height;

protected:
	uint8_t newX, newY;
	float xVel, yVel;

};

#endif

