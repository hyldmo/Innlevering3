#ifndef _GAMEOBJECT_h
#define _GAMEOBJECT_h

#include "Renderer.h"

class GameObject
{
public:
	GameObject();
	GameObject(uint8_t _x, uint8_t _y);
	virtual ~GameObject();

	virtual void Update(uint8_t deltaTime) = 0; //deltaTime is in milliseconds
	virtual void Draw() = 0;
	
	uint8_t x, y;

protected:

	uint8_t newX, newY;

};

#endif

