#pragma once
#include "MarioState.h"
class CMario;

#define RACCOON_MARIO_ANI_FALLING_WHILE_FLYING_RIGHT		37
#define RACCOON_MARIO_ANI_FALLING_WHILE_FLYING_LEFT			38
#define RACCOON_MARIO_ANI_FLYING_STATE_RIGHT	33
#define RACCOON_MARIO_ANI_FLYING_STATE_LEFT	34
#define MARIO_SLOW_GRAVITY	0.005f

class FallingWhileFlyingState : public MarioState {
	int flap_tails = 0;
public:

	FallingWhileFlyingState() { debug_state = 5; };

	void handleOnKeyUp(CMario& mario, int keyCode);

	void handleOnKeyDown(CMario& mario, int keyCode);

	void handleKeyState(CMario& mario, BYTE* states);

	void update(CMario& mario, DWORD dt);

};

