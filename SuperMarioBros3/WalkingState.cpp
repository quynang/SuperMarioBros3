#include "WalkingState.h"
#include <dinput.h>
#include "Utils.h"
#include "IdleState.h"
#include "JumpingState.h"
#include "FlyingState.h"

void WalkingState::handleOnKeyUp(CMario& mario, int keyCode) {

	switch (keyCode)
	{
	case DIK_RIGHT:
		mario.marioState = new IdleState();
	case DIK_LEFT:
		mario.marioState = new IdleState();
	case DIK_A:
		in_speed_run = 0;
		counter_time = 0;
		break;
	}

};

void WalkingState::handleOnKeyDown(CMario& mario, int keyCode) {
	switch (keyCode)
	{
	case DIK_SPACE:
		if (mario.power >= 4 && mario.type == MARIO_TYPE_RACCOON)
			mario.marioState = new FlyingState();
		else
			mario.marioState = new JumpingState();
		break;
	case DIK_A:
		in_speed_run = 1;
		break;

	}
};

void WalkingState::handleKeyState(CMario& mario, BYTE* states) {

	if ((states[DIK_RIGHT] & 0x80) > 0) {
		//mario.vx = MARIO_WALKING_SPEED;
		mario.nx = 1;
	}

	if ((states[DIK_LEFT] & 0x80) > 0) {
		//mario.vx = -MARIO_WALKING_SPEED;
		mario.nx = -1;
	}

	if ((states[DIK_A] & 0x80) > 0) {
		mario.vx = 1.5 * mario.vx;
	}

	
	if ((states[DIK_S] & 0x80) > 0) {
		mario.can_pick_item = 1;
	}
	else
	{
		mario.can_pick_item = 0;
	}
};

void WalkingState::update(CMario& mario, DWORD dt) {

	mario.vx = MARIO_WALKING_SPEED * mario.nx;
	if (in_speed_run)
		counter_time += dt;
		
	
	mario.power = (int) ((counter_time/1000) / 0.1);

};

int WalkingState::getAni(CMario& mario) {

	int ani = -1;

	if (mario.nx > 0)
	{
		switch (mario.type)
		{
			case MARIO_TYPE_SMALL:
				mario.power >= 4 ? ani = MARIO_ANI_SMALL_RUNNING_RIGHT: ani = MARIO_ANI_SMALL_WALKING_RIGHT;
				break;
			case MARIO_TYPE_BIG:
				mario.power >= 4 ? ani = MARIO_ANI_BIG_RUNNING_RIGHT : ani = MARIO_ANI_BIG_WALKING_RIGHT;
				break;
			case MARIO_TYPE_RACCOON:
				mario.power >= 4 ? ani = RACCOON_MARIO_ANI_RUNNING_RIGHT: ani = RACCOON_MARIO_ANI_WALKING_RIGHT;
				break;
			case MARIO_TYPE_FIRE:
				mario.power >= 4 ? ani = FIRE_MARIO_ANI_RUNNING_RIGHT: ani = FIRE_MARIO_ANI_WALKING_RIGHT;
				break;
		}
	}
	else
	{
		switch (mario.type)
		{
			case MARIO_TYPE_SMALL:
				mario.power >= 4 ? ani = MARIO_ANI_SMALL_RUNNING_LEFT: ani = MARIO_ANI_SMALL_WALKING_LEFT;
				break;
			case MARIO_TYPE_BIG:
				mario.power >= 4 ? ani = MARIO_ANI_BIG_RUNNING_LEFT : ani = MARIO_ANI_BIG_WALKING_LEFT;
				break;
			case MARIO_TYPE_RACCOON:
				mario.power >= 4 ? ani = RACCOON_MARIO_ANI_RUNNING_LEFT : ani = RACCOON_MARIO_ANI_WALKING_LEFT;
				break;
			case MARIO_TYPE_FIRE:
				mario.power >= 4 ? ani = FIRE_MARIO_ANI_RUNNING_LEFT : ani = FIRE_MARIO_ANI_WALKING_LEFT;
				break;
		}
	}

	return ani;

}