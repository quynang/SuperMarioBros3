#pragma once
#include "MarioState.h"
class CMario;

#define MARIO_ANI_TAIL_SMACKING_3_RIGHT	63
#define MARIO_ANI_TAIL_SMACKING_3_LEFT	64

class TailSmacking_3_State : public MarioState {
	float counter_time = 0;
public:

	TailSmacking_3_State() { current_state = TAIL_SMACKING_3; };

	void handleOnKeyUp(CMario& mario, int keyCode);

	void handleOnKeyDown(CMario& mario, int keyCode);

	void handleKeyState(CMario& mario, BYTE* states);

	void update(CMario& mario, DWORD dt);

	int getAni(CMario& mario);
};

