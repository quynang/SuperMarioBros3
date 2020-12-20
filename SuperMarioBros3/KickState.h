#pragma once
#include "MarioState.h"
#include "Utils.h"
class CMario;

#define KICK_ACTION_TIME 0.07f

class KickState : public MarioState {

public:

	KickState() { current_state = KICK; };

	float counter_time = 0;

	void handleOnKeyUp(CMario& mario, int keyCode);

	void handleOnKeyDown(CMario& mario, int keyCode);

	void handleKeyState(CMario& mario, BYTE* states);

	void update(CMario& mario, DWORD dt);

	int getAni(CMario& mario);

};

