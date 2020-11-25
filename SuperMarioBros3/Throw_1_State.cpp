#include "Throw_1_State.h"
#include "Throw_2_State.h"
#include <dinput.h>
#include "Utils.h"

void Throw_1_State::handleOnKeyUp(CMario& mario, int keyCode) {
	
};

void Throw_1_State::handleOnKeyDown(CMario& mario, int keyCode) {


};

void Throw_1_State::handleKeyState(CMario& mario, BYTE* states) {


};

void Throw_1_State::update(CMario& mario, DWORD dt) {

	counter_time += dt;

	if (counter_time >= TIME_ANI_THROW)
		mario.state = new Throw_2_State();

};

int Throw_1_State::getAni(CMario& mario) {

	int ani = -1;

	if (mario.nx > 0)
	{
		ani = FIRE_MARIO_ANI_THROW_1_RIGHT;
	}
		
	else
	{
		ani = FIRE_MARIO_ANI_THROW_1_LEFT;
	}
	
	return ani;
}