#pragma once
#include "MarioState.h"
class CMario;

#define FIRE_MARIO_ANI_THROW_1_RIGHT	81
#define FIRE_MARIO_ANI_THROW_1_LEFT	82

class Throw_1_State : public MarioState {
	float counter_time = 0;
public:

	Throw_1_State() { current_state = THROW_1; };

	void handleOnKeyUp(CMario& mario, int keyCode);

	void handleOnKeyDown(CMario& mario, int keyCode);

	void handleKeyState(CMario& mario, BYTE* states);

	void update(CMario& mario, DWORD dt);

	int getAni(CMario& mario);
};

