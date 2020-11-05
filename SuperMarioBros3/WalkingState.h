#pragma once
#include "MarioState.h"
class WalkingState : public MarioState {

public:
	virtual void handleOnKeyUp(CMario& mario, int keyCode);

	virtual void handleOnKeyDown(CMario& mario, int keyCode);

	virtual void handleKeyState(CMario& mario, BYTE* states);

	virtual void update(CMario& mario);
};