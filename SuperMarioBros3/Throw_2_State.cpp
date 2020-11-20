#include "Throw_2_State.h"
#include "IdleState.h"
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

	if (counter_time >= TIME_ANI_THROW)
		mario.marioState = new IdleState();

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