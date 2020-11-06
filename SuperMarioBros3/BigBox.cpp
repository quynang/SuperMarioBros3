#include "BigBox.h"

void CBigBox::Render()
{
	RenderBoundingBox();
}

void CBigBox::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + FRAME_SIZE*size_width;
	b = y + FRAME_SIZE*size_height;
}