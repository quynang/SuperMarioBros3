#pragma once
#include "Item.h"

#define SUPER_LEAF_ANI_SET_ID	11
#define SUPER_LEAF_ANI_LEFT_INDEX	0
#define SUPER_LEAF_ANI_RIGHT_INDEX	1

#define SUPER_LEAF_SPEED_BOUNCING_Y	-0.25f
#define SUPER_LEAF_SPEED_Y	0.05f;
#define SUPER_LEAF_SPEED_X	0.1f

#define SUPER_LEAF_STATE_BOUNCING	100
#define SUPER_LEAF_STATE_FALLING	200

#define SUPER_LEAF_BBOX_WIDTH	16
#define SUPER_LEAF_BBOX_HEIGHT	14

#define MAX_CHARGE_Y	40
#define MAX_CHARGE_X	20

class SuperLeaf : public Item
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt);
	virtual void Render();
	float	charge_y = 0;
	float	charge_x = 0;
	int state;
public:
	SuperLeaf(float x, float y);
	int GetState() { return this->state; }
	virtual void SetState(int state);
	void handleIsCollected();
};