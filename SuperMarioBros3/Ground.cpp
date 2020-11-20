#include "Ground.h"

void CGround::Render()
{
	//RenderBoundingBox();
}

void CGround::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + FRAME_SIZE*size_width;
	b = y + FRAME_SIZE*size_height;
}