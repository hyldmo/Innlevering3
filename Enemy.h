#ifndef _ENEMY_h
#define _ENEMY_h

#include "GameObject.h"

class Enemy : public GameObject
{
public:
	Enemy();
	Enemy(uint8_t x, uint8_t y);
	~Enemy();

	void Update(unsigned long deltaTime);
	void Draw() override;
	float x, y, newX, newY;
	float xVel, yVel;

	int width, height;

	void Init(const uint8_t x, const uint8_t y);
};


#endif

