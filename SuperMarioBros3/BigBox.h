#pragma once
#include "GameObject.h"
#include "StaticObject.h"
#include "Mario.h"

#define FRAME_SIZE 16

class CBigBox : public StaticObject
{
	int size_width;
	int size_height;

public:
	CBigBox(int s_w, int s_h) { size_width = s_w;  size_height = s_h; };
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};