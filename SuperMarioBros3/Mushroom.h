#pragma once
#include "Item.h"

#define MUSHROOM_GRAVITY	0.08f
#define MUSHROOM_MOVING_SPEED	0.08f
#define MUSHROOM_SPROUT_SPEED_Y	-0.05f
#define MUSHROOM_MOVING_SPEED 0.1f
#define MUSHROOM_STATE_SPROUT	100
#define MUSHROOM_STATE_MOVING	200
#define MUSHROOM_STATE_COLLECTED	300

#define ITEMS_ANI_SET	7

#define MUSHROOM_BBOX_WIDTH	16
#define MUSHROOM_BBOX_HEIGHT	16
class Mushroom : public Item
{
protected:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt);
	virtual void Render();
	float	charge_y = 0;
	int state;
public:
	Mushroom();
	Mushroom(float x, float y);
	int GetState() { return this->state; }
	virtual void SetState(int state);
	void handleIsCollected();
};