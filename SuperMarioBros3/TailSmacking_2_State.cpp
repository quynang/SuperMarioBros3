#include "TailSmacking_2_State.h"
#include "TailSmacking_3_State.h"
#include <dinput.h>
#include "Utils.h"

void TailSmacking_2_State::handleOnKeyUp(CMario& mario, int keyCode) {
	
};

void TailSmacking_2_State::handleOnKeyDown(CMario& mario, int keyCode) {


};

void TailSmacking_2_State::handleKeyState(CMario& mario, BYTE* states) {


};

void TailSmacking_2_State::update(CMario& mario, DWORD dt) {

	counter_time += dt;

	if (counter_time >= TIME_ANI_SMACKING_TAIL)
		mario.state = new TailSmacking_3_State();

};

int TailSmacking_2_State::getAni(CMario& mario) {
	int ani = -1;

	if (mario.nx > 0)
	{
		mario.state->current_state == JUMPING ? ani = MARIO_ANI_TAIL_SMACKING_JUMP_2_RIGHT : ani = MARIO_ANI_TAIL_SMACKING_STAND_2_RIGHT;
	}
		
	else
	{
		mario.state->current_state == JUMPING ? ani = MARIO_ANI_TAIL_SMACKING_JUMP_2_LEFT : ani = MARIO_ANI_TAIL_SMACKING_STAND_2_LEFT;
	}
	
	return ani;
}