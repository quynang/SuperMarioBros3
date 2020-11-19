#include "TailSmacking_1_State.h"
#include "TailSmacking_2_State.h"
#include <dinput.h>
#include "Utils.h"

void TailSmacking_1_State::handleOnKeyUp(CMario& mario, int keyCode) {
	
};

void TailSmacking_1_State::handleOnKeyDown(CMario& mario, int keyCode) {


};

void TailSmacking_1_State::handleKeyState(CMario& mario, BYTE* states) {


};

void TailSmacking_1_State::update(CMario& mario, DWORD dt) {

	counter_time += dt;

	if (counter_time >= TIME_ANI_SMACKING_TAIL)
		mario.marioState = new TailSmacking_2_State();

};

int TailSmacking_1_State::getAni(CMario& mario) {

	int ani = -1;

	if (mario.nx > 0)
	{
		ani = MARIO_ANI_TAIL_SMACKING_1_RIGHT;
	}
		
	else
	{
		ani = MARIO_ANI_TAIL_SMACKING_1_LEFT;
	}
	
	return ani;
}