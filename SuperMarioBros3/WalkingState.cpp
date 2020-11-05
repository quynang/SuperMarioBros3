#include "WalkingState.h"
#include <dinput.h>
#include "Utils.h"
#include "IdleState.h"

void WalkingState::handleOnKeyUp(CMario& mario, int keyCode) {

	switch (keyCode)
	{
	case DIK_RIGHT:
		mario.marioState = new IdleState();
	case DIK_LEFT:
		mario.marioState = new IdleState();
	}

};

void WalkingState::handleOnKeyDown(CMario& mario, int keyCode) {

};

void WalkingState::handleKeyState(CMario& mario, BYTE* states) {

	if ((states[DIK_RIGHT] & 0x80) > 0) {
		//mario.vx = MARIO_WALKING_SPEED;
		mario.nx = 1;
	}

	if ((states[DIK_LEFT] & 0x80) > 0) {
		//mario.vx = -MARIO_WALKING_SPEED;
		mario.nx = -1;
	}

};

void WalkingState::update(CMario& mario) {
	
	if (mario.nx > 0)
		mario.SetAni(MARIO_ANI_BIG_WALKING_RIGHT);
	else
		mario.SetAni(MARIO_ANI_BIG_WALKING_LEFT);

	mario.vx = MARIO_WALKING_SPEED * mario.nx;
};
