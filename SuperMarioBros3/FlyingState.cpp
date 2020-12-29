#include "FlyingState.h"
#include <dinput.h>
#include "Utils.h"
#include "FallingWhileFlyingState.h"
#include "FallingState.h"

void FlyingState::handleOnKeyUp(CMario& mario, int keyCode) {
	switch (keyCode)
	{
	case DIK_X:
		stop_flap_tail = true;
		break;
	}
};

void FlyingState::handleOnKeyDown(CMario& mario, int keyCode) {
	switch (keyCode)
	{
	case DIK_X:
		stop_flap_tail = false;
		break;
	}
};

void FlyingState::handleKeyState(CMario& mario, BYTE* states) {
	/*if ((states[DIK_RIGHT] & 0x80) > 0 || (states[DIK_LEFT] & 0x80) > 0) {
		mario.vx = FLYING_SPEED_X * mario.nx;
	}
	*/
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

void FlyingState::update(CMario& mario, DWORD dt) {

	mario.vy = stop_flap_tail ? MARIO_GRAVITY*dt : -MARIO_FLYING_SPEED_Y;

	counter_time += dt;
	if (counter_time > MAX_TIME)
	{
		mario.state = new FallingState();
	}
		
}

int FlyingState::getAni(CMario& mario) {
	int ani = -1;

	if (mario.nx > 0)
		ani = stop_flap_tail ? RACCOON_MARIO_ANI_FALLING_WHILE_FLYING_RIGHT : RACCOON_MARIO_ANI_FLYING_STATE_RIGHT;
	else
		ani = stop_flap_tail ? RACCOON_MARIO_ANI_FALLING_WHILE_FLYING_LEFT : RACCOON_MARIO_ANI_FLYING_STATE_LEFT;

	return ani;
}

