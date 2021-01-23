#include "WalkingState.h"
#include <dinput.h>
#include "Utils.h"
#include "IdleState.h"
#include "JumpingState.h"
#include "FlyingState.h"
#include "FallingState.h"

void WalkingState::handleOnKeyUp(CMario& mario, int keyCode) {

	switch (keyCode)
	{
	case DIK_RIGHT:
		mario.state = new IdleState();
	case DIK_LEFT:
		mario.state = new IdleState();
	case DIK_A:
		mario.is_running = false;
		break;
	}

};

void WalkingState::handleOnKeyDown(CMario& mario, int keyCode) {
	switch (keyCode)
	{
	case DIK_X:
		if (mario.power == 7 && mario.type == MARIO_TYPE_RACCOON)
			mario.state = new FlyingState();
		break;
	case DIK_A:
		mario.is_running = true;
		break;
	case DIK_S:
		mario.state = new JumpingState();
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
		mario.is_running = true;
	}
	else
	{
		mario.is_running = false;
	}

	
	if ((states[DIK_A] & 0x80) > 0) {
		mario.can_pick_item = 1;
	}
	else
	{
		mario.can_pick_item = 0;
	}
};

void WalkingState::update(CMario& mario, DWORD dt) {

	mario.vx = MARIO_WALKING_SPEED * mario.nx;
	mario.vy += MARIO_GRAVITY;
	if (mario.is_running)
	{
		mario.vx = 1.5* MARIO_WALKING_SPEED * mario.nx;
		//counter_time += dt;
	}
		
		
	
	//mario.power = (int) ((counter_time/1000) / 0.1);

};

int WalkingState::getAni(CMario& mario) {

	int ani = -1;
	if (mario.is_holding)
	{
		if (mario.nx > 0)
		{
			switch (mario.type)
			{
				case MARIO_TYPE_SMALL:
					ani = MARIO_ANI_SMALL_HOLDING_WALKING_RIGHT;
					break;
				case MARIO_TYPE_BIG:
					ani = MARIO_ANI_BIG_HOLDING_WALKING_RIGHT;
					break;
				case MARIO_TYPE_RACCOON:
					ani = RACCOON_MARIO_ANI_HOLDING_WALKING_RIGHT;
					break;
				case MARIO_TYPE_FIRE:
					ani = FIRE_MARIO_ANI_HOLDING_WALKING_RIGHT;
					break;
			}
		}
		else
		{
			switch (mario.type)
			{
				case MARIO_TYPE_SMALL:
					ani = MARIO_ANI_SMALL_HOLDING_WALKING_LEFT;
					break;
				case MARIO_TYPE_BIG:
					ani = MARIO_ANI_BIG_HOLDING_WALKING_LEFT;
					break;
				case MARIO_TYPE_RACCOON:
					ani = RACCOON_MARIO_ANI_HOLDING_WALKING_LEFT;
					break;
				case MARIO_TYPE_FIRE:
					ani = FIRE_MARIO_ANI_HOLDING_WALKING_LEFT;
					break;
			}
		}

	}
	else
	{
		if (mario.nx > 0)
		{
			switch (mario.type)
			{
			case MARIO_TYPE_SMALL:
				mario.power == 7 ? ani = MARIO_ANI_SMALL_RUNNING_RIGHT : ani = MARIO_ANI_SMALL_WALKING_RIGHT;
				break;
			case MARIO_TYPE_BIG:
				mario.power == 7 ? ani = MARIO_ANI_BIG_RUNNING_RIGHT : ani = MARIO_ANI_BIG_WALKING_RIGHT;
				break;
			case MARIO_TYPE_RACCOON:
				mario.power == 7 ? ani = RACCOON_MARIO_ANI_RUNNING_RIGHT : ani = RACCOON_MARIO_ANI_WALKING_RIGHT;
				break;
			case MARIO_TYPE_FIRE:
				mario.power == 7 ? ani = FIRE_MARIO_ANI_RUNNING_RIGHT : ani = FIRE_MARIO_ANI_WALKING_RIGHT;
				break;
			}
		}
		else
		{
			switch (mario.type)
			{
			case MARIO_TYPE_SMALL:
				mario.power == 7 ? ani = MARIO_ANI_SMALL_RUNNING_LEFT : ani = MARIO_ANI_SMALL_WALKING_LEFT;
				break;
			case MARIO_TYPE_BIG:
				mario.power == 7 ? ani = MARIO_ANI_BIG_RUNNING_LEFT : ani = MARIO_ANI_BIG_WALKING_LEFT;
				break;
			case MARIO_TYPE_RACCOON:
				mario.power == 7 ? ani = RACCOON_MARIO_ANI_RUNNING_LEFT : ani = RACCOON_MARIO_ANI_WALKING_LEFT;
				break;
			case MARIO_TYPE_FIRE:
				mario.power == 7 ? ani = FIRE_MARIO_ANI_RUNNING_LEFT : ani = FIRE_MARIO_ANI_WALKING_LEFT;
				break;
			}
		}
	}

	return ani;

}