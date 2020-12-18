#pragma once

#include "Enemy.h"
#define PIRANHA_BBOX_WIDTH	16
#define PIRANHA_BBOX_HEIGHT	24
#define PIRANHA_SPEED_Y 0.08f
#define MAX_Y	23
#define PIRANHA_STATE_MOVE_UP	100
#define PIRANHA_STATE_MOVE_DOWN	200
#define PIRANHA_STATE_HIDDEN	300
#define PIRANHA_STATE_WAITING	400

#define MAX_TIME_TO_SWICTH_ACTION	800
class PiranhaPlant : public Enemy
{
	int state;
	float charge_y = 0;
	float counter_time = 0;
public:
	PiranhaPlant();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt);
	virtual void Render();
	int GetState() { return this->state; }
	virtual void SetState(int state);
};