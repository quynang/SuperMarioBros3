#pragma once
#include "MarioState.h"
class CMario;

class FallingState : public MarioState {
	bool slow_falling = false;

public:

	FallingState() { current_state = FALLING; };

	void handleOnKeyUp(CMario& mario, int keyCode);

	void handleOnKeyDown(CMario& mario, int keyCode);

	void handleKeyState(CMario& mario, BYTE* states);

	void update(CMario& mario, DWORD dt);

	int getAni(CMario& mario);
};

