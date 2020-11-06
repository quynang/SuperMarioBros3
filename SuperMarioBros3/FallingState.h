#pragma once
#include "MarioState.h"
class CMario;

#define MARIO_ANI_BIG_FALLING_RIGHT		11
#define MARIO_ANI_BIG_FALLING_LEFT			12

#define MARIO_ANI_SMALL_FALLING_RIGHT	16
#define MARIO_ANI_SMALL_FALLING_LEFT	15

class FallingState : public MarioState {

public:

	//FallingState() { debug_state = 3; };

	void handleOnKeyUp(CMario& mario, int keyCode);

	void handleOnKeyDown(CMario& mario, int keyCode);

	void handleKeyState(CMario& mario, BYTE* states);

	void update(CMario& mario, DWORD dt);

};

