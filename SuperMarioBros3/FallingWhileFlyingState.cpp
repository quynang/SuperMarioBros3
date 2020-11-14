#include "FallingWhileFlyingState.h"
#include <dinput.h>
#include "Utils.h"

void FallingWhileFlyingState::handleOnKeyUp(CMario& mario, int keyCode) {
	switch (keyCode)
	{
	case DIK_SPACE:
		flap_tails = 0;
		break;
		
	}
};

void FallingWhileFlyingState::handleOnKeyDown(CMario& mario, int keyCode) {
	switch (keyCode)
	{
	case DIK_SPACE:
		flap_tails = 1;
		break;
		
	}
};

void FallingWhileFlyingState::handleKeyState(CMario& mario, BYTE* states) {
	if ((states[DIK_RIGHT] & 0x80) > 0) {
		mario.nx = 1;
		mario.vx = FLYING_SPEED_X * mario.nx;
	}

	else if ((states[DIK_LEFT] & 0x80) > 0) {
		mario.nx = -1;
		mario.vx = FLYING_SPEED_X * mario.nx;
	}
	else {
		mario.vx = 0;
	}
};

void FallingWhileFlyingState::update(CMario& mario, DWORD dt) {

	mario.vy = MARIO_GRAVITY*dt;

	if (flap_tails)
		mario.vy = MARIO_SLOW_GRAVITY * dt;
};

int FallingWhileFlyingState::getAni(CMario& mario) {

	int ani = -1;
		
	if (mario.nx > 0)
	{
		flap_tails ? ani = RACCOON_MARIO_ANI_FLYING_STATE_RIGHT : ani = RACCOON_MARIO_ANI_FALLING_WHILE_FLYING_RIGHT;
	}
	else
	{
		flap_tails ? ani = RACCOON_MARIO_ANI_FLYING_STATE_LEFT : ani = RACCOON_MARIO_ANI_FALLING_WHILE_FLYING_LEFT;
	}

	return ani;
}