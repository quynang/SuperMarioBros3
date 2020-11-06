#include "JumpingState.h"
#include "FallingState.h"
#include <dinput.h>
#include "IdleState.h"
#include "Utils.h"

void JumpingState::handleOnKeyDown(CMario& mario, int keyCode) {

};

void JumpingState::handleOnKeyUp(CMario& mario, int keyCode) {

};

void JumpingState::handleKeyState(CMario& mario, BYTE* states) {

};

void JumpingState::update(CMario& mario, DWORD dt) {
	
	/*
		ChargeY_ là khoảng đường nhảy được trước đó tính tới thời điểm hàm update này được goị
	*/
	if (mario.current_state == WALKING)
		mario.vx = MARIO_WALKING_SPEED*mario.nx;

	mario.current_state = JUMPING;
	mario.vy = -MARIO_JUMP_SPEED_Y;

	if (mario.nx > 0)
		mario.SetAni(MARIO_ANI_BIG_JUMPING_RIGHT);
	else
		mario.SetAni(MARIO_ANI_BIG_JUMPING_LEFT);

	//Điều chỉnh lại dy để đảm bảo rằng mario sẽ nhảy chính xác một khoảng bằng MAX_CHARGE.
	if (abs(mario.dy) + chargeY_ >= MAX_CHARGE) {
		mario.dy = -(MAX_CHARGE - chargeY_); //Giá trị âm bởi vì lúc này mario vẫn đang nhảy lên.
		mario.vy = 0;
		mario.marioState = new FallingState();
	}
	
	chargeY_ += abs(mario.dy);

	
};