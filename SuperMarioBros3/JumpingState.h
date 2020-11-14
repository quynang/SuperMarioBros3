#pragma once
#include "MarioState.h"

#define MAX_CHARGE 60

#define MARIO_ANI_BIG_JUMPING_LEFT	9
#define MARIO_ANI_BIG_JUMPING_RIGHT	10

#define MARIO_ANI_SMALL_JUMPING_LEFT	13
#define MARIO_ANI_SMALL_JUMPING_RIGHT	14

#define RACCOON_MARIO_ANI_JUMPING_RIGHT	31
#define RACCOON_MARIO_ANI_JUMPING_LEFT	32

class JumpingState : public MarioState {

public:

	JumpingState() : chargeY_(0) { current_state = JUMPING; };

	void handleOnKeyUp(CMario& mario, int keyCode);

	void handleOnKeyDown(CMario& mario, int keyCode);

	void handleKeyState(CMario& mario, BYTE* states);

	void update(CMario& mari, DWORD dt);

	int getAni(CMario& mario);

private:
	float chargeY_;
};