#include "IdleState.h"
#include <dinput.h>
#include "WalkingState.h"

void IdleState::handleOnKeyUp(CMario& mario, int keyCode) {

};

void IdleState::handleOnKeyDown(CMario& mario, int keyCode) {

};

void IdleState::handleKeyState(CMario& mario, BYTE* states) {

	if ((states[DIK_RIGHT] & 0x80) > 0) {
		mario.marioState = new WalkingState();
	}
	if ((states[DIK_LEFT] & 0x80) > 0) {
		mario.marioState = new WalkingState();
	}

};

void IdleState::update(CMario& mario) {

	if (mario.nx > 0)
		mario.SetAni(MARIO_ANI_BIG_IDLE_RIGHT);
	else
		mario.SetAni(MARIO_ANI_BIG_IDLE_LEFT);

	mario.vx = 0;

};
