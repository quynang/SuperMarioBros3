#include "PlantFireBullet.h"
#include "PlayScence.h"
#include <math.h>

PlantFireBullet::PlantFireBullet() {

}

PlantFireBullet::PlantFireBullet(float x, float y, int nx) {
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	SetAnimationSet(animation_sets->Get(ANI_SET_ID_FIRE_BULLET));
	this->x = x;
	this->y = y;
	this->nx = nx;
	this->vx = SPEED_X_FIRE_BULLET*nx;
	this->vy = calculateSpeedY();
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(this);
}

void PlantFireBullet::Update(DWORD dt) {
	MovableObject::Update(dt);
	x += dx;
	y += dy;
	charge_x += abs(dx);

	if (charge_x >= MAX_X)
		this->is_dead = true;

}

void PlantFireBullet::Render() {
	int ani = -1;

	if (nx > 0)
		ani = INDEX_ANI_FIRE_BULLET_RIGHT;
	else
		ani = INDEX_ANI_FIRE_BULLET_LEFT;

	animation_set->at(ani)->Render(x,y);

	//RenderBoundingBox();
}

void PlantFireBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BBOX_WIDTH_PLANT_FIRE_BULLET;
	bottom = y + BBOX_HEIGHT_PLANT_FIRE_BULLET;
}

float PlantFireBullet::calculateSpeedY() {

	float player_x, player_y;

	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetPosition(player_x, player_y);

	float current_distance_x = this->x - player_x;
	float current_distance_y = this->y - player_y;
	float speed_y = (current_distance_y / current_distance_x) * this->vx;
	if (speed_y > MAX_SPEED_Y) speed_y = MAX_SPEED_Y;

	return speed_y;

}