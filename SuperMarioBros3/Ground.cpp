#include "Ground.h"

void CGround::Render()
{
	RenderBoundingBox();
}

void CGround::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + GROUND_BOX_WIDTH;
	b = y + GROUND_BOX_HEIGHT;
}