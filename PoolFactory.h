#ifndef _POOLFACTORY_h 
#define  _POOLFACTORY_h 

#include "GameObject.h"

template <class T, uint8_t max_items> 
class PoolFactory
{
public:
	PoolFactory();

	void NewItem(uint8_t x, uint8_t y);

	T pool[max_items];

	void UpdateAll(uint8_t deltaTime);

private: 

	uint8_t index;
	uint8_t numObjects;
};

//This has to be here for c++ reasons

template <class T, uint8_t max_items>
PoolFactory<T, max_items>::PoolFactory()
{
	index = 0;
	numObjects = 0;
}

template <class T, uint8_t max_items>
void PoolFactory<T, max_items>::NewItem(uint8_t x, uint8_t y)
{
	if (index == max_items) {
		index = 0;
	}
	if (numObjects < max_items)
	{
		pool[index++] = T(x, y);
		numObjects++;
	}
	else
		pool[index++].Init(x, y);
		


}

template <class T, uint8_t max_items>
void PoolFactory<T, max_items>::UpdateAll(uint8_t deltaTime)
{
	for (int i = 0; i < max_items; i++)
	{
		if (i < numObjects) {
			pool[i].Update(deltaTime);
			pool[i].Draw();
		}
		else break;
	}
}


#endif
