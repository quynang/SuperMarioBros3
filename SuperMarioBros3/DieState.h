#pragma once
#include "MarioState.h"
class CMario;

class DieState : public MarioState {
	float counter_time = 0;
public:

	DieState() { current_state = DIE; };
	void handleOnKeyUp(CMario& mario, int keyCode);

	void handleOnKeyDown(CMario& mario, int keyCode);

	void handleKeyState(CMario& mario, BYTE* states);

	void update(CMario& mario, DWORD dt);

	int getAni(CMario& mario);
};

