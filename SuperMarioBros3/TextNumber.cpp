#include "TextNumber.h"

TextNumber::TextNumber(float x, float y, int num_val) {
	this->x = x;
	this->y = y;
	this->number = num_val;
	SetStep(BOUNCING_STEP);
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	SetAnimationSet(animation_sets->Get(TEXT_NUMBER_ANI_SET_ID));
}

void TextNumber::Update(DWORD dt) {
	dy = vy * dt;
	y += dy;
	charge_Y += abs(dy);

	if (charge_Y >= MAX_Y) this->is_finished = true;
};

void TextNumber::Render() {
	int ani = -1;
	switch (number)
	{
	case 100: 
		ani = ANI_NUMBER_100;
		break;
	case 200:
		ani = ANI_NUMBER_200;
		break;
	case 400:
		ani = ANI_NUMBER_400;
		break;
	case 800:
		ani = ANI_NUMBER_800;
		break;
	case 1000:
		ani = ANI_NUMBER_1000;
		break;
	case 1:
		ani = ANI_1_UP;
		break;
	}

	animation_set->at(ani)->Render(x, y);
}

void TextNumber::SetStep(int step) {
	this->step = step;
	switch (step)
	{
	case BOUNCING_STEP:
		vy = TEXT_NUMBER_SPEED_UP;
		break;
	}
}