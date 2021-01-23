#pragma once
#include "Effect.h"
#define MARIO_TYPE_UP_ANI_SET_ID	13
#define MARIO_TYPE_UP_ANI_LEFT_INDEX	0
#define MARIO_TYPE_UP_ANI_RIGHT_INDEX	1

#define MAX_TIME_TYPE_UP_EFFECT	600
class MarioTypeUp : public Effect
{
	int nx;
	float counter_time = 0;
public:
	MarioTypeUp(float x, float y, int nx);
	void Update(DWORD dt);
	void Render();

};