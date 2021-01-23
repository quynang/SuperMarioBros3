#include "JumpingState.h"
#include "FallingState.h"
#include "TailSmacking_1_State.h"
#include "Throw_1_State.h"
#include <dinput.h>
#include "IdleState.h"
#include "Utils.h"

void JumpingState::handleOnKeyDown(CMario& mario, int keyCode) {
	switch (keyCode)
	{
	case DIK_A:
		if (mario.type == MARIO_TYPE_RACCOON)
			mario.state = new TailSmacking_1_State();
		else if(mario.type == MARIO_TYPE_FIRE)
			mario.state = new Throw_1_State();
		break;
	};
}
	

void JumpingState::handleOnKeyUp(CMario& mario, int keyCode) {

};

void JumpingState::handleKeyState(CMario& mario, BYTE* states) {
	if ((states[DIK_RIGHT] & 0x80) > 0) {
		mario.nx = 1;
		mario.vx = MARIO_WALKING_SPEED*mario.nx;
	}
	if ((states[DIK_LEFT] & 0x80) > 0) {
		mario.nx = -1;
		mario.vx = MARIO_WALKING_SPEED*mario.nx;
	}

	if ((states[DIK_S] & 0x80) > 0) {
		if(chargeY_ > 20)
			setJumpHeight(JUMP_HEIGHT_MAX);
	}
};

void JumpingState::setJumpHeight(float height) {
	this->jump_height = height;
}

void JumpingState::update(CMario& mario, DWORD dt) {
	
	/*
		ChargeY_ là khoảng đường nhảy được trước đó tính tới thời điểm hàm update này được goị
	*/
	mario.vy = -MARIO_JUMP_SPEED_Y;

	//Điều chỉnh lại dy để đảm bảo rằng mario sẽ nhảy chính xác một khoảng bằng MAX_CHARGE.
	if (abs(mario.dy) + chargeY_ >= jump_height) {
		mario.dy = -(jump_height - chargeY_); //Giá trị âm bởi vì lúc này mario vẫn đang nhảy lên.
		mario.vy = 0;
		mario.state = new FallingState();
	}
	
	chargeY_ += abs(mario.dy);
	
};

int JumpingState::getAni(CMario& mario) {

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
				ani = MARIO_ANI_SMALL_JUMPING_RIGHT;
				break;
			case MARIO_TYPE_BIG:
				ani = MARIO_ANI_BIG_JUMPING_RIGHT;
				break;
			case MARIO_TYPE_RACCOON:
				ani = RACCOON_MARIO_ANI_JUMPING_RIGHT;
				break;
			case MARIO_TYPE_FIRE:
				ani = FIRE_MARIO_ANI_JUMPING_RIGHT;
				break;
			}
		}

		else
		{
			switch (mario.type)
			{
			case MARIO_TYPE_SMALL:
				ani = MARIO_ANI_SMALL_JUMPING_LEFT;
				break;
			case MARIO_TYPE_BIG:
				ani = MARIO_ANI_BIG_JUMPING_LEFT;
				break;
			case MARIO_TYPE_RACCOON:
				ani = RACCOON_MARIO_ANI_JUMPING_LEFT;
				break;
			case MARIO_TYPE_FIRE:
				ani = FIRE_MARIO_ANI_JUMPING_LEFT;
				break;
			}
		}
	}

	return ani;
}