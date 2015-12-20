#include "Bullet.h"

Bullet::Bullet()
{
	active = false;
	x = 200;
	y = 200;
}

Bullet::Bullet(const int _x, const int _y)
{
	active = true;
	x = _x;
	y = _y;
}

Bullet::~Bullet() {}

void Bullet::Draw()
{
	Renderer::Get()->fillCircle(x, y, 1, ST7735_BLUE);
}

void Bullet::Update(unsigned long deltaTime)
{
	if(active) {
		Renderer::Get()->fillCircle(x, y, 1, ST7735_BLACK);
		x += 7;
		Draw();

		if(x-2 > Renderer::Get()->width())
			active = false;
	}
}

void Bullet::Init(const int _x, const int _y) {
	active = true;
	x = _x;
	y = _y;
}
