#ifndef _BULLET_h
#define _BULLET_h

#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet();
	Bullet(const uint8_t _x, const uint8_t _y);
	~Bullet();

	void Draw() override;
	void Update(uint8_t deltaTime) override;

	void Init(const uint8_t _x, const uint8_t _y);

	bool active;
};

#endif
