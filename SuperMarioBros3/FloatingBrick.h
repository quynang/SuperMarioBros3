#pragma once
#include "StaticObject.h"
#define BOUNCING_STATE	100
#define REBOUNDING_STATE	200
#define STATIC_STATE	300

#define MAX_HEIGHT	15

#define BRICK_ANI_QUESTION_MARK	0
#define BRICK_ANI_COLLECTED	1
#define BRICK_BOX_WIDTH	16
#define BRICK_BOX_HEIGHT	16

#define BOUNCE_SPEED_Y	0.6f

//Item type
#define	ITEM_TYPE_RED_MUSHROOM	1000
#define ITEM_TYPE_COIN	0
#define ITEM_TYPE_SUPER_LEAF	2000

class CFloatingBrick : public StaticObject
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
	CFloatingBrick(float init_y, int item_type) { this->init_y = init_y; this->item_type = item_type; };
	int GetState() { return this->state; }
	virtual void SetState(int state);
};