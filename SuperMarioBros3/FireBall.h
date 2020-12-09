#pragma once
#include "MovableObject.h"

#define FIRE_BALL_BBOX_WIDTH  8
#define FIRE_BALL_BBOX_HEIGHT 8
#define FIRE_BALL_ANI_SET	6
#define FIRE_BALL_ANI_RIGHT	0
#define FIRE_BALL_ANI_LEFT	1

#define FIRE_BALL_V0	0.4f
#define FIRE_BALL_GRAVITY	0.004f

class FireBall : public MovableObject
{
	float time_elapsed = 0;
	float angle;
public:
	FireBall();
	FireBall(float x, float y, int nx);
	virtual void Render();
	virtual void Update(DWORD dt);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};