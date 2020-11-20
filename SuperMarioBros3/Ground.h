#pragma once
#include "GameObject.h"
#define FRAME_SIZE	16
class CGround : public CGameObject
{
	int size_width;
	int size_height;
public:
	CGround(int s_w, int s_h) { size_width = s_w;  size_height = s_h; };
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};