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
	{
		switch (mario.type)
		{
			case MARIO_TYPE_SMALL:
				mario.SetAni(MARIO_ANI_SMALL_FALLING_RIGHT);
				break;
			case MARIO_TYPE_BIG:
				mario.SetAni(MARIO_ANI_BIG_FALLING_RIGHT);
				break;
			case MARIO_TYPE_RACCOON:
				mario.SetAni(RACCOON_MARIO_ANI_FALLING_RIGHT);
				break;
		}
	}
		
	else
	{
		switch (mario.type)
		{
			case MARIO_TYPE_SMALL:
				mario.SetAni(MARIO_ANI_SMALL_FALLING_LEFT);
				break;
			case MARIO_TYPE_BIG:
				mario.SetAni(MARIO_ANI_BIG_FALLING_LEFT);
				break;
			case MARIO_TYPE_RACCOON:
				mario.SetAni(RACCOON_MARIO_ANI_FALLING_LEFT);
				break;
		}
	}
};
