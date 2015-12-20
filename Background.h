#pragma once

#include "GameObject.h"

class Background : public GameObject
{
public:
	Background(int y);
	~Background();

	void Update(unsigned long deltaTime);
	void Draw() override;


private:

	int x1, y1, x2, y2;
};