#include "FallingState.h"
#include <dinput.h>
#include "Utils.h"

void FallingState::handleOnKeyUp(CMario& mario, int keyCode) {

};

void FallingState::handleOnKeyDown(CMario& mario, int keyCode) {

};

void FallingState::handleKeyState(CMario& mario, BYTE* states) {

};

void FallingState::update(CMario& mario, DWORD dt) {

	mario.vy += MARIO_GRAVITY*dt;

	if (mario.nx > 0)
		mario.SetAni(MARIO_ANI_BIG_FALLING_RIGHT);
	else 
		mario.SetAni(MARIO_ANI_BIG_FALLING_LEFT);
};
