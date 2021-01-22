#pragma once
#include "MarioState.h"
class CMario;
#define MOVING_BAR_SPEED_FALLING	0.1f

class StandOnMovingBarState : public MarioState {

public:

	StandOnMovingBarState() { current_state = STAND_ON_MOVING_BAR; };
	void handleOnKeyUp(CMario& mario, int keyCode);

	void handleOnKeyDown(CMario& mario, int keyCode);

	void handleKeyState(CMario& mario, BYTE* states);

	void update(CMario& mario, DWORD dt);

	int getAni(CMario& mario);
};

