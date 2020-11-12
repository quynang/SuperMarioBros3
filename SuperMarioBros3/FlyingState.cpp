#include "FlyingState.h"
#include <dinput.h>
#include "Utils.h"
#include "FallingWhileFlyingState.h"

void FlyingState::handleOnKeyUp(CMario& mario, int keyCode) {

};

void FlyingState::handleOnKeyDown(CMario& mario, int keyCode) {

};

void FlyingState::handleKeyState(CMario& mario, BYTE* states) {
	if ((states[DIK_RIGHT] & 0x80) > 0 || (states[DIK_LEFT] & 0x80) > 0) {
		mario.vx = FLYING_SPEED_X*mario.nx;
	}
	else {
		mario.vx = 0;
	}
};

void FlyingState::update(CMario& mario, DWORD dt) {

	mario.vy = -MARIO_FLYING_SPEED_Y;

	counter_time += dt;
	if (counter_time / 1000 > MAX_TIME)
		mario.marioState = new FallingWhileFlyingState();

	if (mario.nx > 0)
		mario.SetAni(RACCOON_MARIO_ANI_FLYING_STATE_RIGHT);
	else
		mario.SetAni(RACCOON_MARIO_ANI_FLYING_STATE_LEFT);
}	

