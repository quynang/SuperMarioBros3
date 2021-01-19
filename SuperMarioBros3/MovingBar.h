#pragma once
#include "MovableObject.h"

#define MOVING_BAR_ANI_SET_ID	26

#define MOVING_BAR_SPEED_X -0.02f
#define MOVING_BAR_SPEED_FALLING	0.05f

#define MOVING_BAR_BBOX_WIDTH	48
#define MOVING_BAR_BBOX_HEIGHT	16

#define MOVING_BAR_STATE_STATIC	100
#define MOVING_BAR_STATE_MOVING	200
#define MOVING_BAR_STATE_FALLING	300

class MovingBar : public MovableObject
{
protected:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt);
	virtual void Render();
	int state;
public:
	MovingBar();
	int GetState() { return this->state; }
	virtual void SetState(int state);
};