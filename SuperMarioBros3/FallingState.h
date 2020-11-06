#pragma once
#include "MarioState.h"
class CMario;

class FallingState : public MarioState {

public:

	//FallingState() { debug_state = 3; };

	void handleOnKeyUp(CMario& mario, int keyCode);

	void handleOnKeyDown(CMario& mario, int keyCode);

	void handleKeyState(CMario& mario, BYTE* states);

	void update(CMario& mario, DWORD dt);

};

