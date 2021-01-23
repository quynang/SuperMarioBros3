#pragma once
#include "Effect.h"
#define ENTERING_PIPE_ANI_SET_ID	27
#define MARIO_TYPE_SMALL_INDEX	0
#define MARIO_TYPE_BIG_INDEX	1
#define MARIO_TYPE_RACCOON_INDEX	2
#define MARIO_TYPE_FIRE_INDEX	3
#define SPEED_Y 0.08f
#define MARIO_TYPE_SMALL	1
#define MARIO_TYPE_BIG	2
#define MARIO_TYPE_RACCOON	3
#define MARIO_TYPE_FIRE	4
#define MAX_Y_ENTERING_PIPE_EFFECT	32
#define MAX_TIME_ENTERING_PIPE_EFFECT	600
class EnteringPipe : public Effect
{
	int scence_id;
	float counter_time = 0;
	float counter_y = 0;
public:
	EnteringPipe(float x, float y, int scence_id);
	void Update(DWORD dt);
	void Render();

};