#include "JumpingState.h"
#include "FallingState.h"
#include "TailSmacking_1_State.h"
#include <dinput.h>
#include "IdleState.h"
#include "Utils.h"

void JumpingState::handleOnKeyDown(CMario& mario, int keyCode) {
	switch (keyCode)
	{
	case DIK_D:
		mario.marioState = new TailSmacking_1_State();
		break;
	};
}
	

void JumpingState::handleOnKeyUp(CMario& mario, int keyCode) {

};

void JumpingState::handleKeyState(CMario& mario, BYTE* states) {
	if ((states[DIK_RIGHT] & 0x80) > 0 || (states[DIK_LEFT] & 0x80) > 0) {
		mario.vx = MARIO_WALKING_SPEED*mario.nx;
	}
};

void JumpingState::update(CMario& mario, DWORD dt) {
	
	/*
		ChargeY_ là khoảng đường nhảy được trước đó tính tới thời điểm hàm update này được goị
	*/

	mario.vy = -MARIO_JUMP_SPEED_Y;

	//Điều chỉnh lại dy để đảm bảo rằng mario sẽ nhảy chính xác một khoảng bằng MAX_CHARGE.
	if (abs(mario.dy) + chargeY_ >= MAX_CHARGE) {
		mario.dy = -(MAX_CHARGE - chargeY_); //Giá trị âm bởi vì lúc này mario vẫn đang nhảy lên.
		mario.vy = 0;
		mario.marioState = new FallingState();
	}
	
	chargeY_ += abs(mario.dy);
	
};

int JumpingState::getAni(CMario& mario) {

	int ani = -1;

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

	return ani;
}