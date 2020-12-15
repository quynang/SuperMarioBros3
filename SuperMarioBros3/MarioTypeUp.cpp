#include "MarioTypeUp.h"
#include "PlayScence.h"
MarioTypeUp::MarioTypeUp(float x, float y, int nx) {
	this->x = x;
	this->y = y;
	this->nx = nx;
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	SetAnimationSet(animation_sets->Get(MARIO_TYPE_UP_ANI_SET_ID));
}

void MarioTypeUp::Update(DWORD dt) {

	//TODO: This is tricky and temporary solution. Let's refactor if we can find better solution.
	if (counter_time > 0) {
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->turnOffGameObjectUpdate();
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->setIsVisible(false);
	}
	counter_time += dt;
	if (counter_time >= 600) {
		this->is_finished = true;
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->turnOnGameObjectUpdate();
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->setIsVisible(true);
	}
};

void MarioTypeUp::Render() {
	int ani = -1;
	if (nx == -1)
		ani = MARIO_TYPE_UP_ANI_LEFT_INDEX;
	else
		ani = MARIO_TYPE_UP_ANI_RIGHT_INDEX;

	animation_set->at(ani)->Render(x, y);
}