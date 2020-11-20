#pragma once
#include "MarioState.h"
class CMario;

#define FIRE_MARIO_ANI_THROW_2_RIGHT	83
#define FIRE_MARIO_ANI_THROW_2_LEFT	84

class Throw_2_State : public MarioState {
	float counter_time = 0;
	int is_threw_item = 0;
public:

	Throw_2_State() { current_state = THROW_2; };

	void handleOnKeyUp(CMario& mario, int keyCode);

	void handleOnKeyDown(CMario& mario, int keyCode);

	void handleKeyState(CMario& mario, BYTE* states);

	void update(CMario& mario, DWORD dt);

	int getAni(CMario& mario);
};

