#include "IdleState.h"
#include <dinput.h>
#include "WalkingState.h"
#include "JumpingState.h"
#include "Utils.h"

void IdleState::handleOnKeyUp(CMario& mario, int keyCode) {
	
};

void IdleState::handleOnKeyDown(CMario& mario, int keyCode) {

	switch (keyCode)
	{
	case DIK_SPACE:
		mario.marioState = new JumpingState();
	}

};

void IdleState::handleKeyState(CMario& mario, BYTE* states) {

	if ((states[DIK_RIGHT] & 0x80) > 0) {
		mario.marioState = new WalkingState();
	}

	if ((states[DIK_LEFT] & 0x80) > 0) {
		mario.marioState = new WalkingState();
	}

};

void IdleState::update(CMario& mario, DWORD dt) {

	mario.vy = 0;
	mario.vx = 0;

	if (mario.nx > 0)
		mario.SetAni(MARIO_ANI_BIG_IDLE_RIGHT);
	else
		mario.SetAni(MARIO_ANI_BIG_IDLE_LEFT);

};
