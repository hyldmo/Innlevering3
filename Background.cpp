#include "Background.h"

Background::Background(int y)
{
	x1 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;
}

Background::~Background() {}

void Background::Update(unsigned long deltaTime)
{
}

void Background::Draw()
{
	while(x1 + x2 < Renderer::Get()->width()) {
		y2 = random(30);
		Renderer::Get()->drawLine(x1, y1, (x1 += 10) + 10, y2, ST7735_WHITE);
		(y1 = random(30));
		Renderer::Get()->drawLine(x1, y2, (x1 += 10) + 10, y1, ST7735_WHITE);
	}
}
