#include "Throw_2_State.h"
#include "IdleState.h"
#include "FireBall.h"
#include <dinput.h>
#include "Utils.h"

void Throw_2_State::handleOnKeyUp(CMario& mario, int keyCode) {
	
};

void Throw_2_State::handleOnKeyDown(CMario& mario, int keyCode) {


};

void Throw_2_State::handleKeyState(CMario& mario, BYTE* states) {


};

void Throw_2_State::update(CMario& mario, DWORD dt) {

	counter_time += dt;

	if (!is_threw_item) {
		float x, y;
		mario.getPositionOfHandWhenThrowing(x, y);

		FireBall* fireBall = new FireBall(mario.nx > 0 ? x : x - FIRE_BALL_BBOX_WIDTH, y, mario.nx);
		is_threw_item = 1;
	}

	if (counter_time >= TIME_ANI_THROW)
		mario.state = new IdleState();

};

int Throw_2_State::getAni(CMario& mario) {

	int ani = -1;

	if (mario.nx > 0)
	{
		ani = FIRE_MARIO_ANI_THROW_2_RIGHT;
	}
		
	else
	{
		ani = FIRE_MARIO_ANI_THROW_2_LEFT;
	}
	
	return ani;
}