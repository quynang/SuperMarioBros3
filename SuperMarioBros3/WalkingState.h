#pragma once
#include "MarioState.h"

#define MARIO_ANI_BIG_WALKING_RIGHT			4
#define MARIO_ANI_BIG_WALKING_LEFT			5
#define MARIO_ANI_SMALL_WALKING_RIGHT		6
#define MARIO_ANI_SMALL_WALKING_LEFT		7
#define MARIO_ANI_SMALL_RUNNING_LEFT	18
#define MARIO_ANI_SMALL_RUNNING_RIGHT	17
#define MARIO_ANI_BIG_RUNNING_LEFT	20
#define MARIO_ANI_BIG_RUNNING_RIGHT	19
#define RACCOON_MARIO_ANI_WALKING_RIGHT	27
#define RACCOON_MARIO_ANI_WALKING_LEFT	28
#define RACCOON_MARIO_ANI_RUNNING_RIGHT	29
#define RACCOON_MARIO_ANI_RUNNING_LEFT	30
#define FIRE_MARIO_ANI_WALKING_RIGHT	67
#define FIRE_MARIO_ANI_WALKING_LEFT	68
#define FIRE_MARIO_ANI_RUNNING_RIGHT	69
#define FIRE_MARIO_ANI_RUNNING_LEFT	70

class WalkingState : public MarioState {

	float counter_time = 0;
	int in_speed_run = 0;

public:
	WalkingState() { current_state = WALKING; };

	virtual void handleOnKeyUp(CMario& mario, int keyCode);

	virtual void handleOnKeyDown(CMario& mario, int keyCode);

	virtual void handleKeyState(CMario& mario, BYTE* states);

	virtual void update(CMario& mario, DWORD dt);

	int getAni(CMario& mario);
};