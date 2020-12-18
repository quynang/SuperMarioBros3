#pragma once
#include "GameObject.h"
#include "StaticObject.h"

#define GREEN_PIPE_ANI_UP	0
#define GREEN_PIPE_ANI_DOWN	1
#define BOX_PIPE_WIDTH 32
#define FRAME_SIZE	16
#define GREEN_PIPE_SPRITE_HEIGHT 32
#define GREEN_PIPE_TYPE_UP	1
#define GREEN_PIPE_TYPE_DOWN	2
#define GREEN_PIPE_TYPE_NONE_ANI	3
class CGreenPipe : public StaticObject
{
	int size_height;
	int type;
public:
	CGreenPipe(int s_h, int type) { this->size_height = s_h; this->type = type; };
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};