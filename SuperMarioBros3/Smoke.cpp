#include "Smoke.h"
#include "PlayScence.h"
Smoke::Smoke(float x, float y) {
	this->x = x;
	this->y = y;
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	SetAnimationSet(animation_sets->Get(SMOKE_ANI_SET_ID));
}

void Smoke::Update(DWORD dt) {

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

void Smoke::Render() {

	animation_set->at(0)->Render(x, y);
}
