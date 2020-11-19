#include "TailSmacking_3_State.h"
#include "IdleState.h"
#include <dinput.h>
#include "Utils.h"

void TailSmacking_3_State::handleOnKeyUp(CMario& mario, int keyCode) {
	
};

void TailSmacking_3_State::handleOnKeyDown(CMario& mario, int keyCode) {


};

void TailSmacking_3_State::handleKeyState(CMario& mario, BYTE* states) {


};

void TailSmacking_3_State::update(CMario& mario, DWORD dt) {

	counter_time += dt;

	if (counter_time >= TIME_ANI_SMACKING_TAIL)
		mario.marioState = new IdleState();

};

int TailSmacking_3_State::getAni(CMario& mario) {

	int ani = -1;

	if (mario.nx > 0)
	{
		ani = MARIO_ANI_TAIL_SMACKING_3_RIGHT;
	}
		
	else
	{
		ani = MARIO_ANI_TAIL_SMACKING_3_LEFT;
	}
	
	return ani;
}