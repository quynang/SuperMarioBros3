#pragma once
#include "BrickAbstract.h"

#define FLOATING_BRICK_ANI_SET_ID	4
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
#define BRICK_ITEM_TYPE_COIN_EFFECT	0
#define BRICK_ITEM_TYPE_DYNAMIC	1
#define BRICK_ITEM_TYPE_BUTTON_P	2
#define BRICK_ITEM_TYPE_GREEN_MUSHROOM	3

class CFloatingBrick : public BrickAbstract
{
protected:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt);
	void Render();
	int state = 0;
	int item_type = 0;
	int count_item = 1;

public:
	float countY_ = 0;
	float init_y = 0;
	void ProduceItem();
	CFloatingBrick() { this->SetAnimationSetById(FLOATING_BRICK_ANI_SET_ID); };
	int GetState() { return this->state; }
	virtual void SetState(int state);
	virtual void SetInitInfoFromStringLine(string line);
	virtual void handleWasHitByHeadOfMario();
	virtual void handleWasAttacked();

};