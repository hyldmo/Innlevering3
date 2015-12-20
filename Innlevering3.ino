#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "Renderer.h"
#include <SPI.h>
#include <SD.h>
#include "Renderer.h"
#include "PoolFactory.h"
#include "Background.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"


int x1, y1, x2, y2;
int xInc;
Background* bg;
Player* player;
const int poolSize = 20; //refactor this
//Bullet* bulletPool[poolSize];
PoolFactory<Bullet, 20> bulletPool;
//PoolFactory<Enemy, 8> enemyPool;

int count;

unsigned long newTime;
uint8_t deltaTime;
unsigned long oldTime;

void setup()
{
	pinMode(6, INPUT);

	Serial.begin(9600);

	x1 = 0;
	y1 = 0; 
	x2 = 0;
	y2 = 0;
	xInc = 0;
	count = 0;
	player = new Player(5, Renderer::Get()->height() / 2);
	//bg = new Background(10);
	bulletPool = PoolFactory<Bullet, 20>();
	//enemyPool = new PoolFactory<Enemy, 8>;
	newTime = millis();

	//enemyPool->NewItem(Renderer::Get()->width(), Renderer::Get()->height() / 2);
}

void loop() {
	oldTime = newTime;
	newTime = millis();
	deltaTime = newTime - oldTime;


	player->Update(deltaTime);
	if (digitalRead(6))
	{
		bulletPool.NewItem(player->x + player->width, player->y + player->height / 2);
	}

	bulletPool.UpdateAll(deltaTime);
	//enemyPool->UpdateAll(deltaTime);
	
	/*
	if(digitalRead(6))
	{
		if(count == poolSize - 1) {
			count = 0;
		}

		if(bulletPool[count])
			bulletPool[count++]->Init(player->x + player->width, player->y + player->height/2);
		else 
			bulletPool[count++] = new Bullet(player->x + player->width, player->y + player->height / 2);
	}

	for(int i = 0; i < poolSize; i++)
	{
		if (bulletPool[i])
			bulletPool[i]->Update(deltaTime);
		else break;
	}
	*/
	delay(10);
	//bg->Draw();
}
