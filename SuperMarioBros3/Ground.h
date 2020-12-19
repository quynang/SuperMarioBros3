#pragma once
#include "GameObject.h"
#include "Utils.h"
#include "StaticObject.h"
#define GROUND_BOX_WIDTH  16
#define GROUND_BOX_HEIGHT 16

class CGround : public StaticObject
{
public:
	virtual void Render();
	CGround() { this->ignore_collide_nx = true; }
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};