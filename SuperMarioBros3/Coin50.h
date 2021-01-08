#pragma once
#include "Utils.h"
#include "Item.h"
#define COIN_50_ANI_SET_ID	9
#define COIN_50_BOX_WIDTH  14
#define COIN_50_BOX_HEIGHT 16
#define COIN_50_ANI_SET_ID	9
class Coin50 : public Item
{
public:
	Coin50() { SetAnimationSetById(COIN_50_ANI_SET_ID); };
	Coin50(float x, float y);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void handleIsCollected();
};