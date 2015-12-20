#include "Enemy.h"

#include <Arduino.h>


Enemy::Enemy()
{
}

Enemy::Enemy(uint8_t x, uint8_t y)
{
	width = 20; //img.width;
	height = 20; //img.height;
}

Enemy::~Enemy() {
}


void Enemy::Update(unsigned long deltaTime)
{
	int baseX, baseY;

	baseX = 522;
	baseY = 512;

	newX += xVel;
	newY += yVel;

	newX = constrain(newX, 0, Renderer::Get()->width() - width);
	newY = constrain(newY, 0, Renderer::Get()->height() - height);


	if ((abs(x - newX) >= 1 || abs(y - newY) >= 1)) {

		Draw();

		if (newX > x) {
			Renderer::Get()->fillRect(x, y, newX - x, height, ST7735_BLACK);

		}
		else if (newX < x) {
			Renderer::Get()->fillRect(newX + width, y, x - newX, height, ST7735_BLACK);

		}
		if (newY > y)
			Renderer::Get()->fillRect(x, y, width, newY - y, ST7735_BLACK);
		else if (newY < y)
			Renderer::Get()->fillRect(x, newY + height, width, y - newY, ST7735_BLACK);

		x = newX;
		y = newY;


	}


}

void Enemy::Draw()
{
	Renderer::Get()->drawRect(newX, newY, width, height, ST7735_RED);
}

void Enemy::Init(const uint8_t x, const uint8_t y)
{
	xVel = -5;
	yVel = 0;

	newX = x;
	newY = y;
}
