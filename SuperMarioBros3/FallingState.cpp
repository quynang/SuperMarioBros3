#include "FallingState.h"
#include <dinput.h>
#include "Utils.h"

void FallingState::handleOnKeyUp(CMario& mario, int keyCode) {
	switch (keyCode)
	{
	case DIK_X:
		slow_falling = false;
		break;
		
	}
};

void FallingState::handleOnKeyDown(CMario& mario, int keyCode) {
	switch (keyCode)
	{
	case DIK_X:
		slow_falling = true;
		break;
		
	}
};

void FallingState::handleKeyState(CMario& mario, BYTE* states) {
	if ((states[DIK_X] & 0x80) > 0) {
		slow_falling = true;
	}
};

void FallingState::update(CMario& mario, DWORD dt) {
	if (slow_falling && mario.type == MARIO_TYPE_RACCOON)
		mario.vy = MARIO_GRAVITY*dt;
	else 
		mario.vy += MARIO_GRAVITY*dt;

};

int FallingState::getAni(CMario& mario) {
	int ani = -1;
	if (mario.is_holding) {
		if (mario.nx > 0)
		{
			switch (mario.type)
			{
			case MARIO_TYPE_SMALL:
				ani = SMALL_MARIO_ANI_FALLING_AND_JUMPING_WHEN_HOLDING_RIGHT;
				break;
			case MARIO_TYPE_BIG:
				ani = BIG_MARIO_ANI_FALLING_AND_JUMPING_WHEN_HOLDING_RIGHT;
				break;
			case MARIO_TYPE_RACCOON:
				ani = RACCOON_MARIO_ANI_FALLING_AND_JUMPING_WHEN_HOLDING_RIGHT;
				break;
			case MARIO_TYPE_FIRE:
				ani = FIRE_MARIO_ANI_FALLING_AND_JUMPING_WHEN_HOLDING_RIGHT;
				break;
			}
		}

		else
		{
			switch (mario.type)
			{
			case MARIO_TYPE_SMALL:
				ani = SMALL_MARIO_ANI_FALLING_AND_JUMPING_WHEN_HOLDING_LEFT;
				break;
			case MARIO_TYPE_BIG:
				ani = BIG_MARIO_ANI_FALLING_AND_JUMPING_WHEN_HOLDING_LEFT;
				break;
			case MARIO_TYPE_RACCOON:
				ani = RACCOON_MARIO_ANI_FALLING_AND_JUMPING_WHEN_HOLDING_LEFT;
				break;
			case MARIO_TYPE_FIRE:
				ani = FIRE_MARIO_ANI_FALLING_AND_JUMPING_WHEN_HOLDING_LEFT;
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
				ani = MARIO_ANI_SMALL_FALLING_RIGHT;
				break;
			case MARIO_TYPE_BIG:
				ani = MARIO_ANI_BIG_FALLING_RIGHT;
				break;
			case MARIO_TYPE_RACCOON:
				ani = slow_falling ? SLOW_FALLING_ANI_RIGHT : RACCOON_MARIO_ANI_FALLING_RIGHT;
				break;
			case MARIO_TYPE_FIRE:
				ani = FIRE_MARIO_ANI_FALLING_RIGHT;
				break;
			}
		}

		else
		{
			switch (mario.type)
			{
			case MARIO_TYPE_SMALL:
				ani = MARIO_ANI_SMALL_FALLING_LEFT;
				break;
			case MARIO_TYPE_BIG:
				ani = MARIO_ANI_BIG_FALLING_LEFT;
				break;
			case MARIO_TYPE_RACCOON:
				ani = slow_falling ? SLOW_FALLING_ANI_LEFT : RACCOON_MARIO_ANI_FALLING_LEFT;
				break;
			case MARIO_TYPE_FIRE:
				ani = FIRE_MARIO_ANI_FALLING_LEFT;
				break;
			}
		}
	}

	return ani;
}
