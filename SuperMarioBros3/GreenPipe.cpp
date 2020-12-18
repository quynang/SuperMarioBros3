#include "GreenPipe.h"

void CGreenPipe::Render()
{
	if (type == GREEN_PIPE_TYPE_UP)
		animation_set->at(GREEN_PIPE_ANI_UP)->Render(x, y);
	else if (type == GREEN_PIPE_TYPE_DOWN)
		animation_set->at(GREEN_PIPE_ANI_DOWN)->Render(x, y + this->size_height * FRAME_SIZE - GREEN_PIPE_SPRITE_HEIGHT);
	//RenderBoundingBox();
}

void CGreenPipe::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BOX_PIPE_WIDTH;
	b = y + FRAME_SIZE*size_height;
}