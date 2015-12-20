#ifndef _PLAYER_h
#define _PLAYER_h

#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(uint8_t _x, uint8_t _y);
	~Player();

	void Update(unsigned long deltaTime) override;
	void Draw() override;
private:

	Renderer::Image img;
};

#endif