#pragma once
#include "MarioState.h"
class CMario;

class IdleState : public MarioState {

public:

	IdleState() { current_state = IDLE; };
	void handleOnKeyUp(CMario& mario, int keyCode);

	void handleOnKeyDown(CMario& mario, int keyCode);

	void handleKeyState(CMario& mario, BYTE* states);

	void update(CMario& mario, DWORD dt);

	int getAni(CMario& mario);
};

