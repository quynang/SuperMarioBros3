#pragma once
#include "MarioState.h"

#define MARIO_ANI_BIG_WALKING_RIGHT			4
#define MARIO_ANI_BIG_WALKING_LEFT			5
#define MARIO_ANI_SMALL_WALKING_RIGHT		6
#define MARIO_ANI_SMALL_WALKING_LEFT		7

class WalkingState : public MarioState {

public:
	virtual void handleOnKeyUp(CMario& mario, int keyCode);

	virtual void handleOnKeyDown(CMario& mario, int keyCode);

	virtual void handleKeyState(CMario& mario, BYTE* states);

	virtual void update(CMario& mario, DWORD dt);
};