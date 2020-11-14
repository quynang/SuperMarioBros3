#pragma once
#include "MarioState.h"
#define RACCOON_MARIO_ANI_FLYING_STATE_RIGHT	33
#define RACCOON_MARIO_ANI_FLYING_STATE_LEFT	34
#define MAX_TIME	2.0f
class FlyingState : public MarioState
{
	float counter_time = 0;
public:
	FlyingState() { current_state = FLYING; };
	void handleOnKeyUp(CMario& mario, int keyCode);

	void handleOnKeyDown(CMario& mario, int keyCode);

	void handleKeyState(CMario& mario, BYTE* states);

	void update(CMario& mario, DWORD dt);

	int getAni(CMario& mario);
};

