#include "EnteringPipe.h"
#include "PlayScence.h"
#include "EffectFactory.h"
EnteringPipe::EnteringPipe(float x, float y, int scence_id) {
	this->x = x;
	this->y = y;
	this->zIndex = 0;
	this->scence_id = scence_id;
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	SetAnimationSet(animation_sets->Get(ENTERING_PIPE_ANI_SET_ID));
	CGame::GetInstance()->DisableKeyboard();
}

void EnteringPipe::Update(DWORD dt) {

	//TODO: This is tricky and temporary solution. Let's refactor if we can find better solution.
	
	counter_y += dt * SPEED_Y;
	if (counter_y < 32)
	{
		this->y += dt*SPEED_Y;
	}
	
	if (counter_time > 0) {
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->turnOffGameObjectUpdate();
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->setIsVisible(false);
	}
	counter_time += dt;
	if (counter_time >= 600) {
		CGame::GetInstance()->EnableKeyboard();
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->turnOnGameObjectUpdate();
		CGame::GetInstance()->SwitchScene(scence_id);
	}
};

void EnteringPipe::Render() {
	if (this->is_finished) return;
	int ani = -1;
	int mario_current_type = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->getCurrentType();
	switch (mario_current_type)
	{
	case MARIO_TYPE_SMALL:
		ani = MARIO_TYPE_SMALL_INDEX;
		break;
	case MARIO_TYPE_BIG:
		ani = MARIO_TYPE_BIG_INDEX;
		break;
	case MARIO_TYPE_RACCOON:
		ani = MARIO_TYPE_RACCOON_INDEX;
		break;
	case MARIO_TYPE_FIRE:
		ani = MARIO_TYPE_FIRE_INDEX;
		break;

	}

	animation_set->at(ani)->Render(x, y);
}
