#include "GreenPipe.h"
#include "Utils.h"

void CGreenPipe::Render()
{
	if (type == GREEN_PIPE_TYPE_UP || type == GREEN_PIPE_TYPE_CAN_ENTERING)
		animation_set->at(GREEN_PIPE_ANI_UP)->Render(x, y);

	else if (type == GREEN_PIPE_TYPE_DOWN)
		animation_set->at(GREEN_PIPE_ANI_DOWN)->Render(x, y + FRAME_SIZE * this->size_height - GREEN_PIPE_SPRITE_HEIGHT);
		
	//RenderBoundingBox();
}

void CGreenPipe::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BOX_PIPE_WIDTH;
	b = y + FRAME_SIZE*size_height;
}

void CGreenPipe::SetInitInfoFromStringLine(string line)
{
	vector<string> tokens = split(line);
	int size_height = atoi(tokens[4].c_str());
	int type = atoi(tokens[5].c_str());
	this->size_height = size_height;
	this->type = type;
}
