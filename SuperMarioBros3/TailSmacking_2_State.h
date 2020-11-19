#pragma once
#include "MarioState.h"
class CMario;

#define MARIO_ANI_TAIL_SMACKING_STAND_2_RIGHT	59
#define MARIO_ANI_TAIL_SMACKING_STAND_2_LEFT	60

#define MARIO_ANI_TAIL_SMACKING_JUMP_2_RIGHT	61
#define MARIO_ANI_TAIL_SMACKING_JUMP_2_LEFT	62


class TailSmacking_2_State : public MarioState {
	float counter_time = 0;
public:

	TailSmacking_2_State() { current_state = TAIL_SMACKING_2; };

	void handleOnKeyUp(CMario& mario, int keyCode);

	void handleOnKeyDown(CMario& mario, int keyCode);

	void handleKeyState(CMario& mario, BYTE* states);

	void update(CMario& mario, DWORD dt);

	int getAni(CMario& mario);
};

