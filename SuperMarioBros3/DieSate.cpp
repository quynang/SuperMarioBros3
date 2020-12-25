#include "DieState.h"
#include <dinput.h>
#include "Utils.h"
#include "Game.h"
#define OVER_WORLD_MAP_SCENE_ID	2
void DieState::handleOnKeyUp(CMario& mario, int keyCode) {

};

void DieState::handleOnKeyDown(CMario& mario, int keyCode) {

};

void DieState::handleKeyState(CMario& mario, BYTE* states) {


};

void DieState::update(CMario& mario, DWORD dt) {

	mario.vx = 0;
	mario.vy = -0.3f;
	counter_time += dt;
	if (counter_time > 120)
		mario.vy = 0.3f;
};

int DieState::getAni(CMario& mario) {

	return MARIO_ANI_DIE;
}