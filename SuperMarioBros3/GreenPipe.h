#pragma once
#include "GameObject.h"

#define BOX_PIPE_WIDTH 32
#define FRAME_SIZE	16
class CGreenPipe : public CGameObject
{
	int size_height;

public:
	CGreenPipe(int s_h) { size_height = s_h; };
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};