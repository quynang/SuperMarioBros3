#include "Broken.h"
#include "PlayScence.h"
Broken::Broken(float x, float y) {
	this->x = x;
	this->y = y;
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	SetAnimationSet(animation_sets->Get(BROKEN_ANI_SET_ID));
	point_1.x = this->x;
	point_1.y = this->y;
	point_2.x = this->x + SPACING;
	point_2.y = this->y;
	point_3.x = this->x;
	point_3.y = this->y + SPACING;
	point_4.x = this->x + SPACING;
	point_4.y = this->y + SPACING;
}

void Broken::Update(DWORD dt) {

	counter_time += dt;

	if (counter_time >= MAX_TIME)
		this->is_finished = true;

	float scale_x = dt * SPEED_X;
	float scale_y = dt * SPEED_Y;
	
	point_1.x -= scale_x;
	point_1.y -= scale_y;

	point_2.x += scale_x;
	point_2.y -= scale_y;

	point_3.x -= scale_x;
	point_3.y += scale_y;

	point_4.x += scale_x;
	point_4.y += scale_y;
		
};

void Broken::Render() {
	animation_set->at(0)->Render(point_1.x, point_1.y);
	animation_set->at(0)->Render(point_2.x, point_2.y);
	animation_set->at(0)->Render(point_3.x, point_3.y);
	animation_set->at(0)->Render(point_4.x, point_4.y);
}
