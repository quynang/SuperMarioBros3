#include "IdleState.h"
#include <dinput.h>
#include "WalkingState.h"
#include "JumpingState.h"
#include "TailSmacking_1_State.h"
#include "Throw_1_State.h"
#include "FireBall.h"
#include "Utils.h"

void IdleState::handleOnKeyUp(CMario& mario, int keyCode) {
	switch (keyCode)
	{
	
	case DIK_A:
		mario.is_holding = false;
		mario.can_pick_item = false;
		mario.is_running = false;
		break;
	}	
};

void IdleState::handleOnKeyDown(CMario& mario, int keyCode) {

	switch (keyCode)
	{
	case DIK_S:
		mario.state = new JumpingState();
		break;
	case DIK_A:
		if (mario.type == MARIO_TYPE_RACCOON)
			mario.state = new TailSmacking_1_State();
		else if (mario.type == MARIO_TYPE_FIRE)
			mario.state = new Throw_1_State();
		break;
	}

};

void IdleState::handleKeyState(CMario& mario, BYTE* states) {

	if ((states[DIK_RIGHT] & 0x80) > 0) {
		mario.state = new WalkingState();
	}

	if ((states[DIK_LEFT] & 0x80) > 0) {
		mario.state = new WalkingState();
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
			ani = mario.is_holding ? MARIO_ANI_IDLE_SMALL_HOLDING_RIGHT : MARIO_ANI_SMALL_IDLE_RIGHT;
			break;
		case MARIO_TYPE_BIG:
			ani =  mario.is_holding ? MARIO_ANI_IDLE_BIG_HOLDING_RIGHT : MARIO_ANI_BIG_IDLE_RIGHT;
			break;
		case MARIO_TYPE_RACCOON:
			ani =  mario.is_holding ? RACCOON_MARIO_ANI_IDLE_HOLDING_RIGHT : RACCOON_MARIO_ANI_IDLE_RIGHT;
			break;
		case MARIO_TYPE_FIRE:
			ani =  mario.is_holding ? FIRE_MARIO_ANI_IDLE_HOLDING_RIGHT : FIRE_MARIO_ANI_IDLE_RIGHT;
			break;
		}
	}
		
	else
	{
		switch (mario.type)
		{
		case MARIO_TYPE_SMALL:
			ani = mario.is_holding ? MARIO_ANI_IDLE_SMALL_HOLDING_LEFT : MARIO_ANI_SMALL_IDLE_LEFT;
			break;
		case MARIO_TYPE_BIG:
			ani =  mario.is_holding ? MARIO_ANI_IDLE_BIG_HOLDING_LEFT : MARIO_ANI_BIG_IDLE_LEFT;
			break;
		case MARIO_TYPE_RACCOON:
			ani =  mario.is_holding ? RACCOON_MARIO_ANI_IDLE_HOLDING_LEFT : RACCOON_MARIO_ANI_IDLE_LEFT;
			break;
		case MARIO_TYPE_FIRE:
			ani =  mario.is_holding ? FIRE_MARIO_ANI_IDLE_HOLDING_LEFT : FIRE_MARIO_ANI_IDLE_LEFT;
			break;
		}
	}
	
	return ani;
}