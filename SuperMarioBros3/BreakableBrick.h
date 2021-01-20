#pragma once
#include "BrickAbstract.h"

#define BREAKABLE_BRICK_ANI_SET_ID	12
#define BREAKABLE_BRICK_BBOX_WIDTH	16
#define BREAKABLE_BRICK_BBOX_HEIGHT	16

class BreakableBrick : public BrickAbstract
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt);
	virtual void Render();
	int state;
	bool visible = true;
	int item_type;

public:
	BreakableBrick() { this->tag = "BREAKABLE_BRICK"; SetAnimationSetById(BREAKABLE_BRICK_ANI_SET_ID); }
	float countY_ = 0;
	float init_y;
	void ProduceItem();
	int GetState() { return this->state; }
	virtual void SetState(int state);
	virtual void handleWasHitByHeadOfMario();
	virtual void handleWasAttacked();

};