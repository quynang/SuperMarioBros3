#pragma once
#include "GameObject.h"
#include "StaticObject.h"
#include "Mario.h"

#define FRAME_SIZE 16

class CBigBox : public StaticObject
{
	int size_width = 0;
	int size_height = 0;

public:
	CBigBox() { this->ignore_collide_nx = true; }
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void SetInitInfoFromStringLine(string line);
};