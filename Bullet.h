#ifndef _BULLET_h
#define _BULLET_h

#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet();
	Bullet(const int _x, const int _y);
	~Bullet();

	void Draw() override;
	void Update(unsigned long deltaTime) override;

	void Init(const int _x, const int _y);

	bool active;
};

#endif
