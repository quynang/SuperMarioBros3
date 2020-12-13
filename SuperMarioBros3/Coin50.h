#pragma once
#include "Utils.h"
#include "StaticObject.h"
#define COIN_50_BOX_WIDTH  14
#define COIN_50_BOX_HEIGHT 16

class Coin50 : public StaticObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};