#include "HoldingState.h"
#include <dinput.h>
#include "Utils.h"
#include "IdleState.h"
#include "JumpingState.h"
#include "FlyingState.h"

void HoldingState::handleOnKeyUp(CMario& mario, int keyCode) {

	switch (keyCode)
	{
	case DIK_RIGHT:
		mario.vx = 0;
		break;
	case DIK_LEFT:
		mario.vx = 0;
		break;
	case DIK_S:
		mario.can_pick_item = 0;
		break;
	}

};

void HoldingState::handleOnKeyDown(CMario& mario, int keyCode) {

};

void HoldingState::handleKeyState(CMario& mario, BYTE* states) {

	if ((states[DIK_RIGHT] & 0x80) > 0) {
		//mario.vx = MARIO_WALKING_SPEED;
		mario.nx = 1;
		mario.vx = MARIO_WALKING_SPEED;
	}

	if ((states[DIK_LEFT] & 0x80) > 0) {
		//mario.vx = -MARIO_WALKING_SPEED;
		mario.nx = -1;
		mario.vx = -MARIO_WALKING_SPEED;
	}
};

void HoldingState::update(CMario& mario, DWORD dt) {

};

int HoldingState::getAni(CMario& mario) {
	int ani = -1;

	if (mario.nx > 0)
	{
		switch (mario.type)
		{
		case MARIO_TYPE_SMALL:
			mario.vx != 0 ? ani = MARIO_ANI_SMALL_HOLDING_WALKING_RIGHT : ani = MARIO_ANI_IDLE_SMALL_HOLDING_RIGHT;
			break;
		case MARIO_TYPE_BIG:
			mario.vx != 0 ? ani = MARIO_ANI_BIG_HOLDING_WALKING_RIGHT : ani = MARIO_ANI_IDLE_BIG_HOLDING_RIGHT;
			break;
		case MARIO_TYPE_RACCOON:
			mario.vx != 0 ? ani = RACCOON_MARIO_ANI_HOLDING_WALKING_RIGHT : ani = RACCOON_MARIO_ANI_IDLE_HOLDING_RIGHT;
			break;
		}
	}
		
	else
	{
		switch (mario.type)
		{
		case MARIO_TYPE_SMALL:
			mario.vx != 0 ? ani = MARIO_ANI_SMALL_HOLDING_WALKING_LEFT : ani = MARIO_ANI_IDLE_SMALL_HOLDING_LEFT;
			break;
		case MARIO_TYPE_BIG:
			mario.vx != 0 ? ani = MARIO_ANI_BIG_HOLDING_WALKING_LEFT : ani = MARIO_ANI_IDLE_BIG_HOLDING_LEFT;
			break;
		case MARIO_TYPE_RACCOON:
			mario.vx != 0 ? ani = RACCOON_MARIO_ANI_HOLDING_WALKING_LEFT : ani = RACCOON_MARIO_ANI_IDLE_HOLDING_LEFT;
			break;
		}
	}

	return ani;
}