#pragma once
#include "GameObject.h"

#define GROUND_BOX_WIDTH  16
#define GROUND_BOX_HEIGHT 16

class CGround : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};