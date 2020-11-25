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

	if (counter_time / 1000 > KICK_ACTION_TIME)
	{
		counter_time = 0;
		mario.state = new IdleState();
	}
		

};


int KickState::getAni(CMario& mario) {

	int ani = -1;

	if (mario.nx > 0)
	{
		switch (mario.type)
		{
		case MARIO_TYPE_SMALL:
			ani = MARIO_ANI_SMALL_KICK_RIGHT;
			break;
		case MARIO_TYPE_BIG:
			ani = MARIO_ANI_BIG_KICK_RIGHT;
			break;
		case MARIO_TYPE_RACCOON:
			ani = RACCOON_MARIO_ANI_KICK_RIGHT;
			break;
		case MARIO_TYPE_FIRE:
			ani = FIRE_MARIO_ANI_KICK_RIGHT;
			break;
		}
	}

	else
	{
		switch (mario.type)
		{
		case MARIO_TYPE_SMALL:
			ani = MARIO_ANI_SMALL_KICK_LEFT;
			break;
		case MARIO_TYPE_BIG:
			ani = MARIO_ANI_BIG_KICK_LEFT;
			break;
		case MARIO_TYPE_RACCOON:
			ani = RACCOON_MARIO_ANI_KICK_LEFT;
			break;
		case MARIO_TYPE_FIRE:
			ani = FIRE_MARIO_ANI_KICK_LEFT;
			break;
		}
	};

	return ani;
}
