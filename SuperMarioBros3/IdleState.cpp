#include "IdleState.h"
#include <dinput.h>
#include "WalkingState.h"
#include "JumpingState.h"
#include "TailSmacking_1_State.h"
#include "Throw_1_State.h"
#include "FireBall.h"
#include "Utils.h"

void IdleState::handleOnKeyUp(CMario& mario, int keyCode) {
	
};

void IdleState::handleOnKeyDown(CMario& mario, int keyCode) {

	switch (keyCode)
	{
	case DIK_SPACE:
		mario.marioState = new JumpingState();
		break;
	case DIK_D:
		if(mario.type == MARIO_TYPE_RACCOON)
			mario.marioState = new TailSmacking_1_State();
		else
			mario.marioState = new Throw_1_State();
		break;
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

	mario.vx = 0;

};

int IdleState::getAni(CMario& mario) {

	int ani = -1;

	if (mario.nx > 0)
	{
		switch (mario.type)
		{
		case MARIO_TYPE_SMALL:
			ani = MARIO_ANI_SMALL_IDLE_RIGHT;
			break;
		case MARIO_TYPE_BIG:
			ani = MARIO_ANI_BIG_IDLE_RIGHT;
			break;
		case MARIO_TYPE_RACCOON:
			ani = RACCOON_MARIO_ANI_IDLE_RIGHT;
			break;
		case MARIO_TYPE_FIRE:
			ani = FIRE_MARIO_ANI_IDLE_RIGHT;
			break;
		}
	}
		
	else
	{
		switch (mario.type)
		{
		case MARIO_TYPE_SMALL:
			ani = MARIO_ANI_SMALL_IDLE_LEFT;
			break;
		case MARIO_TYPE_BIG:
			ani = MARIO_ANI_BIG_IDLE_LEFT;
			break;
		case MARIO_TYPE_RACCOON:
			ani = RACCOON_MARIO_ANI_IDLE_LEFT;
			break;
		case MARIO_TYPE_FIRE:
			ani = FIRE_MARIO_ANI_IDLE_LEFT;
			break;
		}
	}
	
	return ani;
}