#include "WalkingState.h"
#include <dinput.h>
#include "Utils.h"
#include "IdleState.h"
#include "JumpingState.h"

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
	switch (keyCode)
	{
	case DIK_SPACE:
		mario.marioState = new JumpingState();
	}
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

	if ((states[DIK_A] & 0x80) > 0) {
		mario.vx = 1.5 * mario.vx;
	}
};

void WalkingState::update(CMario& mario, DWORD dt) {
	mario.current_state = WALKING;
	mario.vx = MARIO_WALKING_SPEED * mario.nx;

	if (mario.nx > 0)
	{
		switch (mario.type)
		{
			case MARIO_TYPE_SMALL:
			mario.SetAni(MARIO_ANI_SMALL_WALKING_RIGHT);
			break;
			case MARIO_TYPE_BIG:
			mario.SetAni(MARIO_ANI_BIG_WALKING_RIGHT);
			break;
		}
	}
		
	else
	{
		switch (mario.type)
		{
			case MARIO_TYPE_SMALL:
			mario.SetAni(MARIO_ANI_SMALL_WALKING_LEFT);
			break;
			case MARIO_TYPE_BIG:
			mario.SetAni(MARIO_ANI_BIG_WALKING_LEFT);
			break;
		}
	}
};
