#pragma once
#include "MarioState.h"
class CMario;

#define MARIO_ANI_TAIL_SMACKING_1_RIGHT	57
#define MARIO_ANI_TAIL_SMACKING_1_LEFT	58

class TailSmacking_1_State : public MarioState {
	float counter_time = 0;
public:

	TailSmacking_1_State() { current_state = TAIL_SMACKING_1; };

	void handleOnKeyUp(CMario& mario, int keyCode);

	void handleOnKeyDown(CMario& mario, int keyCode);

	void handleKeyState(CMario& mario, BYTE* states);

	void update(CMario& mario, DWORD dt);

	int getAni(CMario& mario);
};

