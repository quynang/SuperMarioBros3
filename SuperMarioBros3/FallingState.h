#pragma once
#include "MarioState.h"
class CMario;

#define MARIO_ANI_BIG_FALLING_RIGHT		11
#define MARIO_ANI_BIG_FALLING_LEFT			12

#define MARIO_ANI_SMALL_FALLING_RIGHT	16
#define MARIO_ANI_SMALL_FALLING_LEFT	15

#define RACCOON_MARIO_ANI_FALLING_RIGHT	35
#define RACCOON_MARIO_ANI_FALLING_LEFT	36

class FallingState : public MarioState {

public:

	FallingState() { current_state = FALLING; };

	void handleOnKeyUp(CMario& mario, int keyCode);

	void handleOnKeyDown(CMario& mario, int keyCode);

	void handleKeyState(CMario& mario, BYTE* states);

	void update(CMario& mario, DWORD dt);

	int getAni(CMario& mario);
};

