#include "KickState.h"
#include <dinput.h>
#include "IdleState.h"
#include "Utils.h"

void KickState::handleOnKeyUp(CMario& mario, int keyCode) {
	
};

void KickState::handleOnKeyDown(CMario& mario, int keyCode) {

};

void KickState::handleKeyState(CMario& mario, BYTE* states) {

};

void KickState::update(CMario& mario, DWORD dt) {

	mario.vx = 0;
	counter_time += dt;

	if (mario.nx > 0)
	{
		switch (mario.type)
		{
			case MARIO_TYPE_SMALL:
				mario.SetAni(MARIO_ANI_SMALL_KICK_RIGHT);
				break;
			case MARIO_TYPE_BIG:
				mario.SetAni(MARIO_ANI_BIG_KICK_RIGHT);
				break;
			case MARIO_TYPE_RACCOON:
				mario.SetAni(RACCOON_MARIO_ANI_KICK_RIGHT);
				break;
		}
	}
		
	else
	{
		switch (mario.type)
		{
			case MARIO_TYPE_SMALL:
				mario.SetAni(MARIO_ANI_SMALL_KICK_LEFT);
				break;
			case MARIO_TYPE_BIG:
				mario.SetAni(MARIO_ANI_BIG_KICK_LEFT);
				break;
			case MARIO_TYPE_RACCOON:
				mario.SetAni(RACCOON_MARIO_ANI_KICK_LEFT);
				break;
		}
	}

	if (counter_time / 1000 > 0.07)
	{
		counter_time = 0;
		mario.marioState = new IdleState();
	}
		

};
