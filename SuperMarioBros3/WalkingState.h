#pragma once
#include "MarioState.h"

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