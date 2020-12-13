#include "Coin50.h"

void Coin50::Render()
{
	//RenderBoundingBox();
	animation_set->at(0)->Render(x, y);
}

void Coin50::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + COIN_50_BOX_WIDTH;
	b = y + COIN_50_BOX_HEIGHT;
}