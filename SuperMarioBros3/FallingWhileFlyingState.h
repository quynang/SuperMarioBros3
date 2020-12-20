#pragma once
#include "MarioState.h"
class CMario;

#define MARIO_SLOW_GRAVITY	0.005f

class FallingWhileFlyingState : public MarioState {
	int flap_tails = 0;
public:

	FallingWhileFlyingState() { current_state = FALLING_WHILE_FLYING; };

	void handleOnKeyUp(CMario& mario, int keyCode);

	void handleOnKeyDown(CMario& mario, int keyCode);

	void handleKeyState(CMario& mario, BYTE* states);

	void update(CMario& mario, DWORD dt);

	int getAni(CMario& mario);

};

