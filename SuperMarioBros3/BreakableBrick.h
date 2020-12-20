#pragma once
#include "StaticObject.h"
#define BREAKABLE_BRICK_ANI_SET_ID	12
#define BREAKABLE_BRICK_BBOX_WIDTH	16
#define BREAKABLE_BRICK_BBOX_HEIGHT	16

class BreakableBrick : public StaticObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt);
	virtual void Render();
	int state;
	int item_type;

public:
	float countY_ = 0;
	float init_y;
	void ProduceItem();
	int GetState() { return this->state; }
	virtual void SetState(int state);
	void handleIsBroken();
};