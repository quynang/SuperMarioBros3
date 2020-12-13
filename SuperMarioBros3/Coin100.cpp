#include "Coin100.h"

Coin100::Coin100() {
	this->x = x;
	this->y = y;
	SetStep(BOUNCING_STEP);
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	SetAnimationSet(animation_sets->Get(COIN_100_ANI_SET_ID));
}

void Coin100::Update(DWORD dt) {
	if (step == FALL_DOWN_STEP) vy += COIN_GRAVITY;

	dy = vy * dt;
	charge_Y += abs(dy);
	
	if (charge_Y >= MAX_Y && step == BOUNCING_STEP) SetStep(FALL_DOWN_STEP);
	if (charge_Y >= MAX_Y && step == FALL_DOWN_STEP) this->is_finished = true;

	y += dy;

	
};

void Coin100::Render() {
	animation_set->at(0)->Render(x, y);
}

void Coin100::SetStep(int step) {
	this->step = step;
	switch (step)
	{
	case BOUNCING_STEP:
		vy = -0.3f;
		break;
	case FALL_DOWN_STEP:
		this->charge_Y = 0;
		vy = 0;
		break;
	}
}