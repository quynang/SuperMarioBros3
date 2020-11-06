#pragma once
#include "MarioState.h"
class CMario;

class IdleState : public MarioState {

public:

	//IdleState() { debug_state = 1; };
	void handleOnKeyUp(CMario& mario, int keyCode);

	void handleOnKeyDown(CMario& mario, int keyCode);

	void handleKeyState(CMario& mario, BYTE* states);

	void update(CMario& mario, DWORD dt);

};

