#pragma once
#include "MarioState.h"
class CMario;
#define MARIO_ANI_BIG_IDLE_RIGHT		0
#define MARIO_ANI_BIG_IDLE_LEFT			1
#define MARIO_ANI_SMALL_IDLE_RIGHT		2
#define MARIO_ANI_SMALL_IDLE_LEFT			3
#define RACCOON_MARIO_ANI_IDLE_RIGHT	25
#define RACCOON_MARIO_ANI_IDLE_LEFT	26

class IdleState : public MarioState {

public:

	IdleState() { current_state = IDLE; };
	void handleOnKeyUp(CMario& mario, int keyCode);

	void handleOnKeyDown(CMario& mario, int keyCode);

	void handleKeyState(CMario& mario, BYTE* states);

	void update(CMario& mario, DWORD dt);

};

