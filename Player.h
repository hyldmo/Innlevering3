#ifndef _PLAYER_h
#define _PLAYER_h

#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(uint8_t _x, uint8_t _y);
	~Player();

	void Update(uint8_t deltaTime) override;
	void Draw() override;

	uint8_t width, height;
private:

	float xVel, yVel;
	

	Renderer::Image img;
};

#endif