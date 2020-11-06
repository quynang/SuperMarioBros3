#include "GreenPipe.h"

void CGreenPipe::Render()
{
	RenderBoundingBox();
}

void CGreenPipe::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BOX_PIPE_WIDTH;
	b = y + FRAME_SIZE*size_height;
}