#include "Player.h"

#include <Arduino.h>


Player::Player(uint8_t _x, uint8_t _y)
{
	/*
	if(!Renderer::loadBMP("plane35.bmp", img)) {
		Renderer::Get()->fillScreen(ST7735_BLACK);
		Renderer::Get()->setTextSize(2);
		Renderer::Get()->setTextColor(ST7735_RED);
		Renderer::Get()->print("Couldn't load image");
		delay(100000);
	}*/
	
	x = _x;
	y = _y;

	newX = x;
	newY = y;

	Draw();

	width = 35; //img.width;
	height = 9; //img.height;
}

Player::~Player() {
}

void Player::Update(unsigned long deltaTime)
{
	int baseX, baseY;

	baseX = 522;
	baseY = 512;


	xVel = (analogRead(A0) - baseX) / Renderer::Get()->width() * ((float)deltaTime / 30);
	yVel = (analogRead(A1) - baseY) / Renderer::Get()->height() * ((float)deltaTime / 30);


	newX = (uint8_t)round(constrain(((float)newX - xVel), 0, Renderer::Get()->width() - width));
	newY = (uint8_t)round(constrain(((float)newY - yVel), 0, Renderer::Get()->height() - height));


	if((abs(x- newX) >= 1 || abs(y - newY) >= 1) ) {
		
		Draw();
		
		if(newX > x) {
			Renderer::Get()->fillRect(x, y, newX - x, height, ST7735_BLACK);

		} else if(newX < x) {
			Renderer::Get()->fillRect(newX + width, y, x - newX, height, ST7735_BLACK);

		}
		if(newY > y)
			Renderer::Get()->fillRect(x, y, width, newY - y, ST7735_BLACK);
		else if(newY < y)
			Renderer::Get()->fillRect(x, newY + height, width, y - newY, ST7735_BLACK);

		x = newX;
		y = newY;

		
	}

	
}

void Player::Draw()
{
	//Renderer::drawBMP(newX, newY, img);
	Renderer::bmpDraw("plane35.bmp", newX, newY);
}

